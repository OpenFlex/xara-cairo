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

// Definition of the op smooth classes

/*
*/

#ifndef INC_OPSMOOTH
#define INC_OPSMOOTH


#define OPTOKEN_SMOOTHSELECTION _T("SmoothSelection")
#define SMOOTH_CONSTANT 27000000

/********************************************************************************************

>	class OpSmoothSelection : public SelOperation

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/10/94
	Purpose:	This class will smooth paths between selected control point regions.
				It processes all selected objects within the current document.
	SeeAlso:	-

********************************************************************************************/

class OpSmoothSelection: public SelOperation
{

	CC_DECLARE_DYNCREATE( OpSmoothSelection )    

public:
	OpSmoothSelection();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void 			GetOpName(String_256* OpName);
	void			Do(OpDescriptor*);	
};


#endif

