/*
 * File: ekf_6dof.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 13-Oct-2017 20:51:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ekf_6dof.h"
#include "norm.h"

/* Variable Definitions */
static float states_est[4];
static boolean_T states_est_not_empty;
static float P_P_est[16];

/* Function Definitions */

/*
 * function y = test_ekf(gyroX,gyroY,gyroZ,accX,accY,accZ,dt )
 *      gyroX,gyroY,gyroZ,...        %陀螺仪原始值
 *      accX,accY,accZ,...         %加速度原始值 m/s^2
 *      %magX,magY,magZ,...         %地磁原始值
 *      dt)  %积分时间
 * Arguments    : float gyroX
 *                float gyroY
 *                float gyroZ
 *                float accX
 *                float accY
 *                float accZ
 *                float dt
 *                const float TX[4]
 *                float y[4]
 * Return Type  : void
 */
void ekf_6dof(float gyroX, float gyroY, float gyroZ, float accX, float accY,
              float accZ, float dt, const float TX[4], float y[4])
{
  float A[16];
  float maxval;
  int rtemp;
  float scale;
  float states_prd[4];
  int r2;
  float absxk;
  float H[12];
  float t;
  float G[12];
  int r1;
  float b_A[16];
  float b_G[16];
  float P_P_prd[16];
  float a[3];
  float b_H[12];
  float c[9];
  int r3;
  static const signed char b[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  float Kg[12];
  float b_a[3];
  static const signed char iv0[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 1 };

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
  if (!states_est_not_empty) {
    /* states_est = [1;0;0;0];             % x_est=[x,y,Vx,Vy,Ax,Ay]' */
    for (rtemp = 0; rtemp < 4; rtemp++) {
      states_est[rtemp] = TX[rtemp];
    }

    states_est_not_empty = true;
  }

  /*  状态预测，协方差预测 */
  maxval = 0.0F;
  scale = 1.17549435E-38F;
  for (rtemp = 0; rtemp < 4; rtemp++) {
    states_prd[rtemp] = 0.0F;
    for (r2 = 0; r2 < 4; r2++) {
      states_prd[rtemp] += A[rtemp + (r2 << 2)] * states_est[r2];
    }

    absxk = (float)fabs(states_prd[rtemp]);
    if (absxk > scale) {
      t = scale / absxk;
      maxval = 1.0F + maxval * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      maxval += t * t;
    }
  }

  maxval = scale * (float)sqrt(maxval);
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

  maxval = 0.0024F * dt;
  maxval *= maxval;
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
  maxval = 0.0283F / norm(a);
  maxval *= maxval;
  scale = 9.81007F / norm(a);
  scale = (1.0F - scale) * (1.0F - scale);
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

      c[r2 + 3 * r1] = absxk + (maxval * (float)b[r2 + 3 * r1] + scale * (float)
        b[r2 + 3 * r1]);
    }
  }

  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = (float)fabs(c[0]);
  scale = (float)fabs(c[1]);
  if (scale > maxval) {
    maxval = scale;
    r1 = 1;
    r2 = 0;
  }

  if ((float)fabs(c[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  c[r2] /= c[r1];
  c[r3] /= c[r1];
  c[3 + r2] -= c[r2] * c[3 + r1];
  c[3 + r3] -= c[r3] * c[3 + r1];
  c[6 + r2] -= c[r2] * c[6 + r1];
  c[6 + r3] -= c[r3] * c[6 + r1];
  if ((float)fabs(c[3 + r3]) > (float)fabs(c[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  c[3 + r3] /= c[3 + r2];
  c[6 + r3] -= c[3 + r3] * c[6 + r2];
  for (rtemp = 0; rtemp < 4; rtemp++) {
    Kg[rtemp + (r1 << 2)] = G[rtemp] / c[r1];
    Kg[rtemp + (r2 << 2)] = G[4 + rtemp] - Kg[rtemp + (r1 << 2)] * c[3 + r1];
    Kg[rtemp + (r3 << 2)] = G[8 + rtemp] - Kg[rtemp + (r1 << 2)] * c[6 + r1];
    Kg[rtemp + (r2 << 2)] /= c[3 + r2];
    Kg[rtemp + (r3 << 2)] -= Kg[rtemp + (r2 << 2)] * c[6 + r2];
    Kg[rtemp + (r3 << 2)] /= c[6 + r3];
    Kg[rtemp + (r2 << 2)] -= Kg[rtemp + (r3 << 2)] * c[3 + r3];
    Kg[rtemp + (r1 << 2)] -= Kg[rtemp + (r3 << 2)] * c[r3];
    Kg[rtemp + (r1 << 2)] -= Kg[rtemp + (r2 << 2)] * c[r2];
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

      b_A[rtemp + (r2 << 2)] = (float)iv0[rtemp + (r2 << 2)] - absxk;
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

/*
 * Arguments    : void
 * Return Type  : void
 */
void ekf_6dof_init(void)
{
  static const float fv0[16] = { 1.0E-10F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0E-10F,
    0.0F, 0.0F, 0.0F, 0.0F, 1.0E-10F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0E-10F };

  memcpy(&P_P_est[0], &fv0[0], sizeof(float) << 4);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void states_est_not_empty_init(void)
{
  states_est_not_empty = false;
}

/*
 * File trailer for ekf_6dof.c
 *
 * [EOF]
 */
