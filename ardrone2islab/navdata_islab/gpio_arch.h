/*
    #============================================================#
    File: gpio_arch.h
    Description: Header file - state estimation
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
 * @file arch/linux/mcu_periph/gpio_arch.h
 *
 * GPIO helper functions for linux/omap.
 * @todo implement gpio_set|clear
 */

#ifndef GPIO_ARCH_H
#define GPIO_ARCH_H

#include "std.h"

/**
 * Setup one or more pins of the given GPIO port as outputs.
 * @param[in] port
 * @param[in] gpios If multiple pins are to be changed, use logical OR '|' to separate them.
 */
extern void gpio_setup_output(uint32_t port, uint16_t gpios);

/**
 * Setup one or more pins of the given GPIO port as inputs.
 * @param[in] port
 * @param[in] gpios If multiple pins are to be changed, use logical OR '|' to separate them.
 */
extern void gpio_setup_input(uint32_t port, uint16_t gpios);

/**
 * Set a gpio output to high level.
 */
extern void gpio_set(uint32_t port, uint16_t pin);

/**
 * Clear a gpio output to low level.
 */
extern void gpio_clear(uint32_t port, uint16_t pin);


/**
 * Read a gpio value.
 */
extern uint16_t gpio_get(uint32_t gpioport, uint16_t gpios);

#endif /* GPIO_ARCH_H */
