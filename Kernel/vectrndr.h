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

#ifndef _INC_VECTOR_RENDER_REGION_H
#define _INC_VECTOR_RENDER_REGION_H

/********************************************************************************************

>	class VectorFileRenderRegion : public RenderRegion

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/10/00
	Purpose:	Encapsulates the functions shared by the CMX, EPS, and Flash render regions.
				This class is never itself instantiated.

********************************************************************************************/

class VectorFileRenderRegion : public RenderRegion
{
	CC_DECLARE_DYNAMIC ( VectorFileRenderRegion )

public:

	// Constructors.
	VectorFileRenderRegion( void );
	VectorFileRenderRegion( DocRect	ClipRect,
							 Matrix		ConvertMatrix,
							 FIXED16	ViewScale );

	// Destructor.
	virtual ~VectorFileRenderRegion( void );

	// Initialisation code.
	BOOL Init( void );

	// Start and stop rendering.
	virtual BOOL StartRender( void );
	virtual BOOL StopRender( void );		

	// These functions are never called, but are included to over-ride pure virtuals in the
	// base class.
	void DrawRect( DocRect *RectToRender );
	void DrawDragRect( DocRect *RectToRender );
	void DrawLine( const DocCoord	&StartPoint,
					const DocCoord	&EndPoint );
	void DrawPixel( const DocCoord &Point );
	void DrawBlob( DocCoord	p,
					BlobType	type );
	void DrawCross( const DocCoord	&Point,
					 const UINT32		Size );
	void DrawBitmap( const DocCoord	&Point,
					  KernelBitmap*		pBitmap );
	void DrawBitmap( const DocCoord	&Point,
					  UINT32				BitmapID,
					  UINT32				ToolID = NULL );
	void DrawBitmapBlob( const DocCoord	&Point,
						  KernelBitmap*		BlobShape );
	void DrawBitmapBlob( const DocCoord	&Point, ResourceID resID );

protected:

	// Calculate the size of a pixel.
	MILLIPOINT CalcPixelWidth();
	MILLIPOINT CalcScaledPixelWidth();

	// Initialisation functions.
	virtual void InitClipping();
	virtual void InitAttributes();
	virtual void DeInitAttributes();
	virtual void SetOSDrawingMode();
	virtual void SetQualityLevel();

	// Blending function for rendering shadows.
	DocColour AlphaBlend( DocColour &Foreground,
						   DocColour &Background,
						   UINT32 Transp );

	// Member variables.
	AttributeEntry	*LastOutputAttrs;
};

#endif
