/* x86/bobcat gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 2019 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of either:

  * the GNU Lesser General Public License as published by the Free
    Software Foundation; either version 3 of the License, or (at your
    option) any later version.

or

  * the GNU General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any
    later version.

or both in parallel, as here.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received copies of the GNU General Public License and the
GNU Lesser General Public License along with the GNU MP Library.  If not,
see https://www.gnu.org/licenses/.  */

#define GMP_LIMB_BITS 32
#define GMP_LIMB_BYTES 4

/* NOTE: In a fat binary build SQR_TOOM2_THRESHOLD here cannot be greater than
   the value in mpn/x86/k7/gmp-mparam.h.  The latter is used as a hard limit in
   k7/sqr_basecase.asm.  */

/* 2050 MHz AMD Jaguar/Kabini */
/* FFT tuning limit = 0.5 */
/* Generated by tuneup.c, 2019-09-27, gcc 8.3 */

#define MOD_1_NORM_THRESHOLD                 4
#define MOD_1_UNNORM_THRESHOLD               7
#define MOD_1N_TO_MOD_1_1_THRESHOLD          4
#define MOD_1U_TO_MOD_1_1_THRESHOLD          4
#define MOD_1_1_TO_MOD_1_2_THRESHOLD        18
#define MOD_1_2_TO_MOD_1_4_THRESHOLD         0  /* never mpn_mod_1s_2p */
#define PREINV_MOD_1_TO_MOD_1_THRESHOLD      9
#define USE_PREINV_DIVREM_1                  1  /* native */
#define DIV_QR_1N_PI1_METHOD                 1  /* 48.54% faster than 2 */
#define DIV_QR_1_NORM_THRESHOLD          MP_SIZE_T_MAX  /* never */
#define DIV_QR_1_UNNORM_THRESHOLD        MP_SIZE_T_MAX  /* never */
#define DIV_QR_2_PI2_THRESHOLD           MP_SIZE_T_MAX  /* never */
#define DIVEXACT_1_THRESHOLD                 0  /* always (native) */
#define BMOD_1_TO_MOD_1_THRESHOLD           27

#define DIV_1_VS_MUL_1_PERCENT             243

#define MUL_TOOM22_THRESHOLD                32
#define MUL_TOOM33_THRESHOLD                89
#define MUL_TOOM44_THRESHOLD               154
#define MUL_TOOM6H_THRESHOLD               318
#define MUL_TOOM8H_THRESHOLD               478

#define MUL_TOOM32_TO_TOOM43_THRESHOLD     101
#define MUL_TOOM32_TO_TOOM53_THRESHOLD     159
#define MUL_TOOM42_TO_TOOM53_THRESHOLD     104
#define MUL_TOOM42_TO_TOOM63_THRESHOLD     119
#define MUL_TOOM43_TO_TOOM54_THRESHOLD     154

#define SQR_BASECASE_THRESHOLD               0  /* always (native) */
#define SQR_TOOM2_THRESHOLD                 38
#define SQR_TOOM3_THRESHOLD                138
#define SQR_TOOM4_THRESHOLD                220
#define SQR_TOOM6_THRESHOLD                366
#define SQR_TOOM8_THRESHOLD                502

#define MULMID_TOOM42_THRESHOLD             72

#define MULMOD_BNM1_THRESHOLD               19
#define SQRMOD_BNM1_THRESHOLD               24

#define MUL_FFT_MODF_THRESHOLD             606  /* k = 5 */
#define MUL_FFT_TABLE3                                      \
  { {    606, 5}, {     25, 6}, {     13, 5}, {     27, 6}, \
    {     15, 5}, {     31, 6}, {     27, 7}, {     15, 6}, \
    {     31, 7}, {     17, 6}, {     35, 7}, {     19, 6}, \
    {     39, 7}, {     23, 6}, {     47, 7}, {     27, 8}, \
    {     15, 7}, {     35, 8}, {     19, 7}, {     41, 8}, \
    {     23, 7}, {     49, 8}, {     31, 7}, {     63, 8}, \
    {     43, 9}, {     23, 8}, {     55, 9}, {     31, 8}, \
    {     67, 9}, {     39, 8}, {     79, 9}, {     47, 8}, \
    {     95, 9}, {     55,10}, {     31, 9}, {     79,10}, \
    {     47, 9}, {     95,11}, {     31,10}, {     63, 9}, \
    {    135,10}, {     79, 9}, {    159,10}, {     95,11}, \
    {     63,10}, {    159,11}, {     95,12}, {     63,11}, \
    {    127,10}, {    255, 9}, {    511,10}, {    271, 9}, \
    {    543, 8}, {   1087,11}, {    159,10}, {    319, 9}, \
    {    639,10}, {    335, 9}, {    671,11}, {    191,10}, \
    {    383, 9}, {    767,10}, {    399, 9}, {    799,10}, \
    {    415,12}, {   4096,13}, {   8192,14}, {  16384,15}, \
    {  32768,16} }
#define MUL_FFT_TABLE3_SIZE 69
#define MUL_FFT_THRESHOLD                 5760

#define SQR_FFT_MODF_THRESHOLD             530  /* k = 5 */
#define SQR_FFT_TABLE3                                      \
  { {    530, 5}, {     28, 6}, {     15, 5}, {     31, 6}, \
    {     28, 7}, {     15, 6}, {     33, 7}, {     17, 6}, \
    {     35, 7}, {     19, 6}, {     39, 7}, {     23, 6}, \
    {     47, 7}, {     29, 8}, {     15, 7}, {     35, 8}, \
    {     19, 7}, {     41, 8}, {     23, 7}, {     49, 8}, \
    {     31, 7}, {     63, 8}, {     43, 9}, {     23, 8}, \
    {     51, 9}, {     31, 8}, {     67, 9}, {     39, 8}, \
    {     79, 9}, {     47, 8}, {     95, 9}, {     55,10}, \
    {     31, 9}, {     79,10}, {     47, 9}, {     95,11}, \
    {     31,10}, {     63, 9}, {    135,10}, {     79, 9}, \
    {    159,10}, {     95,11}, {     63,10}, {    159,11}, \
    {     95,10}, {    191,12}, {     63,11}, {    127,10}, \
    {    255, 9}, {    511,10}, {    271, 9}, {    543,10}, \
    {    287,11}, {    159,10}, {    319, 9}, {    639,10}, \
    {    335, 9}, {    671,10}, {    351, 9}, {    703,11}, \
    {    191,10}, {    383, 9}, {    767,10}, {    399, 9}, \
    {    799,10}, {    415,12}, {   4096,13}, {   8192,14}, \
    {  16384,15}, {  32768,16} }
#define SQR_FFT_TABLE3_SIZE 70
#define SQR_FFT_THRESHOLD                 4736

#define MULLO_BASECASE_THRESHOLD             3
#define MULLO_DC_THRESHOLD                  43
#define MULLO_MUL_N_THRESHOLD            11278
#define SQRLO_BASECASE_THRESHOLD            10
#define SQRLO_DC_THRESHOLD                  11
#define SQRLO_SQR_THRESHOLD               8907

#define DC_DIV_QR_THRESHOLD                 92
#define DC_DIVAPPR_Q_THRESHOLD             234
#define DC_BDIV_QR_THRESHOLD                92
#define DC_BDIV_Q_THRESHOLD                176

#define INV_MULMOD_BNM1_THRESHOLD           90
#define INV_NEWTON_THRESHOLD               250
#define INV_APPR_THRESHOLD                 244

#define BINV_NEWTON_THRESHOLD              276
#define REDC_1_TO_REDC_N_THRESHOLD          83

#define MU_DIV_QR_THRESHOLD               1787
#define MU_DIVAPPR_Q_THRESHOLD            1652
#define MUPI_DIV_QR_THRESHOLD              122
#define MU_BDIV_QR_THRESHOLD              1442
#define MU_BDIV_Q_THRESHOLD               1713

#define POWM_SEC_TABLE  1,22,96,579,1420

#define GET_STR_DC_THRESHOLD                15
#define GET_STR_PRECOMPUTE_THRESHOLD        29
#define SET_STR_DC_THRESHOLD               262
#define SET_STR_PRECOMPUTE_THRESHOLD       676

#define FAC_DSC_THRESHOLD                  141
#define FAC_ODD_THRESHOLD                  121

#define MATRIX22_STRASSEN_THRESHOLD         33
#define HGCD2_DIV1_METHOD                    1  /* 11.71% faster than 4 */
#define HGCD_THRESHOLD                      84
#define HGCD_APPR_THRESHOLD                 60
#define HGCD_REDUCE_THRESHOLD             3389
#define GCD_DC_THRESHOLD                   562
#define GCDEXT_DC_THRESHOLD                379
#define JACOBI_BASE_METHOD                   4  /* 1.67% faster than 1 */
