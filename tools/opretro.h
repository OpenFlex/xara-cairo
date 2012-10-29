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

// Header file for the Freehand Retro Fitting Operation

#ifndef INC_OPRETRO
#define INC_OPRETRO


class OpState;
class NodePath;

#define OPTOKEN_RETROFIT _T("RetroFit")




/********************************************************************************************

>	class OpRetroFit : public SelOperation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/5/94
	Purpose:	This operation handles the updating of a freehand path after it has
				been retro fitted

********************************************************************************************/

class OpRetroFit : public SelOperation
{
CC_DECLARE_DYNCREATE(OpRetroFit);

public:
	// Construction/Destruction
	OpRetroFit() {}

	// A function that I have added in order to get information into the operation
	BOOL BuildUndo(NodePath*, NodePath*);

	// The Do Function that performs the actual operation
	void Do(OpDescriptor* pOp);
		
	// These functions required for the OpDescriptor class
	static BOOL Init();
	static OpState GetState(String_256* Description, OpDescriptor*);
};



#endif	// INC_OPRETRO
