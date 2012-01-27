/*
 * abs.cpp
 *
 * Code generation for function 'abs'
 *
 * C source code generated on: Sat Jan 28 01:30:07 2012
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
void b_abs(const creal32_T x[8192], real32_T y[8192])
{
  int32_T k;
  real32_T a;
  real32_T b;
  for (k = 0; k < 8192; k++) {
    a = (real32_T)fabs(x[k].re);
    b = (real32_T)fabs(x[k].im);
    if (a < b) {
      a /= b;
      b *= (real32_T)sqrt(a * a + 1.0F);
    } else if (a > b) {
      b /= a;
      b = (real32_T)sqrt(b * b + 1.0F) * a;
    } else if (rtIsNaNF(b)) {
    } else {
      b = a * 1.41421354F;
    }

    y[k] = b;
  }
}

/* End of code generation (abs.cpp) */
