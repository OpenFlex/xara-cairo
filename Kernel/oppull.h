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

// Definition of the op nudge classes

#ifndef INC_PULL
#define INC_PULL

#include "tranlate.h"

#define OPTOKEN_PULLONTOGRID _T("PullOntoGrid")

/********************************************************************************************

>	class OpPullOntoGrid : public OpTranslateTrans

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/03/95
	Purpose:	Translate the selection so that one of it's corners lies on the grid.

********************************************************************************************/

class OpPullOntoGrid : public OpTranslateTrans
{
CC_DECLARE_DYNCREATE(OpPullOntoGrid);

public:
	static BOOL    Init();
	static OpState GetState(String_256*, OpDescriptor*);

	// Do() will nudge each selected object by GetXNudgeDisplacement() in the x direction
	// and GetYNudgeDisplacement in the y direction
	virtual void Do(OpDescriptor* pOpDesc);

};

#endif  // INC_PULL


