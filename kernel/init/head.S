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




#include <arch/x86/paging.h>


.align 8
.text

.globl _start

/* 
 * We can't use any symbol addresses before we setup PML4-entry. 
 * Because linker use 0xffff8000 to fill all addresses (see kernel/kernel.lds). 
 * So, we must setup PML4E first. 
 */
_start:
	movq $PML4_ADDR, %rax
	movq $PDPT_ADDR | PATT_USER, 2048(%rax)
	movq %rax, %cr3

	/* ok, now we can use addresses because we had been set PML4E */

	lgdt gdt_desc(%rip)
	lidt idt_desc(%rip)

	/* first, setup segment descriptor */
	leaq switch_segment(%rip), %rax

	pushq $0x08
	pushq %rax
	lretq



switch_segment:
	/* segment registers are 16-bits, but use `rax` is faster than `ax` */
	movq $0x10, %rax
	movq %rax, %ds
	movq %rax, %es
	movq %rax, %fs
	movq %rax, %gs

	movq %rax, %ss
	movq $0x0000000000007c00, %rsp

	callq setup_idt

	/* enable interrupt in init() */

	leaq init(%rip), %rax
	pushq $0x08
	pushq %rax

	lretq



/* setup paging */
setup_paging:
	/* set attributes for 0 - 64MB pages */

	/* start address 0 */
	xorq %rax, %rax

	/* page address (first set in boot/x86/loader.asm) */
	movq $PTE_ADDR, %rdi

	/* count of entries will set */
	movq $64 * 1048576 / PAGE_SIZE, %rcx

	cld

rep_spage:
	orq $PATT_KERNEL, %rax

	/* repeat while rcx > 0, then rcx-- */
	stosq
	addq $PAGE_SIZE, %rax

	loop rep_spage

	ret

	
	


/* setup IDT entries */

setup_idt:
	/* offset address of interrupt handler */
	leaq default_int(%rip), %rdx

	/* RAX is low 64 bit of IDT-entry */
	/* selector: 0x08 */
	movq $(0x08 << 16), %rax
	movw %dx, %ax
	/* 8E means present, DPL = 0, TYPE = E, and IST = 0 */
	movq $(0x8e00 << 32), %rcx
	addq %rcx, %rax

	/* offset low 32 bit to RCX */
	movl %edx, %ecx
	/* only high 16 bits */
	shrl $16, %ecx
	shlq $48, %rcx

	addq %rcx, %rax

	/* only high 32 bits */
	shrq $32, %rdx

	leaq idt_table(%rip), %rdi
	/* entries in IDT */
	movq $256, %rcx

rep_sidt:
	movq %rax, (%rdi)
	movq %rdx, 8(%rdi)
	addq $0x10, %rdi
	dec %rcx
	jnz rep_sidt

	retq



default_int:
	leaq int_msg(%rip), %rdi
	call printf

default_int_die:
	hlt
	jmp default_int_die

	iretq



.section .rodata
.align 8

int_msg: .asciz "unknow interrupt or fault"

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



