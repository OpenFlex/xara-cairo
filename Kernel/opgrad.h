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

// The Grad Fill creation and Editing operations


#ifndef INC_OPGRAD
#define INC_OPGRAD

//#include "selop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "fillattr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "attrappl.h"
//#include "flags.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "fillramp.h"

#define OPTOKEN_GRADFILL 	_T("GraduatedFill")
#define OPTOKEN_EDITFILL    _T("EditGraduatedFill")
#define OPTOKEN_MUTATEFILL  _T("MutateGraduatedFill")
#define OPTOKEN_CHANGEFILL  _T("ChangeFillColour")
#define OPTOKEN_SELECTCOLS  _T("ChangeSelectionColours")

class Spread;

// These are lots of helper functions for drawing the fill meshes.
// Some of them won't be needed eventually, and others should really
// be in the Blob Manager.
void MakeMeshArrow(Path *, DocCoord &, DocCoord &, DocCoord*);
void MakeMeshDottedLine(Path *, DocCoord &, DocCoord &);
void MakeMeshSemiCircle(Path *, DocCoord , DocCoord, DocCoord);
void MakeMeshEllipse(Path *, DocCoord , DocCoord , DocCoord End2 = DocCoord(0,0));
void CalcMeshEllipseEdge(const DocCoord&, const DocCoord&, DocCoord*, DocCoord*, DocCoord*);
DocRect GetMeshSemiCircleBounds(DocCoord Start, DocCoord End, DocCoord End2);
DocRect GetMeshEllipseBounds(DocCoord Start, DocCoord End, DocCoord End2 = DocCoord(0,0));
DocCoord MakeLineAtAngle(DocCoord Start, DocCoord End, ANGLE Offset = 90, INT32 Length = 0);
ANGLE CalcLineAngle(DocCoord Start, DocCoord End);
void MakePerpendicularMeshLines(DocCoord, DocCoord, DocRect, DocCoord*);
DocCoord CentreOf(DocRect Rect);
void MakeMeshParallelagram(Path*, DocCoord, DocCoord, DocCoord);
void GetMeshParallelagram(DocCoord, DocCoord, DocCoord,
							DocCoord*, DocCoord*, DocCoord*, DocCoord*);
DocRect GetParallelagramBounds(DocCoord, DocCoord, DocCoord);
void GetBitmapVirtualPoints(DocCoord Start, DocCoord End, DocCoord End2,
							DocCoord* P1, DocCoord* P2, DocCoord* P3);
void GetBitmapRealPoints(DocCoord Start, DocCoord End, DocCoord End2,
							DocCoord* P1, DocCoord* P2, DocCoord* P3);

void IncludeArrowHead(DocRect* Bounds, DocCoord Start, DocCoord End);

BOOL AreLinesPerpendicular(DocCoord* Start, DocCoord* End, DocCoord* End2);

/********************************************************************************************

>	class OpCreateFill : public Operation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/7/94
	Purpose:	An operation to add a Linear Graduated Fill to the selected Object(s).

********************************************************************************************/

class OpCreateFill : public Operation
{

CC_DECLARE_DYNCREATE(OpCreateFill);

public:
	// Construction/Destruction
	OpCreateFill();

	// Virtual functions needed for the dragging operations to work
	virtual void DoDrag( AttrFillGeometry*, Spread* pSpread, DocCoord Anchor);
	virtual void DragPointerMove( DocCoord PointerPos, ClickModifiers ClickMods, Spread*, BOOL bSolidDrag);
	virtual void DragFinished(	DocCoord PointerPos, 
								ClickModifiers ClickMods, Spread*, 
								BOOL Success, BOOL bSolidDrag);


	// Some Render functions to draw the EORed control lines
	virtual void RenderDragBlobs( DocRect, Spread* , BOOL bSolidDrag);

	// These functions required for the OpDescriptor class
	static BOOL Init();
	static OpState GetState(String_256* Description, OpDescriptor*);

	// interogates the current (drag) Operation for statusLine text
	virtual BOOL GetStatusLineText(String_256* pText, Spread* pSpread, DocCoord DocPos, ClickModifiers ClickMods);

private:
	DocRect GetDragBlobRect();
		
protected:
	// Infomation about what we are editing
	AttrFillGeometry*	GradFill;
	Spread*   			StartSpread;

	// Mouse Positions
	DocCoord  		StartPoint;
	DocCoord  		LastMousePosition;
};



/********************************************************************************************

********************************************************************************************/



/********************************************************************************************

>	class OpEditFill : public OpApplyAttribToSelected

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/7/94
	Purpose:	This operation edits an AttrLinearFill already in the tree. 
				It is normally started when the Tool detects a drag on one of its selected
				blobs.

********************************************************************************************/

class OpEditFill : public OpApplyAttribToSelected
{
CC_DECLARE_DYNCREATE(OpEditFill);

public:
	// Construction/Destruction
	OpEditFill();

	// The all important Do functions
	void DoCreate(DocCoord&, Spread*, AttrFillGeometry*);
	void DoDrag(DocCoord&, Spread*, AttrFillGeometry*, FillControl ControlHit);
	
	// Virtual functions needed for the dragging operations to work
	virtual void DragPointerMove(DocCoord PointerPos, ClickModifiers ClickMods, Spread*, BOOL bSolidDrag);
	virtual void DragPointerIdle(DocCoord PointerPos, ClickModifiers ClickMods, Spread*, BOOL bSolidDrag);
	virtual void DragFinished(DocCoord PointerPos, ClickModifiers ClickMods, Spread*, BOOL Success, BOOL bSolidDrag);
	virtual BOOL DragKeyPress(KeyPress* pKeyPress, BOOL bSolidDrag);
	virtual void DragModeChanged(BOOL bSolidDrag);

	// Some Render functions to will draw the EORed path
	void RenderDragBlobs(DocRect, Spread*, BOOL bSolidDrag);

	// interogates the current (drag) Operation for StatusLine text
	BOOL GetStatusLineText(String_256* pText, Spread* pSpread, DocCoord DocPos, ClickModifiers ClickMods);

	// These functions required for the OpDescriptor class
	static BOOL Init();
	static OpState GetState(String_256* Description, OpDescriptor*);

	AttrFillGeometry * GetGradFill() { return GradFill; }

protected:
	DocRect GetDragBlobRect();

	void RedrawFills(ClickModifiers& ClickMods);
	void CheckForCompoundRedraw();

	BOOL ApplyNewFill();
	BOOL ApplyEditedFill();

	void SelectAllBlobs();

	void RenderFinalBlobs(DocRect, Spread*, BOOL bSolidDrag);
	void RenderSelectionFillBlobs(SelRange*, DocRect, Spread*);
	void RenderInitSelectionBlobs(SelRange*, DocRect, Spread*);
	void RenderInitBlobs(DocRect, Spread*, BOOL bSolidDrag);

	double FindAspectRatio();

// Vars
protected:
	// Infomation about what we are editing
	AttrFillGeometry*	GradFill;
	AttrFillGeometry*	FillClone;
	Spread*   			StartSpread;
	FillControl			DragControl;		// Which Blob are we dragging ?

	BaseDocument*	pFillsDoc;
	DocRect 		LastDragRect;
	BOOL 			InvalidateAll;
	BOOL 			InvalidateCompound;
	Node* 			pCompound;

	BOOL			DragIsIdle;
	BOOL			DoneIdleRedraw;
	MonotonicTime	Time;

	BOOL 			ShowDragBlobs;
	BOOL 			DontDrawBlobs;

	BOOL 			AlwaysFail;
	BOOL 			ApplyAtEnd;
	BOOL 			ShouldApplyNewFill;
	BOOL 			ForceAspectLock;
	BOOL 			IsRequired;
	BOOL 			CheckForCompound;
	BOOL 			CallAllowOp;

	FlagState 		TranspState;

	List 			AttrGroups;
	
	double			AspectRatio;

	// Mouse Positions
	DocCoord  		AnchorPos;
	DocCoord  		LastMousePosition;

public:
	static BOOL InteractiveDragUpdate;
	static BOOL ContinuousEOR;
	static BOOL CreateFill;

	static UINT32 IdleFillDelay;
};

/********************************************************************************************

>	class ModifyFillCoordsAction : public Action

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/94
	Purpose:	An action which undoes the modification of Grad Fill data. This action can
				be used for undoing changing control points.
	SeeAlso:	-

********************************************************************************************/
/*
class ModifyFillCoordsAction : public Action
{

CC_DECLARE_DYNCREATE(ModifyFillCoordsAction)

public:
	ModifyFillCoordsAction();
	~ModifyFillCoordsAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							INT32 NumChanged,
							Action** NewAction);
	void StoreChanges(AttrFillGeometry* Fill, DocCoord* Coords, BOOL* SelState);

protected:
	INT32 NumChangedCoords;

	AttrFillGeometry* 	ChangedFill;
	DocCoord* 			ChangedCoords;
	BOOL*				SelectionState;
};
*/

/********************************************************************************************

>	class OpChangeFillColour : public SelOperation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/7/94
	Purpose:	This operation Changes the Colour of a Fill already in the tree. 

********************************************************************************************/
/*
class OpChangeFillColour : public SelOperation
{
CC_DECLARE_DYNCREATE(OpChangeFillColour);

public:
	// Construction/Destruction
	OpChangeFillColour();

	// The all important Do function
	void Do(DocColour &, DocColour &, AttrFillGeometry *);
	
	// These functions required for the OpDescriptor class
	static BOOL Init();
	static OpState GetState(String_256* Description, OpDescriptor*);
};
*/

/********************************************************************************************

>	class OpChangeSelectionColours : public SelOperation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/7/94
	Purpose:	This operation Changes the Colour of a Fill already in the tree. 

********************************************************************************************/
/*
class OpChangeSelectionColours : public SelOperation
{
CC_DECLARE_DYNCREATE(OpChangeSelectionColours);

public:
	// Construction/Destruction
	OpChangeSelectionColours();

	// The all important Do function
	BOOL Do(DocColour &);
	
	// These functions required for the OpDescriptor class
	static BOOL Init();
	static OpState GetState(String_256* Description, OpDescriptor*);
};
*/

/********************************************************************************************

>	class ModifyFillColoursAction : public Action

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/94
	Purpose:	An action which undoes the modification of Grad Fill data. This action can
				be used for undoing changing colours.
	SeeAlso:	-

********************************************************************************************/
/*
class ModifyFillColoursAction : public Action
{

CC_DECLARE_DYNCREATE(ModifyFillColoursAction)

public:
	ModifyFillColoursAction();
	~ModifyFillColoursAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							INT32 NumChangedColours,
							Action** NewAction);
	void StoreChanges(AttrFillGeometry* Fill, DocColour* Colours, BOOL* SelState);

protected:
	INT32 NumChangedColours;

	AttrFillGeometry* 	ChangedFill;
	DocColour* 			ChangedColours;
	BOOL*				SelectionState;
};
*/

/********************************************************************************************

>	class RestoreFillRampAction : public Action

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/10/99
	Purpose:	Action for restoring fill ramps after changes have been made
	SeeAlso:	-

********************************************************************************************/

class RestoreFillRampAction : public Action
{

CC_DECLARE_DYNCREATE(RestoreFillRampAction)

public:
	RestoreFillRampAction();
	~RestoreFillRampAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							AttrFillGeometry* pFill,
							RestoreFillRampAction** NewAction);
							
protected:
	AttrFillGeometry* m_pAttr;
	ColourRamp m_LastRamp;
};


#endif // INC_OPGRAD



