/* 
 * File: _coder_estimate_rincf_drone_api.h 
 *  
 * MATLAB Coder version            : 2.6 
 * C/C++ source code generated on  : 27-Aug-2015 20:15:44 
 */

#ifndef ___CODER_ESTIMATE_RINCF_DRONE_API_H__
#define ___CODER_ESTIMATE_RINCF_DRONE_API_H__
/* Include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Function Declarations */
extern void estimate_rincf_drone_initialize(emlrtContext *aContext);
extern void estimate_rincf_drone_terminate(void);
extern void estimate_rincf_drone_atexit(void);
extern void estimate_rincf_drone_api(const mxArray *prhs[8], const mxArray *plhs[1]);
extern void estimate_rincf_drone_xil_terminate(void);
extern void estimate_rincf_drone(double x_est[7], double omega[3], double acc[3], double mag[3], double K_ss[36], double g_e[3], double b_e[3], double dt);

#endif
/* 
 * File trailer for _coder_estimate_rincf_drone_api.h 
 *  
 * [EOF] 
 */
