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

// This file contains code to handle ObjChange parameter classes.
// An ObjChange parameter is used to pass to a parent node informing
// it that a child has changed.

/*
*/

#include "camtypes.h"
//#include "resource.h"
#include "objchge.h"


CC_IMPLEMENT_DYNAMIC(ObjChangeParam, CCObject)
CC_IMPLEMENT_DYNAMIC(ObjChangePathEdit, ObjChangeParam)
CC_IMPLEMENT_DYNAMIC(ObjChangeParamWithToken, ObjChangeParam)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW


/********************************************************************************************

>	ObjChangeFlags::ObjChangeFlags(	BOOL Delete 		= FALSE,
									BOOL Replace 		= FALSE,
									BOOL Move 			= FALSE,
									BOOL Attr 			= FALSE,
									BOOL MultiReplace 	= FALSE,
									BOOL Transform	 	= FALSE,
									BOOL Copy			= FALSE,
									BOOL Regen			= FALSE);

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/01/95
	Purpose:	constructor for ObjChange flags class

********************************************************************************************/

ObjChangeFlags::ObjChangeFlags(	BOOL Delete,
								BOOL Replace,
								BOOL Move,
								BOOL Attrib,
								BOOL MultiReplace,
								BOOL Transform,
								BOOL Copy,
								BOOL Regen)
{
 	DeleteNode 			= Delete;
 	ReplaceNode 		= Replace;
 	MoveNode 			= Move;
	Attribute			= Attrib;
	MultiReplaceNode 	= MultiReplace;
	TransformNode 		= Transform;
	CopyNode			= Copy;
	RegenerateNode		= Regen;
}


/********************************************************************************************

>  ObjChangeMask::ObjChangeMask()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/01/95
	Purpose:	constructor for ObjChangeMask. This sets the various maskable changes to
				false, ie they will not be sent during and interactive change.

********************************************************************************************/

ObjChangeMask::ObjChangeMask()
{
	// set all flags to false;
	EorBlobs = FALSE;
	Finished = FALSE;
}

/********************************************************************************************

>  void ObjChangeMask::ClaimAll()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/01/95
	Purpose:	A quick way of setting all the mask bits to true, for a particular
				ObjChangeMask. This starts forcing all ObjChange messages for a particular
				op to be sent.

********************************************************************************************/

void ObjChangeMask::ClaimAll()
{
	// set all flags to false;
	EorBlobs = TRUE;
	Finished = TRUE;
}

/********************************************************************************************

>  void ObjChangeMask::CorrectMask()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/01/95
	Purpose:	Checks the ObjChangeMask settings and corrects them where necessary.
				It thus ensures object change messages are not called out of sequence or
				or missed out when necessary.

********************************************************************************************/

void ObjChangeMask::CorrectMask()
{
	// does nothing at present
}


/********************************************************************************************

>	ObjChangeParam::ObjChangeParam()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/01/95
	Purpose:	Constructor for the ObjChangeParam class

********************************************************************************************/

ObjChangeParam::ObjChangeParam()
{
	ChangeType			= OBJCHANGE_UNDEFINED;
	pChangeOp			= NULL;
	pChangeNode			= NULL;	
	DenialReason		= 0;
	ChangeDirection		= OBJCHANGE_CALLEDBYOP;
	m_pCallingChild		= NULL;
	m_bRetainCachedData = FALSE;
}


/********************************************************************************************

>	ObjChangeParam::ObjChangeParam(	ObjChangeType cType,
									ObjChangeFlags cFlags,
									Node* cNode,
									UndoableOperation* cOp,
									ObjChangeDirection direction=OBJCHANGE_CALLEDBYOP,
									Node* pCallingChild = NULL)

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/2/95
	Inputs:		cType	= a change type
				cFlags	= change flags
				cNode	= a pointer to the node thats changing
				cOp		= a pointer to the current operation (NULL if the change is occuring
						  in a none undoable way)
				direction = direction in which the AllowOp is being called
				pCallingChild = the node calling the AllowOp, if OBJCHANGE_CALLEDBYCHILD set.
	Purpose:	Initialises an ObjChange parameter block.

********************************************************************************************/

ObjChangeParam::ObjChangeParam(	ObjChangeType cType,
								ObjChangeFlags cFlags,
								Node* cNode,
								UndoableOperation* cOp,
								ObjChangeDirection direction,
								Node* pCallingChild)
{
	DenialReason = 0;
	Define(cType,cFlags,cNode,cOp,direction,pCallingChild);
}



/********************************************************************************************

>	ObjChangeParam::~ObjChangeParam()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/01/95
	Purpose:	Destructor for the ObjChangeParam class

********************************************************************************************/

ObjChangeParam::~ObjChangeParam()
{
}


/********************************************************************************************

>	void ObjChangeParam::Define(ObjChangeType cType,
								ObjChangeFlags cFlags,
								Node* cNode,
								UndoableOperation* cOp,
								ObjChangeDirection direction=OBJCHANGE_CALLEDBYOP,
								pCallingChild = NULL)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/01/95
	Inputs:		cType	= a change type
				cFlags	= change flags
				cNode	= a pointer to the node thats changing
				cOp		= a pointer to the current operation (NULL if the change is occuring
						  in a none undoable way)
				direction = direction in which AllowOp is called
				pCallingChild = the node calling the AllowOp, if OBJCHANGE_CALLEDBYCHILD set.
	Returns:	-
	Purpose:	Initialises an ObjChange parameter block.

********************************************************************************************/

void ObjChangeParam::Define(ObjChangeType cType,
							ObjChangeFlags cFlags,
							Node* cNode,
							UndoableOperation* cOp,
							ObjChangeDirection direction,
							Node* pCallingChild)
{
	ERROR3IF(cType==OBJCHANGE_UNDEFINED,"ObjChangeParam::Define() called with an illegal change type");
	//ERROR3IF(cNode==NULL,"ObjChangeParam::Define() called with a null child node pointer");

	// Now set the internal variables
	ChangeType			= cType;
	ChangeFlags			= cFlags;
	pChangeOp			= cOp;
	pChangeNode			= cNode;
	ChangeDirection		= direction;
	m_pCallingChild		= pCallingChild;
	m_bRetainCachedData = FALSE;
}


/********************************************************************************************

>	ObjChangePathEdit::ObjChangePathEdit()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/01/95
	Purpose:	Constructor for the ObjChangePathEdit class

********************************************************************************************/

ObjChangePathEdit::ObjChangePathEdit() : ObjChangeParam()
{
	pChangePath = NULL;
	pChangeSpread = NULL;
}


/********************************************************************************************

>	ObjChangePathEdit::~ObjChangePathEdit()

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/01/95
	Purpose:	Destructor for the ObjChangePathEdit class

********************************************************************************************/

ObjChangePathEdit::~ObjChangePathEdit()
{
}

/********************************************************************************************

>	void ObjChangePathEdit::Define(	ObjChangeType cType,
									ObjChangeFlags cFlags,
									Node* cNode,
									UndoableOperation* cOp
									Path* cPath
									Spread* cSpread)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/01/95
	Inputs:		cType	= a change type
				cFlags	= change flags
				cNode	= a pointer to the node thats changing
				cOp		= a pointer to the current operation 
						  (NULL if the change is occuring in a none undoable way)
				cPath	= a pointer to the current version of the path
						  (can be NULL for all but PRE and POSTCHANGE parameters)
				cSpread = a pointer to a spread
						  (can be NULL for all but PRE and POSTCHANGE parameters)

	Returns:	-
	Purpose:	Initialises an ObjChangePathEdit parameter block.

********************************************************************************************/

void ObjChangePathEdit::Define(	ObjChangeType cType,
								ObjChangeFlags cFlags,
								Node* cNode,
								UndoableOperation* cOp,
								Path* cPath,
								Spread* cSpread)
{
	ERROR3IF(cPath==NULL,"ObjChangePathEdit::Define() called with a null edit path");
	ERROR3IF(cSpread==NULL,"ObjChangePathEdit::Define() called with a null edit Spread");

	ObjChangeParam::Define(cType,cFlags,cNode,cOp);

	// Now set the internal variables
	pChangePath = cPath;
	pChangeSpread = cSpread;
}



/********************************************************************************************

>	ChangeCode ObjChangePathEdit::Define(Node* cNode,
										 UndoableOperation* cOp
										 Path* cPath
										 Spread* cSpread
										 BOOL All)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/01/95
	Inputs:		cNode	= a pointer to the node thats changing
				cOp		= a pointer to the current operation 
						  (NULL if the change is occuring in a none undoable way)
				cPath	= a pointer to the current version of the path
						  (can be NULL for all but PRE and POSTCHANGE parameters)
				cSpread = a pointer to a spread
						  (can be NULL for all but PRE and POSTCHANGE parameters)
				All		= a bool, used to send the message to all of cNodes parents
						  if TRUE or just its immediate parent if FALSE;
	Returns:	ChangeCode
	Purpose:	Initialises an ObjChangePathEdit parameter block with a ChangeStarting
				message.

********************************************************************************************/

ChangeCode ObjChangePathEdit::ObjChangeStarting(Node* cNode,
												UndoableOperation* cOp,
												Path* cPath,
												Spread* cSpread,
												BOOL All)
{
	// Create some change flags
	ObjChangeFlags ChgeFlags;
	// Now define the change block				   
	Define(OBJCHANGE_STARTING,ChgeFlags,cNode,cOp,cPath,cSpread);
	// Send the message to the nodes parents
	ChangeCode Chge = cNode->WarnParentOfChange(this,All);
	// Correct the message mask returned
	ChangeMask.CorrectMask();

	return Chge;
}



/********************************************************************************************

>	ChangeCode ObjChangePathEdit::RenderCurrentBlobs(Node* cNode,
													 UndoableOperation* cOp,
													 Path* cPath,
													 Spread* cSpread,
													 BOOL All)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/01/95
	Inputs:		See ObjChangeStarting

********************************************************************************************/

ChangeCode ObjChangePathEdit::RenderCurrentBlobs(Node* cNode,
												 UndoableOperation* cOp,
												 Path* cPath,
												 Spread* cSpread,
												 BOOL All)
{
	// Create some change flags
	ObjChangeFlags ChgeFlags;
	// Now define the change block				   
	Define(OBJCHANGE_RENDERCURRENTBLOBS,ChgeFlags,cNode,cOp,cPath,cSpread);
	return (cNode->WarnParentOfChange(this,All));
}



/********************************************************************************************

>	ChangeCode ObjChangePathEdit::RenderChangedBlobs(Node* cNode,
													 UndoableOperation* cOp,
													 Path* cPath,
													 Spread* cSpread,
													 BOOL All)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/01/95
	Inputs:		See ObjChangeStarting

********************************************************************************************/

ChangeCode ObjChangePathEdit::RenderChangedBlobs(Node* cNode,
												 UndoableOperation* cOp,
												 Path* cPath,
												 Spread* cSpread,
												 BOOL All)
{
	// Create some change flags
	ObjChangeFlags ChgeFlags;
	// Now define the change block				   
	Define(OBJCHANGE_RENDERCHANGEDBLOBS,ChgeFlags,cNode,cOp,cPath,cSpread);
	return (cNode->WarnParentOfChange(this,All));
}



/********************************************************************************************

>	ChangeCode ObjChangePathEdit::ObjChangeFinished(Node* cNode,
										 			UndoableOperation* cOp,
										 			Path* cPath,
										 			Spread* cSpread,
										 			BOOL All)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/01/95
	Inputs:		See ObjChangeStarting

********************************************************************************************/

ChangeCode ObjChangePathEdit::ObjChangeFinished(Node* cNode,
												UndoableOperation* cOp,
												Path* cPath,
												Spread* cSpread,
												BOOL All)
{
	// Create some change flags
	ObjChangeFlags ChgeFlags;
	// Now define the change block				   
	Define(OBJCHANGE_FINISHED,ChgeFlags,cNode,cOp,cPath,cSpread);
	return (cNode->WarnParentOfChange(this,All));
}



/********************************************************************************************

>	ChangeCode ObjChangePathEdit::ObjChangeFailed(	Node* cNode,
													UndoableOperation* cOp,
													Path* cPath,
													Spread* cSpread,
													BOOL All)

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/01/95
	Inputs:		See ObjChangeStarting
	Purpose:	Send the parents of cNode an OBJCHANGE_FAILED message.

********************************************************************************************/

ChangeCode ObjChangePathEdit::ObjChangeFailed(	Node* cNode,
												UndoableOperation* cOp,
												Path* cPath,
												Spread* cSpread,
												BOOL All)
{
	// Create some change flags
	ObjChangeFlags ChgeFlags;
	// Now define the change block				   
	Define(OBJCHANGE_FAILED,ChgeFlags,cNode,cOp,cPath,cSpread);
	return (cNode->WarnParentOfChange(this,All));
}


/////////////////////////////////////////////////////////////////////////////////////////////
///		ObjChangeParamWithToken


/********************************************************************************************

>	ObjChangeParamWithToken::ObjChangeParamWithToken()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/03/95
	Purpose:	Constructor for the ObjChangeParamWithToken class.  This is almost idential
				to ObjChangeParam, except that it always has an OpToken of the operation
				that will be applied.  The pointer to the operation may still be NULL.
				This gives you a way of seeing what the operation will be before it starts.
				Most usefully in an operations GetState.

********************************************************************************************/

ObjChangeParamWithToken::ObjChangeParamWithToken(	ObjChangeType cType,
													ObjChangeFlags cFlags,
													Node* cNode,
													UndoableOperation* cOp,
													String* pToken)
						: ObjChangeParam(	cType,
											cFlags,
											cNode,
											cOp)
{
	OperationToken = *pToken;
}



/********************************************************************************************

>	ObjChangeParamWithToken::~ObjChangeParamWithToken()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/03/95
	Purpose:	Destructor for the ObjChangeParamWithToken class

********************************************************************************************/

ObjChangeParamWithToken::~ObjChangeParamWithToken()
{
}
