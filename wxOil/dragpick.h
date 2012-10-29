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

// DragCol.h - Colour DragInformation base class


#ifndef INC_DRAGPICK
#define INC_DRAGPICK

#include "draginfo.h"

class IndexedColour;



/********************************************************************************************

>	class ColourPickerDragInformation : public DragInformation

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com> (upgraded by Jason)
	Created:	05/05/94 (8/8/96)

	Purpose:	Contains all information about a colour being dragged.

********************************************************************************************/

class ColourPickerDragInformation : public DragInformation
{ 	
CC_DECLARE_DYNCREATE(ColourPickerDragInformation)

protected:
	void InitObject(void);
		// Shared construction code

public:
	ColourPickerDragInformation();
		// Default constructor - DO NOT USE

	static BOOL Init();
		// static class initialisation


public:		// Specialised interface

public:		// Overridden interfaces
	virtual UINT32 GetCursorID(DragTarget* pDragTarget);
	virtual BOOL GetStatusLineText(String_256 *TheText, DragTarget* pDragTarget);

	virtual UINT32 GetCursorID(void);
 	virtual BOOL GetStatusLineText(String_256 *TheText);

	virtual BOOL OnDrawSolidDrag(wxPoint Origin, wxDC *TheDC);
	
	virtual INT32 GetDragTransparency();

	virtual BOOL OnMouseMove(wxPoint p);

protected:
	static INT32		DragTransparency;

	DocColour TheColour;	// Holds the colour definition (or references the document col)

	enum Status
	{
		NO_COLOUR,
		SCREEN_COLOUR,
		DOC_COLOUR,
		COLOURBAR_COLOUR
	};

	Status m_Status;

	wxScreenDC ScreenDC;

};

#endif

