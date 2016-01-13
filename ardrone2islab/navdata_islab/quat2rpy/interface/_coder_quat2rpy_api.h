/* 
 * File: _coder_quat2rpy_api.h 
 *  
 * MATLAB Coder version            : 2.6 
 * C/C++ source code generated on  : 24-Jun-2015 17:02:33 
 */

#ifndef ___CODER_QUAT2RPY_API_H__
#define ___CODER_QUAT2RPY_API_H__
/* Include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Function Declarations */
extern void quat2rpy_initialize(emlrtContext *aContext);
extern void quat2rpy_terminate(void);
extern void quat2rpy_atexit(void);
extern void quat2rpy_api(const mxArray *prhs[1], const mxArray *plhs[3]);
extern void quat2rpy(double q[4], double *yaw, double *pitch, double *roll);
extern void quat2rpy_xil_terminate(void);

#endif
/* 
 * File trailer for _coder_quat2rpy_api.h 
 *  
 * [EOF] 
 */
