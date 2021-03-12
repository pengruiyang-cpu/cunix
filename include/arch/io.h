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



#ifndef INCLUDED_IO_H
#define INCLUDED_IO_H

#include <kernel/types.h>


typedef __uint16_t port_t;


#define inb(port) ({ \
	__uint8_t _r; \
	__asm__ volatile ("inb %%dx, %%al" : "=a" (_r) : "d" (port)); \
	_r; \
})

#define inw(port) ({ \
	__uint16_t _r; \
	__asm__ volatile ("inw %%dx, %%ax" : "=a" (_r) : "d" (port)); \
	_r; \
})

#define inl(port) ({ \
	__uint32_t _r; \
	__asm__ volatile ("inl %%dx, %%eax" : "=a" (_r) : "d" (port)); \
	_r; \
})


#define outb(value, port) \
	__asm__ volatile ("outb %%al, %%dx" :: "a" (value), "d" (port));

#define outw(value, port) \
	__asm__ volatile ("outw %%ax, %%dx" :: "a" (value), "d" (port));

#define outl(value, port) \
	__asm__ volatile ("outl %%eax, %%dx" :: "a" (value), "d" (port));


#endif
