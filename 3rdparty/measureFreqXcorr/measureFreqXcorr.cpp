/*
 * measureFreqXcorr.cpp
 *
 * Code generation for function 'measureFreqXcorr'
 *
 * C source code generated on: Sun Jan 29 01:38:19 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getNote.h"
#include "measureFreqXcorr.h"
#include "mrdivide.h"
#include "polyfit.h"
#include "diff.h"
#include "ifft.h"
#include "power.h"
#include "abs.h"
#include "fft.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void measureFreqXcorr(const int32_T s[8192], real32_T Fs, real32_T *F, real32_T *
                      snr, creal32_T w[8192])
{
  static real32_T b_s[8192];
  int32_T i0;
  static real32_T sh[8192];
  real32_T b_sh[8192];
  static creal32_T c_sh[8192];
  static creal32_T d_sh[8192];
  boolean_T e_sh[8192];
  static real_T shd[8191];
  boolean_T poses_pos[8191];
  boolean_T poses_neg[8191];
  int32_T idx;
  int16_T ii_data[1];
  int8_T ii_sizes[2];
  int32_T ixstart;
  boolean_T exitg3;
  int16_T idx_start_data[1];
  int16_T b_ii_data[8191];
  int16_T b_ii_sizes[2];
  boolean_T exitg2;
  boolean_T guard1 = FALSE;
  int32_T tmp_data[8191];
  int16_T c_ii_data[8191];
  int32_T ix;
  int16_T idx_ends_data[8191];
  real32_T mtmp;
  boolean_T exitg1;
  real32_T f_sh[7];
  real_T b_idx;
  real_T c_idx[7];
  real32_T PP[3];
  real32_T PZ;
  for (i0 = 0; i0 < 8192; i0++) {
    b_s[i0] = (real32_T)s[i0];
  }

  fft(b_s, w);
  b_abs(w, sh);
  memcpy((void *)&b_sh[0], (void *)&sh[0], sizeof(real32_T) << 13);
  power(b_sh, sh);
  ifft(sh, c_sh);
  memcpy((void *)&d_sh[0], (void *)&c_sh[0], sizeof(creal32_T) << 13);
  c_mrdivide(d_sh, c_sh[0], c_sh);
  for (i0 = 0; i0 < 8192; i0++) {
    e_sh[i0] = (c_sh[i0].re > 0.5F);
    sh[i0] = c_sh[i0].re;
  }

  diff(e_sh, shd);
  for (i0 = 0; i0 < 8191; i0++) {
    poses_pos[i0] = (shd[i0] > 0.0);
    poses_neg[i0] = (shd[i0] < 0.0);
  }

  idx = 0;
  for (i0 = 0; i0 < 2; i0++) {
    ii_sizes[i0] = 1;
  }

  ixstart = 1;
  exitg3 = 0U;
  while ((exitg3 == 0U) && (ixstart < 8192)) {
    if (poses_pos[ixstart - 1]) {
      idx = 1;
      ii_data[0] = (int16_T)ixstart;
      exitg3 = 1U;
    } else {
      ixstart++;
    }
  }

  if (idx == 0) {
    ii_sizes[0] = 1;
    ii_sizes[1] = 0;
  }

  ixstart = ii_sizes[1] - 1;
  i0 = 0;
  while (i0 <= ixstart) {
    idx_start_data[0] = ii_data[0];
    i0 = 1;
  }

  idx = 0;
  for (i0 = 0; i0 < 2; i0++) {
    b_ii_sizes[i0] = (int16_T)(1 + 8190 * i0);
  }

  ixstart = 1;
  exitg2 = 0U;
  while ((exitg2 == 0U) && (ixstart < 8192)) {
    guard1 = FALSE;
    if (poses_neg[ixstart - 1]) {
      idx++;
      b_ii_data[idx - 1] = (int16_T)ixstart;
      if (idx >= 8191) {
        exitg2 = 1U;
      } else {
        guard1 = TRUE;
      }
    } else {
      guard1 = TRUE;
    }

    if (guard1 == TRUE) {
      ixstart++;
    }
  }

  if (1 > idx) {
    idx = 0;
  }

  ixstart = idx - 1;
  for (i0 = 0; i0 <= ixstart; i0++) {
    tmp_data[i0] = 1 + i0;
  }

  ixstart = idx - 1;
  for (i0 = 0; i0 <= ixstart; i0++) {
    ix = 0;
    while (ix <= 0) {
      c_ii_data[i0] = b_ii_data[tmp_data[i0] - 1];
      ix = 1;
    }
  }

  b_ii_sizes[0] = 1;
  b_ii_sizes[1] = (int16_T)idx;
  ixstart = idx - 1;
  for (i0 = 0; i0 <= ixstart; i0++) {
    b_ii_data[i0] = c_ii_data[i0];
  }

  ixstart = b_ii_sizes[1] - 1;
  for (i0 = 0; i0 <= ixstart; i0++) {
    idx_ends_data[i0] = b_ii_data[i0];
  }

  for (ixstart = 0; ixstart <= idx_start_data[0] - 2; ixstart++) {
    sh[ixstart] = 0.0F;
  }

  for (ixstart = 0; ixstart <= 8191 - idx_ends_data[0]; ixstart++) {
    sh[idx_ends_data[0] + ixstart] = 0.0F;
  }

  ixstart = 1;
  mtmp = sh[0];
  idx = 1;
  if (rtIsNaNF(sh[0])) {
    ix = 2;
    exitg1 = 0U;
    while ((exitg1 == 0U) && (ix < 8193)) {
      ixstart = ix;
      if (!rtIsNaNF(sh[ix - 1])) {
        mtmp = sh[ix - 1];
        exitg1 = 1U;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 8192) {
    while (ixstart + 1 < 8193) {
      if (sh[ixstart] > mtmp) {
        mtmp = sh[ixstart];
        idx = ixstart + 1;
      }

      ixstart++;
    }
  }

  if (idx < 4) {
    idx = 4;
  } else {
    if (idx > 8189) {
      idx = 8189;
    }
  }

  for (i0 = 0; i0 < 7; i0++) {
    b_idx = (real_T)idx + (-3.0 + (real_T)i0);
    f_sh[i0] = sh[(int32_T)b_idx - 1];
    c_idx[i0] = b_idx;
  }

  polyfit(c_idx, f_sh, PP);
  PZ = b_mrdivide(mrdivide(-PP[1], 2.0), PP[0]);
  if (PZ > 0.0F) {
    *F = b_mrdivide(Fs, PZ - 1.0F);
  } else {
    *F = 0.0F * Fs;
  }

  *snr = (real32_T)fabs(mtmp);
}

/* End of code generation (measureFreqXcorr.cpp) */
