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

// pathpcs - Definition of rendering PathProcessor class

#include "camtypes.h"

#include "pathpcs.h"


CC_IMPLEMENT_DYNAMIC(PathProcessor, CCObject);

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW



/********************************************************************************************

>	PathProcessor::PathProcessor()

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/12/96

	Purpose:	Constructor

********************************************************************************************/

PathProcessor::PathProcessor()
{
	NextProcessor = NULL;
	ParentAttr	  = NULL;
	m_DisableMe   = FALSE;
}



/********************************************************************************************

>	virtual PathProcessor::~PathProcessor()

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/12/96

	Purpose:	Destructor
	
	Errors:		If this object still has a non-NULL Next pointer, it will ERROR3 in
				an effort to get you to clean up properly before destruction.

********************************************************************************************/

PathProcessor::~PathProcessor()
{
	ERROR3IF(NextProcessor != NULL, "PathProcessor deleted while still possibly held in stack");
}



/********************************************************************************************

>	virtual BOOL PathProcessor::WillChangeFillAndStrokeSeparately(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/12/96

	Purpose:	Called by the RenderRegion to determine if this PathProcessor affects
				the "fill" and "stroke" portions of the path separately. (Generally
				speaking, only fill/stroke providers will cause these two different
				"bits" of a path to be rendered separately). This call is made BEFORE
				this Processor's ProcessPath function will be called.

				If the caller gets a TRUE back, the stroke and fill paths will be
				rendered separately.

	Notes:		Base class implementation returns FALSE. Derived Stroke and Fill
				processors should probably override this method to return TRUE.

********************************************************************************************/

BOOL PathProcessor::WillChangeFillAndStrokeSeparately(void)
{
	return(FALSE);
}



/********************************************************************************************

>	virtual void PathProcessor::ProcessPath(Path *pPath, RenderRegion *pRender) = 0;

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/12/96

	Purpose:	ABSTRACT FUNCTION - see derived classes

				Called by the RenderRegion to apply the path processing operation to 
				the given path.

	Notes:		* When rendering a path, always pass in your 'this' pointer to
				  RenderRegion::DrawPath, so that you don't start an infinite
				  recursion!

				* To stop rendering of the path, simply return without calling the RR

				* To render this path unchanged, simply call directly back to the RR:
					pRender->DrawPath(pPath, this);
				
				* Only affect the fill of this path if pPath->IsFilled

				* Only affect the stroke of this path if pPath->IsStroked

				* If converting a path into a "filled path" for stroking, the output
				  path should be rendered with IsStroked=FALSE or it'll get a line
				  around the outside!				

				* If you render any attributes, etc, then you should preserve the
				  render region state with calls to SaveContext() and RestoreContext()

********************************************************************************************/


/********************************************************************************************

>	virtual BOOL PathProcessor::DoesActuallyDoAnything(RenderRegion* pRender)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/10/2000
	Inputs:		pRender - pointer to the render region that we are about to render our path into
	Returns:	TRUE if it is anticipated that this path processor will alter the path in any
				way, FALSE if not
	Purpose:	To determine whether or not our path processor is 'default' i.e. if does not 
				change the path at all.  If so then the render region will be free to use
				DrawPathToOutputDevice which will let us use dash patterns, arrowheads etc.
	
	Errors:		

********************************************************************************************/

BOOL PathProcessor::DoesActuallyDoAnything(RenderRegion* pRender)
{
	return !m_DisableMe;
}


/********************************************************************************************

>	void PathProcessor::SetDisabled(BOOL Value)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/10/00
	Inputs:		Whether or not to disable this PPB

	Purpose:	Sets the flag which we use to determine whether or not we should do anything
				when it comes to rendering.

********************************************************************************************/

void PathProcessor::SetDisabled(BOOL Value)
{
	m_DisableMe = Value;
}


/********************************************************************************************

>	BOOL PathProcessor::IsDisabled()

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/10/00
	Inputs:		-
	Returns:	Whether or not we are disabled
	Purpose:	

********************************************************************************************/

BOOL PathProcessor::IsDisabled()
{
	return m_DisableMe;
}
