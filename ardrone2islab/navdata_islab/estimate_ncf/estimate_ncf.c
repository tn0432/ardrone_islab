/*
 * File: estimate_ncf.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 24-Jun-2015 13:23:47
 */

/* Include files */
#include "rt_nonfinite.h"
#include "estimate_ncf.h"

/* Function Definitions */

/*
 * Arguments    : double q_est[4]
 *                double b_est[3]
 *                const double omega[3]
 *                const double acc[3]
 *                double kp
 *                double dt
 * Return Type  : void
 */
void estimate_ncf(double q_est[4], double b_est[3], const double omega[3], const
                  double acc[3], double kp, double dt)
{
  double wx;
  double wy;
  double wz;
  double dv0[16];
  double dv1[16];
  int k;
  int i0;
  double dv2[4];
  double t;
  double Rbe[9];
  double b_Rbe[9];
  double c_Rbe[3];
  double b[3];
  static const double b_b[3] = { 0.0, 0.0, -9.81 };

  double a[3];
  wx = omega[0] + b_est[0];
  wy = omega[1] + b_est[1];
  wz = omega[2] + b_est[2];
  dv0[0] = 0.0;
  dv0[4] = -wx;
  dv0[8] = -wy;
  dv0[12] = -wz;
  dv0[1] = wx;
  dv0[5] = 0.0;
  dv0[9] = wz;
  dv0[13] = -wy;
  dv0[2] = wy;
  dv0[6] = -wz;
  dv0[10] = 0.0;
  dv0[14] = wx;
  dv0[3] = wz;
  dv0[7] = wy;
  dv0[11] = -wx;
  dv0[15] = 0.0;
  for (k = 0; k < 4; k++) {
    for (i0 = 0; i0 < 4; i0++) {
      dv1[i0 + (k << 2)] = 0.5 * dv0[i0 + (k << 2)];
    }
  }

  for (k = 0; k < 4; k++) {
    dv2[k] = 0.0;
    for (i0 = 0; i0 < 4; i0++) {
      wx = dv2[k] + dv1[k + (i0 << 2)] * q_est[i0];
      dv2[k] = wx;
    }
  }

  for (k = 0; k < 4; k++) {
    q_est[k] += dv2[k] * dt;
  }

  wx = 0.0;
  wy = 2.2250738585072014E-308;
  for (k = 0; k < 4; k++) {
    wz = fabs(q_est[k]);
    if (wz > wy) {
      t = wy / wz;
      wx = 1.0 + wx * t * t;
      wy = wz;
    } else {
      t = wz / wy;
      wx += t * t;
    }
  }

  wx = wy * sqrt(wx);
  for (k = 0; k < 4; k++) {
    q_est[k] /= wx;
  }

  /*   QUAT2DCM Convert quaternion to direction cosine matrix. */
  /*    N = QUAT2DCM( Q ) calculates the direction cosine matrix, N, for a */
  /*    given quaternion, Q.  Input Q is an M-by-4 matrix containing M */
  /*    quaternions.  N returns a 3-by-3-by-M matrix of direction cosine  */
  /*    matrices.  The direction cosine matrix performs the coordinate */
  /*    transformation of a vector in inertial axes to a vector in body axes. */
  /*    Each element of Q must be a real number.  Additionally, Q has its */
  /*    scalar number as the first column.  */
  /*  */
  /*    Examples: */
  /*  */
  /*    Determine the direction cosine matrix from q = [1 0 1 0]: */
  /*       dcm = quat2dcm([1 0 1 0]) */
  /*  */
  /*    Determine the direction cosine matrices from multiple quaternions: */
  /*       q = [1 0 1 0; 1 0.5 0.3 0.1]; */
  /*       dcm = quat2dcm(q) */
  /*  */
  /*    See also ANGLE2DCM, DCM2ANGLE, DCM2QUAT, ANGLE2QUAT, QUAT2ANGLE, QUATROTATE.  */
  /*    Copyright 2000-2007 The MathWorks, Inc. */
  /*    $Revision: 1.1.6.3 $  $Date: 2007/05/10 13:42:37 $ */
  /* qin = quatnormalize( q ); */
  /* syms xx real */
  Rbe[0] = ((q_est[0] * q_est[0] + q_est[1] * q_est[1]) - q_est[2] * q_est[2]) -
    q_est[3] * q_est[3];
  Rbe[3] = 2.0 * (q_est[1] * q_est[2] + q_est[0] * q_est[3]);
  Rbe[6] = 2.0 * (q_est[1] * q_est[3] - q_est[0] * q_est[2]);
  Rbe[1] = 2.0 * (q_est[1] * q_est[2] - q_est[0] * q_est[3]);
  Rbe[4] = ((q_est[0] * q_est[0] - q_est[1] * q_est[1]) + q_est[2] * q_est[2]) -
    q_est[3] * q_est[3];
  Rbe[7] = 2.0 * (q_est[2] * q_est[3] + q_est[0] * q_est[1]);
  Rbe[2] = 2.0 * (q_est[1] * q_est[3] + q_est[0] * q_est[2]);
  Rbe[5] = 2.0 * (q_est[2] * q_est[3] - q_est[0] * q_est[1]);
  Rbe[8] = ((q_est[0] * q_est[0] - q_est[1] * q_est[1]) - q_est[2] * q_est[2]) +
    q_est[3] * q_est[3];
  for (k = 0; k < 3; k++) {
    for (i0 = 0; i0 < 3; i0++) {
      b_Rbe[i0 + 3 * k] = -Rbe[i0 + 3 * k];
    }
  }

  for (k = 0; k < 3; k++) {
    c_Rbe[k] = 0.0;
    for (i0 = 0; i0 < 3; i0++) {
      c_Rbe[k] += b_Rbe[k + 3 * i0] * b_b[i0];
    }

    b[k] = c_Rbe[k];
  }

  a[0] = acc[1] * b[2] - acc[2] * b[1];
  a[1] = acc[2] * b[0] - acc[0] * b[2];
  a[2] = acc[0] * b[1] - acc[1] * b[0];
  for (k = 0; k < 3; k++) {
    b_est[k] = kp * (0.5 * a[k]);
  }
}

/*
 * File trailer for estimate_ncf.c
 *
 * [EOF]
 */
