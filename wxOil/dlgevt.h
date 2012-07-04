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


#ifndef INC_DLGEVT
#define	INC_DLGEVT

#include "drawctl.h"
//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "dlgtypes.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "msg.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "ktimer.h"

class	DialogManager;
class	DialogOp;

// Need a type for the hash data or we get duplicate const error
typedef const TCHAR * EventNameString;

// Declare the hash map from ResourceID to String
WX_DECLARE_HASH_MAP( WXTYPE, EventNameString, wxIntegerHash, wxIntegerEqual, EventNumberToName );

class DialogEventHandler;

class DlgEvtTimer : public KernelTimer
{
	CC_DECLARE_DYNAMIC(DlgEvtTimer);
friend class DialogEventHandler;
public:
	DlgEvtTimer(DialogEventHandler * pEvtHandler=NULL, DialogOp * pDialogOp=NULL, UINT32 IDEvent=NULL,
				void (* lpfnTimer)(void *) = NULL, void * Param=NULL) :
				m_pEvtHandler(pEvtHandler),
				m_pDialogOp(pDialogOp),
				m_IDEvent(IDEvent),
				m_lpfnTimer(lpfnTimer),
				m_Param(Param) {}
	~DlgEvtTimer() {}
protected:
	virtual void Notify();
	DialogEventHandler * m_pEvtHandler;
	DialogOp *m_pDialogOp;
	UINT32 m_IDEvent;
	void (* m_lpfnTimer)(void *);
	void * m_Param;
};

// Declare the hash map from integers to timers - note this CONTAINS the timers themselves
WX_DECLARE_HASH_MAP( UINT32, DlgEvtTimer*, wxIntegerHash, wxIntegerEqual, IntegerToKernelTimer );

class wxCamDialogEvent;

/*******************************************************************************************

>	class DialogEventHandler : public wxEvtHandler

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	19/12/2005
	Purpose:	A derived event handler to wire up wxDialog derived classes to DialogManager
	Notes:		In the OIL
	See Also:	

********************************************************************************************/

class DialogEventHandler : public wxEvtHandler
{
	friend class DialogManager;
	friend class DlgEvtTimer;

public:
	DialogEventHandler();
	DialogEventHandler(DialogOp * pOp);
	~DialogEventHandler(); // Note - do not call the destructor from within an event being handled!
	void Destroy();
	void CommandEvent(wxCommandEvent &event);
	void ScrollEvent(wxScrollEvent &event);
	void CloseEvent(wxCloseEvent &event);
	void MouseEvent(wxMouseEvent &event);
	void WindowDestroyEvent(wxWindowDestroyEvent &event);
	void OnChildFocus(wxChildFocusEvent &event);
	void OnSetFocus(wxFocusEvent &event);
	void CamDialogEvent(wxCamDialogEvent &event);
	void MoveEvent(wxMoveEvent &event);
	void SizeEvent(wxSizeEvent &event);
	void NotebookEvent(wxNotebookEvent &event);

	void GrimReaperEvent(wxCamDialogEvent &event);

	UINT32 AddTimer(DialogOp * pDialogOp, UINT32 nIDEvent, UINT32 nElapse, void (* lpfnTimer)(void *) =  NULL, void * param=NULL, BOOL OneShot=FALSE);
	BOOL DeleteTimer(UINT32 nIDEvent);

	static inline const TCHAR * GetEventName(WXTYPE EventNum) // Return the EventName
	{
		if (!pHash) return DefaultString;
		EventNumberToName::iterator i=pHash->find(EventNum);
		const TCHAR * text = (const TCHAR *)((i==pHash->end())?NULL:i->second);
		return text?text:DefaultString;
	};

	static BOOL Init();
	static void DeInit();

private:
	DECLARE_CLASS(wxEvtHandler)
	DECLARE_EVENT_TABLE()
	wxWindow * pwxWindow;
	DialogOp * pDialogOp;
	CDlgResID ID;
	BOOL wxAUImanaged;
	BOOL m_GrimReaperSent;

	IntegerToKernelTimer m_TimerHash;

	static EventNumberToName * pHash;
	static const TCHAR * DefaultString;

	static DialogEventHandler * m_GrimReaper;
};


/*******************************************************************************************

>	class wxCamDialogEvent : public wxEvent

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	19/12/2005
	Purpose:	A derived event to allow for postprocessing of dialog events
	Notes:		In the OIL
	See Also:	

********************************************************************************************/

class wxCamDialogEvent : public wxEvent
{
public:
	// Aargh note wxEvent's constructor has paramaters the otherway around from this - designed to match wxCommandEvent
	wxCamDialogEvent(wxEventType commandType = wxEVT_NULL, INT32 id=0 ) : wxEvent(id, commandType), msg(NULL, DIM_NONE, 0) {}
	wxCamDialogEvent(wxEventType commandType, INT32 id, DialogMsg m ) : wxEvent(id, commandType), msg(m) {}

	wxCamDialogEvent(const wxCamDialogEvent& event) : wxEvent(event), msg (event.msg) {}

	virtual wxEvent *Clone() const {return new wxCamDialogEvent(*this); }

	DECLARE_DYNAMIC_CLASS(wxCamDialogEvent);

	DialogMsg	msg;
};

typedef void (wxEvtHandler::*wxCamDialogEventFunction)(wxCamDialogEvent &);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(wxEVT_CAMDIALOG_DEFERREDMSG, 1001)
	DECLARE_EVENT_TYPE(wxEVT_CAMDIALOG_GRIMREAPER, 1002)
	DECLARE_EVENT_TYPE(wxEVT_CAMDIALOG_REDRAW, 1003)
END_DECLARE_EVENT_TYPES()

#define EVT_CAMDIALOG_DEFERREDMSG(id, fn) DECLARE_EVENT_TABLE_ENTRY(wxEVT_CAMDIALOG_DEFERREDMSG, id, -1, \
	(wxObjectEventFunction)(wxEventFunction)(wxCamDialogEventFunction) &fn, (wxObject *) NULL),
#define EVT_CAMDIALOG_GRIMREAPER(id, fn) DECLARE_EVENT_TABLE_ENTRY(wxEVT_CAMDIALOG_GRIMREAPER, id, -1, \
	(wxObjectEventFunction)(wxEventFunction)(wxCamDialogEventFunction) &fn, (wxObject *) NULL),
#define EVT_CAMDIALOG_REDRAW(id, fn) DECLARE_EVENT_TABLE_ENTRY(wxEVT_CAMDIALOG_REDRAW, id, -1, \
	(wxObjectEventFunction)(wxEventFunction)(wxCamDialogEventFunction) &fn, (wxObject *) NULL),

#endif

