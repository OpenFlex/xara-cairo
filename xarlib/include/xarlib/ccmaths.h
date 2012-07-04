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
 */ 

// New maths types.

#ifndef INC_CCMATHS
#define INC_CCMATHS

#include "xarlib/xlong.h"
#include "xarlib/fixed16.h"
#include "xarlib/fixed.h"
//#include "fixed32.h"
//#include "ratio.h"

// The following types are same as those defined in classes above.

typedef xlong 	XLONG;		// 64-bit signed value
typedef fixed16 FIXED16;	// 32-bit signed value with binary point between bits 15 and 16.
/*typedef fixed32 FIXED32;	// 64-bit signed value with binary point between bits 31 and 32.
typedef ratio	RATIO;		// 32-bit signed value with binary point between bits 30 and 31. 
*/
typedef fixed16 ANGLE;		// used to represent angles 
typedef XLONG XMILLIPOINT;	// 64-bit coordinate units

// Function Prototypes

BOOL InitMaths();

XLONG Mul(const INT32, const INT32);

XLONG Asl(const INT32, UINT32);

XLONG Asr(const INT32, UINT32);

INT32 MulDiv32By32(const INT32, const INT32, const INT32);
inline fixed16 Div32By32(const INT32 a, const INT32 b)
{
	fixed16 v( InternalDiv32by32( a, b ) );
	return v;
}
  								
XLONG CCAPI MakeXLong(const INT32);

XLONG CCAPI MakeXLong(const double);

// this value of PI taken from Standard C Library by Plauger
#define	PI	3.14159265358979323846

#endif

