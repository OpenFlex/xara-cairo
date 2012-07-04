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

// Function Prototypes and types for the handle manager to opperate.


#ifndef INC_HANDLES
#define INC_HANDLES

//#ifdef DEBUG                      
	// For now, only use unique ids when debuging
	//#define USE_UNIQUE_IDS
//#endif


// A few new types just for handles and their friends
#ifdef USE_UNIQUE_IDS
	typedef DWORD   	MHANDLE;
#else
	typedef UINT32    	MHANDLE;
#endif

// Useful defines used in the Handles module
const MHANDLE			BAD_MHANDLE	 = MHANDLE(NULL);

// Initialisation
BOOL    InitHandles();
void    DeinitHandles();

// Claim and release functions
MHANDLE ClaimHandle( ADDR Address );
BOOL    ReleaseHandle( MHANDLE Handle );
BOOL    ReleaseRangeOfHandles( ADDR LowAddr, ADDR HighAddr );

// info on a handle
ADDR    DescribeHandle( MHANDLE Handle );

// Changing handles
BOOL    RelocateHandles( ADDR LowAddr, ADDR HighAddr, INT32 shift );
ADDR    AlterHandle( MHANDLE Handle, ADDR Address );

#endif
