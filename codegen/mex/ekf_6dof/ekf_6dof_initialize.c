/*
 * ekf_6dof_initialize.c
 *
 * Code generation for function 'ekf_6dof_initialize'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ekf_6dof.h"
#include "ekf_6dof_initialize.h"
#include "_coder_ekf_6dof_mex.h"
#include "ekf_6dof_data.h"

/* Function Declarations */
static void ekf_6dof_once(void);

/* Function Definitions */
static void ekf_6dof_once(void)
{
  P_P_est_not_empty_init();
  states_est_not_empty_init();

  /* Allocate instance data */
  covrtAllocateInstanceData(&emlrtCoverageInstance);

  /* Initialize Coverage Information */
  covrtScriptInit(&emlrtCoverageInstance, "E:\\jiangxx\\matlab_work\\ekf_6dof.m",
                  0, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0);

  /* Initialize Function Information */
  covrtFcnInit(&emlrtCoverageInstance, 0, 0, "ekf_6dof", 0, -1, 2503);

  /* Initialize Basic Block Information */
  covrtBasicBlockInit(&emlrtCoverageInstance, 0, 2, 1099, -1, 2498);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0, 1, 1033, -1, 1079);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0, 0, 285, -1, 827);

  /* Initialize If Information */
  covrtIfInit(&emlrtCoverageInstance, 0, 0, 938, 960, -1, 1084);

  /* Initialize MCDC Information */
  /* Initialize For Information */
  /* Initialize While Information */
  /* Initialize Switch Information */
  /* Start callback for coverage engine */
  covrtScriptStart(&emlrtCoverageInstance, 0U);
}

void ekf_6dof_initialize(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    ekf_6dof_once();
  }
}

/* End of code generation (ekf_6dof_initialize.c) */
