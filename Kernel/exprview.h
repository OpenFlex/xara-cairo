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


// Express View that renders non-stop

#ifndef INC_EXPRVIEW
#define INC_EXPRVIEW

//#include "view.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "oilrect.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class CDC;
class OILBitmap;
class GRenderBitmap;

typedef INT32	BPP;

/**************************************************************************************

>	class ExpressView : public View

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/09/96
	Purpose:	Renders the current document into the device context given in OnDraw()
				This is primarily used for embedding documents.

**************************************************************************************/
class ExpressView : public View
{
	CC_DECLARE_DYNAMIC(ExpressView)

public:
	// Construction/Destruction
	ExpressView(Document*);
	BOOL	Init();

	virtual ~ExpressView();

	// Pure implementation
	virtual BOOL	ViewStateChanged();

	virtual void	SetViewPixelSize();

	virtual void	ContinueRenderView(RenderRegion*, Spread*, BOOL = TRUE, BOOL = TRUE, BOOL bForceImmediate = FALSE);
	virtual CDC*	GetRenderDC();

	virtual BOOL	GetForeBackMode();
	virtual void	SetForeBackMode(BOOL);

	// These are what you want
	BOOL	DoRender(CDC* pDC, DocRect drClip, const DocRect& BitmapSize, BPP Bpp);
	OILBitmap* GetBitmap() const;

/////////////////////////////////////////////////////////////////////////////////////////////////
//	Scrolling, scaling and extents

public:
	// Pure implementations
	virtual DocRect		GetDocViewRect(Spread*);
	virtual void		SetExtent(DocCoord, DocCoord);
	virtual WorkRect	GetViewRect();

protected:
	FIXED16	m_XScale;
	FIXED16	m_YScale;
	Matrix	m_ScaleMatrix;

	GRenderBitmap*	m_pBitmapRegion;

	CDC*		m_pCDC;
	BPP			m_Bpp;
	OILBitmap*	m_pBitmap;

protected:
	// Support functions
	virtual Matrix ConstructRenderingMatrix(Spread *pSpread);
	// Function to build the render regions that are needed to print
	virtual void MakeNewRenderRegion(Spread *, DocRect, CDC *, RenderType, BOOL PaintPaper = FALSE, Node* pInvalidNode = NULL);
};



/**************************************************************************************

>	class Selection : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/09/96
	Purpose:	Provides manipulation for selections of objects

**************************************************************************************/
/*
class Selection : public CC_CLASS_MEMDUMP
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(Selection);

public:
	virtual DocRect GetBounds();
};


class WholeSelection : public Selection
{
	virtual DocRect GetBounds();
};
*/
#endif  // INC_EXPRVIEW
