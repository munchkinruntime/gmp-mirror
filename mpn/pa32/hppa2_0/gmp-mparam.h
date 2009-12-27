/* gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 1999, 2000, 2001, 2002, 2009 Free Software
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

#define GMP_LIMB_BITS 32
#define BYTES_PER_MP_LIMB 4

/* 552 MHz PA8600 (gcc61.fsffrance.org) */

/* Generated by tuneup.c, 2009-11-29, gcc 4.2 */

#define MUL_TOOM22_THRESHOLD                15
#define MUL_TOOM33_THRESHOLD                91
#define MUL_TOOM44_THRESHOLD               154
#define MUL_TOOM6H_THRESHOLD               204
#define MUL_TOOM8H_THRESHOLD               482

#define MUL_TOOM32_TO_TOOM43_THRESHOLD      97
#define MUL_TOOM32_TO_TOOM53_THRESHOLD     103
#define MUL_TOOM42_TO_TOOM53_THRESHOLD     109
#define MUL_TOOM42_TO_TOOM63_THRESHOLD     103

#define SQR_BASECASE_THRESHOLD               6
#define SQR_TOOM2_THRESHOLD                 47
#define SQR_TOOM3_THRESHOLD                 93
#define SQR_TOOM4_THRESHOLD                250
#define SQR_TOOM6_THRESHOLD                278
#define SQR_TOOM8_THRESHOLD                502

#define MULMOD_BNM1_THRESHOLD               13
#define SQRMOD_BNM1_THRESHOLD               15

#define MUL_FFT_TABLE  { 304, 672, 896, 2560, 10240, 24576, 98304, 0 }
#define MUL_FFT_MODF_THRESHOLD             296
#define MUL_FFT_THRESHOLD                 2816

#define SQR_FFT_TABLE  { 304, 672, 1152, 2560, 6144, 24576, 98304, 0 }
#define SQR_FFT_MODF_THRESHOLD             232
#define SQR_FFT_THRESHOLD                 2304

#define MULLO_BASECASE_THRESHOLD             0  /* always */
#define MULLO_DC_THRESHOLD                  90
#define MULLO_MUL_N_THRESHOLD             3215

#define DC_DIV_QR_THRESHOLD                100
#define DC_DIVAPPR_Q_THRESHOLD             342
#define DC_BDIV_QR_THRESHOLD               119
#define DC_BDIV_Q_THRESHOLD                246

#define INV_MULMOD_BNM1_THRESHOLD           12
#define INV_NEWTON_THRESHOLD               274
#define INV_APPR_THRESHOLD                 268

#define BINV_NEWTON_THRESHOLD              327
#define REDC_1_TO_REDC_N_THRESHOLD          70

#define MATRIX22_STRASSEN_THRESHOLD         15
#define HGCD_THRESHOLD                      99
#define GCD_DC_THRESHOLD                   372
#define GCDEXT_DC_THRESHOLD                241
#define JACOBI_BASE_METHOD                   2

#define DIVREM_1_NORM_THRESHOLD              0  /* always */
#define DIVREM_1_UNNORM_THRESHOLD            3
#define MOD_1_NORM_THRESHOLD                 3
#define MOD_1_UNNORM_THRESHOLD               4
#define MOD_1N_TO_MOD_1_1_THRESHOLD         15
#define MOD_1U_TO_MOD_1_1_THRESHOLD          0  /* always */
#define MOD_1_1_TO_MOD_1_2_THRESHOLD         8
#define MOD_1_2_TO_MOD_1_4_THRESHOLD        18
#define PREINV_MOD_1_TO_MOD_1_THRESHOLD     21
#define USE_PREINV_DIVREM_1                  1
#define DIVREM_2_THRESHOLD                   0  /* always */
#define DIVEXACT_1_THRESHOLD                 0  /* always */
#define BMOD_1_TO_MOD_1_THRESHOLD           31

#define GET_STR_DC_THRESHOLD                 7
#define GET_STR_PRECOMPUTE_THRESHOLD        14
#define SET_STR_DC_THRESHOLD               224
#define SET_STR_PRECOMPUTE_THRESHOLD       788
