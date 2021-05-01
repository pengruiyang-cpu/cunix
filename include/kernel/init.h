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




#ifndef INCLUDED_INIT_H
#define INCLUDED_INIT_H


#include <kernel/types.h>
#include <kernel/errno.h>



#define KERNEL_CS 0x0008
#define KERNEL_DS 0x0010


struct inode_desc {
	/* this struct is a general descriptor, so we must know
	 * how big is it. */

	__uint32_t size;

	/* file descriptor */
	__uint32_t fd;

	/* this is optional (offset) */
	__uint32_t off;

	/* this is optional too */
	char *name;

	/* real inode saves here */
	void *real_inode;
};


struct file_operations {
	/* open a file */
	struct inode_desc * (* open) (char *, __uint32_t, __uint32_t, errno_t *);

	/* or create one */

	/* `creat` doesn't return file-descriptor, it returns errno */
	errno_t (* creat) (char *, __uint32_t, __uint32_t);

	/* `fill` fills a inode descriptor */
	errno_t (* fill) (char *, __uint32_t, __uint32_t, struct inode_desc *);


	/* read from file-descriptor */
	errno_t (* read) (struct inode_desc *, char *, __uint64_t);
	
	/* write to file-descriptor */
	errno_t (* write) (struct inode_desc *, char *, __uint64_t);

	/* change position */

	/* 'seg' = whence */

#define SEEK_SET 0x0001
#define SEEK_CUR 0x0002
#define SEEK_END 0x0003

	__uint32_t (* lseek) (struct inode_desc *, __uint32_t, __uint32_t);

	/* close a file-descriptor */
	void (* close) (struct inode_desc *);
};


#endif

