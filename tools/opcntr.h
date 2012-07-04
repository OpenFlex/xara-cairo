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

// Header for the Contour operations

#ifndef INC_OPCONTOUR
#define INC_OPCONTOUR

#define OPTOKEN_CREATECONTOUR	_T("CreateContour")
#define OPTOKEN_REMOVECONTOUR	_T("RemoveContour")
#define OPTOKEN_CHANGECONTOURWIDTH _T("ChangeContourWidth")
#define OPTOKEN_CHANGECONTOUR_INNER _T("ChangeContourToInner")
#define OPTOKEN_CHANGECONTOUR_OUTER _T("ChangeContourToOuter")
#define OPTOKEN_CHANGECONTOURSTEPS	_T("ChangeContourSteps")
#define OPTOKEN_CHANGECONTOURCOLOURTYPE _T("ChangeContourColourType")
#define OPTOKEN_CHANGECONTOURATTRPROFILE	_T("ChangeContourAttributeProfile")
#define OPTOKEN_CHANGECONTOUROBJPROFILE		_T("ChangeContourObjectProfile")
#define OPTOKEN_CHANGECONTOURSTEPDISTANCE	_T("ChangeContourStepDistance")
#define OPTOKEN_CONVERTPATHTOSHAPES		_T("ConvertPathToShapes")
#define OPTOKEN_TOGGLEINSETPATH	_T("InsetPath")

class NodeContourController;
class NodeGroup;
class AttrStrokeType;
class AttrBrushType;

#include "blendatt.h"
//#include "biasgain.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "selop.h"
//#include "becomea.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************************************
>	class CreateContourParam : public OpParam

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/8/99
	Purpose:	The op param for the creation of contours
********************************************************************************************/
class CreateContourParam : public OpParam
{
CC_DECLARE_DYNCREATE(CreateContourParam)
public:
	CreateContourParam(List * pList = NULL,
						UINT32 Steps	= 5,
						INT32 Width  = -5000,
						BOOL bInset = FALSE)
	{
		m_pNodeList = pList;
		m_Steps = Steps;
		m_Width = Width;
		m_bInsetPath = bInset;
	}
	
	// the node list to create the contour on
	List * m_pNodeList;

	// the number of steps involved
	UINT32 m_Steps;

	// the width of the contour in document coordinates
	INT32 m_Width;

	BOOL m_bInsetPath;
} ;


/********************************************************************************************
>	class OpCreateContour : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/8/99
	Purpose:	Creates contours on the selection
********************************************************************************************/

class OpCreateContour : public SelOperation
{

CC_DECLARE_DYNCREATE(OpCreateContour)

public:
	// Construction/Destruction
	OpCreateContour();
	~OpCreateContour();

	virtual void Do(OpDescriptor *pOpDesc);
	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);

//	BOOL GenerateBitmapShapes(NodeBevel* pCurrent, SelRange SelectionRng);

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);
	virtual BOOL MayChangeNodeBounds() const { return TRUE; }
};

/********************************************************************************************
>	class OpRemoveContour : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/8/99
	Purpose:	Removes contours on the selection
********************************************************************************************/

class OpRemoveContour : public SelOperation
{

CC_DECLARE_DYNCREATE(OpRemoveContour)

public:
	// Construction/Destruction
	OpRemoveContour();
	~OpRemoveContour();

	virtual void Do(OpDescriptor *pOpDesc);
	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);

//	BOOL GenerateBitmapShapes(NodeBevel* pCurrent, SelRange SelectionRng);

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	virtual BOOL MayChangeNodeBounds() const { return TRUE; }
};

/********************************************************************************************
>	class RegenerateContourAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/3/99
	Purpose:	Forces a regeneration of the bevel in all nodes in the list
				Used by NodeBevelcontroller::OnChildChange to force redraws in undos/redos
********************************************************************************************/
class RegenerateContourAction : public Action
{

CC_DECLARE_DYNCREATE(RegenerateContourAction)

public:
	RegenerateContourAction();
	~RegenerateContourAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							List * pNodes,
							RegenerateContourAction** NewAction,
							BOOL bCache = FALSE);
protected:
	List * m_pNodes;
	BOOL m_bCache;
	DocRect m_OldRect;
};

/********************************************************************************************
>	class OpChangeContourWidth : public UndoableOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/3/99
	Purpose:	Forces a regeneration of the bevel in all nodes in the list
				Used by NodeBevelcontroller::OnChildChange to force redraws in undos/redos
********************************************************************************************/
class OpChangeContourWidth : public UndoableOperation
{

CC_DECLARE_DYNCREATE(OpChangeContourWidth)

public:
	// Construction/Destruction
	OpChangeContourWidth();
	~OpChangeContourWidth();

	virtual void Do(OpDescriptor *pOpDesc);
	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	void GetOpName(String_256 *pOpName);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return TRUE; }
} ;


/********************************************************************************************
>	class ChangeContourWidthParam : public OpParam

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/3/99
	Purpose:	Parameter for the change countour operation
********************************************************************************************/
class ChangeContourWidthParam : public OpParam
{
public:
	// parameters -
	// pNodes	-	The list of nodes to invoke this op on
	// NewWidth -	The new width to set
	// bKeepWidth -	Whether to keep the direction (either inner or outer) of the
	//				contour when setting the width, or whether to just take the new width
	//				and use this
	ChangeContourWidthParam(List * pNodes, MILLIPOINT NewWidth, BOOL bKeepDirection)
	{	
		m_pNodes = pNodes;
		m_Width = NewWidth;
		m_bKeepDirection = bKeepDirection;
	}

	List * m_pNodes;
	MILLIPOINT m_Width;
	BOOL m_bKeepDirection;
} ;

/********************************************************************************************
>	class ContourWidthListItem : public ListItem

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/3/99
	Purpose:	ListItem for use in ChangeContourWidthAction's list
********************************************************************************************/
class ContourWidthListItem : public ListItem
{
public:
	ContourWidthListItem(MILLIPOINT Width) { m_Width = Width; }

	MILLIPOINT m_Width;
} ;

/********************************************************************************************
>	class ChangeContourWidthAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/3/99
	Purpose:	Forces a regeneration of the bevel in all nodes in the list
				Used by NodeBevelcontroller::OnChildChange to force redraws in undos/redos
********************************************************************************************/
class ChangeContourWidthAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeContourWidthAction)

public:
	ChangeContourWidthAction();
	~ChangeContourWidthAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							List * pNodes,
							MILLIPOINT NewWidth,
							BOOL bKeepDirection,
							ChangeContourWidthAction** NewAction);
protected:
	List m_Nodes;
	List m_WidthList;	
};

/********************************************************************************************
>	class ChangeContourToOuterAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/9/99
	Purpose:	Changes the node to an outer contour node & regenerates
********************************************************************************************/
class ChangeContourToOuterAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeContourToOuterAction)

public:
	ChangeContourToOuterAction();
	~ChangeContourToOuterAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeContourController * pContour,
							ChangeContourToOuterAction** NewAction);
protected:
	NodeContourController * m_pContour;
	MILLIPOINT m_LastWidth;
};

/********************************************************************************************
>	class ChangeContourToInnerAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/9/99
	Purpose:	Changes the node to an inner contour node & regenerates
********************************************************************************************/
class ChangeContourToInnerAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeContourToInnerAction)

public:
	ChangeContourToInnerAction();
	~ChangeContourToInnerAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeContourController * pContour,
							ChangeContourToInnerAction** NewAction);
protected:
	NodeContourController * m_pContour;
	MILLIPOINT m_LastWidth;
};

/********************************************************************************************
>	class OpChangeContourToInner : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/3/99
	Purpose:	Changes all contours to inner - used by the button on the infobar
********************************************************************************************/

class OpChangeContourToInner : public SelOperation
{

CC_DECLARE_DYNCREATE(OpChangeContourToInner)

public:
	// Construction/Destruction
	OpChangeContourToInner();
	~OpChangeContourToInner();

	virtual void Do(OpDescriptor *pOpDesc);
	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);
};


/********************************************************************************************
>	class OpChangeContourToOuter : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/3/99
	Purpose:	Changes all contours to outer - used by the button on the infobar
********************************************************************************************/

class OpChangeContourToOuter : public SelOperation
{

CC_DECLARE_DYNCREATE(OpChangeContourToOuter)

public:
	// Construction/Destruction
	OpChangeContourToOuter();
	~OpChangeContourToOuter();

	virtual void Do(OpDescriptor *pOpDesc);
	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);
};


/********************************************************************************************

>	class OpChangeContourSteps : public SelOperation

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/11/94
	Purpose:	This changes the number of steps of the selected blends

********************************************************************************************/


class OpChangeContourSteps : public SelOperation
{
CC_DECLARE_DYNCREATE(OpChangeContourSteps);

public:
	// Construction/Destruction
	OpChangeContourSteps()  {}
	~OpChangeContourSteps() {}

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	// The all-important Do() func
	virtual void DoWithParam(OpDescriptor*,OpParam* pOpParam);
	virtual void GetOpName(String_256* OpName);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};


/********************************************************************************************

>	class ChangeContourStepsAction : public Action

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/11/94
	Purpose:	An action which undoes the modification of a path's filled bit (or redoes it)
				It can also be used to undo the IsStroked flag as well.
	SeeAlso:	-

********************************************************************************************/

class ChangeContourStepsAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeContourStepsAction)

public:
	ChangeContourStepsAction();
	~ChangeContourStepsAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							Node* pThisNodeBlend,
							UINT32 NumSteps,
							double DistanceEntered,
							ChangeContourStepsAction** NewAction);
protected:
	Node*	 	pNodeBlend;
	UINT32		OldNumSteps;
	double      OldDistanceEntered;
};

/********************************************************************************************

>	class OpChangeContourColourType : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/11/94
	Purpose:	This changes the number of steps of the selected blends

********************************************************************************************/


class OpChangeContourColourType : public SelOperation
{
CC_DECLARE_DYNCREATE(OpChangeContourColourType);

public:
	// Construction/Destruction
	OpChangeContourColourType()  {}
	~OpChangeContourColourType() {}

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	// The all-important Do() func
	virtual void DoWithParam(OpDescriptor*,OpParam* pOpParam);
	virtual void GetOpName(String_256* OpName);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};

/********************************************************************************************

>	class OpChangeContourAttributeProfile : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/11/94
	Purpose:	This changes the number of steps of the selected blends

********************************************************************************************/


class OpChangeContourAttributeProfile : public SelOperation
{
CC_DECLARE_DYNCREATE(OpChangeContourAttributeProfile);

public:
	// Construction/Destruction
	OpChangeContourAttributeProfile()  {}
	~OpChangeContourAttributeProfile() {}

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	// The all-important Do() func
	virtual void DoWithParam(OpDescriptor*,OpParam* pOpParam);
	virtual void GetOpName(String_256* OpName);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};

/********************************************************************************************

>	class ChangeContourAttributeProfile : public Action

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/11/94
	Purpose:	An action which undoes the modification of a path's filled bit (or redoes it)
				It can also be used to undo the IsStroked flag as well.
	SeeAlso:	-

********************************************************************************************/

class ChangeContourAttributeProfileAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeContourAttributeProfileAction)

public:
	ChangeContourAttributeProfileAction();
	~ChangeContourAttributeProfileAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeContourController* pThisNodeContour,
							CProfileBiasGain Profile,
							ChangeContourAttributeProfileAction** NewAction);

	static void ChangeAttributeProfileWithNoUndo (CProfileBiasGain &Profile);
protected:
	NodeContourController*	 	m_pNode;
	CProfileBiasGain m_Profile;
};





/********************************************************************************************

>	class ChangeContourColourTypeAction : public Action

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/11/94
	Purpose:	An action which undoes the modification of a path's filled bit (or redoes it)
				It can also be used to undo the IsStroked flag as well.
	SeeAlso:	-

********************************************************************************************/

class ChangeContourColourTypeAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeContourColourTypeAction)

public:
	ChangeContourColourTypeAction();
	~ChangeContourColourTypeAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeContourController* pThisNodeContour,
							ColourBlendType type,
							ChangeContourColourTypeAction** NewAction);
protected:
	NodeContourController*	 	m_pNode;
	ColourBlendType m_OldType;
};

/********************************************************************************************
>	class CreateContourParam : public OpParam

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/8/99
	Purpose:	The op param for the creation of contours
********************************************************************************************/
class ChangeContourProfileParam : public OpParam
{

public:
	ChangeContourProfileParam(CProfileBiasGain &Profile)
	{
		m_Profile = Profile;
	}
	
	CProfileBiasGain m_Profile;
} ;

/********************************************************************************************

>	class OpChangeContourObjectProfile : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/11/94
	Purpose:	This changes the number of steps of the selected blends

********************************************************************************************/

class OpChangeContourObjectProfile : public SelOperation
{
CC_DECLARE_DYNCREATE(OpChangeContourObjectProfile);

public:
	// Construction/Destruction
	OpChangeContourObjectProfile()  {}
	~OpChangeContourObjectProfile() {}

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	// The all-important Do() func
	virtual void DoWithParam(OpDescriptor*,OpParam* pOpParam);
	virtual void GetOpName(String_256* OpName);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};


/********************************************************************************************

>	class ChangeContourObjectProfile : public Action

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/11/94
	Purpose:	An action which undoes the modification of a path's filled bit (or redoes it)
				It can also be used to undo the IsStroked flag as well.
	SeeAlso:	-

********************************************************************************************/

class ChangeContourObjectProfileAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeContourObjectProfileAction)

public:
	ChangeContourObjectProfileAction();
	~ChangeContourObjectProfileAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeContourController* pThisNodeContour,
							CProfileBiasGain Profile,
							ChangeContourObjectProfileAction** NewAction);

	static void ChangeObjectProfileWithNoUndo (CProfileBiasGain &Profile);
protected:
	NodeContourController*	 	m_pNode;
	CProfileBiasGain m_Profile;
};

/********************************************************************************************

>	class OpChangeContourStepDistance : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/11/94
	Purpose:	This changes the step distance of the selected blends

********************************************************************************************/

class OpChangeContourStepDistance : public SelOperation
{
CC_DECLARE_DYNCREATE(OpChangeContourStepDistance);

public:
	// Construction/Destruction
	OpChangeContourStepDistance()  {}
	~OpChangeContourStepDistance() {}

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	// The all-important Do() func
	virtual void DoWithParam(OpDescriptor*,OpParam* pOpParam);
	virtual void GetOpName(String_256* OpName);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};

/********************************************************************************************

>	class OpConvertPathToShapes : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/2/2000
	Purpose:	This creates objects out of the paths of the selected objects

********************************************************************************************/

class OpConvertPathToShapes : public SelOperation
{
CC_DECLARE_DYNCREATE(OpConvertPathToShapes);

public:
	// Construction/Destruction
	OpConvertPathToShapes()  {}
	~OpConvertPathToShapes() {}

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	// The all-important Do() func
	virtual void Do(OpDescriptor*);
	virtual void GetOpName(String_256* OpName);	

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }


	static BOOL ConvertPathToShapes(OpConvertPathToShapes* pOp, NodeRenderableInk* pInk);
	
	// when we convert a stroked shape we want to swap the stroke colour to become the 
	// new fill colour
	static BOOL AdjustStrokeAndFillAttrs(OpConvertPathToShapes* pOp, 
											NodePath* pNewNode, 
											NodeRenderableInk* pCreatedByNode = NULL,
											CCAttrMap* pAttrMap = NULL);

protected: // functions to convert objects with brush and stroke attributes

	// Converts an ink node with a brush attribute applied
	static BOOL ConvertBrush(OpConvertPathToShapes* pOp, AttrBrushType* pAttrBrush, NodeRenderableInk* pInk);

	// Converts an ink node with a stroke attribute applied
	static BOOL ConvertStroke(OpConvertPathToShapes* pOp, AttrStrokeType* pStroke, NodeRenderableInk* pInk);

};

/***********************************************************************************************

>	class ConvertPathToShapesBecomeA : public BecomeA

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com> Mc
	Created:	10/2/2000
	Purpose:	The become A structure for the above operation
				Adds a node into the tree which is the stroked path of the particular node
				passed into the PassBack function
	Notes:		When stepping through, you MUST store the next node before calling
				DoBecomeA - since the tree will be changed when PassBack is called in this
				class.

***********************************************************************************************/

class ConvertPathToShapesBecomeA : public BecomeA
{
public:
	ConvertPathToShapesBecomeA(	BecomeAReason Reason,
					CCRuntimeClass* pClass, 
					UndoableOperation* pOp, 
					BOOL Sel);

	virtual BOOL PassBack(NodeRenderableInk* pNewNode,NodeRenderableInk* pCreatedByNode,CCAttrMap* pAttrMap=NULL);

	void GetSummedPath(Path * pPath) { pPath->CloneFrom(m_SummedPath); }
	NodeRenderableInk* GetContextNode();

private:
	Path m_SummedPath;
	NodeGroup* m_pContextNode;
};

/********************************************************************************************

>	class OpToggleContourInsetPath : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/2/2000
	Purpose:	Toggles the inset path states of all selected contours

********************************************************************************************/

class OpToggleContourInsetPath : public SelOperation
{
CC_DECLARE_DYNCREATE(OpToggleContourInsetPath);

public:
	// Construction/Destruction
	OpToggleContourInsetPath()  {}
	~OpToggleContourInsetPath() {}

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	// The all-important Do() func
	virtual void DoWithParam(OpDescriptor*, OpParam*);
	virtual void GetOpName(String_256* OpName);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
private:
	UINT32 m_OpName;
};

/********************************************************************************************
>	class ToggleInsetPathAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/3/99
	Purpose:	Toggles the inset path flag on the given node
********************************************************************************************/
class ToggleInsetPathAction : public Action
{

CC_DECLARE_DYNCREATE(ToggleInsetPathAction)

public:
	ToggleInsetPathAction();
	~ToggleInsetPathAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeContourController *pNode,
							BOOL bInsetPathFlag, 
							ToggleInsetPathAction** NewAction);
protected:
	NodeContourController * m_pNode;
	BOOL m_OldSetting;
};



#endif
