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


// The ScreenCamView class - subclass of ScreenView used for screen display.

#ifndef INC_SCRCAMVW
#define INC_SCRCAMVW

#include "camview.h"
//#include "draginfo.h"
//#include "dragtrgt.h"
#include "scrvw.h"

/*

class CCPrintInfo;
class PrintControl;
class OILHorizontalRuler;
class OILVerticalRuler;
class OriginGadget;
*/
class ExternalClipboard;

/********************************************************************************************

>	class ScreenCamView : public CCamView

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/01/95
	Purpose:	A subclass of CCamView which is the class actually used for screen
				display.
	SeeAlso:	CCamView; PrintCamView

********************************************************************************************/

class ScreenCamView : public ScreenView
{
////////////////////////////////////////////////////////////////////////////////
// A contained canvas to emulate MFC style views
protected:
	class ScreenCamCanvas :
		public ScreenView::ScreenCanvas
	{
	public:
		ScreenCamCanvas( wxView *v, wxMDIChildFrame *frame, const wxPoint& pos, const wxSize& size, 
			/* TYPENOTE: Correct */ long style ) : ScreenCanvas( v, frame, pos, size, style )
		{
		}
		
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Message response functions.
	protected:
		void 	OnSize( wxSizeEvent &event );

	private:
		DECLARE_EVENT_TABLE()
	};

	// Creator shim, that creates a canvas suitable for this view
	virtual CCamCanvas* CreateCanvas( wxView *v, wxMDIChildFrame *frame, const wxPoint& pos, 
		const wxSize& size, /* TYPENOTE: Correct */ long style )
	{
		return new ScreenCamCanvas( v, frame, pos, size, style );
	}
	
////////////////////////////////////////////////////////////////////////////////////////////////
// Creation and destruction.
public:
	virtual BOOL IsScreenCamView() { return TRUE; }

////////////////////////////////////////////////////////////////////////////
// OLE drag and drop
public:
PORTNOTE("other","Removed OLE usage")
#ifndef EXCLUDE_FROM_XARALX
#if (_OLE_VER >= 0x200)
	virtual DROPEFFECT OnDragEnter( COleDataObject* pDataObject, DWORD dwKeyState,
									CPoint point );
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState,
									CPoint point );
	virtual void OnDragLeave();

	virtual BOOL OnDrop(COleDataObject* pDataObject,
						DROPEFFECT dropEffect, CPoint point);
#endif

private:
#if (_OLE_VER >= 0x200)
	virtual void HandleOleDragOutOfView(CPoint point);
	COleDropTarget		m_DropTarget;		// OLE drop Target
	BOOL				m_DropFormatOK;		// Is the data format OK for dropping?
	ExternalClipboard*	m_pTempClipboard;	// Our drag and drop clipboard
	BOOL				m_ClipBoardSwapped;	// TRUE if we had to swap to the DragAndDrop clipboard
#endif
#endif
	
////////////////////////////////////////////////////////////////////////////////////////////////
// Message response functions.
protected:
    DECLARE_DYNAMIC_CLASS( ScreenCamView )
    DECLARE_EVENT_TABLE()

    bool OnCreate( wxDocument* doc, /* TYPENOTE: Correct */ long flags );
	void OnSize( wxSizeEvent& event );
};



#endif  // INC_SCRCAMVW
