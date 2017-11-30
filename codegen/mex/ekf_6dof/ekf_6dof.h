/*
 * ekf_6dof.h
 *
 * Code generation for function 'ekf_6dof'
 *
 */

#ifndef EKF_6DOF_H
#define EKF_6DOF_H

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "covrt.h"
#include "rtwtypes.h"
#include "ekf_6dof_types.h"

/* Function Declarations */
extern void P_P_est_not_empty_init(void);
extern void ekf_6dof(const emlrtStack *sp, real32_T gyroX, real32_T gyroY,
                     real32_T gyroZ, real32_T accX, real32_T accY, real32_T accZ,
                     real32_T dt, const real32_T TX[4], real32_T y[4]);
extern void states_est_not_empty_init(void);

#endif

/* End of code generation (ekf_6dof.h) */
