/*
 * xara-cairo, a vector drawing program
 *
 * Based on Xara XL, Copyright (C) 1993-2006 Xara Group Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */


// file to map user names from USERNUMBER
// must remain in-step with makefile

#ifndef INC_LOGNAME
#define INC_LOGNAME

#ifndef USERNUMBER
#error USERNUMBER has not been set!
#endif

#undef USERNAME

#if USERNUMBER == 1
#define	USERNAME	"Andy"
#endif

#if USERNUMBER == 2
#define USERNAME	"Jim"
#endif

#if USERNUMBER == 3
#define	USERNAME	"Phil"
#endif

#if USERNUMBER == 4
#define	USERNAME	"Alex"
#endif

#if USERNUMBER == 5
#define	USERNAME	"MarkN"
#endif

#if USERNUMBER == 6
#define	USERNAME	"Rik"
#endif

#if USERNUMBER == 7
#define	USERNAME	"Tim"
#endif

#if USERNUMBER == 8
#define	USERNAME	"Simon"
#endif

#if USERNUMBER == 9
#define	USERNAME	"JustinF"
#endif

#if USERNUMBER == 10
#define	USERNAME	"Jason"
#endif

#if USERNUMBER == 11
#define	USERNAME	"Will"
#endif

#if USERNUMBER == 12
#define USERNAME	"Nobody1"
#endif

#if USERNUMBER == 13
#define USERNAME	"Nobody2"
#endif

#if USERNUMBER == 14
#define USERNAME	"Nobody3"
#endif

#ifndef USERNAME
#error USERNUMBER not recognised
#endif

#endif
