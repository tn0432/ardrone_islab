/*
 * File: rpy2quat.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 24-Jun-2015 16:06:34
 */

/* Include files */
#include "rt_nonfinite.h"
#include "rpy2quat.h"

/* Function Definitions */

/*
 * Arguments    : double yaw
 *                double pitch
 *                double roll
 *                double q[4]
 * Return Type  : void
 */
void rpy2quat(double yaw, double pitch, double roll, double q[4])
{
  double angles[3];
  double cang[3];
  int i0;
  double b_cang;
  angles[0] = yaw;
  angles[1] = pitch;
  angles[2] = roll;
  for (i0 = 0; i0 < 3; i0++) {
    b_cang = cos(angles[i0] / 2.0);
    angles[i0] = sin(angles[i0] / 2.0);
    cang[i0] = b_cang;
  }

  q[0] = cang[0] * cang[1] * cang[2] + angles[0] * angles[1] * angles[2];
  q[1] = cang[0] * cang[1] * angles[2] - angles[0] * angles[1] * cang[2];
  q[2] = cang[0] * angles[1] * cang[2] + angles[0] * cang[1] * angles[2];
  q[3] = angles[0] * cang[1] * cang[2] - cang[0] * angles[1] * angles[2];
}

/*
 * File trailer for rpy2quat.c
 *
 * [EOF]
 */
