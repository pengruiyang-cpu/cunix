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


.globl panic

panic:
	leaq panic_msg(%rip), %rsi
	call print

	movq %rdi, %rsi
	call print

die:
	hlt
	jmp die



.globl __stack_chk_fail

__stack_chk_fail:
	/* display on screen: kernel panic: stack check failed. */
	leaq stackfail_msg(%rip), %rdi
	call panic

	/* it never go here */



/* no `.globl` with this. this is temporary */
print:
	pushq %rdi
	/* message address in RSI */
	movq tmp_fb(%rip), %rdi
	
	/* RDI / RSI ++ */
	cld

	movb $0x07, %ah

.loop:
	/* load to AL from RSI */
	lodsb
	cmpb $0x00, %al
	je .ret

	/* store to RDI from AX */
	stosw

	jmp .loop

.ret:
	movq %rdi, tmp_fb(%rip)
	popq %rdi
	ret


.data
.align 8

panic_msg: .asciz "kernel panic: "
stackfail_msg: .asciz "stack check failed"
tmp_fb: .quad 0x00000000000b8000

