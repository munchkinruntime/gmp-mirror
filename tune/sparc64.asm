dnl  sparc_tick -- sparc v9 64-bit time stamp counter access routine.

dnl  Copyright (C) 2000 Free Software Foundation, Inc.
dnl 
dnl  This file is part of the GNU MP Library.
dnl 
dnl  The GNU MP Library is free software; you can redistribute it and/or
dnl  modify it under the terms of the GNU Library General Public License as
dnl  published by the Free Software Foundation; either version 2 of the
dnl  License, or (at your option) any later version.
dnl 
dnl  The GNU MP Library is distributed in the hope that it will be useful,
dnl  but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl  Library General Public License for more details.
dnl 
dnl  You should have received a copy of the GNU Library General Public
dnl  License along with the GNU MP Library; see the file COPYING.LIB.  If
dnl  not, write to the Free Software Foundation, Inc., 59 Temple Place -
dnl  Suite 330, Boston, MA 02111-1307, USA.

include(`../config.m4')


C mp_limb_t speed_cyclecounter (unsigned long p[2]);

ASM_START()
PROLOGUE(speed_cyclecounter)
	rd	%tick,%g1
	stx	%g1,[%o0]		C low
	xor	%g1,%g1,%g1
	stx	%g1,[%o0+8]		C high
	retl
	nop
EPILOGUE(speed_cyclecounter)
