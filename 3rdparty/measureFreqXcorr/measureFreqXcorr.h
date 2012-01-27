/*
 * measureFreqXcorr.h
 *
 * Code generation for function 'measureFreqXcorr'
 *
 * C source code generated on: Sat Jan 28 01:02:05 2012
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
extern creal32_T eml_div(const creal32_T x, real_T y);
extern void measureFreqXcorr(const int32_T s[8192], real32_T Fs, real32_T *F, real32_T *snr, creal32_T w[8192]);
#endif
/* End of code generation (measureFreqXcorr.h) */
