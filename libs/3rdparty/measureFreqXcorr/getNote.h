/*
 * getNote.h
 *
 * Code generation for function 'getNote'
 *
 * C source code generated on: Sat Feb 04 00:52:50 2012
 *
 */

#ifndef __GETNOTE_H__
#define __GETNOTE_H__
/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"

#include "rtwtypes.h"
#include "getNote_types.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern void getNote(real32_T f, real32_T *noteFreq, real32_T *noteError, char_T noteName[3], int32_T *noteOctave);
extern void getNote_initialize(void);
extern void getNote_terminate(void);
extern void measureFreqXcorr(const int32_T s[8192], uint16_T analizeTime, real32_T Fs, real32_T th, real32_T *F, real32_T *snr, creal32_T w_data[65535], int32_T w_sizes[2]);
extern void powerMeter(const int32_T signal[8192], uint32_T len, real32_T *dB, real32_T *Lin);
#endif
/* End of code generation (getNote.h) */
