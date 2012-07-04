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


// low-level functions for fixed-point arithmetic
// should only be called by fixed16.cpp/fixed32.cpp - everyone else should use ccmaths.h

#ifndef INC_FIX24ASM
#define	INC_FIX24ASM

// requires that fixed24 already be defined

#define	retfixed24 fixed24

retfixed24 Fixed24Mul( fixed24, fixed24 );
retfixed24 Fixed24Div( fixed24, fixed24 );

double Fixed24ToDouble( fixed24 );
retfixed24 DoubleToFixed24( double );


#ifdef FULL_FIXED24
retfixed24 Div32by32(INT32,INT32);

retfixed24	Fixed24Sin( fixed24 );
retfixed24	Fixed24Cos( fixed24 );

INT32 MatrixCalc( fixed24, INT32, fixed24, INT32);
INT32 LongMulFixed24( INT32, fixed24 );
INT32 LongDivFixed24( INT32 arg, fixed24 );
INT32 MPtoPixel( INT32 arg, fixed24 );
INT32 MPtoOS256( INT32 arg, fixed24 );
#endif

#endif
