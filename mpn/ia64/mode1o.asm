dnl  Itanium-2 mpn_modexact_1c_odd -- mpn by 1 exact remainder.

dnl  Contributed to the GNU project by Kevin Ryde.

dnl  Copyright 2003-2005 Free Software Foundation, Inc.

dnl  This file is part of the GNU MP Library.

dnl  The GNU MP Library is free software; you can redistribute it and/or modify
dnl  it under the terms of the GNU Lesser General Public License as published
dnl  by the Free Software Foundation; either version 3 of the License, or (at
dnl  your option) any later version.

dnl  The GNU MP Library is distributed in the hope that it will be useful, but
dnl  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
dnl  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
dnl  License for more details.

dnl  You should have received a copy of the GNU Lesser General Public License
dnl  along with the GNU MP Library.  If not, see https://www.gnu.org/licenses/.

include(`../config.m4')


C            cycles/limb
C Itanium:      15
C Itanium 2:     8


dnl  Usage: ABI32(`code')
dnl
dnl  Emit the given code only under HAVE_ABI_32.
dnl
define(ABI32,
m4_assert_onearg()
`ifdef(`HAVE_ABI_32',`$1')')


C mp_limb_t mpn_modexact_1c_odd (mp_srcptr src, mp_size_t size,
C                                mp_limb_t divisor, mp_limb_t carry);
C
C The modexact algorithm is usually conceived as a dependent chain
C
C	l = src[i] - c
C	q = low(l * inverse)
C	c = high(q*divisor) + (src[i]<c)
C
C but we can work the src[i]-c into an xma by calculating si=src[i]*inverse
C separately (off the dependent chain) and using
C
C	q = low(c * inverse + si)
C	c = high(q*divisor + c)
C
C This means the dependent chain is simply xma.l followed by xma.hu, for a
C total 8 cycles/limb on itanium-2.
C
C The reason xma.hu works for the new c is that the low of q*divisor is
C src[i]-c (being the whole purpose of the q generated, and it can be
C verified algebraically).  If there was an underflow from src[i]-c, then
C there will be an overflow from (src-c)+c, thereby adding 1 to the new c
C the same as the borrow bit (src[i]<c) gives in the first style shown.
C
C Incidentally, fcmp is not an option for treating src[i]-c, since it
C apparently traps to the kernel for unnormalized operands like those used
C and generated by ldf8 and xma.  On one GNU/Linux system it took about 1200
C cycles.
C
C
C First Limb:
C
C The first limb uses q = (src[0]-c) * inverse shown in the first style.
C This lets us get the first q as soon as the inverse is ready, without
C going through si=s*inverse.  Basically at the start we have c and can use
C it while waiting for the inverse, whereas for the second and subsequent
C limbs it's the other way around, ie. we have the inverse and are waiting
C for c.
C
C At .Lentry the first two instructions in the loop have been done already.
C The load of f11=src[1] at the start (predicated on size>=2), and the
C calculation of q by the initial different scheme.
C
C
C Entry Sequence:
C
C In the entry sequence, the critical path is the calculation of the
C inverse, so this is begun first and optimized.  Apart from that, ar.lc is
C established nice and early so the br.cloop's should predict perfectly.
C And the load for the low limbs src[0] and src[1] can be initiated long
C ahead of where they're needed.
C
C
C Inverse Calculation:
C
C The initial 8-bit inverse is calculated using a table lookup.  If it hits
C L1 (which is likely if we're called several times) then it should take a
C total 4 cycles, otherwise hopefully L2 for 9 cycles.  This is considered
C the best approach, on balance.  It could be done bitwise, but that would
C probably be about 14 cycles (2 per bit beyond the first couple).  Or it
C could be taken from 4 bits to 8 with xmpy doubling as used beyond 8 bits,
C but that would be about 11 cycles.
C
C The table is not the same as binvert_limb_table, instead it's 256 bytes,
C designed to be indexed by the low byte of the divisor.  The divisor is
C always odd, so the relevant data is every second byte in the table.  The
C padding lets us use zxt1 instead of extr.u, the latter would cost an extra
C cycle because it must go down I0, and we're using the first I0 slot to get
C ip.  The extra 128 bytes of padding should be insignificant compared to
C typical ia64 code bloat.
C
C Having the table in .text allows us to use IP-relative addressing,
C avoiding a fetch from ltoff.  .rodata is apparently not suitable for use
C IP-relative, it gets a linker relocation overflow on GNU/Linux.
C
C
C Load Scheduling:
C
C In the main loop, the data loads are scheduled for an L2 hit, which means
C 6 cycles for the data ready to use.  In fact we end up 7 cycles ahead.  In
C any case that scheduling is achieved simply by doing the load (and xmpy.l
C for "si") in the immediately preceding iteration.
C
C The main loop requires size >= 2, and we handle size==1 by an initial
C br.cloop to enter the loop only if size>1.  Since ar.lc is established
C early, this should predict perfectly.
C
C
C Not done:
C
C Consideration was given to using a plain "(src[0]-c) % divisor" for
C size==1, but cycle counting suggests about 50 for the sort of approach
C taken by gcc __umodsi3, versus about 47 for the modexact.  (Both assuming
C L1 hits for their respective fetching.)
C
C Consideration was given to a test for high<divisor and replacing the last
C loop iteration with instead c-=src[size-1] followed by c+=d if underflow.
C Branching on high<divisor wouldn't be good since a mispredict would cost
C more than the loop iteration saved, and the condition is of course data
C dependent.  So the theory would be to shorten the loop count if
C high<divisor, and predicate extra operations at the end.  That would mean
C a gain of 6 when high<divisor, or a cost of 2 if not.
C
C Whether such a tradeoff is a win on average depends on assumptions about
C how many bits in the high and the divisor.  If both are uniformly
C distributed then high<divisor about 50% of the time.  But smallish
C divisors (less chance of high<divisor) might be more likely from
C applications (mpz_divisible_ui, mpz_gcd_ui, etc).  Though biggish divisors
C would be normal internally from say mpn/generic/perfsqr.c.  On balance,
C for the moment, it's felt the gain is not really enough to be worth the
C trouble.
C
C
C Enhancement:
C
C Process two source limbs per iteration using a two-limb inverse and a
C sequence like
C
C	ql  = low (c * il + sil)	quotient low limb
C	qlc = high(c * il + sil)
C	qh1 = low (c * ih + sih)	quotient high, partial
C
C	cl = high (ql * d + c)		carry out of low
C	qh = low (qlc * 1 + qh1)	quotient high limb
C
C	new c = high (qh * d + cl)	carry out of high
C
C This would be 13 cycles/iteration, giving 6.5 cycles/limb.  The two limb
C s*inverse as sih:sil = sh:sl * ih:il would be calculated off the dependent
C chain with 4 multiplies.  The bigger inverse would take extra time to
C calculate, but a one limb iteration to handle an odd size could be done as
C soon as 64-bits of inverse were ready.
C
C Perhaps this could even extend to a 3 limb inverse, which might promise 17
C or 18 cycles for 3 limbs, giving 5.66 or 6.0 cycles/limb.
C

ASM_START()
	.explicit

	.text
	.align	32
.Ltable:
data1	0,0x01, 0,0xAB, 0,0xCD, 0,0xB7, 0,0x39, 0,0xA3, 0,0xC5, 0,0xEF
data1	0,0xF1, 0,0x1B, 0,0x3D, 0,0xA7, 0,0x29, 0,0x13, 0,0x35, 0,0xDF
data1	0,0xE1, 0,0x8B, 0,0xAD, 0,0x97, 0,0x19, 0,0x83, 0,0xA5, 0,0xCF
data1	0,0xD1, 0,0xFB, 0,0x1D, 0,0x87, 0,0x09, 0,0xF3, 0,0x15, 0,0xBF
data1	0,0xC1, 0,0x6B, 0,0x8D, 0,0x77, 0,0xF9, 0,0x63, 0,0x85, 0,0xAF
data1	0,0xB1, 0,0xDB, 0,0xFD, 0,0x67, 0,0xE9, 0,0xD3, 0,0xF5, 0,0x9F
data1	0,0xA1, 0,0x4B, 0,0x6D, 0,0x57, 0,0xD9, 0,0x43, 0,0x65, 0,0x8F
data1	0,0x91, 0,0xBB, 0,0xDD, 0,0x47, 0,0xC9, 0,0xB3, 0,0xD5, 0,0x7F
data1	0,0x81, 0,0x2B, 0,0x4D, 0,0x37, 0,0xB9, 0,0x23, 0,0x45, 0,0x6F
data1	0,0x71, 0,0x9B, 0,0xBD, 0,0x27, 0,0xA9, 0,0x93, 0,0xB5, 0,0x5F
data1	0,0x61, 0,0x0B, 0,0x2D, 0,0x17, 0,0x99, 0,0x03, 0,0x25, 0,0x4F
data1	0,0x51, 0,0x7B, 0,0x9D, 0,0x07, 0,0x89, 0,0x73, 0,0x95, 0,0x3F
data1	0,0x41, 0,0xEB, 0,0x0D, 0,0xF7, 0,0x79, 0,0xE3, 0,0x05, 0,0x2F
data1	0,0x31, 0,0x5B, 0,0x7D, 0,0xE7, 0,0x69, 0,0x53, 0,0x75, 0,0x1F
data1	0,0x21, 0,0xCB, 0,0xED, 0,0xD7, 0,0x59, 0,0xC3, 0,0xE5, 0,0x0F
data1	0,0x11, 0,0x3B, 0,0x5D, 0,0xC7, 0,0x49, 0,0x33, 0,0x55, 0,0xFF


PROLOGUE(mpn_modexact_1c_odd)

	C r32	src
	C r33	size
	C r34	divisor
	C r35	carry

	.prologue
.Lhere:
{ .mmi;	add	r33 = -1, r33		C M0  size-1
	mov	r14 = 2			C M1  2
	mov	r15 = ip		C I0  .Lhere
}{.mmi;	setf.sig f6 = r34		C M2  divisor
	setf.sig f9 = r35		C M3  carry
	zxt1	r3 = r34		C I1  divisor low byte
}	;;

{ .mmi;	add	r3 = .Ltable-.Lhere, r3	C M0  table offset ip and index
	sub	r16 = 0, r34		C M1  -divisor
	.save	ar.lc, r2
	mov	r2 = ar.lc		C I0
}{.mmi;	.body
	setf.sig f13 = r14		C M2  2 in significand
	mov	r17 = -1		C M3  -1
ABI32(`	zxt4	r33 = r33')		C I1  size extend
}	;;

{ .mmi;	add	r3 = r3, r15		C M0  table entry address
ABI32(` addp4	r32 = 0, r32')		C M1  src extend
	mov	ar.lc = r33		C I0  size-1 loop count
}{.mmi;	setf.sig f12 = r16		C M2  -divisor
	setf.sig f8 = r17		C M3  -1
}	;;

{ .mmi;	ld1	r3 = [r3]		C M0  inverse, 8 bits
	ldf8	f10 = [r32], 8		C M1  src[0]
	cmp.ne	p6,p0 = 0, r33		C I0  test size!=1
}	;;

	C Wait for table load.
	C Hope for an L1 hit of 1 cycles to ALU, but could be more.
	setf.sig f7 = r3		C M2  inverse, 8 bits
(p6)	ldf8	f11 = [r32], 8		C M1  src[1], if size!=1
	;;

	C 5 cycles

	C f6	divisor
	C f7	inverse, being calculated
	C f8	-1, will be -inverse
	C f9	carry
	C f10	src[0]
	C f11	src[1]
	C f12	-divisor
	C f13	2
	C f14	scratch

	xmpy.l	f14 = f13, f7		C 2*i
	xmpy.l	f7 = f7, f7		C i*i
	;;
	xma.l	f7 = f7, f12, f14	C i*i*-d + 2*i, inverse 16 bits
	;;

	xmpy.l	f14 = f13, f7		C 2*i
	xmpy.l	f7 = f7, f7		C i*i
	;;
	xma.l	f7 = f7, f12, f14	C i*i*-d + 2*i, inverse 32 bits
	;;

	xmpy.l	f14 = f13, f7		C 2*i
	xmpy.l	f7 = f7, f7		C i*i
	;;

	xma.l	f7 = f7, f12, f14	C i*i*-d + 2*i, inverse 64 bits
	xma.l	f10 = f9, f8, f10	C sc = c * -1 + src[0]
	;;
ASSERT(p6, `
	xmpy.l	f15 = f6, f7 ;;	C divisor*inverse
	getf.sig r31 = f15 ;;
	cmp.eq	p6,p0 = 1, r31	C should == 1
')

	xmpy.l	f10 = f10, f7		C q = sc * inverse
	xmpy.l	f8 = f7, f8		C -inverse = inverse * -1
	br.cloop.sptk.few.clr .Lentry	C main loop, if size > 1
	;;

	C size==1, finish up now
	xma.hu	f9 = f10, f6, f9	C c = high(q * divisor + c)
	mov	ar.lc = r2		C I0
	;;
	getf.sig r8 = f9		C M2  return c
	br.ret.sptk.many b0



.Ltop:
	C r2	saved ar.lc
	C f6	divisor
	C f7	inverse
	C f8	-inverse
	C f9	carry
	C f10	src[i] * inverse
	C f11	scratch src[i+1]

	add	r16 = 160, r32
	ldf8	f11 = [r32], 8		C src[i+1]
	;;
	C 2 cycles

	lfetch	[r16]
	xma.l	f10 = f9, f8, f10	C q = c * -inverse + si
	;;
	C 3 cycles

.Lentry:
	xma.hu	f9 = f10, f6, f9	C c = high(q * divisor + c)
	xmpy.l	f10 = f11, f7		C si = src[i] * inverse
	br.cloop.sptk.few.clr .Ltop
	;;



	xma.l	f10 = f9, f8, f10	C q = c * -inverse + si
	mov	ar.lc = r2		C I0
	;;
	xma.hu	f9 = f10, f6, f9	C c = high(q * divisor + c)
	;;
	getf.sig r8 = f9		C M2  return c
	br.ret.sptk.many b0

EPILOGUE()
