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


// class used to report errors
// (taken from errors.h 1.26)

#ifndef INC_ERRORBOX
#define	INC_ERRORBOX

// #include "errordlg.h"

class ErrorInfo;

/////////////////////////////////////////////////////////////////////////////
// CInformErrorDialog dialog

class CInformErrorDialog : public wxDialog
{
// Construction
public:
	CInformErrorDialog(wxWindow* pParent = NULL);	// standard constructor

	static wxWindow* GetSafeParent();

// Dialog Data
	//{{AFX_DATA(CInformErrorDialog)
	enum { IDD = _R(IDD_ERRORBOX) };
	wxButton		   *m_Button[ERRORDLG_MAXBUTTONS];
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	virtual BOOL OnInitDialog();
	void OnPaint();
	void OnClickedButton1();
	void OnClickedButton2();
	void OnClickedButton3();
	void OnClickedButton4();
	void OnClickedButton5();
	void OnCancelCmd();
    
	// Man Made Section
	// The strings that are to be displayed in the buttons and the static text box
	UINT32		m_StaticTextStr;
	UINT32		m_ButtonStr[ERRORDLG_MAXBUTTONS];
	UINT32		m_ErrorBoxType;		// Holds a ERRORTYPE_ description of whether the error is warning etc.
	UINT32		m_TitleStr;			// optionally holds ID of string to use for dialogue title
	UINT32		m_OwnerModule;
	UINT32		m_OK;				// which button is the "accept" button
	UINT32		m_Cancel;			// which button, if any, is the "reject" button
	UINT32		m_Help;				// which button, if any, is the "give me help" button

	POINT		IconPos;
	HWND		ParentHwnd;					// parent window, or NULL

	void GetDialogInfo();
	BOOL SetupButtons(HDC hDC, INT32 NumButtons);
	BOOL SetupMessage(HDC hDC);

	// Handles a button being clicked, ending the dialog, running help etc.
	virtual void HandleButton(UINT32 idButton);

	// The ID's of the error box buttons.
	static UINT32 ButtonID[ERRORDLG_MAXBUTTONS];

	// The default button size for the error box.
	static SIZE DefButtonSize;

	// How far apart the buttons should be.
	static INT32 ButtonSpacing;

	// Default size of the dialog
	static SIZE DialogSize;

	// Space between buttons and the edge of the dialog
	static INT32 EdgeSpacing;

	// Position of the buttons' top edges.
	static INT32 DefTopOfButton;

	// Position of the icon
	static POINT DefIconPos;

	// Default size of the area used to contain the error message.
	static SIZE DefMsgSize;

	// TRUE if we've initialised the above variables already; FALSE if not.
	static BOOL ValidInfo;

	// The text for each of the buttons.
	static String_64 ButtonText[ERRORDLG_MAXBUTTONS];

	// Andy Hills, 22-11-00
	// We need to store the help context as the dialogue is created.
	// This is because various On<Event> handlers can cause the help context
	// to be changed in the background, causing bug 6359 (Help button doesn't
	// work second time)
	UINT32 m_nHelpContext;

	friend INT32 InformGeneral(UINT32 Error, UINT32 modID, UINT32 ErrorMsg, 
				  			 UINT32 Butt1, UINT32 Butt2, UINT32 Butt3, UINT32 Butt4,
				  			 UINT32 OK, UINT32 Cancel);
	friend INT32 InformGeneral(UINT32 Error, ErrorInfo *pInfo, UINT32 ModID);
	friend void InformLastError(UINT32);
};

#endif
