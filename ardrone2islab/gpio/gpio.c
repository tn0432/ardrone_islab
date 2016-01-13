/*
    #============================================================#
    File: gpio.c 
    Description: C file - GPIO
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

#include <stdio.h>
#include <stdlib.h>
#include "gpio.h"

//val=0 -> set gpio output lo
//val=1 -> set gpio output hi
//val=-1 -> set gpio as input (output hi-Z)
int gpio_set(int nr,int val) 
{
	char cmdline[200];
	if(val<0) sprintf(cmdline,"/usr/sbin/gpio %d -d i",nr);
	else if(val>0) sprintf(cmdline,"/usr/sbin/gpio %d -d ho 1",nr);
	else sprintf(cmdline,"/usr/sbin/gpio %d -d ho 0",nr);
	return system(cmdline);
}


