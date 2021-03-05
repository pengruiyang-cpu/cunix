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




#include <kernel/types.h>
#include <kernel/errno.h>



#define MAKE_MODULE(name) struct file_operations name##_fop = { \
	.open = name##_open; \
	.creat = name##_create; \
	.read = name##_read; \
	.write = name##_write; \
	.lseek = name##_lseek; \
	.close = name##_close; \
};


struct inode_desc {
	/* this struct is a general descriptor, so we must know
	 * how big is it. */

	__uint32_t size;

	/* file descriptor */
	__uint32_t fd;

	/* this is optional */
	__uint32_t off;

	/* this is optional too */
	char *name;
};


struct file_oprerations {
	/* open a file */
	struct inode_desc * (* open) (char *name, __uint32_t type, __uint32_t mode, __uint32_t *errno);
	struct inode_desc * (* open) (__uint32_t type, __uint32_t mode, __uint32_t *errno);

	/* or create one */

	/* `creat` doesn't return file-descriptor, it returns errno */
	errno_t (* creat) (char *name, __uint32_t type, __uint32_t mode);
	errno_t (* creat) (__uint32_t type, __uint32_t mode);

	/* read from file-descriptor */
	errno_t (* read) (struct inode_desc *i, char *buffer, __uint64_t l);
	
	/* write to file-descriptor */
	errno_t (* write) (struct inode_desc *i, char *buffer, __uint64_t l);

	/* change position */

	/* 'seg' = whence */
	__uint32_t (* lseek) (struct inode_desc *i, __uint32_t off, __uint32_t seg);

	/* close a file-descriptor */
	void (* close) (struct inode_desc *i);
};


