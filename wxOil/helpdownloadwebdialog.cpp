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
#include "camelot.h"
#include "resdll.h"
#include "stdafx.h"
#include "helpdownloadwebdialog.h"
#include "helpuser.h"
//#include "helppath.h"
#include "product.h"
#include "menuops.h"
#include "camnet.h"
//#include "phil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpDownloadWebDialog dialog
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************

>	CHelpDownloadWebDialog::CHelpDownloadWebDialog(CString WebFile)

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/4/2004
	Purpose:	Construct a CHelpDownloadWebDialog

****************************************************************************/

CHelpDownloadWebDialog::CHelpDownloadWebDialog(TCHAR* WebFile)
	: CWebDialogDlg(FALSE,WebFile,NULL,FALSE,0)
{
	m_bFastConnection = (InternetManager::GetConnectionType()>=CONNECTION_ISDN);
}



BOOL CHelpDownloadWebDialog::OnInitDialog()
{
TRACEUSER( "Phil", _T("CHDlWDlg::InitDialog Entry\n"));
	CWebDialogDlg::OnInitDialog();
TRACEUSER( "Phil", _T("CHDlWDlg::InitDialog 2\n"));

	if (m_bFastConnection)
	{
		m_WebCommand.SetLayerVisibility("fast", TRUE);
		m_WebCommand.SetLayerVisibility("slow", FALSE);
	}
	else
	{
		m_WebCommand.SetLayerVisibility("fast", FALSE);
		m_WebCommand.SetLayerVisibility("slow", TRUE);
	}

TRACEUSER( "Phil", _T("CHDlWDlg::InitDialog Exit\n"));
	return FALSE;  // return TRUE  unless you set the focus to a control
}



/****************************************************************************

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/4/2004
	Purpose:	override the handling of web dialog events 

****************************************************************************/

void CHelpDownloadWebDialog::OnWebCommandDoCommand(LPCTSTR Command, LPCTSTR CommandInfo) 
{
	CString sCommand = Command;
	CString sCommandInfo = CommandInfo;
	TRACE( _T("Received Command:%s\n"), sCommand );
	if (sCommand == "close" || sCommand == "exit" || sCommand == "later")
	{
		EndDialog(IDCANCEL);
	}
	else if ( sCommand == "yes" || sCommand == "download" || sCommand == "ok" )
	{
		EndDialog(IDOK);
	}
	else if ( sCommand == "ignore" )
	{
		EndDialog(_R(IDB_IGNORE));
	}
	else if ( sCommand == "fast")
	{
		m_WebCommand.SetLayerVisibility("fast", TRUE);
		m_WebCommand.SetLayerVisibility("slow", FALSE);
		m_bFastConnection = TRUE;
	}
	else if ( sCommand == "slow" )
	{
		m_WebCommand.SetLayerVisibility("fast", FALSE);
		m_WebCommand.SetLayerVisibility("slow", TRUE);
		m_bFastConnection = FALSE;
	}
	else if ( sCommand == "help" )
	{
		HelpUserTopic(_R(IDS_HELPPATH_Misc_Xara_Ltd)/*23106*/);
	}
}

