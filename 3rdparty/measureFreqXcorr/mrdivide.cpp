/*
 * mrdivide.cpp
 *
 * Code generation for function 'mrdivide'
 *
 * C source code generated on: Sun Jan 29 01:38:19 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getNote.h"
#include "measureFreqXcorr.h"
#include "mrdivide.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
real32_T b_mrdivide(real32_T A, real32_T B)
{
  return A / B;
}

void c_mrdivide(const creal32_T A[8192], const creal32_T B, creal32_T y[8192])
{
  int32_T i1;
  real32_T brm;
  real32_T bim;
  real32_T d;
  for (i1 = 0; i1 < 8192; i1++) {
    if (B.im == 0.0F) {
      if (A[i1].im == 0.0F) {
        y[i1].re = A[i1].re / B.re;
        y[i1].im = 0.0F;
      } else if (A[i1].re == 0.0F) {
        y[i1].re = 0.0F;
        y[i1].im = A[i1].im / B.re;
      } else {
        y[i1].re = A[i1].re / B.re;
        y[i1].im = A[i1].im / B.re;
      }
    } else if (B.re == 0.0F) {
      if (A[i1].re == 0.0F) {
        y[i1].re = A[i1].im / B.im;
        y[i1].im = 0.0F;
      } else if (A[i1].im == 0.0F) {
        y[i1].re = 0.0F;
        y[i1].im = -(A[i1].re / B.im);
      } else {
        y[i1].re = A[i1].im / B.im;
        y[i1].im = -(A[i1].re / B.im);
      }
    } else {
      brm = (real32_T)fabs(B.re);
      bim = (real32_T)fabs(B.im);
      if (brm > bim) {
        bim = B.im / B.re;
        d = B.re + bim * B.im;
        y[i1].re = (A[i1].re + bim * A[i1].im) / d;
        y[i1].im = (A[i1].im - bim * A[i1].re) / d;
      } else if (bim == brm) {
        bim = B.re > 0.0F ? 0.5F : -0.5F;
        d = B.im > 0.0F ? 0.5F : -0.5F;
        y[i1].re = (A[i1].re * bim + A[i1].im * d) / brm;
        y[i1].im = (A[i1].im * bim - A[i1].re * d) / brm;
      } else {
        bim = B.re / B.im;
        d = B.im + bim * B.re;
        y[i1].re = (bim * A[i1].re + A[i1].im) / d;
        y[i1].im = (bim * A[i1].im - A[i1].re) / d;
      }
    }
  }
}

real32_T mrdivide(real32_T A, real_T B)
{
  return A / (real32_T)B;
}

/* End of code generation (mrdivide.cpp) */
