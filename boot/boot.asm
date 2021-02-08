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




BI_BOOTDEV equ 0x7e00

org 0x7c00


xor ax, ax

mov ds, ax
mov es, ax

mov ss, ax
mov sp, 0x7c00

; display message: `Cunix is booting...`


; boot device driver number is in DL (by BIOS-19)
mov [BI_BOOTDEV], dl


mov si, message
call print

call load_loader

jmp 0x0000:0x8000


message: db "Cunix is booting...", 0x0d, 0x0a, 0x00
diskpanic_message: db "read disk failed", 0x0d, 0x0a, 0x00
panic_message: db "panic: ", 0x00

print:
	; SI: message address
	mov al, [si]
	add si, 1

	cmp al, 0x00
	je .ret

	mov ah, 0x0e
	mov bx, 0x0f
	int 0x10

	jmp print

.ret:
	ret


load_loader:
	mov ax, 0x0201
	mov dx, 0x0000
	mov dl, [BI_BOOTDEV]
	mov cx, 0x0002
	mov bx, 0x8000
	int 0x13

	mov di, diskpanic_message

	jc .try_lba

	ret

.try_lba:
	mov ax, 0x0002
	mov cl, 0x0001
	mov bx, 0x8000
	call read_lba

	jc panic
	ret

read_lba:
	push dword 0x00000000
	push dword eax
	push word es
	push word bx
	push word cx
	push word 0x0010

	mov ah, 0x42
	mov dl, 0x00
	mov si, sp
	int 0x13
	add sp, 0x10

	ret


panic:
	mov si, panic_message
	call print

	mov si, di
	call print

	hlt
	jmp $



times 510 - ($ - $$) db 0x00
db 0x55, 0xaa

