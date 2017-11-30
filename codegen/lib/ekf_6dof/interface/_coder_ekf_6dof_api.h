/*
 * File: _coder_ekf_6dof_api.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 13-Oct-2017 20:51:32
 */

#ifndef _CODER_EKF_6DOF_API_H
#define _CODER_EKF_6DOF_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_ekf_6dof_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void ekf_6dof(real32_T gyroX, real32_T gyroY, real32_T gyroZ, real32_T
                     accX, real32_T accY, real32_T accZ, real32_T dt, real32_T
                     TX[4], real32_T y[4]);
extern void ekf_6dof_api(const mxArray * const prhs[8], const mxArray *plhs[1]);
extern void ekf_6dof_atexit(void);
extern void ekf_6dof_initialize(void);
extern void ekf_6dof_terminate(void);
extern void ekf_6dof_xil_terminate(void);

#endif

/*
 * File trailer for _coder_ekf_6dof_api.h
 *
 * [EOF]
 */
