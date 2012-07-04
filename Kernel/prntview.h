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


// PrintView - subclass of DocView used for printing.

#ifndef INC_PRNTVIEW
#define INC_PRNTVIEW

//#include "view.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "oilrect.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "printctl.h"

class PrintView : public View
{
	CC_DECLARE_DYNAMIC(PrintView)

public:
	// Construction/Destruction
	PrintView(Document*);
	virtual ~PrintView();

	// Rendering
	virtual void ContinueRenderView(RenderRegion*, Spread*, BOOL = TRUE, BOOL = TRUE, BOOL bForceImmediate = FALSE);
	virtual CNativeDC *GetRenderDC();
	virtual BOOL GetForeBackMode();
	virtual void SetForeBackMode(BOOL);
	virtual void SetViewPixelSize();
	void AttachToDC(CNativeDC *pDC);
	void OnDraw(CNativeDC*, OilRect);

	// Interface to OIL view
	virtual BOOL ViewStateChanged();

	// Useful function for coping with rotating Rect objects
	static void CorrectRotatedRectangle(Rect *);

protected:
	void PrintRegion(Spread *pSpread, DocRect ClipRect, CNativeDC *pDevContext, RenderType rType);
	CNativeDC		   *PrintDC;

	// Function to build the render regions that are needed to print
	virtual void MakeNewRenderRegion(Spread *, DocRect, CNativeDC *, RenderType, BOOL PaintPaper = FALSE, Node* pInvalidNode = NULL);

public:
	Matrix ConstructRenderingMatrix(Spread *pSpread);

/////////////////////////////////////////////////////////////////////////////////////////////////
//	Scrolling, scaling and extents

public:
	virtual DocRect GetDocViewRect(Spread*);
	virtual void SetExtent(DocCoord, DocCoord);
	virtual WorkRect GetViewRect();

/////////////////////////////////////////////////////////////////////////////////////////////
// Printing layout

public:
	PrintPatchInfo PatchInfo;

	friend class ScreenView;
};


/********************************************************************************************

>	class PrintRenderCallback : public RenderCallback

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/11/2004
	Purpose:	Handling callbacks from RenderTree
	Notes:		RenderTree function calls the main function in this class when it's about
				to render any Node.

********************************************************************************************/

class PrintRenderCallback : public RenderCallback
{
public:
	PrintRenderCallback(PrintView* pPrintView) {m_pPrintView = pPrintView;}

	virtual BOOL BeforeNode(RenderRegion* pRegion, Node* pNode);

private:
	PrintView* m_pPrintView;
};


#endif  // INC_PRNTVIEW

