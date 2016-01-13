/* 
 * File: _coder_estimate_ncf_api.h 
 *  
 * MATLAB Coder version            : 2.6 
 * C/C++ source code generated on  : 24-Jun-2015 13:23:47 
 */

#ifndef ___CODER_ESTIMATE_NCF_API_H__
#define ___CODER_ESTIMATE_NCF_API_H__
/* Include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Function Declarations */
extern void estimate_ncf_initialize(emlrtContext *aContext);
extern void estimate_ncf_terminate(void);
extern void estimate_ncf_atexit(void);
extern void estimate_ncf_api(const mxArray *prhs[6], const mxArray *plhs[2]);
extern void estimate_ncf_xil_terminate(void);
extern void estimate_ncf(double q_est[4], double b_est[3], double omega[3], double acc[3], double kp, double dt);

#endif
/* 
 * File trailer for _coder_estimate_ncf_api.h 
 *  
 * [EOF] 
 */
