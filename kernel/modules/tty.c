/* Copyright (C) 2021 Rain */

/* This file is part of Cunix. */

/* 
  Cunix is free software: you can redistribute it and/or modify 
  it under the terms of the GNU General Public License as published by 
  the Free Software Foundation, either version 3 of the License, or 
  (at your option) and later version. 
*/

/*
  Cunix is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
  GNU General Public License for more details. 
*/

/*
  You should have received a copy of the GNU General Public License 
   along with Cunix. If not, see <https://www.gnu.org/licenses/>.  
*/




#include <kernel/init.h>
#include <kernel/types.h>
#include <kernel/errno.h>

#include <modules/tty.h>
#include <arch/io.h>
#include <arch/sys.h>

#include <stdarg.h>




__uint16_t read_cursor(void) {
	__uint16_t pos = 0;

	outb(CURSORCTL_POSLO, CURSOR_INDEX);
	pos |= inb(CURSOR_DATA);

	outb(CURSORCTL_POSHI, CURSOR_INDEX);
	pos |= ((__uint16_t) inb(CURSOR_DATA)) << 8;

	return pos;
}



void write_cursor(__uint16_t pos) {
	outb(CURSORCTL_POSLO, CURSOR_INDEX);
	outb((__uint8_t) (pos & 0xff), CURSOR_DATA);

	outb(CURSORCTL_POSHI, CURSOR_INDEX);
	outb((__uint8_t) ((pos >> 8) & 0xff), CURSOR_DATA);

	return;
}



__uint64_t printf(const char *s, ...) {
	/* l: character puts (no '%') */
	__uint64_t i, l;
	/* if prev character is '%', state = '%' */
	char state, c;
	/* fmt_s only use in %s, but we cannot define variables in switch-case */
	char *fmt_s;
	va_list values;

	va_start(values, s);
	state = 0;

	for (i = 0, l = 0; s[i]; i++) {
		c = s[i];
		/* check state */
		if (!state) {
			if (c == '%') {
				state = '%';
				continue;
			}

			/* c != '%' (it's not a formater), put it */
			else {
				putc(c);
				l++;
				continue;
			}
		}

		/* it's a formater */
		else {
			if (c == 'd') {
				l += printint((int) va_arg(values, int), 10, 1);
			}

			else if (c == 'x') {
				/* `x` is 64-bits, I think it's */
				l += printint((long) va_arg(values, long), 16, 0);
			}

			else if (c == 's') {
				fmt_s = (char *) va_arg(values, char *);
				if (!fmt_s) 
					fmt_s = "(null)";
						
				/* put while end of fmt_s */
				while (*fmt_s) {
					putc(*fmt_s);
					fmt_s++;
					l++;
				}
			}
			
			else if (c == 'c') {
				/* `char` aligned to `int` in GCC */
				putc((char) va_arg(values, int));
				l++;
			}

			else if (c == '%') {
				/* put % on screen */
				putc(c);
				l++;
			}

			else {
				/* don't forget put % */
				putc('%');
				putc(c);
				l++;
			}

			state = 0;
		}
	}


	/* update cursor position */
	write_cursor(read_cursor() + (__uint16_t) l);

	va_end(values);

	return i;
}
 

__uint64_t printint(long n, int base, int sign) {
	static char digits[] = {"0123456789abcdef"};
	char buf[32];
	/* neg: x < 0 && signed interger */
	int i, neg, j;
	/* x: real number should put */
	__uint64_t x;

	if (n < 0 && sign) {
		neg = 1;
		x = -n;
	}

	else {
		neg = 0;
		x = n;
	}

	i = 0;
	do {
		/* get string of based-number */
		/* the first bit of 10-based digit is at buf[15] */
		buf[i++] = digits[x % base];
	} while (x /= base);

	if (neg) 
		buf[i++] = '-';

	j = i;
	while (--j >= 0) 
		putc(buf[j]);

	return i;
}
