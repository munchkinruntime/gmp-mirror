/* Include file for internal GNU MP types and definitions.

   THE CONTENTS OF THIS FILE ARE FOR INTERNAL USE AND ARE ALMOST CERTAIN TO
   BE SUBJECT TO INCOMPATIBLE CHANGES IN FUTURE GNU MP RELEASES.

Copyright 1991, 1993, 1994, 1995, 1996, 1997, 1999, 2000 Free Software
Foundation, Inc.

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


#ifndef __GMP_IMPL_H__
#define __GMP_IMPL_H__

/* When used from the GMP_FUNC_ALLOC test, config.h doesn't exist, but the
   equivalent definitions will have come from confdefs.h included at the
   start of the test program.  */
#if ! GMP_FUNC_ALLOCA_TEST
#include "config.h"
#include "gmp-mparam.h"
#endif

/* #include "longlong.h" */


/* The following tries to get a good version of alloca.  The tests are
   adapted from autoconf AC_FUNC_ALLOCA, with a couple of additions.
   Whether this succeeds is tested by GMP_FUNC_ALLOCA and HAVE_ALLOCA will
   be setup appropriately.

   ifndef alloca - a cpp define might already exist.  glibc <stdlib.h>
       includes <alloca.h> which uses GCC __builtin_alloca.  HP cc
       +Olibcalls supposedly provides a #define.

   GCC __builtin_alloca - preferred whenever available.

   _AIX pragma - IBM compilers need a #pragma in "each module that needs to
       use alloca".  Pragma indented to protect pre-ANSI cpp's.  _IBMR2 was
       used in past versions of GMP, retained still in case it matters.

       The autoconf manual says this pragma needs to be at the start of a C
       file, apart from comments and preprocessor directives.  Is that true?
       xlc on aix 4.xxx doesn't seem to mind it being after prototypes etc
       from gmp.h.
*/

#ifndef alloca
# ifdef __GNUC__
#  define alloca __builtin_alloca
# else
#  ifdef __DECC
#   define alloca(x) __ALLOCA(x)
#  else
#   ifdef _MSC_VER
#    include <malloc.h>
#    define alloca _alloca
#   else
#    if HAVE_ALLOCA_H
#     include <alloca.h>
#    else
#     if defined (_AIX) || defined (_IBMR2)
 #pragma alloca
#     else
       char *alloca ();
#     endif
#    endif
#   endif
#  endif
# endif
#endif


#if ! HAVE_ALLOCA || USE_STACK_ALLOC
#include "stack-alloc.h"
#else
#define TMP_DECL(m)
#define TMP_ALLOC(x) alloca(x)
#define TMP_MARK(m)
#define TMP_FREE(m)
#endif

/* Allocating various types. */
#define TMP_ALLOC_TYPE(n,type) ((type *) TMP_ALLOC ((n) * sizeof (type)))
#define TMP_ALLOC_LIMBS(n)     TMP_ALLOC_TYPE(n,mp_limb_t)
#define TMP_ALLOC_MP_PTRS(n)   TMP_ALLOC_TYPE(n,mp_ptr)


#define ABS(x) (x >= 0 ? x : -x)
#define MIN(l,o) ((l) < (o) ? (l) : (o))
#define MAX(h,i) ((h) > (i) ? (h) : (i))
#define numberof(x)  (sizeof (x) / sizeof ((x)[0]))

/* Field access macros.  */
#define SIZ(x) ((x)->_mp_size)
#define ABSIZ(x) ABS (SIZ (x))
#define PTR(x) ((x)->_mp_d)
#define LIMBS(x) ((x)->_mp_d)
#define EXP(x) ((x)->_mp_exp)
#define PREC(x) ((x)->_mp_prec)
#define ALLOC(x) ((x)->_mp_alloc)

/* Extra casts because shorts are promoted to ints by "~" and "<<".  "-1"
   rather than "1" in SIGNED_TYPE_MIN avoids warnings from some compilers
   about arithmetic overflow.  */
#define UNSIGNED_TYPE_MAX(type)      ((type) ~ (type) 0)
#define UNSIGNED_TYPE_HIGHBIT(type)  ((type) ~ (UNSIGNED_TYPE_MAX(type) >> 1))
#define SIGNED_TYPE_MIN(type)        (((type) -1) << (8*sizeof(type)-1))
#define SIGNED_TYPE_MAX(type)        ((type) ~ SIGNED_TYPE_MIN(type))
#define SIGNED_TYPE_HIGHBIT(type)    SIGNED_TYPE_MIN(type)

#define MP_LIMB_T_MAX      UNSIGNED_TYPE_MAX (mp_limb_t)
#define MP_LIMB_T_HIGHBIT  UNSIGNED_TYPE_HIGHBIT (mp_limb_t)

#define MP_SIZE_T_MAX      SIGNED_TYPE_MAX (mp_size_t)

#ifndef ULONG_MAX
#define ULONG_MAX          UNSIGNED_TYPE_MAX (unsigned long)
#endif
#define ULONG_HIGHBIT      UNSIGNED_TYPE_HIGHBIT (unsigned long)
#define LONG_HIGHBIT       SIGNED_TYPE_HIGHBIT (long)
#ifndef LONG_MAX
#define LONG_MAX           SIGNED_TYPE_MAX (long)
#endif

#ifndef USHORT_MAX
#define USHORT_MAX         UNSIGNED_TYPE_MAX (unsigned short)
#endif
#define USHORT_HIGHBIT     UNSIGNED_TYPE_HIGHBIT (unsigned short)
#define SHORT_HIGHBIT      SIGNED_TYPE_HIGHBIT (short)
#ifndef SHORT_MAX
#define SHORT_MAX          SIGNED_TYPE_MAX (short)
#endif


#define MPZ_FITS_STYPE_SDT(size,data,type)                               \
  ((size) == 0                                                           \
   || ((size) == 1  && (data) <  UNSIGNED_TYPE_HIGHBIT (unsigned type))  \
   || ((size) == -1 && (data) <= UNSIGNED_TYPE_HIGHBIT (unsigned type)))

#define MPZ_FITS_UTYPE_SDT(size,data,type)                              \
  ((size) == 0                                                          \
   || ((size) == 1  && (data) <  UNSIGNED_TYPE_MAX (type)))


/* Swap macros. */

#define MP_LIMB_T_SWAP(x, y)                    \
  do {                                          \
    mp_limb_t __mp_limb_t_swap__tmp = (x);      \
    (x) = (y);                                  \
    (y) = __mp_limb_t_swap__tmp;                \
  } while (0)
#define MP_SIZE_T_SWAP(x, y)                    \
  do {                                          \
    mp_size_t __mp_size_t_swap__tmp = (x);      \
    (x) = (y);                                  \
    (y) = __mp_size_t_swap__tmp;                \
  } while (0)

#define MP_PTR_SWAP(x, y)               \
  do {                                  \
    mp_ptr __mp_ptr_swap__tmp = (x);    \
    (x) = (y);                          \
    (y) = __mp_ptr_swap__tmp;           \
  } while (0)
#define MP_SRCPTR_SWAP(x, y)                    \
  do {                                          \
    mp_srcptr __mp_srcptr_swap__tmp = (x);      \
    (x) = (y);                                  \
    (y) = __mp_srcptr_swap__tmp;                \
  } while (0)

#define MPN_PTR_SWAP(xp,xs, yp,ys)      \
  do {                                  \
    MP_PTR_SWAP (xp, yp);               \
    MP_SIZE_T_SWAP (xs, ys);            \
  } while(0)
#define MPN_SRCPTR_SWAP(xp,xs, yp,ys)   \
  do {                                  \
    MP_SRCPTR_SWAP (xp, yp);            \
    MP_SIZE_T_SWAP (xs, ys);            \
  } while(0)

#define MPZ_PTR_SWAP(x, y)              \
  do {                                  \
    mpz_ptr __mpz_ptr_swap__tmp = (x);  \
    (x) = (y);                          \
    (y) = __mpz_ptr_swap__tmp;          \
  } while (0)
#define MPZ_SRCPTR_SWAP(x, y)                   \
  do {                                          \
    mpz_srcptr __mpz_srcptr_swap__tmp = (x);    \
    (x) = (y);                                  \
    (y) = __mpz_srcptr_swap__tmp;               \
  } while (0)


#if defined (__cplusplus)
extern "C" {
#endif

extern void * (*__gmp_allocate_func) _PROTO ((size_t));
extern void * (*__gmp_reallocate_func) _PROTO ((void *, size_t, size_t));
extern void   (*__gmp_free_func) _PROTO ((void *, size_t));

void *__gmp_default_allocate _PROTO ((size_t));
void *__gmp_default_reallocate _PROTO ((void *, size_t, size_t));
void __gmp_default_free _PROTO ((void *, size_t));

#define __GMP_ALLOCATE_FUNC_TYPE(n,type) \
  ((type *) (*__gmp_allocate_func) ((n) * sizeof (type)))
#define __GMP_ALLOCATE_FUNC_LIMBS(n)   __GMP_ALLOCATE_FUNC_TYPE (n, mp_limb_t)

#define __GMP_REALLOCATE_FUNC_TYPE(p, old_size, new_size, type) \
  ((type *) (*__gmp_reallocate_func)                            \
   (p, (old_size) * sizeof (type), (new_size) * sizeof (type)))
#define __GMP_REALLOCATE_FUNC_LIMBS(p, old_size, new_size) \
  __GMP_REALLOCATE_FUNC_TYPE(p, old_size, new_size, mp_limb_t)

#define __GMP_FREE_FUNC_TYPE(p,n,type) (*__gmp_free_func) (p, (n) * sizeof (type))
#define __GMP_FREE_FUNC_LIMBS(p,n)     __GMP_FREE_FUNC_TYPE (p, n, mp_limb_t)


#if (__STDC__-0) || defined (__cplusplus)

#else

#define const			/* Empty */
#define signed			/* Empty */

#endif

#if defined (__GNUC__) && defined (__i386__)
#if 0
/* Check that these actually improve things.
   Need a cld after each std too. */
#define MPN_COPY_INCR(DST, SRC, N)					\
  __asm__ ("cld\n\trep\n\tmovsl" : :					\
	   "D" (DST), "S" (SRC), "c" (N) :				\
	   "cx", "di", "si", "memory")
#define MPN_COPY_DECR(DST, SRC, N)					\
  __asm__ ("std\n\trep\n\tmovsl" : :					\
	   "D" ((DST) + (N) - 1), "S" ((SRC) + (N) - 1), "c" (N) :	\
	   "cx", "di", "si", "memory")
#define MPN_NORMALIZE_NOT_ZERO(P, N)					\
  do {									\
    __asm__ ("std\n\trepe\n\tscasl" : "=c" (N) :			\
	     "a" (0), "D" ((P) + (N) - 1), "0" (N) :			\
	     "cx", "di");						\
    (N)++;								\
  } while (0)
#endif
#endif

#if HAVE_NATIVE_mpn_copyi
#define mpn_copyi __MPN(copyi)
void mpn_copyi _PROTO ((mp_ptr, mp_srcptr, mp_size_t));
#endif

/* Remap names of internal mpn functions.  */
#define __clz_tab               __MPN(clz_tab)
#define mpn_udiv_w_sdiv		__MPN(udiv_w_sdiv)
#define mpn_reciprocal		__MPN(reciprocal)

#define mpn_gcd_finda	__MPN(gcd_finda)
mp_limb_t mpn_gcd_finda _PROTO((const mp_limb_t cp[2]));

#define mpn_kara_mul_n	__MPN(kara_mul_n)
void mpn_kara_mul_n _PROTO((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t, mp_ptr));

#define mpn_kara_sqr_n  __MPN(kara_sqr_n)
void mpn_kara_sqr_n _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_ptr));

#define mpn_toom3_mul_n  __MPN(toom3_mul_n)
void mpn_toom3_mul_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t,mp_ptr));

#define mpn_toom3_sqr_n  __MPN(toom3_sqr_n)
void mpn_toom3_sqr_n _PROTO((mp_ptr, mp_srcptr, mp_size_t, mp_ptr));

#define mpn_fft_best_k  __MPN(fft_best_k)
int mpn_fft_best_k _PROTO ((mp_size_t n, int sqr));

#define mpn_mul_fft  __MPN(mul_fft)
void mpn_mul_fft _PROTO ((mp_ptr op, mp_size_t pl,
                          mp_srcptr n, mp_size_t nl,
                          mp_srcptr m, mp_size_t ml,
                          int k));

#define mpn_mul_fft_full  __MPN(mul_fft_full)
void mpn_mul_fft_full _PROTO ((mp_ptr op,
                               mp_srcptr n, mp_size_t nl,
                               mp_srcptr m, mp_size_t ml));

#define mpn_fft_next_size  __MPN(fft_next_size)
mp_size_t mpn_fft_next_size _PROTO ((mp_size_t pl, int k));

#define mpn_sb_divrem_mn  __MPN(sb_divrem_mn)
mp_limb_t mpn_sb_divrem_mn _PROTO ((mp_ptr, mp_ptr, mp_size_t,
                                    mp_srcptr, mp_size_t));

#define mpn_dc_divrem_n  __MPN(dc_divrem_n)
mp_limb_t mpn_dc_divrem_n _PROTO ((mp_ptr, mp_ptr, mp_srcptr, mp_size_t));

/* #define mpn_tdiv_q  __MPN(tdiv_q) */
/* void mpn_tdiv_q _PROTO ((mp_ptr, mp_size_t, mp_srcptr, mp_size_t, mp_srcptr, mp_size_t)); */

#define mpz_divexact_gcd  __gmpz_divexact_gcd
void mpz_divexact_gcd _PROTO ((mpz_ptr q, mpz_srcptr a, mpz_srcptr d));


/* Copy NLIMBS *limbs* from SRC to DST, NLIMBS==0 allowed.  */
#ifndef MPN_COPY_INCR
#if HAVE_NATIVE_mpn_copyi
#define MPN_COPY_INCR(DST, SRC, NLIMBS)   mpn_copyi (DST, SRC, NLIMBS)
#else
#define MPN_COPY_INCR(DST, SRC, NLIMBS)                 \
  do {                                                  \
    mp_size_t __i;                                      \
    ASSERT (MPN_SAME_OR_INCR_P (DST, SRC, NLIMBS));     \
    for (__i = 0; __i < (NLIMBS); __i++)                \
      (DST)[__i] = (SRC)[__i];                          \
  } while (0)
#endif
#endif

#if HAVE_NATIVE_mpn_copyd
#define mpn_copyd __MPN(copyd)
void mpn_copyd _PROTO ((mp_ptr, mp_srcptr, mp_size_t));
#endif

/* NLIMBS==0 allowed */
#ifndef MPN_COPY_DECR
#if HAVE_NATIVE_mpn_copyd
#define MPN_COPY_DECR(DST, SRC, NLIMBS)   mpn_copyd (DST, SRC, NLIMBS)
#else
#define MPN_COPY_DECR(DST, SRC, NLIMBS)                 \
  do {                                                  \
    mp_size_t __i;                                      \
    ASSERT (MPN_SAME_OR_DECR_P (DST, SRC, NLIMBS));     \
    for (__i = (NLIMBS) - 1; __i >= 0; __i--)           \
      (DST)[__i] = (SRC)[__i];                          \
  } while (0)
#endif
#endif

/* Define MPN_COPY for vector computers.  Since #pragma cannot be in a macro,
   rely on function inlining. */
#if defined (_CRAY) || defined (__uxp__)
static inline void
_MPN_COPY (d, s, n) mp_ptr d; mp_srcptr s; mp_size_t n;
{
  int i;				/* Faster for Cray with plain int */
#pragma _CRI ivdep			/* Cray PVP systems */
#pragma loop noalias d,s		/* Fujitsu VPP systems */
  for (i = 0; i < n; i++)
    d[i] = s[i];
}
#define MPN_COPY _MPN_COPY
#endif

#ifndef MPN_COPY
#define MPN_COPY(d,s,n)                         \
  do {                                          \
    ASSERT (MPN_SAME_OR_SEPARATE_P (d, s, n));  \
    MPN_COPY_INCR (d, s, n);                    \
  } while (0)
#endif

/* Zero NLIMBS *limbs* AT DST.  */
#ifndef MPN_ZERO
#define MPN_ZERO(DST, NLIMBS)                   \
  do {                                          \
    mp_size_t __i;                              \
    ASSERT ((NLIMBS) >= 0);                     \
    for (__i = 0; __i < (NLIMBS); __i++)        \
      (DST)[__i] = 0;                           \
  } while (0)
#endif

#ifndef MPN_NORMALIZE
#define MPN_NORMALIZE(DST, NLIMBS) \
  do {									\
    while (NLIMBS > 0)							\
      {									\
	if ((DST)[(NLIMBS) - 1] != 0)					\
	  break;							\
	NLIMBS--;							\
      }									\
  } while (0)
#endif
#ifndef MPN_NORMALIZE_NOT_ZERO
#define MPN_NORMALIZE_NOT_ZERO(DST, NLIMBS)     \
  do {                                          \
    ASSERT ((NLIMBS) >= 1);                     \
    while (1)                                   \
      {                                         \
	if ((DST)[(NLIMBS) - 1] != 0)           \
	  break;                                \
	NLIMBS--;                               \
      }                                         \
  } while (0)
#endif

/* Strip least significant zero limbs from ptr,size by incrementing ptr and
   decrementing size.  The number in ptr,size must be non-zero, ie. size!=0
   and somewhere a non-zero limb.  */
#define MPN_STRIP_LOW_ZEROS_NOT_ZERO(ptr, size) \
  do {                                          \
    ASSERT ((size) >= 1);                       \
    while ((ptr)[0] == 0)                       \
      {                                         \
        (ptr)++;                                \
        (size)--;                               \
        ASSERT (size >= 0);                     \
      }                                         \
  } while (0)

/* Initialize X of type mpz_t with space for NLIMBS limbs.  X should be a
   temporary variable; it will be automatically cleared out at function
   return.  We use __x here to make it possible to accept both mpz_ptr and
   mpz_t arguments.  */
#define MPZ_TMP_INIT(X, NLIMBS)                                         \
  do {                                                                  \
    mpz_ptr __x = (X);                                                  \
    ASSERT ((NLIMBS) >= 1);                                             \
    __x->_mp_alloc = (NLIMBS);                                          \
    __x->_mp_d = (mp_ptr) TMP_ALLOC ((NLIMBS) * BYTES_PER_MP_LIMB);     \
  } while (0)

/* Realloc for an mpz_t WHAT if it has less thann NEEDED limbs.  */
#define MPZ_REALLOC(what,needed) \
  do {								\
    if ((needed) > ALLOC (what))				\
      _mpz_realloc (what, needed);				\
  } while (0)

#define MPZ_EQUAL_1_P(z)  (SIZ(z)==1 && PTR(z)[0] == 1)


/* FIB_SIZE(n) is the number of limbs needed for Fibonacci number F[n], not
   exactly but certainly it's no fewer than needed.

   From Knuth vol 1 section 1.2.8, F[n] = phi^n/sqrt(5) rounded to the
   nearest integer, where phi=(1+sqrt(5))/2 is the golden ratio.  So the
   number of bits required is n*log_2((1+sqrt(5))/2) = n*0.6942419.

   The multiplier is done with 23/32=0.71875 for efficient calculation on
   CPUs without good floating point.  The +2 is for rounding up.

   Note that a division is done first, since on a 32-bit system it's at
   least conceivable to go right up to n==ULONG_MAX.  (F[2^32-1] would be
   about 380Mbytes, plus temporary workspace of about 1.2Gbytes here and
   whatever a multiply of two 190Mbyte numbers takes.)  */

#define MPZ_FIB_SIZE(n) \
  ((mp_size_t) ((n) / 32 * 23 / BITS_PER_MP_LIMB) + 2)


#define mpn_zero_p  __MPN(zero_p)
int mpn_zero_p _PROTO ((mp_srcptr p, mp_size_t n));

#if HAVE_INLINE || defined (_FORCE_INLINES)
/* n==0 is allowed and is considered a zero value.  */
inline int
mpn_zero_p (mp_srcptr p, mp_size_t n)
{
  mp_size_t i;

  ASSERT (n >= 0);
  for (i = 0; i < n; i++)
    if (p[i] != 0)
      return 0;

  return 1;
}
#endif


/* For a threshold between algorithms A and B, size>=thresh is where B
   should be used.  Special value MP_SIZE_T_MAX means only ever use A, or
   value 0 means only ever use B.  The tests for these special values will
   be compile-time constants, so the compiler should be able to eliminate
   the code for the unwanted algorithm.  */

#define ABOVE_THRESHOLD(size,thresh)    \
  ((thresh) == 0                        \
   || ((thresh) != MP_SIZE_T_MAX        \
       && (size) >= (thresh)))
#define BELOW_THRESHOLD(size,thresh)  (! ABOVE_THRESHOLD (size, thresh))


/* If KARATSUBA_MUL_THRESHOLD is not already defined, define it to a
   value which is good on most machines.  */
#ifndef KARATSUBA_MUL_THRESHOLD
#define KARATSUBA_MUL_THRESHOLD 32
#endif

/* If TOOM3_MUL_THRESHOLD is not already defined, define it to a
   value which is good on most machines.  */
#ifndef TOOM3_MUL_THRESHOLD
#define TOOM3_MUL_THRESHOLD 256
#endif

#ifndef KARATSUBA_SQR_THRESHOLD
#define KARATSUBA_SQR_THRESHOLD (2*KARATSUBA_MUL_THRESHOLD)
#endif

#ifndef TOOM3_SQR_THRESHOLD
#define TOOM3_SQR_THRESHOLD (2*TOOM3_MUL_THRESHOLD)
#endif

/* First k to use for an FFT modF multiply.  A modF FFT is an order
   log(2^k)/log(2^(k-1)) algorithm, so k=3 is merely 1.5 like karatsuba,
   whereas k=4 is 1.33 which is faster than toom3 at 1.485.    */
#define FFT_FIRST_K  4

/* Threshold at which FFT should be used to do a modF NxN -> N multiply. */
#ifndef FFT_MODF_MUL_THRESHOLD
#define FFT_MODF_MUL_THRESHOLD   (TOOM3_MUL_THRESHOLD * 3)
#endif
#ifndef FFT_MODF_SQR_THRESHOLD
#define FFT_MODF_SQR_THRESHOLD   (TOOM3_SQR_THRESHOLD * 3)
#endif

/* Threshold at which FFT should be used to do an NxN -> 2N multiply.  This
   will be a size where FFT is using k=7 or k=8, since an FFT-k used for an
   NxN->2N multiply and not recursing into itself is an order
   log(2^k)/log(2^(k-2)) algorithm, so it'll be at least k=7 at 1.39 which
   is the first better than toom3.  */
#ifndef FFT_MUL_THRESHOLD
#define FFT_MUL_THRESHOLD   (FFT_MODF_MUL_THRESHOLD * 10)
#endif
#ifndef FFT_SQR_THRESHOLD
#define FFT_SQR_THRESHOLD   (FFT_MODF_SQR_THRESHOLD * 10)
#endif

/* Table of thresholds for successive modF FFT "k"s.  The first entry is
   where FFT_FIRST_K+1 should be used, the second FFT_FIRST_K+2,
   etc.  See mpn_fft_best_k(). */
#ifndef FFT_MUL_TABLE
#define FFT_MUL_TABLE                           \
  { TOOM3_MUL_THRESHOLD * 4,   /* k=5 */        \
    TOOM3_MUL_THRESHOLD * 8,   /* k=6 */        \
    TOOM3_MUL_THRESHOLD * 16,  /* k=7 */        \
    TOOM3_MUL_THRESHOLD * 32,  /* k=8 */        \
    TOOM3_MUL_THRESHOLD * 96,  /* k=9 */        \
    TOOM3_MUL_THRESHOLD * 288, /* k=10 */       \
    0 }
#endif
#ifndef FFT_SQR_TABLE
#define FFT_SQR_TABLE                           \
  { TOOM3_SQR_THRESHOLD * 4,   /* k=5 */        \
    TOOM3_SQR_THRESHOLD * 8,   /* k=6 */        \
    TOOM3_SQR_THRESHOLD * 16,  /* k=7 */        \
    TOOM3_SQR_THRESHOLD * 32,  /* k=8 */        \
    TOOM3_SQR_THRESHOLD * 96,  /* k=9 */        \
    TOOM3_SQR_THRESHOLD * 288, /* k=10 */       \
    0 }
#endif

#ifndef FFT_TABLE_ATTRS
#define FFT_TABLE_ATTRS   static const
#endif

#define MPN_FFT_TABLE_SIZE  16


/* mpn_dc_divrem_n(n) calls 2*mul(n/2)+2*div(n/2), thus to be faster than
   div(n) = 4*div(n/2), we need mul(n/2) to be faster than the classic way,
   i.e. n/2 >= KARATSUBA_MUL_THRESHOLD

   Measured values are between 2 and 4 times KARATSUBA_MUL_THRESHOLD, so go
   for 3 as an average.  */

#ifndef DC_THRESHOLD
#define DC_THRESHOLD    (3 * KARATSUBA_MUL_THRESHOLD)
#endif


/* It seems the bigcase code usually cuts in almost immediately (ie. only a
   few sizes want the simple addition based code), so set the defaults like
   that.  */
#ifndef FIB_THRESHOLD
#if BITS_PER_MP_LIMB == 32
#define FIB_THRESHOLD  100
#endif
#if BITS_PER_MP_LIMB == 64
#define FIB_THRESHOLD  200
#endif
#endif


/* Return non-zero if xp,xsize and yp,ysize overlap.
   If xp+xsize<=yp there's no overlap, or if yp+ysize<=xp there's no
   overlap.  If both these are false, there's an overlap. */
#define MPN_OVERLAP_P(xp, xsize, yp, ysize) \
  ((xp) + (xsize) > (yp) && (yp) + (ysize) > (xp))

/* Return non-zero if xp,xsize and yp,ysize are either identical or not
   overlapping.  Return zero if they're partially overlapping. */
#define MPN_SAME_OR_SEPARATE_P(xp, yp, size)    \
  MPN_SAME_OR_SEPARATE2_P(xp, size, yp, size)
#define MPN_SAME_OR_SEPARATE2_P(xp, xsize, yp, ysize)           \
  ((xp) == (yp) || ! MPN_OVERLAP_P (xp, xsize, yp, ysize))

/* Return non-zero if dst,dsize and src,ssize are either identical or
   overlapping in a way suitable for an incrementing/decrementing algorithm.
   Return zero if they're partially overlapping in an unsuitable fashion. */
#define MPN_SAME_OR_INCR2_P(dst, dsize, src, ssize)             \
  ((dst) <= (src) || ! MPN_OVERLAP_P (dst, dsize, src, ssize))
#define MPN_SAME_OR_INCR_P(dst, src, size)      \
  MPN_SAME_OR_INCR2_P(dst, size, src, size)
#define MPN_SAME_OR_DECR2_P(dst, dsize, src, ssize)             \
  ((dst) >= (src) || ! MPN_OVERLAP_P (dst, dsize, src, ssize))
#define MPN_SAME_OR_DECR_P(dst, src, size)      \
  MPN_SAME_OR_DECR2_P(dst, size, src, size)


#if HAVE_VOID
#define CAST_TO_VOID        (void)
#else
#define CAST_TO_VOID
#endif


/* ASSERT() is a private assertion checking scheme, similar to <assert.h>.
   ASSERT() does the check only if WANT_ASSERT is selected, ASSERT_ALWAYS()
   does it always.  Generally assertions are meant for development, but
   might help when looking for a problem later too.

   ASSERT_NOCARRY() uses ASSERT() to check the expression is zero, but if
   assertion checking is disabled, the expression is still evaluated.  This
   is meant for use with routines like mpn_add_n() where the return value
   represents a carry or whatever that shouldn't occur.  For example,
   ASSERT_NOCARRY (mpn_add_n (rp, s1p, s2p, size)); */

#ifdef __LINE__
#define ASSERT_LINE  __LINE__
#else
#define ASSERT_LINE  -1
#endif

#ifdef __FILE__
#define ASSERT_FILE  __FILE__
#else
#define ASSERT_FILE  ""
#endif

int __gmp_assert_fail _PROTO((const char *filename, int linenum,
                              const char *expr));

#if HAVE_STRINGIZE
#define ASSERT_FAIL(expr)  __gmp_assert_fail (ASSERT_FILE, ASSERT_LINE, #expr)
#else
#define ASSERT_FAIL(expr)  __gmp_assert_fail (ASSERT_FILE, ASSERT_LINE, "expr")
#endif

#define ASSERT_ALWAYS(expr)     \
  do {                          \
    if (!(expr))                \
      ASSERT_FAIL (expr);       \
  } while (0)

#if WANT_ASSERT
#define ASSERT(expr)           ASSERT_ALWAYS (expr)
#define ASSERT_NOCARRY(expr)   ASSERT_ALWAYS ((expr) == 0)

#else
#define ASSERT(expr)           do {} while (0)
#define ASSERT_NOCARRY(expr)   (expr)
#endif


#if HAVE_NATIVE_mpn_com_n
#define mpn_com_n __MPN(com_n)
void mpn_com_n _PROTO ((mp_ptr, mp_srcptr, mp_size_t));
#else
#define mpn_com_n(d,s,n)                                \
  do {                                                  \
    mp_ptr     __d = (d);                               \
    mp_srcptr  __s = (s);                               \
    mp_size_t  __n = (n);                               \
    ASSERT (__n >= 1);                                  \
    ASSERT (MPN_SAME_OR_SEPARATE_P (__d, __s, __n));    \
    do                                                  \
      *__d++ = ~ *__s++;                                \
    while (--__n);                                      \
  } while (0)
#endif

#define MPN_LOGOPS_N_INLINE(d,s1,s2,n,dop,op,s2op)      \
  do {                                                  \
    mp_ptr	 __d = (d);                             \
    mp_srcptr	 __s1 = (s1);                           \
    mp_srcptr	 __s2 = (s2);                           \
    mp_size_t	 __n = (n);                             \
    ASSERT (__n >= 1);                                  \
    ASSERT (MPN_SAME_OR_SEPARATE_P (__d, __s1, __n));   \
    ASSERT (MPN_SAME_OR_SEPARATE_P (__d, __s2, __n));   \
    do                                                  \
      *__d++ = dop (*__s1++ op s2op *__s2++);           \
    while (--__n);                                      \
  } while (0)

#if HAVE_NATIVE_mpn_and_n
#define mpn_and_n __MPN(and_n)
void mpn_and_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t));
#else
#define mpn_and_n(d,s1,s2,n)  MPN_LOGOPS_N_INLINE(d,s1,s2,n, ,&, )
#endif

#if HAVE_NATIVE_mpn_andn_n
#define mpn_andn_n __MPN(andn_n)
void mpn_andn_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t));
#else
#define mpn_andn_n(d,s1,s2,n) MPN_LOGOPS_N_INLINE(d,s1,s2,n, ,&,~)
#endif

#if HAVE_NATIVE_mpn_nand_n
#define mpn_nand_n __MPN(nand_n)
void mpn_nand_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t));
#else
#define mpn_nand_n(d,s1,s2,n) MPN_LOGOPS_N_INLINE(d,s1,s2,n,~,&, )
#endif

#if HAVE_NATIVE_mpn_ior_n
#define mpn_ior_n __MPN(ior_n)
void mpn_ior_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t));
#else
#define mpn_ior_n(d,s1,s2,n)  MPN_LOGOPS_N_INLINE(d,s1,s2,n, ,|, )
#endif

#if HAVE_NATIVE_mpn_iorn_n
#define mpn_iorn_n __MPN(iorn_n)
void mpn_iorn_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t));
#else
#define mpn_iorn_n(d,s1,s2,n) MPN_LOGOPS_N_INLINE(d,s1,s2,n, ,|,~)
#endif

#if HAVE_NATIVE_mpn_nior_n
#define mpn_nior_n __MPN(nior_n)
void mpn_nior_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t));
#else
#define mpn_nior_n(d,s1,s2,n) MPN_LOGOPS_N_INLINE(d,s1,s2,n,~,|, )
#endif

#if HAVE_NATIVE_mpn_xor_n
#define mpn_xor_n __MPN(xor_n)
void mpn_xor_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t));
#else
#define mpn_xor_n(d,s1,s2,n)  MPN_LOGOPS_N_INLINE(d,s1,s2,n, ,^, )
#endif

#if HAVE_NATIVE_mpn_xnor_n
#define mpn_xnor_n __MPN(xnor_n)
void mpn_xnor_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t));
#else
#define mpn_xnor_n(d,s1,s2,n) MPN_LOGOPS_N_INLINE(d,s1,s2,n,~,^, )
#endif

/* Structure for conversion between internal binary format and
   strings in base 2..36.  */
struct bases
{
  /* Number of digits in the conversion base that always fits in an mp_limb_t.
     For example, for base 10 on a machine where a mp_limb_t has 32 bits this
     is 9, since 10**9 is the largest number that fits into a mp_limb_t.  */
  int chars_per_limb;

  /* log(2)/log(conversion_base) */
  double chars_per_bit_exactly;

  /* base**chars_per_limb, i.e. the biggest number that fits a word, built by
     factors of base.  Exception: For 2, 4, 8, etc, big_base is log2(base),
     i.e. the number of bits used to represent each digit in the base.  */
  mp_limb_t big_base;

  /* A BITS_PER_MP_LIMB bit approximation to 1/big_base, represented as a
     fixed-point number.  Instead of dividing by big_base an application can
     choose to multiply by big_base_inverted.  */
  mp_limb_t big_base_inverted;
};

#define __mp_bases __MPN(mp_bases)
extern const struct bases __mp_bases[256];
extern mp_size_t __gmp_default_fp_limb_precision;

#if defined (__i386__)
#define TARGET_REGISTER_STARVED 1
#else
#define TARGET_REGISTER_STARVED 0
#endif

/* Use a library function for invert_limb, if available. */
#if ! defined (invert_limb) && HAVE_NATIVE_mpn_invert_limb
#define mpn_invert_limb  __MPN(invert_limb)
mp_limb_t mpn_invert_limb _PROTO ((mp_limb_t));
#define invert_limb(invxl,xl)  (invxl = __MPN(invert_limb) (xl))
#endif

#ifndef invert_limb
#define invert_limb(invxl,xl)                   \
  do {                                          \
    mp_limb_t dummy;                            \
    ASSERT ((xl) != 0);                         \
    if (xl << 1 == 0)                           \
      invxl = ~(mp_limb_t) 0;                   \
    else                                        \
      udiv_qrnnd (invxl, dummy, -xl, 0, xl);    \
  } while (0)
#endif

/* Divide the two-limb number in (NH,,NL) by D, with DI being the largest
   limb not larger than (2**(2*BITS_PER_MP_LIMB))/D - (2**BITS_PER_MP_LIMB).
   If this would yield overflow, DI should be the largest possible number
   (i.e., only ones).  For correct operation, the most significant bit of D
   has to be set.  Put the quotient in Q and the remainder in R.  */
#define udiv_qrnnd_preinv(q, r, nh, nl, d, di)                            \
  do {                                                                    \
    mp_limb_t _q, _ql, _r;                                                \
    mp_limb_t _xh, _xl;                                                   \
    ASSERT ((d) != 0);                                                    \
    umul_ppmm (_q, _ql, (nh), (di));                                      \
    _q += (nh);                 /* DI is 2**BITS_PER_MP_LIMB too small */ \
    umul_ppmm (_xh, _xl, _q, (d));                                        \
    sub_ddmmss (_xh, _r, (nh), (nl), _xh, _xl);                           \
    if (_xh != 0)                                                         \
      {                                                                   \
	sub_ddmmss (_xh, _r, _xh, _r, 0, (d));                            \
	_q += 1;                                                          \
	if (_xh != 0)                                                     \
	  {                                                               \
	    sub_ddmmss (_xh, _r, _xh, _r, 0, (d));                        \
	    _q += 1;                                                      \
	  }                                                               \
      }                                                                   \
    if (_r >= (d))                                                        \
      {                                                                   \
	_r -= (d);                                                        \
	_q += 1;                                                          \
      }                                                                   \
    (r) = _r;                                                             \
    (q) = _q;                                                             \
  } while (0)
/* Like udiv_qrnnd_preinv, but for for any value D.  DNORM is D shifted left
   so that its most significant bit is set.  LGUP is ceil(log2(D)).  */
#define udiv_qrnnd_preinv2gen(q, r, nh, nl, d, di, dnorm, lgup) \
  do {									\
    mp_limb_t _n2, _n10, _n1, _nadj, _q1;				\
    mp_limb_t _xh, _xl;							\
    _n2 = ((nh) << (BITS_PER_MP_LIMB - (lgup))) + ((nl) >> 1 >> (l - 1));\
    _n10 = (nl) << (BITS_PER_MP_LIMB - (lgup));				\
    _n1 = ((mp_limb_signed_t) _n10 >> (BITS_PER_MP_LIMB - 1));		\
    _nadj = _n10 + (_n1 & (dnorm));					\
    umul_ppmm (_xh, _xl, di, _n2 - _n1);				\
    add_ssaaaa (_xh, _xl, _xh, _xl, 0, _nadj);				\
    _q1 = ~(_n2 + _xh);							\
    umul_ppmm (_xh, _xl, _q1, d);					\
    add_ssaaaa (_xh, _xl, _xh, _xl, nh, nl);				\
    _xh -= (d);								\
    (r) = _xl + ((d) & _xh);						\
    (q) = _xh - _q1;							\
  } while (0)
/* Exactly like udiv_qrnnd_preinv, but branch-free.  It is not clear which
   version to use.  */
#define udiv_qrnnd_preinv2norm(q, r, nh, nl, d, di) \
  do {									\
    mp_limb_t _n2, _n10, _n1, _nadj, _q1;				\
    mp_limb_t _xh, _xl;							\
    _n2 = (nh);								\
    _n10 = (nl);							\
    _n1 = ((mp_limb_signed_t) _n10 >> (BITS_PER_MP_LIMB - 1));		\
    _nadj = _n10 + (_n1 & (d));						\
    umul_ppmm (_xh, _xl, di, _n2 - _n1);				\
    add_ssaaaa (_xh, _xl, _xh, _xl, 0, _nadj);				\
    _q1 = ~(_n2 + _xh);							\
    umul_ppmm (_xh, _xl, _q1, d);					\
    add_ssaaaa (_xh, _xl, _xh, _xl, nh, nl);				\
    _xh -= (d);								\
    (r) = _xl + ((d) & _xh);						\
    (q) = _xh - _q1;							\
  } while (0)

/* Two dependent multiplies, plus about 6 cycles of other dependent
   calculations. */
#ifndef UDIV_NORM_PREINV_TIME
#define UDIV_NORM_PREINV_TIME    (2*UMUL_TIME + 6)
#endif

/* When divisor was unnormalized there's going to be some shifting, so
   assume a couple of extra cycles.  (The shifting isn't on the dependent
   chain, but on some chips it seems to upset the code generation a bit.)  */
#ifndef UDIV_UNNORM_PREINV_TIME
#define UDIV_UNNORM_PREINV_TIME  (UDIV_NORM_PREINV_TIME + 2)
#endif


/* modlimb_invert() sets "inv" to the multiplicative inverse of "n" modulo
   2^BITS_PER_MP_LIMB, ie. so that inv*n == 1 mod 2^BITS_PER_MP_LIMB.
   "n" must be odd (otherwise such an inverse doesn't exist).

   This is not to be confused with invert_limb(), which is completely
   different.

   The table lookup gives an inverse with the low 8 bits valid, and each
   multiply step doubles the number of bits.  See Jebelean's exact division
   paper, end of section 4 (reference in gmp.texi).

   Possible enhancement: Could use UHWtype until the last step, if half-size
   multiplies are faster (might help under _LONG_LONG_LIMB).  */

#define modlimb_invert_table  __gmp_modlimb_invert_table
extern const unsigned char  modlimb_invert_table[128];

#if BITS_PER_MP_LIMB <= 32
#define modlimb_invert(inv,n)                                   \
  do {                                                          \
    mp_limb_t  __n = (n);                                       \
    mp_limb_t  __inv;                                           \
    ASSERT ((__n & 1) == 1);                                    \
    __inv = modlimb_invert_table[(__n&0xFF)/2]; /*  8 */        \
    __inv = 2 * __inv - __inv * __inv * __n;    /* 16 */        \
    __inv = 2 * __inv - __inv * __inv * __n;    /* 32 */        \
    ASSERT (__inv * __n == 1);                                  \
    (inv) = __inv;                                              \
  } while (0)
#endif

#if BITS_PER_MP_LIMB > 32 && BITS_PER_MP_LIMB <= 64
#define modlimb_invert(inv,n)                                   \
  do {                                                          \
    mp_limb_t  __n = (n);                                       \
    mp_limb_t  __inv;                                           \
    ASSERT ((__n & 1) == 1);                                    \
    __inv = modlimb_invert_table[(__n&0xFF)/2]; /*  8 */        \
    __inv = 2 * __inv - __inv * __inv * __n;    /* 16 */        \
    __inv = 2 * __inv - __inv * __inv * __n;    /* 32 */        \
    __inv = 2 * __inv - __inv * __inv * __n;    /* 64 */        \
    ASSERT (__inv * __n == 1);                                  \
    (inv) = __inv;                                              \
  } while (0)
#endif

/* Multiplicative inverse of 3, modulo 2^BITS_PER_MP_LIMB.
   0xAAAAAAAB for 32 bits, 0xAAAAAAAAAAAAAAAB for 64 bits. */
#define MODLIMB_INVERSE_3   ((MP_LIMB_T_MAX / 3) * 2 + 1)


/* The `mode' attribute was introduced in GCC 2.2, but we can only distinguish
   between GCC 2 releases from 2.5, since __GNUC_MINOR__ wasn't introduced
   until then.  */
#if (__GNUC__ - 0 > 2 || defined (__GNUC_MINOR__)) && ! defined (__APPLE_CC__)
/* Define stuff for longlong.h.  */
typedef unsigned int UQItype	__attribute__ ((mode (QI)));
typedef		 int SItype	__attribute__ ((mode (SI)));
typedef unsigned int USItype	__attribute__ ((mode (SI)));
typedef		 int DItype	__attribute__ ((mode (DI)));
typedef unsigned int UDItype	__attribute__ ((mode (DI)));
#else
typedef unsigned char UQItype;
typedef		 long SItype;
typedef unsigned long USItype;
#if defined _LONGLONG || defined _LONG_LONG_LIMB
typedef	long long int DItype;
typedef unsigned long long int UDItype;
#else /* Assume `long' gives us a wide enough type.  Needed for hppa2.0w.  */
typedef long int DItype;
typedef unsigned long int UDItype;
#endif
#endif

typedef mp_limb_t UWtype;
typedef unsigned int UHWtype;
#define W_TYPE_SIZE BITS_PER_MP_LIMB

/* Define ieee_double_extract and _GMP_IEEE_FLOATS.  */

#if (defined (__arm__) && (defined (__ARMWEL__) || defined (__linux__)))
/* Special case for little endian ARM since floats remain in big-endian.  */
#define _GMP_IEEE_FLOATS 1
union ieee_double_extract
{
  struct
    {
      unsigned int manh:20;
      unsigned int exp:11;
      unsigned int sig:1;
      unsigned int manl:32;
    } s;
  double d;
};
#else
#if defined (_LITTLE_ENDIAN) || defined (__LITTLE_ENDIAN__)		\
 || defined (__alpha)							\
 || defined (__clipper__)						\
 || defined (__cris)							\
 || defined (__i386__)							\
 || defined (__i860__)							\
 || defined (__i960__)							\
 || defined (__ia64)							\
 || defined (MIPSEL) || defined (_MIPSEL)				\
 || defined (__ns32000__)						\
 || defined (__WINNT) || defined (_WIN32)
#define _GMP_IEEE_FLOATS 1
union ieee_double_extract
{
  struct
    {
      unsigned int manl:32;
      unsigned int manh:20;
      unsigned int exp:11;
      unsigned int sig:1;
    } s;
  double d;
};
#else /* Need this as an #else since the tests aren't made exclusive.  */
#if defined (_BIG_ENDIAN) || defined (__BIG_ENDIAN__)			\
 || defined (__a29k__) || defined (_AM29K)				\
 || defined (__arm__)							\
 || (defined (__convex__) && defined (_IEEE_FLOAT_))			\
 || defined (_CRAYMPP) || defined (_CRAYIEEE)				\
 || defined (__i370__) || defined (__mvs__)				\
 || defined (__mc68000__) || defined (__mc68020__) || defined (__m68k__)\
    || defined(mc68020)							\
 || defined (__m88000__)						\
 || defined (MIPSEB) || defined (_MIPSEB)				\
 || defined (__hppa) || defined (__hppa__)				\
 || defined (__pyr__)							\
 || defined (__ibm032__)						\
 || defined (_IBMR2) || defined (_ARCH_PPC)				\
 || defined (__sh__)							\
 || defined (__sparc) || defined (sparc)				\
 || defined (__we32k__)
#define _GMP_IEEE_FLOATS 1
union ieee_double_extract
{
  struct
    {
      unsigned int sig:1;
      unsigned int exp:11;
      unsigned int manh:20;
      unsigned int manl:32;
    } s;
  double d;
};
#endif
#endif
#endif

/* Using "(2.0 * ((mp_limb_t) 1 << (BITS_PER_MP_LIMB - 1)))" doesn't work on
   SunOS 4.1.4 native /usr/ucb/cc (K&R), it comes out as -4294967296.0,
   presumably due to treating the mp_limb_t constant as signed rather than
   unsigned. */
#define MP_BASE_AS_DOUBLE (4.0 * ((mp_limb_t) 1 << (BITS_PER_MP_LIMB - 2)))
#if BITS_PER_MP_LIMB == 64
#define LIMBS_PER_DOUBLE 2
#else
#define LIMBS_PER_DOUBLE 3
#endif

double __gmp_scale2 _PROTO ((double, int));
int __gmp_extract_double _PROTO ((mp_ptr, double));

extern int __gmp_junk;
extern const int __gmp_0;
#define GMP_ERROR(code)   (gmp_errno |= (code), __gmp_junk = 10/__gmp_0)
#define DIVIDE_BY_ZERO    GMP_ERROR(GMP_ERROR_DIVISION_BY_ZERO)
#define SQRT_OF_NEGATIVE  GMP_ERROR(GMP_ERROR_SQRT_OF_NEGATIVE)

#if defined _LONG_LONG_LIMB
#if defined (__STDC__)
#define CNST_LIMB(C) C##LL
#else
#define CNST_LIMB(C) C/**/LL
#endif
#else /* not _LONG_LONG_LIMB */
#if defined (__STDC__)
#define CNST_LIMB(C) C##L
#else
#define CNST_LIMB(C) C/**/L
#endif
#endif /* _LONG_LONG_LIMB */

/*** Stuff used by mpn/generic/perfsqr.c and mpn/generic/next_prime.c ***/
#if BITS_PER_MP_LIMB == 32
#define PP 0xC0CFD797L		/* 3 x 5 x 7 x 11 x 13 x ... x 29 */
#define PP_INVERTED 0x53E5645CL
#define PP_MAXPRIME 29
#define PP_MASK 0x208A28A8L
#endif

#if BITS_PER_MP_LIMB == 64
#define PP CNST_LIMB(0xE221F97C30E94E1D)	/* 3 x 5 x 7 x 11 x 13 x ... x 53 */
#define PP_INVERTED CNST_LIMB(0x21CFE6CFC938B36B)
#define PP_MAXPRIME 53
#define PP_MASK CNST_LIMB(0x208A20A08A28A8)
#endif


/* BIT1 means a result value in bit 1 (second least significant bit), with a
   zero bit representing +1 and a one bit representing -1.  Bits other than
   bit 1 are garbage.

   JACOBI_TWOS_U_BIT1 and JACOBI_RECIP_UU_BIT1 are used in mpn_jacobi_base
   and their speed is important.  Expressions are used rather than
   conditionals to accumulate sign changes, which effectively means XORs
   instead of conditional JUMPs. */

/* (a/0), with a signed; is 1 if a=+/-1, 0 otherwise */
#define JACOBI_S0(a) \
  (((a) == 1) | ((a) == -1))

/* (a/0), with a unsigned; is 1 if a=+/-1, 0 otherwise */
#define JACOBI_U0(a) \
  ((a) == 1)

/* (a/0), with a an mpz_t; is 1 if a=+/-1, 0 otherwise
   An mpz_t always has at least one limb of allocated space, so the fetch of
   the low limb is valid. */
#define JACOBI_Z0(a) \
  (((SIZ(a) == 1) | (SIZ(a) == -1)) & (PTR(a)[0] == 1))

/* Convert a bit1 to +1 or -1. */
#define JACOBI_BIT1_TO_PN(result_bit1) \
  (1 - ((result_bit1) & 2))

/* (2/b), with b unsigned and odd;
   is (-1)^((b^2-1)/8) which is 1 if b==1,7mod8 or -1 if b==3,5mod8 and
   hence obtained from (b>>1)^b */
#define JACOBI_TWO_U_BIT1(b) \
  (((b) >> 1) ^ (b))

/* (2/b)^twos, with b unsigned and odd */
#define JACOBI_TWOS_U_BIT1(twos, b) \
  (((twos) << 1) & JACOBI_TWO_U_BIT1 (b))

/* (2/b)^twos, with b unsigned and odd */
#define JACOBI_TWOS_U(twos, b) \
  (JACOBI_BIT1_TO_PN (JACOBI_TWOS_U_BIT1 (twos, b)))

/* (a/b) effect due to sign of a: signed/unsigned, b odd;
   is (-1)^((b-1)/2) if a<0, or +1 if a>=0 */
#define JACOBI_ASGN_SU_BIT1(a, b) \
  ((((a) < 0) << 1) & (b))

/* (a/b) effect due to sign of b: signed/mpz;
   is -1 if a and b both negative, +1 otherwise */
#define JACOBI_BSGN_SZ_BIT1(a, b) \
  ((((a) < 0) & (SIZ(b) < 0)) << 1)

/* (a/b) effect due to sign of b: mpz/signed */
#define JACOBI_BSGN_ZS_BIT1(a, b) \
  JACOBI_BSGN_SZ_BIT1(b, a)

/* (a/b) reciprocity to switch to (b/a), a,b both unsigned and odd.
   Is (-1)^((a-1)*(b-1)/4), which means +1 if either a,b==1mod4, or -1 if
   both a,b==3mod4, achieved in bit 1 by a&b.  No ASSERT()s about a,b odd
   because this is used in a couple of places with only bit 1 of a or b
   valid. */
#define JACOBI_RECIP_UU_BIT1(a, b) \
  ((a) & (b))


/* For testing and debugging.  */
#define MPZ_CHECK_FORMAT(z)					\
  do {								\
    ASSERT_ALWAYS (SIZ(z) == 0 || PTR(z)[ABSIZ(z) - 1] != 0);	\
    ASSERT_ALWAYS (ALLOC(z) >= ABSIZ(z));			\
  } while (0)

#define MPQ_CHECK_FORMAT(q)                             \
  do {                                                  \
    MPZ_CHECK_FORMAT (mpq_numref (q));                  \
    MPZ_CHECK_FORMAT (mpq_denref (q));                  \
    ASSERT_ALWAYS (SIZ(mpq_denref(q)) >= 1);            \
                                                        \
    if (SIZ(mpq_numref(q)) == 0)                        \
      {                                                 \
        /* should have zero as 0/1 */                   \
        ASSERT_ALWAYS (SIZ(mpq_denref(q)) == 1          \
                       && PTR(mpq_denref(q))[0] == 1);  \
      }                                                 \
    else                                                \
      {                                                 \
        /* should have no common factors */             \
        mpz_t  g;                                       \
        mpz_init (g);                                   \
        mpz_gcd (g, mpq_numref(q), mpq_denref(q));      \
        ASSERT_ALWAYS (mpz_cmp_ui (g, 1) == 0);         \
        mpz_clear (g);                                  \
      }                                                 \
  } while (0)


#define MPZ_PROVOKE_REALLOC(z)					\
  do { ALLOC(z) = ABSIZ(z); } while (0)

#define MPZ_SET_STR_OR_ABORT(_r,_s,_b)                  \
  do {                                                  \
    if (mpz_set_str (_r, _s, _b) != 0)                  \
      {                                                 \
        fprintf (stderr, "ERROR mpz_set_str\n");        \
        fprintf (stderr, "   str  = \"%s\"\n", _s);     \
        fprintf (stderr, "   base = %d\n", _b);         \
        abort();                                        \
      }                                                 \
  } while (0)

#define MPF_SET_STR_OR_ABORT(_r,_s,_b)                  \
  do {                                                  \
    if (mpf_set_str (_r, _s, _b) != 0)                  \
      {                                                 \
        fprintf (stderr, "ERROR mpf_set_str\n");        \
        fprintf (stderr, "   str  = \"%s\"\n", _s);     \
        fprintf (stderr, "   base = %d\n", _b);         \
        abort();                                        \
      }                                                 \
  } while (0)


#if TUNE_PROGRAM_BUILD
/* Some extras wanted when recompiling some .c files for use by the tune
   program.  Not part of a normal build. */

extern mp_size_t  mul_threshold[];
extern mp_size_t  fft_modf_mul_threshold;
extern mp_size_t  sqr_threshold[];
extern mp_size_t  fft_modf_sqr_threshold;
extern mp_size_t  dc_threshold[];
extern mp_size_t  fib_threshold[];
extern mp_size_t  powm_threshold[];
extern mp_size_t  gcd_accel_threshold[];
extern mp_size_t  gcdext_threshold[];

#undef KARATSUBA_MUL_THRESHOLD
#undef TOOM3_MUL_THRESHOLD
#undef FFT_MUL_TABLE
#undef FFT_MUL_THRESHOLD
#undef FFT_MODF_MUL_THRESHOLD
#undef KARATSUBA_SQR_THRESHOLD
#undef TOOM3_SQR_THRESHOLD
#undef FFT_SQR_TABLE
#undef FFT_SQR_THRESHOLD
#undef FFT_MODF_SQR_THRESHOLD
#undef DC_THRESHOLD
#undef FIB_THRESHOLD
#undef POWM_THRESHOLD
#undef GCD_ACCEL_THRESHOLD
#undef GCDEXT_THRESHOLD

#define KARATSUBA_MUL_THRESHOLD  mul_threshold[0]
#define TOOM3_MUL_THRESHOLD      mul_threshold[1]
#define FFT_MUL_TABLE            { 0 }
#define FFT_MUL_THRESHOLD        mul_threshold[2]
#define FFT_MODF_MUL_THRESHOLD   fft_modf_mul_threshold
#define KARATSUBA_SQR_THRESHOLD  sqr_threshold[0]
#define TOOM3_SQR_THRESHOLD      sqr_threshold[1]
#define FFT_SQR_TABLE            { 0 }
#define FFT_SQR_THRESHOLD        sqr_threshold[2]
#define FFT_MODF_SQR_THRESHOLD   fft_modf_sqr_threshold
#define DC_THRESHOLD             dc_threshold[0]
#define FIB_THRESHOLD            fib_threshold[0]
#define POWM_THRESHOLD           powm_threshold[0]
#define GCD_ACCEL_THRESHOLD      gcd_accel_threshold[0]
#define GCDEXT_THRESHOLD         gcdext_threshold[0]

/* Sizes the tune program tests up to, used in a couple of recompilations. */
#define KARATSUBA_SQR_MAX_GENERIC  200
#define TOOM3_MUL_THRESHOLD_LIMIT  700

#undef  FFT_TABLE_ATTRS
#define FFT_TABLE_ATTRS
extern mp_size_t mpn_fft_table[2][MPN_FFT_TABLE_SIZE];

#if TUNE_PROGRAM_BUILD_SQR
#undef KARATSUBA_SQR_THRESHOLD
#define KARATSUBA_SQR_THRESHOLD  KARATSUBA_SQR_MAX_GENERIC
#endif

#endif /* TUNE_PROGRAM_BUILD */

#if defined (__cplusplus)
}
#endif

#endif
