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

// Operations supplied by the Line tool

#ifndef INC_OPBEZIER
#define INC_OPBEZIER

//#include "doccoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "undoop.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class BezierTool;
class Cursor;

#define OPTOKEN_INSERTFLOATER	_T("OpInsertFloater")
#define OPTOKEN_REMOVEFLOATER	_T("OpRemoveFloater")

/********************************************************************************************

>	class OpSelectPathPoints : public UndoableOperation

	Author:		Jim_Lynn (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/6/94
	Purpose:	This is the operation that marquee selects points in paths

********************************************************************************************/

class OpSelectPathPoints : public UndoableOperation
{

CC_DECLARE_DYNCREATE(OpSelectPathPoints);

public:
	// Construction/Destruction
	OpSelectPathPoints();

	// The all important Do functions
	void DoDrag( DocCoord Anchor, Spread*, BOOL isAdjust, BezierTool* toolptr, ClickModifiers );
	
	// Virtual functions needed for the dragging operations to work
	virtual void DragPointerMove( DocCoord PointerPos, ClickModifiers ClickMods, Spread*, BOOL bSolidDrag);
	virtual void DragFinished(	DocCoord PointerPos, 
								ClickModifiers ClickMods, 
								Spread*, 
								BOOL Success, BOOL bSolidDrag);

	// Some Render functions to will draw the EORed path
	void RenderDragBlobs( DocRect, Spread*, BOOL bSolidDrag);
		
	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);
	static BOOL Init();

	static BOOL DragInProgress();

private:
	DocCoord	StartPoint;			// The start of the rectangle
	Spread *	StartSpread;
	DocCoord	PreviousPoint;		// So that we don't update too often.
	BOOL		AdjustDrag;			// Is the drag adjust or not?
	BezierTool*	BezToolPtr;			// Points back to the bezier tool
	ClickModifiers Mods;			// which modifiers were in evidence from the original click
	static BOOL	DragUnderway;		// This op is not re-entrant.

	Cursor* pcMarqueeCursor;				// Normal freehand cursor
	void	ChangeCursor(Cursor* cursor);	// function to change cursor
	void	PushCursor(Cursor* cursor);		// Push this cursor onto the cursor stack
	void	PopCursor();					// Pop our cursor off the stack
	void	RemoveDragBlobs(BOOL, BOOL);	// Restores the selection blobs to pre-drag state
	void	RenderRubberRect(DocRect* Rect);
	void	RenderRubberSelection(RenderRegion* pRegion);
};



/********************************************************************************************

>	class OpRemoveFloater : public UndoableOperation

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/12/94
	Purpose:	This is the operation that the line tool uses to remove the floating endpoint
				in an undoable kind of way.

********************************************************************************************/

class OpRemoveFloater : public UndoableOperation
{

CC_DECLARE_DYNCREATE(OpRemoveFloater);

public:
	OpRemoveFloater();
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);
	void DoWithParam(OpDescriptor*, OpParam* pOpParam);
};



/********************************************************************************************

>	class OpInsertFloater : public UndoableOperation

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/12/94
	Purpose:	This is the operation that the line tool uses to insert the floating endpoint
				in an undoable kind of way.

********************************************************************************************/

class OpInsertFloater : public UndoableOperation
{

CC_DECLARE_DYNCREATE(OpInsertFloater);

public:
	OpInsertFloater();
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);
	void DoWithParam(OpDescriptor*, OpParam* pOpParam);
};



/********************************************************************************************

>	class InsertFloaterParam : public OpParam

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/12/94
	Purpose:	This is the OpParam object passed to OpInsertFloater to position the floating
				endpoint

********************************************************************************************/
class InsertFloaterParam : public OpParam
{
CC_DECLARE_MEMDUMP(InsertFloaterParam);

public:
	InsertFloaterParam(DocCoord* pInsertPos, Spread* pInsertSpread, BezierTool* pLineTool, Document* pWorkDoc);

	DocCoord	InsertPos;
	Spread*		InsertSpread;
	BezierTool*	pTool;
	Document*	pOpWorkingDocument;
};



/********************************************************************************************

>	class InsertFloaterAction : public Action

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	05/12/94
	Purpose:	An action to provide the Line tool with an undoable way of inserting the 
				floating endpoint.  This isn't stored in the document, which makes life
				tricky.
	SeeAlso:	

********************************************************************************************/

class InsertFloaterAction : public Action
{

CC_DECLARE_DYNCREATE(InsertFloaterAction)

public:
	InsertFloaterAction();
	~InsertFloaterAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							Action** NewAction);
	static ActionCode DoInsert( Operation* pOp,
								ActionList* pActionList,
								BezierTool* pTool,
								DocCoord*	pPoint,
								Spread*		pSpread);
	// Data members
	BezierTool*	pLineTool;
	DocCoord	Point;
	Spread*		pSpread;
};


/********************************************************************************************

>	class RemoveFloaterAction : public Action

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	05/12/94
	Purpose:	An action to provide the Line tool with an undoable way of removing the 
				floating endpoint.  This isn't stored in the document, which makes life
				tricky.
	SeeAlso:	

********************************************************************************************/

class RemoveFloaterAction : public Action
{

CC_DECLARE_DYNCREATE(RemoveFloaterAction)

public:
	RemoveFloaterAction();
	~RemoveFloaterAction();
	virtual ActionCode Execute();
	static ActionCode Init( Operation* pOp,
							ActionList* pActionList,
							BezierTool* pTool,
							Action** NewAction);
	static ActionCode DoRemove( Operation* pOp,
								ActionList* pActionList,
								BezierTool* pTool);
protected:
	BezierTool*	pLineTool;
};


#endif 		// INC_OPBEZIER




