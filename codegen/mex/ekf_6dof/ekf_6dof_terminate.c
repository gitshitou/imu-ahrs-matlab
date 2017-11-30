/*
 * ekf_6dof_terminate.c
 *
 * Code generation for function 'ekf_6dof_terminate'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ekf_6dof.h"
#include "ekf_6dof_terminate.h"
#include "_coder_ekf_6dof_mex.h"
#include "ekf_6dof_data.h"

/* Function Definitions */
void ekf_6dof_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);

  /* Free instance data */
  covrtFreeInstanceData(&emlrtCoverageInstance);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

void ekf_6dof_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (ekf_6dof_terminate.c) */
