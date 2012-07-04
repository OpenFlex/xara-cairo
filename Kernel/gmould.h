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

// Header for the base class mould shapes implementation

#ifndef INC_GMOULD
#define INC_GMOULD

/********************************************************************************************

>	class GMould : public CCObject

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com> / Peter
	Created:	21/01/97
	Purpose:	common functions used GEnvelope and GPerspective are held in this base class.

********************************************************************************************/

/*

void Define( POINT *P, RECT *pBBox, DWORD pTolerance = 0 ) ;

	Define the envelope with twelve control points P. The source path has bounding box pBBox.
	pTolerance defines the accuracy with which curves are moulded. If pTolerance is zero then
	curves are never split.

void FitPoint(  POINT a, POINT& b ) ;

	This will mould the point a returning the result in b. Note that a may be outside the
	original bounding box.

void FitPoint( DPOINT a, POINT& b ) ;

	This will mould the point a specified as two values in the range 0 to 1. The result is
	returned in b. This call can be used for drawing grid points.

void PlotTile(
	void* pData,
	void PlotTriangle(
		void* pData,
		CONST POINT *PointA, CONST POINT *PointB, CONST POINT *PointC,
		CONST POINT *Point0, CONST POINT *Point1, CONST POINT *Point2
	),
	CONST POINT *PointA, CONST POINT *PointB, CONST POINT *PointC,
	CONST INT32 Steps
) ;

	This call can be used to plot a bitmap by splitting the bitmap into triangles. The bitmap
	area is defined by the three points PointA, PointB and PointC. Steps controls the fineness of
	the approximation. The PlotTriangle routine is called to plot each triangle in turn. It is
	passed pData and the new bitmap control points PointA, PointB, PointC and the triangle
	boundary points Point0, Point1, Point2. pData can be used as a pointer to a data block
	containing such information as the bitmap size.

void PlotTile4(
	void* pData,
	void PlotTriangle(
		void* pData,
		CONST POINT *PointA, CONST POINT *PointB, CONST POINT *PointC,
		CONST POINT *Point0, CONST POINT *Point1, CONST POINT *Point2
	),
	CONST POINT *PointA, CONST POINT *PointB, CONST POINT *PointC, CONST POINT *PointD,
	CONST INT32 Steps
) ;

	This call can be used to plot a bitmap by splitting the bitmap into triangles. The bitmap
	area is defined by the three points PointA, PointB, PointC and PointD. Other parameters are
	as for PlotTile.

*/


class GPerspective ;

class GMould : public CCObject
{
	CC_DECLARE_DYNAMIC(GMould)
	
	public:
		GMould();

		BOOL Define( POINT *P, RECT *pBBox, DWORD pTolerance = 0 );
		
		virtual void CopyShape( POINT *P ) = 0;
		virtual BOOL Redefine( POINT *P ) = 0 ;
		virtual BOOL FitPath(CONST POINT *IPoints,	
							 CONST BYTE  *ITypes, 
							 DWORD ILength,
							 LPPOINT OPoints, 
							 LPBYTE  OTypes, 
							 DWORD OLength,	
							 BOOL Close = FALSE) = 0;

		void	FitPoint( POINT a, POINT& b );
		void	FitPoint( DPOINT a, POINT& b );
		DocRect GetBoundingRect();
		RECT    GetSourceBBox() const { return SrcBBox; }

	/*
		void PlotTile(
			void* pData,
			void PlotTriangle(
				void* pData,
				CONST POINT *PointA, CONST POINT *PointB, CONST POINT *PointC,
				CONST POINT *Point0, CONST POINT *Point1, CONST POINT *Point2
			),
			CONST POINT *PointA, CONST POINT *PointB, CONST POINT *PointC,
			CONST INT32 Steps
		) ;
		void PlotTile4(
			void* pData,
			void PlotTriangle(
				void* pData,
				CONST POINT *PointA, CONST POINT *PointB, CONST POINT *PointC,
				CONST POINT *Point0, CONST POINT *Point1, CONST POINT *Point2
			),
			CONST POINT *PointA, CONST POINT *PointB, CONST POINT *PointC, CONST POINT *PointD,
			CONST INT32 Steps
		) ;
	*/


	protected:
		double CalcTolerance( DWORD pTolerance );
		
		inline BOOL	GenOp( BYTE Op, DPOINT T );
		inline BOOL	GenMove( DPOINT T );
		inline BOOL	GenLine( DPOINT T );
		
		void        ScaleSrc(  POINT a, DPOINT& b ) ;
		void           Scale(  POINT a, DPOINT& b ) ;
		void	InverseScale( DPOINT a,  POINT& b ) ;

		BOOL	GenCurve( DPOINT C2, DPOINT C4, 
						  DPOINT P0, DPOINT P2, DPOINT P4, DPOINT P6,
						  DPOINT T0, DPOINT T2, DPOINT T4, DPOINT T6 );

		virtual void ScaleView() = 0;
		virtual void CalcViewBBox() = 0;
		virtual void CalcViewConsts() = 0;
		virtual void Transform( DPOINT a, DPOINT& b ) = 0;

	protected:
		RECT    SrcBBox ;
		INT32    MinX, MaxX, MinY, MaxY;
		INT32	Width, Depth ;

		double  Tolerance ;
		LPPOINT OPoints ; 
		LPBYTE  OTypes ; 
		DWORD   OLength ;


	/*
		void PlotTile(
			void* pData,
			void PlotTriangle(
				void* pData,
				CONST POINT *PointA, CONST POINT *PointB, CONST POINT *PointC,
				CONST POINT *Point0, CONST POINT *Point1, CONST POINT *Point2
			),
			CONST INT32 Tolerance,
			INT32 i, INT32 j, INT32 s,
			POINT p00, POINT p10, POINT p11, POINT p01,
			POINT q00, POINT q10, POINT q11, POINT q01,
			BOOL f00_10, BOOL f10_11, BOOL f01_11, BOOL f00_01
		) ;
		void PlotTile4(
			void* pData,
			void PlotTriangle(
				void* pData,
				CONST POINT *PointA, CONST POINT *PointB, CONST POINT *PointC,
				CONST POINT *Point0, CONST POINT *Point1, CONST POINT *Point2
			),
			CONST INT32 Tolerance,
			GPerspective* Per,
			INT32 i, INT32 j, INT32 s,
			POINT p00, POINT p10, POINT p11, POINT p01,
			POINT q00, POINT q10, POINT q11, POINT q01,
			BOOL f00_10, BOOL f10_11, BOOL f01_11, BOOL f00_01
		) ;
		void PlotTriangles(
			void* pData,
			void PlotTriangle(
				void* pData,
				CONST POINT *PointA, CONST POINT *PointB, CONST POINT *PointC,
				CONST POINT *Point0, CONST POINT *Point1, CONST POINT *Point2
			),
			INT32 i, INT32 j, INT32 s,
			POINT q00, POINT q10, POINT q11, POINT q01
		) ;
	*/

};


inline BOOL GMould::GenOp( BYTE Op, DPOINT T )
{
	if ( OLength-- < 1 ) return FALSE ;
	InverseScale( T, *OPoints++ ) ; *OTypes++ = Op ;
	return TRUE ;
}

inline BOOL GMould::GenMove( DPOINT T )
{
	return GenOp( PT_MOVETO, T );
}

inline BOOL GMould::GenLine( DPOINT T )
{
	return GenOp( PT_LINETO, T );
}


#endif
