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

// clipboard mapping for native files declaration

#ifndef INC_CLIPMAP_H
#define INC_CLIPMAP_H

#include "clipmap.h"

/********************************************************************************************

>	class CMXClipMap : public ClipboardMapping

	Author:		Ben_Summers (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/09/96
	
	Purpose:	Clipboard mapping class for Native files -- wired into the
				system in winoil\clipext.cpp

	SeeAlso:	ClipboardMapping; ExternalClipboard; Filter

*********************************************************************************************/

class CCAPI NativeClipMap : public ClipboardMapping
{
CC_DECLARE_DYNCREATE(NativeClipMap)

friend class ExternalClipboard;
friend class OpClipboardExport;
friend class OpClipboardImport;

protected:
	NativeClipMap();
	NativeClipMap(ClipboardMappingType TheType, UINT32 ClaimType = 0);

public:			// Public method for constructing a mapping object
	static void CreateAndRegister(ClipboardMappingType TheType, UINT32 ClaimType = 0);
				// NOTE that we can register this for CF_TEXT, SF_UNICODETEXT, and CF_OEMTEXT, and it
				// will respond to any of these by asking for UNICODE text from the clipboard, which
				// will automatically do the conversion for us if necessary. 3 formats for the price of 1.

protected:		// Entry points for external clipboard manager
	virtual BOOL HandleImport(SelOperation *Caller, HANDLE ClipboardData, InternalClipboard *Dest);
			// Works out how to call the parent filter to import the given clipboard data
		
	virtual HANDLE HandleExport(Operation *Caller, InternalClipboard *Source);
			// Works out how to call the parent filter to export the given clipboard document

private:
	BOOL RemoveMultipleLayers(InternalClipboard *Dest);
			// This ensures that there is only one layer after an import into the given clipboard doc.
			// Objects that live in any extra layers are moved to the first layer, and the extra layers
			// are deleted.
};


#endif // INC_CLIPMAP_H

