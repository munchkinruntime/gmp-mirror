/* 80486 gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 2001, 2002, 2003 Free Software Foundation, Inc.

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

#define BITS_PER_MP_LIMB 32
#define BYTES_PER_MP_LIMB 4


/* 100MHz DX4 */

/* Generated by tuneup.c, 2003-02-13, gcc 2.95 */

#define MUL_KARATSUBA_THRESHOLD          18
#define MUL_TOOM3_THRESHOLD             228

#define SQR_BASECASE_THRESHOLD           13
#define SQR_KARATSUBA_THRESHOLD          49
#define SQR_TOOM3_THRESHOLD             238

#define DIV_SB_PREINV_THRESHOLD       MP_SIZE_T_MAX  /* never */
#define DIV_DC_THRESHOLD                 72
#define POWM_THRESHOLD                   38

#define GCD_ACCEL_THRESHOLD               3
#define GCDEXT_THRESHOLD                 55
#define JACOBI_BASE_METHOD                2

#define USE_PREINV_DIVREM_1               0
#define USE_PREINV_MOD_1                  0
#define DIVREM_2_THRESHOLD            MP_SIZE_T_MAX  /* never */
#define DIVEXACT_1_THRESHOLD              0  /* always (native) */
#define MODEXACT_1_ODD_THRESHOLD         17

#define GET_STR_DC_THRESHOLD             32
#define GET_STR_PRECOMPUTE_THRESHOLD     82
#define SET_STR_THRESHOLD              3524

#define MUL_FFT_TABLE  { 464, 928, 1920, 4608, 10240, 40960, 0 }
#define MUL_FFT_MODF_THRESHOLD          392
#define MUL_FFT_THRESHOLD              2816

#define SQR_FFT_TABLE  { 432, 928, 1920, 4608, 14336, 40960, 0 }
#define SQR_FFT_MODF_THRESHOLD          392
#define SQR_FFT_THRESHOLD              2816
