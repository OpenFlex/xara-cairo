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
#include "htmldwnd.h"
#include "htmlfltr.h"
//#include "webster.h"

//#include "resimmap.h"	//For _R(IDS_HTML_DOWNLOADFAILED)


DECLARE_SOURCE("$Revision: 1282 $");

CC_IMPLEMENT_DYNCREATE(OpBitmapDownload, DownloadOp) 

#define new CAM_DEBUG_NEW


///////////////////////////////////////////////////////////////////////////////
/////////////////				Bitmap download			///////////////////////
///////////////////////////////////////////////////////////////////////////////


/********************************************************************************************

>	BitmapDownloadParam::BitmapDownloadParam()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01/05/97
	Inputs:		
	Returns:	
	Purpose:	Default constructor. Do nothing
	Errors:		

********************************************************************************************/

BitmapDownloadParam::BitmapDownloadParam()
{
}


/********************************************************************************************

>	BitmapDownloadParam::~BitmapDownloadParam()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01/05/97
	Inputs:		
	Returns:	
	Purpose:	Destructor. Do nothing
	Errors:		

********************************************************************************************/

BitmapDownloadParam::~BitmapDownloadParam()
{
}

/********************************************************************************************

>	BOOL BOOL OpBitmapDownload::Init()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/04/97
	Inputs:		
	Returns:	TRUE if the Init worked ok
	Purpose:	
	Errors:		

********************************************************************************************/

BOOL OpBitmapDownload::Init()
{
	return RegisterOpDescriptor(
		0,									// Tool ID
 		_R(IDS_OPBITMAPDOWNLOAD),				// String resource ID
		CC_RUNTIME_CLASS(OpBitmapDownload),	// Runtime class
 		OPTOKEN_OPBITMAPDOWNLOAD,			// Token string
 		OpBitmapDownload::GetState,			// GetState function
		0,									// Help ID
		0,									// Bubble ID
		0,									// Resource ID
		0									// Control ID
	);
}


/********************************************************************************************

>	OpState OpBitmapDownload::GetState(String_256*, OpDescriptor*)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/04/97
	Inputs:		
	Returns:	
	Purpose:	
	Errors:		

********************************************************************************************/

OpState OpBitmapDownload::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;
	return(OpSt);
}


/********************************************************************************************

>	BOOL OpBitmapDownload::OnDocChangingMsg(Document* pChangingDoc, DocChangingMsg::DocState State)

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/05/97
	Inputs:		pChangingDoc -
				State -
	Returns:	
	Purpose:	End (abort) the operation when for instance the current document has been destroyed
				while downloading.
	Errors:		

********************************************************************************************/

BOOL OpBitmapDownload::OnDocChangingMsg(Document* pChangingDoc, DocChangingMsg::DocState State)
{
	BitmapDownloadParam* pBMPParam = (BitmapDownloadParam*) pParam;

	if (pParam != NULL)
	{
		if (State == DocChangingMsg::ABOUTTODIE && pChangingDoc == pBMPParam->m_DestDoc)
		{
			FailAndExecute(); 
			End();
		}
	}

	return TRUE;
}

/********************************************************************************************

>	void OpBitmapDownload::OnDownloadSuccess()

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/04/97
	Inputs:		
	Returns:	
	Purpose:	Start the bitmap import
	Errors:		

********************************************************************************************/

void OpBitmapDownload::OnDownloadSuccess()
{
	// get a pointer to the OpParam so that I can retrieve some useful information
	BitmapDownloadParam* pBMPParam = (BitmapDownloadParam*) pParam;

	String_256 BitmapFile = (pBMPParam->file).GetFileName();
	if (IsUserName("Olivier"))
		TRACE1("OpBitmapDownload::OnDownloadSuccess(), file = %s\n", (TCHAR*)BitmapFile);

	INT32 TagId = pBMPParam->m_TagId;
	//SelOperation *Op = pBMPParam->m_Op;
	Document *DestDoc = pBMPParam->m_DestDoc;
	PathName Path = pBMPParam->file;
	INT32 FileNum = pBMPParam->m_FileNum;
	INT32 FileNumber = pBMPParam->m_FileNumber;
	DocCoord PosTranslate = pBMPParam->m_PosTranslate;
	BOOL IsCenter = pBMPParam->m_IsCenter;
	String_256 NewName = pBMPParam->m_FileName;

	// set the current document
	DestDoc->SetCurrent();

	// create a new undoable operation 
	// we can't import a bitmap without having a undoable op pointer
	SelOperation *Op = new SelOperation();

	// Tell the filter we're importing an HTML page
	HTMLFilter::ImportingHTML=TRUE;

	//Import the bitmap
	HTMLFilter::DoImportBitmap(TagId, Op, DestDoc, Path, FileNum, FileNumber, PosTranslate, IsCenter, &NewName);

	//And tell the filter we're no longer importing an HTML page
	HTMLFilter::ImportingHTML=FALSE;
	
	// End the op
	Op->End();

	// remove the temporary bitmap file
	remove((TCHAR*) (String_256) Path.GetPath());

}

/******************************************************************************************
>	virtual void DownloadOp::OnDownloadFail()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/01/97
	Inputs:		-
	Outputs:	- 
						
	Returns:	- 
	Purpose:	This function is called if the file download fails.

				It puts up a message that says "Webster could not download from the URL
				you typed"

******************************************************************************************/

void OpBitmapDownload::OnDownloadFail()
{
	//First get a pointer to the parameters
	BitmapDownloadParam* pBMPParam = (BitmapDownloadParam*) pParam;

	if (pBMPParam==NULL)
	{
		ERROR2RAW("OpBitmapDownload::OnDownloadFail - no download parameters");
		return;
	}

	//Get the URL which the user typed
	String_256 strURL=pBMPParam->strURL;

	//And put it up as a message
	String_256 strMessage;
	strMessage.MakeMsg(_R(IDS_HTML_DOWNLOADFAILED), &strURL);
	Error::SetError(0, strMessage, 0);
	InformError();
}

