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

#include "camtypes.h"
#include "opwhat.h"
//#include "opdesc.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ollie.h"
// #include "helpmgr.h"

// #include <winuser.h>

DECLARE_SOURCE("$Revision: 1282 $");  

CC_IMPLEMENT_DYNCREATE(OpWhatsThis, Operation)  

#define new CAM_DEBUG_NEW

     
// ------------------------------------------------------------------------------------------
// OpWhatsThis methods
    
/********************************************************************************************

>	OpWhatsThis::OpWhatsThis() 

	Author:		Ollie_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/11/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	OpWhatsThis constructor
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
            
            
OpWhatsThis::OpWhatsThis(): Operation()								
{                              
}

 /********************************************************************************************

>	BOOL OpWhatsThis::Init()

	Author:		Ollie_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/11/95
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if the operation could be successfully initialised 
				FALSE if no more memory could be allocated 
				
	Purpose:	OpWhatsThis initialiser method
	Errors:		ERROR will be called if there was insufficient memory to allocate the 
				operation.
	SeeAlso:	-

********************************************************************************************/

BOOL OpWhatsThis::Init()
{
	return (RegisterOpDescriptor(0,										// Module (Tool) ID
	 							_R(IDS_WHATSTHISOP),						// String resource ID
								CC_RUNTIME_CLASS(OpWhatsThis),			// Ops runtime class
	 							OPTOKEN_WHATSTHIS,						// Optoken ID
	 							OpWhatsThis::GetState,					// Pointer to the GetState function
	 							0,	/* help ID */						// help identifier
	 							_R(IDBBL_WHATSTHIS),						// string resource for bubble help
	 							0,										// resource ID
	 							0,										// control ID
								SYSTEMBAR_ILLEGAL,						// group bar ID
								TRUE, 									// Receive messages
								FALSE,
								FALSE,
								0,
								0
								 )); 
}               

/********************************************************************************************

>	OpState	OpWhatsThis::GetState(String_256*, OpDescriptor*)

	Author:		Ollie_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/11/95
	Inputs:		-
	Outputs:	-
	Returns:	The state of the OpWhatsThis
	Purpose:	For finding the OpWhatsThis' state.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

OpState	OpWhatsThis::GetState(String_256* UIDescription, OpDescriptor*)
{
	OpState OpSt;
		
	OpSt.Greyed = FALSE;

	return(OpSt);  				  // isn't this returning a local variable????????
}

/********************************************************************************************

>	void OpWhatsThis::Do(OpDescriptor*)

	Author:		Ollie_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/11/95
	Inputs:		OpDescriptor (unused)
	Outputs:	-
	Returns:	-
	Purpose:	Puts Camelot into the "What's This?" help mode.
	Errors:		dunno yet 
	SeeAlso:	-

********************************************************************************************/

void OpWhatsThis::Do(OpDescriptor*)
{
	MessageBox(NULL, "Not implemented","Message", MB_OK );

	// Selecting this op drops the program into a mode where clicking on anything in
	// the program elicits help on it. The pointer should change when the program
	// is in this mode.
	
#ifdef _DEBUG
	TRACEUSER( "Ollie", _T("What's This Operation -> Do it!\n"));
#endif

	// Send a WM_HELP to a greyed button.
	// ?????
	
	// Drop into the context sensitive help mode.
	// BOOL Succeeded = HelpManager::EnterHelpMode();
	
	End();
}  
     
