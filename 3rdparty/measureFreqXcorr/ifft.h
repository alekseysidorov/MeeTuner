/*
 * ifft.h
 *
 * Code generation for function 'ifft'
 *
 * C source code generated on: Sat Jan 28 01:02:05 2012
 *
 */

#ifndef __IFFT_H__
#define __IFFT_H__
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
extern void ifft(const real32_T x[8192], creal32_T y[8192]);
#endif
/* End of code generation (ifft.h) */
