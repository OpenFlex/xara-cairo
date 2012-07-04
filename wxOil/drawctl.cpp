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



#include "camtypes.h"

#include "dlgevt.h"
#include "drawctl.h"

/*****************************************************************************

This file contains the class for wxCamDrawControl, derived from
wxEvtHandler. This contains a mapping allowing dialogs of ANY class
derived from wxDialog to call the relevant bits of DialogManager.

*****************************************************************************/

DEFINE_EVENT_TYPE(wxEVT_CAMDRAWCONTROL_INVOKE)
IMPLEMENT_DYNAMIC_CLASS( wxCamDrawControlEvent, wxEvent )

IMPLEMENT_DYNAMIC_CLASS( wxCamDrawControl, wxControl )
BEGIN_EVENT_TABLE(wxCamDrawControl, wxControl)
	EVT_CAMDRAWCONTROL_INVOKE(wxID_ANY, wxCamDrawControl::OnInvoke)
	EVT_PAINT(wxCamDrawControl::OnPaint)
	EVT_MOUSE_EVENTS(wxCamDrawControl::OnMouseEvent)
	EVT_SIZE(wxCamDrawControl::OnSize)
END_EVENT_TABLE();

IMPLEMENT_DYNAMIC_CLASS( wxCamDrawControlXmlHandler, wxXmlResourceHandler)

/********************************************************************************************

>	BOOL wxCamDrawControl::Create( wxWindow * parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
					 [TYPENOTE: Correct] long style, const wxValidator& validator = wxDefaultValidator,
					 wxCamDrawControlStyle cacstyle = (wxCamDrawControlStyle)0,
					 wxString opdesc = wxString(_T("")))

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	30/12/2005
	Inputs:		parent - parent window
				id - id to use
				pos - position
				size - size
				style - style
				validator - validator (up to here, all the same as wxControl)
				cacstyle - the style of CamDrawControl to use, i.e. the flags passed
				opdesc - the opdescriptor to use, OR the empty string
	Outputs:	None
	Returns:	TRUE if succeeded, FALSE if fails
	Purpose:	Initialize the control
	Errors:		via wxMessageBox
	SeeAlso:	-

********************************************************************************************/

BOOL wxCamDrawControl::Create( wxWindow * parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
					 /*TYPENOTE: Correct*/ long style, const wxValidator& validator,
					 wxCamDrawControlStyle cacstyle,
					 wxString opdesc)
{
	if (!wxControl::Create(parent, id, pos, size, style, validator))
		return FALSE;

	m_CamDrawControlStyle = cacstyle;
	m_OpDesc = opdesc;
	return TRUE;
}


/********************************************************************************************

>	void wxCamDrawControl::OnPaint(wxPaintEvent & event)


	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	30/12/2005
	Inputs:		event - the event
	Outputs:	-
	Returns:	-
	Purpose:	Paints the control
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void wxCamDrawControl::OnPaint(wxPaintEvent & event)
{
	if (!m_Frozen)
	{
		wxCamDialogEvent RedrawEvent(wxEVT_CAMDIALOG_REDRAW, GetId());
		wxWindow * pParent=GetParent();
		if (pParent)
			pParent->GetEventHandler()->ProcessEvent(RedrawEvent);	
	}
}

/********************************************************************************************

>	void wxCamDrawControl::OnSize(wxSizeEvent & event)


	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	30/12/2005
	Inputs:		event - the event
	Outputs:	-
	Returns:	-
	Purpose:	Handles resizing of a control
	Errors:		-
	SeeAlso:	-

This is passed to the containing window's event handler for information

********************************************************************************************/

void wxCamDrawControl::OnSize(wxSizeEvent & event)
{
	wxWindow * pParent=GetParent();
	if (pParent)
		pParent->GetEventHandler()->ProcessEvent(event);	

	event.Skip();	// Pretend we didn't handle it
}


/********************************************************************************************

>	void wxCamDrawControl::OnMouseEvent(wxMouseEvent & event)


	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	30/12/2005
	Inputs:		event - the event
	Outputs:	-
	Returns:	-
	Purpose:	Handles mouse events
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void wxCamDrawControl::OnMouseEvent(wxMouseEvent & event)
{
	// Irritatingly wxMouseEvent does not propagate to the parent, but we expect it to.
	// so we have to fake it (sigh)
	// event.Skip(); // pretend we did not handle it, so it falls through to the dialog

	if ( !(GetExtraStyle() & wxWS_EX_BLOCK_EVENTS) )
	{
		wxWindow * pParent = GetParent();
		if (pParent && !pParent->IsBeingDeleted())
		{
			wxEvtHandler *pHandler = pParent->GetEventHandler();
			if (pHandler && pHandler->IsKindOf(CLASSINFO(DialogEventHandler))) // Only propagate to our own dialogs
			{
				pHandler->ProcessEvent(event);
			}
		}
	}
}



/********************************************************************************************

>	void wxCamDrawControl::OnInvoke(wxCamDrawControlEvent & event)


	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	30/12/2005
	Inputs:		event - the event
	Outputs:	-
	Returns:	-
	Purpose:	Handles deferred invoke events
	Errors:		-
	SeeAlso:	-

We do not process these immediately because otherwise the application does not have a chance
to redraw between undo etc. Instead we send a deferred message back to ourselves

********************************************************************************************/

void wxCamDrawControl::OnInvoke(wxCamDrawControlEvent & event)
{
	Invoke();
}

/********************************************************************************************

>	void wxCamDrawControl::Invoke()


	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	30/12/2005
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Does the work of the button being pressed
	Errors:		-
	SeeAlso:	-

We send ourselves our COMMAND event (which DialogManager picks up) and invoke the op
descriptor attached ourselves.

********************************************************************************************/

void wxCamDrawControl::Invoke()
{
	if (!IsEnabled())
	{
		return; // Don't even send messages if the control is greyed
	}

	wxCommandEvent ButtonEvent(wxEVT_COMMAND_BUTTON_CLICKED, GetId());
	ProcessEvent(ButtonEvent);
	// If it's attached to an OpDescriptor, we invoke it.
//	ControlList::Get()->Invoke(this);
}

/********************************************************************************************

>	wxCamDrawControlXmlHandler::wxCamDrawControlXmlHandler()


	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	30/12/2005
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Constructor
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

wxCamDrawControlXmlHandler::wxCamDrawControlXmlHandler() : wxXmlResourceHandler()
{
	XRC_ADD_STYLE(wxCDCS_DEFAULT);
	XRC_ADD_STYLE(wxCDCS_SETCLIPRECT);
	AddWindowStyles();
}

/********************************************************************************************

>	wxObject * wxCamDrawControlXmlHandler::DoCreateResource()


	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	30/12/2005
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Creates a wxCamDrawControl from XML
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

wxObject * wxCamDrawControlXmlHandler::DoCreateResource()
{
	XRC_MAKE_INSTANCE(control, wxCamDrawControl);
	control->Create(m_parentAsWindow,
					GetID(),
					GetPosition(),
					GetSize(),
					(GetStyle() & ~wxBORDER_MASK) | wxNO_BORDER,
					wxDefaultValidator,
					(wxCamDrawControlStyle)GetStyle(_T("camdrawstyle")),
					GetParamValue(_T("optoken"))
					);

	SetupWindow(control);

	return control;
}

/********************************************************************************************

>	bool [TYPENOTE: Correct] wxCamDrawControlXmlHandler::DoCreateResource()


	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	30/12/2005
	Inputs:		node - a pointer to the xml node
	Outputs:	-
	Returns:	TRUE if we can load it
	Purpose:	Determines whether or not we can handle an object type
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

bool /*TYPENOTE: Correct*/ wxCamDrawControlXmlHandler::CanHandle(wxXmlNode *node)
{
	bool	fOurClass = node->GetPropVal(wxT("class"), wxEmptyString) == wxT("wxCamDrawControl");
	return fOurClass;

	// This doesn't work on some compilers (although it is identical to what's above
	// just not in a function implemented in a header)
//	return (IsOfClass(node, wxT("wxCamDrawControl")));
}
