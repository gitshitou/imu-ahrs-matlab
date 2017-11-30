/*
 * File: norm.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 13-Oct-2017 20:51:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "ekf_6dof.h"
#include "norm.h"

/* Function Definitions */

/*
 * Arguments    : const float x[3]
 * Return Type  : float
 */
float norm(const float x[3])
{
  float y;
  float scale;
  int k;
  float absxk;
  float t;
  y = 0.0F;
  scale = 1.17549435E-38F;
  for (k = 0; k < 3; k++) {
    absxk = (float)fabs(x[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0F + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * (float)sqrt(y);
}

/*
 * File trailer for norm.c
 *
 * [EOF]
 */
