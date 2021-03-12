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




#include <kernel/types.h>

void bitmap_set(unsigned char *bitmap, unsigned int pos, unsigned char value) {
	unsigned char mask = 0x80 >> (pos & 0x7);
	if (value) {
		bitmap[pos >> 3] |= mask;
	}
	else {
		bitmap[pos >> 3] &= ~mask;
	}
}

char bitmap_read(unsigned char *bitmap, unsigned int pos) {
	unsigned char mask = 0x80 >> (pos & 0x7);

	return (mask & bitmap[pos >> 3]) == mask ? 1 : 0;
}

