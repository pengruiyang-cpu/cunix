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




#ifndef INCLUDED_TTY_H
#define INCLUDED_TTY_H

/* index register of cursor */
#define CURSOR_INDEX 0x03d4

/* data register of cursor */
#define CURSOR_DATA  0x03d5

/* write to CURSOR_INDEX */
#define CURSORCTL_POSHI 0x0e
#define CURSORCTL_POSLO 0x0f

#define TEXT_VGA_X 80


#ifndef ASSEMBLY

#include <stdarg.h>

/* kernel/asm/tty.c */

void tty_init(void);

void putc(char c);

/* kernel/modules/tty.c */

/* return value: length of string printed */

/* we use number formats (1B per format), not % */
__uint64_t printf(const char *fmt, ...);

__uint64_t printint(long, int, int);

__uint16_t read_cursor(void);

void write_cursor(__uint16_t pos);

#endif


#endif
