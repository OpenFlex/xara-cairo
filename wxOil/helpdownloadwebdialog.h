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


#ifndef _HELPDOWNLOADWEBDIALOG
#define _HELPDOWNLOADWEBDIALOG

#include "webcommand.h"
#include "webdialogdlg.h"

/////////////////////////////////////////////////////////////////////////////
// CHelpDownloadWebDialog 

class CHelpDownloadWebDialog : public CWebDialogDlg
{
// Construction
public:
	CHelpDownloadWebDialog(TCHAR* WebFile);	// standard constructor

// Implementation
protected:
	virtual afx_msg void OnWebCommandDoCommand(LPCTSTR Command, LPCTSTR CommandInfo);
	virtual BOOL OnInitDialog();

// Attributes
public:
	BOOL m_bFastConnection;

};

#endif
