/*
    #============================================================#
    File: controlthread_pid.c 
    Description: C file - Motion Control Thread
    Author: Trung Nguyen (tn0432@mun.ca) 
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


#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h>  //exit()
#include <pthread.h>
#include <math.h>

#include "util/type.h"
#include "util/util.h"
#include "motorboard/mot.h"
#include "navdata_islab/navdata_islab.h"
#include "udp/udp.h"
#include "pid.h"
#include "controlthread_pid.h"

float adj_roll;
float adj_pitch;
float adj_yaw;
float adj_h;

pthread_t ctl_thread;

pid_struct pid_roll;
pid_struct pid_pitch;

float throttle;

struct att_struct ahrsdata;

struct setpoint_struct {
  float pitch;     //radians  
  float roll;      //radians     
  float yaw;     //yaw in radians   
  float h;         
  float pitch_roll_max; //radians     
  float throttle_min; //min throttle (while flying)
  float throttle_max; //max throttle (while flying)
} setpoint;

udp_struct udpNavLog;
int logcnt=0;
void navLog_Send();
void *ctl_thread_main(void* data);

int ctl_Init(char *client_addr) 
{
	int rc;
       
	//----- Initialize PID controller -----//
	//some saturation for controller
	setpoint.pitch_roll_max=DEG2RAD(10); //degrees      
  	setpoint.throttle_min=0.05;//0.5
  	setpoint.throttle_max=0.95; //0.85
  			
	//init pid pitch/roll //Kp, Ki, Kd, imax
	pid_Init(&pid_roll,  0.33,0.0,0.25,1); //[0.35 0.25] with additional part [0.33 0.25] without ...
	pid_Init(&pid_pitch, 0.33,0.0,0.25,1);
  	throttle=0.000;

	//----- Initialize AHRS system -----// 
  	printf("Initialize Attitude.. \n");
	//rc = att_Init(&att);
	//if(rc) return rc;
	if(navdata_init()) printf("navdata initialized\n");
	navdata_flattrim(&ahrsdata);
	//printf("bias_after:%f\t%f\t%f\n",gyros_offset[0],gyros_offset[1],gyros_offset[2]);
        sleep(1);


	//----- Initialize UDP -----//
  	// Udp logger
  	printf("client\n");
  	udpClient_Init(&udpNavLog, "192.168.43.176", 9930); // Update the IP of ground station to send data
	//udpClient_Init(&udpNavLog, "192.168.1.4", 9930);
  	//navLog_Send();
  	printf("udpClient_Init\n", rc);
  
	//----- Start motor thread -----//
	printf("Initialize motor\n");
	rc = mot_Init();
	if(rc) return rc;
  
	//----- Start ctl thread -----//
	printf("Initialize ctl_thread_main\n"); 
	rc = pthread_create(&ctl_thread, NULL, ctl_thread_main, NULL); 
	if(rc) {
		printf("ctl_Init: Return code from pthread_create(mot_thread) is %d\n", rc);
		return 202;
	}
	else printf("rc = %d\n", rc);


}

void *ctl_thread_main(void* data)
{
	int cnt;
	int rc;
	//printf("run pthread");
	//navdata_update(&ahrsdata); //get data from thread	
    
	while(1) {
		// get navdata
		navdata_update(&ahrsdata); //get data from thread
	
    		float motor[4]; 
    
    		if(setpoint.h<=0.02) {
      			//motors off
      			adj_roll = 0;
      			adj_pitch = 0;
      			adj_h = 0;
      			adj_yaw = 0;
      			throttle = 0;
		}else{    
 
      			//attitude pid controller
      			adj_roll  = pid_Calc(&pid_roll,  setpoint.roll   - ahrsdata.roll,  ahrsdata.dt);
      			adj_pitch = pid_Calc(&pid_pitch, setpoint.pitch  - ahrsdata.pitch, ahrsdata.dt);
      			adj_yaw = setpoint.yaw;    
      			throttle = setpoint.h;
      			if(throttle < setpoint.throttle_min) throttle = setpoint.throttle_min;
      			if(throttle > setpoint.throttle_max) throttle = setpoint.throttle_max;  
    		}
    
    	// Convert pid adjustments to motor values
        motor[0] = throttle +adj_roll -adj_pitch +adj_yaw;
    	motor[1] = throttle -adj_roll -adj_pitch -adj_yaw;
    	motor[2] = throttle -adj_roll +adj_pitch +adj_yaw;
    	motor[3] = throttle +adj_roll +adj_pitch -adj_yaw;
    	
    	float motor_min = 0.125;
    	if(motor[0] < motor_min) motor[0] = motor_min;
    	if(motor[1] < motor_min) motor[1] = motor_min;
    	if(motor[2] < motor_min) motor[2] = motor_min;
    	if(motor[3] < motor_min) motor[3] = motor_min;

    	ahrsdata.motor1 = motor[0];
    	ahrsdata.motor2 = motor[1];
    	ahrsdata.motor3 = motor[2];
    	ahrsdata.motor4 = motor[3];
	
    	//printf("motor: %.5f,%.5f,%.5f,%.5f\n",motor[0],motor[1],motor[2],motor[3]);
   	//printf("throttle = %.5f, adj_roll = %0.5f, adj_pitch = %0.5f, adj_yaw = %0.5f \n", throttle,adj_roll,adj_pitch,adj_yaw);
    	//printf("throttle = %.5f, adj_roll = %0.5f, adj_pitch = %0.5f, motor: %.5f,%.5f,%.5f,%.5f \n", throttle,adj_roll,adj_pitch,motor[0],motor[1],motor[2],motor[3]);
    	//send to motors
    	mot_Run(motor[0],motor[1],motor[2],motor[3]); // Comment when you do not want motors rotate
        
    	//blink leds    
    	cnt++;
    	if((cnt%200)==0) 
      		mot_SetLeds(MOT_LEDGREEN,MOT_LEDGREEN,MOT_LEDGREEN,MOT_LEDGREEN);
    	else if((cnt%200)==100) 
      		mot_SetLeds(0,0,0,0);
        
    	// Send UDP nav log packet    
    	navLog_Send();
  
	// Yield to other threads
	pthread_yield();
	}
}


//logging
void navLog_Send()
{
  char logbuf[512];
  int logbuflen;

  float motval[4];
	mot_GetMot(motval);
  
  logcnt++;//38
  logbuflen=sprintf(logbuf,(char*)" %.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f "
    //sequence+timestamp
    ,ahrsdata.tm   // navdata timestamp in sec
    ,ahrsdata.tm_pre   
    ,ahrsdata.frame

    ,ahrsdata.pitch_w  //=sum(gx * dt)
    ,ahrsdata.pitch_a  //=pitch(az,ax)
    ,ahrsdata.pitch    //kalman pitch estimate from gy and pitch_a

    //roll estimates in radians, positive is roll right (fly rightward)
    ,ahrsdata.roll_w   //=sum(gy * dt)
    ,ahrsdata.roll_a   //=roll(az,ay)
    ,ahrsdata.roll     //kalman roll estimate from gx and roll_a
  
    //yaw estimate, positive is yaw left
    ,ahrsdata.yaw_w      //=sum(gz * dt)
    ,ahrsdata.yaw_m      //=sum(gz * dt)
    ,ahrsdata.yaw      //=sum(gz * dt)

    ,ahrsdata.dt  // time since last navdata sample in sec
    ,ahrsdata.dt2 // time consumed by the ahrs calculations
    ,ahrsdata.q_est[0]
    ,ahrsdata.q_est[1]
    ,ahrsdata.q_est[2]
    ,ahrsdata.q_est[3]
    ,ahrsdata.b_est[0]
    ,ahrsdata.b_est[1]
    ,ahrsdata.b_est[2]
  
    //copy of physical navdata values
    ,ahrsdata.ts  // navdata timestamp in sec
    ,ahrsdata.hraw    // height above ground in [cm] 
    ,ahrsdata.h_meas// 1=height was measured in this sample, 0=height is copy of prev value

    ,ahrsdata.ax   // acceleration x-axis in [G] front facing up is positive         
    ,ahrsdata.ay   // acceleration y-axis in [G] left facing up is positive                
    ,ahrsdata.az   // acceleration z-axis in [G] top facing up is positive            
    ,ahrsdata.wx   // gyro value x-axis in [rad/sec] right turn, i.e. roll right is positive           
    ,ahrsdata.wy   // gyro value y-axis in [rad/sec] right turn, i.e. pirch down is positive                     
    ,ahrsdata.wz   // gyro value z-axis in [rad/sec] right turn, i.e. yaw left is positive
    ,ahrsdata.magX
    ,ahrsdata.magY 
    ,ahrsdata.magZ
    ,ahrsdata.pressure
    ,ahrsdata.rotX
    ,ahrsdata.rotY
    ,ahrsdata.rotZ
    ,ahrsdata.altd
    ,ahrsdata.motor1
    ,ahrsdata.motor2
    ,ahrsdata.motor3
    ,ahrsdata.motor4
  );    
  udpClient_Send(&udpNavLog,logbuf,logbuflen); 
}

void ctl_SetSetpoint(float pitch, float roll, float yaw, float h)
{
  if(pitch > setpoint.pitch_roll_max) pitch = setpoint.pitch_roll_max;
  if(pitch < -setpoint.pitch_roll_max) pitch = -setpoint.pitch_roll_max;
  setpoint.pitch=pitch;
  if(roll > setpoint.pitch_roll_max) roll = setpoint.pitch_roll_max;
  if(roll < -setpoint.pitch_roll_max) roll = -setpoint.pitch_roll_max;
  setpoint.roll=roll;
  setpoint.yaw=yaw;
  setpoint.h = h;
}

