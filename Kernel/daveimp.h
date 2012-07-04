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


// The operation for the "Import from URL..." menu item

#ifndef INC_BEVEL
#define INC_BEVEL

#include "impexpop.h"
#include "webaddr.h"

class DaveDlg;

/********************************************************************************************

>	class OpBevel : public OpMenuImport

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29-7-98
	Purpose:	testing
	SeeAlso:	

********************************************************************************************/

#define	OPTOKEN_BEVEL	_T("DavesBevelling")

class OpBevel : public OpMenuImport
{
	CC_DECLARE_DYNCREATE(OpBevel)

public:
	OpBevel();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);

protected:
	BOOL ImportURL(WebAddress urlToGet);
	Filter* GetAllFilter();

	DaveDlg *m_pDlg;
	
	
};


#endif // INC_DAVETEST
