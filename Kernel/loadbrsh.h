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


// Load default brushes on start-up - Header


#ifndef INC_LOADBRUSH
#define INC_LOADBRUSH

#include "lddirect.h"

class Document;
class CCamApp;

/*****************************************************************************************

>	class LoadBrushDirect : public LoadDirect

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/3/2000
	Purpose:	Class is used to load a document containing the default brushes on startup.
				Most of the action takes place in the base class.
*****************************************************************************************/

class LoadBrushDirect : public LoadDirect
{
	CC_DECLARE_MEMDUMP(LoadBrushDirect);

	protected:
		virtual BOOL OnLoadDocument(Document* pKernelDoc);
};

#endif
