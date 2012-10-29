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

// DragCol.cpp - Colour DragInformation base class

/*
*/


#include "camtypes.h"

#include "ccolbar.h"
#include "coldlog.h"
#include "colourix.h"
#include "colormgr.h"
#include "devcolor.h"
#include "dragpick.h"
#include "dragmgr.h"
#include "keypress.h"
#include "camframe.h"
//#include "resource.h"
#include "sgcolour.h"
#include "camview.h"
#include "lineattr.h"

#include "palman.h"

#include "backgrnd.h"	// OpBackground
#include "keypress.h"	// KeyPress
//#include "galstr.h"		// _R(IDS_DRAGCOL_DROP_SETPAGEBACKGROUND)

CC_IMPLEMENT_DYNCREATE(ColourPickerDragInformation, DragInformation)



const INT32 CellSize = 16;		// X/Y size of the solid-dragged colour square



// Default to non-transparent dragging
INT32 ColourPickerDragInformation::DragTransparency = 0;



/********************************************************************************************

>	void ColourPickerDragInformation::InitObject(void)
	 
	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	30/05/2006

	Purpose:	Shared code for initialising the object - called by all constructors

********************************************************************************************/

void ColourPickerDragInformation::InitObject(void)
{
	// Init member variables
	TheColour = DocColour(COLOUR_TRANS);
	m_Status=NO_COLOUR;

	// Set up a few things about this drag
	DoesSolidDrag = TRUE;
	
	// offset of colour swatch from the pointer
	SolidDragOffset.x = 14;
	SolidDragOffset.y = 4;	   
	
	// size of the solid drag redraw
	SolidDragSize.x = CellSize;
	SolidDragSize.y = CellSize;
}



/********************************************************************************************

>	void ColourPickerDragInformation::ColourPickerDragInformation() 
	 
	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/1/95		  

	Purpose:	Constructor

********************************************************************************************/

ColourPickerDragInformation::ColourPickerDragInformation()
{
	InitObject();
}


/********************************************************************************************

>	static BOOL ColourPickerDragInformation::Init()

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	30/05/2006
	Returns:	-
	Purpose:	Initialise any Colour Drag stuff. (eg. ini file preferences).
	SeeAlso:	-

********************************************************************************************/

BOOL ColourPickerDragInformation::Init()
{
	// Setup preference for drag transparency
	if (GetApplication()->DeclareSection(_T("Dragging"), 1))
		GetApplication()->DeclarePref( NULL, _T("ColourPickerDragTransparency"), &DragTransparency, 0, 100);

	return TRUE;
}




/********************************************************************************************

>	void ColourPickerDragInformation::GetCursorID(DragTarget* pDragTarget)

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/3/95
	Purpose:	Set cursor over this target


********************************************************************************************/

UINT32 ColourPickerDragInformation::GetCursorID(DragTarget* pDragTarget)
{
	return GetCursorID();
}



/********************************************************************************************

>	virtual BOOL ColourPickerDragInformation::GetStatusLineText(String_256 * TheText, DragTarget* pDragTarget)

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	30/05/2006
	Returns:	Whether String is valid
	Purpose:	provide status line text for this target
   
********************************************************************************************/

BOOL ColourPickerDragInformation::GetStatusLineText(String_256 * TheText, DragTarget* pDragTarget)
{
	return GetStatusLineText(TheText);
}


/********************************************************************************************

>	virtual UINT32 ColourPickerDragInformation::GetCursorID()

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/1/95
	Returns:	a cursor ID to set during this drag
	Purpose:	Determines what cursor to display during a colour drag
   
********************************************************************************************/

UINT32 ColourPickerDragInformation::GetCursorID()
{
	switch (m_Status)
	{
		case DOC_COLOUR:
			return _R(IDC_COLOURPICKERCURSORDOC);
		case SCREEN_COLOUR:
			return _R(IDC_COLOURPICKERCURSOR);
		case COLOURBAR_COLOUR:
			return _R(IDC_COLOURPICKERCURSORCOLBAR);
		default:
			break;
	}

	return(_R(IDC_COLOURPICKERCURSORNOREAD));
}



/********************************************************************************************

>	virtual BOOL ColourPickerDragInformation::GetStatusLineText(String_256 * TheText)

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	30/05/2006

	Outputs:	TheText - If it returns TRUE, this is filled in with status line text
	Returns:	Whether String is valid

	Purpose:	provide status line text for this drag
   
********************************************************************************************/

BOOL ColourPickerDragInformation::GetStatusLineText(String_256 *TheText)
{
	ResourceID r;
	switch (m_Status)
	{
		case DOC_COLOUR:
			r = _R(IDS_DRAGGINGCOLOURPICKERTOOLDOCRC);
			break;
		case SCREEN_COLOUR:
			r = _R(IDS_DRAGGINGCOLOURPICKERTOOLRS);
			break;
		case COLOURBAR_COLOUR:
			r = _R(IDS_DRAGGINGCOLOURPICKERTOOLCOLOURBARRC);
			break;
		default:
			r = _R(IDS_DRAGGINGCOLOURPICKERTOOLNOREAD);
	}

	*TheText=String_256(r);
	return TRUE;
}




/********************************************************************************************

>	void ColourPickerDragInformation::OnDrawSolidDrag(CRect DragRect,CDC * TheDC) 
	 
	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	30/05/2006
	Inputs:		TheDC - pointer to a DC ready to draw into.
	Outputs:	-
	Returns:	-
	Purpose:	allows the drag to draw into a Device Context - DragManager will look after
				painting the background	etc.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL ColourPickerDragInformation::OnDrawSolidDrag(wxPoint Origin, wxDC *TheDC)
{
	if (m_Status == NO_COLOUR)
		return FALSE;	

	// set up gbrush
//	CPalette * OldPal = NULL;
//	if (PaletteManager::UsePalette())
//	{
//		OldPal = PaletteManager::StartPaintPalette( TheDC );
//	}

	GBrush GDrawBrush;
	GDrawBrush.Init(TheDC);
	GDrawBrush.Start();

	// get a gbrush brush
	Document *ScopeDoc = Document::GetSelected();
	ERROR2IF(ScopeDoc == NULL, FALSE, "No Selected Doc !");

	wxBrush* pDragBrush = new wxBrush;
	
	BOOL BrushCreate = TRUE;

	if (pDragBrush != NULL )
	{
		if (TheColour.IsTransparent())
		{
//			TheDC->SetBkColor(RGB(255,255,255));		// ensure white background
			pDragBrush->SetStyle(wxCROSSDIAG_HATCH);
			pDragBrush->SetColour(wxColour(0,0,0));		// Fill with black/white cross hatch
		}
		else
		{
			DWORD ScreenWord;

			ColourContextRGBT *CCrgbt = (ColourContextRGBT *)
						ColourManager::GetColourContext(COLOURMODEL_RGBT, DocView::GetSelected());
			ScreenWord = ConvertColourToScreenWord(CCrgbt, &TheColour);

			// create the Brush and	Pen
			if (GDrawBrush.Available())
			{
				GDrawBrush.GetLogBrush((COLORREF)ScreenWord, pDragBrush);
			}
			else
				pDragBrush->SetColour((COLORREF)ScreenWord);
		}

		wxPen MyPen(wxColour(0,0,0));

		// Set the brush origin so the dither (or Hatch) patterns
		// don't move around as you drag.
//		TheDC->SetBrushOrg(Origin.x, Origin.y);
		
		//the rectangle to draw into
		wxRect DrawRect(Origin.x, Origin.y, SolidDragSize.x-1, SolidDragSize.y-1);

		// select brushes and pens ..
		TheDC->SetBrush(*pDragBrush);
		TheDC->SetPen(MyPen);

		// draw the thingy. In this case, it's a colour patch, circular for a spot colour, else a square
#ifndef WEBSTER // don't distinguish spots in Webster Martin 15/07/97
		if (!TheColour.IsTransparent() && TheColour.GetSpotParent() != NULL)
 			TheDC->DrawEllipse(DrawRect);
 		else
#endif // WEBSTER
 			TheDC->DrawRectangle(DrawRect);
		    						
    	// clean up the dc
    	TheDC->SetBrush(wxNullBrush);
		TheDC->SetPen(wxNullPen);

    	// delete the objects
		delete pDragBrush;
	}
	else
		BrushCreate = FALSE;
	
	// Finish with GBrush
	GDrawBrush.Stop();
//	if (OldPal)
//		PaletteManager::StopPaintPalette(TheDC, OldPal);
	
	// problems !!!
	ERROR2IF(!BrushCreate, FALSE, "Failed to make a solid drag brush!");

	return TRUE;
}



/********************************************************************************************

>	virtual INT32 ColourPickerDragInformation::GetDragTransparency()
 
	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	30/05/2006
	Returns:	-
	Purpose:	Specifies how transparent a drag should be.
				A value of 0, will cause a normal solid blit.
				Any other value (between 0 and 100), will cause a masked blit.
	SeeAlso:	-

********************************************************************************************/

INT32 ColourPickerDragInformation::GetDragTransparency()
{
	return ColourPickerDragInformation::DragTransparency;
}


/********************************************************************************************

>	virtual BOOL ColourPickerDragInformation::OnMouseMove(wxPoint p)
 
	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	30/05/2006
	Returns:	-
	Purpose:	Called on a mouse move. Find the doc colour under point p
	SeeAlso:	-

********************************************************************************************/

BOOL ColourPickerDragInformation::OnMouseMove(wxPoint p)
{
	Status OldStatus = m_Status;
	m_Status = SCREEN_COLOUR;
	DocColour col(COLOUR_TRANS);

	CWindowID	WinID=::wxChildWindowFromPoint(p, FALSE, -1);
	DocView*	pDocView=NULL;
	Spread*		pSpread=NULL;
	WinCoord	WndPos(0,0);
	DocCoord	DocPos(0,0);

	ColourEditDlg* pColourEditDlg = ColourEditDlg::GetColourEditDlg ();
	// Check we can't pick from the colour picker
	wxWindow * w = WinID;
	while (w)
	{
		if (pColourEditDlg && (w==pColourEditDlg->WindowID))
		{
			// No picking colours from the colour editor
			m_Status = NO_COLOUR;
			break;
		}
		if (w->IsKindOf(CLASSINFO(CColourBar)))
		{
			wxPoint cpoint = w->ScreenToClient(p);
			if (((CColourBar*) w)->IsColourPickerOverStripRect (w, cpoint))
			{
				IndexedColour * pIndexedColour = NULL;
				m_Status = COLOURBAR_COLOUR;
				((CColourBar*) w)->DoColourPickerColour (w, cpoint, &pIndexedColour);
				if (pIndexedColour)
				{
					// Disassociate from indexed colour
					DocColour Temp;
					Temp.MakeRefToIndexedColour(pIndexedColour);
					INT32 r, g, b;
					Temp.GetRGBValue(&r, &g, &b);
					col = DocColour(r, g, b);
				}
				break;
			}
		}
		w=w->GetParent();
	}

	Pixel32bpp Pix;
	NodeRenderableInk* pNode = NULL;

	if (m_Status == SCREEN_COLOUR)
	{
		if (WinID != NULL)
			pDocView=CCamView::GetDocViewFromWindowID(WinID);
	
		if (pDocView != NULL)
		{
			OilCoord OilPos = WndPos.ToOil(pDocView, TRUE);
			pSpread = pDocView->OilToSpreadCoord(OilPos, &DocPos);
		}
	
		if (pDocView)		// were over an active (or inactive document)
		{
			if (pDocView==DocView::GetSelected())
			{
				pNode = NodeRenderableInk::FindSimpleAtPointForColourPicker (pSpread, DocPos, Pix);
				m_Status = DOC_COLOUR;
			}
			else
			{	
				m_Status = SCREEN_COLOUR;
			}
		}
	}

	switch (m_Status)
	{
		case DOC_COLOUR:
		{
			const double conversion = 1.0/255.0;
							
			FIXED24 rValF24 = Pix.Red * conversion;
			FIXED24 gValF24 = Pix.Green * conversion;
			FIXED24 bValF24 = Pix.Blue * conversion;
			FIXED24 tValF24 = Pix.Alpha * conversion;
			
			//DocColour* TheColour = new DocColour (rValF24, gValF24, bValF24);
			ColourRGBT TheColourRGBT;
			TheColourRGBT.Red = rValF24;
			TheColourRGBT.Green = gValF24;
			TheColourRGBT.Blue = bValF24;
			TheColourRGBT.Transparent = tValF24;
			col = DOCCOLOUR_RGBT(&TheColourRGBT);//DocColour (rValF24, gValF24, bValF24);
		}

		case SCREEN_COLOUR:
		{
			wxColour c(*wxBLACK);
			ScreenDC.GetPixel(p, &c);

			const double conversion = 1.0/255.0;

			FIXED24 rValF24 = c.Red() * conversion;
			FIXED24 gValF24 = c.Green() * conversion;
			FIXED24 bValF24 = c.Blue() * conversion;

			col=DocColour(rValF24, gValF24, bValF24);
		}

		case COLOURBAR_COLOUR:
		default:
			break;

	}

	if ((OldStatus != m_Status ) || (col !=TheColour))
	{
		TheColour = col;

		// COLOURBAR_COLOUR has already updated the colour picker
		if ((m_Status != NO_COLOUR) && (m_Status != COLOURBAR_COLOUR))
		{
			IndexedColour* theIndexedColour = ColourManager::GenerateNewUnnamedColour (ColourManager::GetColourList(), &TheColour);
	
			// Tell the colour edit dlg about the node that this colour came
			// from so it can block attribute application if its the same node
			if (pColourEditDlg && theIndexedColour)
				pColourEditDlg->SetEditingColour (theIndexedColour, pNode);
			//pColourEditDlg->SetEditingColour (theIndexedColour);
		}

	}

	return TRUE;
}
