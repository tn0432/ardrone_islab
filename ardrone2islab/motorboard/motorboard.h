/*
    #============================================================#
    File: motorboard.h
    Description: Header file - Motor Control
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
#ifndef _MOTORBOARD_H
#define _MOTORBOARD_H

#include "../util/type.h"

#define MOT_LEDOFF 0
#define MOT_LEDRED 1
#define MOT_LEDGREEN 2
#define MOT_LEDORANGE 3

int motorboard_Init();
void motorboard_SetPWM(u16 pwm0, u16 pwm1, u16 pwm2, u16 pwm3);
void motorboard_SetLeds(u08 led0, u08 led1, u08 led2, u08 led3);
void motorboard_Close();

#endif
