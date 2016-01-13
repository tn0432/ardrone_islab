/*
 * File: estimate_rincf_drone.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 27-Aug-2015 20:15:44
 */

#ifndef __ESTIMATE_RINCF_DRONE_H__
#define __ESTIMATE_RINCF_DRONE_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "estimate_rincf_drone_types.h"

/* Function Declarations */
extern void estimate_rincf_drone(double x_est[7], const double omega[3], const
  double acc[3], const double mag[3], const double K_ss[36], const double g_e[3],
  const double b_e[3], double dt);

#endif

/*
 * File trailer for estimate_rincf_drone.h
 *
 * [EOF]
 */
