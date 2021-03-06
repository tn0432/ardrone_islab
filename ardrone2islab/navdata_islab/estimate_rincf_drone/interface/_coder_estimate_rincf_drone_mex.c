/*
 * _coder_estimate_rincf_drone_mex.c
 *
 * Code generation for function 'estimate_rincf_drone'
 *
 */

/* Include files */
#include "mex.h"
#include "_coder_estimate_rincf_drone_api.h"

/* Function Declarations */
static void estimate_rincf_drone_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

/* Variable Definitions */
emlrtContext emlrtContextGlobal = { true, false, EMLRT_VERSION_INFO, NULL, "estimate_rincf_drone", NULL, false, {2045744189U,2170104910U,2743257031U,4284093946U}, NULL };
void *emlrtRootTLSGlobal = NULL;

/* Function Definitions */
static void estimate_rincf_drone_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  const mxArray *outputs[1];
  const mxArray *inputs[8];
  int n = 0;
  int nOutputs = (nlhs < 1 ? 1 : nlhs);
  int nInputs = nrhs;
  emlrtStack st = { NULL, NULL, NULL };
  /* Module initialization. */
  estimate_rincf_drone_initialize(&emlrtContextGlobal);
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 8) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, mxINT32_CLASS, 8, mxCHAR_CLASS, 20, "estimate_rincf_drone");
  } else if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, mxCHAR_CLASS, 20, "estimate_rincf_drone");
  }
  /* Temporary copy for mex inputs. */
  for (n = 0; n < nInputs; ++n) {
    inputs[n] = prhs[n];
  }
  /* Call the function. */
  estimate_rincf_drone_api(inputs, outputs);
  /* Copy over outputs to the caller. */
  for (n = 0; n < nOutputs; ++n) {
    plhs[n] = emlrtReturnArrayR2009a(outputs[n]);
  }
  /* Module finalization. */
  estimate_rincf_drone_terminate();
}

void estimate_rincf_drone_atexit_wrapper(void)
{
   estimate_rincf_drone_atexit();
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /* Initialize the memory manager. */
  mexAtExit(estimate_rincf_drone_atexit_wrapper);
  /* Dispatch the entry-point. */
  estimate_rincf_drone_mexFunction(nlhs, plhs, nrhs, prhs);
}
/* End of code generation (_coder_estimate_rincf_drone_mex.c) */
