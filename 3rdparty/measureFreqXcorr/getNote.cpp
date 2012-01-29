/*
 * getNote.cpp
 *
 * Code generation for function 'getNote'
 *
 * C source code generated on: Sun Jan 29 22:42:04 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getNote.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static real_T notes[145];

/* Function Declarations */
static void b_abs(const creal32_T x_data[65535], const int32_T x_sizes[2],
                  real32_T y_data[65535], int32_T y_sizes[2]);
static void b_eml_fft(const real32_T x_data[65535], const int32_T x_sizes[1],
                      uint32_T n, creal32_T y_data[65535], int32_T y_sizes[1]);
static real32_T b_mrdivide(real32_T A, real32_T B);
static void c_mrdivide(const creal32_T A_data[65535], const int32_T A_sizes[2],
  const creal32_T B, creal32_T y_data[65535], int32_T y_sizes[2]);
static void diff(const boolean_T x_data[65535], const int32_T x_sizes[2], real_T
                 y_data[65534], int32_T y_sizes[2]);
static real32_T eml_div(real32_T x, real_T y);
static void eml_fft(const real32_T x[8192], uint32_T n, creal32_T y_data[65535],
                    int32_T y_sizes[1]);
static void eml_matlab_zlarf(int32_T m, int32_T n, int32_T iv0, real_T tau,
  real_T C[21], int32_T ic0, real_T work[3]);
static void eml_qrsolve(const real_T A[21], real32_T B[7], boolean_T
  ignoreRankDeficiency, real32_T Y[3], real_T *rankR);
static real32_T eml_scalar_abs(const creal32_T x);
static void eml_scalexp_alloc(const real32_T varargin_1_data[65535], const
  int32_T varargin_1_sizes[2], real32_T z_data[65535], int32_T z_sizes[2]);
static real_T eml_xnrm2(int32_T n, const real_T x[21], int32_T ix0);
static void fft(const real32_T x[8192], uint16_T varargin_1, creal32_T y_data
                [65535], int32_T y_sizes[2]);
static void ifft(const real32_T x_data[65535], const int32_T x_sizes[2],
                 creal32_T y_data[65535], int32_T y_sizes[2]);
static real32_T mrdivide(real32_T A, real_T B);
static void polyfit(const real_T x[7], const real32_T y[7], real32_T p[3]);
static void power(const real32_T a_data[65535], const int32_T a_sizes[2],
                  real32_T y_data[65535], int32_T y_sizes[2]);
static real_T rt_powd_snf(real_T u0, real_T u1);
static real32_T rt_powf_snf(real32_T u0, real32_T u1);

/* Function Definitions */

/*
 *
 */
static void b_abs(const creal32_T x_data[65535], const int32_T x_sizes[2],
                  real32_T y_data[65535], int32_T y_sizes[2])
{
  uint16_T uv0[2];
  int32_T k;
  for (k = 0; k < 2; k++) {
    uv0[k] = (uint16_T)x_sizes[k];
  }

  y_sizes[0] = 1;
  y_sizes[1] = uv0[1];
  for (k = 0; k <= x_sizes[1] - 1; k++) {
    y_data[k] = eml_scalar_abs(x_data[k]);
  }
}

/*
 *
 */
static void b_eml_fft(const real32_T x_data[65535], const int32_T x_sizes[1],
                      uint32_T n, creal32_T y_data[65535], int32_T y_sizes[1])
{
  int32_T nd2;
  int32_T b_n;
  int32_T nRows;
  int32_T nRowsM1;
  int32_T ixDelta;
  int32_T nRowsD2;
  int32_T nRowsD4;
  int32_T lastChan;
  real32_T e;
  real32_T costab1q_data[16385];
  int32_T k;
  static real32_T costab_data[32769];
  static real32_T sintab_data[32769];
  int32_T ix;
  int32_T chanStart;
  uint32_T ju;
  int32_T i;
  uint32_T c_n;
  boolean_T tst;
  real32_T temp_im;
  int32_T iDelta;
  int32_T iDelta2;
  int32_T iheight;
  int32_T ihi;
  y_sizes[0] = (int32_T)n;
  if (n > (uint32_T)x_sizes[0]) {
    nd2 = y_sizes[0];
    nd2--;
    for (b_n = 0; b_n <= nd2; b_n++) {
      y_data[b_n].re = 0.0F;
      y_data[b_n].im = 0.0F;
    }
  }

  if (x_sizes[0] == 0) {
  } else {
    nRows = (int32_T)n;
    if (x_sizes[0] > nRows) {
      nd2 = nRows;
    } else {
      nd2 = x_sizes[0];
    }

    nRowsM1 = nd2 - 1;
    nd2 = x_sizes[0] - nRowsM1;
    ixDelta = 1 >= nd2 ? 1 : nd2;
    nRowsD2 = (nRows + (nRows < 0)) >> 1;
    nRowsD4 = (nRowsD2 + (nRowsD2 < 0)) >> 1;
    lastChan = nRows * (x_sizes[0] / x_sizes[0] - 1);
    e = 6.28318548F / (real32_T)nRows;
    costab1q_data[0] = 1.0F;
    nd2 = (nRowsD4 + (nRowsD4 < 0)) >> 1;
    for (k = 1; k <= nd2; k++) {
      costab1q_data[k] = (real32_T)cos(e * (real32_T)k);
    }

    for (k = nd2 + 1; k <= nRowsD4 - 1; k++) {
      costab1q_data[k] = (real32_T)sin(e * (real32_T)(nRowsD4 - k));
    }

    costab1q_data[nRowsD4] = 0.0F;
    b_n = nRowsD4;
    nd2 = b_n << 1;
    costab_data[0] = 1.0F;
    sintab_data[0] = 0.0F;
    for (k = 1; k <= b_n; k++) {
      costab_data[k] = costab1q_data[k];
      sintab_data[k] = costab1q_data[b_n - k];
    }

    for (k = b_n + 1; k <= nd2; k++) {
      costab_data[k] = -costab1q_data[nd2 - k];
      sintab_data[k] = costab1q_data[k - b_n];
    }

    ix = 0;
    chanStart = 0;
    while ((nRows > 0) && (chanStart <= lastChan)) {
      ju = 0U;
      nd2 = chanStart;
      for (i = 1; i <= nRowsM1; i++) {
        y_data[nd2].re = x_data[ix];
        y_data[nd2].im = 0.0F;
        c_n = n;
        tst = TRUE;
        while (tst) {
          c_n >>= 1U;
          ju ^= c_n;
          tst = ((int32_T)(ju & c_n) == 0);
        }

        nd2 = chanStart + (int32_T)ju;
        ix++;
      }

      y_data[nd2].re = x_data[ix];
      y_data[nd2].im = 0.0F;
      ix += ixDelta;
      nd2 = chanStart + nRows;
      if (nRows > 1) {
        for (i = chanStart; i <= nd2 - 2; i += 2) {
          e = y_data[i + 1].re;
          temp_im = y_data[i + 1].im;
          y_data[i + 1].re = y_data[i].re - y_data[i + 1].re;
          y_data[i + 1].im = y_data[i].im - y_data[i + 1].im;
          y_data[i].re += e;
          y_data[i].im += temp_im;
        }
      }

      iDelta = 2;
      iDelta2 = 4;
      k = nRowsD4;
      iheight = 1 + ((nRowsD4 - 1) << 2);
      while (k > 0) {
        i = chanStart;
        ihi = chanStart + iheight;
        while (i < ihi) {
          nd2 = i + iDelta;
          e = y_data[nd2].re;
          temp_im = y_data[nd2].im;
          y_data[i + iDelta].re = y_data[i].re - y_data[nd2].re;
          y_data[i + iDelta].im = y_data[i].im - y_data[nd2].im;
          y_data[i].re += e;
          y_data[i].im += temp_im;
          i += iDelta2;
        }

        nd2 = chanStart + 1;
        for (b_n = k; b_n < nRowsD2; b_n += k) {
          i = nd2;
          ihi = nd2 + iheight;
          while (i < ihi) {
            e = costab_data[b_n] * y_data[i + iDelta].re - sintab_data[b_n] *
              y_data[i + iDelta].im;
            temp_im = costab_data[b_n] * y_data[i + iDelta].im + sintab_data[b_n]
              * y_data[i + iDelta].re;
            y_data[i + iDelta].re = y_data[i].re - e;
            y_data[i + iDelta].im = y_data[i].im - temp_im;
            y_data[i].re += e;
            y_data[i].im += temp_im;
            i += iDelta2;
          }

          nd2++;
        }

        k >>= 1;
        iDelta = iDelta2;
        iDelta2 <<= 1;
        iheight -= iDelta;
      }

      chanStart += nRows;
    }

    if (y_sizes[0] > 1) {
      e = 1.0F / (real32_T)y_sizes[0];
      nd2 = y_sizes[0] - 1;
      for (b_n = 0; b_n <= nd2; b_n++) {
        y_data[b_n].re *= e;
        y_data[b_n].im *= e;
      }
    }
  }
}

/*
 *
 */
static real32_T b_mrdivide(real32_T A, real32_T B)
{
  return A / B;
}

/*
 *
 */
static void c_mrdivide(const creal32_T A_data[65535], const int32_T A_sizes[2],
  const creal32_T B, creal32_T y_data[65535], int32_T y_sizes[2])
{
  int32_T loop_ub;
  int32_T i4;
  real32_T brm;
  real32_T bim;
  real32_T d;
  y_sizes[0] = 1;
  y_sizes[1] = A_sizes[1];
  loop_ub = A_sizes[0] * A_sizes[1] - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    if (B.im == 0.0F) {
      if (A_data[i4].im == 0.0F) {
        y_data[i4].re = A_data[i4].re / B.re;
        y_data[i4].im = 0.0F;
      } else if (A_data[i4].re == 0.0F) {
        y_data[i4].re = 0.0F;
        y_data[i4].im = A_data[i4].im / B.re;
      } else {
        y_data[i4].re = A_data[i4].re / B.re;
        y_data[i4].im = A_data[i4].im / B.re;
      }
    } else if (B.re == 0.0F) {
      if (A_data[i4].re == 0.0F) {
        y_data[i4].re = A_data[i4].im / B.im;
        y_data[i4].im = 0.0F;
      } else if (A_data[i4].im == 0.0F) {
        y_data[i4].re = 0.0F;
        y_data[i4].im = -(A_data[i4].re / B.im);
      } else {
        y_data[i4].re = A_data[i4].im / B.im;
        y_data[i4].im = -(A_data[i4].re / B.im);
      }
    } else {
      brm = (real32_T)fabs(B.re);
      bim = (real32_T)fabs(B.im);
      if (brm > bim) {
        bim = B.im / B.re;
        d = B.re + bim * B.im;
        y_data[i4].re = (A_data[i4].re + bim * A_data[i4].im) / d;
        y_data[i4].im = (A_data[i4].im - bim * A_data[i4].re) / d;
      } else if (bim == brm) {
        bim = B.re > 0.0F ? 0.5F : -0.5F;
        d = B.im > 0.0F ? 0.5F : -0.5F;
        y_data[i4].re = (A_data[i4].re * bim + A_data[i4].im * d) / brm;
        y_data[i4].im = (A_data[i4].im * bim - A_data[i4].re * d) / brm;
      } else {
        bim = B.re / B.im;
        d = B.im + bim * B.re;
        y_data[i4].re = (bim * A_data[i4].re + A_data[i4].im) / d;
        y_data[i4].im = (bim * A_data[i4].im - A_data[i4].re) / d;
      }
    }
  }
}

/*
 *
 */
static void diff(const boolean_T x_data[65535], const int32_T x_sizes[2], real_T
                 y_data[65534], int32_T y_sizes[2])
{
  int32_T tmp2;
  uint16_T ySize[2];
  int8_T y1_data[65534];
  int32_T ixLead;
  int32_T iyLead;
  int32_T work_data_idx_0;
  int32_T m;
  int32_T tmp1;
  if (x_sizes[1] == 0) {
    y_sizes[0] = 1;
    y_sizes[1] = 0;
  } else {
    tmp2 = x_sizes[1] - 1;
    tmp2 = tmp2 <= 1 ? tmp2 : 1;
    if (tmp2 < 1) {
      y_sizes[0] = 0;
      y_sizes[1] = 0;
    } else {
      for (tmp2 = 0; tmp2 < 2; tmp2++) {
        ySize[tmp2] = (uint16_T)x_sizes[tmp2];
      }

      ySize[1] = (uint16_T)(x_sizes[1] - 1);
      ixLead = 1;
      iyLead = 0;
      work_data_idx_0 = x_data[0];
      for (m = 2; m <= x_sizes[1]; m++) {
        tmp2 = work_data_idx_0;
        work_data_idx_0 = x_data[ixLead];
        tmp1 = x_data[ixLead] - tmp2;
        ixLead++;
        y1_data[iyLead] = (int8_T)tmp1;
        iyLead++;
      }

      y_sizes[0] = 1;
      y_sizes[1] = ySize[1];
      tmp1 = ySize[1] - 1;
      for (tmp2 = 0; tmp2 <= tmp1; tmp2++) {
        y_data[tmp2] = (real_T)y1_data[tmp2];
      }
    }
  }
}

/*
 *
 */
static real32_T eml_div(real32_T x, real_T y)
{
  return x / (real32_T)y;
}

/*
 *
 */
static void eml_fft(const real32_T x[8192], uint32_T n, creal32_T y_data[65535],
                    int32_T y_sizes[1])
{
  uint32_T sz[2];
  int32_T nd2;
  int32_T b_n;
  int32_T nRows;
  int32_T minval;
  int32_T ixDelta;
  int32_T nRowsD2;
  int32_T nRowsD4;
  real32_T e;
  real32_T costab1q_data[16385];
  int32_T k;
  static real32_T costab_data[32769];
  static real32_T sintab_data[32769];
  int32_T ix;
  uint32_T ju;
  int32_T i;
  uint32_T c_n;
  boolean_T tst;
  real32_T temp_im;
  int32_T iDelta;
  int32_T iDelta2;
  int32_T iheight;
  int32_T ihi;
  for (nd2 = 0; nd2 < 2; nd2++) {
    sz[nd2] = (uint32_T)(8192 + -8191 * nd2);
  }

  sz[0] = n;
  y_sizes[0] = (int32_T)sz[0];
  if (n > 8192U) {
    nd2 = y_sizes[0];
    b_n = nd2 - 1;
    for (nd2 = 0; nd2 <= b_n; nd2++) {
      y_data[nd2].re = 0.0F;
      y_data[nd2].im = 0.0F;
    }
  }

  nRows = (int32_T)n;
  if (8192 > nRows) {
    minval = nRows;
  } else {
    minval = 8192;
  }

  nd2 = 8193 - minval;
  ixDelta = 1 >= nd2 ? 1 : nd2;
  nRowsD2 = (nRows + (nRows < 0)) >> 1;
  nRowsD4 = (nRowsD2 + (nRowsD2 < 0)) >> 1;
  e = 6.28318548F / (real32_T)nRows;
  costab1q_data[0] = 1.0F;
  nd2 = (nRowsD4 + (nRowsD4 < 0)) >> 1;
  for (k = 1; k <= nd2; k++) {
    costab1q_data[k] = (real32_T)cos(e * (real32_T)k);
  }

  for (k = nd2 + 1; k <= nRowsD4 - 1; k++) {
    costab1q_data[k] = (real32_T)sin(e * (real32_T)(nRowsD4 - k));
  }

  costab1q_data[nRowsD4] = 0.0F;
  b_n = nRowsD4;
  nd2 = b_n << 1;
  costab_data[0] = 1.0F;
  sintab_data[0] = 0.0F;
  for (k = 1; k <= b_n; k++) {
    costab_data[k] = costab1q_data[k];
    sintab_data[k] = -costab1q_data[b_n - k];
  }

  for (k = b_n + 1; k <= nd2; k++) {
    costab_data[k] = -costab1q_data[nd2 - k];
    sintab_data[k] = -costab1q_data[k - b_n];
  }

  ix = 0;
  b_n = 0;
  while ((nRows > 0) && (b_n <= 0)) {
    ju = 0U;
    nd2 = 0;
    for (i = 1; i <= minval - 1; i++) {
      y_data[nd2].re = x[ix];
      y_data[nd2].im = 0.0F;
      c_n = n;
      tst = TRUE;
      while (tst) {
        c_n >>= 1U;
        ju ^= c_n;
        tst = ((int32_T)(ju & c_n) == 0);
      }

      nd2 = (int32_T)ju;
      ix++;
    }

    y_data[nd2].re = x[ix];
    y_data[nd2].im = 0.0F;
    ix += ixDelta;
    if (nRows > 1) {
      for (i = 0; i <= nRows - 2; i += 2) {
        e = y_data[i + 1].re;
        temp_im = y_data[i + 1].im;
        y_data[i + 1].re = y_data[i].re - y_data[i + 1].re;
        y_data[i + 1].im = y_data[i].im - y_data[i + 1].im;
        y_data[i].re += e;
        y_data[i].im += temp_im;
      }
    }

    iDelta = 2;
    iDelta2 = 4;
    k = nRowsD4;
    iheight = 1 + ((nRowsD4 - 1) << 2);
    while (k > 0) {
      for (i = 0; i < iheight; i += iDelta2) {
        nd2 = i + iDelta;
        e = y_data[nd2].re;
        temp_im = y_data[nd2].im;
        y_data[i + iDelta].re = y_data[i].re - y_data[nd2].re;
        y_data[i + iDelta].im = y_data[i].im - y_data[nd2].im;
        y_data[i].re += e;
        y_data[i].im += temp_im;
      }

      nd2 = 1;
      for (b_n = k; b_n < nRowsD2; b_n += k) {
        i = nd2;
        ihi = nd2 + iheight;
        while (i < ihi) {
          e = costab_data[b_n] * y_data[i + iDelta].re - sintab_data[b_n] *
            y_data[i + iDelta].im;
          temp_im = costab_data[b_n] * y_data[i + iDelta].im + sintab_data[b_n] *
            y_data[i + iDelta].re;
          y_data[i + iDelta].re = y_data[i].re - e;
          y_data[i + iDelta].im = y_data[i].im - temp_im;
          y_data[i].re += e;
          y_data[i].im += temp_im;
          i += iDelta2;
        }

        nd2++;
      }

      k >>= 1;
      iDelta = iDelta2;
      iDelta2 <<= 1;
      iheight -= iDelta;
    }

    b_n = nRows;
  }
}

/*
 *
 */
static void eml_matlab_zlarf(int32_T m, int32_T n, int32_T iv0, real_T tau,
  real_T C[21], int32_T ic0, real_T work[3])
{
  int32_T lastv;
  int32_T i;
  int32_T lastc;
  boolean_T exitg2;
  int32_T colbottom;
  int32_T exitg1;
  int32_T iy;
  int32_T i5;
  int32_T ix;
  real_T c;
  int32_T ia;
  if (tau != 0.0) {
    lastv = m;
    i = iv0 + m;
    while ((lastv > 0) && (C[i - 2] == 0.0)) {
      lastv--;
      i--;
    }

    lastc = n;
    exitg2 = 0U;
    while ((exitg2 == 0U) && (lastc > 0)) {
      i = ic0 + (lastc - 1) * 7;
      colbottom = (i + lastv) - 1;
      do {
        exitg1 = 0U;
        if (i <= colbottom) {
          if (C[i - 1] != 0.0) {
            exitg1 = 1U;
          } else {
            i++;
          }
        } else {
          lastc--;
          exitg1 = 2U;
        }
      } while (exitg1 == 0U);

      if (exitg1 == 1U) {
        exitg2 = 1U;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc == 0) {
    } else {
      i = lastc - 1;
      for (iy = 1; iy <= i + 1; iy++) {
        work[iy - 1] = 0.0;
      }

      iy = 0;
      i5 = ic0 + 7 * i;
      for (i = ic0; i <= i5; i += 7) {
        ix = iv0;
        c = 0.0;
        colbottom = i + lastv;
        for (ia = i; ia <= colbottom - 1; ia++) {
          c += C[ia - 1] * C[ix - 1];
          ix++;
        }

        work[iy] += c;
        iy++;
      }
    }

    if (-tau == 0.0) {
    } else {
      i = ic0 - 1;
      colbottom = 0;
      for (ia = 1; ia <= lastc; ia++) {
        if (work[colbottom] != 0.0) {
          c = work[colbottom] * -tau;
          ix = iv0;
          i5 = lastv + i;
          for (iy = i; iy + 1 <= i5; iy++) {
            C[iy] += C[ix - 1] * c;
            ix++;
          }
        }

        colbottom++;
        i += 7;
      }
    }
  }
}

/*
 *
 */
static void eml_qrsolve(const real_T A[21], real32_T B[7], boolean_T
  ignoreRankDeficiency, real32_T Y[3], real_T *rankR)
{
  real_T b_A[21];
  real_T tau[3];
  int8_T jpvt[3];
  real_T work[3];
  int32_T nmip1;
  real_T vn1[3];
  real_T vn2[3];
  int32_T k;
  int32_T pvt;
  real_T atmp;
  real_T tol;
  real_T xnorm;
  real_T a;
  int32_T i;
  int32_T i_i;
  int32_T ix;
  real32_T wj;
  memcpy((void *)&b_A[0], (void *)&A[0], 21U * sizeof(real_T));
  for (nmip1 = 0; nmip1 < 3; nmip1++) {
    jpvt[nmip1] = (int8_T)(1 + nmip1);
    work[nmip1] = 0.0;
  }

  k = 1;
  for (pvt = 0; pvt < 3; pvt++) {
    atmp = 0.0;
    tol = 2.2250738585072014E-308;
    for (nmip1 = k; nmip1 <= k + 6; nmip1++) {
      xnorm = fabs(A[nmip1 - 1]);
      if (xnorm > tol) {
        a = tol / xnorm;
        atmp = 1.0 + atmp * a * a;
        tol = xnorm;
      } else {
        a = xnorm / tol;
        atmp += a * a;
      }
    }

    atmp = tol * sqrt(atmp);
    vn1[pvt] = atmp;
    vn2[pvt] = vn1[pvt];
    k += 7;
  }

  for (i = 0; i < 3; i++) {
    i_i = i + i * 7;
    nmip1 = 3 - i;
    pvt = 0;
    if (nmip1 > 1) {
      ix = i;
      tol = fabs(vn1[i]);
      for (k = 2; k <= nmip1; k++) {
        ix++;
        xnorm = fabs(vn1[ix]);
        if (xnorm > tol) {
          pvt = k - 1;
          tol = xnorm;
        }
      }
    }

    pvt += i;
    if (pvt + 1 != i + 1) {
      ix = 7 * pvt;
      nmip1 = 7 * i;
      for (k = 0; k < 7; k++) {
        tol = b_A[ix];
        b_A[ix] = b_A[nmip1];
        b_A[nmip1] = tol;
        ix++;
        nmip1++;
      }

      nmip1 = (int32_T)jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = (int8_T)nmip1;
      vn1[pvt] = vn1[i];
      vn2[pvt] = vn2[i];
    }

    ix = i_i + 2;
    atmp = b_A[i_i];
    tol = 0.0;
    xnorm = eml_xnrm2(6 - i, b_A, ix);
    if (xnorm != 0.0) {
      a = fabs(b_A[i_i]);
      if (a < xnorm) {
        a /= xnorm;
        xnorm *= sqrt(a * a + 1.0);
      } else if (a > xnorm) {
        tol = xnorm / a;
        xnorm = sqrt(tol * tol + 1.0) * a;
      } else if (rtIsNaN(xnorm)) {
      } else {
        xnorm = a * 1.4142135623730951;
      }

      if (b_A[i_i] >= 0.0) {
        xnorm = -xnorm;
      }

      if (fabs(xnorm) < 1.0020841800044864E-292) {
        pvt = 0;
        do {
          pvt++;
          nmip1 = (ix - i) + 5;
          for (k = ix; k <= nmip1; k++) {
            b_A[k - 1] *= 9.9792015476736E+291;
          }

          xnorm *= 9.9792015476736E+291;
          atmp *= 9.9792015476736E+291;
        } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

        xnorm = eml_xnrm2(6 - i, b_A, ix);
        a = fabs(atmp);
        if (a < xnorm) {
          a /= xnorm;
          xnorm *= sqrt(a * a + 1.0);
        } else if (a > xnorm) {
          tol = xnorm / a;
          xnorm = sqrt(tol * tol + 1.0) * a;
        } else if (rtIsNaN(xnorm)) {
        } else {
          xnorm = a * 1.4142135623730951;
        }

        if (atmp >= 0.0) {
          xnorm = -xnorm;
        }

        tol = (xnorm - atmp) / xnorm;
        atmp = 1.0 / (atmp - xnorm);
        nmip1 = (ix - i) + 5;
        while (ix <= nmip1) {
          b_A[ix - 1] *= atmp;
          ix++;
        }

        for (k = 1; k <= pvt; k++) {
          xnorm *= 1.0020841800044864E-292;
        }

        atmp = xnorm;
      } else {
        tol = (xnorm - b_A[i_i]) / xnorm;
        atmp = 1.0 / (b_A[i_i] - xnorm);
        nmip1 = (ix - i) + 5;
        while (ix <= nmip1) {
          b_A[ix - 1] *= atmp;
          ix++;
        }

        atmp = xnorm;
      }
    }

    tau[i] = tol;
    b_A[i_i] = atmp;
    if (i + 1 < 3) {
      atmp = b_A[i_i];
      b_A[i_i] = 1.0;
      eml_matlab_zlarf(7 - i, 2 - i, i_i + 1, tau[i], b_A, (i + (i + 1) * 7) + 1,
                       work);
      b_A[i_i] = atmp;
    }

    for (pvt = i + 1; pvt + 1 < 4; pvt++) {
      if (vn1[pvt] != 0.0) {
        xnorm = fabs(b_A[i + 7 * pvt]) / vn1[pvt];
        atmp = xnorm * xnorm;
        xnorm = 1.0 - xnorm * xnorm;
        if (1.0 - atmp < 0.0) {
          xnorm = 0.0;
        }

        tol = vn1[pvt] / vn2[pvt];
        if (xnorm * (tol * tol) <= 1.4901161193847656E-8) {
          ix = (i + 7 * pvt) + 2;
          atmp = 0.0;
          tol = 2.2250738585072014E-308;
          nmip1 = (ix - i) + 5;
          while (ix <= nmip1) {
            xnorm = fabs(b_A[ix - 1]);
            if (xnorm > tol) {
              a = tol / xnorm;
              atmp = 1.0 + atmp * a * a;
              tol = xnorm;
            } else {
              a = xnorm / tol;
              atmp += a * a;
            }

            ix++;
          }

          atmp = tol * sqrt(atmp);
          vn1[pvt] = atmp;
          vn2[pvt] = vn1[pvt];
        } else {
          vn1[pvt] *= sqrt(xnorm);
        }
      }
    }
  }

  tol = 7.0 * fabs(b_A[0]) * 2.2204460492503131E-16;
  *rankR = 0.0;
  k = 0;
  while ((k < 3) && (!(fabs(b_A[k + 7 * k]) <= tol))) {
    (*rankR)++;
    k++;
  }

  for (i = 0; i < 3; i++) {
    Y[i] = 0.0F;
  }

  for (pvt = 0; pvt < 3; pvt++) {
    if (tau[pvt] != 0.0) {
      wj = B[pvt];
      for (i = 0; i <= 5 - pvt; i++) {
        nmip1 = (pvt + i) + 1;
        wj += (real32_T)b_A[nmip1 + 7 * pvt] * B[nmip1];
      }

      wj *= (real32_T)tau[pvt];
      if (wj != 0.0F) {
        B[pvt] -= wj;
        for (i = 0; i <= 5 - pvt; i++) {
          nmip1 = (pvt + i) + 1;
          B[nmip1] -= (real32_T)b_A[nmip1 + 7 * pvt] * wj;
        }
      }
    }
  }

  for (i = 0; i < 3; i++) {
    Y[jpvt[i] - 1] = B[i];
  }

  for (pvt = 0; pvt < 3; pvt++) {
    Y[jpvt[2 - pvt] - 1] = eml_div(Y[jpvt[2 - pvt] - 1], b_A[(7 * (2 - pvt) -
      pvt) + 2]);
    for (i = 0; i <= 1 - pvt; i++) {
      Y[jpvt[i] - 1] -= Y[jpvt[2 - pvt] - 1] * (real32_T)b_A[i + 7 * (2 - pvt)];
    }
  }
}

/*
 *
 */
static real32_T eml_scalar_abs(const creal32_T x)
{
  real32_T y;
  real32_T a;
  a = (real32_T)fabs(x.re);
  y = (real32_T)fabs(x.im);
  if (a < y) {
    a /= y;
    y *= (real32_T)sqrt(a * a + 1.0F);
  } else if (a > y) {
    y /= a;
    y = (real32_T)sqrt(y * y + 1.0F) * a;
  } else if (rtIsNaNF(y)) {
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

/*
 *
 */
static void eml_scalexp_alloc(const real32_T varargin_1_data[65535], const
  int32_T varargin_1_sizes[2], real32_T z_data[65535], int32_T z_sizes[2])
{
  uint16_T uv1[2];
  int32_T i2;
  for (i2 = 0; i2 < 2; i2++) {
    uv1[i2] = (uint16_T)varargin_1_sizes[i2];
  }

  z_sizes[0] = 1;
  z_sizes[1] = uv1[1];
}

/*
 *
 */
static real_T eml_xnrm2(int32_T n, const real_T x[21], int32_T ix0)
{
  real_T y;
  real_T scale;
  int32_T kend;
  int32_T k;
  real_T absxk;
  real_T t;
  y = 0.0;
  if (n < 1) {
  } else if (n == 1) {
    y = fabs(x[ix0 - 1]);
  } else {
    scale = 2.2250738585072014E-308;
    kend = (ix0 + n) - 1;
    for (k = ix0; k <= kend; k++) {
      absxk = fabs(x[k - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = 1.0 + y * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }
    }

    y = scale * sqrt(y);
  }

  return y;
}

/*
 *
 */
static void fft(const real32_T x[8192], uint16_T varargin_1, creal32_T y_data
                [65535], int32_T y_sizes[2])
{
  int32_T y1_sizes;
  static creal32_T y1_data[65535];
  int32_T i1;
  eml_fft(x, (uint32_T)varargin_1, y1_data, *(int32_T (*)[1])&y1_sizes);
  y_sizes[0] = 1;
  y_sizes[1] = y1_sizes;
  y1_sizes--;
  for (i1 = 0; i1 <= y1_sizes; i1++) {
    y_data[i1] = y1_data[i1];
  }
}

/*
 *
 */
static void ifft(const real32_T x_data[65535], const int32_T x_sizes[2],
                 creal32_T y_data[65535], int32_T y_sizes[2])
{
  static real32_T b_x_data[65535];
  int32_T b_x_sizes;
  int32_T y1_sizes;
  int32_T i3;
  static creal32_T y1_data[65535];
  b_x_sizes = x_sizes[1];
  y1_sizes = x_sizes[1] - 1;
  for (i3 = 0; i3 <= y1_sizes; i3++) {
    b_x_data[i3] = x_data[i3];
  }

  b_eml_fft(b_x_data, *(int32_T (*)[1])&b_x_sizes, (uint32_T)x_sizes[1], y1_data,
            *(int32_T (*)[1])&y1_sizes);
  y_sizes[0] = 1;
  y_sizes[1] = y1_sizes;
  y1_sizes--;
  for (i3 = 0; i3 <= y1_sizes; i3++) {
    y_data[i3] = y1_data[i3];
  }
}

/*
 *
 */
static real32_T mrdivide(real32_T A, real_T B)
{
  return A / (real32_T)B;
}

/*
 *
 */
static void polyfit(const real_T x[7], const real32_T y[7], real32_T p[3])
{
  real_T V[21];
  real32_T b_y[7];
  int32_T k;
  real_T rr;
  real32_T p1[3];
  for (k = 0; k < 7; k++) {
    V[14 + k] = 1.0;
    V[7 + k] = x[k];
    V[k] = x[k] * V[7 + k];
    b_y[k] = y[k];
  }

  eml_qrsolve(V, b_y, TRUE, p1, &rr);
  for (k = 0; k < 3; k++) {
    p[k] = p1[k];
  }
}

/*
 *
 */
static void power(const real32_T a_data[65535], const int32_T a_sizes[2],
                  real32_T y_data[65535], int32_T y_sizes[2])
{
  int32_T k;
  eml_scalexp_alloc(a_data, a_sizes, y_data, y_sizes);
  for (k = 0; k <= y_sizes[1] - 1; k++) {
    y_data[k] = rt_powf_snf(a_data[k], 2.0F);
  }
}

static real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T d0;
  real_T d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = rtNaN;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

static real32_T rt_powf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  real32_T f0;
  real32_T f1;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = ((real32_T)rtNaN);
  } else {
    f0 = (real32_T)fabs(u0);
    f1 = (real32_T)fabs(u1);
    if (rtIsInfF(u1)) {
      if (f0 == 1.0F) {
        y = ((real32_T)rtNaN);
      } else if (f0 > 1.0F) {
        if (u1 > 0.0F) {
          y = ((real32_T)rtInf);
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = ((real32_T)rtInf);
      }
    } else if (f1 == 0.0F) {
      y = 1.0F;
    } else if (f1 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = (real32_T)sqrt(u0);
    } else if ((u0 < 0.0F) && (u1 > (real32_T)floor(u1))) {
      y = ((real32_T)rtNaN);
    } else {
      y = (real32_T)pow(u0, u1);
    }
  }

  return y;
}

/*
 * function [noteFreq, noteError, noteName, noteOctave] = getNote(f)
 */
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

  /* 'getNote:3' if isempty(notes) */
  /* 'getNote:6' [~,n] = min(abs(notes-f)); */
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

  /* 'getNote:7' noteFreq = notes(n); */
  *noteFreq = notes[itmp];

  /* 'getNote:8' noteError = 100*log2(f/noteFreq)*12; */
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

  /* 'getNote:9' noteOctave = fix((n-1)/12)+1; */
  b_y = ((real_T)(itmp + 1) - 1.0) / 12.0;
  if (b_y > 0.0) {
    ixstart = (int32_T)floor(b_y);
  } else {
    ixstart = 0;
  }

  *noteOctave = (real_T)ixstart + 1.0;

  /* 'getNote:11' switch mod(n-1,12)+1 */
  switch ((itmp - (int32_T)floor(((real_T)(itmp + 1) - 1.0) / 12.0) * 12) + 1) {
   case 1:
    /* 'getNote:12' case 1 */
    /* 'getNote:13' noteName = char('A'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'A';
    break;

   case 2:
    /* 'getNote:14' case 2 */
    /* 'getNote:15' noteName = char('Bb'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 2;
    for (ixstart = 0; ixstart < 2; ixstart++) {
      noteName_data[ixstart] = cv0[ixstart];
    }
    break;

   case 3:
    /* 'getNote:16' case 3 */
    /* 'getNote:17' noteName = char('B'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'B';
    break;

   case 4:
    /* 'getNote:18' case 4 */
    /* 'getNote:19' noteName = char('C'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'C';
    break;

   case 5:
    /* 'getNote:20' case 5 */
    /* 'getNote:21' noteName = char('C#'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 2;
    for (ixstart = 0; ixstart < 2; ixstart++) {
      noteName_data[ixstart] = cv1[ixstart];
    }
    break;

   case 6:
    /* 'getNote:22' case 6 */
    /* 'getNote:23' noteName = char('D'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'D';
    break;

   case 7:
    /* 'getNote:24' case 7 */
    /* 'getNote:25' noteName = char('Eb'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 2;
    for (ixstart = 0; ixstart < 2; ixstart++) {
      noteName_data[ixstart] = cv2[ixstart];
    }
    break;

   case 8:
    /* 'getNote:26' case 8 */
    /* 'getNote:27' noteName = char('E'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'E';
    break;

   case 9:
    /* 'getNote:28' case 9 */
    /* 'getNote:29' noteName = char('F'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'F';
    break;

   case 10:
    /* 'getNote:30' case 10 */
    /* 'getNote:31' noteName = char('F#'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 2;
    for (ixstart = 0; ixstart < 2; ixstart++) {
      noteName_data[ixstart] = cv3[ixstart];
    }
    break;

   case 11:
    /* 'getNote:32' case 11 */
    /* 'getNote:33' noteName = char('G'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 1;
    noteName_data[0] = 'G';
    break;

   case 12:
    /* 'getNote:34' case 12 */
    /* 'getNote:35' noteName = char('Ab'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 2;
    for (ixstart = 0; ixstart < 2; ixstart++) {
      noteName_data[ixstart] = cv4[ixstart];
    }
    break;

   default:
    /* 'getNote:36' otherwise */
    /* 'getNote:37' noteName = char('NaN'); */
    noteName_sizes[0] = 1;
    noteName_sizes[1] = 3;
    for (ixstart = 0; ixstart < 3; ixstart++) {
      noteName_data[ixstart] = cv5[ixstart];
    }
    break;
  }
}

void getNote_initialize(void)
{
  int32_T k;
  static const real_T dv0[145] = { -4.0, -3.9166666666666665,
    -3.8333333333333335, -3.75, -3.6666666666666665, -3.5833333333333335, -3.5,
    -3.4166666666666665, -3.3333333333333335, -3.25, -3.1666666666666665,
    -3.0833333333333335, -3.0, -2.9166666666666665, -2.8333333333333335, -2.75,
    -2.6666666666666665, -2.5833333333333335, -2.5, -2.4166666666666665,
    -2.3333333333333335, -2.25, -2.1666666666666665, -2.0833333333333335, -2.0,
    -1.9166666666666667, -1.8333333333333333, -1.75, -1.6666666666666667,
    -1.5833333333333333, -1.5, -1.4166666666666667, -1.3333333333333333, -1.25,
    -1.1666666666666667, -1.0833333333333333, -1.0, -0.91666666666666663,
    -0.83333333333333337, -0.75, -0.66666666666666663, -0.58333333333333337,
    -0.5, -0.41666666666666669, -0.33333333333333331, -0.25,
    -0.16666666666666666, -0.083333333333333329, 0.0, 0.083333333333333329,
    0.16666666666666666, 0.25, 0.33333333333333331, 0.41666666666666669, 0.5,
    0.58333333333333337, 0.66666666666666663, 0.75, 0.83333333333333337,
    0.91666666666666663, 1.0, 1.0833333333333333, 1.1666666666666667, 1.25,
    1.3333333333333333, 1.4166666666666667, 1.5, 1.5833333333333333,
    1.6666666666666667, 1.75, 1.8333333333333333, 1.9166666666666667, 2.0,
    2.0833333333333335, 2.1666666666666665, 2.25, 2.3333333333333335,
    2.4166666666666665, 2.5, 2.5833333333333335, 2.6666666666666665, 2.75,
    2.8333333333333335, 2.9166666666666665, 3.0, 3.0833333333333335,
    3.1666666666666665, 3.25, 3.3333333333333335, 3.4166666666666665, 3.5,
    3.5833333333333335, 3.6666666666666665, 3.75, 3.8333333333333335,
    3.9166666666666665, 4.0, 4.083333333333333, 4.166666666666667, 4.25,
    4.333333333333333, 4.416666666666667, 4.5, 4.583333333333333,
    4.666666666666667, 4.75, 4.833333333333333, 4.916666666666667, 5.0,
    5.083333333333333, 5.166666666666667, 5.25, 5.333333333333333,
    5.416666666666667, 5.5, 5.583333333333333, 5.666666666666667, 5.75,
    5.833333333333333, 5.916666666666667, 6.0, 6.083333333333333,
    6.166666666666667, 6.25, 6.333333333333333, 6.416666666666667, 6.5,
    6.583333333333333, 6.666666666666667, 6.75, 6.833333333333333,
    6.916666666666667, 7.0, 7.083333333333333, 7.166666666666667, 7.25,
    7.333333333333333, 7.416666666666667, 7.5, 7.583333333333333,
    7.666666666666667, 7.75, 7.833333333333333, 7.916666666666667, 8.0 };

  rt_InitInfAndNaN(8U);
  for (k = 0; k < 145; k++) {
    notes[k] = rt_powd_snf(2.0, dv0[k]);
    notes[k] *= 110.0;
  }
}

void getNote_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * function [F, snr, w] = measureFreqXcorr(s, analizeTime, Fs)
 */
void measureFreqXcorr(const int32_T s[8192], uint16_T analizeTime, real32_T Fs,
                      real32_T *F, real32_T *snr, creal32_T w_data[65535],
                      int32_T w_sizes[2])
{
  real32_T b_s[8192];
  int32_T i0;
  int32_T sh_sizes[2];
  static real32_T sh_data[65535];
  static real32_T b_sh_data[65535];
  int32_T shd_sizes[2];
  int32_T k;
  static creal32_T c_sh_data[65535];
  static creal32_T d_sh_data[65535];
  int32_T b_sh_sizes[2];
  static boolean_T e_sh_data[65535];
  int32_T c_sh_sizes[2];
  static real_T shd_data[65534];
  static boolean_T poses_pos_data[65534];
  boolean_T poses_neg_data[65534];
  int32_T nx;
  int32_T idx;
  int32_T ii_data[1];
  int32_T ixstart;
  boolean_T exitg4;
  int32_T b_ii_data[1];
  int32_T idx_start_sizes;
  int32_T idx_start_data[1];
  static int32_T c_ii_data[65534];
  boolean_T exitg3;
  boolean_T guard1 = FALSE;
  static int32_T d_ii_data[65534];
  static int32_T idx_ends_data[65534];
  boolean_T x_data[1];
  boolean_T exitg2;
  static int32_T tmp_data[65533];
  static int32_T b_tmp_data[65533];
  static int32_T c_tmp_data[65535];
  static int32_T d_tmp_data[65535];
  real32_T mtmp;
  boolean_T exitg1;
  real32_T sh[7];
  real_T b_idx;
  real_T c_idx[7];
  real32_T PP[3];
  real32_T PZ;

  /* 'measureFreqXcorr:2' F = single(0); */
  *F = 0.0F;

  /* 'measureFreqXcorr:3' snr = single(0); */
  *snr = 0.0F;

  /* 'measureFreqXcorr:5' w = fft(single(s), analizeTime); */
  for (i0 = 0; i0 < 8192; i0++) {
    b_s[i0] = (real32_T)s[i0];
  }

  fft(b_s, analizeTime, w_data, w_sizes);

  /* 'measureFreqXcorr:6' sh = ifft(abs(w).^2); */
  b_abs(w_data, w_sizes, sh_data, sh_sizes);
  shd_sizes[0] = 1;
  shd_sizes[1] = sh_sizes[1];
  k = sh_sizes[0] * sh_sizes[1] - 1;
  for (i0 = 0; i0 <= k; i0++) {
    b_sh_data[i0] = sh_data[i0];
  }

  power(b_sh_data, shd_sizes, sh_data, sh_sizes);
  ifft(sh_data, sh_sizes, c_sh_data, shd_sizes);

  /* 'measureFreqXcorr:7' sh = real(sh/sh(1)); */
  b_sh_sizes[0] = 1;
  b_sh_sizes[1] = shd_sizes[1];
  k = shd_sizes[0] * shd_sizes[1] - 1;
  for (i0 = 0; i0 <= k; i0++) {
    d_sh_data[i0] = c_sh_data[i0];
  }

  c_mrdivide(d_sh_data, b_sh_sizes, c_sh_data[0], c_sh_data, shd_sizes);
  sh_sizes[0] = 1;
  sh_sizes[1] = shd_sizes[1];
  k = shd_sizes[0] * shd_sizes[1] - 1;
  for (i0 = 0; i0 <= k; i0++) {
    sh_data[i0] = c_sh_data[i0].re;
  }

  /* 'measureFreqXcorr:8' shi = sh>0.5; */
  /* 'measureFreqXcorr:9' shd = diff(shi); */
  c_sh_sizes[0] = 1;
  c_sh_sizes[1] = sh_sizes[1];
  k = sh_sizes[1] - 1;
  for (i0 = 0; i0 <= k; i0++) {
    e_sh_data[i0] = (sh_data[i0] > 0.5F);
  }

  diff(e_sh_data, c_sh_sizes, shd_data, shd_sizes);

  /* 'measureFreqXcorr:10' poses_pos = shd>0; */
  k = shd_sizes[0] * shd_sizes[1] - 1;
  for (i0 = 0; i0 <= k; i0++) {
    poses_pos_data[i0] = (shd_data[i0] > 0.0);
  }

  /* 'measureFreqXcorr:11' poses_neg = shd<0; */
  k = shd_sizes[0] * shd_sizes[1] - 1;
  for (i0 = 0; i0 <= k; i0++) {
    poses_neg_data[i0] = (shd_data[i0] < 0.0);
  }

  /* 'measureFreqXcorr:12' idx_start = find(poses_pos, 1, 'first'); */
  nx = shd_sizes[0] * shd_sizes[1];
  k = 1 <= nx ? 1 : nx;
  idx = 0;
  ixstart = 1;
  exitg4 = 0U;
  while ((exitg4 == 0U) && (ixstart <= nx)) {
    if (poses_pos_data[ixstart - 1]) {
      idx = 1;
      ii_data[0] = ixstart;
      exitg4 = 1U;
    } else {
      ixstart++;
    }
  }

  if (k == 1) {
    if (idx == 0) {
      k = 0;
    }
  } else {
    if (1 > idx) {
      ixstart = -1;
    } else {
      ixstart = 0;
    }

    i0 = 0;
    while (i0 <= ixstart) {
      b_ii_data[0] = ii_data[0];
      i0 = 1;
    }

    k = ixstart + 1;
    i0 = 0;
    while (i0 <= ixstart) {
      ii_data[0] = b_ii_data[0];
      i0 = 1;
    }
  }

  idx_start_sizes = k;
  k--;
  for (i0 = 0; i0 <= k; i0++) {
    idx_start_data[i0] = ii_data[i0];
  }

  /* 'measureFreqXcorr:13' idx_ends   = find(poses_neg); */
  nx = shd_sizes[0] * shd_sizes[1];
  idx = 0;
  ixstart = 1;
  exitg3 = 0U;
  while ((exitg3 == 0U) && (ixstart <= nx)) {
    guard1 = FALSE;
    if (poses_neg_data[ixstart - 1]) {
      idx++;
      c_ii_data[idx - 1] = ixstart;
      if (idx >= nx) {
        exitg3 = 1U;
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

  if (nx == 1) {
    if (idx == 0) {
      nx = 0;
    }
  } else {
    if (1 > idx) {
      idx = 0;
    }

    k = idx - 1;
    for (i0 = 0; i0 <= k; i0++) {
      d_ii_data[i0] = c_ii_data[i0];
    }

    nx = idx;
    k = idx - 1;
    for (i0 = 0; i0 <= k; i0++) {
      c_ii_data[i0] = d_ii_data[i0];
    }
  }

  k = nx - 1;
  for (i0 = 0; i0 <= k; i0++) {
    idx_ends_data[i0] = c_ii_data[i0];
  }

  /* 'measureFreqXcorr:14' idx_end = idx_ends(find(idx_ends>idx_start,1,'first')); */
  k = nx - 1;
  for (i0 = 0; i0 <= k; i0++) {
    x_data[i0] = (idx_ends_data[i0] > idx_start_data[i0]);
  }

  k = 1 <= nx ? 1 : nx;
  idx = 0;
  ixstart = 1;
  exitg2 = 0U;
  while ((exitg2 == 0U) && (ixstart <= nx)) {
    if (x_data[0]) {
      idx = 1;
      exitg2 = 1U;
    } else {
      ixstart = 2;
    }
  }

  if (k == 1) {
    if (idx == 0) {
      k = 0;
    }
  } else {
    if (1 > idx) {
      ixstart = -1;
    } else {
      ixstart = 0;
    }

    k = ixstart + 1;
  }

  /* 'measureFreqXcorr:15' if isempty(idx_end) || isempty(idx_start) */
  if ((k == 0) || (idx_start_sizes == 0)) {
  } else {
    /* 'measureFreqXcorr:18' sh (1:(idx_start(1)-1)) = 0; */
    if (1.0 > (real_T)idx_start_data[0] - 1.0) {
      i0 = -1;
    } else {
      i0 = idx_start_data[0] - 2;
    }

    for (ixstart = 0; ixstart <= i0; ixstart++) {
      tmp_data[ixstart] = 1 + ixstart;
    }

    k = i0;
    for (ixstart = 0; ixstart <= k; ixstart++) {
      b_tmp_data[ixstart] = tmp_data[ixstart];
    }

    k = i0;
    for (i0 = 0; i0 <= k; i0++) {
      sh_data[b_tmp_data[i0] - 1] = 0.0F;
    }

    /* 'measureFreqXcorr:19' sh (idx_end(1)+1:analizeTime) = 0; */
    if (idx_ends_data[0] + 1 > analizeTime) {
      i0 = 0;
      ixstart = 0;
    } else {
      i0 = idx_ends_data[0];
      ixstart = analizeTime;
    }

    nx = ixstart - i0;
    k = (ixstart - i0) - 1;
    for (ixstart = 0; ixstart <= k; ixstart++) {
      c_tmp_data[ixstart] = (i0 + ixstart) + 1;
    }

    k = nx - 1;
    for (i0 = 0; i0 <= k; i0++) {
      d_tmp_data[i0] = c_tmp_data[i0];
    }

    k = nx - 1;
    for (i0 = 0; i0 <= k; i0++) {
      sh_data[d_tmp_data[i0] - 1] = 0.0F;
    }

    /* 'measureFreqXcorr:20' [M,p] = max(sh); */
    ixstart = 1;
    mtmp = sh_data[0];
    k = 1;
    if (sh_sizes[1] > 1) {
      if (rtIsNaNF(sh_data[0])) {
        nx = 2;
        exitg1 = 0U;
        while ((exitg1 == 0U) && (nx <= sh_sizes[1])) {
          ixstart = nx;
          if (!rtIsNaNF(sh_data[nx - 1])) {
            mtmp = sh_data[nx - 1];
            exitg1 = 1U;
          } else {
            nx++;
          }
        }
      }

      if (ixstart < sh_sizes[1]) {
        while (ixstart + 1 <= sh_sizes[1]) {
          if (sh_data[ixstart] > mtmp) {
            mtmp = sh_data[ixstart];
            k = ixstart + 1;
          }

          ixstart++;
        }
      }
    }

    /* 'measureFreqXcorr:22' if ~isempty(p) */
    /* 'measureFreqXcorr:23' if p < 4 */
    if (k < 4) {
      /* 'measureFreqXcorr:24' p = 4; */
      k = 4;
    } else {
      if (k > (uint16_T)((uint32_T)analizeTime - 3U)) {
        /* 'measureFreqXcorr:25' elseif p > analizeTime-3 */
        /* 'measureFreqXcorr:26' p = double(analizeTime)-3; */
        k = analizeTime - 3;
      }
    }

    /* 'measureFreqXcorr:29' idx = p+(-3:3); */
    /* 'measureFreqXcorr:31' PP = polyfit(idx, sh(idx), 2); */
    for (i0 = 0; i0 < 7; i0++) {
      b_idx = (real_T)k + (-3.0 + (real_T)i0);
      sh[i0] = sh_data[(int32_T)b_idx - 1];
      c_idx[i0] = b_idx;
    }

    polyfit(c_idx, sh, PP);

    /* 'measureFreqXcorr:32' PZ = -PP(2)/2/PP(1); */
    PZ = b_mrdivide(mrdivide(-PP[1], 2.0), PP[0]);

    /* 'measureFreqXcorr:34' if (PZ>0) */
    if (PZ > 0.0F) {
      /* 'measureFreqXcorr:35' F = single(real(Fs/(PZ-1))); */
      *F = b_mrdivide(Fs, PZ - 1.0F);
    } else {
      /* 'measureFreqXcorr:36' else */
      /* 'measureFreqXcorr:37' F = single(0*Fs); */
      *F = 0.0F * Fs;
    }

    /* 'measureFreqXcorr:39' snr = abs(M); */
    *snr = (real32_T)fabs(mtmp);
  }
}

/* End of code generation (getNote.cpp) */
