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
	mov cl, 0x02
	mov bx, 0x8000

.read_loop:
	call read_sector_chs

	mov di, diskpanic_message

	jc .try_lba

; read 8 sectors
	add cl, 0x02
	add bx, 0x0200

	cmp cl, 0x0a
	je .ret

	jmp .read_loop

.ret:
	ret
	

.try_lba:
	call read_sector_lba

	jc panic

	add cl, 0x02
	add bx, 0x0200
	
	cmp cl, 0x0a
	je .ret
	
	jmp .read_loop
	
	

read_sector_chs:
	mov ax, 0x0201
	xor ch, ch
	; CL is argument `start sector`
	xor dh, dh

	mov dl ,[BI_BOOTDEV]

	int 0x13
	ret
	

read_sector_lba:
	push dword 0x00000000
	; ECX is argument `LBA address`
	push dword ecx
	push word es
	push word bx
	; 1 sector
	push word 0x0001
	push word 0x0010

	mov ah, 0x42
	mov dl, [BI_BOOTDEV]
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

