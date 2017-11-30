/*
 * ekf_6dof.c
 *
 * Code generation for function 'ekf_6dof'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ekf_6dof.h"
#include "mpower.h"
#include "warning.h"
#include "norm.h"
#include "ekf_6dof_data.h"

/* Variable Definitions */
static real32_T states_est[4];
static boolean_T states_est_not_empty;
static real32_T P_P_est[16];
static emlrtRSInfo emlrtRSI = { 38, "ekf_6dof",
  "E:\\jiangxx\\matlab_work\\ekf_6dof.m" };

static emlrtRSInfo b_emlrtRSI = { 54, "ekf_6dof",
  "E:\\jiangxx\\matlab_work\\ekf_6dof.m" };

static emlrtRSInfo c_emlrtRSI = { 55, "ekf_6dof",
  "E:\\jiangxx\\matlab_work\\ekf_6dof.m" };

static emlrtRSInfo d_emlrtRSI = { 58, "ekf_6dof",
  "E:\\jiangxx\\matlab_work\\ekf_6dof.m" };

static emlrtRSInfo g_emlrtRSI = { 6, "replaceoperators.cpp:118",
  "b:\\matlab\\src\\cgir_float2fixed\\src\\replaceoperators.cpp:118" };

static emlrtRSInfo h_emlrtRSI = { 1, "dts_binary_op",
  "C:\\Program Files\\MATLAB\\R2016a\\toolbox\\coder\\float2fixed\\dtslib\\dts_binary_op.p"
};

static emlrtRSInfo i_emlrtRSI = { 1, "mrdivide",
  "C:\\Program Files\\MATLAB\\R2016a\\toolbox\\eml\\lib\\matlab\\ops\\mrdivide.p"
};

static emlrtRSInfo j_emlrtRSI = { 48, "lusolve",
  "C:\\Program Files\\MATLAB\\R2016a\\toolbox\\eml\\eml\\+coder\\+internal\\lusolve.m"
};

static emlrtRSInfo k_emlrtRSI = { 249, "lusolve",
  "C:\\Program Files\\MATLAB\\R2016a\\toolbox\\eml\\eml\\+coder\\+internal\\lusolve.m"
};

static emlrtRSInfo l_emlrtRSI = { 76, "lusolve",
  "C:\\Program Files\\MATLAB\\R2016a\\toolbox\\eml\\eml\\+coder\\+internal\\lusolve.m"
};

/* Function Definitions */
void P_P_est_not_empty_init(void)
{
}

void ekf_6dof(const emlrtStack *sp, real32_T gyroX, real32_T gyroY, real32_T
              gyroZ, real32_T accX, real32_T accY, real32_T accZ, real32_T dt,
              const real32_T TX[4], real32_T y[4])
{
  real32_T A[16];
  real32_T maxval;
  int32_T rtemp;
  real32_T scale;
  static const real32_T fv0[16] = { 1.0E-10F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0E-10F,
    0.0F, 0.0F, 0.0F, 0.0F, 1.0E-10F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0E-10F };

  real32_T states_prd[4];
  int32_T r2;
  real32_T absxk;
  real32_T H[12];
  real32_T t;
  real32_T G[12];
  int32_T r1;
  real32_T b_A[16];
  real32_T b_G[16];
  real32_T P_P_prd[16];
  real32_T a[3];
  real32_T b_H[12];
  real32_T b[9];
  int32_T r3;
  static const int8_T b_b[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  real32_T Kg[12];
  real32_T b_a[3];
  static const int8_T iv0[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
  };

  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  g_st.prev = &f_st;
  g_st.tls = f_st.tls;
  covrtLogFcn(&emlrtCoverageInstance, 0U, 0);
  covrtLogBasicBlock(&emlrtCoverageInstance, 0U, 0);

  /* function y = test_ekf(gyroX,gyroY,gyroZ,accX,accY,accZ,dt ) */
  /*      gyroX,gyroY,gyroZ,...        %陀螺仪原始值 */
  /*      accX,accY,accZ,...         %加速度原始值 m/s^2 */
  /*      %magX,magY,magZ,...         %地磁原始值 */
  /*      dt)  %积分时间 */
  /* 状态转移矩阵..。 */
  A[0] = 1.0F;
  A[4] = -0.5F * dt * gyroX;
  A[8] = -0.5F * dt * gyroY;
  A[12] = -0.5F * dt * gyroZ;
  A[1] = 0.5F * dt * gyroX;
  A[5] = 1.0F;
  A[9] = 0.5F * dt * gyroZ;
  A[13] = -0.5F * dt * gyroY;
  A[2] = 0.5F * dt * gyroY;
  A[6] = -0.5F * dt * gyroZ;
  A[10] = 1.0F;
  A[14] = 0.5F * dt * gyroX;
  A[3] = 0.5F * dt * gyroZ;
  A[7] = 0.5F * dt * gyroY;
  A[11] = -0.5F * dt * gyroX;
  A[15] = 1.0F;

  /* Q */
  /* R */
  /* --- Dataset parameters */
  /* deltat = 1/200;             % Sampling period */
  /* noise_gyro = 2.4e-2;        % Gyroscope noise(discrete), rad/s */
  /* noise_accel = 2.83e-2;      % Accelerometer noise, m/s^2 */
  /*  Gyroscope noise(discrete), rad/s */
  /*  Gravity magnitude, m/s^2 */
  /*  Initial state conditions */
  if (covrtLogIf(&emlrtCoverageInstance, 0U, 0U, 0, !states_est_not_empty)) {
    covrtLogBasicBlock(&emlrtCoverageInstance, 0U, 1);

    /* states_est = [1;0;0;0];             % x_est=[x,y,Vx,Vy,Ax,Ay]' */
    for (rtemp = 0; rtemp < 4; rtemp++) {
      states_est[rtemp] = TX[rtemp];
    }

    states_est_not_empty = true;
    memcpy(&P_P_est[0], &fv0[0], sizeof(real32_T) << 4);
  }

  covrtLogBasicBlock(&emlrtCoverageInstance, 0U, 2);

  /*  状态预测，协方差预测 */
  maxval = 0.0F;
  scale = 1.17549435E-38F;
  for (rtemp = 0; rtemp < 4; rtemp++) {
    states_prd[rtemp] = 0.0F;
    for (r2 = 0; r2 < 4; r2++) {
      states_prd[rtemp] += A[rtemp + (r2 << 2)] * states_est[r2];
    }

    absxk = muSingleScalarAbs(states_prd[rtemp]);
    if (absxk > scale) {
      t = scale / absxk;
      maxval = 1.0F + maxval * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      maxval += t * t;
    }
  }

  maxval = scale * muSingleScalarSqrt(maxval);
  for (r2 = 0; r2 < 4; r2++) {
    states_prd[r2] /= maxval;
  }

  /* 四元数归一化 */
  H[0] = -states_est[1];
  H[4] = -states_est[2];
  H[8] = -states_est[3];
  H[1] = states_est[0];
  H[5] = -states_est[3];
  H[9] = states_est[2];
  H[2] = states_est[3];
  H[6] = states_est[0];
  H[10] = -states_est[1];
  H[3] = -states_est[2];
  H[7] = states_est[1];
  H[11] = states_est[0];
  for (r2 = 0; r2 < 3; r2++) {
    for (r1 = 0; r1 < 4; r1++) {
      G[r1 + (r2 << 2)] = H[r1 + (r2 << 2)] / 2.0F;
    }
  }

  st.site = &emlrtRSI;
  maxval = mpower(0.0024F * dt);
  for (r2 = 0; r2 < 4; r2++) {
    for (r1 = 0; r1 < 4; r1++) {
      b_A[r2 + (r1 << 2)] = 0.0F;
      for (rtemp = 0; rtemp < 4; rtemp++) {
        b_A[r2 + (r1 << 2)] += A[r2 + (rtemp << 2)] * P_P_est[rtemp + (r1 << 2)];
      }

      b_G[r2 + (r1 << 2)] = 0.0F;
      for (rtemp = 0; rtemp < 3; rtemp++) {
        b_G[r2 + (r1 << 2)] += G[r2 + (rtemp << 2)] * G[r1 + (rtemp << 2)];
      }
    }

    for (r1 = 0; r1 < 4; r1++) {
      absxk = 0.0F;
      for (rtemp = 0; rtemp < 4; rtemp++) {
        absxk += b_A[r2 + (rtemp << 2)] * A[r1 + (rtemp << 2)];
      }

      P_P_prd[r2 + (r1 << 2)] = absxk + maxval * b_G[r2 + (r1 << 2)];
    }
  }

  /* 估计量 */
  a[0] = accX;
  a[1] = accY;
  a[2] = accZ;

  /*  [ -2*q2,  2*q3, -2*q0, 2*q1] */
  /*  [  2*q1,  2*q0,  2*q3, 2*q2] */
  /*  [  2*q0, -2*q1, -2*q2, 2*q3] */
  b_H[0] = -2.0F * states_prd[2];
  b_H[3] = 2.0F * states_prd[3];
  b_H[6] = -2.0F * states_prd[0];
  b_H[9] = 2.0F * states_prd[1];
  b_H[1] = 2.0F * states_prd[1];
  b_H[4] = 2.0F * states_prd[0];
  b_H[7] = 2.0F * states_prd[3];
  b_H[10] = 2.0F * states_prd[2];
  b_H[2] = 2.0F * states_prd[0];
  b_H[5] = -2.0F * states_prd[1];
  b_H[8] = -2.0F * states_prd[2];
  b_H[11] = 2.0F * states_prd[3];

  /*  H =[ (98*states(3))/5, -(98*states(4))/5,  (98*states(1))/5, -(98*states(2))/5;... */
  /*      -(98*states(2))/5, -(98*states(1))/5, -(98*states(4))/5, -(98*states(3))/5;... */
  /*      -(98*states(1))/5,  (98*states(2))/5,  (98*states(3))/5, -(98*states(4))/5]; */
  t = norm(a);

  /*  Measurement noise R */
  st.site = &b_emlrtRSI;
  maxval = mpower(0.0283F / norm(a));
  st.site = &c_emlrtRSI;
  scale = mpower(1.0F - 9.81007F / norm(a));
  for (r2 = 0; r2 < 4; r2++) {
    for (r1 = 0; r1 < 3; r1++) {
      G[r2 + (r1 << 2)] = 0.0F;
      for (rtemp = 0; rtemp < 4; rtemp++) {
        G[r2 + (r1 << 2)] += P_P_prd[r2 + (rtemp << 2)] * b_H[r1 + 3 * rtemp];
      }
    }
  }

  for (r2 = 0; r2 < 3; r2++) {
    for (r1 = 0; r1 < 4; r1++) {
      H[r2 + 3 * r1] = 0.0F;
      for (rtemp = 0; rtemp < 4; rtemp++) {
        H[r2 + 3 * r1] += b_H[r2 + 3 * rtemp] * P_P_prd[rtemp + (r1 << 2)];
      }
    }

    for (r1 = 0; r1 < 3; r1++) {
      absxk = 0.0F;
      for (rtemp = 0; rtemp < 4; rtemp++) {
        absxk += H[r2 + 3 * rtemp] * b_H[r1 + 3 * rtemp];
      }

      b[r2 + 3 * r1] = absxk + (maxval * (real32_T)b_b[r2 + 3 * r1] + scale *
        (real32_T)b_b[r2 + 3 * r1]);
    }
  }

  st.site = &d_emlrtRSI;
  b_st.site = &g_emlrtRSI;
  c_st.site = &h_emlrtRSI;
  d_st.site = &i_emlrtRSI;
  e_st.site = &j_emlrtRSI;
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = muSingleScalarAbs(b[0]);
  scale = muSingleScalarAbs(b[1]);
  if (scale > maxval) {
    maxval = scale;
    r1 = 1;
    r2 = 0;
  }

  if (muSingleScalarAbs(b[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  b[r2] /= b[r1];
  b[r3] /= b[r1];
  b[3 + r2] -= b[r2] * b[3 + r1];
  b[3 + r3] -= b[r3] * b[3 + r1];
  b[6 + r2] -= b[r2] * b[6 + r1];
  b[6 + r3] -= b[r3] * b[6 + r1];
  if (muSingleScalarAbs(b[3 + r3]) > muSingleScalarAbs(b[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  b[3 + r3] /= b[3 + r2];
  b[6 + r3] -= b[3 + r3] * b[6 + r2];
  if ((b[r1] == 0.0F) || (b[3 + r2] == 0.0F) || (b[6 + r3] == 0.0F)) {
    f_st.site = &k_emlrtRSI;
    g_st.site = &l_emlrtRSI;
    warning(&g_st);
  }

  for (rtemp = 0; rtemp < 4; rtemp++) {
    Kg[rtemp + (r1 << 2)] = G[rtemp] / b[r1];
    Kg[rtemp + (r2 << 2)] = G[4 + rtemp] - Kg[rtemp + (r1 << 2)] * b[3 + r1];
    Kg[rtemp + (r3 << 2)] = G[8 + rtemp] - Kg[rtemp + (r1 << 2)] * b[6 + r1];
    Kg[rtemp + (r2 << 2)] /= b[3 + r2];
    Kg[rtemp + (r3 << 2)] -= Kg[rtemp + (r2 << 2)] * b[6 + r2];
    Kg[rtemp + (r3 << 2)] /= b[6 + r3];
    Kg[rtemp + (r2 << 2)] -= Kg[rtemp + (r3 << 2)] * b[3 + r3];
    Kg[rtemp + (r1 << 2)] -= Kg[rtemp + (r3 << 2)] * b[r3];
    Kg[rtemp + (r1 << 2)] -= Kg[rtemp + (r2 << 2)] * b[r2];
  }

  /* Kg= P(k|k-1)HT/(HP(k|k-1)HT+R) */
  for (r2 = 0; r2 < 3; r2++) {
    absxk = 0.0F;
    for (r1 = 0; r1 < 4; r1++) {
      absxk += b_H[r2 + 3 * r1] * states_prd[r1];
    }

    b_a[r2] = a[r2] / t - absxk;
  }

  /* P_P_est = P_P_prd -P_P_prd * H;    eye(4) */
  for (rtemp = 0; rtemp < 4; rtemp++) {
    absxk = 0.0F;
    for (r2 = 0; r2 < 3; r2++) {
      absxk += Kg[rtemp + (r2 << 2)] * b_a[r2];
    }

    states_est[rtemp] = states_prd[rtemp] + absxk;
    for (r2 = 0; r2 < 4; r2++) {
      absxk = 0.0F;
      for (r1 = 0; r1 < 3; r1++) {
        absxk += Kg[rtemp + (r1 << 2)] * b_H[r1 + 3 * r2];
      }

      b_A[rtemp + (r2 << 2)] = (real32_T)iv0[rtemp + (r2 << 2)] - absxk;
    }

    for (r2 = 0; r2 < 4; r2++) {
      P_P_est[rtemp + (r2 << 2)] = 0.0F;
      for (r1 = 0; r1 < 4; r1++) {
        P_P_est[rtemp + (r2 << 2)] += b_A[rtemp + (r1 << 2)] * P_P_prd[r1 + (r2 <<
          2)];
      }
    }

    y[rtemp] = states_est[rtemp];
  }
}

void states_est_not_empty_init(void)
{
  states_est_not_empty = false;
}

/* End of code generation (ekf_6dof.c) */
