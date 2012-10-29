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

// OpImgSet - Imagesetting related Ops

#ifndef INC_OPIMGSET
#define INC_OPIMGSET

#include "colplate.h"

// The following Ops are defined in this file:
#define OPTOKEN_COMPOSITEPREVIEW	_T("CompositePreview")
#define OPTOKEN_IMAGESETTING		_T("ImagesettingSubmenu")
#define OPTOKEN_OVERPRINTFILL		_T("OverprintFill")
#define OPTOKEN_OVERPRINTLINE		_T("OverprintLine")
#define OPTOKEN_PRINTONALLPLATES	_T("PrintOnAllPlates")

#define OPTOKEN_CYANPREVIEW			_T("CyanPreview")
#define OPTOKEN_MAGENTAPREVIEW		_T("MagentaPreview")
#define OPTOKEN_YELLOWPREVIEW		_T("YellowPreview")
#define OPTOKEN_KEYPREVIEW			_T("KeyPreview")
#define OPTOKEN_MONOPLATEPREVIEW	_T("MonoPlatePreview")
#define OPTOKEN_SHOWPRINTERCOLOURS	_T("ShowPrinterColours")
#define OPTOKEN_CANCELPREVIEW		_T("CancelPreview")

#define OPTOKEN_SPOTPREVIEWBASE		_T("SpotPreview")
#define OPTOKEN_SPOTPREVIEW1		_T("SpotPreview1")
#define OPTOKEN_SPOTPREVIEW2		_T("SpotPreview2")
#define OPTOKEN_SPOTPREVIEW3		_T("SpotPreview3")
#define OPTOKEN_SPOTPREVIEW4		_T("SpotPreview4")
#define OPTOKEN_SPOTPREVIEW5		_T("SpotPreview5")
#define OPTOKEN_SPOTPREVIEW6		_T("SpotPreview6")
#define OPTOKEN_SPOTPREVIEW7		_T("SpotPreview7")
#define OPTOKEN_SPOTPREVIEW8		_T("SpotPreview8")
#define OPTOKEN_SPOTPREVIEWMORE		_T("SpotPreviewMore")

// Centralised function which inits all of the other Ops in this file
extern BOOL InitImagesettingOps(void);
void SetNewColourPlate(ColourPlateType NewType, INT32 WhichToggle, INT32 WhichSpot);
IndexedColour* FindWhichSpot(INT32 WhichSpot);


/**************************************************************************************

>	class OpToggleCompositePreview : public Operation

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/96

	Purpose:	An Op for toggling composite print preview on and off

	Notes:		This Op is available from the main "Window" menu

**************************************************************************************/

class OpShowPrinterColours : public Operation
{
	CC_DECLARE_DYNCREATE(OpShowPrinterColours)

public:
	OpShowPrinterColours() : Operation() {};

	void Do(OpDescriptor* OpDesc);

	static BOOL Init(void);
	static OpState GetState(String_256 *ShadeReason, OpDescriptor *OpDesc);
};


/**************************************************************************************

>	class OpToggleCompositePreview : public Operation

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/96

	Purpose:	An Op for toggling composite print preview on and off

	Notes:		This Op is available from the main "Window" menu

**************************************************************************************/

class OpToggleCompositePreview : public Operation
{
	CC_DECLARE_DYNCREATE(OpToggleCompositePreview)

public:
	OpToggleCompositePreview();

	void Do(OpDescriptor*);

	static BOOL Init(void);
	static OpState GetState(String_256 *ShadeReason, OpDescriptor *OpDesc);

protected:
	static BOOL CanToggleState(void);
	static BOOL IsInCompositeMode(void);
};


/**************************************************************************************

>	class OpToggleCyanPreview : public Operation

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/12/2003

	Purpose:	An Op for toggling cyan plate print preview on and off

	Notes:		This Op is available from the "Window/Show Printer Colours" submenu

**************************************************************************************/

class OpToggleCyanPreview : public Operation
{
	CC_DECLARE_DYNCREATE(OpToggleCyanPreview)

public:
	OpToggleCyanPreview() {};

	void Do(OpDescriptor*);

	static BOOL Init(void);
	static OpState GetState(String_256 *ShadeReason, OpDescriptor *OpDesc);

protected:
	static BOOL CanToggleState(void);
	static BOOL IsInCyanMode(void);
};


/**************************************************************************************

>	class OpToggleMagentaPreview : public Operation

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/12/2003

	Purpose:	An Op for toggling Magenta plate print preview on and off

	Notes:		This Op is available from the "Window/Show Printer Colours" submenu

**************************************************************************************/

class OpToggleMagentaPreview : public Operation
{
	CC_DECLARE_DYNCREATE(OpToggleMagentaPreview)

public:
	OpToggleMagentaPreview() {};

	void Do(OpDescriptor*);

	static BOOL Init(void);
	static OpState GetState(String_256 *ShadeReason, OpDescriptor *OpDesc);

protected:
	static BOOL CanToggleState(void);
	static BOOL IsInMagentaMode(void);
};


/**************************************************************************************

>	class OpToggleYellowPreview : public Operation

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/12/2003

	Purpose:	An Op for toggling Yellow plate print preview on and off

	Notes:		This Op is available from the "Window/Show Printer Colours" submenu

**************************************************************************************/

class OpToggleYellowPreview : public Operation
{
	CC_DECLARE_DYNCREATE(OpToggleYellowPreview)

public:
	OpToggleYellowPreview() {};

	void Do(OpDescriptor*);

	static BOOL Init(void);
	static OpState GetState(String_256 *ShadeReason, OpDescriptor *OpDesc);

protected:
	static BOOL CanToggleState(void);
	static BOOL IsInYellowMode(void);
};


/**************************************************************************************

>	class OpToggleKeyPreview : public Operation

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/12/2003

	Purpose:	An Op for toggling Key plate print preview on and off

	Notes:		This Op is available from the "Window/Show Printer Colours" submenu

**************************************************************************************/

class OpToggleKeyPreview : public Operation
{
	CC_DECLARE_DYNCREATE(OpToggleKeyPreview)

public:
	OpToggleKeyPreview() {};

	void Do(OpDescriptor*);

	static BOOL Init(void);
	static OpState GetState(String_256 *ShadeReason, OpDescriptor *OpDesc);

protected:
	static BOOL CanToggleState(void);
	static BOOL IsInKeyMode(void);
};


/**************************************************************************************

>	class OpToggleSpotPreview : public Operation

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/12/2003

	Purpose:	An Op for toggling Spot plate print preview on and off

	Notes:		This Op is available from the "Window/Show Printer Colours" submenu

**************************************************************************************/

class OpToggleSpotPreview : public Operation
{
	CC_DECLARE_DYNCREATE(OpToggleSpotPreview)

public:
	OpToggleSpotPreview() {};

	void Do(OpDescriptor*);

	static BOOL Init(void);
	static OpState GetState(String_256 *ShadeReason, OpDescriptor *OpDesc);

protected:
	static BOOL CanToggleState(void);
	static BOOL IsInSpotMode(void);
};


/**************************************************************************************

>	class OpToggleMonoPlatePreview : public Operation

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/12/2003

	Purpose:	An Op for toggling mono plate print preview on and off

	Notes:		This Op is available from the "Window/Show Printer Colours" submenu

**************************************************************************************/

class OpToggleMonoPlatePreview : public Operation
{
	CC_DECLARE_DYNCREATE(OpToggleMonoPlatePreview)

public:
	OpToggleMonoPlatePreview() {};

	void Do(OpDescriptor*);

	static BOOL Init(void);
	static OpState GetState(String_256 *ShadeReason, OpDescriptor *OpDesc);

protected:
	static BOOL CanToggleState(void);
	static BOOL IsInMonoMode(void);
};



/**************************************************************************************

>	class OpOverprintLine : public SelOperation

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/96

	Purpose:	An Op for toggling the AttrOverprintLine attribute

	Notes:		This Op is available from the context menu, when popped up
				over a selection. It resides in the "Imagesetting" submenu.
				See viewmenu.cpp for details.

**************************************************************************************/

class OpOverprintLine : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpOverprintLine)

public:
	OpOverprintLine();

	void Do(OpDescriptor *OpDesc);

	static BOOL Init(void);
	static OpState GetState(String_256 *ShadeReason, OpDescriptor *OpDesc);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};



/**************************************************************************************

>	class OpOverprintFill : public SelOperation

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/96

	Purpose:	An Op for toggling the AttrOverprintFill attribute

	Notes:		This Op is available from the context menu, when popped up
				over a selection. It resides in the "Imagesetting" submenu.
				See viewmenu.cpp for details.

**************************************************************************************/

class OpOverprintFill : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpOverprintFill)

public:
	OpOverprintFill();

	void Do(OpDescriptor *OpDesc);

	static BOOL Init(void);
	static OpState GetState(String_256 *ShadeReason, OpDescriptor *OpDesc);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};



/**************************************************************************************

>	class OpPrintOnAllPlates : public SelOperation

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/96

	Purpose:	An Op for toggling the AttrPrintOnAllPlates attribute

	Notes:		This Op is available from the context menu, when popped up
				over a selection. It resides in the "Imagesetting" submenu.
				See viewmenu.cpp for details.

**************************************************************************************/

class OpPrintOnAllPlates : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpPrintOnAllPlates)

public:
	OpPrintOnAllPlates();

	void Do(OpDescriptor *OpDesc);

	static BOOL Init(void);
	static OpState GetState(String_256 *ShadeReason, OpDescriptor *OpDesc);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};

#endif

