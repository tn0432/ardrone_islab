/*
 * File: estimate_ncf.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 24-Jun-2015 13:23:47
 */

#ifndef __ESTIMATE_NCF_H__
#define __ESTIMATE_NCF_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "estimate_ncf_types.h"

/* Function Declarations */
extern void estimate_ncf(double q_est[4], double b_est[3], const double omega[3],
  const double acc[3], double kp, double dt);

#endif

/*
 * File trailer for estimate_ncf.h
 *
 * [EOF]
 */
