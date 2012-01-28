/*
 * ifft.cpp
 *
 * Code generation for function 'ifft'
 *
 * C source code generated on: Sun Jan 29 01:38:19 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getNote.h"
#include "measureFreqXcorr.h"
#include "ifft.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void ifft(const real32_T x[8192], creal32_T y[8192])
{
  static creal32_T b_y1[8192];
  real32_T costab1q[2049];
  int32_T k;
  real32_T costab[4097];
  real32_T sintab[4097];
  int32_T ix;
  uint32_T ju;
  int32_T iy;
  int32_T i;
  uint32_T n;
  boolean_T tst;
  real32_T temp_re;
  real32_T temp_im;
  int32_T iDelta;
  int32_T iDelta2;
  int32_T iheight;
  int32_T ihi;
  costab1q[0] = 1.0F;
  for (k = 0; k < 1024; k++) {
    costab1q[k + 1] = (real32_T)cos(0.000766990415F * ((real32_T)k + 1.0F));
  }

  for (k = 0; k < 1023; k++) {
    costab1q[k + 1025] = (real32_T)sin(0.000766990415F * (2048.0F - ((real32_T)k
      + 1025.0F)));
  }

  costab1q[2048] = 0.0F;
  costab[0] = 1.0F;
  sintab[0] = 0.0F;
  for (k = 0; k < 2048; k++) {
    costab[k + 1] = costab1q[k + 1];
    sintab[k + 1] = costab1q[2047 - k];
  }

  for (k = 0; k < 2048; k++) {
    costab[k + 2049] = -costab1q[2047 - k];
    sintab[k + 2049] = costab1q[k + 1];
  }

  ix = 0;
  ju = 0U;
  iy = 0;
  for (i = 0; i < 8191; i++) {
    b_y1[iy].re = x[ix];
    b_y1[iy].im = 0.0F;
    n = 8192U;
    tst = TRUE;
    while (tst) {
      n >>= 1U;
      ju ^= n;
      tst = ((int32_T)(ju & n) == 0);
    }

    iy = (int32_T)ju;
    ix++;
  }

  b_y1[iy].re = x[ix];
  b_y1[iy].im = 0.0F;
  for (i = 0; i < 8192; i += 2) {
    temp_re = b_y1[i + 1].re;
    temp_im = b_y1[i + 1].im;
    b_y1[i + 1].re = b_y1[i].re - b_y1[i + 1].re;
    b_y1[i + 1].im = b_y1[i].im - b_y1[i + 1].im;
    b_y1[i].re += temp_re;
    b_y1[i].im += temp_im;
  }

  iDelta = 2;
  iDelta2 = 4;
  k = 2048;
  iheight = 8189;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      ix = i + iDelta;
      temp_re = b_y1[ix].re;
      temp_im = b_y1[ix].im;
      b_y1[i + iDelta].re = b_y1[i].re - b_y1[ix].re;
      b_y1[i + iDelta].im = b_y1[i].im - b_y1[ix].im;
      b_y1[i].re += temp_re;
      b_y1[i].im += temp_im;
    }

    ix = 1;
    for (iy = k; iy < 4096; iy += k) {
      i = ix;
      ihi = ix + iheight;
      while (i < ihi) {
        temp_re = costab[iy] * b_y1[i + iDelta].re - sintab[iy] * b_y1[i +
          iDelta].im;
        temp_im = costab[iy] * b_y1[i + iDelta].im + sintab[iy] * b_y1[i +
          iDelta].re;
        b_y1[i + iDelta].re = b_y1[i].re - temp_re;
        b_y1[i + iDelta].im = b_y1[i].im - temp_im;
        b_y1[i].re += temp_re;
        b_y1[i].im += temp_im;
        i += iDelta2;
      }

      ix++;
    }

    k >>= 1;
    iDelta = iDelta2;
    iDelta2 <<= 1;
    iheight -= iDelta;
  }

  for (ix = 0; ix < 8192; ix++) {
    b_y1[ix].re *= 0.000122070313F;
    b_y1[ix].im *= 0.000122070313F;
    y[ix] = b_y1[ix];
  }
}

/* End of code generation (ifft.cpp) */
