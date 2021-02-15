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




; 32 bit segment descriptor: 
; BASE | G  | 32/16 | 64 | LIMIT | PRESENT | PERMISSION | SYSSEG | TYPE | BASE | LIMIT
; 63   | 55 | 54    | 53 | 51	 | 47	   | 46		| 44     | 43	| 39   | 15


; type-bit 0: accessed
; type-bit 1: readable / writable
; type-bit 2: conforming / expansion-direction
; type-bit 3: 1 / 0

; permision: DPL 0-2

; G: 
; if G = 1: 
; 	limit = limit * 4KB

; else:
;	limit = limit  * 1B


