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




#ifndef INCLUDED_VGA_H
#define INCLUDED_VGA_H


#include <kernel/init.h>
#include <kernel/errno.h>
#include <kernel/types.h>
#include <kernel/module.h>


#define TEXT_VGA_X 80



extern struct file_operations vga;


struct vga_inode {
	struct inode_desc inode;

	/* frame buffer start address */
	/* frame buffer in text mode: 
	   char ASCII | char COLOR
	*/

	/* but use char is easier */

	__uint8_t *fb;

	__uint32_t x, y;
};

extern struct vga_inode stdout;


struct inode_desc *vga_open(char *, __uint32_t, __uint32_t, errno_t *);
errno_t vga_creat(char *, __uint32_t, __uint32_t);
errno_t vga_read(struct inode_desc *, char *, __uint64_t);
errno_t vga_fill(char *, __uint32_t, __uint32_t, struct vga_inode *);
errno_t vga_write(struct vga_inode *, char *, __uint64_t);
errno_t vga_lseek(struct inode_desc *, __uint32_t off, __uint32_t seg);
void vga_close(struct inode_desc *);

#endif

