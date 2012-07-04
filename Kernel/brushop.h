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


// operations involving brush definitions

#ifndef INC_BRUSHOP
#define INC_BRUSHOP

#include "opdrbrsh.h"

#define OPTOKEN_CHANGEBRUSHDEF _T("ChangeBrushDefinition")
#define OPTOKEN_SELECTBRUSH _T("MakeBrushSelected")
#define OPTOKEN_DELETEBRUSH _T("DeactivateBrush")

/********************************************************************************************

>	class OpChangeBrushDefinition : public SelOperation

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/11/99
	Purpose:	This operation exists so that we can make undoable edits to the brush definitions
				stored in the brush component
	SeeAlso:	-

********************************************************************************************/

class OpChangeBrushDefinition : public UndoableOperation
{
CC_DECLARE_DYNCREATE(OpChangeBrushDefinition);

public:
	// Construction/Destruction
	OpChangeBrushDefinition();  					

	~OpChangeBrushDefinition();

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	// The all-important Do() func
	virtual void DoWithParam(OpDescriptor*,OpParam* pOpParam);
	virtual void GetOpName(String_256* OpName);

private:
	ChangeBrushType ChangeType;
};


/********************************************************************************************

>	class ChangeBrushDefOpParam : public ChangeBrushOpParam

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/99
	Purpose:	The param passed to OpChangeBrushDefinition::DoWithParam, identical to ChangeBrushOpParam
				except for 1) it has a brush handle member and 2) it takes its old and new values
				from its brush definition instead of a path processor
	SeeAlso:	-

********************************************************************************************/

class ChangeBrushDefOpParam : public ChangeBrushOpParam
{

CC_DECLARE_DYNAMIC(ChangeBrushDefOpParam)

public:
	ChangeBrushDefOpParam() { m_Handle = BrushHandle_NoBrush;}
	ChangeBrushDefOpParam(const ChangeBrushOpParam& Other);
	~ChangeBrushDefOpParam() {};

	void SetOldValues(BrushDefinition* pBrushedNode);
	void SetNewValues(BrushDefinition* pBrushedNode);

	virtual ChangeBrushOpParam operator=(const ChangeBrushOpParam& Other);

public:
	BrushHandle m_Handle;

};

/********************************************************************************************

>	class ChangeBrushDefAction : public Action

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/3/2000
	Purpose:	An action which changes one or all of the members of a brush definition
	SeeAlso:	ChangeBrushAction, which this is based upon

********************************************************************************************/

class ChangeBrushDefAction : public Action
{

CC_DECLARE_DYNCREATE(ChangeBrushDefAction)

public:
	ChangeBrushDefAction();
	~ChangeBrushDefAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							ChangeBrushDefOpParam* pChangeParam,
							ChangeBrushDefAction** NewAction);
protected:	
	// helper functions
	static BOOL ChangeBrushName(String_32 Name, BrushDefinition* pBrushDef);
	static BOOL ChangeBrushSpacing(MILLIPOINT NewSpacing,  BrushDefinition* pBrushDef);
	static BOOL ChangeSpacingIncrProp(double NewIncr,  BrushDefinition* pBrushDef);
	static BOOL ChangeSpacingIncrConst(MILLIPOINT NewIncr, BrushDefinition* pBrushDef);
	static BOOL ChangeBrushScaling(double NewScaling, BrushDefinition* pBrushDef);
	static BOOL ChangeScalingRandSeed(UINT32 NewSeed, BrushDefinition* pBrushDef);
	static BOOL ChangeScalingIncr(double NewIncr, BrushDefinition* pBrushDef);
	static BOOL ChangeScalingIncrConst(double Incr, BrushDefinition* pBrushDef);
	static BOOL ChangeScalingPressure(UINT32 Pressure, BrushDefinition* pBrushDef);
	static BOOL ChangeScalingMaxRand(UINT32 NewMax, BrushDefinition* pBrushDef);
	static BOOL ChangeTangential(BOOL bRotate, BrushDefinition* pBrushDef);
	static BOOL ChangeRotation(double NewAngle, BrushDefinition* pBrushDef);
	static BOOL ChangeRotationRandSeed(UINT32 NewSeed, BrushDefinition* pBrushDef);
	static BOOL ChangeRotationMaxRand(UINT32 NewMax, BrushDefinition* pBrushDef);
	static BOOL ChangeRotationMaxPressure(UINT32 Pressure, BrushDefinition* pBrushDef);
	static BOOL ChangeOffsetValue(MILLIPOINT NewOffset, BrushDefinition* pBrushDef);
	static BOOL ChangeOffsetType(PathOffset NewOffset, BrushDefinition* pBrushDef);
	static BOOL ChangeOffsetTypeSeed(UINT32 NewSeed, BrushDefinition* pBrushDef);
	static BOOL ChangeOffsetIncrProp(double NewIncrProp, BrushDefinition* pBrushDef);
	static BOOL ChangeOffsetIncrConst(MILLIPOINT NewIncrConst, BrushDefinition* pBrushDef);
	static BOOL ChangeOffsetValMaxRand(UINT32 NewMax, BrushDefinition* pBrushDef);
	static BOOL ChangeOffsetValRandSeed(UINT32 NewSeed, BrushDefinition* pBrushDef);
	static BOOL ChangeBrushTile(BOOL bTile, BrushDefinition* pBrushDef);
	static BOOL ChangeSpacingMaxRand(UINT32 NewMaxRand, BrushDefinition* pBrushDef);
	static BOOL ChangeSpacingRandSeed(UINT32 NewSeed, BrushDefinition* pBrushDef);
	static BOOL ChangeUseLocalFillColour(BOOL bUseLocal, BrushDefinition* pBrushDef);
	static BOOL ChangeUseLocalGradFill(BOOL bUseLocal, BrushDefinition* pBrushDef);
	static BOOL ChangeSequenceType(SequenceType SeqType, BrushDefinition* pBrushDef);
	static BOOL ChangeSequenceSeed(UINT32 NewSeed, BrushDefinition* pBrushDef);
	static BOOL ChangeAll(ChangeBrushOpParam* pParam, BrushDefinition* pBrushDef);
	static BOOL ChangeTimeStamp(double NewValue, BrushDefinition* pBrushDef);
	
protected: // data
	ChangeBrushDefOpParam 	m_ChangeParam;
};

/********************************************************************************************

>	class OpSelectBrush : public Operation

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/2000
	Purpose:	This operation can take place only in the Freehand tool. If there is a single
				selected brush then it makes that brush selected in the combo so that the
				user can draw with it straight away rather than having to select it in the
				combo themselves.
				Note that it is not undoable because a) it makes no change to anything in the document
				and b) it can only be called whilst in the Freehand tool (and what would happen if 
				it were undone outside of the  Freehand tool is rather hard to define).
	SeeAlso:	-

********************************************************************************************/

class OpSelectBrush : public Operation
{
	CC_DECLARE_DYNCREATE(OpSelectBrush)

public:
	// Construction/Destruction
	OpSelectBrush();  					

	~OpSelectBrush();

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	// The all-important Do() func
	virtual void Do(OpDescriptor*);
	virtual void GetOpName(String_256* OpName);

};


/********************************************************************************************

>	class OpDeactivateBrush : public UndoableOperation

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/2000
	Purpose:	This operation takes a brush handle as a parameter, locates the appropriate brush
				definition and sets the flag indicating that it has been deactivated.
				Also removes the item from the line gallery and freehand combo.
	SeeAlso:	-

********************************************************************************************/

class OpDeactivateBrush : public UndoableOperation
{
	CC_DECLARE_DYNCREATE(OpDeactivateBrush);
public:
	OpDeactivateBrush();
	~OpDeactivateBrush();

	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

	// The all-important Do() func
	virtual void DoWithParam(OpDescriptor*,OpParam* pOpParam);
	virtual void GetOpName(String_256* OpName);
};



/********************************************************************************************

>	class DeactivateBrushDefAction : public Action

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/3/2000
	Purpose:	Does most of the dirty work for the above operation
	SeeAlso:	OpDeactivateBrush

********************************************************************************************/

class DeactivateBrushDefAction : public Action
{
	CC_DECLARE_DYNCREATE(DeactivateBrushDefAction)
	
		DeactivateBrushDefAction() {m_Handle = BrushHandle_NoBrush;}

public:
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							BrushHandle Handle,
							DeactivateBrushDefAction** NewAction);


	BrushHandle m_Handle;
};


#endif
