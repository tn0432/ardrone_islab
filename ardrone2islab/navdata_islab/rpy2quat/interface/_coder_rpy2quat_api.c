/*
 * File: _coder_rpy2quat_api.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 24-Jun-2015 16:06:34
 */

/* Include files */
#include "_coder_rpy2quat_api.h"

/* Function Declarations */
static double emlrt_marshallIn(const emlrtStack *sp, const mxArray *yaw, const
  char *identifier);
static double b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static const mxArray *emlrt_marshallOut(const double u[4]);
static double c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);

/* Function Definitions */

/*
 * Arguments    : emlrtContext *aContext
 * Return Type  : void
 */
void rpy2quat_initialize(emlrtContext *aContext)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, aContext, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void rpy2quat_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void rpy2quat_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  rpy2quat_xil_terminate();
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void rpy2quat_api(const mxArray * const prhs[3], const mxArray *plhs[1])
{
  double (*q)[4];
  double yaw;
  double pitch;
  double roll;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  q = (double (*)[4])mxMalloc(sizeof(double [4]));

  /* Marshall function inputs */
  yaw = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "yaw");
  pitch = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "pitch");
  roll = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "roll");

  /* Invoke the target function */
  rpy2quat(yaw, pitch, roll, *q);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*q);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *yaw
 *                const char *identifier
 * Return Type  : double
 */
static double emlrt_marshallIn(const emlrtStack *sp, const mxArray *yaw, const
  char *identifier)
{
  double y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = b_emlrt_marshallIn(sp, emlrtAlias(yaw), &thisId);
  emlrtDestroyArray(&yaw);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double
 */
static double b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  double y;
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const double u[4]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const double u[4])
{
  const mxArray *y;
  static const int iv0[2] = { 0, 0 };

  const mxArray *m0;
  static const int iv1[2] = { 1, 4 };

  y = NULL;
  m0 = emlrtCreateNumericArray(2, iv0, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m0, (void *)u);
  emlrtSetDimensions((mxArray *)m0, iv1, 2);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double
 */
static double c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  double ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, 0);
  ret = *(double *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * File trailer for _coder_rpy2quat_api.c
 *
 * [EOF]
 */
