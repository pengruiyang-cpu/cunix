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




#include <kernel/init.h>
#include <kernel/types.h>
#include <kernel/errno.h>
#include <kernel/module.h>

#include <lib/rlib.h>
#include <arch/io.h>

#include <kernel/vgatext.h>




__uint32_t next_fd = 1;
struct vga_inode stdout;


struct inode_desc *vga_open(char *name, __uint32_t type, __uint32_t mode, errno_t *errno) {
	*errno = -E_NOSUPP;
}


errno_t vga_creat(char *name, __uint32_t type, __uint32_t mode) {
	return -E_NOSUPP;
}


errno_t vga_read(struct inode_desc *inode, char *buffer, __uint64_t l) {
	return -E_HNOSUP;
}


void update_cursor(__uint32_t x, __uint32_t y) {
	__uint16_t pos = y * TEXT_VGA_X + x;

	outb(0x0f, 0x03d4);
	outb((__uint8_t) (pos & 0xff), 0x03d5);
	outb(0x0e, 0x03d4);
	outb((__uint8_t) ((pos >> 8) & 0xff), 0x03d5);

	return;
}

__uint16_t read_cursor(void) {
	__uint16_t pos = 0;

	outb(0x0f, 0x03d4);
	pos |= inb(0x03d5);

	outb(0x0e, 0x03d4);
	pos |= ((__uint16_t) inb(0x03d5)) << 8;

	return pos;
}


errno_t vga_fill(char *name, __uint32_t type, __uint32_t mode, struct vga_inode *inode) {
	inode->inode.size = sizeof(struct vga_inode);
	inode->inode.fd = next_fd;

	inode->inode.off = 1 * TEXT_VGA_X + 0;

	inode->fb = (__uint8_t *) 0xb8000;
	inode->x = 0;

	/* first line is in use */
	inode->y = 1;

	next_fd++;

	update_cursor(0, 0);
	
	return 0;
}


errno_t vga_write(struct vga_inode *inode, char *buffer, __uint64_t l) {
	/* for safety, we re-calc offset */
	inode->inode.off = (inode->y * TEXT_VGA_X + inode->x) * 2;
	
	if (*buffer == '\n') {
		/* we use LF to line feed, not CRLF in Windows */
		inode->x = 0;
		inode->y++;
		update_cursor(inode->x, inode->y);

		return 0;
	}

	if (*buffer == '\r') {
		inode->x = 0;
		update_cursor(inode->x, inode->y);
	}


	/* put it */

	inode->fb[inode->inode.off] = *buffer;
	/* color white */
	inode->fb[inode->inode.off + 1] = 0x0f;

	inode->inode.off += 2;

	inode->x++;
	if (inode->x == TEXT_VGA_X) {
		inode->x = 0;
		inode->y++;
	}

	update_cursor(inode->x, inode->y);

	return 0;
}


extern errno_t vga_lseek(struct inode_desc *inode, __uint32_t off, __uint32_t seg);

__asm__ ("vga_lseek: ret\n");


void vga_close(struct inode_desc *inode) {
	/* disable cursor */
	outb(0x3d4,  0x0a);
	outb(0x3d5, 0x20);

	return;
}


struct file_operations vga = INIT_MODULE(vga);

