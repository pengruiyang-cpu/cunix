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




#ifndef INCLUDED_MODULE_H
#define INCLUDED_MODULE_H

#include <kernel/init.h>
#include <kernel/types.h>
#include <kernel/errno.h>


#define INIT_MODULE(modn) { \
	.open = modn##_open, \
	.creat = modn##_creat, \
	.fill = modn##_fill, \
	.read = modn##_read, \
	.write = modn##_write, \
	.lseek = modn##_lseek, \
	.close = modn##_close \
};


#endif
