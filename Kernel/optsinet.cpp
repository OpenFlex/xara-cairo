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
#include "appprefs.h"
#include "optsinet.h"	// dialog/gadget ids
//#include "optsres.h"	// _R(IDS_PROXY)...
//#include "app.h"		// Camelot object - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "document.h"	// document object - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "spread.h"		// spread object - in camtypes.h [AUTOMATICALLY REMOVED]
#include "page.h"		// page object
//#include "webster.h"
#include "camnet.h"

//#include "resource.h"	// _R(IDS_CANCEL)#

CC_IMPLEMENT_DYNAMIC(InternetTab, OptionsTabs)   

/******************************************************************************************

>	BOOL InternetTab::CommitSection()

	Author:		Adrian_Stoicar (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/06/97
	Returns:	TRUE if succesful, FALSE otherwise 
	Purpose:	Effect any changes made to the Internet settings

******************************************************************************************/

BOOL InternetTab::CommitSection() 
{
	ERROR2IF(pPrefsDlg==NULL,FALSE,"GridTab::CommitSection() - pPrefsDlg==NULL");
	if (pPrefsDlg->TalkToPage(_R(IDD_OPTSTAB_INTERNET))==FALSE)
		return TRUE;	// just return with no error

	// Read in the new potential cache size
	BOOL Valid = TRUE;
	UINT32 lCacheSize = pPrefsDlg->GetMemoryGadgetValue(_R(IDC_CACHESIZE),1024,UINT32_MAX,_R(IDS_INVALIDCACHESIZE),&Valid);

	if ((lCacheSize < 500 * SIZEOFKILOBYTE) || (lCacheSize == UINT32_MAX))
	{
		InformWarning(_R(IDS_INVALIDCACHESIZE));

		if (lCacheSize < 500 * SIZEOFKILOBYTE)
		{
			lCacheSize = 500 * SIZEOFKILOBYTE;
		}
		else
		{
			lCacheSize = UINT32_MAX;
		}

		pPrefsDlg->SetMemoryGadgetValue(_R(IDC_CACHESIZE), lCacheSize);
	}

	if(!Valid) return FALSE;

	if (Valid && !DownloadCache::SetSize(lCacheSize))
	{
		InformError(_R(IDS_INSUFFICIENT_DISK_SPACE));
		return FALSE;
	}

	UINT32 lCacheUsage = DownloadCache::GetUsage();
	pPrefsDlg->SetLongGadgetValue(_R(IDC_CACHEUSAGE), lCacheUsage);

	// Sort out the connection type
	if (pPrefsDlg->GetBoolGadgetSelected(_R(IDC_14K)))
		InternetManager::SetConnectionType(CONNECTION_SLOWMODEM);
	else if (pPrefsDlg->GetBoolGadgetSelected(_R(IDC_28K)))
		InternetManager::SetConnectionType(CONNECTION_FASTMODEM);
	else if (pPrefsDlg->GetBoolGadgetSelected(_R(IDC_56K)))
		InternetManager::SetConnectionType(CONNECTION_X2);
	else if (pPrefsDlg->GetBoolGadgetSelected(_R(IDC_ISDN)))
		InternetManager::SetConnectionType(CONNECTION_ISDN);
	return TRUE;
}


/********************************************************************************************

>	BOOL InternetTab::HandleMsg(DialogMsg* Msg)

	Author:		Adrian_Stoicar (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/07/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Handles all the Internet options tabs messages 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

BOOL InternetTab::HandleMsg(DialogMsg* Msg)
{
	ERROR2IF(Msg == NULL,FALSE,"Null message received");
	ERROR2IF(pPrefsDlg == NULL,FALSE,"HandleMsg called with no dialog pointer");

	BOOL ok = pPrefsDlg->TalkToPage(_R(IDD_OPTSTAB_INTERNET));	// The Page page identifier
	if (!ok)
		return TRUE;		// page not present

	switch(Msg->DlgMsg)
	{
		case DIM_CREATE:	// Initialise controls
			ok = InitSection();
			if (!ok)
				InformError();
			break;
		case DIM_TEXT_CHANGED:
			OptionsTabs::SetApplyNowState(TRUE);
			OptionsTabs::UngreyApplyNow();
			break;
		case DIM_LFT_BN_CLICKED:
			switch (Msg->GadgetID)
			{
				case _R(IDC_FLUSHCACHE):
					{
						DownloadCache::Flush();
						UINT32 lCacheUsage = DownloadCache::GetUsage();
						pPrefsDlg->SetMemoryGadgetValue(_R(IDC_CACHEUSAGE), lCacheUsage);
					}
					break;
				default:
					OptionsTabs::SetApplyNowState(TRUE);
			}
			break;
	}	
	return TRUE;
}  


/******************************************************************************************

>	BOOL GridTab::InitSection()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/10/95
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if successful, else FALSE
	Purpose:	Sets initial values for the Page section of the options dialog box.
				This section includes the:-
	Errors:		-
	SeeAlso:	AppPrefsDlg; OptionsTabs; UpdateSection;

******************************************************************************************/

BOOL InternetTab::InitSection()
{
	ERROR2IF(pPrefsDlg == NULL,FALSE,"InitSection called with no dialog pointer");

	// Fill in the data regardless of whether the proxy is enabled or not
	// Now get the current settings
	TCHAR szHostName[INTERNET_MAX_PATH_LENGTH];
	SERVENT proxyEntry = {szHostName, NULL, 0x0000, NULL};
	bool bProxyEnabled;

	String_256 strProxyNote(_T(""));
	
	if (!InternetManager::GetProxyServer(&proxyEntry, &bProxyEnabled))
	{
		// failed to read proxy settings
		String_256 strProxyError(_R(IDS_PROXY_SUB_ERROR));
		strProxyNote.MakeMsg(_R(IDS_PROXY_NOTE), static_cast<TCHAR *>(strProxyError));
	}
	else
	{
		// read settings ok
		if (bProxyEnabled)
		{
			// proxy server enabled
			String_256 strProxyEnabled;
			strProxyEnabled.MakeMsg(_R(IDS_PROXY_SUB_ENABLED), proxyEntry.s_name, proxyEntry.s_port);
			strProxyNote.MakeMsg(_R(IDS_PROXY_NOTE), static_cast<TCHAR *>(strProxyEnabled));
		}
		else
		{
			// proxy server disabled
			String_256 strProxyDisabled(_R(IDS_PROXY_SUB_DISABLED));
			strProxyNote.MakeMsg(_R(IDS_PROXY_NOTE), static_cast<TCHAR *>(strProxyDisabled));
		}
	}

	pPrefsDlg->SetStringGadgetValue(_R(IDC_PROXY_DETAILS), &strProxyNote);

	// Sort out the connection type
	UINT32 nSelID;
	switch (InternetManager::GetConnectionType())
	{
		case CONNECTION_SLOWMODEM:
			nSelID = _R(IDC_14K);
			break;
		case CONNECTION_FASTMODEM:
			nSelID = _R(IDC_28K);
			break;
		case CONNECTION_X2:
			nSelID = _R(IDC_56K);
			break;
		case CONNECTION_ISDN:
			nSelID = _R(IDC_ISDN);
	}
	pPrefsDlg->SetBoolGadgetSelected(nSelID, TRUE);

	
	// Sort out the download cache section.
	UINT32 lCacheUsage = DownloadCache::GetUsage();
	pPrefsDlg->SetLongGadgetValue(_R(IDC_CACHEUSAGE), lCacheUsage);

	UINT32 lCacheSize = DownloadCache::GetSize();
	pPrefsDlg->SetMemoryGadgetValue(_R(IDC_CACHESIZE), lCacheSize);
	return TRUE;
}


