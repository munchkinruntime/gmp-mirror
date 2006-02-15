/* AMD K7 gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 2000, 2001, 2002, 2003, 2004, 2005 Free Software
Foundation, Inc.

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
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA. */

#define BITS_PER_MP_LIMB 64
#define BYTES_PER_MP_LIMB 8


/* 1800 MHz Athlon 64 / rev CG / socket 754 */

/* Generated by tuneup.c, 2005-03-19, gcc 3.4 */

#define MUL_KARATSUBA_THRESHOLD          24
#define MUL_TOOM3_THRESHOLD              81

#define SQR_BASECASE_THRESHOLD            9
#define SQR_KARATSUBA_THRESHOLD          28
#define SQR_TOOM3_THRESHOLD             109

#define MULLOW_BASECASE_THRESHOLD         0  /* always */
#define MULLOW_DC_THRESHOLD              24
#define MULLOW_MUL_N_THRESHOLD          375

#define DIV_SB_PREINV_THRESHOLD           0  /* always */
#define DIV_DC_THRESHOLD                 48
#define POWM_THRESHOLD                  200

#define HGCD_SCHOENHAGE_THRESHOLD       182
#define GCD_ACCEL_THRESHOLD               3
#define GCD_SCHOENHAGE_THRESHOLD        426
#define GCDEXT_SCHOENHAGE_THRESHOLD     514
#define JACOBI_BASE_METHOD                1

#define MOD_1_NORM_THRESHOLD              0  /* always */
#define MOD_1_UNNORM_THRESHOLD            0  /* always */
#define USE_PREINV_DIVREM_1               1  /* native */
#define USE_PREINV_MOD_1                  1
#define DIVREM_2_THRESHOLD                0  /* always */
#define DIVEXACT_1_THRESHOLD              0  /* always (native) */
#define MODEXACT_1_ODD_THRESHOLD          0  /* always (native) */

#define GET_STR_DC_THRESHOLD             19
#define GET_STR_PRECOMPUTE_THRESHOLD     27
#define SET_STR_THRESHOLD              8540

#define MUL_FFT_TABLE  { 688, 1440, 3136, 5888, 15360, 45056, 114688, 458752, 1310720, 3145728, 0 }
#define MUL_FFT_MODF_THRESHOLD          704
#define MUL_FFT_THRESHOLD              6528

#define SQR_FFT_TABLE  { 624, 1312, 2880, 5888, 13312, 36864, 114688, 327680, 1310720, 3145728, 0 }
#define SQR_FFT_MODF_THRESHOLD          640
#define SQR_FFT_THRESHOLD              5760
