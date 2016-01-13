/*
    #============================================================#
    File: util.c
    Description: C file - util
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
#include <fcntl.h>   /* File control definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <time.h>  
#include <sys/time.h>

#include "util.h"

//non blocking getchar
int util_getch(void)
{
struct termios oldt,
newt;
int ch=-1;
tcgetattr( STDIN_FILENO, &oldt );
newt = oldt;
newt.c_lflag &= ~( ICANON | ECHO );
tcsetattr( STDIN_FILENO, TCSANOW, &newt );
fcntl(STDIN_FILENO, F_SETFL, FNDELAY);
ch = getchar();
fcntl(STDIN_FILENO, F_SETFL, 0);
tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
return ch;
}

//return timestamp in seconds with microsecond resolution
double util_timestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL); 
  return (double)tv.tv_sec+((double)tv.tv_usec)/1000000;
}

//return timestamp in microseconds since first call to this function
int util_timestamp_int()
{
  static struct timeval tv1;
  struct timeval tv;
  if(tv1.tv_usec==0 && tv1.tv_sec==0) gettimeofday(&tv1, NULL); 
  gettimeofday(&tv, NULL); 
  return (int)(tv.tv_sec-tv1.tv_sec)*1000000+(int)(tv.tv_usec-tv1.tv_usec);
}
