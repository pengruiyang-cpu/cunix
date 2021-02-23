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




org 0x7c00

_start:
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

%include "arch/x86/readdisk.inc"

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
	mov cl, 0x02
	mov bx, 0x8000

	mov di, diskpanic_message

.read_loop:
	call read_sector
	jc panic

; read 9 sectors (1 loader, 8 kernel)
	add cl, 0x01
	add bx, 0x0200

	cmp cl, 0x0a
	je .ret

	jmp .read_loop

.ret:
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

