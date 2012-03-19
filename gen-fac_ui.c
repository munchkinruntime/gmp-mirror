/* Generate mpz_fac_ui data.

Copyright 2002, 2011, 2012 Free Software Foundation, Inc.

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

#include <stdio.h>
#include <stdlib.h>

#include "bootstrap.c"


/* x=floor(y^(1/z)) */
void
mpz_root (mpz_t x, mpz_t y, unsigned long z)
{
  mpz_t t, u, v;

  if (mpz_cmp_ui (y, 1) <= 0)
    {
      mpz_set (x, y);
      return;
    }
  mpz_init (t);
  mpz_init (v);
  mpz_init_set_ui (u, 1);
  mpz_mul_2exp (u, u, mpz_sizeinbase (y, 2) / z + 1);
  do
    {
      mpz_pow_ui (t, u, z - 1);
      mpz_tdiv_q (t, y, t);
      mpz_mul_ui (v, u, z - 1);
      mpz_add (t, t, v);
      mpz_tdiv_q_ui (t, t, z);
      if (mpz_cmp (t, u) >= 0)
	break;
      mpz_set (u, t);
    }
  while (1);
  mpz_set (x, u);
  mpz_clear (u);
  mpz_clear (v);
  mpz_clear (t);
}

/* returns 0 on success		*/
int
gen_consts (int numb, int nail, int limb)
{
  mpz_t x, y, z, t;
  unsigned long a, b;

  printf ("/* This file is automatically generated by gen-fac_ui.c */\n\n");
  printf ("#if GMP_NUMB_BITS != %d\n", numb);
  printf ("Error , error this data is for %d GMP_NUMB_BITS only\n", numb);
  printf ("#endif\n");
  printf ("#if GMP_LIMB_BITS != %d\n", limb);
  printf ("Error , error this data is for %d GMP_LIMB_BITS only\n", limb);
  printf ("#endif\n");

  printf
    ("/* This table is 0!,1!,2!,3!,...,n! where n! has <= GMP_NUMB_BITS bits */\n");
  printf
    ("#define ONE_LIMB_FACTORIAL_TABLE CNST_LIMB(0x1),CNST_LIMB(0x1");
  mpz_init_set_ui (x, 1);
  for (b = 2;; b++)
    {
      mpz_mul_ui (x, x, b);	/* so b!=a       */
      if (mpz_sizeinbase (x, 2) > numb)
	break;
      printf ("),CNST_LIMB(0x");
      mpz_out_str (stdout, 16, x);
    }
  printf (")\n");

  printf
    ("\n/* This table is 0!,1!,2!/2,3!/2,...,n!/2^sn where n!/2^sn is an */\n");
  printf
    ("/* odd integer for each n, and n!/2^sn has <= GMP_NUMB_BITS bits */\n");
  printf
    ("#define ONE_LIMB_ODD_FACTORIAL_TABLE CNST_LIMB(0x1),CNST_LIMB(0x1),CNST_LIMB(0x1");
  mpz_set_ui (x, 1);
  for (b = 3;; b++)
    {
      for (a = b; (a & 1) == 0; a >>= 1);
      mpz_mul_ui (x, x, a);
      if (mpz_sizeinbase (x, 2) > numb)
	break;
      printf ("),CNST_LIMB(0x");
      mpz_out_str (stdout, 16, x);
    }
  printf (")\n");

  printf
    ("\n/* This table is 1!!,3!!,...,(2n+1)!! where (2n+1)!! has <= GMP_NUMB_BITS bits */\n");
  printf
    ("#define ONE_LIMB_ODD_DOUBLEFACTORIAL_TABLE CNST_LIMB(0x1");
  mpz_set_ui (x, 1);
  for (b = 3;; b+=2)
    {
      mpz_mul_ui (x, x, b);
      if (mpz_sizeinbase (x, 2) > numb)
	break;
      printf ("),CNST_LIMB(0x");
      mpz_out_str (stdout, 16, x);
    }
  printf (")\n");

  printf
    ("\n/* This table x_1, x_2,... contains values s.t. x_n^n has <= GMP_NUMB_BITS bits */\n");
  printf
    ("#define NTH_ROOT_NUMB_MASK_TABLE (GMP_NUMB_MASK");
  for (b = 2;b <= 8; b++)
    {
      mpz_set_ui (x, 1);
      mpz_mul_2exp (x, x, numb);
      mpz_sub_ui (x, x, 1);
      mpz_root (x, x, b);
      if (mpz_sizeinbase (x, 2) < 4)
	break;
      printf ("),CNST_LIMB(0x");
      mpz_out_str (stdout, 16, x);
    }
  printf (")\n");

#if 0
  mpz_set_ui (x, 1);
  mpz_mul_2exp (x, x, limb + 1);	/* x=2^(limb+1)        */
  mpz_init (y);
  mpz_set_ui (y, 10000);
  mpz_mul (x, x, y);		/* x=2^(limb+1)*10^4     */
  mpz_set_ui (y, 27182);	/* exp(1)*10^4      */
  mpz_tdiv_q (x, x, y);		/* x=2^(limb+1)/exp(1)        */
  printf ("\n/* is 2^(GMP_LIMB_BITS+1)/exp(1) */\n");
  printf ("#define FAC2OVERE CNST_LIMB(0x");
  mpz_out_str (stdout, 16, x);
  printf (")\n");


  printf
    ("\n/* FACMULn is largest odd x such that x*(x+2)*...*(x+2(n-1))<=2^GMP_NUMB_BITS-1 */\n\n");
  mpz_init (z);
  mpz_init (t);
  for (a = 2; a <= 4; a++)
    {
      mpz_set_ui (x, 1);
      mpz_mul_2exp (x, x, numb);
      mpz_root (x, x, a);
      /* so x is approx sol       */
      if (mpz_even_p (x))
	mpz_sub_ui (x, x, 1);
      mpz_set_ui (y, 1);
      mpz_mul_2exp (y, y, numb);
      mpz_sub_ui (y, y, 1);
      /* decrement x until we are <= real sol     */
      do
	{
	  mpz_sub_ui (x, x, 2);
	  odd_products (t, x, a);
	  if (mpz_cmp (t, y) <= 0)
	    break;
	}
      while (1);
      /* increment x until > real sol     */
      do
	{
	  mpz_add_ui (x, x, 2);
	  odd_products (t, x, a);
	  if (mpz_cmp (t, y) > 0)
	    break;
	}
      while (1);
      /* dec once to get real sol */
      mpz_sub_ui (x, x, 2);
      printf ("#define FACMUL%lu CNST_LIMB(0x", a);
      mpz_out_str (stdout, 16, x);
      printf (")\n");
    }
#endif

  return 0;
}

int
main (int argc, char *argv[])
{
  int nail_bits, limb_bits, numb_bits;

  if (argc != 3)
    {
      fprintf (stderr, "Usage: gen-fac_ui limbbits nailbits\n");
      exit (1);
    }
  limb_bits = atoi (argv[1]);
  nail_bits = atoi (argv[2]);
  numb_bits = limb_bits - nail_bits;
  if (limb_bits < 2 || nail_bits < 0 || numb_bits < 1)
    {
      fprintf (stderr, "Invalid limb/nail bits %d,%d\n", limb_bits,
	       nail_bits);
      exit (1);
    }
  gen_consts (numb_bits, nail_bits, limb_bits);
  return 0;
}
