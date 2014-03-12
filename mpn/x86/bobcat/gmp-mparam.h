/* x86/bobcat gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 2000-2011 Free Software Foundation, Inc.

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

/* Generated by tuneup.c, 2014-03-12, gcc 4.5 */

#define MOD_1_NORM_THRESHOLD                 0  /* always */
#define MOD_1_UNNORM_THRESHOLD               0  /* always */
#define MOD_1N_TO_MOD_1_1_THRESHOLD         12
#define MOD_1U_TO_MOD_1_1_THRESHOLD          5
#define MOD_1_1_TO_MOD_1_2_THRESHOLD        16
#define MOD_1_2_TO_MOD_1_4_THRESHOLD         0  /* never mpn_mod_1s_2p */
#define PREINV_MOD_1_TO_MOD_1_THRESHOLD     16
#define USE_PREINV_DIVREM_1                  1  /* native */
#define DIV_QR_1N_PI1_METHOD                 1
#define DIV_QR_1_NORM_THRESHOLD              2
#define DIV_QR_1_UNNORM_THRESHOLD        MP_SIZE_T_MAX  /* never */
#define DIV_QR_2_PI2_THRESHOLD           MP_SIZE_T_MAX  /* never */
#define DIVEXACT_1_THRESHOLD                 0  /* always (native) */
#define BMOD_1_TO_MOD_1_THRESHOLD           40

#define MUL_TOOM22_THRESHOLD                28
#define MUL_TOOM33_THRESHOLD                90
#define MUL_TOOM44_THRESHOLD               154
#define MUL_TOOM6H_THRESHOLD               270
#define MUL_TOOM8H_THRESHOLD               490

#define MUL_TOOM32_TO_TOOM43_THRESHOLD      89
#define MUL_TOOM32_TO_TOOM53_THRESHOLD     107
#define MUL_TOOM42_TO_TOOM53_THRESHOLD      95
#define MUL_TOOM42_TO_TOOM63_THRESHOLD     110
#define MUL_TOOM43_TO_TOOM54_THRESHOLD     130

#define SQR_BASECASE_THRESHOLD               0  /* always (native) */
#define SQR_TOOM2_THRESHOLD                 38
#define SQR_TOOM3_THRESHOLD                121
#define SQR_TOOM4_THRESHOLD                212
#define SQR_TOOM6_THRESHOLD                303
#define SQR_TOOM8_THRESHOLD                454

#define MULMID_TOOM42_THRESHOLD             74

#define MULMOD_BNM1_THRESHOLD               18
#define SQRMOD_BNM1_THRESHOLD               23

#define MUL_FFT_MODF_THRESHOLD             654  /* k = 5 */
#define MUL_FFT_TABLE3                                      \
  { {    654, 5}, {     25, 6}, {     13, 5}, {     27, 6}, \
    {     27, 7}, {     15, 6}, {     33, 7}, {     17, 6}, \
    {     35, 7}, {     19, 6}, {     39, 7}, {     23, 6}, \
    {     47, 7}, {     27, 8}, {     15, 7}, {     35, 8}, \
    {     19, 7}, {     41, 8}, {     23, 7}, {     49, 8}, \
    {     31, 7}, {     63, 8}, {     39, 9}, {     23, 8}, \
    {     55, 9}, {     31, 8}, {     67, 9}, {     39, 8}, \
    {     79, 9}, {     47, 8}, {     95, 9}, {     55,10}, \
    {     31, 9}, {     63, 8}, {    127, 9}, {     79,10}, \
    {     47, 9}, {    103,11}, {     31,10}, {     63, 9}, \
    {    135,10}, {     79, 9}, {    159,10}, {     95, 9}, \
    {    199,10}, {    111,11}, {     63,10}, {    159,11}, \
    {     95,10}, {    191,12}, {     63,11}, {    127,10}, \
    {    255, 9}, {    511,10}, {    271, 9}, {    543, 8}, \
    {   1087,11}, {    159, 9}, {    639,10}, {    335, 9}, \
    {    671,11}, {    191,10}, {    383, 9}, {    767,10}, \
    {    399, 9}, {    799,11}, {    223,12}, {    127,11}, \
    {    255,10}, {    543, 9}, {   1087,11}, {    287,10}, \
    {    607, 9}, {   1215,10}, {    671,12}, {    191,11}, \
    {    383,10}, {    799,11}, {    415,13}, {    127,12}, \
    {    255,11}, {    543,10}, {   1087,11}, {    607,10}, \
    {   1215,11}, {    671,10}, {   1343,11}, {    735,10}, \
    {   1471,12}, {    383,11}, {    799,10}, {   1599,11}, \
    {    863,12}, {    447,11}, {    991,13}, {    255,12}, \
    {    511,11}, {   1087,12}, {    575,11}, {   1215,12}, \
    {    639,11}, {   1343,12}, {    703,11}, {   1471,13}, \
    {    383,12}, {    767,11}, {   1599,12}, {    831,11}, \
    {   1727,12}, {    959,14}, {    255,13}, {    511,12}, \
    {   1215,13}, {    639,12}, {   1471,13}, {    767,12}, \
    {   1727,13}, {    895,12}, {   1919,14}, {    511,13}, \
    {   1023,12}, {   2111,13}, {   1151,12}, {   2431,13}, \
    {   8192,14}, {  16384,15}, {  32768,16} }
#define MUL_FFT_TABLE3_SIZE 127
#define MUL_FFT_THRESHOLD                 7552

#define SQR_FFT_MODF_THRESHOLD             606  /* k = 5 */
#define SQR_FFT_TABLE3                                      \
  { {    606, 5}, {     28, 6}, {     15, 5}, {     31, 6}, \
    {     28, 7}, {     15, 6}, {     33, 7}, {     17, 6}, \
    {     35, 7}, {     19, 6}, {     39, 7}, {     23, 6}, \
    {     47, 7}, {     29, 8}, {     15, 7}, {     35, 8}, \
    {     19, 7}, {     41, 8}, {     23, 7}, {     49, 8}, \
    {     31, 7}, {     63, 8}, {     43, 9}, {     23, 8}, \
    {     55, 9}, {     31, 8}, {     67, 9}, {     39, 8}, \
    {     79, 9}, {     47, 8}, {     95, 9}, {     55,10}, \
    {     31, 9}, {     79,10}, {     47, 9}, {    103,11}, \
    {     31,10}, {     63, 9}, {    135,10}, {     79, 9}, \
    {    159,10}, {     95, 9}, {    191,11}, {     63,10}, \
    {    159,11}, {     95,10}, {    191,12}, {     63,11}, \
    {    127,10}, {    255, 9}, {    511,10}, {    271, 9}, \
    {    543, 8}, {   1087,11}, {    159,10}, {    319, 9}, \
    {    639,10}, {    335, 9}, {    671, 8}, {   1343,10}, \
    {    351,11}, {    191,10}, {    383, 9}, {    767,10}, \
    {    399, 9}, {    799, 8}, {   1599,10}, {    415,12}, \
    {    127,11}, {    255,10}, {    511, 9}, {   1023,10}, \
    {    543, 9}, {   1087,11}, {    287,10}, {    607, 9}, \
    {   1215,11}, {    319,10}, {    671, 9}, {   1343,12}, \
    {    191,11}, {    383,10}, {    799,11}, {    415,10}, \
    {    831,13}, {    127,12}, {    255,11}, {    511,10}, \
    {   1023,11}, {    543,10}, {   1087,11}, {    607,10}, \
    {   1215,12}, {    319,11}, {    671,10}, {   1343,11}, \
    {    735,10}, {   1471,12}, {    383,11}, {    799,10}, \
    {   1599,11}, {    863,12}, {    447,11}, {    991,13}, \
    {    255,12}, {    511,11}, {   1087,12}, {    575,11}, \
    {   1215,12}, {    639,11}, {   1343,12}, {    703,11}, \
    {   1471,13}, {    383,12}, {    767,11}, {   1599,12}, \
    {    831,11}, {   1727,12}, {    959,14}, {    255,13}, \
    {    511,12}, {   1215,13}, {    639,12}, {   1471,13}, \
    {    767,12}, {   1727,13}, {    895,12}, {   1983,14}, \
    {    511,13}, {   1023,12}, {   2111,13}, {   1151,12}, \
    {   2431,13}, {   8192,14}, {  16384,15}, {  32768,16} }
#define SQR_FFT_TABLE3_SIZE 136
#define SQR_FFT_THRESHOLD                 5760

#define MULLO_BASECASE_THRESHOLD             5
#define MULLO_DC_THRESHOLD                  45
#define MULLO_MUL_N_THRESHOLD            14281

#define DC_DIV_QR_THRESHOLD                 71
#define DC_DIVAPPR_Q_THRESHOLD             238
#define DC_BDIV_QR_THRESHOLD                67
#define DC_BDIV_Q_THRESHOLD                151

#define INV_MULMOD_BNM1_THRESHOLD           66
#define INV_NEWTON_THRESHOLD               228
#define INV_APPR_THRESHOLD                 222

#define BINV_NEWTON_THRESHOLD              270
#define REDC_1_TO_REDC_N_THRESHOLD          71

#define MU_DIV_QR_THRESHOLD               1718
#define MU_DIVAPPR_Q_THRESHOLD            1718
#define MUPI_DIV_QR_THRESHOLD               91
#define MU_BDIV_QR_THRESHOLD              1589
#define MU_BDIV_Q_THRESHOLD               1718

#define POWM_SEC_TABLE  1,16,96,416,1185

#define MATRIX22_STRASSEN_THRESHOLD         17
#define HGCD_THRESHOLD                      88
#define HGCD_APPR_THRESHOLD                137
#define HGCD_REDUCE_THRESHOLD             3664
#define GCD_DC_THRESHOLD                   465
#define GCDEXT_DC_THRESHOLD                345
#define JACOBI_BASE_METHOD                   4

#define GET_STR_DC_THRESHOLD                18
#define GET_STR_PRECOMPUTE_THRESHOLD        34
#define SET_STR_DC_THRESHOLD               270
#define SET_STR_PRECOMPUTE_THRESHOLD       828

#define FAC_DSC_THRESHOLD                  256
#define FAC_ODD_THRESHOLD                   34
