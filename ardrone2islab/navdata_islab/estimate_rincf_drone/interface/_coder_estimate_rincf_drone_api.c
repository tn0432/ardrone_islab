/*
 * File: _coder_estimate_rincf_drone_api.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 27-Aug-2015 20:15:44
 */

/* Include files */
#include "_coder_estimate_rincf_drone_api.h"

/* Function Declarations */
static double (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *x_est,
  const char *identifier))[7];
static double (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[7];
static double (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *omega,
  const char *identifier))[3];
static double (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[3];
static double (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *K_ss,
  const char *identifier))[36];
static double (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[36];
static double (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *g_e,
  const char *identifier))[3];
static double (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[3];
static double i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *dt, const
  char *identifier);
static double j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void emlrt_marshallOut(const double u[7], const mxArray *y);
static double (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[7];
static double (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static double (*m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[36];
static double (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static double o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);

/* Function Definitions */

/*
 * Arguments    : emlrtContext *aContext
 * Return Type  : void
 */
void estimate_rincf_drone_initialize(emlrtContext *aContext)
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
void estimate_rincf_drone_terminate(void)
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
void estimate_rincf_drone_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  estimate_rincf_drone_xil_terminate();
}

/*
 * Arguments    : const mxArray *prhs[8]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void estimate_rincf_drone_api(const mxArray *prhs[8], const mxArray *plhs[1])
{
  double (*x_est)[7];
  double (*omega)[3];
  double (*acc)[3];
  double (*mag)[3];
  double (*K_ss)[36];
  double (*g_e)[3];
  double (*b_e)[3];
  double dt;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, true, -1);
  prhs[1] = emlrtProtectR2012b(prhs[1], 1, false, -1);
  prhs[2] = emlrtProtectR2012b(prhs[2], 2, false, -1);
  prhs[3] = emlrtProtectR2012b(prhs[3], 3, false, -1);
  prhs[4] = emlrtProtectR2012b(prhs[4], 4, false, -1);
  prhs[5] = emlrtProtectR2012b(prhs[5], 5, false, -1);
  prhs[6] = emlrtProtectR2012b(prhs[6], 6, false, -1);

  /* Marshall function inputs */
  x_est = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "x_est");
  omega = c_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "omega");
  acc = c_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "acc");
  mag = c_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "mag");
  K_ss = e_emlrt_marshallIn(&st, emlrtAlias(prhs[4]), "K_ss");
  g_e = g_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "g_e");
  b_e = g_emlrt_marshallIn(&st, emlrtAlias(prhs[6]), "b_e");
  dt = i_emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "dt");

  /* Invoke the target function */
  estimate_rincf_drone(*x_est, *omega, *acc, *mag, *K_ss, *g_e, *b_e, dt);

  /* Marshall function outputs */
  emlrt_marshallOut(*x_est, prhs[0]);
  plhs[0] = prhs[0];
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *x_est
 *                const char *identifier
 * Return Type  : double (*)[7]
 */
static double (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *x_est,
  const char *identifier))[7]
{
  double (*y)[7];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = b_emlrt_marshallIn(sp, emlrtAlias(x_est), &thisId);
  emlrtDestroyArray(&x_est);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double (*)[7]
 */
  static double (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[7]
{
  double (*y)[7];
  y = k_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *omega
 *                const char *identifier
 * Return Type  : double (*)[3]
 */
static double (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *omega,
  const char *identifier))[3]
{
  double (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = d_emlrt_marshallIn(sp, emlrtAlias(omega), &thisId);
  emlrtDestroyArray(&omega);
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
  y = l_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *K_ss
 *                const char *identifier
 * Return Type  : double (*)[36]
 */
static double (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *K_ss,
  const char *identifier))[36]
{
  double (*y)[36];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = f_emlrt_marshallIn(sp, emlrtAlias(K_ss), &thisId);
  emlrtDestroyArray(&K_ss);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double (*)[36]
 */
  static double (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[36]
{
  double (*y)[36];
  y = m_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *g_e
 *                const char *identifier
 * Return Type  : double (*)[3]
 */
static double (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *g_e,
  const char *identifier))[3]
{
  double (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = h_emlrt_marshallIn(sp, emlrtAlias(g_e), &thisId);
  emlrtDestroyArray(&g_e);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double (*)[3]
 */
  static double (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3]
{
  double (*y)[3];
  y = n_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *dt
 *                const char *identifier
 * Return Type  : double
 */
static double i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *dt, const
  char *identifier)
{
  double y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = j_emlrt_marshallIn(sp, emlrtAlias(dt), &thisId);
  emlrtDestroyArray(&dt);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double
 */
static double j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  double y;
  y = o_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const double u[7]
 *                const mxArray *y
 * Return Type  : void
 */
static void emlrt_marshallOut(const double u[7], const mxArray *y)
{
  static const int iv0[1] = { 7 };

  mxSetData((mxArray *)y, (void *)u);
  emlrtSetDimensions((mxArray *)y, iv0, 1);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double (*)[7]
 */
static double (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[7]
{
  double (*ret)[7];
  int iv1[1];
  iv1[0] = 7;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, iv1);
  ret = (double (*)[7])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double (*)[3]
 */
  static double (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3]
{
  double (*ret)[3];
  int iv2[2];
  int i0;
  for (i0 = 0; i0 < 2; i0++) {
    iv2[i0] = 1 + (i0 << 1);
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv2);
  ret = (double (*)[3])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double (*)[36]
 */
static double (*m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[36]
{
  double (*ret)[36];
  int iv3[2];
  int i;
  for (i = 0; i < 2; i++) {
    iv3[i] = 6;
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv3);
  ret = (double (*)[36])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double (*)[3]
 */
  static double (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3]
{
  double (*ret)[3];
  int iv4[1];
  iv4[0] = 3;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, iv4);
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
static double o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  double ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, 0);
  ret = *(double *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * File trailer for _coder_estimate_rincf_drone_api.c
 *
 * [EOF]
 */
