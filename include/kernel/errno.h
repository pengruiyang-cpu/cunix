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




typedef __uint32_t errno_t;


/* error in kernel */
#define E_KERROR 0x20000000

/* error io port */
#define E_IOERROR 0x00000001

/* no enough memory for this call */
#define E_NOMEM	  0x00000002

/* call interrupted by signal */
#define E_SIGNAL  0x00000003


/* no permision */
#define E_DENIED 0x40000000

/* need root to call this */
#define E_NDROOT 0x00000001

/* no io passport */
#define E_IODND  0x00000002

/* need hardware super 0 */
#define E_HARDSP 0x00000003

/* user error (caller) */
#define E_UERROR 0x80000000

/* syntax error for this call (invalid argument) */
#define E_SYNERR 0x00000001

/* error because address is invalid */
#define E_ADDRE  0x00000002

/* call out of range */
#define E_OUTRAG 0x000000003

