/*
 * File: ekf_6dof.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 13-Oct-2017 20:51:32
 */

#ifndef EKF_6DOF_H
#define EKF_6DOF_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "ekf_6dof_types.h"

/* Function Declarations */
extern void ekf_6dof(float gyroX, float gyroY, float gyroZ, float accX, float
                     accY, float accZ, float dt, const float TX[4], float y[4]);
extern void ekf_6dof_init(void);
extern void states_est_not_empty_init(void);

#endif

/*
 * File trailer for ekf_6dof.h
 *
 * [EOF]
 */
