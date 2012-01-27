/*
 * measureFreqXcorr.c
 *
 * Code generation for function 'measureFreqXcorr'
 *
 * C source code generated on: Fri Jan 27 01:45:06 2012
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
static boolean_T eml_relop(const creal_T a, const creal_T b, boolean_T safe_eq);
static real_T rt_atan2d_snf(real_T u0, real_T u1);

/* Function Definitions */
static boolean_T eml_relop(const creal_T a, const creal_T b, boolean_T safe_eq)
{
  boolean_T p;
  real_T b_a;
  real_T b_b;
  real_T c_b;
  int32_T exponent;
  int32_T b_exponent;
  int32_T c_exponent;
  if ((fabs(a.re) > 8.9884656743115785E+307) || (fabs(a.im) >
       8.9884656743115785E+307) || (fabs(b.re) > 8.9884656743115785E+307) ||
      (fabs(b.im) > 8.9884656743115785E+307)) {
    b_a = fabs(a.re / 2.0);
    b_b = fabs(a.im / 2.0);
    if (b_a < b_b) {
      b_a /= b_b;
      b_b *= sqrt(b_a * b_a + 1.0);
    } else if (b_a > b_b) {
      b_b /= b_a;
      b_b = sqrt(b_b * b_b + 1.0) * b_a;
    } else if (rtIsNaN(b_b)) {
    } else {
      b_b = b_a * 1.4142135623730951;
    }

    b_a = fabs(b.re / 2.0);
    c_b = fabs(b.im / 2.0);
    if (b_a < c_b) {
      b_a /= c_b;
      c_b *= sqrt(b_a * b_a + 1.0);
    } else if (b_a > c_b) {
      c_b /= b_a;
      c_b = sqrt(c_b * c_b + 1.0) * b_a;
    } else if (rtIsNaN(c_b)) {
    } else {
      c_b = b_a * 1.4142135623730951;
    }
  } else {
    b_a = fabs(a.re);
    b_b = fabs(a.im);
    if (b_a < b_b) {
      b_a /= b_b;
      b_b *= sqrt(b_a * b_a + 1.0);
    } else if (b_a > b_b) {
      b_b /= b_a;
      b_b = sqrt(b_b * b_b + 1.0) * b_a;
    } else if (rtIsNaN(b_b)) {
    } else {
      b_b = b_a * 1.4142135623730951;
    }

    b_a = fabs(b.re);
    c_b = fabs(b.im);
    if (b_a < c_b) {
      b_a /= c_b;
      c_b *= sqrt(b_a * b_a + 1.0);
    } else if (b_a > c_b) {
      c_b /= b_a;
      c_b = sqrt(c_b * c_b + 1.0) * b_a;
    } else if (rtIsNaN(c_b)) {
    } else {
      c_b = b_a * 1.4142135623730951;
    }
  }

  b_a = fabs(c_b / 2.0);
  if ((!rtIsInf(b_a)) && (!rtIsNaN(b_a))) {
    if (b_a <= 2.2250738585072014E-308) {
      b_a = 4.94065645841247E-324;
    } else {
      frexp(b_a, &exponent);
      b_a = ldexp(1.0, exponent - 53);
    }
  } else {
    b_a = rtNaN;
  }

  if ((fabs(c_b - b_b) < b_a) || (rtIsInf(b_b) && rtIsInf(c_b) && ((b_b > 0.0) ==
        (c_b > 0.0)))) {
    p = TRUE;
  } else {
    p = FALSE;
  }

  if (p) {
    b_b = rt_atan2d_snf(a.im, a.re);
    c_b = rt_atan2d_snf(b.im, b.re);
    b_a = fabs(c_b / 2.0);
    if ((!rtIsInf(b_a)) && (!rtIsNaN(b_a))) {
      if (b_a <= 2.2250738585072014E-308) {
        b_a = 4.94065645841247E-324;
      } else {
        frexp(b_a, &b_exponent);
        b_a = ldexp(1.0, b_exponent - 53);
      }
    } else {
      b_a = rtNaN;
    }

    if ((fabs(c_b - b_b) < b_a) || (rtIsInf(b_b) && rtIsInf(c_b) && ((b_b > 0.0)
          == (c_b > 0.0)))) {
      p = TRUE;
    } else {
      p = FALSE;
    }

    if (p) {
      b_b = fabs(a.re);
      c_b = fabs(b.re);
      b_a = c_b / 2.0;
      if ((!rtIsInf(b_a)) && (!rtIsNaN(b_a))) {
        if (b_a <= 2.2250738585072014E-308) {
          b_a = 4.94065645841247E-324;
        } else {
          frexp(b_a, &c_exponent);
          b_a = ldexp(1.0, c_exponent - 53);
        }
      } else {
        b_a = rtNaN;
      }

      if ((fabs(c_b - b_b) < b_a) || (rtIsInf(b_b) && rtIsInf(c_b) && ((b_b >
             0.0) == (c_b > 0.0)))) {
        p = TRUE;
      } else {
        p = FALSE;
      }

      if (p) {
        b_b = 0.0;
        c_b = 0.0;
      }
    }
  }

  return b_b > c_b;
}

static real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    y = atan2(u0 > 0.0 ? 1.0 : -1.0, u1 > 0.0 ? 1.0 : -1.0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

creal_T eml_div(const creal_T x, real_T y)
{
  creal_T z;
  if (x.im == 0.0) {
    z.re = x.re / y;
    z.im = 0.0;
  } else if (x.re == 0.0) {
    z.re = 0.0;
    z.im = x.im / y;
  } else {
    z.re = x.re / y;
    z.im = x.im / y;
  }

  return z;
}

void measureFreqXcorr(const real_T s[8192], real_T Fs, real_T *F, real_T *snr,
                      creal_T w[8192])
{
  static real_T dv0[8192];
  static real_T dv1[8192];
  static real_T dv2[8192];
  static creal_T sh[8192];
  int32_T i;
  int32_T tmp_data[8192];
  int32_T i0;
  int32_T loop_ub;
  int32_T b_tmp_data[8192];
  creal_T mtmp;
  int32_T p;
  boolean_T exitg1;
  creal_T b_sh[7];
  real_T idx;
  real_T b_idx[7];
  creal_T PP[3];
  creal_T dc0;
  creal_T dc1;
  fft(s, w);
  b_abs(w, dv0);
  memcpy((void *)&dv1[0], (void *)&dv0[0], sizeof(real_T) << 13);
  power(dv1, dv2);
  ifft(dv2, sh);
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
    sh[b_tmp_data[i0] - 1].re = 0.0;
    sh[b_tmp_data[i0] - 1].im = 0.0;
  }

  i = 1;
  mtmp = sh[0];
  p = 1;
  if (rtIsNaN(sh[0].re) || rtIsNaN(sh[0].im)) {
    loop_ub = 1;
    exitg1 = 0U;
    while ((exitg1 == 0U) && (loop_ub + 1 < 1101)) {
      i = loop_ub + 1;
      if (!(rtIsNaN(sh[loop_ub].re) || rtIsNaN(sh[loop_ub].im))) {
        mtmp = sh[loop_ub];
        exitg1 = 1U;
      } else {
        loop_ub++;
      }
    }
  }

  if (i < 1100) {
    while (i + 1 < 1101) {
      if (eml_relop(sh[i], mtmp, TRUE)) {
        mtmp = sh[i];
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
  dc0 = mrdivide(eml_div(PP[1], 2.0), PP[0]);
  dc1.re = dc0.re + 1.0;
  dc1.im = dc0.im;
  dc0 = b_mrdivide(Fs, dc1);
  *F = dc0.re;
  *snr = mtmp.re;
}

/* End of code generation (measureFreqXcorr.c) */
