/*
    #============================================================#
    File: controlthread_pid.h 
    Description: Header file - Motion Control Thread
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
#ifndef _CONTROLTRHEAD_H
#define _CONTROLTRHEAD_H
int ctl_Init(char *client_addr);
void ctl_SetSetpoint(float pitch, float roll, float yawsp, float h);
void ctl_Close();
#endif
