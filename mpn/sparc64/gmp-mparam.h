/* Sparc64 gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 1999, 2000, 2001, 2002 Free Software Foundation,
Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#define BITS_PER_MP_LIMB 64
#define BYTES_PER_MP_LIMB 8

/* Tell the toom3 multiply implementation to call low-level mpn
   functions instead of open-coding operations in C.  */
#ifndef USE_MORE_MPN
#define USE_MORE_MPN 1
#endif


/* 296MHz ultrasparc-II */

#ifdef __GNUC__
/* Generated by tuneup.c, 2003-02-10, gcc 3.2 */

#define MUL_KARATSUBA_THRESHOLD          26
#define MUL_TOOM3_THRESHOLD              89

#define SQR_BASECASE_THRESHOLD            7
#define SQR_KARATSUBA_THRESHOLD          52
#define SQR_TOOM3_THRESHOLD             134

#define DIV_SB_PREINV_THRESHOLD           8
#define DIV_DC_THRESHOLD                 52
#define POWM_THRESHOLD                  212

#define GCD_ACCEL_THRESHOLD               3
#define GCDEXT_THRESHOLD                  6
#define JACOBI_BASE_METHOD                3

#define DIVREM_1_NORM_THRESHOLD           6
#define DIVREM_1_UNNORM_THRESHOLD         6
#define MOD_1_NORM_THRESHOLD              5
#define MOD_1_UNNORM_THRESHOLD            6
#define USE_PREINV_DIVREM_1               1
#define USE_PREINV_MOD_1                  1
#define DIVREM_2_THRESHOLD                5
#define DIVEXACT_1_THRESHOLD              0  /* always */
#define MODEXACT_1_ODD_THRESHOLD          0  /* always */

#define GET_STR_DC_THRESHOLD             11
#define GET_STR_PRECOMPUTE_THRESHOLD     14
#define SET_STR_THRESHOLD              8015

#define MUL_FFT_TABLE  { 304, 672, 1600, 2816, 7168, 20480, 49152, 0 }
#define MUL_FFT_MODF_THRESHOLD          200
#define MUL_FFT_THRESHOLD              1536

#define SQR_FFT_TABLE  { 336, 672, 1600, 2816, 7168, 20480, 49152, 0 }
#define SQR_FFT_MODF_THRESHOLD          200
#define SQR_FFT_THRESHOLD              1312

#else

/* Generated by tuneup.c, 2002-12-22, Sun C 5.0 */

#define MUL_KARATSUBA_THRESHOLD          24
#define MUL_TOOM3_THRESHOLD             114

#define SQR_BASECASE_THRESHOLD            6
#define SQR_KARATSUBA_THRESHOLD          54
#define SQR_TOOM3_THRESHOLD             113

#define DIV_SB_PREINV_THRESHOLD           7
#define DIV_DC_THRESHOLD                 44
#define POWM_THRESHOLD                  243

#define GCD_ACCEL_THRESHOLD               3
#define GCDEXT_THRESHOLD                 19
#define JACOBI_BASE_METHOD                3

#define DIVREM_1_NORM_THRESHOLD           5
#define DIVREM_1_UNNORM_THRESHOLD         6
#define MOD_1_NORM_THRESHOLD              4
#define MOD_1_UNNORM_THRESHOLD            6
#define USE_PREINV_DIVREM_1               1
#define USE_PREINV_MOD_1                  1
#define DIVREM_2_THRESHOLD                6
#define DIVEXACT_1_THRESHOLD              0  /* always */
#define MODEXACT_1_ODD_THRESHOLD          0  /* always */

#define GET_STR_DC_THRESHOLD             12
#define GET_STR_PRECOMPUTE_THRESHOLD     18
#define SET_STR_THRESHOLD              6589

#define MUL_FFT_TABLE  { 304, 672, 1600, 2816, 7168, 20480, 49152, 0 }
#define MUL_FFT_MODF_THRESHOLD          232
#define MUL_FFT_THRESHOLD              1664

#define SQR_FFT_TABLE  { 336, 736, 1600, 2816, 7168, 20480, 49152, 0 }
#define SQR_FFT_MODF_THRESHOLD          232
#define SQR_FFT_THRESHOLD              1536

#endif
