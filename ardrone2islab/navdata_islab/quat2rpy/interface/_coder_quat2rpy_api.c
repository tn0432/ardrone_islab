/*
 * File: _coder_quat2rpy_api.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 24-Jun-2015 17:02:33
 */

/* Include files */
#include "_coder_quat2rpy_api.h"

/* Function Declarations */
static double (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *q, const
  char *identifier))[4];
static double (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[4];
static const mxArray *emlrt_marshallOut(const double u);
static double (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4];

/* Function Definitions */

/*
 * Arguments    : emlrtContext *aContext
 * Return Type  : void
 */
void quat2rpy_initialize(emlrtContext *aContext)
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
void quat2rpy_terminate(void)
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
void quat2rpy_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  quat2rpy_xil_terminate();
}

/*
 * Arguments    : const mxArray *prhs[1]
 *                const mxArray *plhs[3]
 * Return Type  : void
 */
void quat2rpy_api(const mxArray *prhs[1], const mxArray *plhs[3])
{
  double (*q)[4];
  double roll;
  double pitch;
  double yaw;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, false, -1);

  /* Marshall function inputs */
  q = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "q");

  /* Invoke the target function */
  quat2rpy(*q, &yaw, &pitch, &roll);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(yaw);
  plhs[1] = emlrt_marshallOut(pitch);
  plhs[2] = emlrt_marshallOut(roll);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *q
 *                const char *identifier
 * Return Type  : double (*)[4]
 */
static double (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *q, const
  char *identifier))[4]
{
  double (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = b_emlrt_marshallIn(sp, emlrtAlias(q), &thisId);
  emlrtDestroyArray(&q);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double (*)[4]
 */
  static double (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[4]
{
  double (*y)[4];
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const double u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const double u)
{
  const mxArray *y;
  const mxArray *m0;
  y = NULL;
  m0 = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double (*)[4]
 */
static double (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4]
{
  double (*ret)[4];
  int iv0[2];
  int i0;
  for (i0 = 0; i0 < 2; i0++) {
    iv0[i0] = 1 + 3 * i0;
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv0);
  ret = (double (*)[4])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * File trailer for _coder_quat2rpy_api.c
 *
 * [EOF]
 */
