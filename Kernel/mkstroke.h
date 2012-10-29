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
 * */
   
#ifndef INC_MKSTROKE
#define INC_MKSTROKE 


#define OPTOKEN_MAKE_STROKE _T("ConvertToStroke")
   
/********************************************************************************************

>	class OpMakeStroke : public SelOperation

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/03/97
	Purpose:	This class represents the MakeStroke operation.

********************************************************************************************/

class CCAPI OpMakeStroke: public SelOperation
{         

	CC_DECLARE_DYNCREATE( OpMakeStroke )    

public:
	OpMakeStroke();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};  
 

#endif 
