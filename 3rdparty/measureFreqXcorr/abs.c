/*
 * abs.c
 *
 * Code generation for function 'abs'
 *
 * C source code generated on: Fri Jan 27 01:45:06 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "measureFreqXcorr.h"
#include "abs.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_abs(const creal_T x[8192], real_T y[8192])
{
  int32_T k;
  real_T a;
  real_T b;
  for (k = 0; k < 8192; k++) {
    a = fabs(x[k].re);
    b = fabs(x[k].im);
    if (a < b) {
      a /= b;
      b *= sqrt(a * a + 1.0);
    } else if (a > b) {
      b /= a;
      b = sqrt(b * b + 1.0) * a;
    } else if (rtIsNaN(b)) {
    } else {
      b = a * 1.4142135623730951;
    }

    y[k] = b;
  }
}

/* End of code generation (abs.c) */
