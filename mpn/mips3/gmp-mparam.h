/* gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 1999, 2000, 2001 Free Software Foundation, Inc.

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


/* Generated by tuneup.c, 2001-02-23, MIPSpro C 7.2.1 (R10000) */

#define KARATSUBA_MUL_THRESHOLD       13
#define TOOM3_MUL_THRESHOLD           82

#define BASECASE_SQR_THRESHOLD         6
#define KARATSUBA_SQR_THRESHOLD       28
#define TOOM3_SQR_THRESHOLD           93

#define SB_PREINV_THRESHOLD            4
#define DC_THRESHOLD                  48
#define POWM_THRESHOLD                97

#define GCD_ACCEL_THRESHOLD            3
#define GCDEXT_THRESHOLD              21

#define DIVREM_1_NORM_THRESHOLD        3
#define DIVREM_1_UNNORM_THRESHOLD      3
#define MOD_1_NORM_THRESHOLD           3
#define MOD_1_UNNORM_THRESHOLD         3
#define USE_PREINV_MOD_1               1
#define DIVREM_2_THRESHOLD             0
#define MODEXACT_1_ODD_THRESHOLD       0

#define FFT_MUL_TABLE  { 464, 992, 2112, 4352, 9216, 28672, 0 }
#define FFT_MODF_MUL_THRESHOLD       480
#define FFT_MUL_THRESHOLD           3456

#define FFT_SQR_TABLE  { 432, 864, 1984, 3840, 9216, 28672, 0 }
#define FFT_MODF_SQR_THRESHOLD       448
#define FFT_SQR_THRESHOLD           2944
