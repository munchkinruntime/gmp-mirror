/* operator>> -- C++-style input of mpf_t.

Copyright 2001, 2003 Free Software Foundation, Inc.

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

#include <cctype>
#include <iostream>
#include <string>
#include <clocale>    /* for localeconv */

#include "gmp.h"
#include "gmp-impl.h"

using namespace std;


istream &
operator>> (istream &i, mpf_ptr f)
{
  int base;
  char c = 0;
  string s;
  bool ok = false;

  /* C decimal point, as expected by mpf_set_str */
  const char *lconv_point = localeconv()->decimal_point;

  /* C++ decimal point */
#if HAVE_STD__LOCALE
  char point_char = use_facet< numpunct<char> >(i.getloc()).decimal_point();
#else
  const char *point = lconv_point;
  char point_char = *point;
#endif

  i.get(c); // start reading

  if (i.flags() & ios::skipws) // skip initial whitespace
    while (isspace(c) && i.get(c))
      ;

  if (c == '-' || c == '+') // sign
    {
      if (c == '-')
	s = "-";
      i.get(c);
    }

  while (isspace(c) && i.get(c)) // skip whitespace
    ;

  base = 10; // octal/hex floats currently unsupported
  __gmp_istream_set_digits(s, i, c, ok, base); // read the number

  // look for the C++ radix point, but put the C one in for mpf_set_str
  if (c == point_char)
    {
#if HAVE_STD__LOCALE
      i.get(c);
#else // lconv point can be multi-char
      for (;;)
        {
          i.get(c);
          point++;
          if (*point == '\0')
            break;
          if (c != *point)
            goto fail;
        }
#endif
      s += lconv_point;
      __gmp_istream_set_digits(s, i, c, ok, base); // read the mantissa
    }

  if (ok && (c == 'e' || c == 'E' || c == '@')) // exponent
    {
      s += c;
      i.get(c);
      ok = false; // exponent is mandatory

      if (c == '-' || c == '+') // sign
	{
	  s += c;
	  i.get(c);
	}

      while (isspace(c) && i.get(c)) // skip whitespace
	;

      __gmp_istream_set_digits(s, i, c, ok, base); // read the exponent
    }

  if (i.good()) // last character read was non-numeric
    i.putback(c);
  else if (i.eof() && ok) // stopped just before eof
    i.clear();

  if (ok)
    mpf_set_str(f, s.c_str(), base); // extract the number
  else
    {
    fail:
      i.setstate(ios::failbit); // read failed
    }

  return i;
}
