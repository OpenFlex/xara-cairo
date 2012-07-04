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


// Declaration of the following classes
/*
	BlobbyOp         : Demonstration temporary operation which changes the colour of a 
					   documents paper. 
					   and it's actions

*/	



/*
 */        

#ifndef INC_STDBARS
#define INC_STDBARS
    
//#include "undoop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "opdesc.h"    - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ops.h"  	   	// Operation class   - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "dlgtypes.h"  	// The DialogOp types - in camtypes.h [AUTOMATICALLY REMOVED]
#include "dlgmgr.h"		// the dialogue box manager 
//#include "convert.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "bars.h" - in camtypes.h [AUTOMATICALLY REMOVED]

// -----------------------------------------------------------------------------------------
// StandardBar used to test the Dialog system


/*******************************************************************************************

>	class StandardBar : public DialogBarOp

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	17/12/2005
	Purpose:	A class implementing "fixed content" bars
	Notes:		In the OIL
	See Also:	

********************************************************************************************/

class StandardBar: public DialogOp
{
	CC_DECLARE_DYNCREATE( StandardBar )  
public:

	StandardBar() : DialogOp ( (ResourceID) 0, MODELESS) {m_Vertical = FALSE; m_pOpDesc = NULL;}
 
	virtual MsgResult Message( Msg* Msg );  
	void Do(OpDescriptor* pOpDesc);
	static BOOL Init();
	BOOL Create(ResourceID dlg); 

	BOOL IsABar() {return TRUE;}
	BOOL IsVertical() {return m_Vertical;}

	BOOL m_Vertical;
	OpDescriptor * m_pOpDesc;

	static OpState GetState(String_256*, OpDescriptor *pOpDesc);
	static void BroadcastClose(OpDescriptor* pOpDesc);
}; 



#endif
