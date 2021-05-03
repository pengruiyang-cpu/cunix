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




.text
.align 8

.globl putc

putc:
	/* character is in EDI */
	movl %edi, %eax

	/* rdi = *framebuffer */
	movq framebuffer(%rip), %rdi

	/* (es:di) = al, di++ */
	cld
	stosb

	movb 0xf0, %al
	stosb

	movq %rdi, (framebuffer)

	ret



.data
.align 8

framebuffer: .quad 0x000b8000

