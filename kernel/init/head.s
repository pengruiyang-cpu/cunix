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




.align 8
.text

.globl _start
_start:
	lgdt gdt_desc(%rip)
	lidt idt_desc(%rip)

	/* first, setup segment descriptor (for future) */
	movq setup_segment(%rip), %rax

	pushq $0x08
	pushq %rax
	lretq


setup_segment:
	.quad switch_segment


switch_segment:
	/* segment registers are 16-bits, but use `rax` is faster than `ax` */
	movq $0x10, %rax
	movq %rax, %ds
	movq %rax, %es
	movq %rax, %fs
	movq %rax, %gs

	movq %rax, %ss
	movq $0x0000000000007c00, %rsp

	movq init_kernel(%rip), %rax
	pushq $0x08
	pushq %rax

	lretq
	

init_kernel:
	.quad init



setup_pde:
	



.align 8
.data

.globl gdt_table

gdt_table:
	/* first entry must be a null descriptor */
	.quad 0x0000000000000000

	/* kernel code 64-bits */
	.quad 0x0020980000000000

	/* kernel data 64-bits */
	.quad 0x0000920000000000

	/* user code 64-bits */
	.quad 0x0020f80000000000

	/* user data 64-bits */
	.quad 0x0000f20000000000

	/* kernel code 32-bits */
	.quad 0x00cf9a000000ffff

	/* kernel data 32-bits */
	.quad 0x00cf92000000ffff

	.fill 10, 8, 0

end_gdt:

gdt_desc:
	.word end_gdt - gdt_table
	.quad gdt_table

.globl idt_table

idt_table:
	/* this will takes a warning */
	/* .fill 256, 16, 0 */

	.fill 512, 8, 0


end_idt:

idt_desc:
	.word end_idt - idt_table
	.quad idt_table




