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




#ifndef INCLUDED_STRING_H
#define INCLUDED_STRING_H



/* copy src to dest for n bytes */
extern inline void *memcpy(void *dest, void *src, __uint64_t n) {
	__asm__ (
		"cld\n\t"
		"rep movsb\n\t"

		:: "c" (n), "S" (src), "D" (dest)
	);

	return dest;
}


/* set n to src for n bytes */
extern inline void *memset(void *dest, char c, __uint64_t n) {
	__asm__ (
		"cld\n\t"
		"rep stosb\n\t"

		:: "c" (n), "D" (dest), "a" (c)
	);

	return dest;
}


/* set n to src for n words (n must be power of 2) */
extern inline void *memsetw(void *dest, __uint16_t c, __uint64_t n) {
	__asm__ (
		"cld\n\t"
		"rep stosw\n\t"

		:: "c" (n >> 1), "D" (dest), "a" (c)
	);

	return dest;
}


/* set n to src for n dwords (n must be power of 4) */
extern inline void *memsetl(void *dest, __uint32_t c, __uint64_t n) {
	__asm__ (
		"cld\n\t"
		"rep stosl\n\t"

		:: "c" (n >> 2), "D" (dest), "a" (c)
	);

	return dest;
}


/* set n to src for n quads (n must be power of 8) */
extern inline void *memsetq(void *dest, __uint64_t c, __uint64_t n) {
	__asm__ (
		"cld\n\t"
		"rep stosq\n\t"

		:: "c" (n >> 3), "D" (dest), "a" (c)
	);

	return dest;
}




#endif

