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




CYLINDERS_NEED equ 10

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

	call read_it

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


read_it:
	; segment address of loader+kernel
	mov ax, 0x0800
	mov es, ax

	; cylinder 0
	mov ch, 0
	; header 0
	mov dh, 0
	; start sector 2
	mov cl, 2

.read_loop:
	; I know it use to save source-address, but there isn't another 
	; register free. 

	; error counts
	mov si, 0

.retry:
	mov ah, 0x02
	; one sector
	mov al, 1

	; offset 0x0000
	mov bx, 0

	; boot device
	mov dl, [BI_BOOTDEV]

	; call -> BIOS
	int 0x13

	; if error
	jnc .cont_read
	
.error:
	add si, 1
	; we try it for 5 times
	mov di, diskpanic_message

	cmp si, 5
	jae panic

.reset_disk:
	mov ah, 0x00
	mov dl, [BI_BOOTDEV]

	int 0x13

	; and retry

	jmp .retry

.cont_read:
	; add for 0x0020 (not 0x0200)
	mov ax, es
	add ax, 0x0020
	mov es, ax

	; we've been read one sector
	add cl, 1

	; if read done
SECTORS_1_TRACK equ 18
	cmp cl, SECTORS_1_TRACK
	jbe .read_loop

.update_track:
	mov cl, 1
	add dh, 1
HEADS_1_CYLINDER equ 2
	cmp dh, HEADS_1_CYLINDER
	
	jb .read_loop

.update_head
	mov dh, 0
	add ch, 1
	cmp ch, CYLINDERS_NEED
	jb .read_loop

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

