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

//
// SelAll.h
//
// Header for Operations to Select All and Select none
//

#ifndef INC_EDITSEL
#define INC_EDITSEL


// Op Tokens
#define OPTOKEN_EDIT_EDITSELECTION	_T("EditSelection")




/******************************************************************************************

>	class EditSelectionOp : public Operation

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/5/94
	Purpose:	The Select All operation.
	SeeAlso:	Operation

******************************************************************************************/

class CCAPI EditSelectionOp: public Operation
{

	CC_DECLARE_DYNCREATE( EditSelectionOp )

public:
	EditSelectionOp();							// Constructor

	static BOOL		Init();					// Register an OpDescriptor
	                                        // Read the state of an operation
	static OpState	GetState(String_256*, OpDescriptor*);		

	void			Do(OpDescriptor*);		// "Do" function

};

#endif // INC_EDITSEL
