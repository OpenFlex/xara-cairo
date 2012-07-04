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
#include "camdoctp.h"			// document template
#include "camdoc.h"				// document
//#include "ccmdikid.h"			// view frame
//#include "scrcamvw.h"  			// screen view
#include "appstate.h"
#include "errors.h"
//#include "mfccopy.h"
#include "camelot.h"
#include "clipint.h"

IMPLEMENT_CLASS(CCamDocTemplate, wxDocTemplate);
DECLARE_SOURCE("$Revision: 25 $");



CCamDocTemplate::CCamDocTemplate( wxDocManager* pManager, const wxString& descr, const wxString& filter, 
		const wxString& dir, const wxString& ext, const wxString& docTypeName, const wxString& viewTypeName, 
		wxClassInfo* docClassInfo, wxClassInfo* viewClassInfo )
 : wxDocTemplate( pManager, descr, filter, dir, ext, docTypeName, viewTypeName, docClassInfo, viewClassInfo )
{
#if 0
	if (m_hMenu != NULL)
	{
		::DestroyMenu(m_hMenuShared);
		m_hMenuShared = m_hMenu;
	}
		
	if (m_hAccelTable != NULL)
		m_hAccelTable = m_hAccelTable;
	
	#ifdef _DEBUG
		// warnings about missing components (don't bother with accelerators)
		if (m_hMenuShared == NULL)
			TRACE1("Warning: no shared menu for document template #%d\n", nIDResource);
	#endif //_DEBUG

#if _MFC_VER >= 0x400
	// Strangeness we need to do here to create the DocManager as our derived version instead
	// of MFC's version, so we can over-ride DoPromptFilename() - see mfccopy.cpp/h. (Tim)
	// This code fragment taken from mfc\src\doctempl.cpp (MFC4).

	// Er, Richard here... Defining _AFXDLL and using the MD version of MFC seems not to
	// contain this bStaticInit stuff. This needs looking into...
	if (CDocManager::bStaticInit)
	{
		if (CDocManager::pStaticDocManager == NULL)
			CDocManager::pStaticDocManager = new CamelotDocManager;
	}
#endif // _MFC_VER >= 0x400
#endif
}



/********************************************************************************************

>	CDocTemplate::Confidence CCamDocTemplate::MatchDocType(LPCTSTR lpszPathName, CDocument*& rpDocMatch)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/5/95
	Purpose:	This function has been overiden from its MFC version. It is actually
				identical apart from the bit that checks to see if the document is already
				open. The MFC version of the function goes and looks at the files involved
				by calling AfxComparePaths(), but we just compare the paths. This stops the
				floppy drive from being accessed all the time if you have a document opened
				from a floppy drive (it also stops network problems if the conection to
				an open document goes away). I am not too sure what all the params mean.

********************************************************************************************/

#ifndef _MAC
CCamDocTemplate::Confidence CCamDocTemplate::MatchDocType(LPCTSTR lpszPathName, wxDocument*& rpDocMatch)
#else
CCamDocTemplate::Confidence CCamDocTemplate::MatchDocType(LPCTSTR lpszPathName, DWORD dwFileType,
													   wxDocument*& rpDocMatch)
#endif
{
	ASSERT(lpszPathName != NULL);
	rpDocMatch = NULL;

	// go through all documents
	wxList&				listDocuments = GetDocumentManager()->GetDocuments();
	wxNode*				pNode = listDocuments.GetFirst();
	while (pNode != NULL)
	{
		// Get the next document
		CCamDoc* pDoc = (CCamDoc*)pNode->GetData();

	#if (_OLE_VER >= 0x200)
		// Don't consider embedded or hidden docs.
		if (pDoc->IsEmbedded() || pDoc->GetKernelDoc()->IsAHiddenDoc()) continue;
	#endif

		// Find out the names of the old and new documents
		wxString OldDocName  = pDoc->GetFilename();
		wxString OrigDocName = wxString((LPCTSTR) pDoc->GetOriginalPath());
		wxString NewDocName  = wxString(lpszPathName);
		OldDocName.MakeLower();
		OrigDocName.MakeLower();
		NewDocName.MakeLower();

		// Test if the docs refer to the same existing .ART file or if the two docs are based
		// on the same existing non-.ART file.
		BOOL fSameArtFiles = (OldDocName == NewDocName);
		BOOL fSameNonArtFiles = (OldDocName.IsEmpty() && OrigDocName == NewDocName);

		// see if they are the same
		if (fSameArtFiles || fSameNonArtFiles)
		{
			// already open
			TRACEUSER("JustinF", _T("File %s is already open\n"),  (LPCTSTR) lpszPathName);
			rpDocMatch = pDoc;
			return yesAlreadyOpen;
		}

		pNode = pNode->GetNext();
	}

	// see if it matches our default suffix
	if( !m_defaultExt.IsEmpty() )
	{
		// see if extension matches
		LPCTSTR			lpszDot = camStrrchr( lpszPathName, _T('.') );
		if( NULL != lpszDot && 
			0 == camStricmp( lpszDot + 1, m_defaultExt ) )
			return yesAttemptNative; // extension matches, looks like ours
	}

	// otherwise we will guess it may work
	return yesAttemptForeign;
}
