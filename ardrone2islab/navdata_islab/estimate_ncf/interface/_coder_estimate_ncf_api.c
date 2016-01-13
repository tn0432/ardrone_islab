/*
 * File: _coder_estimate_ncf_api.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 24-Jun-2015 13:23:47
 */

/* Include files */
#include "_coder_estimate_ncf_api.h"

/* Function Declarations */
static double (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *q_est,
  const char *identifier))[4];
static double (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[4];
static double (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_est,
  const char *identifier))[3];
static double (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[3];
static double e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *kp, const
  char *identifier);
static double f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void emlrt_marshallOut(const double u[4], const mxArray *y);
static void b_emlrt_marshallOut(const double u[3], const mxArray *y);
static double (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4];
static double (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static double i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);

/* Function Definitions */

/*
 * Arguments    : emlrtContext *aContext
 * Return Type  : void
 */
void estimate_ncf_initialize(emlrtContext *aContext)
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
void estimate_ncf_terminate(void)
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
void estimate_ncf_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  estimate_ncf_xil_terminate();
}

/*
 * Arguments    : const mxArray *prhs[6]
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
void estimate_ncf_api(const mxArray *prhs[6], const mxArray *plhs[2])
{
  double (*q_est)[4];
  double (*b_est)[3];
  double (*omega)[3];
  double (*acc)[3];
  double kp;
  double dt;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, true, -1);
  prhs[1] = emlrtProtectR2012b(prhs[1], 1, true, -1);
  prhs[2] = emlrtProtectR2012b(prhs[2], 2, false, -1);
  prhs[3] = emlrtProtectR2012b(prhs[3], 3, false, -1);

  /* Marshall function inputs */
  q_est = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "q_est");
  b_est = c_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "b_est");
  omega = c_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "omega");
  acc = c_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "acc");
  kp = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "kp");
  dt = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "dt");

  /* Invoke the target function */
  estimate_ncf(*q_est, *b_est, *omega, *acc, kp, dt);

  /* Marshall function outputs */
  emlrt_marshallOut(*q_est, prhs[0]);
  plhs[0] = prhs[0];
  b_emlrt_marshallOut(*b_est, prhs[1]);
  plhs[1] = prhs[1];
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *q_est
 *                const char *identifier
 * Return Type  : double (*)[4]
 */
static double (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *q_est,
  const char *identifier))[4]
{
  double (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = b_emlrt_marshallIn(sp, emlrtAlias(q_est), &thisId);
  emlrtDestroyArray(&q_est);
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
  y = g_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *b_est
 *                const char *identifier
 * Return Type  : double (*)[3]
 */
static double (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_est,
  const char *identifier))[3]
{
  double (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = d_emlrt_marshallIn(sp, emlrtAlias(b_est), &thisId);
  emlrtDestroyArray(&b_est);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double (*)[3]
 */
  static double (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3]
{
  double (*y)[3];
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *kp
 *                const char *identifier
 * Return Type  : double
 */
static double e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *kp, const
  char *identifier)
{
  double y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = f_emlrt_marshallIn(sp, emlrtAlias(kp), &thisId);
  emlrtDestroyArray(&kp);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double
 */
static double f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  double y;
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const double u[4]
 *                const mxArray *y
 * Return Type  : void
 */
static void emlrt_marshallOut(const double u[4], const mxArray *y)
{
  static const int iv0[2] = { 1, 4 };

  mxSetData((mxArray *)y, (void *)u);
  emlrtSetDimensions((mxArray *)y, iv0, 2);
}

/*
 * Arguments    : const double u[3]
 *                const mxArray *y
 * Return Type  : void
 */
static void b_emlrt_marshallOut(const double u[3], const mxArray *y)
{
  static const int iv1[2] = { 1, 3 };

  mxSetData((mxArray *)y, (void *)u);
  emlrtSetDimensions((mxArray *)y, iv1, 2);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double (*)[4]
 */
static double (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4]
{
  double (*ret)[4];
  int iv2[2];
  int i0;
  for (i0 = 0; i0 < 2; i0++) {
    iv2[i0] = 1 + 3 * i0;
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv2);
  ret = (double (*)[4])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double (*)[3]
 */
  static double (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3]
{
  double (*ret)[3];
  int iv3[2];
  int i1;
  for (i1 = 0; i1 < 2; i1++) {
    iv3[i1] = 1 + (i1 << 1);
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv3);
  ret = (double (*)[3])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double
 */
static double i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  double ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, 0);
  ret = *(double *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * File trailer for _coder_estimate_ncf_api.c
 *
 * [EOF]
 */
