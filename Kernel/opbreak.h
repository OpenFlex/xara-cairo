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

// Definition of the op break at points classes

#ifndef INC_OPBREAK
#define INC_OPBREAK

//#include "selop.h"

#define OPTOKEN_BREAKATPOINTS _T("BreakAtPoints")


/********************************************************************************************

>	class OpBreakAtPoints : public SelOperation

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/8/94
	Purpose:	This class will break paths at selected points.
				The effect of this will be to either open a closed path or split
				a open path into two subpaths, or both dependent on the number of
				selected points in the path. 
				There must be at least one selected point for this operation to
				complete correctly.
	SeeAlso:	-

********************************************************************************************/

class OpBreakAtPoints: public SelOperation
{         

	CC_DECLARE_DYNCREATE( OpBreakAtPoints )    

public:
	OpBreakAtPoints();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void 			GetOpName(String_256* OpName);
	void			Do(OpDescriptor*);	

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};



#endif
