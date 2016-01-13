/*
    #============================================================#
    File: pid.c 
    Description: Header file - PID controller
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
#include "pid.h"

void pid_Init(pid_struct *pid, float kp, float ki, float kd, float i_max) 
{
	pid->kp=kp;
	pid->ki=ki;
	pid->kd=kd;
	pid->i_max=i_max;
	pid->i=0;
	pid->e_prev=0;
}

float pid_CalcD(pid_struct *pid, float error, float dt, float d)
{
	pid->i += error * dt;
	if(pid->i > pid->i_max) pid->i = pid->i_max;
	if(pid->i < -pid->i_max) pid->i = -pid->i_max;
	float out = pid->kp * error + pid->ki * pid->i + pid->kd * d;
	pid->e_prev = error;
	return out;
}

float pid_Calc(pid_struct *pid, float error, float dt)
{
	return pid_CalcD(pid,  error, dt, (error - pid->e_prev)/dt);
}

/*
previous_error = setpoint - actual_position
integral = 0
start:
  error = setpoint - actual_position
  integral = integral + (error*dt)
  derivative = (error - previous_error)/dt
  output = (Kp*error) + (Ki*integral) + (Kd*derivative)
  previous_error = error
  wait(dt)
  goto start
*/
