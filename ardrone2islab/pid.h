/*
    #============================================================#
    File: pid.h 
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
struct pid_struct 
{
	float kp;
	float ki;
	float kd;
	float i;
	float e_prev;
	float i_max;
};

void pid_Init(pid_struct *pid, float kp, float ki, float kd, float i_max);
float pid_Calc(pid_struct *pid, float error, float dt);
float pid_CalcD(pid_struct *pid, float error, float dt, float d);

