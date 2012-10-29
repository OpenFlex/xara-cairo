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


// draginfo.cpp - Definitions for global dragging system DragInformation class

/*
*/

#include "camtypes.h"

#include "draginfo.h"
#include "dragmsg.h"
//#include "resource.h"
//#include "mario.h"

CC_IMPLEMENT_DYNAMIC(DragMessage, Msg)
CC_IMPLEMENT_DYNCREATE(DragInformation, CCObject)

#define new CAM_DEBUG_NEW

Cursor * DragInformation::MyCursor = NULL;	


/********************************************************************************************

>	DragInformation::DragInformation(BOOL AdjuatDrag)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/1/95

	Purpose: default constructor

	Documentation:	Docs\Specs\DragMan.doc

********************************************************************************************/


DragInformation::DragInformation(BOOL AdjustDrag)
{
	// default no solid drag
	DoesSolidDrag = FALSE;
	IsAdjustDrag = AdjustDrag;
	SolidDragOffset.x = SolidDragOffset.y = 0;
	SolidDragSize.x = SolidDragSize.y = 0;
}

/********************************************************************************************

>	virtual BOOL DragInformation::OnClick(INT32 Flags, CNativePoint Point)

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/1/95
	Returns:	-
	Inputs :	Flags state of mouse 1 = left click
									 2 = right click
				Point Screen Coord of mouse Click
	Purpose:	this can be overridden to provide click functionality if the drag didn't
				materialise
   
********************************************************************************************/

void DragInformation::OnClick(INT32 Flags, CNativePoint Point)
{
	// do nothing in the base function
}


/********************************************************************************************

>	virtual UINT32 DragInformation::GetCursorID()

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/1/95
	Returns:	a cursor ID to set during this drag
	Purpose:	-
   
********************************************************************************************/

UINT32 DragInformation::GetCursorID()
{
	 return _R(IDC_DRAGGING) ;
}

/********************************************************************************************

>	virtual BOOL DragInformation::GetStatusLineText(String_256 * TheText)
	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/1/95
	Returns:	Whether string is valid
	Purpose:	provide status line text for this drag
   
********************************************************************************************/
BOOL DragInformation::GetStatusLineText(String_256 * TheText)
{
	ERROR2IF(TheText==NULL,FALSE,"NULL string in GetStatusLineText()");
 	* TheText = String_256(_R(IDS_DRAGSTATUSLINETEXT));
	return TRUE;
}

/********************************************************************************************

>	virtual UINT32 DragInformation::DrawSolidDrag()

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/1/95
	Returns:	-
	Purpose:	-
   
********************************************************************************************/

BOOL DragInformation::OnDrawSolidDrag(CNativePoint Origin,CNativeDC * TheDC)
{
  return FALSE;
}



/********************************************************************************************

>	virtual UINT32 DragInformation::GetCursorID(DragTarget* pDragTarget)

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/1/95
	Returns:	a cursor ID to set during this drag
	Purpose:	-
   
********************************************************************************************/

UINT32 DragInformation::GetCursorID(DragTarget* pDragTarget)
{
	 return _R(IDC_DRAGGING) ;
}

/********************************************************************************************

>	virtual BOOL DragInformation::GetStatusLineText(String_256 * TheText, DragTarget* pDragTarget)
	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/1/95
	Returns:	Whether string is valid
	Purpose:	provide status line text for this drag
   
********************************************************************************************/
BOOL DragInformation::GetStatusLineText(String_256 * TheText, DragTarget* pDragTarget)
{
	ERROR2IF(TheText==NULL,FALSE,"NULL string in GetStatusLineText()");
 	* TheText = String_256(_R(IDS_DRAGSTATUSLINETEXT));
	return TRUE;
}

/********************************************************************************************

>	virtual UINT32 DragInformation::DrawSolidDrag(CPoint Origin,CDC * TheDC, DragTarget* pDragTarget)

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/1/95
	Returns:	-
	Purpose:	-
   
********************************************************************************************/

BOOL DragInformation::OnDrawSolidDrag(CNativePoint Origin,CNativeDC * TheDC, DragTarget* pDragTarget)
{
  return FALSE;
}
