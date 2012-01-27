/*
 * fft.c
 *
 * Code generation for function 'fft'
 *
 * C source code generated on: Fri Jan 27 01:45:06 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "measureFreqXcorr.h"
#include "fft.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void fft(const real_T x[8192], creal_T y[8192])
{
  static creal_T b_y1[8192];
  real_T costab1q[2049];
  int32_T k;
  real_T costab[4097];
  real_T sintab[4097];
  int32_T ix;
  uint32_T ju;
  int32_T iy;
  int32_T i;
  uint32_T n;
  boolean_T tst;
  real_T temp_re;
  real_T temp_im;
  int32_T iDelta;
  int32_T iDelta2;
  int32_T iheight;
  int32_T ihi;
  costab1q[0] = 1.0;
  for (k = 0; k < 1024; k++) {
    costab1q[k + 1] = cos(0.00076699039394282058 * ((real_T)k + 1.0));
  }

  for (k = 0; k < 1023; k++) {
    costab1q[k + 1025] = sin(0.00076699039394282058 * (2048.0 - ((real_T)k +
      1025.0)));
  }

  costab1q[2048] = 0.0;
  costab[0] = 1.0;
  sintab[0] = 0.0;
  for (k = 0; k < 2048; k++) {
    costab[k + 1] = costab1q[k + 1];
    sintab[k + 1] = -costab1q[2047 - k];
  }

  for (k = 0; k < 2048; k++) {
    costab[k + 2049] = -costab1q[2047 - k];
    sintab[k + 2049] = -costab1q[k + 1];
  }

  ix = 0;
  ju = 0U;
  iy = 0;
  for (i = 0; i < 8191; i++) {
    b_y1[iy].re = x[ix];
    b_y1[iy].im = 0.0;
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
  b_y1[iy].im = 0.0;
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

  memcpy((void *)&y[0], (void *)&b_y1[0], sizeof(creal_T) << 13);
}

/* End of code generation (fft.c) */
