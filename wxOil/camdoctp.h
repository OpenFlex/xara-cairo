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


/*
 *  */

#ifndef INC_CAMDOCTP
#define INC_CAMDOCTP


/********************************************************************************************
>	class CCamDocTemplate : public CMultiDocTemplate

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	sometime in '93 (sorry!)
	Purpose:	Allows the customisation of the process MFC uses to create, load,
				and associate its view and document classes.
	SeeAlso:	CCamDoc; CCamMDIChild; CCamView
********************************************************************************************/

class CCamDocTemplate : public wxDocTemplate
{
	DECLARE_CLASS(CCamDocTemplate)

public:
	enum Confidence
	{
		noAttempt,
		maybeAttemptForeign,
		maybeAttemptNative,
		yesAttemptForeign,
		yesAttemptNative,
		yesAlreadyOpen
	};

public:
	CCamDocTemplate( wxDocManager* pManager, const wxString& descr, const wxString& filter, 
		const wxString& dir, const wxString& ext, const wxString& docTypeName, 
		const wxString& viewTypeName, wxClassInfo* docClassInfo, wxClassInfo* viewClassInfo );
	#ifndef _MAC
		virtual Confidence MatchDocType(LPCTSTR lpszPathName, wxDocument*& rpDocMatch);
	#else
		virtual Confidence MatchDocType(LPCTSTR lpszFileName, DWORD dwFileType,
										wxDocument*& rpDocMatch);
	#endif
};

#endif
