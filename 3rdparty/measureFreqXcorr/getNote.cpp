/*
 * getNote.cpp
 *
 * Code generation for function 'getNote'
 *
 * C source code generated on: Sun Jan 29 01:38:19 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getNote.h"
#include "measureFreqXcorr.h"
#include "getNote_data.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void getNote(real32_T f, real_T *noteFreq, real32_T *noteError, char_T
             noteName_data[3], int32_T noteName_sizes[2], real_T *noteOctave)
{
  real32_T y[145];
  int32_T ixstart;
  real32_T mtmp;
  int32_T itmp;
  int32_T ix;
  boolean_T exitg1;
  real32_T fdbl;
  int32_T eint;
  real_T b_y;
  static const char_T cv0[2] = { 'B', 'b' };

  static const char_T cv1[2] = { 'C', '#' };

  static const char_T cv2[2] = { 'E', 'b' };

  static const char_T cv3[2] = { 'F', '#' };

  static const char_T cv4[2] = { 'A', 'b' };

  static const char_T cv5[3] = { 'N', 'a', 'N' };

  for (ixstart = 0; ixstart < 145; ixstart++) {
    y[ixstart] = (real32_T)fabs((real32_T)notes[ixstart] - f);
  }

  ixstart = 1;
  mtmp = y[0];
  itmp = 0;
  if (rtIsNaNF(y[0])) {
    ix = 2;
    exitg1 = 0U;
    while ((exitg1 == 0U) && (ix < 146)) {
      ixstart = ix;
      if (!rtIsNaNF(y[ix - 1])) {
        mtmp = y[ix - 1];
        exitg1 = 1U;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 145) {
    while (ixstart + 1 < 146) {
      if (y[ixstart] < mtmp) {
        mtmp = y[ixstart];
        itmp = ixstart;
      }

      ixstart++;
    }
  }

  *noteFreq = notes[itmp];
  fdbl = f / (real32_T)notes[itmp];
  if (fdbl == 0.0F) {
    fdbl = ((real32_T)rtMinusInf);
  } else if (fdbl < 0.0F) {
    fdbl = ((real32_T)rtNaN);
  } else {
    if ((!rtIsInfF(fdbl)) && (!rtIsNaNF(fdbl))) {
      if ((!rtIsInfF(fdbl)) && (!rtIsNaNF(fdbl))) {
        fdbl = (real32_T)frexp(fdbl, &eint);
        mtmp = (real32_T)eint;
      } else {
        mtmp = 0.0F;
      }

      if (fdbl == 0.5F) {
        fdbl = mtmp - 1.0F;
      } else {
        fdbl = (real32_T)log(fdbl) / 0.693147182F + mtmp;
      }
    }
  }

  *noteError = 100.0F * fdbl * 12.0F;
  b_y = ((real_T)(itmp + 1) - 1.0) / 12.0;
  if (b_y > 0.0) {
    ixstart = (int32_T)floor(b_y);
  } else {
    ixstart = 0;
  }

  *noteOctave = (real_T)ixstart + 1.0;
  switch ((itmp - (int32_T)floor(((real_T)(itmp + 1) - 1.0) / 12.0) * 12) + 1) {
   case 1:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'A';
    break;

   case 2:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 2;
    for (ixstart = 0; ixstart < 2; ixstart++) {
      noteName_data[ixstart] = cv0[ixstart];
    }
    break;

   case 3:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'B';
    break;

   case 4:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'C';
    break;

   case 5:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 2;
    for (ixstart = 0; ixstart < 2; ixstart++) {
      noteName_data[ixstart] = cv1[ixstart];
    }
    break;

   case 6:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'D';
    break;

   case 7:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 2;
    for (ixstart = 0; ixstart < 2; ixstart++) {
      noteName_data[ixstart] = cv2[ixstart];
    }
    break;

   case 8:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'E';
    break;

   case 9:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'F';
    break;

   case 10:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 2;
    for (ixstart = 0; ixstart < 2; ixstart++) {
      noteName_data[ixstart] = cv3[ixstart];
    }
    break;

   case 11:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'G';
    break;

   case 12:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 2;
    for (ixstart = 0; ixstart < 2; ixstart++) {
      noteName_data[ixstart] = cv4[ixstart];
    }
    break;

   default:
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 3;
    for (ixstart = 0; ixstart < 3; ixstart++) {
      noteName_data[ixstart] = cv5[ixstart];
    }
    break;
  }
}

/* End of code generation (getNote.cpp) */
