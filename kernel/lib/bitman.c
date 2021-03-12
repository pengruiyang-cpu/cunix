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




#include <lib/rlib.h>


/*
	find a new bit in bm->bitmap. 

	STEPS: 
		1. save free position. 
		2. find a new free position. 
		3. save new free position. 
*/
unsigned int bitman_alloc(struct bitmap_manager *bm) {
	unsigned int p = bm->next_free;
	bitmap_set(bm->bitmap, bm->next_free, 1);

	for (; bitmap_read(bm->bitmap, bm->next_free) == 1; bm->next_free++);

	return p;
}


/*
	free a bit. 

	STEPS: 
		1. free bit pos. 
		2. if pos is lowwer than bm->next_free
			2a. set bm->next_free = pos. 
*/
void bitman_free(struct bitmap_manager *bm, unsigned int pos) {
	bitmap_set(bm->bitmap, pos, 0);

	if (pos < bm->next_free) {
		bm->next_free = pos;
	}
	return;
}
