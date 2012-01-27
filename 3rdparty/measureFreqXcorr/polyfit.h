/*
 * polyfit.h
 *
 * Code generation for function 'polyfit'
 *
 * C source code generated on: Sat Jan 28 01:02:05 2012
 *
 */

#ifndef __POLYFIT_H__
#define __POLYFIT_H__
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
extern void polyfit(const real_T x[7], const creal32_T y[7], creal32_T p[3]);
#endif
/* End of code generation (polyfit.h) */
