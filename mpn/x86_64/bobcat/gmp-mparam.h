/* AMD Bobcat gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 2000-2012 Free Software Foundation, Inc.

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

#define GMP_LIMB_BITS 64
#define GMP_LIMB_BYTES 8

#undef HAVE_NATIVE_mpn_mul_2
#undef HAVE_NATIVE_mpn_addmul_2

/* 1600 MHz AMD Bobcat E-350 */

#define MOD_1_NORM_THRESHOLD                 0  /* always */
#define MOD_1_UNNORM_THRESHOLD               0  /* always */
#define MOD_1N_TO_MOD_1_1_THRESHOLD          3
#define MOD_1U_TO_MOD_1_1_THRESHOLD          2
#define MOD_1_1_TO_MOD_1_2_THRESHOLD        31
#define MOD_1_2_TO_MOD_1_4_THRESHOLD         0  /* never mpn_mod_1s_2p */
#define PREINV_MOD_1_TO_MOD_1_THRESHOLD      7
#define USE_PREINV_DIVREM_1                  1  /* native */
#define DIV_QR_1_NORM_THRESHOLD              1
#define DIV_QR_1_UNNORM_THRESHOLD        MP_SIZE_T_MAX  /* never */
#define DIV_QR_2_PI2_THRESHOLD           MP_SIZE_T_MAX  /* never */
#define DIVEXACT_1_THRESHOLD                 0  /* always (native) */
#define BMOD_1_TO_MOD_1_THRESHOLD           17

#define MUL_TOOM22_THRESHOLD                27
#define MUL_TOOM33_THRESHOLD                32
#define MUL_TOOM44_THRESHOLD               172
#define MUL_TOOM6H_THRESHOLD               357
#define MUL_TOOM8H_THRESHOLD                 0  /* always */

#define MUL_TOOM32_TO_TOOM43_THRESHOLD     113
#define MUL_TOOM32_TO_TOOM53_THRESHOLD     120
#define MUL_TOOM42_TO_TOOM53_THRESHOLD     119
#define MUL_TOOM42_TO_TOOM63_THRESHOLD     181
#define MUL_TOOM43_TO_TOOM54_THRESHOLD     160

#define SQR_BASECASE_THRESHOLD               0  /* always (native) */
#define SQR_TOOM2_THRESHOLD                 28
#define SQR_TOOM3_THRESHOLD                 93
#define SQR_TOOM4_THRESHOLD                390
#define SQR_TOOM6_THRESHOLD                  0  /* always */
#define SQR_TOOM8_THRESHOLD                434

#define MULMID_TOOM42_THRESHOLD             22

#define MULMOD_BNM1_THRESHOLD               11
#define SQRMOD_BNM1_THRESHOLD               13

#define MUL_FFT_MODF_THRESHOLD             404  /* k = 5 */
#define MUL_FFT_TABLE3                                      \
  { {    404, 5}, {     19, 6}, {     10, 5}, {     21, 6}, \
    {     11, 5}, {     23, 6}, {     25, 7}, {     15, 6}, \
    {     31, 7}, {     21, 8}, {     11, 7}, {     25, 8}, \
    {     13, 7}, {     28, 8}, {     15, 7}, {     31, 8}, \
    {     17, 7}, {     35, 8}, {     19, 7}, {     39, 8}, \
    {     29, 9}, {     15, 8}, {     35, 9}, {     19, 8}, \
    {     41, 9}, {     23, 8}, {     47, 9}, {     27,10}, \
    {     15, 9}, {     31, 8}, {     63, 9}, {     39,10}, \
    {     23, 9}, {     55,11}, {     15,10}, {     31, 9}, \
    {     67,10}, {     39, 9}, {     83,10}, {     47, 9}, \
    {     95,10}, {     55,11}, {     31,10}, {     79,11}, \
    {     47,10}, {     95,12}, {     31,11}, {     63,10}, \
    {    143,11}, {     79,10}, {    159,11}, {    111,12}, \
    {     63,11}, {    127,10}, {    255, 9}, {    511,10}, \
    {    271,11}, {    143,10}, {    287,11}, {    159,12}, \
    {     95,11}, {    191,10}, {    383,11}, {    207,13}, \
    {   8192,14}, {  16384,15}, {  32768,16}, {  65536,17}, \
    { 131072,18}, { 262144,19}, { 524288,20}, {1048576,21}, \
    {2097152,22}, {4194304,23}, {8388608,24} }
#define MUL_FFT_TABLE3_SIZE 75
#define MUL_FFT_THRESHOLD                 5760

#define SQR_FFT_MODF_THRESHOLD             404  /* k = 5 */
#define SQR_FFT_TABLE3                                      \
  { {    404, 5}, {     21, 6}, {     11, 5}, {     23, 6}, \
    {     25, 7}, {     25, 8}, {     13, 7}, {     27, 8}, \
    {     15, 7}, {     31, 8}, {     17, 7}, {     35, 8}, \
    {     19, 7}, {     39, 8}, {     27, 9}, {     15, 8}, \
    {     35, 9}, {     19, 8}, {     41, 9}, {     23, 8}, \
    {     47, 9}, {     27,10}, {     15, 9}, {     39,10}, \
    {     23, 9}, {     51,11}, {     15,10}, {     31, 9}, \
    {     67,10}, {     39, 9}, {     83,10}, {     47, 9}, \
    {     95,10}, {     55,11}, {     31,10}, {     79,11}, \
    {     47,10}, {     95,12}, {     31,11}, {     63,10}, \
    {    135,11}, {     79,10}, {    159,11}, {    111,12}, \
    {     63,11}, {    127,10}, {    271,11}, {    143,10}, \
    {    303,11}, {    159,12}, {     95,10}, {    383,11}, \
    {    207,13}, {   8192,14}, {  16384,15}, {  32768,16}, \
    {  65536,17}, { 131072,18}, { 262144,19}, { 524288,20}, \
    {1048576,21}, {2097152,22}, {4194304,23}, {8388608,24} }
#define SQR_FFT_TABLE3_SIZE 64
#define SQR_FFT_THRESHOLD                 3712

#define MULLO_BASECASE_THRESHOLD             0  /* always */
#define MULLO_DC_THRESHOLD                  30
#define MULLO_MUL_N_THRESHOLD            11278

#define DC_DIV_QR_THRESHOLD                 77
#define DC_DIVAPPR_Q_THRESHOLD             204
#define DC_BDIV_QR_THRESHOLD                70
#define DC_BDIV_Q_THRESHOLD                153

#define INV_MULMOD_BNM1_THRESHOLD           85
#define INV_NEWTON_THRESHOLD               250
#define INV_APPR_THRESHOLD                 212

#define BINV_NEWTON_THRESHOLD              254
#define REDC_1_TO_REDC_2_THRESHOLD          71
#define REDC_2_TO_REDC_N_THRESHOLD           0  /* always */

#define MU_DIV_QR_THRESHOLD               1528
#define MU_DIVAPPR_Q_THRESHOLD            1558
#define MUPI_DIV_QR_THRESHOLD              108
#define MU_BDIV_QR_THRESHOLD              1387
#define MU_BDIV_Q_THRESHOLD               1470

#define POWM_SEC_TABLE  1,10,64,712,1035

#define MATRIX22_STRASSEN_THRESHOLD         18
#define HGCD_THRESHOLD                      69
#define HGCD_APPR_THRESHOLD                 50
#define HGCD_REDUCE_THRESHOLD             3014
#define GCD_DC_THRESHOLD                   501
#define GCDEXT_DC_THRESHOLD                321
#define JACOBI_BASE_METHOD                   4

#define GET_STR_DC_THRESHOLD                19
#define GET_STR_PRECOMPUTE_THRESHOLD        32
#define SET_STR_DC_THRESHOLD               286
#define SET_STR_PRECOMPUTE_THRESHOLD      1397

#define FAC_DSC_THRESHOLD                 1005
#define FAC_ODD_THRESHOLD                   46
