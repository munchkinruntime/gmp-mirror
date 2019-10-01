/* AMD bd2 gmp-mparam.h -- Compiler/machine parameter header file.

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

/* 4000 MHz Piledriver Vishera  */
/* FFT tuning limit = 0.5 M */
/* Generated by tuneup.c, 2019-09-27, gcc 8.3 */

#define MOD_1_NORM_THRESHOLD                 3
#define MOD_1_UNNORM_THRESHOLD               4
#define MOD_1N_TO_MOD_1_1_THRESHOLD          6
#define MOD_1U_TO_MOD_1_1_THRESHOLD          4
#define MOD_1_1_TO_MOD_1_2_THRESHOLD        18
#define MOD_1_2_TO_MOD_1_4_THRESHOLD         0  /* never mpn_mod_1s_2p */
#define PREINV_MOD_1_TO_MOD_1_THRESHOLD     12
#define USE_PREINV_DIVREM_1                  1  /* native */
#define DIV_QR_1N_PI1_METHOD                 1  /* 40.53% faster than 2 */
#define DIV_QR_1_NORM_THRESHOLD              5
#define DIV_QR_1_UNNORM_THRESHOLD        MP_SIZE_T_MAX  /* never */
#define DIV_QR_2_PI2_THRESHOLD           MP_SIZE_T_MAX  /* never */
#define DIVEXACT_1_THRESHOLD                 0  /* always (native) */
#define BMOD_1_TO_MOD_1_THRESHOLD           24

#define DIV_1_VS_MUL_1_PERCENT             251

#define MUL_TOOM22_THRESHOLD                32
#define MUL_TOOM33_THRESHOLD                89
#define MUL_TOOM44_THRESHOLD               151
#define MUL_TOOM6H_THRESHOLD               222
#define MUL_TOOM8H_THRESHOLD               354

#define MUL_TOOM32_TO_TOOM43_THRESHOLD      81
#define MUL_TOOM32_TO_TOOM53_THRESHOLD     109
#define MUL_TOOM42_TO_TOOM53_THRESHOLD      99
#define MUL_TOOM42_TO_TOOM63_THRESHOLD     110
#define MUL_TOOM43_TO_TOOM54_THRESHOLD     145

#define SQR_BASECASE_THRESHOLD               0  /* always (native) */
#define SQR_TOOM2_THRESHOLD                 42
#define SQR_TOOM3_THRESHOLD                 89
#define SQR_TOOM4_THRESHOLD                204
#define SQR_TOOM6_THRESHOLD                306
#define SQR_TOOM8_THRESHOLD                502

#define MULMID_TOOM42_THRESHOLD             68

#define MULMOD_BNM1_THRESHOLD               19
#define SQRMOD_BNM1_THRESHOLD               25

#define MUL_FFT_MODF_THRESHOLD             636  /* k = 5 */
#define MUL_FFT_TABLE3                                      \
  { {    636, 5}, {     28, 6}, {     15, 5}, {     31, 6}, \
    {     29, 7}, {     15, 6}, {     33, 7}, {     17, 6}, \
    {     35, 7}, {     19, 6}, {     39, 7}, {     23, 6}, \
    {     47, 7}, {     29, 8}, {     15, 7}, {     35, 8}, \
    {     19, 7}, {     41, 8}, {     23, 7}, {     49, 8}, \
    {     27, 7}, {     55, 9}, {     15, 8}, {     31, 7}, \
    {     63, 8}, {     43, 9}, {     23, 8}, {     55, 9}, \
    {     31, 8}, {     67, 9}, {     39, 8}, {     83, 9}, \
    {     47, 8}, {     95, 9}, {     55,10}, {     31, 9}, \
    {     79,10}, {     47, 9}, {     95,11}, {     31,10}, \
    {     63, 9}, {    135,10}, {     79, 9}, {    159,10}, \
    {     95, 9}, {    191,11}, {     63,10}, {    159,11}, \
    {     95,10}, {    191,12}, {     63,11}, {    127,10}, \
    {    255, 9}, {    511,10}, {    271, 9}, {    543,11}, \
    {    159,10}, {    335,11}, {    191,10}, {    399,11}, \
    {    223,12}, {   4096,13}, {   8192,14}, {  16384,15}, \
    {  32768,16} }
#define MUL_FFT_TABLE3_SIZE 65
#define MUL_FFT_THRESHOLD                 6784

#define SQR_FFT_MODF_THRESHOLD             555  /* k = 5 */
#define SQR_FFT_TABLE3                                      \
  { {    555, 5}, {     28, 6}, {     15, 5}, {     32, 6}, \
    {     29, 7}, {     15, 6}, {     33, 7}, {     17, 6}, \
    {     36, 7}, {     19, 6}, {     39, 7}, {     21, 6}, \
    {     43, 7}, {     29, 8}, {     15, 7}, {     35, 8}, \
    {     19, 7}, {     43, 8}, {     23, 7}, {     49, 8}, \
    {     31, 7}, {     63, 8}, {     43, 9}, {     23, 8}, \
    {     55, 9}, {     31, 8}, {     67, 9}, {     39, 8}, \
    {     79, 9}, {     47, 8}, {     95, 9}, {     55,10}, \
    {     31, 9}, {     79,10}, {     47, 9}, {     95,11}, \
    {     31,10}, {     63, 9}, {    135,10}, {     79, 9}, \
    {    159,10}, {     95,11}, {     63,10}, {    143,11}, \
    {     95,12}, {     63,11}, {    127,10}, {    255, 9}, \
    {    511,10}, {    271, 9}, {    543,10}, {    287,11}, \
    {    159,10}, {    335, 9}, {    671,11}, {    191,10}, \
    {    399, 9}, {    799,10}, {    415,11}, {    223,12}, \
    {   4096,13}, {   8192,14}, {  16384,15}, {  32768,16} }
#define SQR_FFT_TABLE3_SIZE 64
#define SQR_FFT_THRESHOLD                 5760

#define MULLO_BASECASE_THRESHOLD             3
#define MULLO_DC_THRESHOLD                  35
#define MULLO_MUL_N_THRESHOLD            13463
#define SQRLO_BASECASE_THRESHOLD             8
#define SQRLO_DC_THRESHOLD                  41
#define SQRLO_SQR_THRESHOLD              11278

#define DC_DIV_QR_THRESHOLD                 78
#define DC_DIVAPPR_Q_THRESHOLD             200
#define DC_BDIV_QR_THRESHOLD                75
#define DC_BDIV_Q_THRESHOLD                119

#define INV_MULMOD_BNM1_THRESHOLD           66
#define INV_NEWTON_THRESHOLD               274
#define INV_APPR_THRESHOLD                 220

#define BINV_NEWTON_THRESHOLD              288
#define REDC_1_TO_REDC_N_THRESHOLD          74

#define MU_DIV_QR_THRESHOLD               1652
#define MU_DIVAPPR_Q_THRESHOLD            1589
#define MUPI_DIV_QR_THRESHOLD              122
#define MU_BDIV_QR_THRESHOLD              1442
#define MU_BDIV_Q_THRESHOLD               1506

#define POWM_SEC_TABLE  3,22,96,398,865

#define GET_STR_DC_THRESHOLD                12
#define GET_STR_PRECOMPUTE_THRESHOLD        19
#define SET_STR_DC_THRESHOLD               236
#define SET_STR_PRECOMPUTE_THRESHOLD       463

#define FAC_DSC_THRESHOLD                   95
#define FAC_ODD_THRESHOLD                   34

#define MATRIX22_STRASSEN_THRESHOLD         19
#define HGCD2_DIV1_METHOD                    1  /* 8.21% faster than 3 */
#define HGCD_THRESHOLD                      59
#define HGCD_APPR_THRESHOLD                 50
#define HGCD_REDUCE_THRESHOLD             3389
#define GCD_DC_THRESHOLD                   511
#define GCDEXT_DC_THRESHOLD                351
#define JACOBI_BASE_METHOD                   4  /* 15.43% faster than 1 */
