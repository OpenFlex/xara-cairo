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

// Header for the shadow tool operations

#ifndef INC_OPSHADOW
#define INC_OPSHADOW

#include "nodecont.h"

#ifdef BUILDSHADOWS

#include "attrappl.h"
#include "shadinfo.h"	// for SoftShadowInfoBarData
#include "menuitem.h"
#include "effects_stack.h"

class NodeShadowParam;

//#define OPTOKEN_CREATESHADOW			"CreateShadow"
#define OPTOKEN_APPLYSHADOW				_T("ApplyShadow")
#define OPTOKEN_CHANGESHADOWTYPE		_T("ChangeShadowType")
#define OPTOKEN_REMOVESHADOW			_T("RemoveShadow")
#define OPTOKEN_SHADOWPOSITION			_T("ShadowPosition")
#define OPTOKEN_SHADOWPENUMBRA			_T("ShadowPenumbra")
#define OPTOKEN_SHADOWATTRIB			_T("ShadowAttributeApply")
#define OPTOKEN_SHADOWANGLE				_T("ShadowAngle")
#define OPTOKEN_SHADOWHEIGHT			_T("ShadowHeight")
#define OPTOKEN_SHADOWSCALE				_T("ShadowScale")
#define OPTOKEN_SHADOWHEIGHTANDANGLE	_T("ShadowHeightAndAngle")
#define OPTOKEN_SAVESHADOWDATA			_T("SaveShadowData")
#define OPTOKEN_GLOWWIDTH				_T("GlowWidth")
#define OPTOKEN_SHADOWPROFILE			_T("ShadowProfile")
#define OPTOKEN_SHADOWDARKNESS			_T("ShadowDarkness")

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	OpApplyShadow class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************************
>	class OpApplyShadow : public SelOperation

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/11/2004
	Purpose:	Create a shadow object in the tree giving the current selection a shadow.
********************************************************************************************/
class OpApplyShadow : public SelOperation
{

CC_DECLARE_DYNCREATE(OpApplyShadow)

public:
	static BOOL Declare();
	static ListRange*				DoApplyShadow(UndoableOperation* pOp, Range* pRange, NodeShadowParam* pNSParam);
	static NodeShadowController*	DoApplyShadow(UndoableOperation* pOp, Node* pNode, NodeShadowParam* pNSParam, BOOL bSetSelected = TRUE);

public:
	// Construction/Destruction
	OpApplyShadow();
	~OpApplyShadow();

	virtual void Do(OpDescriptor *pOpDesc);
	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);

	// These functions required for the OpDescriptor class
	static OpState GetState(String_256* Description, OpDescriptor*);
	static OpState GetParamState(String_256* pstrDescription, OpDescriptor* pOpDesc, OpParam* pOpParam);

//	void GetOpName(String_256 * pString);

//private:
//	void AddShadowToNode(Node * pNode);
//	UINT32 m_OpName;
};


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	OpChangeShadowType class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************************
>	class OpChangeShadowType : public SelOperation

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/2004
	Purpose:	Create a shadow object in the tree giving the current selection a shadow.
********************************************************************************************/
class OpChangeShadowType : public SelOperation
{

CC_DECLARE_DYNCREATE(OpChangeShadowType)

public:
	static BOOL Declare();
	static BOOL DoChangeShadowType(UndoableOperation* pOp, NodeShadowParam* pNSParam);

public:
	// Construction/Destruction
	OpChangeShadowType();
	~OpChangeShadowType();

	virtual void Do(OpDescriptor *pOpDesc);
	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);

	// These functions required for the OpDescriptor class
	static OpState GetState(String_256* Description, OpDescriptor*);
	static OpState GetParamState(String_256* pstrDescription, OpDescriptor* pOpDesc, OpParam* pOpParam);

//	void GetOpName(String_256 * pString);

//private:
//	void AddShadowToNode(Node * pNode);
//	UINT32 m_OpName;
};


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	OpRemoveShadow class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************************
>	class OpRemoveShadow : public SelOperation

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/11/96
	Purpose:	Remove a shadow object 
********************************************************************************************/
class OpRemoveShadow : public SelOperation
{

CC_DECLARE_DYNCREATE(OpRemoveShadow)

public:
	// Construction/Destruction
	OpRemoveShadow();
	~OpRemoveShadow();

//	virtual void Do(OpDescriptor *pOpDesc);
	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
		
	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);
};


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	OpShadowPosition class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************
>	class ShadowPosition : public OpParam

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/12/96
	Purpose:	Used by OpShadowPosition
********************************************************************************************/

class ShadowPosition : public OpParam
{
	CC_DECLARE_DYNCREATE(ShadowPosition)

public:
	ShadowPosition();
	ShadowPosition(const INT32 x, const INT32 y, BOOL UpdateX=TRUE, BOOL UpdateY=TRUE, SoftShadowTool* pTool=NULL);
	~ShadowPosition();

public:
	INT32 X;
	INT32 Y;
	BOOL m_bUpdateX;
	BOOL m_bUpdateY;
	SoftShadowTool* m_pTool;
};

/********************************************************************************************
>	class OpShadowPosition : public SelOperation

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/12/96
	Purpose:	Update the position of the shadow after modifying the infobar controls
********************************************************************************************/

class OpShadowPosition : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpShadowPosition)

public:
	OpShadowPosition();
	~OpShadowPosition();

	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	static OpState GetState(String_256* Description, OpDescriptor*);
	static BOOL Declare();

};


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	OpShadowPenumbra class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************************
>	class ShadowPosition : public OpParam

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/12/96
	Purpose:	Used by OpShadowPenumbra
********************************************************************************************/

class ShadowPenumbra : public OpParam
{
	CC_DECLARE_DYNCREATE(ShadowPenumbra)

public:
	ShadowPenumbra();
	ShadowPenumbra(const INT32 p, SoftShadowTool* pTool);
	~ShadowPenumbra();

public:
	INT32 P;
	SoftShadowTool* m_pTool;
};


/********************************************************************************************
>	class OpShadowPenumbra : public SelOperation

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/12/96
	Purpose:	Update the position of the shadow after modifying the infobar controls
********************************************************************************************/

class OpShadowPenumbra : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpShadowPenumbra)

public:
	OpShadowPenumbra();
	~OpShadowPenumbra();

	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	static OpState GetState(String_256* Description, OpDescriptor*);
	static BOOL Declare();
};


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	ChangePositionShadowAction class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************

>	class ChangePositionShadowAction : public Action

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/01/97
	Purpose:	An action which undoes the modification of the position of the shadow (X)
	SeeAlso:	-

********************************************************************************************/

class ChangePositionShadowAction : public Action
{

CC_DECLARE_DYNCREATE(ChangePositionShadowAction)

public:
	ChangePositionShadowAction();
	~ChangePositionShadowAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeShadowController* pThisNodeShadow,
							MILLIPOINT NewOffsetX,
							MILLIPOINT NewOffsetY,
							BOOL UpdateX,
							BOOL UpdateY,
							ChangePositionShadowAction** NewAction,
							BOOL Reverse = TRUE);
protected:
	NodeShadowController* m_pNodeShadowCont;
	MILLIPOINT	m_OldPositionX;
	MILLIPOINT  m_OldPositionY;
	BOOL m_bUpdateX;
	BOOL m_bUpdateY;
};


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	ChangePenumbraSizeAction class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************

>	class ChangePenumbraSizeAction : public Action

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/01/97
	Purpose:	An action which undoes the modification of the penumbra size
	SeeAlso:	-

********************************************************************************************/

class ChangePenumbraSizeAction : public Action
{

CC_DECLARE_DYNCREATE(ChangePenumbraSizeAction)

public:
	ChangePenumbraSizeAction();
	~ChangePenumbraSizeAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeShadowController* pThisNodeShadow,
							MILLIPOINT NewPenumbraSize,
							ChangePenumbraSizeAction** NewAction,
							BOOL bReverse = TRUE,
							BOOL bCache = FALSE);
protected:
	NodeShadowController* m_pNodeShadowCont;
	MILLIPOINT	m_OldPenumbraSize;
	DocRect m_LastRect;
	BOOL m_bCache;
};


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	NodeShadowClick class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************************
>	class NodeShadowClick : public OpParam

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/01/97
	Purpose:	When a user click, used by SoftShadowTool::DoWithParam()
********************************************************************************************/

class NodeShadowClick : public OpParam
{
	CC_DECLARE_DYNCREATE(NodeShadowClick)

public:
	NodeShadowClick();
	NodeShadowClick(Node *p, SoftShadowTool* pTool);
	~NodeShadowClick();

public:
	Node *m_pNode;
	SoftShadowTool* m_pTool;
};

/********************************************************************************************
>	class NodeShadowParam : public OpMenuParam

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/6/99
	Purpose:	Creation parameter for shadows (i.e. OpApplyShadow)
********************************************************************************************/
class NodeShadowParam : public OpMenuParam
{
public:
	NodeShadowParam(ShadowType Type				= NodeShadowController::DefaultType,
					double FloorShadowAngle		= NodeShadowController::DefaultFloorAngle,
					double FloorShadowHeight	= NodeShadowController::DefaultFloorHeight,
					INT32 OffsetX					= NodeShadowController::DefaultWallOffsetX,
					INT32 OffsetY					= NodeShadowController::DefaultWallOffsetY,
					INT32 Blur					= NodeShadowController::DefaultBlurSize,
					double Darkness				= NodeShadowController::DefaultDarkness,
					double Scale				= NodeShadowController::DefaultScale,
					MILLIPOINT Width			= NodeShadowController::DefaultGlowWidth,
					const CProfileBiasGain &Profile	= CProfileBiasGain(),
					BOOL bRedraw				= TRUE,
					MILLIPOINT FeatherWidth		= NodeShadowController::DefaultFeatherWidth
					) :
		m_Type(Type),
		m_FloorShadowAngle(FloorShadowAngle),
		m_FloorShadowHeight(FloorShadowHeight),
		m_OffsetX(OffsetX),
		m_OffsetY(OffsetY),
		m_Blur(Blur),
		m_dDarkness(Darkness),
		m_Scale(Scale),
		m_GlowWidth(Width),
		m_FeatherWidth(FeatherWidth),
		m_bRedraw(bRedraw),
		m_Profile(Profile)
	{
		StackPosition = STACKPOS_INSERT_TOP;
		pPPStack = NULL;
		pShadowTool = NULL;
	}

	ShadowType			m_Type;
	double				m_FloorShadowAngle;
	double				m_FloorShadowHeight;
	INT32				m_OffsetX;
	INT32				m_OffsetY;
	INT32			    m_Blur;
	double				m_dDarkness;
	double				m_Scale;
	MILLIPOINT			m_GlowWidth;
	MILLIPOINT			m_FeatherWidth;
	BOOL				m_bRedraw;
	CProfileBiasGain	m_Profile;

	INT32				StackPosition;			// PostProcessor Stack position
	EffectsStack*		pPPStack;				// PostProcessor Stack
	SoftShadowTool*		pShadowTool;
};

/********************************************************************************************

>	class OpApplyAttrib : public SelOperation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/1/95
	Purpose:	Virtual base class for ops that apply attibutes.

********************************************************************************************/

class CCAPI OpApplyAttribForShadows: public OpApplyAttribToSelected
{         
	CC_DECLARE_DYNCREATE( OpApplyAttribForShadows )    

public:
	static BOOL Init();


	
protected:
	// DMc
	// applies a fill attribute to a shadow node
	BOOL DoApply(Node* CurrentNode, 
							NodeAttribute* Attrib, 
							BOOL Mutate, 
							BOOL InvalidateRegion,
							BOOL KeepExistingCols, /* = TRUE */
							BOOL* AttribWasRequired    /* = NULL */);
};

/********************************************************************************************

>	class ChangeFloorShadowHeightAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Action for changing floor shadow heights
	SeeAlso:	-

********************************************************************************************/

class ChangeFloorShadowHeightAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeFloorShadowHeightAction)

public:
	ChangeFloorShadowHeightAction();
	~ChangeFloorShadowHeightAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeShadowController* pThisNodeShadow,
							double NewHeight,
							ChangeFloorShadowHeightAction** NewAction,
							BOOL bReverse = TRUE,
							BOOL bCache = FALSE);
protected:
	NodeShadowController* m_pNodeShadowCont;
	double	m_LastHeight;
	DocRect m_LastRect;
	BOOL m_bCache;
};

/********************************************************************************************

>	class ChangeFloorShadowAngleAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Action for changing floor shadow heights
	SeeAlso:	-

********************************************************************************************/

class ChangeFloorShadowAngleAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeFloorShadowAngleAction)

public:
	ChangeFloorShadowAngleAction();
	~ChangeFloorShadowAngleAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeShadowController* pThisNodeShadow,
							INT32 NewAngle,
							ChangeFloorShadowAngleAction** NewAction,
							BOOL bReverse = TRUE,
							BOOL bCache = FALSE);
protected:
	NodeShadowController* m_pNodeShadowCont;
	INT32	m_LastAngle;
	DocRect m_LastRect;
	BOOL m_bCache;
};

/********************************************************************************************

>	class ChangeShadowTypeAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Action for changing floor shadow heights
	SeeAlso:	-

********************************************************************************************/

class ChangeShadowTypeAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeShadowTypeAction)

public:
	ChangeShadowTypeAction();
	~ChangeShadowTypeAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeShadowController* pThisNodeShadow,
							ShadowType NewType,
							ChangeShadowTypeAction** NewAction,
							BOOL bReverse = TRUE);
protected:
	NodeShadowController* m_pNodeShadowCont;
	ShadowType	m_LastType;
	DocRect m_LastRect;
};

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	OpShadowAngle class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************************
>	class OpShadowAngle : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Update the angle of the selected shadows
********************************************************************************************/

class OpShadowAngle : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpShadowAngle)

public:
	OpShadowAngle();
	~OpShadowAngle();

	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	static OpState GetState(String_256* Description, OpDescriptor*);
	static BOOL Declare();

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};

/********************************************************************************************
>	class OpShadowHeightAndAngle : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Update the angle and height of the selected shadows
				Used by the blob rendering / manipulation code in ShadowTool
********************************************************************************************/

class OpShadowHeightAndAngle : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpShadowHeightAndAngle)

public:
	OpShadowHeightAndAngle();
	~OpShadowHeightAndAngle();

	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	static OpState GetState(String_256* Description, OpDescriptor*);
	static BOOL Declare();
};


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	OpShadowHeight class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************************
>	class OpShadowHeight : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Update the height of the selected shadows
********************************************************************************************/

class OpShadowHeight : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpShadowHeight)

public:
	OpShadowHeight();
	~OpShadowHeight();

	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	static OpState GetState(String_256* Description, OpDescriptor*);
	static BOOL Declare();
};

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	OpShadowScale class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************************
>	class OpShadowScale : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Update the angle of the selected shadows
********************************************************************************************/

class OpShadowScale : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpShadowScale)

public:
	OpShadowScale();
	~OpShadowScale();

	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	static OpState GetState(String_256* Description, OpDescriptor*);
	static BOOL Declare();
};

/********************************************************************************************

>	class ChangeShadowScaleAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Action for changing shadow scale factors
	SeeAlso:	-

********************************************************************************************/

class ChangeShadowScaleAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeShadowScaleAction)

public:
	ChangeShadowScaleAction();
	~ChangeShadowScaleAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeShadowController* pThisNodeShadow,
							double NewScale,
							ChangeShadowScaleAction** NewAction,
							BOOL bReverse = TRUE);
protected:
	NodeShadowController* m_pNodeShadowCont;
	double m_LastScale;
	DocRect m_LastRect;
};

/********************************************************************************************

>	class SaveShadowDataAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Saves all the shadow data for regeneration purposes on undo/redo
	SeeAlso:	-

********************************************************************************************/

class SaveShadowDataAction : public Action
{

CC_DECLARE_DYNCREATE(SaveShadowDataAction)

public:
	SaveShadowDataAction();
	~SaveShadowDataAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							Range &MyRange,
							SaveShadowDataAction** NewAction,
							BOOL bReverse = TRUE);
protected:
	Range * m_pSelRange;
	List m_DataList;
	DocRect m_LastRect;
};

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	OpSaveShadowData class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/********************************************************************************************
>	class SaveShadowDataInfo : public OpParam

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	The id for the op to give in the undo/redo menus
********************************************************************************************/
class SaveShadowDataInfo : public OpParam
{
public:
	SaveShadowDataInfo() { ID = 0; }

	UINT32 ID;
};

/********************************************************************************************
>	class OpSaveShadowData : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Save the current selection's shadow data (to be restored on undo/redo)
********************************************************************************************/

class OpSaveShadowData : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpSaveShadowData)

public:
	OpSaveShadowData();
	~OpSaveShadowData();

	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	static OpState GetState(String_256* Description, OpDescriptor*);
	static BOOL Declare();

	// this is public so other fns can use it
	static BOOL SaveShadowData(UndoableOperation * pOp);

	void GetOpName(String_256 * pString);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }

private:
	UINT32 m_OpName;
};

/********************************************************************************************

>	class ChangeGlowWidthAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/99
	Purpose:	Action for changing glow widths
	SeeAlso:	-

********************************************************************************************/

class ChangeGlowWidthAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeGlowWidthAction)

public:
	ChangeGlowWidthAction();
	~ChangeGlowWidthAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeShadowController* pThisNodeShadow,
							INT32 NewWidth,
							ChangeGlowWidthAction** NewAction,
							BOOL bReverse = TRUE,
							BOOL bCache = FALSE);
protected:
	NodeShadowController* m_pNodeShadowCont;
	INT32	m_LastWidth;
	DocRect m_LastRect;
	BOOL m_bCache;
};

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////	OpGlowWidth class
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************************
>	class OpGlowWidth : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Update the width of the selected glows
********************************************************************************************/

class OpGlowWidth : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpGlowWidth)

public:
	OpGlowWidth();
	~OpGlowWidth();

	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	static OpState GetState(String_256* Description, OpDescriptor*);
	static BOOL Declare();
};

/********************************************************************************************
>	class ShadowProfileOpParam : public OpParam

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/12/96
	Purpose:	Used by OpShadowPosition
********************************************************************************************/

class ShadowProfileOpParam : public OpParam
{
	CC_DECLARE_DYNCREATE(ShadowProfileOpParam)

public:
	ShadowProfileOpParam() { m_pTool=NULL; }
	ShadowProfileOpParam(CProfileBiasGain newProfile, SoftShadowTool* pTool) { Profile = newProfile; m_pTool=pTool; }
	~ShadowProfileOpParam() { };

public:
	CProfileBiasGain Profile;
	SoftShadowTool* m_pTool;
};



/********************************************************************************************
>	class OpChangeShadowProfile : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Update the width of the selected glows
********************************************************************************************/

class OpChangeShadowProfile : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpChangeShadowProfile)

public:
	OpChangeShadowProfile();
	~OpChangeShadowProfile();

	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	static OpState GetState(String_256* Description, OpDescriptor*);
	static BOOL Declare();

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};

/********************************************************************************************

>	class ChangeProfileAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/99
	Purpose:	Action for changing shadow profiles
	SeeAlso:	-

********************************************************************************************/

class ChangeProfileAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeProfileAction)

public:
	ChangeProfileAction();
	~ChangeProfileAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeShadow* pThisNodeShadow,
							CProfileBiasGain &Profile,
							ChangeProfileAction** NewAction,
							BOOL bReverse = TRUE,
							BOOL bCache = FALSE);

	static void ChangeShadowProfileWithNoUndo (CProfileBiasGain &Profile, SoftShadowTool* pTool);
protected:
	NodeShadow* m_pNodeShadow;
	CProfileBiasGain m_LastProfile;	
};

/********************************************************************************************
>	class ShadowDarknessOpParam : public OpParam

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/12/96
	Purpose:	Used by OpShadowPosition
********************************************************************************************/

class ShadowDarknessOpParam : public OpParam
{
	CC_DECLARE_DYNCREATE(ShadowDarknessOpParam)

public:
	ShadowDarknessOpParam() { m_dDarkness = 0; m_pTool=NULL; }
	ShadowDarknessOpParam(double dNewDarkness, SoftShadowTool* pTool) { m_dDarkness = dNewDarkness; m_pTool=pTool; }
	~ShadowDarknessOpParam() { };

public:
	double m_dDarkness;
	SoftShadowTool* m_pTool;
};



/********************************************************************************************
>	class OpChangeShadowDarkness : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/99
	Purpose:	Update the width of the selected glows
********************************************************************************************/

class OpChangeShadowDarkness : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpChangeShadowDarkness)

public:
	OpChangeShadowDarkness();
	~OpChangeShadowDarkness();

	virtual void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	static OpState GetState(String_256* Description, OpDescriptor*);
	static BOOL Declare();

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};

/********************************************************************************************

>	class ChangeShadowDarknessAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/99
	Purpose:	Action for changing shadow profiles
	SeeAlso:	-

********************************************************************************************/

class ChangeShadowDarknessAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeShadowDarknessAction)

public:
	ChangeShadowDarknessAction();
	~ChangeShadowDarknessAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							NodeShadow* pThisNodeShadow,
							double dDarkness,
							ChangeShadowDarknessAction** NewAction,
							BOOL bReverse = FALSE,
							BOOL bCache = FALSE);
protected:
	NodeShadow* m_pNodeShadow;
	double m_dLastDarkness;
};











#endif		// BUILDSHADOWS
#endif 		// INC_OPSHADOW
 
