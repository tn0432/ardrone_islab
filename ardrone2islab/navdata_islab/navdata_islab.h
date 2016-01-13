/*
    #============================================================#
    File: navdata_islab.h
    Description: H file - state estimation
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

#ifndef NAVDATA_H_
#define NAVDATA_H_

#include "std.h"

/**
 * Main navdata structure from the navdata board
 * This is received from the navdata board at ~200Hz
 */

struct att_struct {
  double tm; //timestamp in sec
  double tm_pre;
  float   frame;

  //pitch estimates in radians, positive is pitch down (fly forward)
  float pitch_w;  //=sum(gx * dt)
  float pitch_a;  //=pitch(az,ax)
  float pitch;    //kalman pitch estimate from gy and pitch_a

  //roll estimates in radians, positive is roll right (fly rightward)
  float roll_w;   //=sum(gy * dt)
  float roll_a;   //=roll(az,ay)
  float roll;     //kalman roll estimate from gx and roll_a
  
  //yaw estimate, positive is yaw left
  float yaw_w;      //=sum(gz * dt)
  float yaw_m;      //=sum(gz * dt)
  float yaw;      //=sum(gz * dt)
  
  double dt;  // time since last navdata sample in sec
  double dt2; // time consumed by the ahrs calculations

  double q_est[4];
  double b_est[3];
  
  //copy of physical navdata values
  	double ts;  // navdata timestamp in sec
  	float hraw;    // height above ground in [cm] 
  	char h_meas;// 1=height was measured in this sample, 0=height is copy of prev value
  	float ax;   // acceleration x-axis in [G] front facing up is positive         
	float ay;   // acceleration y-axis in [G] left facing up is positive                
	float az;   // acceleration z-axis in [G] top facing up is positive  
           
	float wx;   // gyro value x-axis in [rad/sec] right turn, i.e. roll right is positive           
	float wy;   // gyro value y-axis in [rad/sec] right turn, i.e. pirch down is positive                     
	float wz;   // gyro value z-axis in [rad/sec] right turn, i.e. yaw left is positive

	float magX;
	float magY; 
	float magZ;

	float pressure;

	float rotX;
	float rotY;
	float rotZ;

	float altd;

	float motor1;
	float motor2;
	float motor3;
	float motor4;

	float x;
	float y;
	float z;
	float vx;
	float vy;
	float vz;
};

struct navdata_measure_t {
  uint16_t taille;
  uint16_t nu_trame;

  uint16_t ax;
  uint16_t ay;
  uint16_t az;

  int16_t vx;
  int16_t vy;
  int16_t vz;
  uint16_t temperature_acc;
  uint16_t temperature_gyro;

  uint16_t ultrasound;

  uint16_t us_debut_echo;
  uint16_t us_fin_echo;
  uint16_t us_association_echo;
  uint16_t us_distance_echo;

  uint16_t us_curve_time;
  uint16_t us_curve_value;
  uint16_t us_curve_ref;

  uint16_t nb_echo;

  uint32_t sum_echo; //unsigned long
  int16_t gradient;

  uint16_t flag_echo_ini;

  int32_t pressure;
  uint16_t temperature_pressure;

  int16_t my;
  int16_t mx;
  int16_t mz;

  uint16_t chksum;

} __attribute__((packed));

/* The baro calibration received from the navboard */
struct bmp180_calib_t {
  int16_t ac1;
  int16_t ac2;
  int16_t ac3;
  uint16_t ac4;
  uint16_t ac5;
  uint16_t ac6;
  int16_t b1;
  int16_t b2;
  int16_t mb;
  int16_t mc;
  int16_t md;

  // These values are calculated
  int32_t b5;
};

/* Navdata board defines */
#define NAVDATA_PACKET_SIZE       60
#define NAVDATA_START_BYTE        0x3A
#define NAVDATA_CMD_START         0x01
#define NAVDATA_CMD_STOP          0x02
#define NAVDATA_CMD_BARO_CALIB    0x17

#define ARDRONE_GPIO_PORT         0x32524
#define ARDRONE_GPIO_PIN_NAVDATA  177

/* Main navdata structure */
struct navdata_t {
  bool_t is_initialized;                  ///< Check if the navdata board is initialized
  int fd;                                 ///< The navdata file pointer

  uint32_t totalBytesRead;
  uint32_t packetsRead;
  uint32_t checksum_errors;
  uint32_t lost_imu_frames;
  uint16_t last_packet_number;

  struct navdata_measure_t measure;       ///< Main navdata packet receieved from navboard
  struct bmp180_calib_t bmp180_calib;     ///< BMP180 calibration receieved from navboard

  bool_t baro_calibrated;                 ///< Whenever the baro is calibrated
  bool_t baro_available;                  ///< Whenever the baro is available
  bool_t imu_lost;                        ///< Whenever the imu is lost
};
extern struct navdata_t navdata;


bool_t navdata_init(void);
void navdata_update(att_struct* ahrsdata);
int16_t navdata_height(void);

/* This should be moved to the uart handling part! */
ssize_t full_write(int fd, const uint8_t *buf, size_t count);
ssize_t full_read(int fd, uint8_t *buf, size_t count);

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
void navdata_attitude_ncf(att_struct* ahrsdata);

#endif /* NAVDATA_H_ */
