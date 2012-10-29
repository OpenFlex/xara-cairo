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

// Header for the perspective mould shapes implementation

#ifndef INC_OBJCHANGE
#define INC_OBJCHANGE


class Node;
class UndoableOperation;
class Path;
class Spread;


/***********************************************************************************************
>	typedef enum ObjChangeType

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Date:		4/5/95
	Purpose:	Indicate to AllowOp()'s from which direction they were called
	SeeAlso:	ObjChangeFlags, ObjChangeParam
***********************************************************************************************/

typedef enum ObjChangeDirection
{
	OBJCHANGE_CALLEDBYOP,
	OBJCHANGE_CALLEDBYPARENT,
	OBJCHANGE_CALLEDBYCHILD
};


/***********************************************************************************************
>	typedef enum ObjChangeType

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Date:		09/01/95
	Purpose:	Types of change one can generate on a child object. These types form the 
				ObjChangeType field inside the following class ObjChangeParam.
	SeeAlso:	ObjChangeFlags, ObjChangeParam
***********************************************************************************************/

typedef enum ObjChangeType
{
	OBJCHANGE_UNDEFINED,
	OBJCHANGE_STARTING,				// the child object is about to undergo a change
	OBJCHANGE_RENDERCURRENTBLOBS,	// during an interactive change ie a drag signal 'before' 
	OBJCHANGE_RENDERCHANGEDBLOBS,	// during an interactive change signal 'after'
	OBJCHANGE_FINISHED,				// having actually changed the tree child object inform the parent
	OBJCHANGE_IGNORE,				// Ignore this ObjChangeParam message
	OBJCHANGE_FAILED				// failed to actually change the child object
};


/***********************************************************************************************
>	class ObjChangeFlags

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com> (& Markn)
	Date:		09/01/95
	Purpose:	Defines physical changes which have occured on an object. These should be as 
				high level as possible.
  				If your object has changed in a subtle way, try and choose the field which best 
  				matches the	change. Try not to invent a new field for your change as like as 
  				not no one will respond to it.
	SeeAlso:	ObjChangeType, ObjChangeParam
***********************************************************************************************/

class ObjChangeFlags
{
	public:
		ObjChangeFlags(	BOOL Delete 		= FALSE,
						BOOL Replace 		= FALSE,
						BOOL Move 			= FALSE,
						BOOL Attr 			= FALSE,
						BOOL MultiReplace	= FALSE,
						BOOL TransForm	 	= FALSE,
						BOOL Copy			= FALSE,
						BOOL Regen			= FALSE);

	public:
		BYTE DeleteNode 			: 1;	// The node will be deleted (or hidden)
		BYTE ReplaceNode			: 1;	// The node will be replaced with *one* other
		BYTE MoveNode 				: 1;	// The node will be moved to another place in the tree
		BYTE Attribute				: 1;	// One or more attributes will be applied to this node
		BYTE MultiReplaceNode		: 1;	// The node will be replaced with one or more nodes
		BYTE TransformNode			: 1;	// The node will be transformed
		BYTE CopyNode				: 1;	// The node will be copied to the clipboard
		BYTE RegenerateNode			: 1;	// The node will be regenerated
};



/***********************************************************************************************
>	class ObjChangeMask

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Date:		11/01/95
	Purpose:	Defines what messages if any are passed to parent objects. The starting message
				is not defined here as this is used to allow nodes to actually set the mask.
				All flags are initialised to FALSE and should be set by nodes to TRUE when they
				want to receive a message. If any parent node requires a message then all will
				get the message. 
				Note the mask is verified and corrected so that messages will be sent correctly
				in sequence. 
***********************************************************************************************/

class ObjChangeMask
{
	public:
		ObjChangeMask();
		void CorrectMask();
		void ClaimAll();

	public:
		BYTE EorBlobs : 1;
		BYTE Finished : 1;
}; 


/***********************************************************************************************
>	class ObjChangeParam

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Date:		09/01/95
	Purpose:	Provides a derivable structure for passing to a nodes OnChildChange virtual 
				function. To create this class parameter simply call Define with the necessary
				change variables.
	SeeAlso:	ObjChangeType, ObjChangeFlags
***********************************************************************************************/

class ObjChangeParam : public CCObject
{
	CC_DECLARE_DYNAMIC(ObjChangeParam)

	public:
		ObjChangeParam();
		ObjChangeParam(ObjChangeType cType,ObjChangeFlags cFlags,Node* cNode,UndoableOperation* cOp,
					   ObjChangeDirection=OBJCHANGE_CALLEDBYOP, Node* pCallingChild = NULL);
		~ObjChangeParam();

		void 				Define(ObjChangeType, ObjChangeFlags, Node*, UndoableOperation*,
								   ObjChangeDirection direction=OBJCHANGE_CALLEDBYOP,
								   Node* pCallingChild = NULL);
		ObjChangeType		GetChangeType()  const { return ChangeType; }
		ObjChangeFlags		GetChangeFlags() const { return ChangeFlags; }
		UndoableOperation*	GetOpPointer()   const { return pChangeOp; }
		Node*				GetChangeObj()   const { return pChangeNode; }
		ObjChangeDirection	GetDirection()   const { return ChangeDirection; }
		void				SetDirection(ObjChangeDirection direction) { ChangeDirection=direction; }

		void				SetReasonForDenial(UINT32 IDS) 	{ DenialReason = IDS; }
		UINT32				GetReasonForDenial()			{ return DenialReason; }
		ObjChangeFlags*		GetSettableChangeFlags() { return &ChangeFlags; }

		void				SetCallingChild(Node* pCallingChild) { m_pCallingChild = pCallingChild; }
		Node*				GetCallingChild() { return m_pCallingChild; }

		void				SetRetainCachedData(BOOL bNewValue) {m_bRetainCachedData = bNewValue;}
		BOOL				GetRetainCachedData() const {return m_bRetainCachedData;}

	public:
		ObjChangeMask		ChangeMask;

	protected:
		ObjChangeType		ChangeType;
		ObjChangeFlags		ChangeFlags;
		ObjChangeDirection  ChangeDirection;
		UndoableOperation*	pChangeOp;
		Node*				pChangeNode;
		UINT32				DenialReason;
		Node*				m_pCallingChild;
		BOOL				m_bRetainCachedData;		// When processing try to retain cached data if possible

};




/***********************************************************************************************

>	class ObjChangePathEdit : public ObjChangeParam

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Date:		10/01/95
	Purpose:	A derived change parameter for use in path editing. It is exactly the same as
				ObjChangeParam apart from providing a path pointer, for use during eor drags,
				to describe the current state of the dragged path. Obviously this cannot be
				determined from the tree object until it has been updated when the drag finishes
	SeeAlso:	

***********************************************************************************************/

class ObjChangePathEdit : public ObjChangeParam
{
	CC_DECLARE_DYNAMIC(ObjChangePathEdit)

	public:
		 ObjChangePathEdit();
		~ObjChangePathEdit();
		 void Define(ObjChangeType,	ObjChangeFlags,	Node*, UndoableOperation*, Path*, Spread*);
		 
		 ChangeCode ObjChangeStarting(Node*,UndoableOperation*,Path*,Spread*,BOOL);
		 ChangeCode RenderCurrentBlobs(Node*,UndoableOperation*,Path*,Spread*,BOOL);
		 ChangeCode RenderChangedBlobs(Node*,UndoableOperation*,Path*,Spread*,BOOL);
		 ChangeCode ObjChangeFinished(Node*,UndoableOperation*,Path*,Spread*,BOOL);
		 ChangeCode ObjChangeFailed(Node*,UndoableOperation*,Path*,Spread*,BOOL);

	public:
		Path*	pChangePath;
		Spread* pChangeSpread;
};



/***********************************************************************************************

>	class ObjChangeParamWithToken

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Date:		6/3/95
	Purpose:	Identical to a ObjChangeParam object, except that there is an additional field
				that contains the OpToken
	SeeAlso:	ObjChangeParam

***********************************************************************************************/

class ObjChangeParamWithToken : public ObjChangeParam
{
	CC_DECLARE_DYNAMIC(ObjChangeParamWithToken)

	public:
		ObjChangeParamWithToken(ObjChangeType cType,ObjChangeFlags cFlags,Node* cNode,UndoableOperation* cOp, String* pToken);
		~ObjChangeParamWithToken();

		String*	GetOpToken() {return &OperationToken;};

	protected:
		String	OperationToken;
};


#endif

