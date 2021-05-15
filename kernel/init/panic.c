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

#include <arch/sys.h>
#include <modules/tty.h>



void panic(char *s) {
	__uint64_t a, b, c;

	a = get_rax(); b = get_rcx(); c = get_rdx();

	printf("RAX: %p  RCX: %p  RDX: %p\n", a, b, c);

	a = get_rbx(); b = get_rsp(); c = get_rbp();

	printf("RBX: %p  RSP: %p  RBP: %p\n", a, b, c);

	a = get_rsi(); b = get_rdi(); c = get_r8();

	printf("RSI: %p  RDI: %p  R8 : %p\n", a, b, c);

	a = get_r9(); b = get_r10(); c = get_r11();

	printf("R9: %p   R10: %p  R11: %p\n", a, b, c);

	a = get_r12(); b = get_r13(); c = get_r14();

	printf("R12: %p  R13: %p  R14: %p\n", a, b, c);

	a = get_r15();

	printf("R15: %p\n", a);

	printf("\nKernel panic: %s\n", s);

	for (;;);
}
