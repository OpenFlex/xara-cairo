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

// A action class for the arbitary region invalidation

#ifndef INC_INVALID
#define INC_INVALID


//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************************************

>	class InvalidateArbitaryAction : public Action

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/8/94
	Purpose:	When executed this action will Force a redraw of the bounding rectangle it
				contains

********************************************************************************************/

class CCAPI InvalidateArbitaryAction : public Action
{                                
	CC_DECLARE_DYNCREATE(InvalidateArbitaryAction)

public:
	// Constructor
	InvalidateArbitaryAction(); 
	
	// The function that initialises and builds a new invalidate action
	static ActionCode Init(Operation* const pOp, ActionList* pActionList, Spread* pSpread, 
						   const DocRect& InvalidRect, Action** NewAction);

	// Actually do the invalidating and undo/redo stuff
	virtual ActionCode Execute();   

	// Access functions to enable op/action merging
	Spread* GetSpread() const {return pSpread;}
	DocRect GetRect() const {return InvalidRect;}
	void SetRect(DocRect NewRect) {InvalidRect = NewRect;}

// member vars
protected:
	Spread* pSpread;
	DocRect InvalidRect;
};

#endif  // INC_INVALID


