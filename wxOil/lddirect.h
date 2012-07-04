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

// Cool class to load a native document directly from code.

#ifndef INC_LOADDIRECT
#define INC_LOADDIRECT

class Document;
class CCamApp;

/*****************************************************************************************

>	class LoadDirect : public CC_CLASS_MEMDUMP

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/08/96
	Purpose:	This class allows the caller to load a xara document in, process the
				data held inside and close the document again. You should derive your
				own class and override the OnLoadDocument() function. You'll be given
				a CCamDoc and Document* which can be used to access data within the
				doc. On return from OnLoadDocument, the document will be destroyed.

*****************************************************************************************/

class LoadDirect : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(LoadDirect);

	public:
        virtual ~LoadDirect() {}
		BOOL Execute(const TCHAR* lpszFilename);

	protected:
		virtual BOOL OnLoadDocument(Document* pKernelDoc);

	private:
		BOOL ExecuteHelper(CCamApp* pApp, const TCHAR* lpszFilename);

};


#endif
