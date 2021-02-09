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




; this page is already in memory (it's not swapped)
PATT_PRESENT 	equ 0x00000001

; read + write
PATT_RDWR	equ 0x00000002

; user mode or kernel mode
PATT_USER	equ 0x00000004

; write cache + memory or cache only
PATT_CACHEMEM	equ 0x00000008

; this page cannot cache
PATT_NCACHE	equ 0x00000010

; this page has been accessed
PATT_ACCESSED	equ 0x00000020

; this page is dirty
PATT_DIRTY 	equ 0x00000040

; this page is in PAT
PATT_PAT	equ 0x00000080

; this is a global page
PATT_GLOBAL	equ 0x00000100


; 0x83
PAGE_KERNEL equ PATT_PRESENT | PATT_RDWR | PATT_PAT

; 0x07
PAGE_USER equ PATT_RDWR | PATT_USER | PATT_PRESENT


