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

// Macros for access to data in RIFF files to aid portability

#ifndef INC_RIFFDATA
#define INC_RIFFDATA


// rules for use:
// data from structures defined in winoil\riffform.h should alway be access via these macros
// If the same bit of data is to be used repeatedly, the result should be cached.

// bytes don't have their own macro

#define RIFFDATA_WORD(x)	(x)
#define RIFFDATA_DWORD(x)	(x)
#define RIFFDATA_FOURCC(x)	(x)


#endif  // INC_RIFFDATA
