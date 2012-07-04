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

// Structures for access to RIFF data formats

// this is in the winoil to allow me to use the pragma pack thingy - compiler dependant

#ifndef INC_RIFFFORM
#define INC_RIFFFORM

#include "riffdata.h"

#pragma pack(push, 1)	// set the compiler to pack to byte alignment - most handy!
						// this must be matched by a pop at the end of the file to avoid
						// things going deeply wrong.


// IMPORTANT: all data in this file should be accessed through the macros in
// intel\riffdata.h, except for bytes.

// A FOURCC is a MS type which is used to contain identifiers for RIFF chunks. It's an
// interger equivalent to string of maximum size four bytes, padded at the right
// with spaces.
typedef DWORD FOURCC;

typedef struct {
	FOURCC	ckID;
	DWORD	ckSize;
} RIFFck;

typedef struct {
	RIFFck	CK;
	FOURCC	FormType;	
} RIFFFile_Header;

// a header goes before this, but will have already been read
typedef struct {
	FOURCC	ListType;
} RIFFFile_List;


#define RIFFTYPE_RIFF	0x46464952
#define RIFFTYPE_LIST	0x5453494C

// This must be the last thing in the file to avoid things going nasty on us
#pragma pack(pop)

#endif  // INC_RIFFFORM


