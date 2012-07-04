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


// Undoable Operations for plug-ins

#ifndef INC_BFXPLUGINUNDOOP
#define INC_BFXPLUGINUNDOOP

#include "plugopun.h"

class Spread;

/********************************************************************************************

>	class BfxPlugInUndoOp : public PlugInUndoOp

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/3/97
	Purpose:	Undoable Operation so that a Bfx plug-ins can be invoked and used.  

********************************************************************************************/				

//#define OPTOKEN_Bfx_UNDO_PLUGINS		"UndoBfxPlugIns"
//#define OPTOKEN_Bfx_UNDO_APPLYLAST	"UndoBfxApplyLast"

class BfxPlugInUndoOp : public PlugInUndoOp
{
	CC_DECLARE_DYNCREATE( BfxPlugInUndoOp );

public:
	BfxPlugInUndoOp();

	virtual void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);	

protected:
	static BOOL CheckBitmapWithPlugIn(const String_256& OpName, KernelBitmap * pBitmap,
									  BOOL IncludeUniqueName = TRUE, BOOL IncludeUndoAbleSig = FALSE);
};


#endif // INC_BFXPLUGINUNDOOP
