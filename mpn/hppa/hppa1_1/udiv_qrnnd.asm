dnl  HP-PA  __udiv_qrnnd division support, used from longlong.h.
dnl  This version runs fast on PA 7000 and later.

dnl  Copyright 1993, 1994, 2000, 2001 Free Software Foundation, Inc.

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
dnl  along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
dnl  the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
dnl  MA 02111-1307, USA.

include(`../config.m4')

C INPUT PARAMETERS
C rem_ptr	gr26
C n1		gr25
C n0		gr24
C d		gr23

ASM_START()
	RODATA
	INT64(L(0000), 0x43f00000, 0x0)	C 2^64

PROLOGUE(mpn_udiv_qrnnd)
C	.callinfo	frame=64,no_calls

	ldo		64(%r30),%r30

	stws		%r25,-16(0,%r30)	C n_hi
	stws		%r24,-12(0,%r30)	C n_lo
ifdef(`PIC',
`	bl		L(0),%r31
	dep		%r0,31,2,%r31

	.label	L(0)
	addil		LR%L(0000)-L(0),%r31
	ldo		RR%L(0000)-L(0)(%r1),%r31',
`
	ldil		`L'%L(0000),%r31
	ldo		R%L(0000)(%r31),%r31')

	fldds		-16(0,%r30),%fr5
	stws		%r23,-12(0,%r30)
	comib,<=	0,%r25,L(1)
	fcnvxf,dbl,dbl	%fr5,%fr5
	fldds		0(0,%r31),%fr4
	fadd,dbl	%fr4,%fr5,%fr5

	.label	L(1)
	fcpy,sgl	%fr0,%fr6L
	fldws		-12(0,%r30),%fr6R
	fcnvxf,dbl,dbl	%fr6,%fr4

	fdiv,dbl	%fr5,%fr4,%fr5

	fcnvfx,dbl,dbl	%fr5,%fr4
	fstws		%fr4R,-16(%r30)
	xmpyu		%fr4R,%fr6R,%fr6
	ldws		-16(%r30),%r28
	fstds		%fr6,-16(0,%r30)
	ldws		-12(0,%r30),%r21
	ldws		-16(0,%r30),%r20
	sub		%r24,%r21,%r22
	subb		%r25,%r20,%r20
	comib,=		0,%r20,L(2)
	ldo		-64(%r30),%r30

	add		%r22,%r23,%r22
	ldo		-1(%r28),%r28

	.label	L(2)
	bv		0(%r2)
	stws		%r22,0(0,%r26)
EPILOGUE(mpn_udiv_qrnnd)
