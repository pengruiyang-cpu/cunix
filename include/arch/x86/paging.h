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



#ifndef INCLUDED_PAGING_H
#define INCLUDED_PAING_H


#define PAGE_PRESENT  0x0001

#define PAGE_RDWR     0x0002

#define PAGE_USER     0x0004

#define PAGE_NWRBACK  0x0008

#define PAGE_NOCACHE  0x0010

#define PAGE_ACCESSED 0x0020

#define PAGE_DIRTY    0x0040

#define PAGE_PAT      0x0080

#define PAGE_GLOBAL   0x0100


/* 0x83 */
#define PATT_KERNEL (PAGE_PRESENT | PAGE_RDWR | PAGE_PAT)

/* 0x07 */
#define PATT_USER   (PAGE_PRESENT | PAGE_RDWR | PAGE_USER)


#define PML4_ADDR 0x70000
#define PDPT_ADDR 0x71000
#define PTE_ADDR  0x72000

#define PAGE_SIZE 0x200000

#endif
