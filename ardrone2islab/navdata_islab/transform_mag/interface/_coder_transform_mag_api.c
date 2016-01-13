/*
 * File: _coder_transform_mag_api.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 28-Aug-2015 10:33:25
 */

/* Include files */
#include "_coder_transform_mag_api.h"

/* Function Declarations */
static double (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *mag, const
  char *identifier))[3];
static double (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[3];
static double c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *pitch,
  const char *identifier);
static double d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static const mxArray *emlrt_marshallOut(const double u[3]);
static double (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static double f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);

/* Function Definitions */

/*
 * Arguments    : emlrtContext *aContext
 * Return Type  : void
 */
void transform_mag_initialize(emlrtContext *aContext)
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
void transform_mag_terminate(void)
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
void transform_mag_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  transform_mag_xil_terminate();
}

/*
 * Arguments    : const mxArray *prhs[3]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void transform_mag_api(const mxArray *prhs[3], const mxArray *plhs[1])
{
  double (*mag_corr)[3];
  double (*mag)[3];
  double pitch;
  double roll;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  mag_corr = (double (*)[3])mxMalloc(sizeof(double [3]));
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, false, -1);

  /* Marshall function inputs */
  mag = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "mag");
  pitch = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "pitch");
  roll = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "roll");

  /* Invoke the target function */
  transform_mag(*mag, pitch, roll, *mag_corr);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*mag_corr);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *mag
 *                const char *identifier
 * Return Type  : double (*)[3]
 */
static double (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *mag, const
  char *identifier))[3]
{
  double (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = b_emlrt_marshallIn(sp, emlrtAlias(mag), &thisId);
  emlrtDestroyArray(&mag);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double (*)[3]
 */
  static double (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3]
{
  double (*y)[3];
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *pitch
 *                const char *identifier
 * Return Type  : double
 */
static double c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *pitch,
  const char *identifier)
{
  double y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = d_emlrt_marshallIn(sp, emlrtAlias(pitch), &thisId);
  emlrtDestroyArray(&pitch);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : double
 */
static double d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  double y;
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const double u[3]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const double u[3])
{
  const mxArray *y;
  static const int iv0[1] = { 0 };

  const mxArray *m0;
  static const int iv1[1] = { 3 };

  y = NULL;
  m0 = emlrtCreateNumericArray(1, iv0, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m0, (void *)u);
  emlrtSetDimensions((mxArray *)m0, iv1, 1);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : double (*)[3]
 */
static double (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
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
 * Return Type  : double
 */
  static double f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  double ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, 0);
  ret = *(double *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * File trailer for _coder_transform_mag_api.c
 *
 * [EOF]
 */
