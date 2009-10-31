/* SPARC v9 32-bit gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 1999, 2000, 2001, 2002, 2004, 2009 Free Software
Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library.  If not, see http://www.gnu.org/licenses/.  */

#define BITS_PER_MP_LIMB 32
#define BYTES_PER_MP_LIMB 4

/* Generated by tuneup.c, 2009-02-12, gcc 2.95 */

#define MUL_TOOM22_THRESHOLD             28
#define MUL_TOOM33_THRESHOLD             97
#define MUL_TOOM44_THRESHOLD            136

#define SQR_BASECASE_THRESHOLD            8
#define SQR_TOOM2_THRESHOLD              60
#define SQR_TOOM3_THRESHOLD             138
#define SQR_TOOM4_THRESHOLD             278

#define MULLOW_BASECASE_THRESHOLD         0  /* always */
#define MULLOW_DC_THRESHOLD             111
#define MULLOW_MUL_N_THRESHOLD          434

#define DIV_SB_PREINV_THRESHOLD           7
#define DIV_DC_THRESHOLD                122
#define POWM_THRESHOLD                  154

#define MATRIX22_STRASSEN_THRESHOLD      12
#define HGCD_THRESHOLD                  155
#define GCD_DC_THRESHOLD                614
#define GCDEXT_DC_THRESHOLD             438
#define JACOBI_BASE_METHOD                2

#define DIVREM_1_NORM_THRESHOLD           5
#define DIVREM_1_UNNORM_THRESHOLD        14
#define MOD_1_NORM_THRESHOLD              4
#define MOD_1_UNNORM_THRESHOLD            5
#define MOD_1_1_THRESHOLD                 7
#define MOD_1_2_THRESHOLD                 8
#define MOD_1_4_THRESHOLD                16
#define USE_PREINV_DIVREM_1               1
#define USE_PREINV_MOD_1                  1
#define DIVREM_2_THRESHOLD                0  /* always */
#define DIVEXACT_1_THRESHOLD              0  /* always */
#define MODEXACT_1_ODD_THRESHOLD      MP_SIZE_T_MAX  /* never */

#define GET_STR_DC_THRESHOLD             12
#define GET_STR_PRECOMPUTE_THRESHOLD     19
#define SET_STR_DC_THRESHOLD            802
#define SET_STR_PRECOMPUTE_THRESHOLD   1647

#define MUL_FFT_TABLE  { 304, 736, 1152, 3584, 10240, 24576, 98304, 393216, 0 }
#define MUL_FFT_MODF_THRESHOLD          264
#define MUL_FFT_THRESHOLD              2304

#define SQR_FFT_TABLE  { 336, 800, 1408, 3584, 10240, 24576, 98304, 393216, 0 }
#define SQR_FFT_MODF_THRESHOLD          248
#define SQR_FFT_THRESHOLD              2304
