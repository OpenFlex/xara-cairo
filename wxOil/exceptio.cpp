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


// OpException class used to test exception handling code.



#include "camtypes.h"
#include "exceptio.h"
//#include "andy.h"
//#include "alex.h"



LPBYTE OpException::lpByte = NULL;
INT32 OpException::iZero[2];
double OpException::dZero[2];
BOOL OpException::RenderTrap = FALSE;
static BYTE GlobalByte;


CC_IMPLEMENT_DYNCREATE(OpException, Operation)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/*******************************************************************

>	void OpException::Do(OpDescriptor*)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/10/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Creates various types of exceptions to verify exception handling.
	Errors:		-

*******************************************************************/


void OpException::Do(OpDescriptor* WhichOp)
{
	if (WhichOp->Token == String( OPTOKEN_EXCEPTION_PTR) )
		GlobalByte = *lpByte;
	else if (WhichOp->Token == String( OPTOKEN_EXCEPTION_INT ) )
		iZero[1] = 1 / iZero[0];
	else if (WhichOp->Token == String( OPTOKEN_EXCEPTION_DBL ) )
		dZero[1] = 1 / dZero[0];									
	else
	{
		DocView *pDocView = DocView::GetSelected();
		if (pDocView != NULL)
		{
			pDocView->ForceRedraw();										// posts the paint message
			CWindowID pWnd = DocView::GetCurrentRenderWindow();
			if (pWnd)
			{
				// Set trap for later
				RenderTrap = TRUE;										
				// Now do the paint
				TRACE( _T("Into update explosion\n"));
				pWnd->Update();										// do the paint
				TRACE( _T("Out of update explosion\n"));
			}
		}
	}
}


/*******************************************************************

>	OpException::OpException()

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/10/93
	Inputs:
	Outputs:
	Returns:
	Purpose:	Constructor for OpException operation. It is not undoable.
	Errors:		None

*******************************************************************/

OpException::OpException()
{
}



/*******************************************************************

>	OpState OpException::GetState(String_256*, OpDescriptor*)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/10/93
	Inputs:
	Outputs:
	Returns:
	Purpose:	This item is always available.
	Errors:		None

*******************************************************************/

OpState OpException::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;

	return OpSt;
}


/*******************************************************************

>	BOOL OpException::Init()

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/10/93
	Inputs:
	Outputs:
	Returns:	TRUE if worked, FALSE if not.
	Purpose:	This item is always available.
	Errors:		Uses SetError if fails.
	Scope:		Static

*******************************************************************/

BOOL OpException::Init()
{

	OpDescriptor *OpEx[4];
	
	OpEx[0] = new OpDescriptor(	0,
							_R(IDM_CRASHME_PTR),
							CC_RUNTIME_CLASS(OpException),
							OPTOKEN_EXCEPTION_PTR,
							OpException::GetState
											);

	OpEx[1] = new OpDescriptor(
							0,
							_R(IDM_CRASHME_INT),
							CC_RUNTIME_CLASS(OpException),
							OPTOKEN_EXCEPTION_INT,
							OpException::GetState
											);

	OpEx[2] = new OpDescriptor( 
							0,
							_R(IDM_CRASHME_DBL),
							CC_RUNTIME_CLASS(OpException),
							OPTOKEN_EXCEPTION_DBL,
							OpException::GetState
											);

	OpEx[3] = new OpDescriptor( 
							0,
							_R(IDM_CRASHME_REN),
							CC_RUNTIME_CLASS(OpException),
							OPTOKEN_EXCEPTION_REN,
							OpException::GetState
											);


	if (!( OpEx[0] && OpEx[1] && OpEx[2] && OpEx[3]))
		return FALSE;

	return TRUE;
}
