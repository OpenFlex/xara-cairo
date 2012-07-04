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

// Gavin's blend code

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// GBlend.h
//
/////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************************************

void Define(
		PPOINT	Src0Points,			First source path
		PBYTE	Src0Types,
		UINT32	Src0Length,
		PPOINT	Src1Points,			Second source path
		PBYTE	Src1Types,
		UINT32	Src1Length,
		BOOL	Flag,				Set for 1 to 1 blending
		UINT32	pFlatness,			Flatness
		PUINT32	Buffer,				Workspace
		UINT32	BufferLength		Workspace length
	) ;

This call should be made once in order to set up a blend. It will blend one subpath to one other
subpath. Each subpath is treated as though it is unclosed.

Paths are expected to be in the form of a single subpath. ClosePath options are ignored.
Workspace required is 4 bytes per path element per path.

Note that currently (04/11/94) there is a lack of error handling. Paths should be in the correct
format.

/////////////////////////////////////////////////////////////////////////////////////////////////

UINT32 Blend(
		double	pRatio,				Blend ratio of 1st path to 2nd path
		PPOINT	DstPoints,			Destination path
		PBYTE	DstTypes,
		UINT32	DstLength			Maximum length of destination path.
	) ;

This call actually performs a blend. It should be called once for each required value of pRatio.

************************************************************************************************/

class GBlend
{
public:
	void Define(
		PPOINT	Src0Points,
		PBYTE	Src0Types,
		UINT32	Src0Length,
		PPOINT	Src1Points,
		PBYTE	Src1Types,
		UINT32	Src1Length,
		BOOL	Flag,
		UINT32	pFlatness,
		PUINT32	Buffer,
		UINT32	BufferLength
	) ;
	UINT32 Blend(
		double	pRatio,
		PPOINT	DstPoints,
		PBYTE	DstTypes,
		INT32	DstLength
	) ;
private:
	BOOL	Is1to1 ;
	UINT32	Flatness ;
	INT32	Ratio ;
	PPOINT	S0Points ; PBYTE S0Types ; UINT32 S0Length ; PUINT32 LengthPtr0 ; PUINT32 EndLengthPtr0 ;
	PPOINT	S1Points ; PBYTE S1Types ; UINT32 S1Length ; PUINT32 LengthPtr1 ; PUINT32 EndLengthPtr1 ;
	PPOINT	 OPoints ; PBYTE  OTypes ; size_t OLength ;
	PPOINT	IPoints0 ; PBYTE ITypes0 ; UINT32 ILength0 ;
	PPOINT	IPoints1 ; PBYTE ITypes1 ; UINT32 ILength1 ;
	PUINT32	LPtr0 ; BYTE Type0 ; UINT32 Length0 ; INT32 Match0 ; UINT32 Total0 ;
	PUINT32	LPtr1 ; BYTE Type1 ; UINT32 Length1 ; INT32 Match1 ; UINT32 Total1 ;
	POINT P00,P01,P02,P03 ;
	POINT P10,P11,P12,P13 ;
	POINT L1,L2,M,R1,R2 ;

 	BOOL CalcPathLengths(
		PPOINT	Points,
		PBYTE	Types,
		UINT32	Length,
		PUINT32	Buffer,
		UINT32	BufferLength,
		PUINT32 &BufferEnd
	) ;
	BOOL BlendNtoN() ;
	BOOL BlendMtoN() ;
	BOOL Blend1to1() ;
	BOOL BlendPoint( BYTE Type, POINT P0, POINT P1 ) ;
	BOOL BlendCurve( POINT P01,POINT P02,POINT P03, POINT P11,POINT P12,POINT P13 ) ;
	void Match    ( PUINT32 Ptr, PUINT32 EndPtr, UINT32 Length, INT32 &Match, UINT32 &Total ) ;
	void MatchLast( PUINT32 Ptr, PUINT32 EndPtr, UINT32 Length, INT32 &Match, UINT32 &Total ) ;
	void ReadPath0() ; void ReadPathStart0() ;
	void ReadPath1() ; void ReadPathStart1() ;
	void Split( POINT P0,POINT P1,POINT P2,POINT P3, INT32 N,UINT32 D ) ;
	INT32 BezierLength( POINT P0, POINT P1, POINT P2, POINT P3 )	;
	INT32 FlattenSplit( POINT P0, POINT P1, POINT P2, POINT P3 ) ;
} ;

/////////////////////////////////////////////////////////////////////////////////////////////////
