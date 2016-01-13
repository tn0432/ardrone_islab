/* 
 * File: _coder_rpy2quat_api.h 
 *  
 * MATLAB Coder version            : 2.6 
 * C/C++ source code generated on  : 24-Jun-2015 16:06:34 
 */

#ifndef ___CODER_RPY2QUAT_API_H__
#define ___CODER_RPY2QUAT_API_H__
/* Include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Function Declarations */
extern void rpy2quat_initialize(emlrtContext *aContext);
extern void rpy2quat_terminate(void);
extern void rpy2quat_atexit(void);
extern void rpy2quat_api(const mxArray * const prhs[3], const mxArray *plhs[1]);
extern void rpy2quat(double yaw, double pitch, double roll, double q[4]);
extern void rpy2quat_xil_terminate(void);

#endif
/* 
 * File trailer for _coder_rpy2quat_api.h 
 *  
 * [EOF] 
 */
