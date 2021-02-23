; Copyright (C) 2021 Rain

; This file is part of Cunix. 
; Cunix is free software: you can redistribute it and/or modify 
; it under the terms of the GNU General Public License as published by 
; the Free Software Foundation, either version 3 of the License, or 
; (at your option) and later version. 

; Cunix is distributed in the hope that it will be useful, 
; but WITHOUT ANY WARRANTY; without even the implied warranty of 
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
; GNU General Public License for more details. 

; You should have received a copy of the GNU General Public License 
; along with Cunix. If not, see <https://www.gnu.org/licenses/>.  




org 0x8200

bits 64

_start:
	mov byte [0xb8000], 'K'

	call setup_idt
	lidt [idt64_descriptor]

	sti

	jmp $


setup_idt:
	lea rdx, ignore_int
	mov rax, (0x08 << 16)
	mov ax, dx
	mov rcx, (0x8e00 << 32)
	add rax, rcx
	mov ecx, edx
	shr ecx, 16
	shl rcx, 48
	add rax, rcx
	shr rdx, 32

	; we save IDT at 0x0000000000000000 like BIOS
	lea rdi, 0x0000000000000000
	mov rcx, 256

.setup_loop:
	mov [rdi], rax
	mov [rdi + 8], rdx
	add rdi, 0x10
	dec rcx
	jne .setup_loop

	ret


ignore_int:
	add byte [0xb8000], 1

	; CPU will cli when it call ignore_int
	hlt


idt64_length equ 0xff * 16

idt64_descriptor:
	dw idt64_length
	dd 0x0000000000000000

