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


#include "camtypes.h"
#include "dragtool.h"
#include "toollist.h"
#include "selector.h"


// Run-time type checking etc etc
CC_IMPLEMENT_MEMDUMP(DragTool, Tool_v1)

// report memory line info
#define new	 CAM_DEBUG_NEW

// These are still char* while we wait for resource technology to be developed for modules
TCHAR* DragTool::FamilyName = _T("Drag Tools");
TCHAR* DragTool::ToolName   = _T("Drag Tool");
TCHAR* DragTool::Purpose    = _T("The parent tool of Selector and Slice tools");
TCHAR* DragTool::Author     = _T("Karim MacDonald");

/********************************************************************************************

>	virtual void DragTool::DragMove(TransformBoundingData* pBoundingData)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/10/1999
	Purpose:	Placeholder for base-class implementations.
				Does nothing here.

********************************************************************************************/
void DragTool::DragMove(TransformBoundingData* pBoundingData)
{
	// empty.
}



/********************************************************************************************

>	virtual BOOL DragTool::BeyondFixedRange(double fpFixedVal)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com> from JustinF's SelectorTool::BeyondFixedRange code.
	Created:	14/10/1999
	Inputs:		fpFixedVal		the double that is to be converted to fixed-point
	Returns:	TRUE if the number is beyond the range that fixed-piont numbers can
				represent, FALSE if its OK to convert.
	Purpose:	Checks for under/overflow in fixed-point calculations.

				This function hails from SelectorTool::BeyondFixedRange.
				The reason it is here is that it needs to be called from
				a pointer to a DragTool, without going through everyone
				elses code and re-casting their pointer to SelectorTool*.
				Because it is a small function, it is implemented here, as well as
				in SelectorTool.

********************************************************************************************/
BOOL DragTool::BeyondFixedRange(double fpFixedVal)
{
	const double fpMinFixPt = 1.0 / (INT32(SHRT_MAX) + 1);		// 1/32768
	const double fpMaxFixPt = SHRT_MAX;							// 32767
	double fp = fabs(fpFixedVal);
	return fp < fpMinFixPt || fp > fpMaxFixPt;
}

/********************************************************************************************

>	virtual void DragTool::OnClick(DocCoord PointerPos, ClickType cType, ClickModifiers cMods, Spread* pSpread)

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/7/2000
	Inputs:		standard things
	Returns:	-
	Purpose:	Call this function (for derived classes) when you don't want to process the
				message yourself (or you don't want to handle it).  This function locates the
				selector tool - and allows it to handle the message.

********************************************************************************************/

void DragTool::OnClick(DocCoord PointerPos, ClickType cType, ClickModifiers cMods, Spread* pSpread)
{
	if ((cType == CLICKTYPE_SINGLE) || (cType == CLICKTYPE_UP))
	{	
		ToolListItem* pSelectorItem = Tool::Find(TOOLID_SELECTOR);
		ERROR3IF(pSelectorItem == NULL, "ARGH! No Selector when we got a click!");
		ERROR3IF(pSelectorItem->m_pTool == NULL, "ARGH! No Selector when we got a click!");
		Tool* pSelector = pSelectorItem->m_pTool;

		if (pSelector)
		{	
			SelectorTool::AllowGuidelineScan (FALSE);
			pSelector->OnClick(PointerPos, cType, cMods, pSpread);
			SelectorTool::AllowGuidelineScan (TRUE);
		}
	}
}
