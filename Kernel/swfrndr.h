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

#ifndef INC_FLASH_RENDER_H
#define INC_FLASH_RENDER_H

#include "fillramp.h"
//#include "rndrgn.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "vectrndr.h"
#include "nodetext.h"
#include "nodeshad.h"
#include "swfbitmp.h"
#include "swftext.h"
#include "swffont.h"
#include "swfshape.h"
#include "swfbuttn.h"
#include "swfplace.h"
#include "swfsprit.h"

class NodeBevel;
class NodeBevelBegin;

// The following functions perform the same role as many of the macros defined in the
// older Camelot code, but since they're based around templates, incorporate type
// checking, and are thus safer to use.

/********************************************************************************************

>	template < class T > T Max ( T InputA, T InputB )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/8/99
	Purpose:	Replacement for the Max macro. It's type safe, and can operate on any C++
				data type.
	Returns:	The maximum of either InputA or InputB.
	SeeAlso:	-

********************************************************************************************/

template < class T > T Max ( T InputA, T InputB )
{
	if ( InputA > InputB )
		return InputA;
	else
		return InputB;
}

/********************************************************************************************

>	template < class T > T Max ( T InputA, T InputB, T InputC, T InputD )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/8/99
	Purpose:	Wrapper around the Max function to return the maximum value from four
				values. (Used for finding the maximum value for the extends of a bounding
				rectangle.
	Returns:	The maximum value of the four inputs.
	SeeAlso:	-

********************************************************************************************/

template < class T > T Max ( T InputA, T InputB, T InputC, T InputD )
{
	return Max ( Max ( InputA, InputB ), Max ( InputC, InputD ) );
}

/********************************************************************************************

>	template < class T > T Min ( T InputA, T InputB )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/11/99
	Purpose:	Replacement for the Min macro. It's type safe, and can operate on any C++
				data type.
	Returns:	The minimum of either InputA or InputB.
	SeeAlso:	-

********************************************************************************************/

template < class T > T Min ( T InputA, T InputB )
{
	if (  ( InputA ) <  ( InputB ) )
		return InputA;
	else
		return InputB;
}

/********************************************************************************************

>	template < class T > T Min ( T InputA, T InputB, T InputC, T InputD )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/11/99
	Purpose:	Wrapper around the Min function to return the minimum value from four
				values. (Used for finding the minimum value for the extends of a bounding
				rectangle.
	Returns:	The minimum value of the four inputs.
	SeeAlso:	-

********************************************************************************************/

template < class T > T Min ( T InputA, T InputB, T InputC, T InputD )
{
	return Min ( Min ( InputA, InputB ), Min ( InputC, InputD ) );
}

/********************************************************************************************

>	template < class T > T Absol ( T a )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/8/99
	Purpose:	Replacement for the Abs macro. It's got the advantage of being easier
				to debug, and fully type safe.
	Returns:	The maximum of either a or b.
	SeeAlso:	-

********************************************************************************************/

template < class T > T Absol ( T a )
{
	if ( a < 0 )
		return -a;
	else
		return a;
}

/********************************************************************************************

>	class FlashRenderRegion : public VectorFileRenderRegion

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/8/99
	Purpose:	Provides the necessary functions to convert image data stored in the
				Camelot tree into the correct values for exporting to the Flash 4 format,
				and output these to the relevant device context.
	
********************************************************************************************/

class FlashRenderRegion : public VectorFileRenderRegion
{
public:
	CC_DECLARE_DYNAMIC( FlashRenderRegion )
 
	// Constructors.
	FlashRenderRegion ( void );
	FlashRenderRegion ( DocRect ClipRect,
						Matrix ConvertMatrix,
						FIXED16 ViewScale );

	// Destructor.
	~FlashRenderRegion( void );

	// Normal functions.
	BOOL ExportCharacter ( TextChar *pTheLetter );
	BOOL ExportBevel ( NodeBevel *pBevel );
	BOOL ExportBevelBegin ( NodeBevelBegin *pBevel );
	BOOL ExportShadow ( Path *pShadowPath,
						OILBitmap *pBitmap,
					    UINT32 Darkness );
	BOOL ExportRenderableNode ( NodeRenderableInk *pInk );

	BOOL ExportAll ( void );

	// These set layer and button IDs used to export roll-over states.
	void SetButtonName ( TCHAR *pButtonName );
	void SetLayerState ( LayerState State );

protected:

	void DrawPathToOutputDevice ( Path *PathToRender,
								  PathShape shapePath = PATHSHAPE_PATH );

	// Extra functionality.
	void InitPointers ( void );

	BOOL ProcessPath ( Path *pPath );
	BOOL ProcessFill ( FillGeometryAttribute *pFill,
					   TranspFillAttribute *pTransparency );
	BOOL ProcessColour ( FillGeometryAttribute *pFill );
	BOOL ProcessTransparency ( TranspFillAttribute *pTransparency,
							   FillGeometryAttribute *pFill );
	BOOL CreateTextRecord ( TextChar *pTheLetter );
	BOOL ProcessFlatFill ( DocColour *pColour );
	BOOL ProcessGradientFill ( DocColour *pStartColour,
							   DocColour *pMidColour,
							   DocColour *pEndColour,
							   ColourRamp *pRamp,
							   DocCoord *pStartPoint,
							   DocCoord *pEndPoint,
							   DocCoord *pEndPoint2,
							   BYTE FillType );
	BOOL ProcessBitmapFill ( FillGeometryAttribute *pFill );
	BOOL RecordBitmapFill ( BitmapFillAttribute *pFill,
							WORD BitmapID );
	WORD GetBitmapID ( OILBitmap *pBitmap,
					   DocColour *pStartColour,
					   DocColour *pEndColour,
					   UINT32		 Transparency );
	BOOL ProcessFlatTransp ( UINT32 Transparency );
	BOOL ProcessGradientTransp ( UINT32 *pStartTransparency,
								 UINT32 *pMidTransparency,
								 UINT32 *pEndTransparency,
								 DocCoord *pStartPoint,
								 DocCoord *pEndPoint,
								 DocCoord *pEndPoint2,
								 BYTE FillType );
	BOOL ProcessBitmapTransp ( TranspFillAttribute *pTransparency,
							   FillGeometryAttribute *pFill );

	UINT32 BlendTransparencies ( UINT32 *pStart,
							   UINT32 *pEnd1,
							   UINT32 *pEnd2,
							   UINT32 *pEnd3 );

	DocColour BlendColours ( DocColour *pStart,
							 DocColour *pEnd1,
							 DocColour *pEnd2,
							 DocColour *pEnd3,
							 ColourRamp *pRamp );

	FlashButtonRecord* ProcessURL ( WebAddressAttribute *pWebAddress );

	BOOL ExportButtonState ( FlashButtonRecord *pButton );

	FlashButtonRecord* MatchButton ( void );

	FlashSprite* MatchSprite ( FlashButtonRecord *pButton );

	BOOL PlaceObject ( WORD ID,
					   FlashType ToRender,
					   DocCoord *pPosition = NULL,
					   BOOL DoTransform = FALSE );

	// Member variables.
	FlashBitmapRecord	*mpBitmap;
	FlashBitmapRecord	*mpBitmapTail;
	FlashTextRecord		*mpText;
	FlashTextRecord		*mpTextTail;
	FlashFontRecord		*mpFont;
	FlashFontRecord		*mpFontTail;
	FlashShapeRecord	*mpShape;
	FlashShapeRecord	*mpShapeTail;
	FlashShapeRecord	*mpShapeLast;
	FlashButtonRecord	*mpButton;
	FlashButtonRecord	*mpButtonTail;
	FlashSprite			*mpSprite;
	FlashSprite			*mpSpriteTail;
	FlashPlaceObject	*mpPlace;
	FlashPlaceObject	*mpPlaceTail;
	String_256			mButtonName;
	LayerState			mButtonState;
	BOOL				mSupressLines;
	BOOL				mExportStroke;
};

#endif	// #ifndef
