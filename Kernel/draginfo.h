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


// draginfo.h - Definitions for global dragging system DragInformation class

#ifndef INC_DRAGINFO
#define INC_DRAGINFO

class Cursor;
class DragTarget;
class ViewDragTarget;
class KernelBitmap;

/*********************************************************************************************

>	class DragInformation : public CCObject

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/1/95
	Purpose:	Objects derived from this abstract class are used to describe everything
				useful to know about the current global drag. They allow drag targets to
				decide what to do with a recieved drag.

	SeeAlso:	DragManagerOp::StartDrag; DragTarget

	Documentation:	Docs\Specs\DragMan.doc

*********************************************************************************************/

class CCAPI DragInformation : public CCObject
{
	friend class DragManagerOp;
	friend class CaptureHandler;

	CC_DECLARE_DYNCREATE(DragInformation)

	
protected:
	DragInformation(BOOL IsAdjustDrag = FALSE);


public:
	virtual void OnClick(INT32 flags, CNativePoint Point);	

	virtual UINT32 GetCursorID();
	virtual BOOL GetStatusLineText(String_256 * TheText);
	virtual BOOL OnDrawSolidDrag(CNativePoint Origin, CNativeDC * TheDC);

	virtual UINT32 GetCursorID(DragTarget* pDragTarget);
	virtual BOOL GetStatusLineText(String_256 * TheText, DragTarget* pDragTarget);
	virtual BOOL OnDrawSolidDrag(CNativePoint Origin, CNativeDC * TheDC, DragTarget* pDragTarget);

	BOOL IsAnAdjustDrag()						{ return IsAdjustDrag; }

public:		// Solid-dragging support
	virtual INT32 GetDragTransparency()			{ return 0; }		// Not transparent
	virtual KernelBitmap *GetSolidDragMask()	{ return NULL; }	// Not masked
	virtual BOOL HasTransparentMask()			{ return FALSE; }
	virtual wxBitmap * GetTransparentMask()		{ return NULL; }

public:		// Special dropping functions called for drop-on-page (called by ViewDragTarget)
	virtual BOOL CanDropOnPage()				{ return FALSE; }
	virtual BOOL OnPageDrop(ViewDragTarget*)	{ return FALSE; }
	virtual BOOL OnMouseMove(wxPoint p)			{ return FALSE; }
	virtual BOOL OnButtonUp(wxPoint p)			{ return FALSE; }

protected:	// Member variables
	static Cursor	   *MyCursor;

	BOOL				DoesSolidDrag;
	CNativePoint		SolidDragOffset;
	CNativeSize			SolidDragSize;

	BOOL				IsAdjustDrag;
};

#endif

