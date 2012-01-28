/*
 * mrdivide.h
 *
 * Code generation for function 'mrdivide'
 *
 * C source code generated on: Sat Jan 28 13:22:16 2012
 *
 */

#ifndef __MRDIVIDE_H__
#define __MRDIVIDE_H__
/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"

#include "rtwtypes.h"
#include "getNote_types.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern real32_T b_mrdivide(real32_T A, real32_T B);
extern void c_mrdivide(const creal32_T A[8192], const creal32_T B, creal32_T y[8192]);
extern real32_T mrdivide(real32_T A, real_T B);
#endif
/* End of code generation (mrdivide.h) */
