/*
 * measureFreqXcorr.cpp
 *
 * Code generation for function 'measureFreqXcorr'
 *
 * C source code generated on: Sat Jan 28 01:02:05 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "measureFreqXcorr.h"
#include "mrdivide.h"
#include "polyfit.h"
#include "ifft.h"
#include "power.h"
#include "abs.h"
#include "fft.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static real32_T rt_atan2f_snf(real32_T u0, real32_T u1);

/* Function Definitions */
static real32_T rt_atan2f_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = ((real32_T)rtNaN);
  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
    y = (real32_T)atan2(u0 > 0.0F ? 1.0F : -1.0F, u1 > 0.0F ? 1.0F : -1.0F);
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = (real32_T)atan2(u0, u1);
  }

  return y;
}

creal32_T eml_div(const creal32_T x, real_T y)
{
  creal32_T z;
  if (x.im == 0.0F) {
    z.re = x.re / (real32_T)y;
    z.im = 0.0F;
  } else if (x.re == 0.0F) {
    z.re = 0.0F;
    z.im = x.im / (real32_T)y;
  } else {
    z.re = x.re / (real32_T)y;
    z.im = x.im / (real32_T)y;
  }

  return z;
}

void measureFreqXcorr(const int32_T s[8192], real32_T Fs, real32_T *F, real32_T *
                      snr, creal32_T w[8192])
{
  static real32_T b_s[8192];
  int32_T i0;
  static real32_T fv0[8192];
  real32_T fv1[8192];
  real32_T fv2[8192];
  static creal32_T sh[8192];
  int32_T i;
  int32_T tmp_data[8192];
  int32_T loop_ub;
  int32_T b_tmp_data[8192];
  real32_T mtmp_im;
  int32_T p;
  boolean_T exitg1;
  real32_T a;
  real32_T b;
  real32_T b_b;
  int32_T exponent;
  boolean_T b_p;
  int32_T b_exponent;
  int32_T c_exponent;
  creal32_T b_sh[7];
  real_T idx;
  real_T b_idx[7];
  creal32_T PP[3];
  creal32_T fc0;
  creal32_T fc1;
  for (i0 = 0; i0 < 8192; i0++) {
    b_s[i0] = (real32_T)s[i0];
  }

  fft(b_s, w);
  b_abs(w, fv0);
  memcpy((void *)&fv1[0], (void *)&fv0[0], sizeof(real32_T) << 13);
  power(fv1, fv2);
  ifft(fv2, sh);
  for (i = 1; sh[i].re < sh[i - 1].re; i++) {
  }

  for (i0 = 0; i0 <= i; i0++) {
    tmp_data[i0] = 1 + i0;
  }

  loop_ub = i;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    b_tmp_data[i0] = tmp_data[i0];
  }

  loop_ub = i;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    sh[b_tmp_data[i0] - 1].re = 0.0F;
    sh[b_tmp_data[i0] - 1].im = 0.0F;
  }

  i = 1;
  *snr = sh[0].re;
  mtmp_im = sh[0].im;
  p = 1;
  if (rtIsNaNF(sh[0].re) || rtIsNaNF(sh[0].im)) {
    loop_ub = 1;
    exitg1 = 0U;
    while ((exitg1 == 0U) && (loop_ub + 1 < 1101)) {
      i = loop_ub + 1;
      if (!(rtIsNaNF(sh[loop_ub].re) || rtIsNaNF(sh[loop_ub].im))) {
        *snr = sh[loop_ub].re;
        mtmp_im = sh[loop_ub].im;
        exitg1 = 1U;
      } else {
        loop_ub++;
      }
    }
  }

  if (i < 1100) {
    while (i + 1 < 1101) {
      if (((real32_T)fabs(sh[i].re) > 1.70141173E+38F) || ((real32_T)fabs(sh[i].
            im) > 1.70141173E+38F) || ((real32_T)fabs(*snr) > 1.70141173E+38F) ||
          ((real32_T)fabs(mtmp_im) > 1.70141173E+38F)) {
        a = (real32_T)fabs(sh[i].re / 2.0F);
        b = (real32_T)fabs(sh[i].im / 2.0F);
        if (a < b) {
          a /= b;
          b *= (real32_T)sqrt(a * a + 1.0F);
        } else if (a > b) {
          b /= a;
          b = (real32_T)sqrt(b * b + 1.0F) * a;
        } else if (rtIsNaNF(b)) {
        } else {
          b = a * 1.41421354F;
        }

        a = (real32_T)fabs(*snr / 2.0F);
        b_b = (real32_T)fabs(mtmp_im / 2.0F);
        if (a < b_b) {
          a /= b_b;
          b_b *= (real32_T)sqrt(a * a + 1.0F);
        } else if (a > b_b) {
          b_b /= a;
          b_b = (real32_T)sqrt(b_b * b_b + 1.0F) * a;
        } else if (rtIsNaNF(b_b)) {
        } else {
          b_b = a * 1.41421354F;
        }
      } else {
        a = (real32_T)fabs(sh[i].re);
        b = (real32_T)fabs(sh[i].im);
        if (a < b) {
          a /= b;
          b *= (real32_T)sqrt(a * a + 1.0F);
        } else if (a > b) {
          b /= a;
          b = (real32_T)sqrt(b * b + 1.0F) * a;
        } else if (rtIsNaNF(b)) {
        } else {
          b = a * 1.41421354F;
        }

        a = (real32_T)fabs(*snr);
        b_b = (real32_T)fabs(mtmp_im);
        if (a < b_b) {
          a /= b_b;
          b_b *= (real32_T)sqrt(a * a + 1.0F);
        } else if (a > b_b) {
          b_b /= a;
          b_b = (real32_T)sqrt(b_b * b_b + 1.0F) * a;
        } else if (rtIsNaNF(b_b)) {
        } else {
          b_b = a * 1.41421354F;
        }
      }

      a = (real32_T)fabs(b_b / 2.0F);
      if ((!rtIsInfF(a)) && (!rtIsNaNF(a))) {
        if (a <= 1.17549435E-38F) {
          a = 1.4013E-45F;
        } else {
          frexp(a, &exponent);
          a = (real32_T)ldexp(1.0, exponent - 24);
        }
      } else {
        a = ((real32_T)rtNaN);
      }

      if (((real32_T)fabs(b_b - b) < a) || (rtIsInfF(b) && rtIsInfF(b_b) && ((b >
             0.0F) == (b_b > 0.0F)))) {
        b_p = TRUE;
      } else {
        b_p = FALSE;
      }

      if (b_p) {
        b = rt_atan2f_snf(sh[i].im, sh[i].re);
        b_b = rt_atan2f_snf(mtmp_im, *snr);
        a = (real32_T)fabs(b_b / 2.0F);
        if ((!rtIsInfF(a)) && (!rtIsNaNF(a))) {
          if (a <= 1.17549435E-38F) {
            a = 1.4013E-45F;
          } else {
            frexp(a, &b_exponent);
            a = (real32_T)ldexp(1.0, b_exponent - 24);
          }
        } else {
          a = ((real32_T)rtNaN);
        }

        if (((real32_T)fabs(b_b - b) < a) || (rtIsInfF(b) && rtIsInfF(b_b) &&
             ((b > 0.0F) == (b_b > 0.0F)))) {
          b_p = TRUE;
        } else {
          b_p = FALSE;
        }

        if (b_p) {
          b = (real32_T)fabs(sh[i].re);
          b_b = (real32_T)fabs(*snr);
          a = b_b / 2.0F;
          if ((!rtIsInfF(a)) && (!rtIsNaNF(a))) {
            if (a <= 1.17549435E-38F) {
              a = 1.4013E-45F;
            } else {
              frexp(a, &c_exponent);
              a = (real32_T)ldexp(1.0, c_exponent - 24);
            }
          } else {
            a = ((real32_T)rtNaN);
          }

          if (((real32_T)fabs(b_b - b) < a) || (rtIsInfF(b) && rtIsInfF(b_b) &&
               ((b > 0.0F) == (b_b > 0.0F)))) {
            b_p = TRUE;
          } else {
            b_p = FALSE;
          }

          if (b_p) {
            b = 0.0F;
            b_b = 0.0F;
          }
        }
      }

      if (b > b_b) {
        *snr = sh[i].re;
        mtmp_im = sh[i].im;
        p = i + 1;
      }

      i++;
    }
  }

  if (p < 4) {
    p = 4;
  }

  for (i0 = 0; i0 < 7; i0++) {
    idx = (real_T)p + (-3.0 + (real_T)i0);
    b_sh[i0] = sh[(int32_T)idx - 1];
    b_idx[i0] = idx;
  }

  polyfit(b_idx, b_sh, PP);

  /*  PD = polyder(PP); */
  /*  PZ = roots(PD); */
  fc0 = mrdivide(eml_div(PP[1], 2.0), PP[0]);
  fc1.re = fc0.re + 1.0F;
  fc1.im = fc0.im;
  fc0 = b_mrdivide(Fs, fc1);
  *F = fc0.re;
}

/* End of code generation (measureFreqXcorr.cpp) */
