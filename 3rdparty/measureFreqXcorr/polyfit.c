/*
 * polyfit.c
 *
 * Code generation for function 'polyfit'
 *
 * C source code generated on: Fri Jan 27 01:45:06 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "measureFreqXcorr.h"
#include "polyfit.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void eml_matlab_zlarf(int32_T m, int32_T n, int32_T iv0, real_T tau,
  real_T C[21], int32_T ic0, real_T work[3]);
static void eml_qrsolve(const real_T A[21], creal_T B[7], boolean_T
  ignoreRankDeficiency, creal_T Y[3], real_T *rankR);
static real_T eml_xnrm2(int32_T n, const real_T x[21], int32_T ix0);

/* Function Definitions */
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
  int32_T i1;
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
      i1 = ic0 + 7 * i;
      for (i = ic0; i <= i1; i += 7) {
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
          i1 = lastv + i;
          for (iy = i; iy + 1 <= i1; iy++) {
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

static void eml_qrsolve(const real_T A[21], creal_T B[7], boolean_T
  ignoreRankDeficiency, creal_T Y[3], real_T *rankR)
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
  real_T y;
  real_T tol;
  real_T wj_im;
  real_T t;
  int32_T i;
  int32_T i_i;
  int32_T ix;
  memcpy((void *)&b_A[0], (void *)&A[0], 21U * sizeof(real_T));
  for (nmip1 = 0; nmip1 < 3; nmip1++) {
    jpvt[nmip1] = (int8_T)(1 + nmip1);
    work[nmip1] = 0.0;
  }

  k = 1;
  for (pvt = 0; pvt < 3; pvt++) {
    y = 0.0;
    tol = 2.2250738585072014E-308;
    for (nmip1 = k; nmip1 <= k + 6; nmip1++) {
      wj_im = fabs(A[nmip1 - 1]);
      if (wj_im > tol) {
        t = tol / wj_im;
        y = 1.0 + y * t * t;
        tol = wj_im;
      } else {
        t = wj_im / tol;
        y += t * t;
      }
    }

    y = tol * sqrt(y);
    vn1[pvt] = y;
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
        wj_im = fabs(vn1[ix]);
        if (wj_im > tol) {
          pvt = k - 1;
          tol = wj_im;
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
    t = b_A[i_i];
    tol = 0.0;
    wj_im = eml_xnrm2(6 - i, b_A, ix);
    if (wj_im != 0.0) {
      tol = fabs(b_A[i_i]);
      wj_im = fabs(wj_im);
      if (tol < wj_im) {
        tol /= wj_im;
        wj_im *= sqrt(tol * tol + 1.0);
      } else if (tol > wj_im) {
        wj_im /= tol;
        wj_im = sqrt(wj_im * wj_im + 1.0) * tol;
      } else if (rtIsNaN(wj_im)) {
      } else {
        wj_im = tol * 1.4142135623730951;
      }

      if (b_A[i_i] >= 0.0) {
        wj_im = -wj_im;
      }

      if (fabs(wj_im) < 1.0020841800044864E-292) {
        pvt = 0;
        do {
          pvt++;
          nmip1 = (ix - i) + 5;
          for (k = ix; k <= nmip1; k++) {
            b_A[k - 1] *= 9.9792015476736E+291;
          }

          wj_im *= 9.9792015476736E+291;
          t *= 9.9792015476736E+291;
        } while (!(fabs(wj_im) >= 1.0020841800044864E-292));

        tol = fabs(t);
        wj_im = fabs(eml_xnrm2(6 - i, b_A, ix));
        if (tol < wj_im) {
          tol /= wj_im;
          wj_im *= sqrt(tol * tol + 1.0);
        } else if (tol > wj_im) {
          wj_im /= tol;
          wj_im = sqrt(wj_im * wj_im + 1.0) * tol;
        } else if (rtIsNaN(wj_im)) {
        } else {
          wj_im = tol * 1.4142135623730951;
        }

        if (t >= 0.0) {
          wj_im = -wj_im;
        }

        tol = (wj_im - t) / wj_im;
        t = 1.0 / (t - wj_im);
        nmip1 = (ix - i) + 5;
        while (ix <= nmip1) {
          b_A[ix - 1] *= t;
          ix++;
        }

        for (k = 1; k <= pvt; k++) {
          wj_im *= 1.0020841800044864E-292;
        }

        t = wj_im;
      } else {
        tol = (wj_im - b_A[i_i]) / wj_im;
        t = 1.0 / (b_A[i_i] - wj_im);
        nmip1 = (ix - i) + 5;
        while (ix <= nmip1) {
          b_A[ix - 1] *= t;
          ix++;
        }

        t = wj_im;
      }
    }

    tau[i] = tol;
    b_A[i_i] = t;
    if (i + 1 < 3) {
      t = b_A[i_i];
      b_A[i_i] = 1.0;
      eml_matlab_zlarf(7 - i, 2 - i, i_i + 1, tau[i], b_A, (i + (i + 1) * 7) + 1,
                       work);
      b_A[i_i] = t;
    }

    for (pvt = i + 1; pvt + 1 < 4; pvt++) {
      if (vn1[pvt] != 0.0) {
        wj_im = fabs(b_A[i + 7 * pvt]) / vn1[pvt];
        y = wj_im * wj_im;
        wj_im = 1.0 - wj_im * wj_im;
        if (1.0 - y < 0.0) {
          wj_im = 0.0;
        }

        tol = vn1[pvt] / vn2[pvt];
        if (wj_im * (tol * tol) <= 1.4901161193847656E-8) {
          ix = (i + 7 * pvt) + 2;
          y = 0.0;
          tol = 2.2250738585072014E-308;
          nmip1 = (ix - i) + 5;
          while (ix <= nmip1) {
            wj_im = fabs(b_A[ix - 1]);
            if (wj_im > tol) {
              t = tol / wj_im;
              y = 1.0 + y * t * t;
              tol = wj_im;
            } else {
              t = wj_im / tol;
              y += t * t;
            }

            ix++;
          }

          y = tol * sqrt(y);
          vn1[pvt] = y;
          vn2[pvt] = vn1[pvt];
        } else {
          vn1[pvt] *= sqrt(wj_im);
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
    Y[i].re = 0.0;
    Y[i].im = 0.0;
  }

  for (pvt = 0; pvt < 3; pvt++) {
    if (tau[pvt] != 0.0) {
      tol = B[pvt].re;
      wj_im = B[pvt].im;
      for (i = 0; i <= 5 - pvt; i++) {
        nmip1 = (pvt + i) + 1;
        tol += b_A[nmip1 + 7 * pvt] * B[nmip1].re;
        wj_im += b_A[nmip1 + 7 * pvt] * B[nmip1].im;
      }

      tol *= tau[pvt];
      wj_im *= tau[pvt];
      if ((tol != 0.0) || (wj_im != 0.0)) {
        B[pvt].re -= tol;
        B[pvt].im -= wj_im;
        for (i = 0; i <= 5 - pvt; i++) {
          nmip1 = (pvt + i) + 1;
          B[nmip1].re -= b_A[nmip1 + 7 * pvt] * tol;
          B[nmip1].im -= b_A[nmip1 + 7 * pvt] * wj_im;
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
      Y[jpvt[i] - 1].re -= Y[jpvt[2 - pvt] - 1].re * b_A[i + 7 * (2 - pvt)];
      Y[jpvt[i] - 1].im -= Y[jpvt[2 - pvt] - 1].im * b_A[i + 7 * (2 - pvt)];
    }
  }
}

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

void polyfit(const real_T x[7], const creal_T y[7], creal_T p[3])
{
  real_T V[21];
  creal_T b_y[7];
  int32_T k;
  real_T rr;
  creal_T p1[3];
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

/* End of code generation (polyfit.c) */
