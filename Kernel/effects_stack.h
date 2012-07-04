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
// Declaration of Bitmap Effects handling classes.
//

#ifndef INC_EFFECTS_STACK
#define INC_EFFECTS_STACK

class Range;
class ListRange;
class NodeEffect;
class EffectsStack;
class NodeLiveEffect;
class NodeFeatherEffect;
class NodeBitmapEffect;

// Define this if you want to pick up the development of the Feather Effect
#define FEATHER_EFFECT

/********************************************************************************************

>	class PPStackLevel : public ListItem

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/10/2004
	Purpose:	
	SeeAlso:	

********************************************************************************************/

class PPStackLevel : public ListItem
{
public:
	CC_DECLARE_DYNAMIC( PPStackLevel )
	PPStackLevel() {pPPNode=NULL; strPostProID=""; bConsistent=TRUE;}
	~PPStackLevel() {}					// Nothing to destruct

// Properties
	NodeEffect*	pPPNode;		// pointer to sample LE node for this stack level
//	_bstr_t				bstrEditDoc;	// sample edit document text for this stack level
	String_256			strPostProID;	// Display name of this LiveEffect level
	ListRange			listSelNodes;	// List of nodes in this stack level
	BOOL				bConsistent;	// TRUE if this level is consistent
										// (all nodes have similar params according to CompareState)
};




/********************************************************************************************

>	class EffectsStack : public List

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/10/2004
	Purpose:	Find and represent a consistent arrangement of LiveEffects above a
				specified range (usually the SelRange)
				This is complicated because the SelRange can have an arbitary collection of
				LiveEffects applied to it which may or may not be wholly or partially
				consisent.
				This class currently holds info about LiveEffects that are applied to all
				nodes in the SelRange, contiguously, in the same order.

********************************************************************************************/

#define STACKPOS_BOTTOM 0
#define STACKPOS_TOP 5000
#define STACKPOS_INSERT_TOP 6000
#define STACKPOS_INVALID -1

class EffectsStack: public List
{
	CC_DECLARE_DYNAMIC(EffectsStack)

public:
	static ListRange*			GetEffectsStackFromNode(Node* pNode, BOOL bNodeMaybeMidStack = FALSE, BOOL bEscapeDerived = TRUE, BOOL bIncludeLocked = FALSE);
	static EffectsStack*		GetEffectsStackFromSelection(Range* pRange = NULL, BOOL bEscapeDerived = TRUE, BOOL bIncludeLocked = FALSE);
	static BOOL					NodesSharePPStack(Node* pNode, Node* pLastNode, BOOL bNodeMaybeMidStack = FALSE, BOOL bIncludeLocked = FALSE);
	static Node*				FindStackBaseFrom(Node* pNode, BOOL bIncludeLocked);
	static Node*				EscapeOldControllers(Node* pUserNode);
	static ListRange*			GetNewLevelRange(Range* pRange = NULL, BOOL bEscapeOldControllers = TRUE);
	static ListRange*			GetTopClassRange(CCRuntimeClass* pClass,
												 BOOL bClassOnly = TRUE,
												 BOOL bIgnorePassThroughEffects = FALSE,
												 Node** ppMasterNode = NULL,
											     INT32* piStackPos = NULL,
											     Range* pRange = NULL,
											     BOOL bEscapeOldControllers = TRUE);

public:
	EffectsStack();
	~EffectsStack();

	BOOL					FindBestProcessor(String_256* pstrEffectID, INT32* piStackPos);
	BOOL					GetLevelInfo(String_256* pstrEffectID, INT32* piStackPos);
	BOOL					LockableNonEmpty();
	void					Clear();
	ListRange*				GetLevelRange(INT32* piStackPos, BOOL bEscapeOldControllers = TRUE);
	ListRange*				GetBaseLevelRange();
	PPStackLevel*			GetLevel(INT32 iStackPos) {return (PPStackLevel*)FindItem(iStackPos);}
	ListRange*				FindLevelContaining(NodeEffect* pNode, INT32* piStackPos);
	BOOL					NodeInTopLevel(NodeEffect* pNode);
	INT32						FindSelectionPos();
	BOOL					BuildEffectMenu(ContextMenu* pMenu);
	void					AttrsHaveChanged();

protected:
	BOOL					Initialise(ListRange* pRange);
	BOOL					Intersect(ListRange* pRange);
	PPStackLevel*			FindMatch(PPStackLevel* pFirstItem, ListRange* pRange, NodeEffect* pPP);

// Properties
public:
	BOOL					bConsistent;

private:
	ListRange*				m_pNewLevelRange;			// This is a ListRange we made to cover the top of the selection
														// but which is not yet in the stack
};




#endif	// INC_EFFECTS_STACK
