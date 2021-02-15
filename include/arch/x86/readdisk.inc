; Copyright (C) 2021 Rain

; This file is part of Cunix. 

; Cunix is free software: you can redistribute it and/or modify 
; it under the terms of the GNU General Public Licene and published by 
; the Free Software Foundation, either version 3 of the License, or 
; (at your option) any later version. 

; Cunix is distributed in the hope that it will be useful, 
; but WITHOUT ANY WARRANTY; without even the implied warranty of 
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
; GNU General Public License for more details. 

; You should have recceived a copy of the GNU General Public License 
; along with Cunix. If not, see <https://www.gnu.org/licenses/>. 




BI_BOOTDEV equ 0x7e00

read_sector:
	; CH is sector number
	call read_sector_chs
	jc .try_lba

	ret

.try_lba:
	call read_sector_lba
	ret

read_sector_chs:
	mov ax, 0x0201
	xor ch, ch

	xor dh, dh

	mov dl, [BI_BOOTDEV]
	
	int 0x13
	ret

read_sector_lba:
	push dword 0x00000000
	push dword ecx
	push word es
	push word bx

	push word 0x0001
	push word 0x0010
	
	mov ah, 0x42
	mov dl, [BI_BOOTDEV]

	int 0x13
	add sp, 0x10

	ret


