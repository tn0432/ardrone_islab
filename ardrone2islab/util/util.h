/*
    #============================================================#
    File: util.h 
    Description: Header file - util
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

#ifndef _UTIL_H
#define _UTIL_H

//degrees to radians
#define DEG2RAD(x) ((x)*3.1415926/180)
//radians to degrees
#define RAD2DEG(x) ((x)/3.1415926*180)

//non blocking getchar
int util_getch(void);
//return timestamp in seconds with microsecond resolution
double util_timestamp();
int util_timestamp_int();
#endif
