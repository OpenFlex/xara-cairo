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
#include "camdoc.h"
#include "camelot.h"
#include "lddirect.h"

CC_IMPLEMENT_MEMDUMP(LoadDirect, CC_CLASS_MEMDUMP);

DECLARE_SOURCE("$Revision: 1320 $");


/*****************************************************************************************

>	BOOL LoadDirect::Execute(const TCHAR* lpszFilename)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/08/96
	Inputs:		lpszFilename = the filename of the document to load.
	Outputs:	-
	Returns:	TRUE if the document was loaded correctly
				FALSE if not
				either (1) theres no application present (unlikely)
				       (2) unable to find the named file to load
					   (3) unable to load the named file due to error
					   (4) there was no kernel document resulting from the load
					   (5) the users OnLoadDocument returned an error

	Purpose:	Execute the action of loading a named document, calling a subclass
				virtual function 'OnLoadDocument' and killing the loaded document.
				The selected document and view will be retained by this function
	
	Notes:		This all works via the MFC. It is impossible to load and format a 
				native document without such things as cam views, doc view, ruler, doc
				scaling objects, doc status objects etc. All format and rendering
				of objects requires this plethora of structures to be present. Hence
				we simulate an MFC OnLoadDocument without actually opening the created
				view in order to do this.


*****************************************************************************************/

BOOL LoadDirect::Execute(const TCHAR* lpszFilename)
{
	// find our main application object
	CCamApp	*pApp = (CCamApp*)&AfxGetApp();
	if (!pApp)
		return FALSE;

	// Recode the currently selected document, view and spread
	Document	*OldSelDocument	= Document::GetSelected();
	DocView		*OldSelView		= DocView::GetSelected();
	Spread		*OldSelSpread	= Document::GetSelectedSpread();

	// call the loader
	BOOL ok = ExecuteHelper(pApp, lpszFilename);

	// reset the previous selected state.
	if (OldSelDocument != NULL)
		Document::SetSelectedViewAndSpread(OldSelDocument,OldSelView,OldSelSpread);

	// return the user state.
	return ok;
}


/*****************************************************************************************

	BOOL LoadDirect::ExecuteHelper(CCamApp* pApp, const TCHAR* lpszFilename)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/08/96
	Inputs:		lpszFilename = the filename of the document to load.
	Outputs:	-
	Returns:	TRUE if the document was processed correctly
				FALSE if not
	Purpose:	Helps out by conditioning its parent. ie, by making the parent routine
				less complex in its condition paths.
	
*****************************************************************************************/

BOOL LoadDirect::ExecuteHelper(CCamApp* pApp, const TCHAR* lpszFilename)
{
	BOOL ok=TRUE;

	PORTNOTETRACE("other", "Disabled LoadDirect::ExecuteHelper");
#ifndef EXCLUDE_FROM_XARALX

	// now call the supporting open document function
	CDocument* pLoadDirectDoc = pApp->OpenHiddenDocument(lpszFilename);
	if (pLoadDirectDoc==NULL)
		return FALSE;

	// assume its a cam doc we have created, and find its kernel doc
	CCamDoc* pCamDoc = (CCamDoc*)pLoadDirectDoc;
	Document* pRealDoc = pCamDoc->GetKernelDoc();

	// call the user function for document decoding
	ok = (pRealDoc!=NULL);
	ok = ok && (OnLoadDocument(pRealDoc));

	// finally toast the loaded document. 
	pCamDoc->SetModified(FALSE);
	pCamDoc->OnCloseDocument();
#endif

	return ok;
}




/*****************************************************************************************

>	BOOL LoadDirect::OnLoadDocument(Document* pKernelDoc)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/08/96
	Inputs:		pKernelDoc = a pointer to the loaded kernel document
	Outputs:	-
	Returns:	TRUE if the document was processed correctly
				FALSE if not

	Purpose:	Having successfully loaded the document, this function will be called to
				process the loaded data. The kernel document can be used to scan the
				document tree and perform any actions necessary. On return from this
				function the calling framework will delete the document and all its
				associated structures.
	
*****************************************************************************************/

BOOL LoadDirect::OnLoadDocument(Document* pKernelDoc)
{
	ERROR3("The base class LoadDirect::OnLoadDocument() has been called, where's your derived class?");
	return FALSE;
}


