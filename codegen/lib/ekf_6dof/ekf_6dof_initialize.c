/*
 * File: ekf_6dof_initialize.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 13-Oct-2017 20:51:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ekf_6dof.h"
#include "ekf_6dof_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void ekf_6dof_initialize(void)
{
  rt_InitInfAndNaN(8U);
  states_est_not_empty_init();
  ekf_6dof_init();
}

/*
 * File trailer for ekf_6dof_initialize.c
 *
 * [EOF]
 */
