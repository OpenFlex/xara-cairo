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

// Encapsulate the kernel'ly bits of the rulers


#ifndef INC_RULERS
#define INC_RULERS

#include "oilruler.h"
#include "userrect.h"
#include "contmenu.h"

class RulerPair;
class DocView;
class NodeRenderableInk;

// WEBSTER - markn 15/1/97
// No rulers in Webster, same as RALPH
#ifndef WEBSTER
#if !defined(EXCLUDE_FROM_RALPH)

/********************************************************************************************
>	class RulerBase : public CCObject

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/8/95
	Purpose:	Common base class for a ruler (X and Y derived)
********************************************************************************************/

class RulerBase : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(RulerBase);

public:
	RulerBase();
	virtual ~RulerBase() {} // suppress warnings

	RulerPair* GetpRulerPair() { return pRulerPair; }
	OILRuler*  GetpOILRuler()  { return pOILRuler; }

	virtual MILLIPOINT    GetOrd(const UserCoord& coord) = 0;
	virtual UserCoord  MakeCoord(const MILLIPOINT ord)   = 0;
	virtual BOOL    IsHorizontal()                       = 0;

	/////////////////////
	// OilRuler interface

	// Called by the OIL ruler when the ruler needs to be redrawn.
	// We do all the platform independent computations and call the
	// OIL ruler back to render specific things (e.g., graticules)
	BOOL Redraw(OilRect* pOilRect);
	virtual BOOL GetStatusLineText(String_256* pText, OilCoord PointerPos);
	virtual BOOL OnRulerClick(OilCoord, ClickType, ClickModifiers);

	/////////////////
	// Tool interface
	
	// For use by tools that wish to render extra things on the ruler
	// (by responding to the RenderRulerBlobs method)
	BOOL HighlightSection(MILLIPOINT ord_lo, MILLIPOINT ord_hi);
	BOOL DrawBitmap(MILLIPOINT ord, ResourceID BitmapID);
	// Allow tools to start a drag after receiving an OnRulerClick call.
	// Drag events will be dispatched via OnRulerClick.
	BOOL StartToolDrag(ClickModifiers Mods, UserCoord, String_256* pOpToken, OpParam* pParam);

protected:
	UserCoord OilToToolCoords(OilCoord PointerPos, Spread* pSpread);
	RulerPair* pRulerPair;
	OILRuler*  pOILRuler;
};


/********************************************************************************************
>	class HorizontalRuler : public RulerBase

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/8/95
	Purpose:	Encapsulates horizontal ruler
********************************************************************************************/

class HorizontalRuler : public RulerBase
{
	CC_DECLARE_MEMDUMP(HorizontalRuler);

public:
	HorizontalRuler();
	BOOL Init(RulerPair* pRulers, OILHorizontalRuler* pOILHRuler);

	virtual MILLIPOINT    GetOrd(const UserCoord& coord) { return coord.x; }
	virtual UserCoord  MakeCoord(const MILLIPOINT ord)   { return UserCoord(ord,0); }
	virtual BOOL    IsHorizontal() { return TRUE; }
};


/********************************************************************************************
>	class VerticalRuler : public RulerBase

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/8/95
	Purpose:	Encapsulates vertical ruler
********************************************************************************************/

class VerticalRuler : public RulerBase
{
	CC_DECLARE_MEMDUMP(VerticalRuler);

public:
	VerticalRuler();
	BOOL Init(RulerPair* pRulers, OILVerticalRuler* pOILVRuler);

	virtual MILLIPOINT    GetOrd(const UserCoord& coord) { return coord.y; }
	virtual UserCoord  MakeCoord(const MILLIPOINT ord)   { return UserCoord(0,ord); }
	virtual BOOL    IsHorizontal() { return FALSE; }
};


/********************************************************************************************
>	struct RulerRedrawData

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/9/95
	Purpose:	structure containing semi-permenent redraw data
********************************************************************************************/

struct RulerRedrawData
{
	UserRect   PasteBoardUserRect;
	INT32       GratStep;
	double     GratStepSize;
	INT32       MinorGrats;
	double     MinorGratStepSize;
	double     GratUnitSize;
	double     ScaleFactor;
	String_32  LegendStr;
};


/********************************************************************************************
>	class RulerPair : public MessageHandler

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/8/95
	Purpose:	Encapsulates a horizontal and vertical ruler pair
********************************************************************************************/

class RulerPair : public MessageHandler
{
	CC_DECLARE_MEMDUMP(RulerPair);

public:
	RulerPair();
	BOOL Init(DocView* pDView, OILHorizontalRuler* pOILHRuler, OILVerticalRuler* pOILVRuler,
			  OriginGadget* pOGadget);

	MsgResult Message(Msg* Msg);
	BOOL      GetStatusLineText(String_256* pText, WinCoord MousePos, CWindowID hWnd);
	BOOL      Update();
	BOOL      UpdateRedrawData();

	BOOL     UpdateMouseFollowers(DocCoord* pDocCoord);
	BOOL     GetMouseFollowerVisibility() { return MouseFollowerVisibility; }
	DocCoord GetMouseFollowerPosition()   { return MouseFollowerPosition; }

	DocView*         GetpDocView()         { return pDocView; }
	Spread*          GetpSpread()          { return pSpread; }
	OriginGadget*    GetpOriginGadget()    { return pOriginGadget; }
	HorizontalRuler* GetpHorizontalRuler() { return &HRuler; }
	VerticalRuler*   GetpVerticalRuler()   { return &VRuler; }
	RulerRedrawData* GetpRedrawData()      { return &RedrawData; }

protected:
	DocView*        pDocView;
	Spread*         pSpread;
	OriginGadget*   pOriginGadget;
	HorizontalRuler HRuler;
	VerticalRuler   VRuler;
	RulerRedrawData RedrawData;

	BOOL     MouseFollowerVisibility;
	DocCoord MouseFollowerPosition;
};


/******************************************************************************
>	class RulerContextMenu : public ContextMenu

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/10/95
	Purpose:	Implements the Ruler context sensitive menu
******************************************************************************/

class RulerContextMenu : public ContextMenu
{
	CC_DECLARE_MEMDUMP(RulerContextMenu);

public:
	virtual BOOL Build();
};


/******************************************************************************
>	class OriginContextMenu : public ContextMenu

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/10/95
	Purpose:	Implements the Ruler context sensitive menu
******************************************************************************/

class OriginContextMenu : public ContextMenu
{
	CC_DECLARE_MEMDUMP(OriginContextMenu);

public:
	virtual BOOL Build();
};
#endif
#endif  // WEBSTER
#endif  // INC_RULERS
