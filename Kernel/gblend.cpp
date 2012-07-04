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

/*
*/

#include "camtypes.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// GBlend.cpp
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "gblend.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

CONST BYTE PT_END = 0 ;

inline BOOL IsntEnd( BYTE Type )
{
	return Type!=PT_END ;
}

inline BOOL IsntMove( BYTE Type )
{
	return (Type & PT_MOVETO)!=PT_MOVETO ;
}

inline BOOL IsLine( BYTE Type )
{
	return (Type & PT_MOVETO)==PT_LINETO ;
}

inline BOOL IsCurve( BYTE Type )
{
	return (Type & PT_MOVETO)==PT_BEZIERTO ;
}

inline BOOL IsntCurve( BYTE Type )
{
	return (Type & PT_MOVETO)!=PT_BEZIERTO ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

inline UINT32 ScaledDiv( UINT32 N, UINT32 D )
{
	if (D == 0)
		return 1;
#if defined(__WXMSW__)
	UINT32 temp ;
	__asm {
		mov		eax,N
		xor		edx,edx
		shld	edx,eax,28
		shl		eax,28
		div		D
		mov		temp,eax
	}
	return temp ;
#else
	return UINT32((UINT64(N)<<28)/D);
#endif
}

inline INT32 ScaledMul( INT32 X, INT32 N )
{
//	return X*N/0x10000000 ;
#if defined(__WXMSW__)
	UINT32 temp ;
	__asm {
		mov		eax,X
		imul	N
		shrd	eax,edx,28
		mov		temp,eax
	}
	return temp ;
#else
	return INT32(INT64(X)*N>>28);
#endif
}

inline UINT32 length( POINT P0, POINT P1 )
{
#if defined(__WXMSW__)
	union {
		struct {
			DWORD lo ;
			DWORD hi ;
		} itemp ;
		double ftemp ;
	} val ;
	__asm {
		mov		eax,P1.x
		sub		eax,P0.x
		imul	eax
		mov		ebx,eax
		mov		ecx,edx
		mov		eax,P1.y
		sub		eax,P0.y
		imul	eax
		add		eax,ebx
		adc		edx,ecx
		mov		val.itemp.lo,eax
		mov		val.itemp.hi,edx
		fild	val.ftemp
		fsqrt
		fistp	val.itemp.lo
	}
	return val.itemp.lo ;
#else
	return (UINT32)sqrt( double(P1.x-P0.x)*(P1.x-P0.x)+double(P1.y-P0.y)*(P1.y-P0.y) ) ;
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

void GBlend::Define(
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
	)
{
	S0Points	= Src0Points ;
	S0Types		= Src0Types ;
	S0Length	= Src0Length ;
	S1Points	= Src1Points ;
	S1Types		= Src1Types ;
	S1Length	= Src1Length ;
	Is1to1		= Flag ;
	Flatness	= pFlatness*27/2 ;
	CalcPathLengths(
		S0Points, S0Types, S0Length,
		LengthPtr0 = Buffer,
		BufferLength,
		EndLengthPtr0
	) ;
	CalcPathLengths(
		S1Points, S1Types, S1Length,
		LengthPtr1 = EndLengthPtr0,
		BufferLength-(EndLengthPtr0-LengthPtr0),
		EndLengthPtr1
	) ;
	Is1to1 = Is1to1 && (EndLengthPtr0-LengthPtr0)==(EndLengthPtr1-LengthPtr1) ;
}

UINT32 GBlend::Blend( double pRatio, PPOINT DPoints, PBYTE DTypes, INT32 DLength )
{
	Ratio		= (INT32) (pRatio*0x10000000) ;
	OPoints		= DPoints ;
	OTypes		= DTypes ;
	OLength		= DLength ;
	IPoints0	= S0Points ;
	ITypes0		= S0Types ;
	ILength0	= S0Length ;
	IPoints1	= S1Points ;
	ITypes1		= S1Types ;
	ILength1	= S1Length ;
	LPtr0		= LengthPtr0 ;
	LPtr1		= LengthPtr1 ;
	P00 = *IPoints0++ ; Type0 = *ITypes0++ ; ILength0-- ;
	P10 = *IPoints1++ ; Type1 = *ITypes1++ ; ILength1-- ;
	if ( !BlendPoint( PT_MOVETO, P00, P10 ) )
		return FALSE ;
	Length0 = 0 ; ReadPathStart0() ;
	Length1 = 0 ; ReadPathStart1() ;
	if ( Is1to1 )
	{
		if ( !BlendNtoN() )
			return 0 ;
	}
	else
	{
		if ( !BlendMtoN() )
			return 0 ;
	}
	return OTypes-DTypes ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GBlend::CalcPathLengths(
		PPOINT	Points,
		PBYTE	Types,
		UINT32	Length,
		PUINT32	Buffer,
		UINT32	BufferLength,
		PUINT32 &BufferEnd
	)
{
	UINT32 TotalLength = 0 ;
	BufferEnd = Buffer ;
    UINT32 i = 1 ;
    while ( i<Length )
    {
		if ( IsLine(Types[i]) )
		{
			*BufferEnd = length( Points[i-1],Points[i] ) ;
			i++ ;
		}
		else /* Curve */
		{
			*BufferEnd = BezierLength( Points[i-1],Points[i],Points[i+1],Points[i+2] ) ;
			i+=3 ;
    	}
		TotalLength += *BufferEnd++ ;
    }
	PUINT32 P = Buffer ;
	UINT32 Total = 0 ;
	while ( P<BufferEnd )
	{
		*P = ScaledDiv( *P, TotalLength ) ;
		Total += *P++ ;
	}
	if ( Total != 0x10000000 )
	{
		while ( *(--P)+0x10000000 <= Total )
		{ }
		*P -= Total-0x10000000 ;
	}
	return TRUE ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

BOOL GBlend::BlendNtoN()
{
	while ( IsntEnd(Type0) || IsntEnd(Type1) )
		if ( !Blend1to1() )
			return FALSE ;
	return TRUE ;
}

BOOL GBlend::BlendMtoN()
{
	UINT32 t ;
	while ( IsntEnd(Type0) || IsntEnd(Type1) )
	{
		if ( LPtr1==EndLengthPtr1-1 )
			MatchLast( LPtr0, EndLengthPtr0, *LPtr1+Length1-Length0, Match0, Total0 ) ;
		else
			Match    ( LPtr0, EndLengthPtr0, *LPtr1+Length1-Length0, Match0, Total0 ) ;
		if ( LPtr0==EndLengthPtr0-1 )
			MatchLast( LPtr1, EndLengthPtr1, *LPtr0+Length0-Length1, Match1, Total1 ) ;
		else
			Match    ( LPtr1, EndLengthPtr1, *LPtr0+Length0-Length1, Match1, Total1 ) ;
		if ( abs(Match0)<abs(Match1) )
		{
			if ( Total0!=1 )
			{
				Match0 += *LPtr1+Length1-Length0 ;
				if ( IsntCurve(Type1) )
				{
					P11.x = (2*P10.x+P13.x)/3 ; P12.x = (P10.x+2*P13.x)/3 ;
					P11.y = (2*P10.y+P13.y)/3 ; P12.y = (P10.y+2*P13.y)/3 ;
				}
				for ( t=2 ; t<=Total0 ; t++ )
				{
					if ( IsCurve(Type0) || IsCurve(Type1) )
					{
						if ( IsntCurve(Type0) )
						{
							P01.x = (2*P00.x+P03.x)/3 ; P02.x = (P00.x+2*P03.x)/3 ;
							P01.y = (2*P00.y+P03.y)/3 ; P02.y = (P00.y+2*P03.y)/3 ;
						}
						Split( P10,P11,P12,P13, *LPtr0,Match0 ) ;
						if ( !BlendCurve( P01,P02,P03, L1,L2,M ) )
							return FALSE ;
						P10 = M ;
						P11 = R1 ;
						P12 = R2 ;
					}
					else
					{
						P10.x += MulDiv(P13.x-P10.x,*LPtr0,Match0) ;
						P10.y += MulDiv(P13.y-P10.y,*LPtr0,Match0) ;
						if ( !BlendPoint( PT_LINETO, P03, P10 ) )
							return FALSE ;
					}
					P00 = P03 ;
					Match0 -= *LPtr0 ;
					ReadPath0() ;
				}
			}
		}
		else
		{
			if ( Total1!=1 )
			{
				Match1 += *LPtr0+Length0-Length1 ;
				if ( IsntCurve(Type0) )
				{
					P01.x = (2*P00.x+P03.x)/3 ; P02.x = (P00.x+2*P03.x)/3 ;
					P01.y = (2*P00.y+P03.y)/3 ; P02.y = (P00.y+2*P03.y)/3 ;
				}
				for ( t=2 ; t<=Total1 ; t++ )
				{
					if ( IsCurve(Type0) || IsCurve(Type1) )
					{
						if ( IsntCurve(Type1) )
						{
							P11.x = (2*P10.x+P13.x)/3 ; P12.x = (P10.x+2*P13.x)/3 ;
							P11.y = (2*P10.y+P13.y)/3 ; P12.y = (P10.y+2*P13.y)/3 ;
						}
						Split( P00,P01,P02,P03, *LPtr1,Match1 ) ;
						if ( !BlendCurve( L1,L2,M, P11,P12,P13 ) )
							return FALSE ;
						P00 = M ;
						P01 = R1 ;
						P02 = R2 ;
					}
					else
					{
						P00.x += MulDiv(P03.x-P00.x,*LPtr1,Match1) ;
						P00.y += MulDiv(P03.y-P00.y,*LPtr1,Match1) ;
						if ( !BlendPoint( PT_LINETO, P00, P13 ) )
							return FALSE ;
					}
					P10 = P13 ;
					Match1 -= *LPtr1 ;
					ReadPath1()	;
				}
			}
		}
		if ( !Blend1to1() )
			return FALSE ;
	} /* while */
	return TRUE ;
}

BOOL GBlend::Blend1to1()
{
	if ( IsCurve(Type0) || IsCurve(Type1) )
	{
		if ( IsntCurve(Type0) )
		{
			P01.x = (2*P00.x+P03.x)/3 ; P02.x = (P00.x+2*P03.x)/3 ;
			P01.y = (2*P00.y+P03.y)/3 ; P02.y = (P00.y+2*P03.y)/3 ;
		}
		if ( IsntCurve(Type1) )
		{
			P11.x = (2*P10.x+P13.x)/3 ; P12.x = (P10.x+2*P13.x)/3 ;
			P11.y = (2*P10.y+P13.y)/3 ; P12.y = (P10.y+2*P13.y)/3 ;
		}
		if ( !BlendCurve( P01,P02,P03, P11,P12,P13 ) )
			return FALSE ;
	}
	else
		if ( !BlendPoint( PT_LINETO, P03, P13 ) )
			return FALSE ;
	P00 = P03 ; ReadPath0() ;
	P10 = P13 ;	ReadPath1() ;
	return TRUE ;
}

BOOL GBlend::BlendPoint( BYTE Type, POINT P0, POINT P1 )
{
	if ( --OLength<0 )
		return FALSE ;
	*OTypes++ = Type ;
	OPoints->x = P0.x+ScaledMul(Ratio,P1.x-P0.x) ;
	OPoints->y = P0.y+ScaledMul(Ratio,P1.y-P0.y) ;
	OPoints++ ;
	return TRUE ;
}

BOOL GBlend::BlendCurve( POINT P01,POINT P02,POINT P03, POINT P11,POINT P12,POINT P13 )
{
	return BlendPoint( PT_BEZIERTO, P01, P11 ) &&
		   BlendPoint( PT_BEZIERTO, P02, P12 ) &&
		   BlendPoint( PT_BEZIERTO, P03, P13 ) ;
}

void GBlend::Match( PUINT32 Ptr, PUINT32 EndPtr, UINT32 Length, INT32 &Match, UINT32 &Total )
{
	Match = -(INT32)Length ;
	Total = 0 ;
	if ( Ptr<EndPtr )
	{
		Match += *Ptr++ ;
		Total++ ;
		while ( Ptr<EndPtr-1 && abs((INT32)Match)>abs((INT32)(*Ptr+Match)) )
		{
			Match += *Ptr++ ;
			Total++ ;
		}
	}
}

void GBlend::MatchLast( PUINT32 Ptr, PUINT32 EndPtr, UINT32 Length, INT32 &Match, UINT32 &Total )
{
	Match = -(INT32)Length ;
	Total = 0 ;
	while ( Ptr<EndPtr )
	{
		Match += *Ptr++ ;
		Total++ ;
	}
}

void GBlend::Split( POINT P0,POINT P1,POINT P2,POINT P3, INT32 N,UINT32 D )
{
	L1.x = P0.x+MulDiv(P1.x-P0.x,N,D) ; L1.y = P0.y+MulDiv(P1.y-P0.y,N,D) ;
	 M.x = P1.x+MulDiv(P2.x-P1.x,N,D) ;  M.y = P1.y+MulDiv(P2.y-P1.y,N,D) ;
	R2.x = P2.x+MulDiv(P3.x-P2.x,N,D) ; R2.y = P2.y+MulDiv(P3.y-P2.y,N,D) ;
	L2.x = L1.x+MulDiv( M.x-L1.x,N,D) ; L2.y = L1.y+MulDiv( M.y-L1.y,N,D) ;
	R1.x =  M.x+MulDiv(R2.x- M.x,N,D) ; R1.y =  M.y+MulDiv(R2.y- M.y,N,D) ;
	 M.x = L2.x+MulDiv(R1.x-L2.x,N,D) ;  M.y = L2.y+MulDiv(R1.y-L2.y,N,D) ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void GBlend::ReadPath0()
{
	Length0 += *LPtr0++ ;
	ReadPathStart0() ;
}

void GBlend::ReadPathStart0()
{
	if ( ILength0==0 )
		Type0 = PT_END ;
	else if ( IsLine(Type0=*ITypes0) )
	{
		ITypes0++ ;
		P03 = *IPoints0++ ;
		ILength0-- ;
	}
	else /* Curve */
	{
		ITypes0+=3 ;
		P01 = *IPoints0++ ;
		P02 = *IPoints0++ ;
		P03 = *IPoints0++ ;
		ILength0-=3 ;
	}
}

void GBlend::ReadPath1()
{
	Length1 += *LPtr1++ ;
	ReadPathStart1() ;
}

void GBlend::ReadPathStart1()
{
	if ( ILength1==0 )
		Type1 = PT_END ;
	else if ( IsLine(Type1=*ITypes1) )
	{
		ITypes1++ ;
		P13 = *IPoints1++ ;
		ILength1-- ;
	}
	else /* Curve */
	{
		ITypes1+=3 ;
		P11 = *IPoints1++ ;
		P12 = *IPoints1++ ;
		P13 = *IPoints1++ ;
		ILength1-=3 ;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

INT32 GBlend::BezierLength( POINT P0, POINT P1, POINT P2, POINT P3 )
{
	UINT32 dx,dy ;
	dx = abs(P1.x*3 - P0.x*2 - P3.x) ;
	dy = abs(P1.y*3 - P0.y*2 - P3.y) ;
	if ( (dx>=dy ? 3*dx+dy : dx+3*dy) > Flatness )
    	return FlattenSplit(P0,P1,P2,P3) ;
	dx = abs(P2.x*3 - P0.x - P3.x*2) ;
	dy = abs(P2.y*3 - P0.y - P3.y*2) ;
	if ( (dx>=dy ? 3*dx+dy : dx+3*dy) > Flatness )
    	return FlattenSplit(P0,P1,P2,P3) ;
	return length(P0,P3) ;
}


INT32 GBlend::FlattenSplit( POINT P0, POINT P1, POINT P2, POINT P3 )
{
	POINT L1, L2, M, R1, R2 ;
	L1.x = (P0.x + P1.x)/2;
	L1.y = (P0.y + P1.y)/2;
	L2.x = (P0.x + 2*P1.x + P2.x)/4;
	L2.y = (P0.y + 2*P1.y + P2.y)/4;
	 M.x = (P0.x + 3*P1.x + 3*P2.x + P3.x)/8;
	 M.y = (P0.y + 3*P1.y + 3*P2.y + P3.y)/8;
	R1.x = (P1.x + 2*P2.x + P3.x)/4;
	R1.y = (P1.y + 2*P2.y + P3.y)/4;
	R2.x = (P2.x + P3.x)/2;
	R2.y = (P2.y + P3.y)/2;
    return BezierLength(P0, L1, L2, M) + BezierLength(M, R1, R2, P3) ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
