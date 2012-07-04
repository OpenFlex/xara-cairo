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

#ifndef INC_FIXEDASM
#define	INC_FIXEDASM

// requires that fixed16 already be defined

#define	retfixed16 fixed16

retfixed16 Fixed16Mul( fixed16, fixed16 );
retfixed16 Fixed16Div( fixed16, fixed16 );

retfixed16 InternalDiv32by32(INT32,INT32);

double Fixed16ToDouble( fixed16 );
retfixed16 DoubleToFixed16( double );

retfixed16	Fixed16Sin( fixed16 );
retfixed16	Fixed16Cos( fixed16 );

INT32 MatrixCalc( fixed16, INT32, fixed16, INT32);
INT32 LongMulFixed16( INT32, fixed16 );
INT32 LongDivFixed16( INT32 arg, fixed16 );
INT32 MPtoPixel( INT32 arg, fixed16 );
INT32 MPtoOS256( INT32 arg, fixed16 );	

#endif
