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

/*

	opdragbx.h

	Base-class for easy drag box operations.
*/

#ifndef OPDRAGBX_H
#define OPDRAGBX_H

//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]

enum  DragType;
enum  StockColour;
class Spread;
class DocCoord;
class DocRect;
class RenderRegion;
class ClickModifiers;


/********************************************************************************************

>	class OpDragBox : public Operation

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/95
	Purpose:	This is a base class for operations that use a drag box to select an area
				within a view, such as the selector and the zoom tools.  This class looks
				after the chore of correctly drawing and updating the xored drag box.

				To use this class derive a new operation from it and override the
				OnDragEnded function to do something useful with the drag box it is passed.
				You can	optionally also override the OnDragStarted, OnPointerMoved, or
				OnPointerIdle functions, eg. to set status text or perform intermediate
				calculations, and the SetBoxColours and CalcDragRect functions to customise
				the "look and feel" of the drag box.

				To run a drag, create an instance of your derived class and call its
				DoDrag() function, passing the mouse position etc that should be available
				in a tool.
	SeeAlso:	class OpCentredDragBox

********************************************************************************************/

class OpDragBox : public Operation
{
public:
	// This function is called on startup, and reads preferences etc.
	static BOOL Init();

	// This function initiates a drag, returning TRUE if it is successful.
	BOOL DoDrag(DragType dt,
				Spread* pStartSpread,
				const DocCoord& dcStartPos,
				ClickModifiers cmods);

protected:
	// Creation & destruction.  The constructor is only available to derived classes (it
	// makes no sense to create objects of this type, only derivatives).
	OpDragBox();

	// You can override these On... functions to do something useful (by default they do
	// nothing).  They can all return FALSE to cancel the drag.  This function is called when
	// the drag is started.
	virtual BOOL OnDragStarted(Spread* pStartSpread,
							   const DocCoord& dcStartPos,
							   ClickModifiers cmods);

	// This function is called when the pointer moves.
	virtual BOOL OnPointerMoved(Spread* pBoxSpread,
							 	const DocRect& drDragBox,
							 	ClickModifiers cmods);

	// This function is called when the pointer hasn't moved for a little while.
	virtual BOOL OnPointerIdle(Spread* pBoxSpread,
							   const DocRect& drDragBox,
							   ClickModifiers cmods);

	// This function is called when the drag finishes, and is passed the final drag box the
	// user has drawn and a drag success code.
	virtual BOOL OnDragEnded(Spread* pBoxSpread,
						   	 const DocRect& drDragBox,
						   	 ClickModifiers cmods,
						   	 BOOL fDragOK);

	// This function can be overridden to calculate the drag box in a different way, eg. for
	// a drag box that grows from a centre point to a corner, instead of the default behaviour
	// which calculates a drag box from one corner to its opposite.
	virtual DocRect CalcDragBox(const DocCoord& dcStartPos, const DocCoord& dcMousePos) const;

	// This function can be overriden to set the line colour for the drag box.  By default it
	// returns COLOUR_XORSELECT, as per user-interface guidelines for selection xor-ing.
	virtual StockColour GetBoxColour() const;

	// If you override the above CalcDragBox function so that the start position is no longer a
	// corner of the drag box, when you get the final drag box in OnDragEnded it may be
	// difficult to work out from it where the drag started, so call this which always knows.
	BOOL GetDragStartPos(Spread** ppStartSpread, DocCoord* pdcStartPos) const;

	// Miscellaneous helpers.  These may well be useful in a derived class.
	static MILLIPOINT Min(MILLIPOINT a, MILLIPOINT b);
	static MILLIPOINT Max(MILLIPOINT a, MILLIPOINT b);

private:
	// Implementation of a drag operation as defined by Operation.
	void DragPointerMove(DocCoord dcMousePos, ClickModifiers cmods, Spread* pSpread, BOOL bSolidDrag);
	void DragPointerIdle(DocCoord dcMousePos, ClickModifiers cmods, Spread* pSpread, BOOL bSolidDrag);
	void DragFinished(DocCoord dcMousePos, ClickModifiers cmods, Spread* pSpread, BOOL fOK, BOOL bSolidDrag);
	void RenderDragBlobs(DocRect drClipRect, Spread* pRenderSpread, BOOL bSolidDrag);

	// These functions erase the old drag box and draw the new one.
	void UpdateSolidDragBox(const DocRect& drNewDragBox);
	void UpdateUnfilledDragBox(const DocRect& drNewDragBox);
	
	// This function draws a render-on-top xored rectangle at the given spread coordinates.
	void DrawXorRect(const DocRect& drClip,	Spread* pspdXor, const DocRect& drXor) const;

	// Data members.
	Spread*	 m_pStartSpread;				// the spread where the drag started
	DocCoord m_dcStartPos;					// the point where the drag started
	DocRect	 m_drLastDragBox;				// the last extent of the drag box

	// Preferences.
	static BOOL m_fDoSolidDragBoxes;		// whether to do solid xored drag boxes or just
											// unfilled rectangles.
	
	CC_DECLARE_DYNCREATE(OpDragBox);
};



/********************************************************************************************

>	class OpCentredDragBox : public OpDragBox

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/4/95
	Purpose:	This is a base class for drag operations that would like a drag box to be
				centred on the initial click point, such as (optionally) the zoom tool.
				Apart from providing a new default CalcDragBox function, it is used the
				same way as OpDragBox.
	SeeAlso:	class OpDragBox

********************************************************************************************/

class OpCentredDragBox : public OpDragBox
{
protected:
	// Creation & destruction.
	OpCentredDragBox();

	// Overridables.
	virtual DocRect CalcDragBox(const DocCoord& dcStartPos, const DocCoord& dcMousePos) const;

private:	
	CC_DECLARE_DYNCREATE(OpCentredDragBox);
};

#endif	// !OPDRAGBX_H
