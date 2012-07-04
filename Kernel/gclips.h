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

// Gavin's path clipping code

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// GClipS.h
//
/////////////////////////////////////////////////////////////////////////////////////////////////

const UINT32 CLIPPING_STYLE		    = 0x0007 ;
const UINT32 CLIPPING_SOURCE_WINDING	= 0x0010 ;
const UINT32 CLIPPING_CLIP_WINDING	= 0x0020 ;
const UINT32 CLIPPING_IS_STROKED		= 0x0040 ;
const UINT32 CLIPPING_IS_CLOSED		= 0x0080 ;

const UINT32 EDGE_CLIP		= 0x0001 ;
const UINT32 EDGE_REVERSED	= 0x0002 ;
const UINT32 EDGE_CURVED		= 0x0004 ;
const UINT32 EDGE_STROKED	= 0x0008 ;

/////////////////////////////////////////////////////////////////////////////////////////////////

struct Curve {
	POINT	P0 ;
	POINT	P1 ;
	POINT	P2 ;
	POINT	P3 ;
} ;

struct Edge {
	Edge	*LK ;			// Link
	Edge	*RLK ;			// Reverse link - only used to initially sort the edges
	double	DX ;			// Slope = (XE-XS)/(YE-YE)
	INT32	XS,YS ;			// Start point
	INT32	XE,YE ;			// End point
	INT32	XI,YI ;			// Intersection point
	UINT32	FF ;			// Flags
	Curve	*ID ;			// Pointer to curve data - used as curve ID.
	UINT32	TS ;			// Start t parameter
	UINT32	TE ;			// End t parameter
} ;

struct LineEdge {
	Edge	*LK ;
	Edge	*RLK ;
	double	DX ;
	INT32	XS,YS ;
	INT32	XE,YE ;
	INT32	XI,YI ;
	UINT32	FF ;
} ;

struct CurveEdge {
	Edge	*LK ;
	Edge	*RLK ;
	double	DX ;
	INT32	XS,YS ;
	INT32	XE,YE ;
	INT32	XI,YI ;
	UINT32	FF ;
	Curve	*ID ;
	UINT32	TS ;
	UINT32	TE ;
} ;

struct Strip {
	Strip	*FSLK ;				// [L]in[K] to next strip, [F]orward sorted by [S]tart value.
	Strip	*RELK ;				// [L]in[K] to next strip, [R]everse sorted by [E]nd value.
	INT32	YS,YE ;
	union	{
		struct {
			INT32	XSL,XEL ;
			union {
				double	DXL ;
				__int64	FGL ;	// -infinity if curve, +infinity if strip is invalid
			} ;
			UINT32	TSL,TEL ;
			INT32	XSR,XER ;
			union {
				double	DXR ;
				__int64	FGR ;	// -infinity if curve
			} ;
			UINT32	TSR,TER ;
			Curve	*IDL,*IDR ;
		} ;
		struct {
			Strip	*FELK ;		// [L]in[K] to next strip, [F]orward sorted by [E]nd value.
			Strip	*RSLK ;		// [L]in[K] to next strip, [R]everse sorted by [S]tart value.
			INT32	XS,XE ;
			union {
				double	DX ;
				__int64	FG ;
			} ;
			UINT32	TS,TE ;
			Curve	*ID ;
		} ;
	} ;
} ;

struct FilledStrip {
	Strip	*FSLK ;				// [L]in[K] to next strip, [F]orward sorted by [S]tart value.
	Strip	*RELK ;				// [L]in[K] to next strip, [R]everse sorted by [E]nd value.
	INT32	YS,YE ;
	INT32	XSL,XEL ;
	union {
		double	DXL ;
		__int64	FGL ;			// -infinity if curve, +infinity if strip is invalid
	} ;
	UINT32	TSL,TEL ;
	INT32	XSR,XER ;
	union {
		double	DXR ;
		__int64	FGR ;			// -infinity if curve
	} ;
	UINT32	TSR,TER ;
	Curve	*IDL,*IDR ;
} ;

struct LineStrip {
	Strip	*FSLK ;				// [L]in[K] to next strip, [F]orward sorted by [S]tart value.
	Strip	*RELK ;				// [L]in[K] to next strip, [R]everse sorted by [E]nd value.
	INT32	YS,YE ;
	Strip	*FELK ;				// [L]in[K] to next strip, [F]orward sorted by [E]nd value.
	Strip	*RSLK ;				// [L]in[K] to next strip, [R]everse sorted by [S]tart value.
	INT32	XS,XE ;
	union {
		double	DX ;
		__int64	FG ;
	} ;
	UINT32	TS,TE ;
	Curve	*ID ;
} ;

/////////////////////////////////////////////////////////////////////////////////////////////////

inline bool IsMove ( CONST BYTE Type ) { return (Type & PT_MOVETO)==PT_MOVETO   ; }
inline bool IsLine ( CONST BYTE Type ) { return (Type & PT_MOVETO)==PT_LINETO   ; }
inline bool IsCurve( CONST BYTE Type ) { return (Type & PT_MOVETO)==PT_BEZIERTO ; }

inline bool IsntMove ( CONST BYTE Type ) { return (Type & PT_MOVETO)!=PT_MOVETO   ; }
inline bool IsntLine ( CONST BYTE Type ) { return (Type & PT_MOVETO)!=PT_LINETO   ; }
inline bool IsntCurve( CONST BYTE Type ) { return (Type & PT_MOVETO)!=PT_BEZIERTO ; }

/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma warning( disable : 4800 )

inline bool IsSourceWinding( UINT32 Flags ) { return Flags & CLIPPING_SOURCE_WINDING ; }
inline bool IsClipWinding  ( UINT32 Flags ) { return Flags & CLIPPING_CLIP_WINDING   ; }
inline bool IsPathStroked  ( UINT32 Flags ) { return Flags & CLIPPING_IS_STROKED     ; }
inline bool IsPathClosed   ( UINT32 Flags ) { return Flags & CLIPPING_IS_CLOSED      ; }

#pragma warning( default : 4800 )

/////////////////////////////////////////////////////////////////////////////////////////////////

inline UINT32 LO( CONST UINT32 l ) { return l & 0x0000ffff ; }
inline UINT32 HI( CONST UINT32 l ) { return l & 0xffff0000 ; }

/////////////////////////////////////////////////////////////////////////////////////////////////
