dnl  IA-64 mpn_copyd -- copy limb vector, decrementing.

dnl  Copyright 2001, 2002 Free Software Foundation, Inc.

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
C rp = r32
C sp = r33
C n = r34

C         cycles/limb
C Itanium:    1
C Itanium 2:  0.5


ASM_START()
PROLOGUE(mpn_copyd)
	.prologue
	.save ar.lc, r2
		mov	r2 = ar.lc
	.body
ifdef(`HAVE_ABI_32',
`		addp4	r32 = 0, r32
		addp4	r33 = 0, r33
		sxt4	r34 = r34
		;;
')
		and	r14 = 3, r34
		cmp.ge	p14, p15 = 3, r34
		add	r34 = -1, r34
		;;
		cmp.eq	p8, p9 = 1, r14
		shladd	r32 = r34, 3, r32
		shladd	r33 = r34, 3, r33
		add	r34 = -3, r34
		cmp.eq	p10, p11 = 2, r14
		cmp.eq	p12, p13 = 3, r14
		;;
	  (p8)	br.dptk	.Lb01
	  (p10)	br.dptk	.Lb10
	  (p12)	br.dptk	.Lb11

.Lb00:	C  n = 0, 4, 8, 12, ...
	  (p14)	br.dptk	.Ls00
		;;
		add	r21 = -8, r33
		ld8	r16 = [r33], -16
		shr	r15 = r34, 2
		;;
		ld8	r17 = [r21], -16
		mov	ar.lc = r15
		ld8	r18 = [r33], -16
		add	r20 = -8, r32
		;;
		ld8	r19 = [r21], -16
		br.cloop.dptk .Loop
		;;
		br.sptk	.Lend
		;;

.Lb01:	C  n = 1, 5, 9, 13, ...
  { .mib;	add	r21 = 0, r33
		add	r20 = 0, r32
		nop.b	0
} { .mib;	add	r33 = -8, r33
		add	r32 = -8, r32
		nop.b	0
		;;
}
		ld8	r19 = [r21], -16
		shr	r15 = r34, 2
	  (p14)	br.dptk	.Ls01
		;;
		ld8	r16 = [r33], -16
		mov	ar.lc = r15
		;;
		ld8	r17 = [r21], -16
		ld8	r18 = [r33], -16
		br.sptk	.Li01
		;;

.Lb10:	C  n = 2,6, 10, 14, ...
		add	r21 = -8, r33
		add	r20 = -8, r32
		ld8	r18 = [r33], -16
		shr	r15 = r34, 2
		;;
		ld8	r19 = [r21], -16
		mov	ar.lc = r15
	  (p14)	br.dptk	.Ls10
		;;
		ld8	r16 = [r33], -16
		ld8	r17 = [r21], -16
		br.sptk	.Li10
		;;

.Lb11:	C  n = 3, 7, 11, 15, ...
  { .mib;	add	r21 = 0, r33
		add	r20 = 0, r32
		nop.b	0
} { .mib;	add	r33 = -8, r33
		add	r32 = -8, r32
		nop.b	0
		;;
}
		ld8	r17 = [r21], -16
		shr	r15 = r34, 2
		;;
		ld8	r18 = [r33], -16
		mov	ar.lc = r15
		ld8	r19 = [r21], -16
	  (p14)	br.dptk	.Ls11
		;;
		ld8	r16 = [r33], -16
		br.sptk	.Li11
		;;

		.align	32
.Loop:
.Li00:
{ .mmb;		st8	[r32] = r16, -16
		ld8	r16 = [r33], -16
		nop.b	0
}
.Li11:
{ .mmb;		st8	[r20] = r17, -16
		ld8	r17 = [r21], -16
		nop.b	0
		;;
}
.Li10:
{ .mmb;		st8	[r32] = r18, -16
		ld8	r18 = [r33], -16
		nop.b	0
}
.Li01:
{ .mmb;		st8	[r20] = r19, -16
		ld8	r19 = [r21], -16
		br.cloop.dptk .Loop
		;;
}
.Lend:		st8	[r32] = r16, -16
.Ls11:		st8	[r20] = r17, -16
		;;
.Ls10:		st8	[r32] = r18, -16
.Ls01:		st8	[r20] = r19, -16
.Ls00:		mov	ar.lc = r2
		br.ret.sptk.many rp
EPILOGUE(mpn_copyd)
ASM_END()
