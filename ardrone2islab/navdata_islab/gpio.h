/*
    #============================================================#
    File: gpio.h
    Description: H file - state estimation
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
 * @file mcu_periph/gpio.h
 *
 * Some architecture independent helper functions for GPIOs.
 *
 * Functions which should be supported by each architecture implementation:
 * - gpio_setup_output(port, gpios)
 * - gpio_setup_input(port, gpios)
 * - gpio_set(port, gpios)
 * - gpio_clear(port, gpios)
 * - gpio_toggle(port, gpios)
 *
 * This includes the architecture specific header where the actual functions are declared.
 */

#ifndef MCU_PERIPH_GPIO_H
#define MCU_PERIPH_GPIO_H

#include "std.h"
#include "gpio_arch.h"


#endif /* MCU_PERIPH_GPIO_H */
