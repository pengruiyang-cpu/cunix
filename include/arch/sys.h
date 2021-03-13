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



#ifndef INCLUDED_SYS_H
#define INCLUDED_SYS_H

#include <kernel/types.h>


#define sgdt(addr) __asm__ __volatile__ ("sgdt %0" : "=m" (addr) : :)
#define lgdt(addr) __asm__ __volatile__ ("lgdt %0" : : "m" (addr))

#define sidt(addr) __asm__ __volatile__ ("sidt %0" : "=m" (addr) : :)
#define lidt(addr) __asm__ __volatile__ ("lidt %0" : : "m" (addr))


#define pause() __asm__ __volatile__ ("pause");
#define nop() __asm__ __volatile__ ("nop");
#define hlt() __asm__ __volatile__ ("hlt");


#endif
