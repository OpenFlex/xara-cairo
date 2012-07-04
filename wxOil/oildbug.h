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


#ifndef INC_OILDBUG
#define INC_OILDBUG

#include "dlgmgr.h"

/********************************************************************************************

>	class DebugTreeInfo

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/06/94
	Purpose:	Encapsulates the platform dependent parts of the debug tree dialog.
				It provides a simple way of linking a datum to a particular item in the
				debug tree dialog's list box.
				This kind of facility can often be supported by the GUI, hence it is in
				the OIL layer.
	SeeAlso:	DebugTreeInfo::AddDebugInfo; DebugTreeInfo::GetDebugInfo

********************************************************************************************/

class DebugTreeInfo
{
public:
	DebugTreeInfo(CWindowID NewID) { WindowID = NewID; }
	~DebugTreeInfo() {}

	BOOL Init() { return TRUE; }

	void AddDebugInfo(INT32 Index, void *Ref);

	void RemoveDebugInfo(INT32 Index) {}

	void *GetDebugInfo(INT32 Index);

	void OutputDebugLine(TCHAR *);

	static void OutputDebug(TCHAR *);

private:
	CWindowID WindowID;
};

#endif
