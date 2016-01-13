/*
 * File: estimate_rincf_drone.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 27-Aug-2015 20:15:44
 */

/* Include files */
#include "rt_nonfinite.h"
#include "estimate_rincf_drone.h"

/* Function Definitions */

/*
 * Arguments    : double x_est[7]
 *                const double omega[3]
 *                const double acc[3]
 *                const double mag[3]
 *                const double K_ss[36]
 *                const double g_e[3]
 *                const double b_e[3]
 *                double dt
 * Return Type  : void
 */
void estimate_rincf_drone(double x_est[7], const double omega[3], const double
  acc[3], const double mag[3], const double K_ss[36], const double g_e[3], const
  double b_e[3], double dt)
{
  double b_x_est[7];
  double c_x_est[7];
  double x[7];
  int i;
  double qnorm;
  double b_x[7];
  double b_g_e[6];
  double inn[6];
  int i0;
  double b_inn[7];
  double c_x[7];

  /* g_e=double([0 0 -9.81]'); */
  /* b_e=double([0.3793   -0.2157    0.8998]'); */
  /* Rbe=double(eye(3)); */
  /* I34=[zeros(3,1) eye(3)]; */
  /* states */
  /* qt=[q0 q1 q2 q3]';                  %quarternions */
  /* w_b=[wbx wby wbz]'; */
  /* states */
  b_x_est[0] = x_est[0];
  b_x_est[1] = x_est[1];
  b_x_est[2] = x_est[2];
  b_x_est[3] = x_est[3];
  b_x_est[4] = x_est[4];
  b_x_est[5] = x_est[5];
  b_x_est[6] = x_est[6];
  c_x_est[0] = (x_est[1] * (x_est[4] - omega[0]) / 2.0 + x_est[2] * (x_est[5] -
    omega[1]) / 2.0) + x_est[3] * (x_est[6] - omega[2]) / 2.0;
  c_x_est[1] = (x_est[3] * (x_est[5] - omega[1]) / 2.0 - x_est[0] * (x_est[4] -
    omega[0]) / 2.0) - x_est[2] * (x_est[6] - omega[2]) / 2.0;
  c_x_est[2] = (x_est[1] * (x_est[6] - omega[2]) / 2.0 - x_est[0] * (x_est[5] -
    omega[1]) / 2.0) - x_est[3] * (x_est[4] - omega[0]) / 2.0;
  c_x_est[3] = (x_est[2] * (x_est[4] - omega[0]) / 2.0 - x_est[1] * (x_est[5] -
    omega[1]) / 2.0) - x_est[0] * (x_est[6] - omega[2]) / 2.0;
  c_x_est[4] = 0.0;
  c_x_est[5] = 0.0;
  c_x_est[6] = 0.0;
  for (i = 0; i < 7; i++) {
    x[i] = b_x_est[i] + c_x_est[i] * dt;
  }

  /* normalize quaternion */
  qnorm = sqrt(((x[0] * x[0] + x[1] * x[1]) + x[2] * x[2]) + x[3] * x[3]);
  b_x[0] = x[0] / qnorm;
  b_x[1] = x[1] / qnorm;
  b_x[2] = x[2] / qnorm;
  b_x[3] = x[3] / qnorm;
  b_x[4] = x[4];
  b_x[5] = x[5];
  b_x[6] = x[6];
  for (i = 0; i < 7; i++) {
    x[i] = b_x[i];
  }

  /* wbx=x(5);wby=x(6);wbz=x(7); */
  /*      accp=[gez*(2*q0*q2 - 2*q1*q3) - gey*(2*q0*q3 + 2*q1*q2) - gex*(q0^2 + q1^2 - q2^2 - q3^2) */
  /*          gex*(2*q0*q3 - 2*q1*q2) - gey*(q0^2 - q1^2 + q2^2 - q3^2) - gez*(2*q0*q1 + 2*q2*q3); */
  /*          gey*(2*q0*q1 - 2*q2*q3) - gex*(2*q0*q2 + 2*q1*q3) - gez*(q0^2 - q1^2 - q2^2 + q3^2)]; */
  /*   */
  /*      magp=[bex*(q0^2 + q1^2 - q2^2 - q3^2) + bey*(2*q0*q3 + 2*q1*q2) - bez*(2*q0*q2 - 2*q1*q3); */
  /*          bey*(q0^2 - q1^2 + q2^2 - q3^2) - bex*(2*q0*q3 - 2*q1*q2) + bez*(2*q0*q1 + 2*q2*q3); */
  /*          bez*(q0^2 - q1^2 - q2^2 + q3^2) + bex*(2*q0*q2 + 2*q1*q3) - bey*(2*q0*q1 - 2*q2*q3)]; */
  /*       */
  /*      y_est=[accp;  magp]; */
  /*       E=    [ q2*(q1*(amx*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) - q0*(amx*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)) - amy*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q2*(amy*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)))) - q0*(q2*(amx*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)) - amy*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q3*(amx*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q0*(amy*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)))) - q1*(q3*(amx*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)) - amy*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) - q2*(amx*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q1*(amy*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)))) - q3*(q1*(amx*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)) - amy*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q0*(amx*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) - q3*(amy*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)))); */
  /*                  q0*(q1*(amx*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)) - amy*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q0*(amx*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) - q3*(amy*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)))) - q1*(q1*(amx*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) - q0*(amx*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)) - amy*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q2*(amy*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)))) - q3*(q2*(amx*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)) - amy*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q3*(amx*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q0*(amy*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)))) - q2*(q3*(amx*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)) - amy*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) - q2*(amx*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q1*(amy*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)))); */
  /*                  q0*(q1*(amx*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) - q0*(amx*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)) - amy*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q2*(amy*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)))) + q1*(q1*(amx*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)) - amy*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q0*(amx*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) - q3*(amy*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)))) + q2*(q2*(amx*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)) - amy*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q3*(amx*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q0*(amy*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)))) - q3*(q3*(amx*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)) - amy*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) - q2*(amx*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gex*q0 + gey*q3 - gez*q2) - q2*(gex*q2 - gey*q1 + gez*q0) + q1*(gex*q1 + gey*q2 + gez*q3) + q3*(gey*q0 - gex*q3 + gez*q1))) + q1*(amy*(q0*(gex*q2 - gey*q1 + gez*q0) - q1*(gey*q0 - gex*q3 + gez*q1) + q2*(gex*q0 + gey*q3 - gez*q2) + q3*(gex*q1 + gey*q2 + gez*q3)) - amz*(q0*(gey*q0 - gex*q3 + gez*q1) + q1*(gex*q2 - gey*q1 + gez*q0) + q2*(gex*q1 + gey*q2 + gez*q3) - q3*(gex*q0 + gey*q3 - gez*q2)))); */
  /*                  q0*(q2*(bmx*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)) - bmy*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q3*(bmx*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q0*(bmy*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)))) - q2*(q1*(bmx*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) - q0*(bmx*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)) - bmy*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q2*(bmy*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)))) + q1*(q3*(bmx*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)) - bmy*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) - q2*(bmx*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q1*(bmy*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)))) + q3*(q1*(bmx*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)) - bmy*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q0*(bmx*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) - q3*(bmy*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)))); */
  /*                  q1*(q1*(bmx*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) - q0*(bmx*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)) - bmy*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q2*(bmy*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)))) - q0*(q1*(bmx*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)) - bmy*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q0*(bmx*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) - q3*(bmy*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)))) + q3*(q2*(bmx*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)) - bmy*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q3*(bmx*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q0*(bmy*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)))) + q2*(q3*(bmx*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)) - bmy*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) - q2*(bmx*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q1*(bmy*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)))); */
  /*                  q3*(q3*(bmx*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)) - bmy*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) - q2*(bmx*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q1*(bmy*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)))) - q1*(q1*(bmx*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)) - bmy*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q0*(bmx*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) - q3*(bmy*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)))) - q2*(q2*(bmx*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)) - bmy*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q3*(bmx*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q0*(bmy*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)))) - q0*(q1*(bmx*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) - q0*(bmx*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2)) - bmy*(q0*(bex*q0 + bey*q3 - bez*q2) - q2*(bex*q2 - bey*q1 + bez*q0) + q1*(bex*q1 + bey*q2 + bez*q3) + q3*(bey*q0 - bex*q3 + bez*q1))) + q2*(bmy*(q0*(bex*q2 - bey*q1 + bez*q0) - q1*(bey*q0 - bex*q3 + bez*q1) + q2*(bex*q0 + bey*q3 - bez*q2) + q3*(bex*q1 + bey*q2 + bez*q3)) - bmz*(q0*(bey*q0 - bex*q3 + bez*q1) + q1*(bex*q2 - bey*q1 + bez*q0) + q2*(bex*q1 + bey*q2 + bez*q3) - q3*(bex*q0 + bey*q3 - bez*q2))))]; */
  /*       K_ss =1.0e-03 *[   0.0229   -0.0000         0    0.0000    0.0000   -0.0000; */
  /*                         -0.0000    0.0228         0    0.0000    0.0000    0.0000; */
  /*                          0.0000   -0.0000         0   -0.8837    0.5025    0.4929; */
  /*                         -0.0202    0.0000         0   -0.0000   -0.0000    0.0000; */
  /*                          0.0000   -0.0201         0   -0.0000   -0.0000   -0.0000; */
  /*                         -0.0000    0.0000         0    0.1741   -0.0990   -0.0971]; */
  /*      K_ss =[     0.0019    0.0000         0    0.0000   -0.0000    0.0000; */
  /*                  0.0000    0.0019         0   -0.0000    0.0000    0.0000; */
  /*                 -0.0000   -0.0000         0    0.0010    0.0010    0.0004; */
  /*                 -0.0014   -0.0000         0   -0.0000    0.0000   -0.0000; */
  /*                 -0.0000   -0.0014         0    0.0000   -0.0000   -0.0000; */
  /*                  0.0000    0.0000         0   -0.0002   -0.0001   -0.0001];    */
  /*       qt=[x(1) x(2) x(3) x(4)]; */
  /*       ii=[1 2 3 4 5 6]; */
  /*            x(1:4,:)= x(1:4,:) + quatmultiply([0 (K_ss(1:3,:)*E(ii,:))'],qt)'; */
  /*            x(5:7,:)= x(5:7,:) + I34*quatmultiply(quatmultiply(qinv(qt)',[0; K_ss(4:6,:)*E(ii,:)]'),qt)'; */
  b_g_e[0] = g_e[1] * ((acc[2] * (((x[0] * x[0] - x[1] * x[1]) - x[2] * x[2]) +
    x[3] * x[3]) - acc[0] * (2.0 * x[0] * x[2] - 2.0 * x[1] * x[3])) + acc[1] *
                       (2.0 * x[0] * x[1] + 2.0 * x[2] * x[3])) - g_e[2] *
    ((acc[1] * (((x[0] * x[0] - x[1] * x[1]) + x[2] * x[2]) - x[3] * x[3]) +
      acc[0] * (2.0 * x[0] * x[3] + 2.0 * x[1] * x[2])) - acc[2] * (2.0 * x[0] *
      x[1] - 2.0 * x[2] * x[3]));
  b_g_e[1] = g_e[2] * ((acc[0] * (((x[0] * x[0] + x[1] * x[1]) - x[2] * x[2]) -
    x[3] * x[3]) - acc[1] * (2.0 * x[0] * x[3] - 2.0 * x[1] * x[2])) + acc[2] *
                       (2.0 * x[0] * x[2] + 2.0 * x[1] * x[3])) - g_e[0] *
    ((acc[2] * (((x[0] * x[0] - x[1] * x[1]) - x[2] * x[2]) + x[3] * x[3]) -
      acc[0] * (2.0 * x[0] * x[2] - 2.0 * x[1] * x[3])) + acc[1] * (2.0 * x[0] *
      x[1] + 2.0 * x[2] * x[3]));
  b_g_e[2] = g_e[0] * ((acc[1] * (((x[0] * x[0] - x[1] * x[1]) + x[2] * x[2]) -
    x[3] * x[3]) + acc[0] * (2.0 * x[0] * x[3] + 2.0 * x[1] * x[2])) - acc[2] *
                       (2.0 * x[0] * x[1] - 2.0 * x[2] * x[3])) - g_e[1] *
    ((acc[0] * (((x[0] * x[0] + x[1] * x[1]) - x[2] * x[2]) - x[3] * x[3]) -
      acc[1] * (2.0 * x[0] * x[3] - 2.0 * x[1] * x[2])) + acc[2] * (2.0 * x[0] *
      x[2] + 2.0 * x[1] * x[3]));
  b_g_e[3] = b_e[2] * ((mag[1] * (((x[0] * x[0] - x[1] * x[1]) + x[2] * x[2]) -
    x[3] * x[3]) + mag[0] * (2.0 * x[0] * x[3] + 2.0 * x[1] * x[2])) - mag[2] *
                       (2.0 * x[0] * x[1] - 2.0 * x[2] * x[3])) - b_e[1] *
    ((mag[2] * (((x[0] * x[0] - x[1] * x[1]) - x[2] * x[2]) + x[3] * x[3]) -
      mag[0] * (2.0 * x[0] * x[2] - 2.0 * x[1] * x[3])) + mag[1] * (2.0 * x[0] *
      x[1] + 2.0 * x[2] * x[3]));
  b_g_e[4] = b_e[0] * ((mag[2] * (((x[0] * x[0] - x[1] * x[1]) - x[2] * x[2]) +
    x[3] * x[3]) - mag[0] * (2.0 * x[0] * x[2] - 2.0 * x[1] * x[3])) + mag[1] *
                       (2.0 * x[0] * x[1] + 2.0 * x[2] * x[3])) - b_e[2] *
    ((mag[0] * (((x[0] * x[0] + x[1] * x[1]) - x[2] * x[2]) - x[3] * x[3]) -
      mag[1] * (2.0 * x[0] * x[3] - 2.0 * x[1] * x[2])) + mag[2] * (2.0 * x[0] *
      x[2] + 2.0 * x[1] * x[3]));
  b_g_e[5] = b_e[1] * ((mag[0] * (((x[0] * x[0] + x[1] * x[1]) - x[2] * x[2]) -
    x[3] * x[3]) - mag[1] * (2.0 * x[0] * x[3] - 2.0 * x[1] * x[2])) + mag[2] *
                       (2.0 * x[0] * x[2] + 2.0 * x[1] * x[3])) - b_e[0] *
    ((mag[1] * (((x[0] * x[0] - x[1] * x[1]) + x[2] * x[2]) - x[3] * x[3]) +
      mag[0] * (2.0 * x[0] * x[3] + 2.0 * x[1] * x[2])) - mag[2] * (2.0 * x[0] *
      x[1] - 2.0 * x[2] * x[3]));
  for (i = 0; i < 6; i++) {
    inn[i] = 0.0;
    for (i0 = 0; i0 < 6; i0++) {
      inn[i] += K_ss[i + 6 * i0] * b_g_e[i0];
    }
  }

  b_inn[0] = (-inn[0] * x[1] - inn[1] * x[2]) - inn[2] * x[3];
  b_inn[1] = (inn[0] * x[0] + inn[1] * x[3]) - inn[2] * x[2];
  b_inn[2] = (inn[1] * x[0] - inn[0] * x[3]) + inn[2] * x[1];
  b_inn[3] = (inn[0] * x[2] - inn[1] * x[1]) + inn[2] * x[0];
  b_inn[4] = (inn[3] * (((x[0] * x[0] + x[1] * x[1]) - x[2] * x[2]) - x[3] * x[3])
              + inn[4] * (2.0 * x[0] * x[3] + 2.0 * x[1] * x[2])) - inn[5] *
    (2.0 * x[0] * x[2] - 2.0 * x[1] * x[3]);
  b_inn[5] = (inn[4] * (((x[0] * x[0] - x[1] * x[1]) + x[2] * x[2]) - x[3] * x[3])
              - inn[3] * (2.0 * x[0] * x[3] - 2.0 * x[1] * x[2])) + inn[5] *
    (2.0 * x[0] * x[1] + 2.0 * x[2] * x[3]);
  b_inn[6] = (inn[5] * (((x[0] * x[0] - x[1] * x[1]) - x[2] * x[2]) + x[3] * x[3])
              + inn[3] * (2.0 * x[0] * x[2] + 2.0 * x[1] * x[3])) - inn[4] *
    (2.0 * x[0] * x[1] - 2.0 * x[2] * x[3]);
  for (i = 0; i < 7; i++) {
    x[i] += b_inn[i];
  }

  /* normalize quaternion */
  qnorm = sqrt(((x[0] * x[0] + x[1] * x[1]) + x[2] * x[2]) + x[3] * x[3]);
  c_x[0] = x[0] / qnorm;
  c_x[1] = x[1] / qnorm;
  c_x[2] = x[2] / qnorm;
  c_x[3] = x[3] / qnorm;
  c_x[4] = x[4];
  c_x[5] = x[5];
  c_x[6] = x[6];
  for (i = 0; i < 7; i++) {
    x[i] = c_x[i];
  }

  for (i = 0; i < 7; i++) {
    x_est[i] = x[i];
  }

  /* K_est=reshape(K_ss,1,[]); */
  /* debug */
}

/*
 * File trailer for estimate_rincf_drone.c
 *
 * [EOF]
 */
