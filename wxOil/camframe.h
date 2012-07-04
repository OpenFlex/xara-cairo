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

#ifndef INC_CAMFRAME
#define INC_CAMFRAME

// Forward definitions
class CCamCanvas;
class wxAuiManager;
class CaptureWnd;

class CCamFrame :
	public wxDocMDIParentFrame
{
public:
	static CCamFrame   *m_pMainFrame;

private:
	DECLARE_CLASS( CCamFrame )
	
	wxMenu			   *m_editMenu;
#if defined(USE_WXAUI)
	wxAuiManager *m_pFrameManager;
#endif
	wxStatusBar*		m_pStatusBar;

	bool				m_ChangingViewMode;

	wxIcon				m_iconAppIcon;

	wxRect m_WndRect;		// Used to remember the unmin/maximised position

public:
	CCamFrame( wxDocManager *manager, wxFrame *frame, const wxString& title, const wxPoint& pos, const wxSize& size,
		   long type ); /* TYPENOTE: Correct */
	~CCamFrame();

	static CCamFrame * GetMainFrame() {return m_pMainFrame;}
	static wxAuiManager * GetFrameManager() { return m_pMainFrame?m_pMainFrame->m_pFrameManager:NULL;}
	
	wxStatusBar* GetStatusBar() const 	{ return m_pStatusBar; }

	BOOL CreateToolbars();

	void UpdateFrameManager();

    /// Creation
    bool Create( wxWindow *parent, wxWindowID id = -1, const wxString &caption = wxT("wxTemplate"), 
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, 
		long style = wxDEFAULT_FRAME_STYLE | wxVSCROLL | wxHSCROLL );

	bool IsChangingViewMode()				{ return m_ChangingViewMode;};
	void SetChangingMode(bool fSetOrClear)	{ m_ChangingViewMode = fSetOrClear;};

    /// Creates the controls and sizers
    void CreateControls();

	void UpdateWndSize();

#if !defined(USE_WXAUI)
    void OnSize(wxSizeEvent &event);
    void OnMove(wxMoveEvent &event);
#endif
	void OnCloseWindow(wxCloseEvent& event);

	void OnMenuCommand			( wxCommandEvent& event );

	void OnZoomIn				( wxCommandEvent& event );
	void OnZoomOut				( wxCommandEvent& event );
	void OnZoomDrawing			( wxCommandEvent& event );
	void OnZoomPage				( wxCommandEvent& event );
	void OnZoomPrevious			( wxCommandEvent& event );
	void OnQualityOutline		( wxCommandEvent& event );
	void OnQualitySimple		( wxCommandEvent& event );
	void OnQualityNormal		( wxCommandEvent& event );
	void OnQualityAntialiased	( wxCommandEvent& event );
	void OnBackgroundRender		( wxCommandEvent& event );
	void OnCaching				( wxCommandEvent& event );
	void OnDoubleBuffer			( wxCommandEvent& event );
	void OnTimeRedraw			( wxCommandEvent& event );
//#if defined(_DEBUG)
	void OnBlobbyDlg			( wxCommandEvent& event );
	void OnBlobbyBar			( wxCommandEvent& event );
	void OnTreeView				( wxCommandEvent& event );
//#endif
	void OnStandardBar			( wxCommandEvent& event );
	
	void OnInitMenuPopup		( wxMenuEvent& event );

	void OnUpdateStandardBar		( wxUpdateUIEvent& event );
	void OnUpdateZoomPrevious		( wxUpdateUIEvent& event );
	void OnUpdateQualityOutline		( wxUpdateUIEvent& event );
	void OnUpdateQualitySimple		( wxUpdateUIEvent& event );
	void OnUpdateQualityNormal		( wxUpdateUIEvent& event );
	void OnUpdateQualityAntialiased	( wxUpdateUIEvent& event );
	void OnUpdateBackgroundRender	( wxUpdateUIEvent& event );
	void OnUpdateCaching			( wxUpdateUIEvent& event );
	void OnUpdateDoubleBuffer		( wxUpdateUIEvent& event );

    /// Should we show tooltips?
    static bool ShowToolTips();

	virtual bool Destroy();

	DECLARE_EVENT_TABLE()
};

extern CCamFrame *GetMainFrame();

#endif
