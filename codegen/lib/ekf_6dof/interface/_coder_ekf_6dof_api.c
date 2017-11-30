/*
 * File: _coder_ekf_6dof_api.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 13-Oct-2017 20:51:32
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_ekf_6dof_api.h"
#include "_coder_ekf_6dof_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true, false, 131434U, NULL, "ekf_6dof", NULL,
  false, { 2045744189U, 2170104910U, 2743257031U, 4284093946U }, NULL };

/* Function Declarations */
static real32_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *TX, const
  char_T *identifier, real32_T y[4]);
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[4]);
static real32_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId);
static real32_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *gyroX,
  const char_T *identifier);
static const mxArray *emlrt_marshallOut(const real32_T u[4]);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[4]);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real32_T
 */
static real32_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real32_T y;
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *TX
 *                const char_T *identifier
 *                real32_T y[4]
 * Return Type  : void
 */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *TX, const
  char_T *identifier, real32_T y[4])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(sp, emlrtAlias(TX), &thisId, y);
  emlrtDestroyArray(&TX);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real32_T y[4]
 * Return Type  : void
 */
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[4])
{
  f_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real32_T
 */
static real32_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  real32_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "single|double", false, 0U, &dims);
  emlrtImportArrayR2015b(sp, src, &ret, 4, false);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *gyroX
 *                const char_T *identifier
 * Return Type  : real32_T
 */
static real32_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *gyroX,
  const char_T *identifier)
{
  real32_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(gyroX), &thisId);
  emlrtDestroyArray(&gyroX);
  return y;
}

/*
 * Arguments    : const real32_T u[4]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real32_T u[4])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[1] = { 4 };

  real32_T *pData;
  int32_T i;
  y = NULL;
  m0 = emlrtCreateNumericArray(1, iv0, mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)mxGetData(m0);
  for (i = 0; i < 4; i++) {
    pData[i] = u[i];
  }

  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real32_T ret[4]
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[4])
{
  static const int32_T dims[1] = { 4 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single|double", false, 1U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 4, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray * const prhs[8]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void ekf_6dof_api(const mxArray * const prhs[8], const mxArray *plhs[1])
{
  real32_T gyroX;
  real32_T gyroY;
  real32_T gyroZ;
  real32_T accX;
  real32_T accY;
  real32_T accZ;
  real32_T dt;
  real32_T TX[4];
  real32_T y[4];
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  gyroX = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "gyroX");
  gyroY = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "gyroY");
  gyroZ = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "gyroZ");
  accX = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "accX");
  accY = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "accY");
  accZ = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "accZ");
  dt = emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "dt");
  c_emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "TX", TX);

  /* Invoke the target function */
  ekf_6dof(gyroX, gyroY, gyroZ, accX, accY, accZ, dt, TX, y);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(y);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void ekf_6dof_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  ekf_6dof_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void ekf_6dof_initialize(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void ekf_6dof_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_ekf_6dof_api.c
 *
 * [EOF]
 */
