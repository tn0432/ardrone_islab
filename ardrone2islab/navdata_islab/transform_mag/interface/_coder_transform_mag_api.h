/* 
 * File: _coder_transform_mag_api.h 
 *  
 * MATLAB Coder version            : 2.6 
 * C/C++ source code generated on  : 28-Aug-2015 10:33:25 
 */

#ifndef ___CODER_TRANSFORM_MAG_API_H__
#define ___CODER_TRANSFORM_MAG_API_H__
/* Include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Function Declarations */
extern void transform_mag_initialize(emlrtContext *aContext);
extern void transform_mag_terminate(void);
extern void transform_mag_atexit(void);
extern void transform_mag_api(const mxArray *prhs[3], const mxArray *plhs[1]);
extern void transform_mag(double mag[3], double pitch, double roll, double mag_corr[3]);
extern void transform_mag_xil_terminate(void);

#endif
/* 
 * File trailer for _coder_transform_mag_api.h 
 *  
 * [EOF] 
 */
