/*
 * norm.c
 *
 * Code generation for function 'norm'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ekf_6dof.h"
#include "norm.h"

/* Function Definitions */
real32_T norm(const real32_T x[3])
{
  real32_T y;
  real32_T scale;
  int32_T k;
  real32_T absxk;
  real32_T t;
  y = 0.0F;
  scale = 1.17549435E-38F;
  for (k = 0; k < 3; k++) {
    absxk = muSingleScalarAbs(x[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0F + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * muSingleScalarSqrt(y);
}

/* End of code generation (norm.c) */
