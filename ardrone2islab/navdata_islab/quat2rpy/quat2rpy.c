/*
 * File: quat2rpy.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 24-Jun-2015 17:02:33
 */

/* Include files */
#include "rt_nonfinite.h"
#include "quat2rpy.h"

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2(b_u0, b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(double)(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/*
 * Arguments    : const double q[4]
 *                double *yaw
 *                double *pitch
 *                double *roll
 * Return Type  : void
 */
void quat2rpy(const double q[4], double *yaw, double *pitch, double *roll)
{
  int k;
  double qin[4];
  double qm;
  double scale;
  double absxk;
  double t;
  for (k = 0; k < 4; k++) {
    qin[k] = q[k];
  }

  qm = 0.0;
  scale = 2.2250738585072014E-308;
  for (k = 0; k < 4; k++) {
    absxk = fabs(q[k]);
    if (absxk > scale) {
      t = scale / absxk;
      qm = 1.0 + qm * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      qm += t * t;
    }
  }

  qm = scale * sqrt(qm);
  for (k = 0; k < 4; k++) {
    qin[k] /= qm;
  }

  /*  find angles for rotations about X, Y, and Z axes */
  *yaw = rt_atan2d_snf(2.0 * (qin[1] * qin[2] + qin[0] * qin[3]), ((qin[0] *
    qin[0] + qin[1] * qin[1]) - qin[2] * qin[2]) - qin[3] * qin[3]);
  *pitch = asin(-2.0 * (qin[1] * qin[3] - qin[0] * qin[2]));
  *roll = rt_atan2d_snf(2.0 * (qin[2] * qin[3] + qin[0] * qin[1]), ((qin[0] *
    qin[0] - qin[1] * qin[1]) - qin[2] * qin[2]) + qin[3] * qin[3]);
}

/*
 * File trailer for quat2rpy.c
 *
 * [EOF]
 */
