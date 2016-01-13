/*
    #============================================================#
    File: mot.h 
    Description: Header File - Motor Control
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
#ifndef _MOT_H
#define _MOT_H

#include "../util/type.h"
#include "motorboard.h"

int mot_Init();
void mot_SetLed(u08 mot_id, u08 led);
void mot_SetLeds(u08 led0, u08 led1, u08 led2, u08 led3);
void mot_Stop();
void mot_Run(float m0, float m1, float m2, float m3);
void mot_GetMot(float *m);
void mot_Close();

#endif
