/*
    #============================================================#
    File: main_fly_islab_pid.c 
    Description: C file - main function
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
#include <stdlib.h>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <pthread.h>
#include <ctype.h>    /* For tolower() function */
#include <math.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "util/type.h"
#include "util/util.h"
#include "motorboard/mot.h"
#include "udp/udp.h"
#include "controlthread_pid.h"


void diep(const char *s)
{
  perror(s);
  exit(1);
}

int main()
{
  printf("Starting \n");
  //wait for udp packet on port 7777
  udp_struct udpCmd;
  udpServer_Init(&udpCmd,7777,1/*blocking*/);

  char buf[1024];

  //if(udpServer_Init(&udpCmd,9930,0)) diep("udpServer_Init");

  int bufcnt=udpServer_Receive(&udpCmd, buf, 1024);
  if(bufcnt<=0) return 1;;
  buf[bufcnt]=0;
  printf("UDP wakeup received from %s\n",inet_ntoa(udpCmd.si_other.sin_addr));

  //kill program.elf
  int rc = system("/usr/bin/killall program.elf > /dev/null 2>&1");
  printf("kill all main program.elf -> returncode=%d  (0=killed,256=not found)\n",rc);	
  sleep(2);

  //init controller
  ctl_Init(inet_ntoa(udpCmd.si_other.sin_addr));
  printf("ctl_Init completed\n");

  char * pch;

  //main loop	
  while(1) { 
    //wait for next packet on cmd port
    bufcnt=udpServer_Receive(&udpCmd, buf, 1024);
    //printf("%d",bufcnt);

    if(bufcnt<=0) continue;
    buf[bufcnt]=0;
    
    //split tokens
    pch = strtok (buf," ,");
    float frontback = 0.0;
    float leftright = 0.0;
    float updown = 0.0;
    float yawrotate = 0.0;
    int countpart = 0;
    while (countpart<=3)
  	{
    		
		if (countpart == 0) updown = atof(pch);
		if (countpart == 1) frontback = atof(pch);
		if (countpart == 2) leftright = atof(pch);
		if (countpart == 3) yawrotate = atof(pch);
		countpart ++;
    		pch = strtok (NULL, " ,");
  	}
    
    if(countpart==4) {
      	//printf("thrust %.3f,roll %.3f,pitch %.3f,yaw %.3f\n", updown,frontback,leftright,yawrotate);
    	ctl_SetSetpoint(frontback,leftright,yawrotate,updown);
    }

  }
  ctl_Close();
  printf("\nDone...\n");
  return 0;

}
