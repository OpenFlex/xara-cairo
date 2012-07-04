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


#ifndef INC_DOCKBAR
#define INC_DOCKBAR

#include "list.h"


class OILChildBar;

/////////////////////////////////////////////////////////////////////////////////////////////
// DockBar General types
/////////////////////////////////////////////////////////////////////////////////////////////


// DONT CHANGE THE ORDER OF THIS ENUM !!
typedef enum
{
	DOCKBAR_LEFT,
	DOCKBAR_RIGHT,
	DOCKBAR_TOP,
	DOCKBAR_BOTTOM,
	DOCKBAR_FLOAT,
	NUM_DOCKBARS,
	DOCKBAR_INVALID = 4000	
} DockBarType;


typedef enum
{
	LARGE_CONTROLS=37,
	SMALL_CONTROLS=29
} ControlSizes;

#define MAX_SLOTS 8


/********************************************************************************************

>	class KernelBarPos : public CCObject

	Author:		Chris_Parks (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/3/94
	Purpose:	To assist in transfer of BarPosition Data between OIL and Kernel Layers   
	SeeAlso:	


********************************************************************************************/

class KernelBarPos : public CCObject
{
	public:
		KernelBarPos(){Slot=0;Position=0;Dock=DOCKBAR_TOP;};
		KernelBarPos( const KernelBarPos &other)
		{
			Slot=other.Slot;
			Position=other.Position;
			Dock=other.Dock;
		} 
		void operator = ( const KernelBarPos &other)
		{
			Slot=other.Slot;
			Position=other.Position;
			Dock=other.Dock;
		} 
	union {
		INT32	Slot;		// The slot in which the bar is placed (0..n)
		INT32	x;		   	// X position of floating bar
	};
	union {
		INT32	Position;	// The pixel position in the slot 
		INT32	y;			// Y position of floating bar
	};
	DockBarType	Dock;	// Type of dock in which this dialogbar lives
};


/********************************************************************************************

>	class OILDockingBar : public CControlBar

	Author:		Chris_Parks (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/3/94
	Purpose:	This is the base class for FixedDockBars and FloatingBars, 
	SeeAlso:	MFC TechNotes 24 -  	


********************************************************************************************/

PORTNOTE("other","Removed OILDockingBar - CControlBar usage switched for wxToolBar")
class OILDockingBar : public wxToolBar // CControlBar
{
// Construction
public:
	OILDockingBar();
	
// Attributes
protected:
	DockBarType			DockType;		// type of bar - LEFT RIGHT TOP BOTTOM FLOATING
	List				ChildBars;		// The list of all child ControlBars
	ControlSizes		ControlSize;	// Small or Large Controls
	wxWindow		   *Parent;			// Parent Window i.e. main frame
	BOOL				HasBigControls; // Big Controls Flag

public: 
private:
	
// Implementation
public:
	virtual	~OILDockingBar();
	virtual BOOL	PlaceBar(wxWindow* hdialogbar ,wxPoint here, wxSize size = wxSize(0,0))=0;
	virtual BOOL	PlaceBar(wxWindow* hdialogbar ,KernelBarPos BarPos, wxSize size = wxSize(0,0))=0;
	virtual BOOL	ReleaseBar(wxWindow* hdialog,BOOL DoTidy)=0;
	KernelBarPos *  GetBarPos(wxWindow* hWnd);
	KernelBarPos *  GetBarPos(StringBase * Name);
	wxRect			GetBarRect(StringBase * Name);
	wxRect			GetBarRect(wxWindow* hWnd);
	BOOL			SetNewHWnd(wxWindow* OldHWnd,wxWindow* NewwHWnd);
	virtual void	SetBigControlState(BOOL Big);
	wxWindow*	IsScreenPointInBar(wxPoint pnt); 
	BOOL	IsBigControls();
	virtual BOOL  DeleteBars() =0;
	virtual wxSize GetBarSize () = 0;
#ifdef _DEBUG
	virtual void AssertValid() const;
PORTNOTE("other", "Removed OILDockingBar::Dump" )
#ifndef EXCLUDE_FROM_XARALX
	virtual void Dump(CDumpContext& dc) const;
#endif
	void Dump_List();
#endif

protected:
    DECLARE_DYNAMIC_CLASS( OILDockingBar )
    DECLARE_EVENT_TABLE()

PORTNOTE("other", "Removed OILDockingBar::OnUpdateCmdUI" )
#ifndef EXCLUDE_FROM_XARALX
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler) ;
#endif

	//{{AFX_MSG(OILDockingBar)
   	//}}AFX_MSG
	// DECLARE_MESSAGE_MAP()
	BOOL	RemoveBar(OILChildBar * ThisBar);
	// BOOL	InsertBarInList(OILChildBar * ThisBar);
	OILChildBar * IsBarInList(wxWindow* hWnd);
	OILChildBar * IsBarInList(StringBase * Name); 
	static OILDockingBar * ChangedDock;
	static BOOL DoRecalc;    
private:

};

/********************************************************************************************

>	class OILFixedDockingBar : public OILDockingBar
	Author:		Chris_Parks (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/3/94
	Purpose:	This class handles the OIL-specific parts of FixedDockingbars.
				They handle the low-level creation/deletion details, 
	SeeAlso:	MFC TechNotes 24 -  	



********************************************************************************************/

PORTNOTE("other","Removed OILFixedDockingBar - OILDockingBar usage")
class OILFixedDockingBar : public OILDockingBar
{
// Construction
public:
	OILFixedDockingBar();
	BOOL Create( wxWindow* pParentWnd,
				DockBarType ReqType,UINT32 id =0);

// Attributes
public: 
private:
	INT32 	NoOfSlots;				// no of Slots in this bar
	INT32		SlotSize[MAX_SLOTS];	// Sizes of slots
	UINT32 	MaxPos;					// Maximum extent of the dock - ie MaxY if Left or Right else MaxX
	wxSize 	DockSize;				// record of bar dimensions
	wxPoint	Position;

	static BOOL	allowTidyBars;

// Implementation
public:

	BOOL	PlaceBar(wxWindow* hdialogbar ,wxPoint here, wxSize size = wxSize(0,0));
	BOOL	PlaceBar(wxWindow* hdialogbar ,KernelBarPos BarPos, wxSize size = wxSize(0,0));
	BOOL	PlaceBarAt(wxWindow* hdialogbar ,KernelBarPos BarPos);
	BOOL	ReleaseBar(wxWindow* hdialog,BOOL DoTidy);
	void 	AppendToSlot(INT32 SlotNo,wxPoint * here);
	BOOL	IsScreenPointInDock(wxPoint here);
	BOOL	IsScreenRectInDock(wxRect BarRect);
	void 	GetDockScreenRect(wxRect * BarRect);
	void 	SetBigControlState(BOOL Big);
	void  	BarPosToClient(KernelBarPos Pos,wxPoint * Point);
	void  	BarPosToScreen(KernelBarPos Pos,wxPoint * Point);
	INT32 	PointToSlot(wxPoint* ThisPoint);
	INT32 	PointToPosition(wxPoint* ThisPoint);
	void 	TidySlots();
	void 	CheckAndCorrectOverlap();
	wxSize	GetBarSize () { return (DockSize); }
	BOOL	SetSlotSize(INT32 SlotNo, INT32 NewSize);

	BOOL  DeleteBars();
PORTNOTE("other", "Removed OILDockingBar::RepositionWindow" )
#ifndef EXCLUDE_FROM_XARALX
	void 	RepositionWindow(AFX_SIZEPARENTPARAMS FAR* lpLayout, 
				wxWindow* wxWindow*, LPCRECT lpRect);
#endif

	static void DoNotTidyBars () { allowTidyBars = FALSE; }
	static void AllowTidyBars () { allowTidyBars = TRUE; }

#ifdef _DEBUG
	virtual void AssertValid() const;
PORTNOTE("other", "Removed OILDockingBar::Dump" )
#ifndef EXCLUDE_FROM_XARALX
	virtual void Dump(CDumpContext& dc) const;
	void Dump_List();
#endif
#endif
protected:
	// to erase the background
	wxBrush BackBrush;

	virtual void DoPaint(wxDC* pDC);

	DECLARE_DYNAMIC_CLASS( OILFixedDockingBar )
	DECLARE_EVENT_TABLE()

	//{{AFX_MSG(OILFixedDockingBar)
//    afx_msg LRESULT OnSizeParent(WPARAM wParam, LPARAM lParam);
   	//afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
   	//}}AFX_MSG

private:
	INT32		TotalSlotSizes(INT32 Slot = -1);
	void 	SetSize(wxRect LayoutRect,wxRect * rect);
	INT32 	GetIntersectPercent(OILChildBar * ThisBar);
	void 	PutInSlot(wxPoint * position, INT32 Size);
	BOOL 	ShiftBarPos(wxPoint * position,INT32 amount);
	BOOL 	ShiftBarSlot(wxPoint * position, INT32 NoSlots);
	BOOL 	CanShuffleForward(OILChildBar * Start,OILChildBar * End,INT32 amount);
	BOOL 	DoShuffleForward(OILChildBar * Start,OILChildBar * End,INT32 amount);
	BOOL 	CanShuffleBackward(OILChildBar * Start,OILChildBar * End,INT32 amount);
	BOOL 	DoShuffleBackward(OILChildBar * Start,OILChildBar * End,INT32 amount);
	void 	InsertSlot(INT32 SlotNo, INT32 NewSize = -1);
	void 	RemoveSlot(INT32 SlotNo);
	INT32		CountSlots();
	void 	PositionBar(OILChildBar * ThisBar);
	BOOL 	PlaceBarInSlot(OILChildBar * ThisBar,INT32 Slot);
	BOOL 	PlaceGalleryInSlot(OILChildBar * ThisBar,INT32 Slot);
	BOOL 	InsertBarInList(OILChildBar * ThisBar); 
	OILChildBar * IsPointInBar(wxPoint ThisPoint);
	OILChildBar * GetSlotHead(INT32 SlotNo);
	OILChildBar * GetOverLap(OILChildBar * ThisBar,INT32 SlotNo,
							INT32 * ForwardOverlap,INT32 * BackwardOverlap);
	BOOL GetGalleryOverLap(OILChildBar* ThisBar,INT32 SlotNo,
							INT32 * ForwardOverlap,INT32 * BackwardOverlap,
							OILChildBar** ppPrevious, OILChildBar** ppNext);
};

/********************************************************************************************

>	class OILFloaters : public OILDockingBar

	Author:		Chris_Parks (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/3/94
	Purpose:	This class handles the OIL-specific parts of Floaters.
				They handle the low-level creation/deletion details, 
	SeeAlso:	MFC TechNotes 24 -  	



********************************************************************************************/

PORTNOTE("other","Removed OILFloaters - OILDockingBar usage")
#ifndef EXCLUDE_FROM_XARALX
class OILFloaters : public OILDockingBar
{
 DECLARE_DYNAMIC(OILFloaters)

// Construction
public:
	OILFloaters();
	BOOL Create(CWnd* pParentWnd);
	
// Attributes
public: 
private:
	SIZE 	DockSize;	// record of bar dimensions (NOT actually used)
						// BUT included so I can get this bastard thing to compile!

// Implementation
public:
	BOOL	PlaceBar(wxWindow* hdialogbar ,wxPoint here, wxSize size = wxSize(0,0));
	BOOL	PlaceBar(wxWindow* hdialogbar ,KernelBarPos BarPos, wxSize size = wxSize(0,0));
	BOOL	ReleaseBar(wxWindow* hdialog,BOOL DoTidy);
	void	SetBigControlState(BOOL Big);
	virtual BOOL  DeleteBars();
	BOOL	RecreateBarsAfterSettingChange();	// UIC 
	SIZE	GetBarSize () { return (DockSize); }
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
		void Dump_List();
	#endif

protected:

   	//afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
   	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	BOOL 	InsertBarInList(OILChildBar * ThisBar); 
};
#endif

#endif
