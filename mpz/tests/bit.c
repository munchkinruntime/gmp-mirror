/* Test mpz_setbit, mpz_clrbit, mpz_tstbit.

Copyright 1997, 2000 Free Software Foundation, Inc.

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

#include <stdio.h>
#include "gmp.h"
#include "gmp-impl.h"
#include "urandom.h"

#ifndef SIZE
#define SIZE 4
#endif


void
debug_mp (mpz_srcptr x, int base)
{
  mpz_out_str (stdout, base, x); fputc ('\n', stdout);
}

/* twos complement, return borrow */
mp_limb_t
mpn_neg (mp_ptr dst, mp_srcptr src, mp_size_t size)
{
  mpn_com_n (dst, src, size);
  return mpn_add_1 (dst, dst, size, 1) ^ 1;
}

mp_limb_t
mpn_tstbit (mp_srcptr ptr, mp_size_t size)
{
  return (ptr[size/BITS_PER_MP_LIMB]
          & (CNST_LIMB(1) << size%BITS_PER_MP_LIMB)) != 0;
}

void
mpz_set_n (mpz_ptr z, mp_srcptr p, mp_size_t size)
{
  ASSERT (size >= 0);
  MPN_NORMALIZE (p, size);
  MPZ_REALLOC (z, size);
  MPN_COPY (PTR(z), p, size);
  SIZ(z) = size;
}


/* See that mpz_tstbit matches a twos complement calculated explicitly, for
   various low zeros.  */
void
check_tstbit (void)
{
#define MAX_ZEROS  3
#define NUM_LIMBS  3

  mp_limb_t      pos[1+NUM_LIMBS+MAX_ZEROS];
  mp_limb_t      neg[1+NUM_LIMBS+MAX_ZEROS];
  mpz_t          z;
  unsigned long  i;
  int            zeros, low1;
  int            got, want;

  mpz_init (z);
  for (zeros = 0; zeros <= MAX_ZEROS; zeros++)
    {
      MPN_ZERO (pos, numberof(pos));
      mpn_random2 (pos+zeros, NUM_LIMBS);

      for (low1 = 0; low1 <= 1; low1++)
        {
          if (low1)
            pos[0] |= 1;

          mpn_neg (neg, pos, numberof(neg));
          mpz_set_n (z, neg, numberof(neg));
          mpz_neg (z, z);

          for (i = 0; i < numberof(pos)*BITS_PER_MP_LIMB; i++)
            {
              got = mpz_tstbit (z, i);
              want = mpn_tstbit (pos, i);
              if (got != want)
                {
                  printf ("wrong at bit %lu, with %d zeros\n", i, zeros);
                  printf ("z neg "); debug_mp (z, -16);
                  mpz_set_n (z, pos, numberof(pos));
                  printf ("pos   "); debug_mp (z, -16);
                  mpz_set_n (z, neg, numberof(neg));
                  printf ("neg   "); debug_mp (z, -16);
                  exit (1);
                }
            }
        }
    }
  mpz_clear (z);
}

int
main (int argc, char *argv[])
{
  mpz_t x, s0, s1, s2, s3, m;
  mp_size_t xsize;
  int i;
  int reps = 100000;
  int bit0, bit1, bit2, bit3;
  unsigned long int bitindex;
  const char  *s = "";

  if (argc == 2)
    reps = atoi (argv[1]);

  check_tstbit ();

  mpz_init (x);
  mpz_init (s0);
  mpz_init (s1);
  mpz_init (s2);
  mpz_init (s3);
  mpz_init (m);

  for (i = 0; i < reps; i++)
    {
      xsize = urandom () % (2 * SIZE) - SIZE;
      mpz_random2 (x, xsize);
      bitindex = urandom () % SIZE;

      mpz_set (s0, x);
      bit0 = mpz_tstbit (x, bitindex);
      mpz_setbit (x, bitindex);
      MPZ_CHECK_FORMAT (x);

      mpz_set (s1, x);
      bit1 = mpz_tstbit (x, bitindex);
      mpz_clrbit (x, bitindex);
      MPZ_CHECK_FORMAT (x);

      mpz_set (s2, x);
      bit2 = mpz_tstbit (x, bitindex);
      mpz_setbit (x, bitindex);
      MPZ_CHECK_FORMAT (x);

      mpz_set (s3, x);
      bit3 = mpz_tstbit (x, bitindex);

#define FAIL(str) do { s = str; goto fail; } while (0)

      if (bit1 != 1)  FAIL ("bit1 != 1");
      if (bit2 != 0)  FAIL ("bit2 != 0");
      if (bit3 != 1)  FAIL ("bit3 != 1");

      if (bit0 == 0)
	{
	  if (mpz_cmp (s0, s1) == 0 || mpz_cmp (s0, s2) != 0 || mpz_cmp (s0, s3) == 0)
	    abort ();
	}
      else
	{
	  if (mpz_cmp (s0, s1) != 0 || mpz_cmp (s0, s2) == 0 || mpz_cmp (s0, s3) != 0)
	    abort ();
	}

      if (mpz_cmp (s1, s2) == 0 || mpz_cmp (s1, s3) != 0)
	abort ();
      if (mpz_cmp (s2, s3) == 0)
	abort ();

      mpz_ui_pow_ui (m, 2L, bitindex);
      MPZ_CHECK_FORMAT (m);
      mpz_ior (x, s2, m);
      MPZ_CHECK_FORMAT (x);
      if (mpz_cmp (x, s3) != 0)
	abort ();

      mpz_com (m, m);
      MPZ_CHECK_FORMAT (m);
      mpz_and (x, s1, m);
      MPZ_CHECK_FORMAT (x);
      if (mpz_cmp (x, s2) != 0)
	abort ();
    }

  exit (0);


 fail:
  printf ("%s\n", s);
  printf ("bitindex = %lu\n", bitindex);
  printf ("x = "); mpz_out_str (stdout, -16, x); printf (" hex\n");
  exit (1);
}
