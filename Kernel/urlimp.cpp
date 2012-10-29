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

// The "Import from URL..." menu item

#include "camtypes.h"

//#include "barsdlgs.h"		//For _R(IDD_BARCONTROLSTORE)

#include "urlimp.h"
#include "fileutil.h"

//#include "resimmap.h"		//For _R(IDS_HTMLIMPORT_FILEDOWNLOAD)
#include "urldlg.h"			//For URLImportDlg

#include "gendwnd.h"		//For the download operation
//#include "webster.h"

#include "xshelpid.h"		//For the help ID

CC_IMPLEMENT_DYNCREATE(OpURLImport, OpMenuImport)

#define new CAM_DEBUG_NEW

/********************************************************************************************

>	BOOL OpURLImport::Init()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/97
	Returns:	TRUE if worked, FALSE if failed (out of memory)
	Purpose:	Declares the OpDescriptor
	Errors:		-

********************************************************************************************/

BOOL OpURLImport::Init()
{
	return RegisterOpDescriptor(
									0, 							// Tool ID
									_R(IDS_URLIMPORT),					// String resource ID
									CC_RUNTIME_CLASS(OpURLImport), 	// Runtime class
									OPTOKEN_URLIMPORT,			// Token string
									GetState,					// GetState function
									_R(IDH_Command_Import_from_Web),							// help ID GTODO: Is this needed?
									_R(IDBBL_URLIMPORT),			// bubble help
									_R(IDD_BARCONTROLSTORE),		// resource ID
									_R(IDC_FILEURLIMPORT),				// control ID
									SYSTEMBAR_FILE,				// Bar ID
									TRUE,						// Receive system messages
									FALSE,						// Smart duplicate operation
									TRUE,						// Clean operation
									0,		// String for one copy only error
									(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC) // Auto state flags
 								);
	
}

/********************************************************************************************

>	void OpURLImport::Do(OpDescriptor*)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/97
	Purpose:	Imports a URL into the current document
	Errors:		-

********************************************************************************************/

void OpURLImport::Do(OpDescriptor*)
{
	//First display our Import from URL dialog and get a filename from it
	WebAddress urlToGet;
	
	BOOL ok=URLImportDlg::OpenAndGetURL(&urlToGet);

	//And if the user clicked OK
	if (ok)
	{

		//So, is the URL we've got back a local filename?
		if (urlToGet.IsLocalFile())
		{
			//Yes. So get it as a pathname
			PathName pthToGet=urlToGet.GetPathName();

			//And first get a pointer to the All filter
			Filter* pAllFilter=GetAllFilter();

			//And if we found it
			if (pAllFilter)
			{
				//Then import the pathname
				String_256 strToGet=pthToGet.GetPath();

				DoImport(pthToGet, pAllFilter, &strToGet);
			}

		}
		else
		{
			//No, it's a URL.

			// Added by Craig Hamilton 30/8/00.
			// Add some error checking to find whether the user has entered a valid URL

			PathName pthToGet = urlToGet.GetPathName();
			String_256 str256 = pthToGet.GetLocation(FALSE);
			CString s = str256;

			if((s == ""))
			{
				// ERROR
				MessageBox(NULL,"There was a problem downloading from the specified URL. Make sure the URL is spelled correctly.","Error from Xara X",MB_OK | MB_ICONWARNING);
				return;
			}
			// End added.

			//So download it
			ImportURL(urlToGet);
		}
	}





}

/********************************************************************************************

>	OpURLImport::OpURLImport()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/97
	Purpose:	Default constructor

********************************************************************************************/

OpURLImport::OpURLImport()
{
	OpFlags.HasOwnTimeIndicator = TRUE; // The OpURLImport op has its own time indicator
}

/********************************************************************************************

>	OpState OpURLImport::GetState(String_256*, OpDescriptor*)

	Author: 	Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/97
	Purpose:	This item is always available, so long as a document is visible.

********************************************************************************************/

OpState OpURLImport::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;

	return OpSt;
}

/*****************************************************************

  Toolkit functions

  ****************************************************************/

 /********************************************************************************************

>	BOOL OpURLImport::ImportURL(WebAddress urlToGet)

	Author: 	Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/97
	Inputs:		urlToGet	The URL to import
	Purpose:	Imports the URL given

********************************************************************************************/

BOOL OpURLImport::ImportURL(WebAddress urlToGet)
{
	//First, set up some variables. We must do this now because I'm 
	//going to use a goto in a moment
	GenericDownloadParam* Param;
	OpDescriptor* pOpDesc;
	PathName pthTemp;

	//We want to import urlToGet using the best available filter

	//To get the best available filter, we simply download to the "All" filter
	//So get a pointer to the All filter
	Filter* pAllFilter=GetAllFilter();

	//Check we found it
	if (pAllFilter==NULL)
		goto ReturnError;

	//Now, get ready to download the file. This is rather complex.

	//First create a new set of download parameters
	//This object will be deleted when the download finishes
	Param = new GenericDownloadParam;
	
	//Now find the generic download OpDescriptor
	pOpDesc = OpDescriptor::FindOpDescriptor(OPTOKEN_OPGENERICDOWNLOAD);

	//And check we found it
	if (pOpDesc==NULL)
		goto ReturnError;
  
	//Now, create a temporary file to download to
	pthTemp=FileUtil::GetTemporaryPathName();

	//And now fill in our parameters
	Param->type = TYPE_HTML;
	Param->priority = AsynchDownload::PRIORITY_NORMAL;
	Param->strDescription = String_256(_R(IDS_HTMLIMPORT_FILEDOWNLOAD));
	Param->file = pthTemp.GetPath();

	Param->strURL = urlToGet.GetWebAddress();
				
	Param->Output = NULL;

	Param->m_pFilter = pAllFilter;
	Param->m_Op = this;						
	Param->pDoc = Document::GetCurrent();

	//And, finally, start the download going, if we've got a URL to download
	if (!Param->strURL.IsEmpty())
		pOpDesc->Invoke((OpParam*) Param);
	
	//And return TRUE
	return TRUE;

ReturnError:
	if (Param)
		delete Param;

	return FALSE;
}

 /********************************************************************************************

>	Filter* OpURLImport::GetAllFilter()

	Author: 	Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/97
	Inputs:		-
	Purpose:	Gets a pointer to the All filter.
    
********************************************************************************************/

Filter* OpURLImport::GetAllFilter()
{
	//So get a pointer to the All filter
	return Filter::FindFilterFromID(FILTERID_GENERIC);
		
}


