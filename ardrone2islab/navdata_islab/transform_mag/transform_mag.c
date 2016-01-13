/*
 * File: transform_mag.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 28-Aug-2015 10:33:25
 */

/* Include files */
#include "rt_nonfinite.h"
#include "transform_mag.h"

/* Function Definitions */

/*
 * Arguments    : const double mag[3]
 *                double pitch
 *                double roll
 *                double mag_corr[3]
 * Return Type  : void
 */
void transform_mag(const double mag[3], double pitch, double roll, double
                   mag_corr[3])
{
  double c;
  double s;
  double b_c;
  double b_s;
  double c_c[9];
  double dv0[9];
  int k;
  static const signed char iv0[3] = { 0, 1, 0 };

  static const signed char iv1[3] = { 1, 0, 0 };

  double d_c[9];
  int i0;
  int i1;
  double y;
  double dv1[3];
  c = cos(pitch);
  s = sin(pitch);
  b_c = cos(roll);
  b_s = sin(roll);
  c_c[0] = c;
  c_c[3] = 0.0;
  c_c[6] = s;
  for (k = 0; k < 3; k++) {
    c_c[1 + 3 * k] = iv0[k];
    dv0[3 * k] = iv1[k];
  }

  c_c[2] = -s;
  c_c[5] = 0.0;
  c_c[8] = c;
  dv0[1] = 0.0;
  dv0[4] = b_c;
  dv0[7] = -b_s;
  dv0[2] = 0.0;
  dv0[5] = b_s;
  dv0[8] = b_c;
  for (k = 0; k < 3; k++) {
    for (i0 = 0; i0 < 3; i0++) {
      d_c[k + 3 * i0] = 0.0;
      for (i1 = 0; i1 < 3; i1++) {
        d_c[k + 3 * i0] += c_c[k + 3 * i1] * dv0[i1 + 3 * i0];
      }
    }

    mag_corr[k] = 0.0;
    for (i0 = 0; i0 < 3; i0++) {
      mag_corr[k] += d_c[k + 3 * i0] * mag[i0];
    }
  }

  mag_corr[2] = 0.0;
  y = 0.0;
  c = 2.2250738585072014E-308;
  for (k = 0; k < 3; k++) {
    s = fabs(mag_corr[k]);
    if (s > c) {
      b_c = c / s;
      y = 1.0 + y * b_c * b_c;
      c = s;
    } else {
      b_c = s / c;
      y += b_c * b_c;
    }
  }

  y = c * sqrt(y);
  c = cos(roll);
  s = sin(roll);
  b_c = cos(pitch);
  b_s = sin(pitch);
  for (k = 0; k < 3; k++) {
    dv0[k] = iv1[k];
    mag_corr[k] /= y;
  }

  dv0[3] = 0.0;
  dv0[4] = c;
  dv0[5] = -s;
  dv0[6] = 0.0;
  dv0[7] = s;
  dv0[8] = c;
  c_c[0] = b_c;
  c_c[1] = 0.0;
  c_c[2] = b_s;
  for (k = 0; k < 3; k++) {
    c_c[3 + k] = iv0[k];
  }

  c_c[6] = -b_s;
  c_c[7] = 0.0;
  c_c[8] = b_c;
  for (k = 0; k < 3; k++) {
    for (i0 = 0; i0 < 3; i0++) {
      d_c[k + 3 * i0] = 0.0;
      for (i1 = 0; i1 < 3; i1++) {
        d_c[k + 3 * i0] += dv0[k + 3 * i1] * c_c[i1 + 3 * i0];
      }
    }

    dv1[k] = 0.0;
    for (i0 = 0; i0 < 3; i0++) {
      dv1[k] += d_c[k + 3 * i0] * mag_corr[i0];
    }
  }

  for (k = 0; k < 3; k++) {
    mag_corr[k] = dv1[k];
  }
}

/*
 * File trailer for transform_mag.c
 *
 * [EOF]
 */
