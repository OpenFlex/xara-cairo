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


#ifndef INC_DRAWCTL
#define	INC_DRAWCTL

#include "ctrllist.h"

enum wxCamDrawControlStyle
{
	// Caching flags start here - the art provider may have a different bitmap depending on the
	// state of these flags...

	wxCDCS_DEFAULT			= 0,
	wxCDCS_SETCLIPRECT		= 1<<0
};

/*******************************************************************************************

>	class wxCamDrawControlEvent : public wxEvent

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	19/12/2005
	Purpose:	A derived event to allow for postprocessing of autorepeat on buttons
	Notes:		In the OIL
	See Also:	

********************************************************************************************/

class wxCamDrawControlEvent : public wxEvent
{
public:
	// Aargh note wxEvent's constructor has paramaters the otherway around from this - designed to match wxCommandEvent
	wxCamDrawControlEvent(wxEventType commandType = wxEVT_NULL, INT32 id=0 ) : wxEvent(id, commandType) {}

	wxCamDrawControlEvent(const wxCamDrawControlEvent& event) : wxEvent(event) {}

	virtual wxEvent *Clone() const {return new wxCamDrawControlEvent(*this); }

	DECLARE_DYNAMIC_CLASS(wxCamDrawControlEvent);

};

typedef void (wxEvtHandler::*wxCamDrawControlEventFunction)(wxCamDrawControlEvent &);

DECLARE_EVENT_TYPE(wxEVT_CAMDRAWCONTROL_INVOKE, -1);

#define EVT_CAMDRAWCONTROL_INVOKE(id, fn) DECLARE_EVENT_TABLE_ENTRY(wxEVT_CAMDRAWCONTROL_INVOKE, id, -1, \
	(wxObjectEventFunction)(wxEventFunction)(wxCamDrawControlEventFunction) &fn, (wxObject *) NULL),

/*******************************************************************************************

>	class wxCamDrawControl : public wxEvtHandler

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	19/12/2005
	Purpose:	A base class for controls using the CamDrawProvider to paint themselves
	Notes:		In the OIL
	See Also:	

This class is specificly written so it will provided cached vector-drawn art.

********************************************************************************************/

class wxCamDrawControl : public wxControl
{
	DECLARE_DYNAMIC_CLASS(wxControl)
	DECLARE_EVENT_TABLE()
public:
	// Creation
	BOOL Create( wxWindow * parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					 /*TYPENOTE: Correct*/ long style = 0, const wxValidator& validator = wxDefaultValidator,
					 wxCamDrawControlStyle cacstyle = wxCDCS_DEFAULT,
					 wxString opdesc = wxString(_T("")));

	// Common init
	void Init() {
					m_CamDrawControlStyle=wxCDCS_DEFAULT;
					m_OpDesc=wxString(_T(""));
					m_Frozen=0;
				}

	// Constructors
	wxCamDrawControl() { Init(); }
	wxCamDrawControl( wxWindow * parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					 /*TYPENOTE: Correct*/ long style = 0, const wxValidator& validator = wxDefaultValidator,
					 wxCamDrawControlStyle cacstyle = wxCDCS_DEFAULT,
					 wxString opdesc = wxString(_T("")))
					{
						Init();
						ControlList::Get()->NewControl(this);
						Create(parent, id, pos, size, style, validator, cacstyle, opdesc);
					}
	~wxCamDrawControl() {  }

	// EventHandlers
	void OnPaint(wxPaintEvent & event);
	void OnSize(wxSizeEvent & event);
	void OnMouseEvent(wxMouseEvent & event);
	void OnInvoke(wxCamDrawControlEvent& event);

	virtual void Freeze() {m_Frozen++;}
	virtual void Thaw() {if (m_Frozen) m_Frozen--;}

	virtual void SetStyle(wxCamDrawControlStyle style) { m_CamDrawControlStyle=style; }
	virtual wxCamDrawControlStyle GetStyle() { return m_CamDrawControlStyle;}

	wxString GetOpDesc() {return m_OpDesc;}
	
protected:
	wxCamDrawControlStyle m_CamDrawControlStyle;

	wxString m_OpDesc;

	INT32 m_Frozen;

	void Invoke();

};

/*******************************************************************************************

>	class wxCamDrawControlXmlHandler : public wxXmlResourceHandler

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	19/12/2005
	Purpose:	A resource handler to enable wxCamDrawControl items to be loaded from XML
	Notes:		In the OIL
	See Also:	

********************************************************************************************/

class wxCamDrawControlXmlHandler : public wxXmlResourceHandler
{
DECLARE_DYNAMIC_CLASS(wxCamDrawControlXmlHandler)
public:
	wxCamDrawControlXmlHandler();
	virtual wxObject *DoCreateResource();
	virtual bool /*TYPENOTE: Correct*/ CanHandle(wxXmlNode *node);
};


#endif

