/* SPARC v8 gmp-mparam.h -- Compiler/machine parameter header file.

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


#define BITS_PER_MP_LIMB 32
#define BYTES_PER_MP_LIMB 4

/* These numbers were obtained on gnistan.sics.se, a MicroSPARC II system */
/* Generated by tuneup.c, 2000-10-09. */

#ifndef KARATSUBA_MUL_THRESHOLD
#define KARATSUBA_MUL_THRESHOLD     10
#endif
#ifndef TOOM3_MUL_THRESHOLD
#define TOOM3_MUL_THRESHOLD        101
#endif

#ifndef KARATSUBA_SQR_THRESHOLD
#define KARATSUBA_SQR_THRESHOLD     20
#endif
#ifndef TOOM3_SQR_THRESHOLD
#define TOOM3_SQR_THRESHOLD        116
#endif

#ifndef DC_THRESHOLD
#define DC_THRESHOLD                32
#endif

#ifndef POWM_THRESHOLD
#define POWM_THRESHOLD              29
#endif

#ifndef GCD_ACCEL_THRESHOLD
#define GCD_ACCEL_THRESHOLD          6
#endif
#ifndef GCDEXT_THRESHOLD
#define GCDEXT_THRESHOLD            32
#endif
