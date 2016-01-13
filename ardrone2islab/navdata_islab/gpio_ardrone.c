/*
    #============================================================#
    File: gpio_ardrone.c
    Description: C file - state estimation
    Author: Oscar De Silva (sendtooscar@gmail.com ) 
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

/**
 * @file boards/ardrone/gpio_ardrone.c
 * ardrone GPIO driver
 */



#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <sys/ioctl.h>

#include "gpio.h"

#define GPIO_MAGIC 'p'
#define GPIO_DIRECTION _IOW(GPIO_MAGIC, 0, struct gpio_direction)
#define GPIO_READ _IOWR(GPIO_MAGIC, 1, struct gpio_data)
#define GPIO_WRITE _IOW(GPIO_MAGIC, 2, struct gpio_data)
int gpiofp = 0;

struct gpio_data {
  int pin;
  int value;
};

enum gpio_mode {
  GPIO_INPUT = 0,             //!< Pin configured for input
  GPIO_OUTPUT_LOW,            //!< Pin configured for output with low level
  GPIO_OUTPUT_HIGH,           //!< Pin configured for output with high level
};

struct gpio_direction {
  int pin;
  enum gpio_mode mode;
};


void gpio_set(uint32_t port, uint16_t pin)
{
  if (port != 0x32524) { return; }  // protect ardrone board from unauthorized use
  struct gpio_data data;
  // Open the device if not open
  if (gpiofp == 0) {
    gpiofp = open("/dev/gpio", O_RDWR);
  }

  // Read the GPIO value
  data.pin = pin;
  data.value = 1;
  ioctl(gpiofp, GPIO_WRITE, &data);
}


void gpio_clear(uint32_t port, uint16_t pin)
{
  if (port != 0x32524) { return; }  // protect ardrone board from unauthorized use
  struct gpio_data data;
  // Open the device if not open
  if (gpiofp == 0) {
    gpiofp = open("/dev/gpio", O_RDWR);
  }

  // Read the GPIO value
  data.pin = pin;
  data.value = 0;
  ioctl(gpiofp, GPIO_WRITE, &data);
}


void gpio_setup_input(uint32_t port, uint16_t pin)
{
  if (port != 0x32524) { return; }  // protect ardrone board from unauthorized use
  struct gpio_direction dir;
  // Open the device if not open
  if (gpiofp == 0) {
    gpiofp = open("/dev/gpio", O_RDWR);
  }

  // Read the GPIO value
  dir.pin = pin;
  dir.mode = GPIO_INPUT;
  ioctl(gpiofp, GPIO_DIRECTION, &dir);
}


void gpio_setup_output(uint32_t port, uint16_t pin)
{
  /*
    if (port != 0x32524) return;  // protect ardrone board from unauthorized use
    struct gpio_direction dir;
    // Open the device if not open
    if (gpiofp == 0)
    gpiofp = open("/dev/gpio",O_RDWR);

    // Read the GPIO value
    dir.pin = pin;
    dir.mode = GPIO_OUTPUT_LOW;
    ioctl(gpiofp, GPIO_DIRECTION, &dir);
  */
}



uint16_t gpio_get(uint32_t port, uint16_t pin)
{
  if (port != 0x32524) { return 0; }  // protect ardrone board from unauthorized use
  struct gpio_data data;
  // Open the device if not open
  if (gpiofp == 0) {
    gpiofp = open("/dev/gpio", O_RDWR);
  }

  // Read the GPIO value
  data.pin = pin;
  ioctl(gpiofp, GPIO_READ, &data);
  return data.value;
}


