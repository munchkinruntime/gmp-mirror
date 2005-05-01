dnl  PowerPC-64 mpn_rsh1add_n -- rp[] = (up[] + vp[]) >> 1

dnl  Copyright 2003 Free Software Foundation, Inc.

dnl  This file is part of the GNU MP Library.

dnl  The GNU MP Library is free software; you can redistribute it and/or modify
dnl  it under the terms of the GNU Lesser General Public License as published
dnl  by the Free Software Foundation; either version 2.1 of the License, or (at
dnl  your option) any later version.

dnl  The GNU MP Library is distributed in the hope that it will be useful, but
dnl  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
dnl  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
dnl  License for more details.

dnl  You should have received a copy of the GNU Lesser General Public License
dnl  along with the GNU MP Library; see the file COPYINGL(IB).  If not, write to
dnl  the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
dnl  MA 02111-1307, USA.

include(`../config.m4')

C		cycles/limb
C POWER3/PPC630:     2		(1.5 c/l should be possible)
C POWER4/PPC970:     4		(2.0 c/l should be possible)

C INPUT PARAMETERS
C rp	r3
C up	r4
C vp	r5
C n	r6

define(`rp',`r3')
define(`up',`r4')
define(`vp',`r5')

define(`s0',`r6')
define(`s1',`r7')
define(`x',`r0')
define(`u0',`r8')
define(`u1',`r9')
define(`v0',`r10')
define(`v1',`r11')


ASM_START()
PROLOGUE(mpn_rsh1add_n)
	mtctr	r6		C copy size to count register
	addi	rp, rp, -8

	ld	u1, 0(up)
	ld	v1, 0(vp)
	addc	x, v1, u1
	rldicl	r12, x, 0, 63	C return value
	srdi	s1, x, 1

	bdz	L(1)

	ld	u0, 8(up)
	ld	v0, 8(vp)

	bdz	L(end)

L(oop):	ldu	u1, 16(up)
	ldu	v1, 16(vp)
	adde	x, v0, u0
	srdi	s0, x, 1
	rldimi	s1, x, 63, 0
	std	s1, 8(rp)

	bdz	L(exit)

	ld	u0, 8(up)
	ld	v0, 8(vp)
	adde	x, v1, u1
	srdi	s1, x, 1
	rldimi	s0, x, 63, 0
	stdu	s0, 16(rp)

	bdnz	L(oop)

L(end):	adde	x, v0, u0
	srdi	s0, x, 1
	rldimi	s1, x, 63, 0
	std	s1, 8(rp)

	li	x, 0
	addze	x, x
	rldimi	s0, x, 63, 0
	std	s0, 16(rp)
	mr	r3, r12
	blr

L(exit):	adde	x, v1, u1
	srdi	s1, x, 1
	rldimi	s0, x, 63, 0
	stdu	s0, 16(rp)

L(1):	li	x, 0
	addze	x, x
	rldimi	s1, x, 63, 0
	std	s1, 8(rp)
	mr	r3, r12
	blr
EPILOGUE()
