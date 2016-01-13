/*
    #============================================================#
    File: navdata_islab.c
    Description: C file - state estimation
    Author: Oscar De Silva (sendtooscar@gmail.com ) 
    Intelligent Systems Lab - Memorial University of Newfoundland - Canada
    Copyright (C) January 2016 

    This is a free software for AR.Drone ver 2.0; you can use, reproduce, 
    redistribute and/or modify it under the terms of Apache License 
    Version 2.0, January 2004 

    This program is distributed in order to foster the study of quadrotor
    trajectory control, but WITHOUT ANY WARRANTY; without even the 
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

    #============================================================#
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>   // for baud rates and options
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <assert.h>
#include <pthread.h>

#include "std.h"
#include "navdata_islab.h"
#include "gpio.h"
#include "../util/util.h"
#include "estimate_rincf_drone/estimate_rincf_drone.h"
#include "transform_mag/transform_mag.h"
#include "rpy2quat/rpy2quat.h"
#include "quat2rpy/quat2rpy.h"

/* Internal used functions */
static void *navdata_read(void *data __attribute__((unused)));
static void navdata_cmd_send(uint8_t cmd);
static bool_t navdata_baro_calib(void);
static void mag_freeze_check(void);
static void baro_update_logic(void);

//Ahrs functions
static void navdata_scale(att_struct* ahrsdata);
static void navdata_attitude_from_acc(att_struct* ahrsdata);
static void navdata_attitude_from_gyro(att_struct* ahrsdata);
static void navdata_attitude_kalman(att_struct* ahrsdata);
void navdata_flattrim(att_struct* ahrsdata);
void navdata_attitude_rincf(att_struct* ahrsdata);

/*navdata structure */
struct navdata_t navdata;

float accs_offset[]                    = { 2040, 2040, 2040 };
const float accs_gains[]               = { 500, 500, 500 }; 
float gyros_offset[]                   = { 0, 0, 0 };
const float gyros_gains[]              = { 939.65, 939.65, 939.65}; //ITG 3050 LSB/rads^-1
float mag_offset[]                     = { -19, 27, -36 };
float mag_norm                         = 77;
double b_e[]                           = { 1, 0, 0 };  //Normalized
const double g_e[]		       = { 0, 0, -1 }; //in g`s
const double K_ss[]			       = {0.0019,    0.0000,      0,   -0.0014,   -0.0000,       0,
                                                  0.0000,    0.0019,      0,   -0.0000,   -0.0014,       0, 
                                                       0,         0,      0,         0,         0,       0,
					               0,         0,      0,         0,         0,       0,  
						       0,         0,      0,         0,         0,       0, 
					          0.0000,    0.0000, 0.0005,   -0.0000,   -0.0000, -0.0001}; 
						//steady state gain in column major format

bool flat_trim_done=false;

/** Buffer filled in the thread (maximum one navdata packet) */
static uint8_t navdata_buffer[NAVDATA_PACKET_SIZE];
/** flag to indicate new packet is available in buffer */
static bool_t navdata_available = FALSE;

/* syncronization variables */
static pthread_mutex_t navdata_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  navdata_cond  = PTHREAD_COND_INITIALIZER;

#ifndef NAVDATA_FILTER_ID
#define NAVDATA_FILTER_ID 2
#endif

/** Sonar offset.
 *  Offset value in ADC
 *  equals to the ADC value so that height is zero
 */
#ifndef SONAR_OFFSET
#define SONAR_OFFSET 880
#endif

/** Sonar scale.
 *  Sensor sensitivity in m/adc (float)
 */
#ifndef SONAR_SCALE
#define SONAR_SCALE 0.00047
#endif

/**
 * Write to fd even while being interrupted
 */
ssize_t full_write(int fd, const uint8_t *buf, size_t count)
{
  size_t written = 0;

  while (written < count) {
    ssize_t n = write(fd, buf + written, count - written);
    if (n < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        continue;
      }
      return n;
    }
    written += n;
  }
  return written;
}

/**
 * Read from fd even while being interrupted
 */
ssize_t full_read(int fd, uint8_t *buf, size_t count)
{
  /* Apologies for illiteracy, but we can't overload |read|.*/
  size_t readed = 0;

  while (readed < count) {
    ssize_t n = read(fd, buf + readed, count - readed);
    if (n < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        continue;
      }
      return n;
    }
    readed += n;
  }
  return readed;
}



/**
 * Initialize the navdata board
 */
bool_t navdata_init()
{
  assert(sizeof(struct navdata_measure_t) == NAVDATA_PACKET_SIZE);
  int test=util_timestamp_int(); //initialize timer (microsecond)

  // Check if the FD isn't already initialized
  if (navdata.fd <= 0) {
    navdata.fd = open("/dev/ttyO1", O_RDWR | O_NOCTTY); //O_NONBLOCK doesn't work

    if (navdata.fd < 0) {
      printf("[navdata] Unable to open navdata board connection(/dev/ttyO1)\n");
      return FALSE;
    }

    // Update the settings of the UART connection
    fcntl(navdata.fd, F_SETFL, 0); //read calls are non blocking
    //set port options
    struct termios options;
    //Get the current options for the port
    tcgetattr(navdata.fd, &options);
    //Set the baud rates to 460800
    cfsetispeed(&options, B460800);
    cfsetospeed(&options, B460800);

    options.c_cflag |= (CLOCAL | CREAD); //Enable the receiver and set local mode
    options.c_iflag = 0; //clear input options
    options.c_lflag = 0; //clear local options
    options.c_oflag &= ~OPOST; //clear output options (raw output)

    //Set the new options for the port
    tcsetattr(navdata.fd, TCSANOW, &options);
  }

  // Reset available flags
  navdata_available = FALSE;
  navdata.baro_calibrated = FALSE;
  navdata.baro_available = FALSE;
  navdata.imu_lost = FALSE;

  // Set all statistics to 0
  navdata.checksum_errors = 0;
  navdata.lost_imu_frames = 0;
  navdata.totalBytesRead = 0;
  navdata.packetsRead = 0;
  navdata.last_packet_number = 0;

  // Stop acquisition
  navdata_cmd_send(NAVDATA_CMD_STOP);

  // Read the baro calibration(blocking)
  if (!navdata_baro_calib()) {
    printf("[navdata] Could not acquire baro calibration!\n");
    return FALSE;
  }
  navdata.baro_calibrated = TRUE;

  // Start acquisition
  navdata_cmd_send(NAVDATA_CMD_START);

  // Set navboard gpio control
  gpio_setup_output(ARDRONE_GPIO_PORT, ARDRONE_GPIO_PIN_NAVDATA);
  gpio_set(ARDRONE_GPIO_PORT, ARDRONE_GPIO_PIN_NAVDATA);

  // Start navdata reading thread
  pthread_t navdata_thread;
  if (pthread_create(&navdata_thread, NULL, navdata_read, NULL) != 0) {
    printf("[navdata] Could not create navdata reading thread!\n");
    return FALSE;
  }


  // Set to initialized
  
  navdata.is_initialized = TRUE;
  return TRUE;
}

static void *navdata_read(void *data __attribute__((unused)))
{
  /* Buffer insert index for reading/writing */
  static uint8_t buffer_idx = 0;

  while (TRUE) {

    // Wait until we are notified to read next data,
    // i.e. buffer has been copied in navdata_update
    pthread_mutex_lock(&navdata_mutex);
    while (navdata_available) {
      pthread_cond_wait(&navdata_cond, &navdata_mutex);
    }
    pthread_mutex_unlock(&navdata_mutex);

    // Read new bytes
    int newbytes = read(navdata.fd, navdata_buffer + buffer_idx, NAVDATA_PACKET_SIZE - buffer_idx);

    // When there was no signal interrupt
    if (newbytes > 0) {
      buffer_idx += newbytes;
      navdata.totalBytesRead += newbytes;
    }

    // If we got a full packet
    if (buffer_idx >= NAVDATA_PACKET_SIZE) {
      // check if the start byte is correct
      if (navdata_buffer[0] != NAVDATA_START_BYTE) {
	uint8_t *pint=(uint8_t*)memchr(navdata_buffer, NAVDATA_START_BYTE, buffer_idx);

        // Check if we found the start byte in the read data
        if (pint != NULL) {
          memmove(navdata_buffer, pint, NAVDATA_PACKET_SIZE - (pint - navdata_buffer));
          buffer_idx = pint - navdata_buffer;
          fprintf(stderr, "[navdata] sync error, startbyte not found, resetting...\n");
        } else {
          buffer_idx = 0;
        }
        continue;
      }

      /* full packet read with startbyte at the beginning, reset insert index */
      buffer_idx = 0;

      // Calculating the checksum
      uint16_t checksum = 0;
      for (int i = 2; i < NAVDATA_PACKET_SIZE - 2; i += 2) {
        checksum += navdata_buffer[i] + (navdata_buffer[i + 1] << 8);
      }

      struct navdata_measure_t *new_measurement = (struct navdata_measure_t *)navdata_buffer; //typecast the packet

      // Check if the checksum is ok
      if (new_measurement->chksum != checksum) {
        fprintf(stderr, "[navdata] Checksum error [calculated: %d] [packet: %d] [diff: %d]\n",
                checksum, new_measurement->chksum, checksum - new_measurement->chksum);
        navdata.checksum_errors++;
	//usleep(1000);
        continue;
      }

      // set flag that we have new valid navdata
      pthread_mutex_lock(&navdata_mutex);
      navdata_available = TRUE;
      pthread_mutex_unlock(&navdata_mutex);
    }
  }

  return NULL;
}

/**
 * Update the navdata (event loop)
 */
void navdata_update(att_struct* ahrsdata)
{
  //

  // Check if initialized
  if (!navdata.is_initialized) {
    navdata_init();
    mag_freeze_check();
    return;
  }

  pthread_mutex_lock(&navdata_mutex);
  // If we got a new navdata packet
  if (navdata_available) {

    // Copy the navdata packet
    memcpy(&navdata.measure, navdata_buffer, NAVDATA_PACKET_SIZE);

    // reset the flag
    navdata_available = FALSE;
    // signal that we copied the buffer and new packet can be read
    pthread_cond_signal(&navdata_cond);
    pthread_mutex_unlock(&navdata_mutex);

    // Check if we missed a packet (our counter and the one from the navdata)
    navdata.last_packet_number++;
    if (navdata.last_packet_number != navdata.measure.nu_trame) {
      fprintf(stderr, "[navdata] Lost frame: %d should have been %d\n",
              navdata.measure.nu_trame, navdata.last_packet_number);
      navdata.lost_imu_frames++;

    }
  
    navdata.last_packet_number = navdata.measure.nu_trame;

    // Invert byte order so that TELEMETRY works better
    uint8_t tmp;
    uint8_t *p = (uint8_t *) & (navdata.measure.pressure);
    tmp = p[0];
    p[0] = p[1];
    p[1] = tmp;
    p = (uint8_t *) & (navdata.measure.temperature_pressure);
    tmp = p[0];
    p[0] = p[1];
    p[1] = tmp;

    baro_update_logic();
    mag_freeze_check();


    // Check if there is a new sonar measurement and update the sonar
    if (navdata.measure.ultrasound >> 15) {
      float sonar_meas = (float)((navdata.measure.ultrasound & 0x7FFF) - SONAR_OFFSET) * SONAR_SCALE;
    }

    //if(flat_trim_done==true){
    double tic=util_timestamp();
    navdata_scale(ahrsdata);			// gyro bias init, zero r,p,y,
    //navdata_attitude_from_acc(ahrsdata);	//1-ok
    //navdata_attitude_from_mag();		//2 -!
    //navdata_attitude_from_gyro(ahrsdata);	//3-ok
    navdata_attitude_rincf(ahrsdata);		//4-ok mag check
    //navdata_attitude_kalman_predict();	//4
    //navdata_attitude_kalman_correct();	//5
    ahrsdata->dt2=util_timestamp()-tic;		//code time check
    //}

    navdata.packetsRead++;
  } else {
    // no new packet available, still unlock mutex again
    pthread_mutex_unlock(&navdata_mutex);
  }
}

static void navdata_scale(att_struct* ahrsdata){
	//check if its a new packet -- this is already done in the calling function
	
	//cordinate system

	//scale acccelerometer
	ahrsdata->ax=(navdata.measure.ax-accs_offset[0])/accs_gains[0]; //in gs
	ahrsdata->ay=(navdata.measure.ay-accs_offset[1])/accs_gains[1]; 
	ahrsdata->az=(navdata.measure.az-accs_offset[2])/accs_gains[2]; 

	//scale gyroscope
	ahrsdata->wx=(navdata.measure.vx-gyros_offset[0])/gyros_gains[0]; // in rad/secs
	ahrsdata->wy=(navdata.measure.vy-gyros_offset[1])/gyros_gains[1]; 
	ahrsdata->wz=(navdata.measure.vz-gyros_offset[2])/gyros_gains[2];

	//scale magnetometer - using default values (call mag calib function for accurate calibearation
	//axis correction
        ahrsdata->magX=navdata.measure.mx;
	ahrsdata->magY=-navdata.measure.my;
	ahrsdata->magZ=-navdata.measure.mz;

	//debias	
	ahrsdata->magX=ahrsdata->magX-mag_offset[0];  
	ahrsdata->magY=ahrsdata->magY-mag_offset[1];
        ahrsdata->magZ=ahrsdata->magZ-mag_offset[2];
	
	
	//normalize
	//double magnorm=sqrt((ahrsdata->magX*ahrsdata->magX + ahrsdata->magY*ahrsdata->magY) + ahrsdata->magZ*ahrsdata->magZ);
	//ahrsdata->magX=ahrsdata->magX/mag_norm;
	//ahrsdata->magY=ahrsdata->magY/mag_norm;
	//ahrsdata->magZ=ahrsdata->magZ/mag_norm;	

	//to do calib and normalize

	//timing
	ahrsdata->tm_pre=ahrsdata->tm;
	ahrsdata->tm=util_timestamp();
	ahrsdata->dt=ahrsdata->tm-ahrsdata->tm_pre; //this tells if your code is going below 500Hz
	ahrsdata->frame=navdata.measure.nu_trame;	
	//ahrsdata.tm=util_timestamp();

	
	//scale gyroscope
	//scale magnetometer
	
}

//1
static void navdata_attitude_from_acc(att_struct* ahrsdata){
	//testeted working perfect-ok
	//cordinate frame - +x back to front , +y rigth to left, +z down to up
	//ahrsdata->pitch_a=atan2(-ahrsdata->ax,ahrsdata->az);
	//ahrsdata->roll_a=atan2(ahrsdata->ay,sqrt(pow(ahrsdata->ax,2.0)+pow(ahrsdata->az,2.0)));
	ahrsdata->pitch_a=-atan2(ahrsdata->ax,sqrt(pow(ahrsdata->ay,2.0)+pow(ahrsdata->az,2.0)));
	ahrsdata->roll_a=atan2(ahrsdata->ay,ahrsdata->az);
}


//2
static void navdata_attitude_from_gyro(att_struct* ahrsdata){
	float wx= ahrsdata->wx;
	float wy= ahrsdata->wy;
	float wz= ahrsdata->wz;
	float thr= ahrsdata->roll_w;
	float thp= ahrsdata->pitch_w;
	float thy= ahrsdata->yaw_w;

	float dthr=wx*cos(thp) + wz*sin(thp);
        float dthp=wy - (wz*cos(thp)*sin(thr))/cos(thr) + (wx*sin(thp)*sin(thr))/cos(thr);
        float dthy=(wz*cos(thp))/cos(thr) - (wx*sin(thp))/cos(thr);
	ahrsdata->roll_w  += dthr * ahrsdata->dt;
	ahrsdata->pitch_w += dthp * ahrsdata->dt;
	ahrsdata->yaw_w   += dthy * ahrsdata->dt;
	
}

//3
void navdata_flattrim(att_struct* ahrsdata){
	//check if nav_data available	

	//find bias of gyros
	float wx_corr=0;
	float wy_corr=0;
	float wz_corr=0;
	b_e[0]=0;b_e[1]=0;b_e[2]=0;
	float frame=0;
	int j=0;
	navdata_update(ahrsdata);
	usleep(4000);
	//for(int i=0;i<100;i++){
	while(j<100){
		navdata_update(ahrsdata);
		
		//debug
		if(ahrsdata->frame-frame>0.9){
			wx_corr+=(float)navdata.measure.vx;
			wy_corr+=(float)navdata.measure.vy;
			wz_corr+=(float)navdata.measure.vz;
			//b_e[0]+=(float)navdata.measure.mx;
			//b_e[1]-=(float)navdata.measure.my; //correct direction aswell
			//b_e[2]-=(float)navdata.measure.mz;
			frame=ahrsdata->frame;
			j=j+1;
			
		}
		else{
			//printf(".");
			frame=ahrsdata->frame;
		}
		usleep(1000);	//sync sleep 5ms
		
		 
	}
	//printf("%f|%f|%f\n",wx_corr,wy_corr,wz_corr);
	//gyro bias init
	gyros_offset[0]=wx_corr/j;
	gyros_offset[1]=wy_corr/j;
        gyros_offset[2]=wz_corr/j;
	b_e[0]=navdata.measure.mx-mag_offset[0];
	b_e[1]=-navdata.measure.my-mag_offset[1];
	b_e[2]=-navdata.measure.mz-mag_offset[2];

	b_e[2]=0;
	
	//mag norm and mag vector init
	mag_norm=sqrt((b_e[0]*b_e[0] + b_e[1]*b_e[1]) + b_e[2]*b_e[2]);	
	b_e[0]=b_e[0]/mag_norm;
	b_e[1]=b_e[1]/mag_norm;
	b_e[2]=b_e[2]/mag_norm;

	//initialize filters
	ahrsdata->roll_w=0;
	ahrsdata->pitch_w=0;
	ahrsdata->yaw_w=0;
	ahrsdata->roll=0;
	ahrsdata->pitch=0;
	ahrsdata->yaw=0;
	ahrsdata->q_est[0]=1;ahrsdata->q_est[1]=0;ahrsdata->q_est[2]=0;ahrsdata->q_est[3]=0;
	ahrsdata->b_est[0]=0;ahrsdata->b_est[1]=0;ahrsdata->b_est[2]=0;

	flat_trim_done=true;
	
}


//4
/* void navdata_attitude_from_mag(){
}*/

//5
/* void navdata_attitude_kalman(){
}*/

/**
 * Sends a one byte commandThe accelerometer bias are not dealt with
by the attitude estimation algorithm. They are in fact estimated
and compensated thanks to the vision system as presented in
Section 4. Under this assumption, various algorithms for atti-
tude estimation can been considered: Kalman filter, extended
Kalman filter (s
 */
static void navdata_cmd_send(uint8_t cmd)
{
  full_write(navdata.fd, &cmd, 1);
  //navdata_scale();
    //navdata_attitude_from_acc();
    //navdata_attitude_from_mag();
    //navdata_attitude_from_gyro();
    //navdata_attitude_kalman();
}


/**
 * Try to receive the baro calibration from the navdata board
 */
static bool_t navdata_baro_calib(void)
{
  // Start baro calibration acquisition
  navdata_cmd_send(NAVDATA_CMD_BARO_CALIB);

  // Receive the calibration (blocking)
  uint8_t calibBuffer[22];
  if (full_read(navdata.fd, calibBuffer, sizeof calibBuffer) < 0) {
    printf("[navdata] Could not read calibration data.");
    return FALSE;
  }

  //Convert the read bytes
  navdata.bmp180_calib.ac1 = calibBuffer[0]  << 8 | calibBuffer[1];
  navdata.bmp180_calib.ac2 = calibBuffer[2]  << 8 | calibBuffer[3];
  navdata.bmp180_calib.ac3 = calibBuffer[4]  << 8 | calibBuffer[5];
  navdata.bmp180_calib.ac4 = calibBuffer[6]  << 8 | calibBuffer[7];
  navdata.bmp180_calib.ac5 = calibBuffer[8]  << 8 | calibBuffer[9];
  navdata.bmp180_calib.ac6 = calibBuffer[10] << 8 | calibBuffer[11];
  navdata.bmp180_calib.b1  = calibBuffer[12] << 8 | calibBuffer[13];
  navdata.bmp180_calib.b2  = calibBuffer[14] << 8 | calibBuffer[15];
  navdata.bmp180_calib.mb  = calibBuffer[16] << 8 | calibBuffer[17];
  navdata.bmp180_calib.mc  = calibBuffer[18] << 8 | calibBuffer[19];
  navdata.bmp180_calib.md  = calibBuffer[20] << 8 | calibBuffer[21];

  return TRUE;
}

/**
 * Check if the magneto is frozen
 * Unknown why this bug happens.
 */
static void mag_freeze_check(void)
{
  // Thanks to Daren.G.Lee for initial fix on 20140530
  static int16_t LastMagValue = 0;
  static int MagFreezeCounter = 0;

  if (LastMagValue == navdata.measure.mx) {
    MagFreezeCounter++;

    // has to have at least 30 times the same value to consider it a frozen magnetometer value
    if (MagFreezeCounter > 30) {
      fprintf(stderr, "mag freeze detected, resetting!\n");

      // set imu_lost flag
      navdata.imu_lost = TRUE;
      navdata.lost_imu_frames++;

      // Stop acquisition
      navdata_cmd_send(NAVDATA_CMD_STOP);

      // Reset the hardware of the navboard
      gpio_clear(ARDRONE_GPIO_PORT, ARDRONE_GPIO_PIN_NAVDATA);
      usleep(20000);
      gpio_set(ARDRONE_GPIO_PORT, ARDRONE_GPIO_PIN_NAVDATA);

      // Wait for 40ms for it to boot
      usleep(40000);

      // Start the navdata again and reset the counter
      navdata_cmd_send(NAVDATA_CMD_START);
      MagFreezeCounter = 0; // reset counter back to zero
    }
  } else {
    navdata.imu_lost = FALSE;
    // Reset counter if value _does_ change
    MagFreezeCounter = 0;
  }
  // set last value
  LastMagValue = navdata.measure.mx;
}

/**
 * Handle the baro(pressure/temperature) logic
 * Sometimes the temperature and pressure are switched because of a bug in
 * the navdata board firmware.
 */
static void baro_update_logic(void)
{
  static int32_t lastpressval = 0;
  static uint16_t lasttempval = 0;
  static int32_t lastpressval_nospike = 0;
  static uint16_t lasttempval_nospike = 0;
  static uint8_t temp_or_press_was_updated_last =
    0; // 0 = press, so we now wait for temp, 1 = temp so we now wait for press

  static int sync_errors = 0;
  static int spike_detected = 0;

  if (temp_or_press_was_updated_last == 0) { // Last update was press so we are now waiting for temp
    // temp was updated
    temp_or_press_was_updated_last = TRUE;

    // This means that press must remain constant
    if (lastpressval != 0) {
      // If pressure was updated: this is a sync error
      if (lastpressval != navdata.measure.pressure) {
        // wait for temp again
        temp_or_press_was_updated_last = FALSE;
        sync_errors++;
        //printf("Baro-Logic-Error (expected updated temp, got press)\n");
      }
    }
  } else {
    // press was updated
    temp_or_press_was_updated_last = FALSE;

    // This means that temp must remain constant
    if (lasttempval != 0) {
      // If temp was updated: this is a sync error
      if (lasttempval != navdata.measure.temperature_pressure) {
        // wait for press again
        temp_or_press_was_updated_last = TRUE;
        sync_errors++;
        //printf("Baro-Logic-Error (expected updated press, got temp)\n");

      } else {
        // We now got valid pressure and temperature
        navdata.baro_available = TRUE;
      }
    }
  }

  // Detected a pressure switch
  if (lastpressval != 0 && lasttempval != 0
      && ABS(lastpressval - navdata.measure.pressure) > ABS(lasttempval - navdata.measure.pressure)) {
    navdata.baro_available = FALSE;
  }

  // Detected a temprature switch
  if (lastpressval != 0 && lasttempval != 0
      && ABS(lasttempval - navdata.measure.temperature_pressure) > ABS(lastpressval - navdata.measure.temperature_pressure)) {
    navdata.baro_available = FALSE;
  }

  lasttempval = navdata.measure.temperature_pressure;
  lastpressval = navdata.measure.pressure;

  /*
   * It turns out that a lot of navdata boards have a problem (probably interrupt related)
   * in which reading I2C data and writing uart output data is interrupted very long (50% of 200Hz).
   * Afterwards, the 200Hz loop tries to catch up lost time but reads the baro too fast swapping the
   * pressure and temperature values by exceeding the minimal conversion time of the bosh baro. The
   * normal Parrot firmware seems to be perfectly capable to fly with this, either with excessive use of
   * the sonar or with software filtering or spike detection. Paparazzi with its tightly coupled baro-altitude
   * had problems. Since this problems looks not uncommon a detector was made. A lot of evidence is grabbed
   * with a logic analyzer on the navboard I2C and serial output. The UART CRC is still perfect, the baro
   * temp-press-temp-press logic is still perfect, so not easy to detect. Temp and pressure are swapped,
   * and since both can have almost the same value, the size of the spike is not predictable. However at
   * every spike of at least 3 broken boards the press and temp are byte-wise exactly the same due to
   * reading them too quickly (trying to catch up for delay that happened earlier due to still non understood
   * reasons. As pressure is more likely to quickly change, a small (yet unlikely) spike on temperature together with
   * press==temp yields very good results as a detector, although theoretically not perfect.

  #samp press temp.
  50925 39284 34501
  50926 39287 34501
  50927 39287 34501
  50928 39283 34501     // *press good -> baro
  50929 39283 34501
  50930 39285 34501     // *press good -> baro
  50931 39285 34500
  50932 34500 34500     // press read too soon from chip (<4.5ms) -> ADC register still previous temp value
  50933 34500 36618     // press not updated, still wrong. Temp is weird: looks like the average of both
  50934 39284 36618     // new press read, but temp still outdated
  50935 39284 34501
  50936 39284 34501     // *press good -> baro
  50937 39284 34500
  50938 39281 34500
  50939 39281 34500
  50940 39280 34500
  50941 39280 34502
  50942 39280 34502
  50943 39280 34501

   */

  // if press and temp are same and temp has jump: neglect the next frame
  if (navdata.measure.temperature_pressure ==
      navdata.measure.pressure) { // && (abs((int32_t)navdata.temperature_pressure - (int32_t)lasttempval) > 40))
    // dont use next 3 packets
    spike_detected = 3;
  }

  if (spike_detected > 0) {
    // disable kalman filter use
    navdata.baro_available = FALSE;

    // override both to last good
    navdata.measure.pressure = lastpressval_nospike;
    navdata.measure.temperature_pressure = lasttempval_nospike;

    // Countdown
    spike_detected--;
  } else { // both are good
    lastpressval_nospike = navdata.measure.pressure;
    lasttempval_nospike = navdata.measure.temperature_pressure;
  }
}

/*Calculated the attitude using a right invariant nonlinear complimenary filter

*/

void navdata_attitude_rincf(att_struct* ahrsdata){
	double omega[3]= {ahrsdata->wx, ahrsdata->wy, ahrsdata->wz};
	double acc[3]= {ahrsdata->ax, ahrsdata->ay, ahrsdata->az};
        double mag[3]= {ahrsdata->magX, ahrsdata->magY, ahrsdata->magZ};
        double mag_corr[3]= {0,0,0};
	double x_est[7]={ahrsdata->q_est[0],ahrsdata->q_est[1],ahrsdata->q_est[2],ahrsdata->q_est[3],ahrsdata->b_est[0],ahrsdata->b_est[1],ahrsdata->b_est[2]};	
	double yaw;
	double pitch;
	double roll;

	//rpy2quat(ahrsdata->yaw, ahrsdata->pitch, ahrsdata->roll, q);

	transform_mag(mag, ahrsdata->pitch, ahrsdata->roll, mag_corr);
	estimate_rincf_drone(x_est,omega,acc,mag_corr,K_ss,g_e,b_e,ahrsdata->dt);
	//estimate_ncf(ahrsdata->q_est,ahrsdata->b_est,omega,acc,0.1,ahrsdata->dt);
	double q[4]={x_est[0],x_est[1],x_est[2],x_est[3]};
	quat2rpy(q, &yaw, &pitch, &roll);
	ahrsdata->yaw=yaw;
	ahrsdata->pitch=pitch;
	ahrsdata->roll=roll;
	ahrsdata->q_est[0]=x_est[0];
	ahrsdata->q_est[1]=x_est[1];
	ahrsdata->q_est[2]=x_est[2];
	ahrsdata->q_est[3]=x_est[3];
	ahrsdata->b_est[0]=x_est[4];
	ahrsdata->b_est[1]=x_est[5];
	ahrsdata->b_est[2]=x_est[6];

}



