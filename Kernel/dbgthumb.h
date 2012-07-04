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

#ifndef INC_URLIMPORTOP
#define INC_URLIMPORTOP

#include "impexpop.h"
#include "webaddr.h"

//GTODO: Take out permanently
//#include "selop.h"
//#include "bmpsdlg.h"
/********************************************************************************************

>	class OpURLImport : public OpMenuImport

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/97
	Purpose:	The "Import from URL..." menu item
	SeeAlso:	OpMenuExport

********************************************************************************************/

#define	OPTOKEN_URLIMPORT	_T("URLImport")

class OpURLImport : public OpMenuImport
{
	CC_DECLARE_DYNCREATE(OpURLImport)

public:
	OpURLImport();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);

protected:
	BOOL ImportURL(WebAddress urlToGet);
	Filter* GetAllFilter();



};


#endif // INC_URLIMPORTOP
