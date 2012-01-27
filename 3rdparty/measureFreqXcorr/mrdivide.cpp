/*
 * mrdivide.cpp
 *
 * Code generation for function 'mrdivide'
 *
 * C source code generated on: Sat Jan 28 01:02:05 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "measureFreqXcorr.h"
#include "mrdivide.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
creal32_T b_mrdivide(real32_T A, const creal32_T B)
{
  creal32_T y;
  real32_T brm;
  real32_T bim;
  real32_T d;
  if (B.im == 0.0F) {
    y.re = A / B.re;
    y.im = 0.0F;
  } else if (B.re == 0.0F) {
    if (A == 0.0F) {
      y.re = 0.0F / B.im;
      y.im = 0.0F;
    } else {
      y.re = 0.0F;
      y.im = -(A / B.im);
    }
  } else {
    brm = (real32_T)fabs(B.re);
    bim = (real32_T)fabs(B.im);
    if (brm > bim) {
      bim = B.im / B.re;
      d = B.re + bim * B.im;
      y.re = (A + bim * 0.0F) / d;
      y.im = (0.0F - bim * A) / d;
    } else if (bim == brm) {
      bim = B.re > 0.0F ? 0.5F : -0.5F;
      d = B.im > 0.0F ? 0.5F : -0.5F;
      y.re = A * bim / brm;
      y.im = (-0.0F - A * d) / brm;
    } else {
      bim = B.re / B.im;
      d = B.im + bim * B.re;
      y.re = bim * A / d;
      y.im = (bim * 0.0F - A) / d;
    }
  }

  return y;
}

creal32_T mrdivide(const creal32_T A, const creal32_T B)
{
  creal32_T y;
  real32_T brm;
  real32_T bim;
  real32_T d;
  if (B.im == 0.0F) {
    if (A.im == 0.0F) {
      y.re = A.re / B.re;
      y.im = 0.0F;
    } else if (A.re == 0.0F) {
      y.re = 0.0F;
      y.im = A.im / B.re;
    } else {
      y.re = A.re / B.re;
      y.im = A.im / B.re;
    }
  } else if (B.re == 0.0F) {
    if (A.re == 0.0F) {
      y.re = A.im / B.im;
      y.im = 0.0F;
    } else if (A.im == 0.0F) {
      y.re = 0.0F;
      y.im = -(A.re / B.im);
    } else {
      y.re = A.im / B.im;
      y.im = -(A.re / B.im);
    }
  } else {
    brm = (real32_T)fabs(B.re);
    bim = (real32_T)fabs(B.im);
    if (brm > bim) {
      bim = B.im / B.re;
      d = B.re + bim * B.im;
      y.re = (A.re + bim * A.im) / d;
      y.im = (A.im - bim * A.re) / d;
    } else if (bim == brm) {
      bim = B.re > 0.0F ? 0.5F : -0.5F;
      d = B.im > 0.0F ? 0.5F : -0.5F;
      y.re = (A.re * bim + A.im * d) / brm;
      y.im = (A.im * bim - A.re * d) / brm;
    } else {
      bim = B.re / B.im;
      d = B.im + bim * B.re;
      y.re = (bim * A.re + A.im) / d;
      y.im = (bim * A.im - A.re) / d;
    }
  }

  return y;
}

/* End of code generation (mrdivide.cpp) */
