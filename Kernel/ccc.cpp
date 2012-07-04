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

// Implementation file for the ConcurrencyController

#include "camtypes.h"
#include "ccc.h"
#include "gdrawasm.h"

// Place any IMPLEMENT type statements here

CC_IMPLEMENT_MEMDUMP(ConcurrencyController, CC_CLASS_MEMDUMP)
//CC_IMPLEMENT_MEMDUMP(CriticalSection, CC_CLASS_MEMDUMP)

// We want better memory tracking
#define new CAM_DEBUG_NEW

// Change this so TRACEUSERs work for you
#define ME	"Colin"

// Ooh Er! Static Members

ConcurrencyController::UserID ConcurrencyController::s_NextFreeUserID = 0;
ConcurrencyController::UserID ConcurrencyController::s_OneAndOnlyUser = 0;
UINT32 ConcurrencyController::s_NumberOfUsers = 0;

UINT32 ConcurrencyController::s_NumberOfActiveOperations = 0;
const Operation* ConcurrencyController::s_pTheActiveOperation = NULL;

// Functions follow



/********************************************************************************************

>	ConcurrencyController::ConcurrencyController() 

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/03/97

	Purpose:	Default constructor for the ConcurrencyController

********************************************************************************************/
ConcurrencyController::ConcurrencyController() 
{
}

BOOL ConcurrencyController::Init()
{
//	CriticalSection::Init();

	return TRUE;
}

/********************************************************************************************

>	ConcurrencyController::~ConcurrencyController() 

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/03/97

	Purpose:	Default destructor for the ConcurrencyController

********************************************************************************************/
ConcurrencyController::~ConcurrencyController() 
{
	if (s_NumberOfUsers > 1)
	{
		TRACEUSER( ME, _T("ConcurrencyController: Users still active\n"));
	}
//	CriticalSection::DeInit();
}


/********************************************************************************************

>	ConcurrencyController::RESULT ConcurrencyController::StartUser(UserID* pNewUserID)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/03/97

	Purpose:	Default destructor for the ConcurrencyController

********************************************************************************************/
ConcurrencyController::RESULT ConcurrencyController::StartUser(UserID* pNewUserID)
{
	RESULT Result = CCR_OK;

	CriticalSection UpdateUserID;
//	UpdateUserID.Start();

	if (s_NumberOfUsers == 0)
	{
		UserID NewUserID = GetNewUserID();
		if (NewUserID != NULL)
		{
			++s_NumberOfUsers;
		}
		else
		{
			Result = CCR_TOO_MANY_USERS;
		}
		*pNewUserID = NewUserID;
	}
	else
	{
		Result = CCR_TOO_MANY_USERS;
	}
//	UpdateUserID.End();

	return Result;
}

	
/********************************************************************************************

>	ConcurrencyController::RESULT ConcurrencyController::EndUser(UserID UserWhosDone)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/03/97

	Purpose:	Default destructor for the ConcurrencyController

********************************************************************************************/
ConcurrencyController::RESULT ConcurrencyController::EndUser(UserID UserWhosDone)
{
	RESULT Result = CCR_OK;

	CriticalSection UpdateUserID;
//	UpdateUserID.Start();

	if (UserWhosDone == s_OneAndOnlyUser)
	{
		s_OneAndOnlyUser = NULL;
		--s_NumberOfUsers;
	}
	else
	{
		Result = CCR_INVALID_USER;
	}

//	UpdateUserID.End();

	return Result;
}


/********************************************************************************************

>	ConcurrencyController::RESULT ConcurrencyController::PrepareForOperation(
															const Operation* const pOperation)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/03/97

	Purpose:	Allows or disallows access to Operations.

	Notes:		En ce moment only one op is allowed per application (static scope)

********************************************************************************************/
ConcurrencyController::RESULT ConcurrencyController::PrepareForOperation(
														const Operation* const pOperation)
{
	RESULT Result = CCR_OK;

	CriticalSection UpdateOpTable;
//	UpdateOpTable.Start();

	if (s_NumberOfActiveOperations == 0)
	{
		ERROR2IF(s_pTheActiveOperation != NULL, CCR_INTERNAL_ERROR, "ActiveOp not NULL");
		
		s_pTheActiveOperation = pOperation;
		++s_NumberOfActiveOperations;
	}
	else
	{
		Result = CCR_TOO_MANY_USERS;
	}
//	UpdateOpTable.End();

	return Result;
}


/********************************************************************************************

>	ConcurrencyController::RESULT ConcurrencyController::FinalizeOperation(
														const Operation* const pOperation)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/03/97

	Purpose:	Default destructor for the ConcurrencyController

********************************************************************************************/
ConcurrencyController::RESULT ConcurrencyController::FinalizeOperation(
														const Operation* const pOperation)
{
	RESULT Result = CCR_OK;

	CriticalSection UpdateOpTable;

	if (pOperation == s_pTheActiveOperation)
	{
		ERROR2IF(s_NumberOfActiveOperations != 1, CCR_INTERNAL_ERROR, "ActiveOps not Unity");

		s_pTheActiveOperation = NULL;
		--s_NumberOfActiveOperations;
	}
	else
	{
		Result = CCR_INVALID_ARGUMENT;
	}

	return Result;
}


/*********************************************************************************************
           
>	ConcurrencyController::RESULT ConcurrencyController::PrepareNodeForUpdate(Node* const pNode)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/02/97

	Inputs:		pNode:	The node to be updated
	Returns:	TRUE if the node can be updated
		FALSE otherwise
	Purpose:	Before updating a node, call this function to ensure the integrity of the 
		document tree.
		This call should be accompanied by a subsequent call to FinalizeNodeUpdate().
		The results of the update are undefined if not.
	See Also:	PrepareNodeForRead()
	
**********************************************************************************************/  
ConcurrencyController::RESULT ConcurrencyController::PrepareNodeForUpdate(Node* const pNode);


/*********************************************************************************************
           
>	ConcurrencyController::RESULT ConcurrencyController::FinalizeNodeUpdate(Node* const pNode)

	Author:	Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/02/97

	Inputs:	pNode:	The node passed in a prior call to PrepareNodeForUpdate()
	Returns:	TRUE if the node was successfully updated
		FALSE otherwise
	Purpose:	Once the given node has been updated in the tree call this function to ensure
		its update is complete.
		This call should be accompanied by a prior call to PrepareForNodeUpdate(). The
		results of the update are undefined if not.
	See Also:	FinalizeNodeRead()
	
**********************************************************************************************/  
ConcurrencyController::RESULT ConcurrencyController::FinalizeNodeUpdate(Node* const pNode);


/*********************************************************************************************
           
>	ConcurrencyController::RESULT ConcurrencyController::PrepareNodeForRead(Node* const pNode)

	Author:	Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/02/97

	Inputs:	pNode:	The node to be read
	Returns:	TRUE if the node can be read
		FALSE otherwise
	Purpose:	Before reading data in a node or passing it as a parameter to a function,
		call this function to ensure the integrity of the document tree.
		This call should be accompanied by a subsequent call to FinalizeNodeRead().
		The results of the read are undefined if not.
	See Also:	PrepareNodeForUpdate()
	
**********************************************************************************************/  
ConcurrencyController::RESULT ConcurrencyController::PrepareNodeForRead(Node* const pNode);


/*********************************************************************************************
           
>	ConcurrencyController::RESULT ConcurrencyController::FinalizeNodeRead(Node* const pNode)

	Author:	Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/02/97

	Inputs:	pNode:	The node that was passed in a previous call to PrepareNodeForRead()
	Returns:	TRUE if the node can be read or updated again.
		FALSE otherwise
	Purpose:	Once the given node has been read or passed as a parameter, call this function 
		to free it for updates.
		This call should be accompanied by a prior call to PrepareNodeForRead(). The
		results of the read are undefined if not.
	See Also:	FinalizeNodeUpdate()
	
**********************************************************************************************/  
ConcurrencyController::RESULT ConcurrencyController::FinalizeNodeRead(Node* const pNode);


/********************************************************************************************

>	UserID ConcurrencyController::GetNewUserID()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/03/97

	Purpose:	Support function to provide a new user id

	Notes:		Assumes thread-safe access to static members

********************************************************************************************/
ConcurrencyController::UserID ConcurrencyController::GetNewUserID()
{
	UserID NextID = ++s_NextFreeUserID;

	// if the NextID is zero, fail it always
	if (NextID == 0)
	{
		--s_NextFreeUserID;
	}
	return NextID;
}


