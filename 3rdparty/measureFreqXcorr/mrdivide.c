/*
 * mrdivide.c
 *
 * Code generation for function 'mrdivide'
 *
 * C source code generated on: Fri Jan 27 01:45:06 2012
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
creal_T b_mrdivide(real_T A, const creal_T B)
{
  creal_T y;
  real_T brm;
  real_T bim;
  real_T d;
  if (B.im == 0.0) {
    y.re = A / B.re;
    y.im = 0.0;
  } else if (B.re == 0.0) {
    if (A == 0.0) {
      y.re = 0.0 / B.im;
      y.im = 0.0;
    } else {
      y.re = 0.0;
      y.im = -(A / B.im);
    }
  } else {
    brm = fabs(B.re);
    bim = fabs(B.im);
    if (brm > bim) {
      bim = B.im / B.re;
      d = B.re + bim * B.im;
      y.re = (A + bim * 0.0) / d;
      y.im = (0.0 - bim * A) / d;
    } else if (bim == brm) {
      bim = B.re > 0.0 ? 0.5 : -0.5;
      d = B.im > 0.0 ? 0.5 : -0.5;
      y.re = A * bim / brm;
      y.im = (-0.0 - A * d) / brm;
    } else {
      bim = B.re / B.im;
      d = B.im + bim * B.re;
      y.re = bim * A / d;
      y.im = (bim * 0.0 - A) / d;
    }
  }

  return y;
}

creal_T mrdivide(const creal_T A, const creal_T B)
{
  creal_T y;
  real_T brm;
  real_T bim;
  real_T d;
  if (B.im == 0.0) {
    if (A.im == 0.0) {
      y.re = A.re / B.re;
      y.im = 0.0;
    } else if (A.re == 0.0) {
      y.re = 0.0;
      y.im = A.im / B.re;
    } else {
      y.re = A.re / B.re;
      y.im = A.im / B.re;
    }
  } else if (B.re == 0.0) {
    if (A.re == 0.0) {
      y.re = A.im / B.im;
      y.im = 0.0;
    } else if (A.im == 0.0) {
      y.re = 0.0;
      y.im = -(A.re / B.im);
    } else {
      y.re = A.im / B.im;
      y.im = -(A.re / B.im);
    }
  } else {
    brm = fabs(B.re);
    bim = fabs(B.im);
    if (brm > bim) {
      bim = B.im / B.re;
      d = B.re + bim * B.im;
      y.re = (A.re + bim * A.im) / d;
      y.im = (A.im - bim * A.re) / d;
    } else if (bim == brm) {
      bim = B.re > 0.0 ? 0.5 : -0.5;
      d = B.im > 0.0 ? 0.5 : -0.5;
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

/* End of code generation (mrdivide.c) */
