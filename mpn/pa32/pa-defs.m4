divert(-1)

dnl  m4 macros for HPPA assembler.

dnl  Copyright 2002 Free Software Foundation, Inc.
dnl
dnl  This file is part of the GNU MP Library.
dnl
dnl  The GNU MP Library is free software; you can redistribute it and/or
dnl  modify it under the terms of the GNU Lesser General Public License as
dnl  published by the Free Software Foundation; either version 2.1 of the
dnl  License, or (at your option) any later version.
dnl
dnl  The GNU MP Library is distributed in the hope that it will be useful,
dnl  but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl  Lesser General Public License for more details.
dnl
dnl  You should have received a copy of the GNU Lesser General Public
dnl  License along with the GNU MP Library; see the file COPYING.LIB.  If
dnl  not, write to the Free Software Foundation, Inc., 59 Temple Place -
dnl  Suite 330, Boston, MA 02111-1307, USA.


dnl  hppa assembler comments are introduced with ";".
dnl
dnl  For cooperation with cpp, aparently lines "# 123" set the line number,
dnl  and other lines starting with a "#" are ignored.

changecom(;)


dnl  Called: PROLOGUE_cpu(GSYM_PREFIX`'foo)
dnl          EPILOGUE_cpu(GSYM_PREFIX`'foo)
dnl
dnl  These are the same as the basic PROLOGUE_cpu and EPILOGUE_cpu in
dnl  mpn/asm-defs.m4, but using .proc / .procend.  These are standard and on
dnl  an ELF system they do what .type and .size normally do.

define(`PROLOGUE_cpu',
m4_assert_numargs(1)
	`.code
	ALIGN(8)
	.proc	`$1'
	.export	`$1',entry
`$1'LABEL_SUFFIX')


define(`EPILOGUE_cpu',
m4_assert_numargs(1)
`	.procend')

divert
