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


/*
	The progress indicator (OIL interface).


*/


#ifndef	OILPROG__INC
#define	OILPROG__INC


class Cursor;					// forward reference, defined in winoil\cursor.h


// These functions support the private implementation of the kernel's progress indicator system.
// Have a look at progress.h and progress.cpp if you are intending to bring up a 
// progress display during a busy/slow operation.


BOOL InitProgressCursor();
Cursor* UpdateProgressCursor(INT32 percent);
void DeInitProgressCursor();

BOOL BreakKeyHit();
void Beep();


#endif	// OILPROG__INC

