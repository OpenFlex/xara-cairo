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

// Header for the regular shape tool implementation

#ifndef INC_REGSHAPETOOL
#define INC_REGSHAPETOOL

//#include "bars.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "doccoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "nodershp.h"
#include "shapeops.h"
//#include "peter.h"
//#include "tool.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "viewrc.h"
#include "dragtool.h"

class Cursor;
class Spread;
class QuickShapeBaseInfoBarOp;
class EditRegularShapeParam;

const INT32 MAX_EDIT_FIELD_LENGTH = 5;

/********************************************************************************************

>	class QuickShapeBase : public Tool_v1

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/11/94
	Purpose:	The base class for the Quick shape tool family.  Not actually a tool itself
				but the QuickShape, Ellipse and Rectangle tool are derived from it.

********************************************************************************************/

class CCAPI QuickShapeBase : public DragTool
{
CC_DECLARE_MEMDUMP(QuickShapeBase);

public:
	QuickShapeBase();
	~QuickShapeBase();

	// Standard calls your tool must provide
	BOOL Init();
	
	// Some very common event handlers
	void SelectChange(BOOL isSelected);
	void OnClick( DocCoord, ClickType, ClickModifiers, Spread* );
	void OnMouseMove(DocCoord PointerPos,Spread* pSpread, ClickModifiers ClickMods);
	BOOL GetStatusLineText(String_256* ptext, Spread* pSpread, DocCoord DocPos, ClickModifiers ClickMods);

	// Some useful static functions
	QuickShapeBaseInfoBarOp* 	GetInfoBar()	{ return pQuickShapeBaseInfoBarOp; }

	enum EditModeIDS {EDITF_CENTRE, EDITF_MAJOR, EDITF_STELLATION, EDITF_CURVE, EDITF_SIZE, EDITF_ROT};
	EditModeIDS EditFieldMode;
	EditModeIDS EditFieldOptions[MAX_EDIT_FIELD_LENGTH];

	// Override these to return the creation settings
	virtual INT32 GetNumSides() = 0;
	virtual INT32 GetCreationMode() = 0;
	virtual BOOL GetPolygon() = 0;
	virtual BOOL GetStellation() = 0;
	virtual BOOL GetCurved() = 0;
	virtual void SetNumSides(INT32 NewValue) = 0;
	virtual void SetCreationMode(INT32 NewValue) = 0;
	virtual void SetPolygon(BOOL NewValue) = 0;
	virtual void SetStellation(BOOL NewValue) = 0;
	virtual void SetCurved(BOOL NewValue) = 0;

	virtual BOOL ForcePolygonToGrey() = 0;
	virtual BOOL ForceEllipseToGrey() = 0;
	virtual BOOL ForceStellationToGrey() = 0;
	virtual BOOL ForceCurvatureToGrey() = 0;
	virtual BOOL ForceNumSidesToGrey() = 0;
	virtual BOOL IsInterestingShape(NodeRegularShape* pShape) = 0;
	virtual INT32 GetShapesToAffect() =0;
	virtual BOOL DoesPolygonExist() = 0;
	virtual BOOL DoesEllipseExist() = 0;
	virtual BOOL DoesStellationExist() = 0;
	virtual BOOL DoesCurvatureExist() = 0;
	virtual BOOL DoesReformSidesExist() = 0;
	virtual BOOL DoesNumSidesExist() = 0;
	virtual INT32 GetCursorID() = 0;
	virtual INT32 GetShapeID() = 0;
	virtual INT32 GetShapesID() = 0;
	virtual BOOL CanReformEdges() {return FALSE;};

	virtual BOOL IsEllipse() {return FALSE;};
	virtual BOOL IsRectangle() {return FALSE;};

protected:
	void DisplayStatusBarHelp(DocCoord DocPos, Spread* pSpread, ClickModifiers ClickMods);
	void GetCurrentStatusLineText(String_256* ptext, Spread* pSpread, DocCoord DocPos, ClickModifiers ClickMods);
	ShapeClickEffect DetermineClickEffect(DocCoord PointerPos, Spread* pSpread, NodeRegularShape** ReturnShape = NULL);
	void ExpandShapeString(StringBase* pString, INT32 StringID, BOOL Singular);

	QuickShapeBaseInfoBarOp* pQuickShapeBaseInfoBarOp;	// Ptr to your tool's infobar

	BOOL CreateCursors();						// Create  your tool's cursors in this func
	void DestroyCursors();						// Destroy your tool's cursors in this func

	Cursor*	pcNormalCursor;						// Your standard cursor to use when your tool becomes active
	Cursor*	pcBlobCursor;						// The cursor to display over shape blobs
	Cursor*	pcEdgeCursor;						// The cursor to display over shape path edges.
	Cursor*	pcCurrentCursor;					// The cursor your tool is currently displaying
	INT32 CurrentCursorID;

	// DetermineClickEffect caches its last result to avoid excessive document scanning
	DocCoord OldDeterminePos;
	Spread*	OldDetermineSpread;
	NodeRegularShape* OldDetermineShape;
	ShapeClickEffect OldDetermineResult;
};



/********************************************************************************************

>	class QuickShapeBaseInfoBarOp : public InformationBarOp

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/11/94
	Purpose:	Class for handling the Regular Shape tool's information bar.

********************************************************************************************/
class QuickShapeBaseInfoBarOp : public InformationBarOp
{
	CC_DECLARE_DYNCREATE( QuickShapeBaseInfoBarOp )  

public:
	QuickShapeBaseInfoBarOp( QuickShapeBase *pTool = NULL, ResourceID r=_R(IDD_REGSHAPETOOLBAR) )
	{
		DlgResID = r;
		pQuickShapeBase = pTool;
		ChangeMode = FALSE;
		CurrentSpread = NULL;
		BumpAmount = 0;
		PreviousCurvature = FALSE;
		PreviousStellation = FALSE;
		PreviousCircular = FALSE;
	};				// Dummy default constructor for DYNCREATE

	MsgResult Message(Msg* Msg);			// All messages to the info bar come through here
	MsgResult DialogMessage(DialogMsg* Msg);	// Handles dialogue messages aimed at the infobar
	BOOL InitialiseInfobar();	
	BOOL SetBarFromSelection();	

	// Functions to read and write the infobar status.
	INT32		GetCreationMode();
	void	SetCreationMode(INT32 NewMode);

	// Functions to read and write the polygon/ellipse status.
	BOOL	IsPolygonCreate();
	void	SetPolygonCreate(BOOL PolygonCreate);

	// Functions to read/write the stellation button.
	BOOL	IsStellationCreate();
	void	SetStellationCreate(BOOL StellationCreate);

	// Functions to read/write the curved button
	BOOL	IsCurvedCreate();
	void	SetCurvedCreate(BOOL CurvedCreate);

	// Functions to read/write the number of sides edit field
	INT32		GetNumSides(BOOL Error);
	void	SetNumSides(INT32 NumberSides);

	// Various other functions
	BOOL AreShapesSelected();
	void SetToolMode();
	void UpdateInfobar();
	void BuildEditMenu(BOOL UpdateImmediate = FALSE);
	void UpdateEditFields(NodeRegularShape* ShapeToShow = NULL, Spread* ShapeSpread = NULL);
	BOOL SetEdit(CGadgetID gid, INT32 nValue, BOOL PaintNow);
	BOOL SetEditPosition(CGadgetID gidX, CGadgetID gidY, DocCoord loc, Spread* pSpread, BOOL PaintNow);
	BOOL EditCommit(BOOL UpperCommit);
	BOOL GetFieldCoord(DocCoord* pCoord, Spread* pSpread);
	BOOL BumpLeft();
	BOOL BumpRight();
	BOOL BumpUp();
	BOOL BumpDown();
	void SetHelp();
	BOOL IsEnabled(CGadgetID gid);

	BOOL EditCommitCentre(BOOL UpperCommit, EditRegularShapeParam* ChangeData);
	BOOL EditCommitSizeAndRotation(BOOL UpperCommit, EditRegularShapeParam* ChangeData);
	BOOL EditCommitStellation(BOOL UpperCommit, EditRegularShapeParam* ChangeData);
	BOOL EditCommitCurvature(BOOL UpperCommit, EditRegularShapeParam* ChangeData);
	BOOL EditCommitWidthAndHeight(BOOL UpperCommit, EditRegularShapeParam* ChangeData);
	BOOL EditCommitRotation(BOOL UpperCommit, EditRegularShapeParam* ChangeData);

	double RestrictAngleZero360(double Current);
	double RestrictAngleMinus180(double Current);

	// Data members
	QuickShapeBase*	pQuickShapeBase;
	BOOL	ChangeMode;
	Spread* CurrentSpread;
	INT32	BumpAmount;
	BOOL	PreviousCurvature;
	BOOL	PreviousStellation;
	BOOL	PreviousCircular;
};

/********************************************************************************************

>	class QuickShapeBaseInfoBarOpCreate : public BarCreate

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/94
	Purpose:	Class for creating RegShapeInfoBarOps.
				Derived classes of BarCreate are used by DialogBarOp::ReadBarsFromFile()

********************************************************************************************/

class QuickShapeBaseInfoBarOpCreate : public BarCreate
{
public:
	DialogBarOp* Create() { return (new QuickShapeBaseInfoBarOp); }
};

/********************************************************************************************

>	class QuickShapeTool : public QuickShapeBase

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/03/95
	Purpose:	The QuickShape tool.

********************************************************************************************/

class CCAPI QuickShapeTool : public QuickShapeBase
{
CC_DECLARE_MEMDUMP(QuickShapeTool);

public:
	QuickShapeTool();
	~QuickShapeTool();

	BOOL Init();
	void Describe(void* InfoPtr);
	UINT32 GetID() { return TOOLID_REGSHAPE; };

	// The creation mode functions
	INT32 GetNumSides() {return NumSides;};
	INT32 GetCreationMode() {return CreationMode;};
	BOOL GetPolygon() {return CreatePolygons;};
	BOOL GetStellation() {return CreateStellated;};
	BOOL GetCurved() {return CreateCurved;};
	void SetNumSides(INT32 NewValue);
	void SetCreationMode(INT32 NewValue);
	void SetPolygon(BOOL NewValue);
	void SetStellation(BOOL NewValue);
	void SetCurved(BOOL NewValue);
	BOOL ForcePolygonToGrey() {return FALSE;};
	BOOL ForceEllipseToGrey() {return FALSE;};
	BOOL ForceStellationToGrey() {return FALSE;};
	BOOL ForceCurvatureToGrey() {return FALSE;};
	BOOL ForceNumSidesToGrey() {return FALSE;};
	BOOL DoesPolygonExist() {return TRUE;};
	BOOL DoesEllipseExist() {return TRUE;};
	BOOL DoesStellationExist() {return TRUE;};
	BOOL DoesCurvatureExist() {return TRUE;};
	BOOL DoesReformSidesExist() {return TRUE;};
	BOOL DoesNumSidesExist() {return TRUE;};
	BOOL IsInterestingShape(NodeRegularShape* pShape);
	INT32 GetShapesToAffect() {return EditRegularShapeParam::AFFECT_ALL;};
	INT32 GetCursorID() {return _R(IDC_REGSHAPETOOLCURSOR);};
	INT32 GetShapeID() {return _R(IDS_REGSHAPE_SINGULAR);};
	INT32 GetShapesID() {return _R(IDS_REGSHAPE_PLURAL);};
	BOOL CanReformEdges() {return TRUE;};

	
private:
	// Keep copies of the creation mode, etc... so when tool is deselected then reselected
	// the info bar is unaffected.
	static INT32 CreationMode;
	static INT32 NumSides;
	static BOOL	CreatePolygons;
	static BOOL	CreateStellated;
	static BOOL	CreateCurved;

	// Standard tool static vars
	static 	TCHAR* FamilyName;				
	static 	TCHAR* ToolName;					
	static 	TCHAR* Purpose;					
	static 	TCHAR* Author;					
};



#endif 		// INC_REGSHAPETOOL




