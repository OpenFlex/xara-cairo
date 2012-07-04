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

// Header file for the ConcurrencyController class

#ifndef INC_CONCURCON
#define INC_CONCURCON

class Operation;
class Node;
/*********************************************************************************************
           
>	class ConcurrencyController

    Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
    Created:	09/03/97

    Purpose:	Ensures no update conflicts with concurrent users to Camelot
	
**********************************************************************************************/  
class ConcurrencyController : public CC_CLASS_MEMDUMP
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(ConcurrencyController);

public:
	ConcurrencyController();
	BOOL Init();
	virtual ~ConcurrencyController();

// Attributes
public:
	typedef UINT32 UserID;
	typedef enum
	{
		CCR_OK = 0,
		CCR_INTERNAL_ERROR = 1,
		CCR_INVALID_ARGUMENT = 10,
		CCR_TOO_MANY_USERS = 100,
		CCR_INVALID_USER = 101
	} RESULT;
// Operations
public:
	RESULT StartUser(UserID* pNewUserID);
	RESULT EndUser(UserID UserWhosDone);

	RESULT PrepareForOperation(const Operation* const pOperation);
	RESULT FinalizeOperation(const Operation* const pOperation);

	RESULT PrepareNodeForRead(Node* const pNode);
	RESULT FinalizeNodeRead(Node* const pNode);
	RESULT PrepareNodeForUpdate(Node* const pNode);
	RESULT FinalizeNodeUpdate(Node* const pNode);


// Overrides

// Implementation
protected:
	UserID GetNewUserID();

private:
	// User Information
	static UserID	s_NextFreeUserID;
	static UserID	s_OneAndOnlyUser;
	static UINT32		s_NumberOfUsers;

	// Operation Lock Information
	static UINT32				s_NumberOfActiveOperations;
	static const Operation*	s_pTheActiveOperation;
};


#endif	// INC_CONCURCON
