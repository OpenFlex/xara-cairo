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


//	WEBSTER-ranbirr-13/11/96
#ifndef WEBSTER

#ifndef INC_PRINTING
#define	INC_PRINTING


#define	 OPTOKEN_PRINT			_T("Print")
#define	 OPTOKEN_PRINT_SETUP	_T("PrintSetup")
#define	 OPTOKEN_PRINT_PREVIEW	_T("PrintPreview")

/********************************************************************************************

>	class OpPrint : public Operation

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/8/93
	Purpose:	This class represents all the Printing operations.
	SeeAlso:	OpPrint

********************************************************************************************/

class OpPrint : public Operation
{
	CC_DECLARE_DYNCREATE( OpPrint )
	
public:

	OpPrint();	                                    // Constructor
	static BOOL Init();                       		// Register an OpDescriptor
	                                                // Read the state of an operation
	static OpState GetState(String_256*, OpDescriptor*);
	void Do(OpDescriptor*);                    		// "Do" function
    
    static void Deinitialise() {}
};


#endif

#endif //webster
