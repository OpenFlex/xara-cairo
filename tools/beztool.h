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

// The Bezier Tool
// Created by Jim on 31/3/94
// Based on the freehand tool



#ifndef INC_BEZTOOL
#define INC_BEZTOOL


//#include "tool.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "selop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "doccoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "wrkrect.h"
//#include "binds.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "rectangl.h"
#include "rsmooth.h"

class NodePath;
class Cursor;
class BezierTool;
class Document;
class NodeBlend;
//class BezToolInfoBarOp;

#define OPTOKEN_BEZTOOL _T("BezierTool")

/*
< clickeffect
< NewPath
< OnPoint
< AddSegment
< ReshapeLine

Comment: 	clickeffect is an enum used by the click and the mouse move code in the 
			bezier tool. The routine called in these events will say what a click should 
			do - either start a new path, click on an existing point, add a segment to a line, 
			reshape a segment of a line or close the path.

Possible values are:	NewPath
						OnPoint
						AddSegment
						ReshapeLine
						ClosePath
*/
	enum clickeffect
	{
		NewPath,
		OnPoint,
		AddSegment,
		ReshapeLine,
		ClosePath
	};

/********************************************************************************************

>	class BezToolInfoBarOp : public InformationBarOp

	Author:		Jim_Lynn (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/94
	Purpose:	Class for handling the bezier tool's information bar.

********************************************************************************************/

class BezToolInfoBarOp : public InformationBarOp
{
	friend class BezierTool;
	CC_DECLARE_DYNCREATE( BezToolInfoBarOp )  
public:
	BezToolInfoBarOp(ResourceID r = _R(IDD_BEZTOOLBAR)) {DlgResID = r;}				// Dummy default constructor for DYNCREATE

	BOOL CheckClassData ();				// arrows controls are enabled even when there disabled!
										// fix for this ....
	
	MsgResult 	Message(Msg* Msg);	// All messages to the info bar come through here

	void		InitControls();		// Initialises the controls in the info bar
	void		EnableControls();	// Enables/disables the controls in the info bar

	virtual void UpdateState();	// Overrides the empty function in InformationBarOp
 
	// DY this will be relocated elsewhere at some point
	NodeBlend* GetBlendOnCurve() ;

protected:
	void UpdateCurveButton();
	void UpdateLineButton();
	void UpdateReversePathsButton ();
	void UpdateSmoothButton();
	void UpdateCuspButton();
	void UpdateTextIndicator();
	void UpdateStartArrowButton();
	void UpdateEndArrowButton();
	void UpdatePositionFields(BOOL ForceUpdate = FALSE, BOOL ScanForCurrent = TRUE);
	void UpdateEditFieldsFromPath(Path*	pPath, Spread* pSpread, INT32 Index, BOOL ForceUpdate, BOOL EnableData[18]);
	void HandleClickOnCurveButton();
	void HandleClickOnLineButton();
	void HandleClickOnReversePathButton();
	void HandleClickOnSmoothButton();
	void HandleClickOnCuspButton(BOOL WithConstrain);
	void HandleClickOnStartArrowButton();
	void HandleClickOnEndArrowButton();
	BOOL HandleBumpClick(CGadgetID GadgetID);
	BOOL HandleEditFieldCommit(CGadgetID CommitField);
	void ScanPointsForToggleSmooth(BOOL MakeSmooth, BOOL WithConstrain);
	BOOL ScanPointsForJoins(BOOL* AllSmooth, BOOL* AllCusp);
	BOOL SetEditLength(CGadgetID gid, INT32 nValue, Spread* pSpread, BOOL PaintNow = FALSE);
	BOOL SetEditPosition(CGadgetID gid, INT32 nValue, Spread* pSpread, BOOL PaintNow = FALSE);
	BOOL SetEditPosition(CGadgetID gidX, CGadgetID gidY, DocCoord loc, Spread* pSpread, BOOL PaintNow = FALSE);
	INT32 GetCurrentIndex();
	double GetAngle(DocCoord Origin, DocCoord Offset);

	BOOL HandleLAFieldCommit(CGadgetID, CGadgetID, CGadgetID, DocCoord, DocCoord, DocCoord*);
	BOOL HandleCoordFieldCommit(UINT32 UpperID, UINT32 LowerID, INT32 Index, DocCoord* NewPos, BOOL* Valid);

	INT32 GetPrevLineIndex(Path* pPath, INT32 Index);
	INT32 GetNextLineIndex(Path* pPath, INT32 Index);

	MsgResult InfobarMessage(Msg* Message) ;

public:
	BezierTool* pBezTool;		// Pointer to instance of bezier tool

private:
	INT32		CurrentIndex;
	NodePath*	CurrentNodePath;
	Path*		CurrentInkPath;
	Spread*		CurrentSpread;
	BOOL		IgnoreNextUpdate;
	INT32		LastShownPrevLength;
	INT32		LastShownNextLength;

};
	

/********************************************************************************************
>	class BezierTool : public Tool_v1

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/7/93
	Purpose:	This class handles the Free Hand Tool that is used to draw lines that follow
				the path of the Mouse Pointer.
********************************************************************************************/

class CCAPI BezierTool : public Tool_v1
{
	friend class BezToolInfoBarOp;

// Give my name in memory dumps
CC_DECLARE_MEMDUMP(BezierTool);

public:
	enum CurrentMode {New, Add, Change};

	BezierTool();
	~BezierTool();
	BOOL Init();
	void Describe(void* InfoPtr);
	UINT32 GetID() { return TOOLID_BEZTOOL; };
	
	// Event Handlers
	void SelectChange(BOOL);
	void OnClick( DocCoord, ClickType, ClickModifiers, Spread* );

	virtual void RenderToolBlobs(Spread*, DocRect*);

	void HandleInfoBarMessage(CDlgMessage DlgMsg, CGadgetID Gadget);

	void OnMouseMove(DocCoord, Spread*, ClickModifiers);
	BOOL OnKeyPress(KeyPress*);
	
	void SetMoveTo(DocCoord MovePos, Spread* pSpread, Document* pDoc);
	void ClearMoveTo();
	BOOL GetMoveTo(Spread** ppSpread, DocCoord* pCoord, Document** ppDoc);

	void SetModeFlag();

	BOOL GetStatusLineText(String_256* ptext, Spread* pSpread, DocCoord DocPos, ClickModifiers ClickMods);
	void GenerateStatusLineText(String_256* ptext, Spread* pSpread, DocCoord DocPos, ClickModifiers ClickMods);

protected:
	// Moving selected points on paths functions
	BOOL CyclePathPoints(BOOL Fowards);
	BOOL HomePathPoints();
	BOOL EndPathPoints();

	BOOL AutoClosePaths();

	void RemoveFloater(DocCoord* FloatPos, Spread* FloatSpread, Document* pDoc);

protected:
	// retro smoothing functions.
	void RetroSmoothChanging(double Smooth);
	void RetroSmoothFinished();
	void RetroSmoothSet(INT32 percent, BOOL Enabled);
	void RetroSmoothInvalidate();
	void UpdateRetroSlider(Path* pPath);
	void ResetRetroSlider();
	Node* OneNodePathSelected();

protected:
	static 	TCHAR* FamilyName;	// The Tools Family Name
	static 	TCHAR* ToolName;		// The Tool Name
	static 	TCHAR* Purpose;		// What the tool is for
	static 	TCHAR* Author;		// Who wrote it

	// The coord of the initial click
	DocCoord StartPos;
	Spread  *StartSpread;

	// The tools cursor
	Cursor* pcMoveBezCursor;				// Move a bezier point
	Cursor* pcReshapeLineCursor;			// Reshape a line segment
	Cursor* pcNewPathCursor;				// Add a new path
	Cursor* pcAddPathCursor;				// Add to an existing path
	Cursor* pcClosePathCursor;				// Close a path
	Cursor*	MyCurrentCursor;				// so I don't flip cursor too often
	void	ChangeCursor(Cursor* cursor);	// function to change cursor
	INT32	CurrentCursorID;

	// When the tool gets a single click in space and there's no endpoint selected,
	// it has to start a new path, but instead of doing what ArtWorks did and inserting
	// a real node in the tree, this tool will do it by using tool blobs.

	BOOL	FloatingEndpoint;	// TRUE if there's a single MoveTo point floating about
	Document* MoveToDoc;		// Document the floating endpoint is in.
	DocCoord MoveToPoint;		// Coords of floating endpoint if present
	Spread*  MoveToSpread;		// Which spread the MoveTo is on

	// A routine which tells me what the effect of clicking will be at any point
	clickeffect DetermineClickEffect(DocCoord PointerPos, Spread* pSpread,
									NodeRenderableInk** ReturnNode, INT32* ReturnPosition,
									INT32* NumSelectedPaths, INT32* NumSelectedPoints );

	// A routine which returns the pointer to the node path we're to edit
	NodePath* FindEditablePath(Node* pSelected);

	static BezToolInfoBarOp*	pBezToolInfoBarOp;

	
	static BOOL CreateCurve;	// Flag that tells the tool to create either a line or a curve
	static BOOL CreateCusp;		// Flag that tells the tool to create either smooth or cusps

	RetroSmooth* pSmooth;		// pointer to the smoothing technology.
	BOOL RetroFlag;				// true if we've found a retro smooth path
	Node* pRetroNode;			// holds a pointer to the node we're interrested in.
	Spread* pRetroSpread;		// holds a pointer to the retro nodes spread.

	BOOL DontDrawOnClearMoveTo;
	
	CurrentMode CurrentToolMode;
}; 



/********************************************************************************************

>	class BezToolInfoBarOpCreate : public BarCreate

	Author:		Jim_Lynn (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/94
	Purpose:	Class for creating BezToolInfoBarOps.
				Derived classes of BarCreate are used by DialogBarOp::ReadBarsFromFile()

********************************************************************************************/

class BezToolInfoBarOpCreate : public BarCreate
{
public:
	DialogBarOp* Create() { return (new BezToolInfoBarOp); }
};


#endif		//INC_BEZTOOL
