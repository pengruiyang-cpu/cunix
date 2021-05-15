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


#define getreg(regname) ({ \
	__uint64_t res; \
	__asm__ __volatile__ ("movq %%" regname ", %0" : "=r" (res)); \
	res; \
})

#define get_rax() getreg("rax")
#define get_rcx() getreg("rcx")
#define get_rdx() getreg("rdx")
#define get_rbx() getreg("rbx")

#define get_rsp() getreg("rsp")
#define get_rbp() getreg("rbp")
#define get_rsi() getreg("rsi")
#define get_rdi() getreg("rdi")

#define get_r8()  getreg("r8")
#define get_r9()  getreg("r9")
#define get_r10() getreg("r10")
#define get_r11() getreg("r11")

#define get_r12() getreg("r12")
#define get_r13() getreg("r13")
#define get_r14() getreg("r14")
#define get_r15() getreg("r15")


#endif
