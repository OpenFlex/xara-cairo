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

// Header for the envelope mould shapes implementation

#ifndef INC_GENVELOPE
#define INC_GENVELOPE

#include "moldshap.h"

/********************************************************************************************

>	class GEnvelope

	Author:		Gavin_Theobald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/2/94
	Purpose:	The low level enveloper class.

********************************************************************************************/

/*

void Define( POINT *P, RECT *pBBox, DWORD pTolerance = 0 ) ;

	Define the envelope with twelve control points P. The source path has bounding box pBBox.
	pTolerance defines the accuracy with which curves are moulded. If pTolerance is zero then
	curves are never split.

void Redefine( POINT *P ) ;

	Redefines the mould after dragging the control points P.


void FitPoint(  POINT a, POINT& b ) ;

	This will mould the point a returning the result in b. Note that a may be outside the
	original bounding box.

void FitPoint( DPOINT a, POINT& b ) ;

	This will mould the point a specified as two values in the range 0 to 1. The result is
	returned in b. This call can be used for drawing grid points.

BOOL FitPath (
	CONST POINT *IPoints,
	CONST BYTE  *ITypes,
	DWORD ILength,
	LPPOINT OPoints,
	LPBYTE  OTypes,
	INT32 OLength,
	BOOL Close = FALSE
) ;

	This will mould a source path IPoints,ITypes,ILength returning the result in the destination
	path OPoints,OTypes,OLength. Curves may be split into several curves for greater accuracy if
	pTolerance was non-zero. If Close is non-zero then open paths are closed.


*/

class GEnvelope : public GMould
{
	CC_DECLARE_DYNAMIC(GEnvelope)

	public:
		GEnvelope();

		virtual BOOL Redefine( POINT *P ) ;
		virtual BOOL FitPath (
			CONST POINT *IPoints,
			CONST BYTE  *ITypes,
			DWORD ILength,
			LPPOINT OPoints,
			LPBYTE  OTypes,
			DWORD OLength,
			BOOL Close = FALSE
		) ;
		virtual void CopyShape( POINT *P ) ;

	private:
		virtual void ScaleView();
		virtual void CalcViewBBox();
		virtual void CalcViewConsts();
		virtual void Transform( DPOINT a, DPOINT& b ) ;
		
	private:
		POINT L0, L1, L2 ;
		POINT T0, T1, T2 ;
		POINT R0, R1, R2 ;
		POINT B0, B1, B2 ;
		DPOINT VL0, VL1, VL2 ;
		DPOINT VT0, VT1, VT2 ;
		DPOINT VR0, VR1, VR2 ;
		DPOINT VB0, VB1, VB2 ;
		DPOINT A, B, C, D, E, F, G, H, J, K, L, M ;
} ;


/********************************************************************************************

>	class GEnvelope2x2

	Author:		Gavin_Theobald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/2/94
	Purpose:	The low level enveloper class.

********************************************************************************************/

/*

void Define( POINT *P, RECT *pBBox, DWORD pTolerance = 0 ) ;

	Define the envelope with twenty-four control points P. The source path has bounding box pBBox.
	pTolerance defines the accuracy with which curves are moulded. If pTolerance is zero then
	curves are never split.

void Redefine( POINT *P ) ;

	Redefines the mould after dragging the control points P.


void FitPoint(  POINT a, POINT& b ) ;

	This will mould the point a returning the result in b. Note that a may be outside the
	original bounding box.

void FitPoint( DPOINT a, POINT& b ) ;

	This will mould the point a specified as two values in the range 0 to 1. The result is
	returned in b. This call can be used for drawing grid points.

BOOL FitPath (
	CONST POINT *IPoints,
	CONST BYTE  *ITypes,
	DWORD ILength,
	LPPOINT OPoints,
	LPBYTE  OTypes,
	INT32 OLength,
	BOOL Close = FALSE
) ;

	This will mould a source path IPoints,ITypes,ILength returning the result in the destination
	path OPoints,OTypes,OLength. Curves may be split into several curves for greater accuracy if
	pTolerance was non-zero. If Close is non-zero then open paths are closed.

*/
/////////////////////////////////////////////////////////////////////////////////////////////////

class GEnvelope2x2 : public GMould
{
	CC_DECLARE_DYNAMIC(GEnvelope2x2)

	public:
		GEnvelope2x2();

		virtual BOOL Redefine( POINT *P ) ;
		virtual BOOL FitPath (
			CONST POINT *IPoints,
			CONST BYTE  *ITypes,
			DWORD ILength,
			LPPOINT OPoints,
			LPBYTE  OTypes,
			DWORD OLength,
			BOOL Close = FALSE
		) ;
		virtual void CopyShape( POINT *P ) ;
	
	private:
		virtual void ScaleView() ;
		virtual void CalcViewBBox() ;
		virtual void CalcViewConsts() ;
		virtual void Transform( DPOINT a, DPOINT& b ) ;

		BOOL CalcConsts() ;
		BOOL GenLine( DPOINT P0, DPOINT P6, DPOINT T0, DPOINT T6 ) ;

	private:
		POINT L0, L1, L2, L3, L4, L5 ;
		POINT T0, T1, T2, T3, T4, T5 ;
		POINT R0, R1, R2, R3, R4, R5 ;
		POINT B0, B1, B2, B3, B4, B5 ;
		POINT H1, H2, H4, H5 ;
		POINT V1, V2, V4, V5 ;
		POINT MM ;
		DPOINT VL0, VL1, VL2, VL3, VL4, VL5 ;
		DPOINT VT0, VT1, VT2, VT3, VT4, VT5 ;
		DPOINT VR0, VR1, VR2, VR3, VR4, VR5 ;
		DPOINT VB0, VB1, VB2, VB3, VB4, VB5 ;
		DPOINT VH1, VH2, VH4, VH5 ;
		DPOINT VV1, VV2, VV4, VV5 ;
		DPOINT VMM ;
		BOOL SmoothX, SmoothY ;
		DPOINT A00, B00, C00, D00, E00, F00, G00, H00, J00, K00, L00, M00 ;
		DPOINT A01, B01, C01, D01, E01, F01, G01, H01, J01, K01, L01, M01 ;
		DPOINT A10, B10, C10, D10, E10, F10, G10, H10, J10, K10, L10, M10 ;
		DPOINT A11, B11, C11, D11, E11, F11, G11, H11, J11, K11, L11, M11 ;
} ;

#endif
