/*
 * diff.cpp
 *
 * Code generation for function 'diff'
 *
 * C source code generated on: Sat Jan 28 13:22:16 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getNote.h"
#include "measureFreqXcorr.h"
#include "diff.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void diff(const boolean_T x[8192], real_T y[8191])
{
  int32_T ixLead;
  int32_T iyLead;
  int32_T work;
  int32_T m;
  int32_T tmp2;
  ixLead = 1;
  iyLead = 0;
  work = x[0];
  for (m = 0; m < 8191; m++) {
    tmp2 = work;
    work = x[ixLead];
    tmp2 = x[ixLead] - tmp2;
    ixLead++;
    y[iyLead] = (real_T)tmp2;
    iyLead++;
  }
}

/* End of code generation (diff.cpp) */
