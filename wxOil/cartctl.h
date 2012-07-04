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


#ifndef INC_CARTCTL
#define	INC_CARTCTL

#include "cartprov.h"
#include "ctrllist.h"

enum wxCamArtControlStyle
{
	// Caching flags start here - the art provider may have a different bitmap depending on the
	// state of these flags...
	wxCACS_TOOLBACKGROUND	= CAF_TOOLBACKGROUND,
	wxCACS_PUSHBUTTON		= CAF_PUSHBUTTON,
	wxCACS_TOGGLEBUTTON		= CAF_TOGGLEBUTTON,	// wxCACS_PUSHBUTTON should also be set if this is set
	wxCACS_ALWAYS3D			= CAF_ALWAYS3D,
	wxCACS_ALLOWHOVER		= CAF_ALLOWHOVER,
	wxCACS_NOINTERNALBORDER	= CAF_NOINTERNALBORDER,
	wxCACS_TEXT				= CAF_TEXT,
	wxCACS_EXACTFIT			= CAF_EXACTFIT,
	wxCACS_HALFHEIGHT		= CAF_HALFHEIGHT,
	wxCACS_TOP				= CAF_TOP,
	wxCACS_BOTTOM			= CAF_BOTTOM,
	wxCACS_LEFT				= CAF_LEFT,
	wxCACS_RIGHT			= CAF_RIGHT,
	wxCACS_NOAUTOREPEAT		= CAF_NOAUTOREPEAT,
	wxCACS_STATUSBARTEXT	= CAF_STATUSBARTEXT,

	wxCACS_DEFAULT			= 0
};

/*******************************************************************************************

>	class wxCamArtControlEvent : public wxEvent

	Author:		Alex_Bligh <alex@alex.org.uk>
o	Created:	19/12/2005
	Purpose:	A derived event to allow for postprocessing of autorepeat on buttons
	Notes:		In the OIL
	See Also:	

********************************************************************************************/

class wxCamArtControlEvent : public wxEvent
{
public:
	// Aargh note wxEvent's constructor has paramaters the otherway around from this - designed to match wxCommandEvent
	wxCamArtControlEvent(wxEventType commandType = wxEVT_NULL, INT32 id=0 ) : wxEvent(id, commandType) {}

	wxCamArtControlEvent(const wxCamArtControlEvent& event) : wxEvent(event) {}

	virtual wxEvent *Clone() const {return new wxCamArtControlEvent(*this); }

	DECLARE_DYNAMIC_CLASS(wxCamArtControlEvent);

};

typedef void (wxEvtHandler::*wxCamArtControlEventFunction)(wxCamArtControlEvent &);

DECLARE_EVENT_TYPE(wxEVT_CAMARTCONTROL_INVOKE, -1);

#define EVT_CAMARTCONTROL_INVOKE(id, fn) DECLARE_EVENT_TABLE_ENTRY(wxEVT_CAMARTCONTROL_INVOKE, id, -1, \
	(wxObjectEventFunction)(wxEventFunction)(wxCamArtControlEventFunction) &fn, (wxObject *) NULL),

/*******************************************************************************************

>	class wxCamArtControl : public wxEvtHandler

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	19/12/2005
	Purpose:	A base class for controls using the CamArtProvider to paint themselves
	Notes:		In the OIL
	See Also:	

This class is specificly written so it will provided cached vector-drawn art.

********************************************************************************************/

class wxCamArtControl : public wxControl
{
	DECLARE_DYNAMIC_CLASS(wxControl)
	DECLARE_EVENT_TABLE()
public:
	// Creation
	BOOL Create( wxWindow * parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					 /*TYPENOTE: Correct*/ long style = 0, const wxValidator& validator = wxDefaultValidator,
					 wxCamArtControlStyle cacstyle = wxCACS_DEFAULT,
					 wxString opdesc = wxString(_T("")));

	// Common init
	void Init() {
					m_Value=0;
					m_CamArtControlStyle=wxCACS_DEFAULT;
					m_BestSize=wxDefaultSize;
					m_State=CAF_DEFAULT;
					m_OpDesc=wxString(_T(""));
					m_Timer.SetOwner(this, _R(IDC_WXCAMARTCONTROL_AUTOREPEAT));
					m_ARDelay=500;
					m_ARRepeat=50;
					m_AREventPending=FALSE;
					m_BitmapId=0;
				}

	// Constructors
	wxCamArtControl() { Init(); }
	wxCamArtControl( wxWindow * parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					 /*TYPENOTE: Correct*/ long style = 0, const wxValidator& validator = wxDefaultValidator,
					 wxCamArtControlStyle cacstyle = wxCACS_DEFAULT,
					 wxString opdesc = wxString(_T("")))
					{
						Init();
						ControlList::Get()->NewControl(this);
						Create(parent, id, pos, size, style, validator, cacstyle, opdesc);
					}
	~wxCamArtControl() { m_Timer.Stop(); }
	// Override
	wxSize DoGetBestSize() const;

	// EventHandlers
	void OnPaint(wxPaintEvent & event);
	void OnMouseEvent(wxMouseEvent & event);
	void OnTimer(wxTimerEvent& event);
	void OnInvoke(wxCamArtControlEvent& event);

	// Reload bitmap
	void NewBitmap() {FindBitmap(); Refresh();}
	
	virtual void SetStyle(wxCamArtControlStyle style) { m_CamArtControlStyle=style; NewBitmap(); }
	virtual wxCamArtControlStyle GetStyle() const { return m_CamArtControlStyle;}

	virtual void SetValue(UINT32 value)
		{
			m_Value=value;
			CamArtFlags o=m_State;
			if (value) m_State=(CamArtFlags)(m_State | CAF_SELECTED); else m_State =(CamArtFlags)(m_State & ~CAF_SELECTED);
			if (o!=m_State) Refresh();
		}
	virtual UINT32 GetValue() { return m_Value;}

	// override Enable to clear hover flag when control disabled
	virtual /*TYPENOTE: Correct*/ bool Enable(bool /*TYPENOTE: Correct*/ enable = true)
		{
			if (!enable)
			{
				m_State = (CamArtFlags)(m_State & ~CAF_BUTTONHOVER);
				m_Timer.Stop(); // Don't process more events
			}
			return wxControl::Enable(enable);
		}

	virtual void SetLabel(const wxString& label) {if (label!=GetLabel()) {wxControl::SetLabel(label); Refresh(TRUE);}}

	wxString GetOpDesc() {return m_OpDesc;}

	const ResourceID GetBitmapId() {return m_BitmapId?m_BitmapId:GetId();}
	void SetBitmapId(ResourceID r=0) {m_BitmapId=r; NewBitmap();}

protected:
	wxCamArtControlStyle m_CamArtControlStyle;
	UINT32 m_Value;
	wxSize m_BestSize;
	CamArtFlags m_State;

	wxTimer m_Timer;
	UINT32 m_ARDelay;
	UINT32 m_ARRepeat;
	BOOL m_AREventPending;

	wxString m_OpDesc;

	void Invoke();

	void FindBitmap();
	CamArtFlags GetArtFlags() {return (CamArtFlags)(m_CamArtControlStyle | m_State | (IsEnabled()?0:CAF_GREYED));}

	ResourceID m_BitmapId;

};

/*******************************************************************************************

>	class wxCamArtControlXmlHandler : public wxXmlResourceHandler

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	19/12/2005
	Purpose:	A resource handler to enable wxCamArtControl items to be loaded from XML
	Notes:		In the OIL
	See Also:	

********************************************************************************************/

class wxCamArtControlXmlHandler : public wxXmlResourceHandler
{
DECLARE_DYNAMIC_CLASS(wxCamArtControlXmlHandler)
public:
	wxCamArtControlXmlHandler();
	virtual wxObject *DoCreateResource();
	virtual bool /*TYPENOTE: Correct*/ CanHandle(wxXmlNode *node);
};


#endif

