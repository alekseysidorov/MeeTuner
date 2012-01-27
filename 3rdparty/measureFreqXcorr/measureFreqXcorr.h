/*
 * measureFreqXcorr.h
 *
 * Code generation for function 'measureFreqXcorr'
 *
 * C source code generated on: Fri Jan 27 01:45:06 2012
 *
 */

#ifndef __MEASUREFREQXCORR_H__
#define __MEASUREFREQXCORR_H__
/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"

#include "rtwtypes.h"
#include "measureFreqXcorr_types.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern creal_T eml_div(const creal_T x, real_T y);
extern void measureFreqXcorr(const real_T s[8192], real_T Fs, real_T *F, real_T *snr, creal_T w[8192]);
#endif
/* End of code generation (measureFreqXcorr.h) */
