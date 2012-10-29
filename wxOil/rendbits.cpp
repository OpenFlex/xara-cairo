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


// class to render into a bitmap (for hit-testing)

/*
*/

#include "camtypes.h"
#include "rendbits.h"
#include "ccdc.h"
//#include "resource.h"
#include "grndclik.h"

// RealClickClass is the class name to use for generic 'bitmap click' class whic
// exands to either OSRenderBitmap or GRenderClick

#define	RealClickClass	GRenderClick



#define new CAM_DEBUG_NEW


#ifndef CLR_INVALID
// Win16 doesn't define this
#define	CLR_INVALID	0xFFFFFFFF
#endif



/********************************************************************************************

>	RenderRegion* OSRenderBitmap::Create(DocRect Rect, Matrix ConvertMatrix, FIXED16 Scale, UINT32 Depth)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Creates a region of type OSRenderBitmap (GDI) or GRenderClick (GDraw).
	SeeAlso:	OSRenderRegion::Create

********************************************************************************************/
/*
RenderRegion* OSRenderBitmap::Create(DocRect Rect, Matrix ConvertMatrix, FIXED16 Scale, UINT32 Depth, BOOL colour)
{
	if (colour == FALSE)
		return new GRenderClick( Rect, ConvertMatrix, Scale, Depth, 0.0 );
	else
		return new GRenderClickColour( Rect, ConvertMatrix, Scale, Depth, 0.0 );
}
*/




/********************************************************************************************

>	RenderRegion* OSRenderBitmap::Create(DocRect Rect, Matrix ConvertMatrix, FIXED16 Scale, RenderType rType)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Creates a region of type OSRenderBitmap (GDI) or GRenderClick (GDraw).
	SeeAlso:	OSRenderRegion::Create

********************************************************************************************/

RenderRegion* OSRenderBitmap::Create(DocRect Rect, Matrix ConvertMatrix, FIXED16 Scale, RenderType rType)
{
	switch (rType)
	{
	case RENDERTYPE_MONOBITMAP:
//		TRACE(_T("Creating MONOBITMAP region (%d, %d) - (%d, %d)  GRenderClick\n"), Rect.lo.x, Rect.lo.y, Rect.hi.x, Rect.hi.y);
		return new GRenderClick( Rect, ConvertMatrix, Scale, 1, 0.0 );
		break;

	case RENDERTYPE_COLOURBITMAP:
//		TRACE(_T("Creating COLOURBITMAP region (%d, %d) - (%d, %d)  GRenderClickColour\n"), Rect.lo.x, Rect.lo.y, Rect.hi.x, Rect.hi.y);
		return new GRenderClickColour( Rect, ConvertMatrix, Scale, 32, 0.0 );
		break;

	case RENDERTYPE_HITDETECT:
//		TRACE(_T("Creating HITDETECT region (%d, %d) - (%d, %d)  GRenderClickColourNoPaper\n"), Rect.lo.x, Rect.lo.y, Rect.hi.x, Rect.hi.y);
		return new GRenderClickColourNoPaper( Rect, ConvertMatrix, Scale, 32, 0.0 );
// BODGE TEST! DO NOT RELEASE!
//		return new GRenderClick( Rect, ConvertMatrix, Scale, 1, 0.0 );
		break;

	default:
		ENSURE(FALSE, "Invalid RenderType passed to OSRenderBitmap::Create");
		return NULL;
	}
	return NULL;
}





/********************************************************************************************

>	BitmapContents OSRenderBitmap::GetContents( RenderRegion *pRegion, BOOL justmiddle)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/93
	Inputs:		A render region which must have been created with RenderOnTop(MONOBITMAP).
				if justmiddle is TRUE, only checks on the centre pixel will be done (which
				is faster).
	Outputs:	None
	Returns:	BITMAPCONTENTS_CENTRE if centre pixel is set, _ANY if any pixel is set,
				_NONE if none and _ERROR if failed for some reason.
	Purpose:	To investigate whether anything has been rendered into a bitmap-based
				render region.
	Errors:		Will ENSURE if NULL render region, if it is not really a OSRenderBitmap.
	Scope:		Static

********************************************************************************************/

BitmapContents OSRenderBitmap::GetContents( RenderRegion *pRegion, BOOL JustMiddle)
{
	ERROR2IF( pRegion==NULL, BITMAPCONTENTS_ERROR, "NULL pRegion" );

	ERROR2IF( !pRegion->IsKindOf(CC_RUNTIME_CLASS(GRenderClick)), BITMAPCONTENTS_ERROR, "Wrong class"  );

	RealClickClass *pBitmap = (RealClickClass*)pRegion;	 			// safe to cast now
	return pBitmap->GetContents( JustMiddle );						// then use member fn
}


/********************************************************************************************

>	void OSRenderBitmap::DebugMe( RenderRegion*, INT32 Stretch=1 )

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/11/93
	Inputs:		How much you want the image stretched by
	Outputs:	-
	Returns:	-
	Purpose:	Dupms the current bitmap onto the current view window, so we can see what
				is going on.
	Errors:		-
	Scope:		Public static

********************************************************************************************/

void OSRenderBitmap::DebugMe(RenderRegion *pRegion, INT32 Stretch)
{

	if (pRegion->IsKindOf( CC_RUNTIME_CLASS(GRenderClick) ) )
		((RealClickClass*)pRegion)->DebugMe(Stretch);
	else
		ERROR3("Wrong class for DebugMe");
}
