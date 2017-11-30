/*
 * _coder_ekf_6dof_api.c
 *
 * Code generation for function '_coder_ekf_6dof_api'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ekf_6dof.h"
#include "_coder_ekf_6dof_api.h"
#include "ekf_6dof_data.h"

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
static real32_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real32_T y;
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

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

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[4])
{
  f_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

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

static const mxArray *emlrt_marshallOut(const real32_T u[4])
{
  const mxArray *y;
  const mxArray *m1;
  static const int32_T iv4[1] = { 4 };

  real32_T *pData;
  int32_T i;
  y = NULL;
  m1 = emlrtCreateNumericArray(1, iv4, mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)mxGetData(m1);
  for (i = 0; i < 4; i++) {
    pData[i] = u[i];
  }

  emlrtAssign(&y, m1);
  return y;
}

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[4])
{
  static const int32_T dims[1] = { 4 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single|double", false, 1U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 4, false);
  emlrtDestroyArray(&src);
}

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
  ekf_6dof(&st, gyroX, gyroY, gyroZ, accX, accY, accZ, dt, TX, y);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(y);
}

/* End of code generation (_coder_ekf_6dof_api.c) */
