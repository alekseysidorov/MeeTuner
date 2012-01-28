/*
 * polyfit.cpp
 *
 * Code generation for function 'polyfit'
 *
 * C source code generated on: Sat Jan 28 13:22:16 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "getNote.h"
#include "measureFreqXcorr.h"
#include "polyfit.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static real32_T eml_div(real32_T x, real_T y);
static void eml_matlab_zlarf(int32_T m, int32_T n, int32_T iv0, real_T tau,
  real_T C[21], int32_T ic0, real_T work[3]);
static void eml_qrsolve(const real_T A[21], real32_T B[7], boolean_T
  ignoreRankDeficiency, real32_T Y[3], real_T *rankR);
static real_T eml_xnrm2(int32_T n, const real_T x[21], int32_T ix0);

/* Function Definitions */
static real32_T eml_div(real32_T x, real_T y)
{
  return x / (real32_T)y;
}

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
  int32_T i2;
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
      i2 = ic0 + 7 * i;
      for (i = ic0; i <= i2; i += 7) {
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
          i2 = lastv + i;
          for (iy = i; iy + 1 <= i2; iy++) {
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

void polyfit(const real_T x[7], const real32_T y[7], real32_T p[3])
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

/* End of code generation (polyfit.cpp) */
