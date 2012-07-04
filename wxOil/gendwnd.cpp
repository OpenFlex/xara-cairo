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
#include "gendwnd.h"
//#include "webster.h"
#include "impexpop.h"
//#include "resimmap.h"	//_R(IDS_HTML_DOWNLOADFAILED)


DECLARE_SOURCE("$Revision: 751 $");

CC_IMPLEMENT_DYNCREATE(OpGenericDownload, DownloadOp) 

#define new CAM_DEBUG_NEW


/********************************************************************************************

>	GenericDownloadParam::GenericDownloadParam()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01/05/97
	Inputs:		
	Returns:	
	Purpose:	Default constructor. Do nothing
	Errors:		

********************************************************************************************/

GenericDownloadParam::GenericDownloadParam()
{

}

/********************************************************************************************

>	GenericDownloadParam::~GenericDownloadParam()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01/05/97
	Inputs:		
	Returns:	
	Purpose:	Destructor. Do nothing
	Errors:		

********************************************************************************************/

GenericDownloadParam::~GenericDownloadParam()
{

}

/********************************************************************************************

>	BOOL OpGenericDownload::Init()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/04/97
	Inputs:		
	Returns:	TRUE if the Init worked ok
	Purpose:	
	Errors:		

********************************************************************************************/

BOOL OpGenericDownload::Init()
{
	return RegisterOpDescriptor(
		0,									// Tool ID
 		_R(IDS_OPGENERICDOWNLOAD),						// String resource ID
		CC_RUNTIME_CLASS(OpGenericDownload),	// Runtime class
 		OPTOKEN_OPGENERICDOWNLOAD,					// Token string
 		OpGenericDownload::GetState,			// GetState function
		0,									// Help ID
		0,									// Bubble ID
		0,									// Resource ID
		0									// Control ID
	);
}


/********************************************************************************************

>	OpState OpGenericDownload::GetState(String_256*, OpDescriptor*)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/04/97
	Inputs:		
	Returns:	
	Purpose:	
	Errors:		

********************************************************************************************/

OpState OpGenericDownload::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;
	return(OpSt);
}


/********************************************************************************************

>	BOOL OpGenericDownload::OnDocChangingMsg(Document* pChangingDoc, DocChangingMsg::DocState State)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/05/97
	Inputs:		pChangingDoc -
				State -
	Returns:	
	Purpose:	End (abort) the operation when for instance the current document has been destroyed
				while downloading.
	Errors:		

********************************************************************************************/

BOOL OpGenericDownload::OnDocChangingMsg(Document* pChangingDoc, DocChangingMsg::DocState State)
{
	GenericDownloadParam* pGenericParam = (GenericDownloadParam*) pParam;
	Document* pCurDoc = pGenericParam->pDoc;

	if (pParam != NULL)
	{
		if (State == DocChangingMsg::ABOUTTODIE && pChangingDoc == pCurDoc)
		{
//			Document::SetSelectedViewAndSpread(pCurDoc);
//			SelOperation* Op = pGenericParam->m_Op;
//			((OpMenuImport*)Op)->EndImport();

			// end of the download op
			FailAndExecute(); 
			End();
		}
	}

	return TRUE;
}


/********************************************************************************************

>	void OpGenericDownload::OnDownloadSuccess()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/04/97
	Inputs:		
	Returns:	
	Purpose:	Function called when the download has finished and is success
				
	Errors:		

********************************************************************************************/

void OpGenericDownload::OnDownloadSuccess()
{
	// get a pointer to the OpParam so that I can retrieve some useful information
	GenericDownloadParam* pGenericParam = (GenericDownloadParam*) pParam;

	String_256 GenericFile = (pGenericParam->file).GetFileName();
	if (IsUserName("Olivier"))
		TRACE1("OpGenericDownload::OnDownloadSuccess(), file = %s\n", (TCHAR*)GenericFile);

	Filter* pFilter = pGenericParam->m_pFilter;
	PathName Path = pGenericParam->file;
	String_256 URL = pGenericParam->strURL;
	SelOperation* Op = pGenericParam->m_Op;

	// call the DoImport function from OpMenuImport class
	((OpMenuImport*)Op)->DoImport(Path, pFilter, &URL);

	// remove the temporary file
	remove((TCHAR*) (String_256) Path.GetPath());
}


/********************************************************************************************

>	void OpGenericDownload::OnDownloadFail()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com> (rewritten by Graham)
	Created:	28/04/97
	Inputs:		
	Returns:	
	Purpose:	Function called when the download has failed
	Errors:		

********************************************************************************************/


void OpGenericDownload::OnDownloadFail()
{
	//First get a pointer to the parameters
	GenericDownloadParam* pGenParam = (GenericDownloadParam*) pParam;

	if (pGenParam==NULL)
	{
		ERROR2RAW("OpBitmapDownload::OnDownloadFail - no download parameters");
		return;
	}

	//Get the URL which the user typed
	String_256 strURL=pGenParam->strURL;

	//And put it up as a message
	String_256 strMessage;
	strMessage.MakeMsg(_R(IDS_HTML_DOWNLOADFAILED), &strURL);
	Error::SetError(0, strMessage, 0);
	InformError();

}


/********************************************************************************************

>	void OpGenericDownload::OnDownloadAbort()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/05/97
	Inputs:		
	Returns:	
	Purpose:	Function called when the use abort download 
	Errors:		

********************************************************************************************/

void OpGenericDownload::OnDownloadAbort()
{

	// get a pointer to the OpParam so that I can retrieve some useful information
	GenericDownloadParam* pGenericParam = (GenericDownloadParam*) pParam;

	String_256 GenericFile = pGenericParam->strURL;
	if (IsUserName("Olivier"))
		TRACE1("OpGenericDownload::OnDownloadAbort(), file = %s\n", (TCHAR*)GenericFile);

	// stop the import op
	SelOperation* Op = pGenericParam->m_Op;
	((OpMenuImport*)Op)->EndImport();
}
