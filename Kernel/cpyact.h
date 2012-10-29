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

/*
*/
// CopyObjectsToClipboardAction action definition

#ifndef INC_CPYACT
#define INC_CPYACT

/********************************************************************************************

>	class CopyObjectsToClipboardAction: public Action

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/9/93
	Purpose:	When executed as an undo action nothing happens except for the creation of a 
				redo CopyObjectsToClipboardAction.

				When executed as a redo all selected objects are copied to the clipboard
	
	SeeAlso:	-

********************************************************************************************/


class CCAPI CopyObjectsToClipboardAction: public Action
{                                
	CC_DECLARE_DYNCREATE( CopyObjectsToClipboardAction )

public:
	CopyObjectsToClipboardAction(); 
	~CopyObjectsToClipboardAction();

	virtual ActionCode Execute();  
	static ActionCode Init(Operation* const pOp, 
						   ActionList* pActionList, 
						   Range NodeRange, 
						   Action** NewAction); 
private:
		
	Range NodeRange; 	  // The range of nodes to copy 
};   

#endif
