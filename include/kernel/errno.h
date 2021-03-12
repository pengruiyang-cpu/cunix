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




#ifndef INCLUDED_ERRNO_H
#define INCLUDED_ERRNO_H

typedef __uint32_t errno_t;


/* error in kernel */
#define E_KERROR 0x20000000

/* error io port */
#define E_IOERROR 0x00000001 | E_KERROR

/* no enough memory for this call */
#define E_NOMEM	  0x00000002 | E_KERROR

/* call interrupted by signal */
#define E_SIGNAL  0x00000003 | E_KERROR

/* kernel not supported */
#define E_NOSUPP  0x00000004 | E_KERROR


/* no permision */
#define E_DENIED 0x40000000

/* need root to call this */
#define E_NDROOT 0x00000001 | E_DENIED

/* no io passport */
#define E_IODND  0x00000002 | E_DENIED

/* need hardware super 0 */
#define E_HARDSP 0x00000003 | E_DENIED

/* hardware no support */
#define E_HNOSUP 0x00000004 | E_DENIED

/* user error (caller) */
#define E_UERROR 0x80000000 | E_UERROR


/* syntax error for this call (invalid argument) */
#define E_SYNERR 0x00000001 | E_UERROR

/* error because address is invalid */
#define E_ADDRE  0x00000002 | E_UERROR

/* call out of range */
#define E_OUTRAG 0x00000003 | E_UERROR

#endif

