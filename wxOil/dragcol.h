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


#ifndef INC_DRAGCOL
#define INC_DRAGCOL

#include "draginfo.h"

class IndexedColour;



/********************************************************************************************

>	class ColourDragInformation : public DragInformation

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com> (upgraded by Jason)
	Created:	05/05/94 (8/8/96)

	Purpose:	Contains all information about a colour being dragged.

********************************************************************************************/

class ColourDragInformation : public DragInformation
{ 	
CC_DECLARE_DYNCREATE(ColourDragInformation)

protected:
	void InitObject(void);
		// Shared construction code

public:
	ColourDragInformation();
		// Default constructor - DO NOT USE

 	ColourDragInformation(IndexedColour *Colour, BOOL IsAdjust, Document* pParent);
		// Document colour

 	ColourDragInformation(DocColour *Colour, BOOL IsAdjust, StringBase *pColourName, BOOL IsSpot);
		// Library colour

	static BOOL Init();
		// static class initialisation


public:		// Specialised interface
	BOOL IsLibraryColour(void);
			// Determine if the dragged colour is a "library" or "document" colour

	Document *GetParentDoc(void);
			// Retrieve the document colour and/or its parent document

	IndexedColour *GetColourForDocument(Document *pDestDoc = NULL);
			// Copy the dragged colour into the given document and return it ready for use
			// NULL means "copy it into the Selected doc"

	void ApplyColourToSelection(void);
			// Applies the dragged colour to the selection (in the Selected Doc)

	IndexedColour *GetInitiallyDraggedColour(void) { return(TheColour.FindParentIndexedColour()); }
			// Get the colour initially dragged - WARNING: use GetColourForDocument unless you have good reason
			// Library colours and "no colour" will return NULL


public:		// Overridden interfaces
	virtual UINT32 GetCursorID(DragTarget* pDragTarget);
	virtual BOOL GetStatusLineText(String_256 *TheText, DragTarget* pDragTarget);

	virtual UINT32 GetCursorID(void);
 	virtual BOOL GetStatusLineText(String_256 *TheText);

	virtual void OnClick(INT32 Flags, CNativePoint Point);
	
	virtual BOOL OnDrawSolidDrag(wxPoint Origin, wxDC *TheDC);
	
	virtual INT32 GetDragTransparency();


public:		// Drop on page support
	virtual BOOL CanDropOnPage()		{ return TRUE; }

	virtual BOOL OnPageDrop(ViewDragTarget* pDragTarget);


protected:
	static INT32		DragTransparency;

	DocColour		TheColour;						// Holds the colour definition (or references the document col)

	Document		*pParentDoc;					// NULL or the parent document		}	Mutually exclusive
	String_64		ColourName;						// NULL or the library colour name	}

	BOOL			LibColIsSpot;					// TRUE if this library colour is a spot colour
													// Undefined for non-library colours
};

#endif

