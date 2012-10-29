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

// Header for the grid tool implementation
// Created by Mark Neves on 18/2/94

#ifndef INC_GRIDTOOL
#define INC_GRIDTOOL

#include "grid.h"

class Cursor;
class Spread;
class ChangeGrid;
class GridInfoBarOp;
class OpState;


/********************************************************************************************

>	class GridTool : public Tool_v1

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/2/94
	Purpose:	A Tool for creating and editing grids

********************************************************************************************/

class CCAPI GridTool : public Tool_v1
{
// Give my name in memory dumps
CC_DECLARE_MEMDUMP(GridTool);

public:
	GridTool();
	~GridTool();
	BOOL Init();
	void Describe(void* InfoPtr);
	UINT32 GetID();
	
	// Event Handlers
	void SelectChange(BOOL isSelected);
	void OnClick( DocCoord, ClickType, ClickModifiers, Spread* );
	void OnMouseMove(DocCoord PointerPos, Spread* pSpread, ClickModifiers mods);
	void RenderToolBlobs(Spread* pSpread,DocRect* pDocRect);

	static GridType		DefaultGridType;

	static void RenderAllGridBlobs(NodeGrid* pGrid);
	static void ChangeSelectedGrids();
	static void ForceRedraw(Spread* pSpread,DocRect Rect);
	static void ForceRedraw(NodeGrid* pGrid);
	static void MakeDefaultGrid(Spread* pSpread);
	static void ToggleDefaultGrid();
	static void DisplayStatusBarHelp(UINT32 StatusID);
	static void DisplayGridInfo(NodeGrid* pGrid);

	static Spread* 			GetSpreadClicked() {return SpreadClicked; }
	static GridInfoBarOp* 	GetGridInfoBarOp() {return pGridInfoBarOp; }

	//static BOOL IsCurrentTool() { return CurrentTool; }

	static Document*	GetDoc() { return GridTool::pDocument; }
	static void			SetDoc(Document* pThisDoc);

private:
	static void ChangeGrid(NodeGrid* pGrid);

	BOOL CreateCursors();
	void RenderAllGridBlobs();

	static void RenderGridBlobsInSpread(DocView* pDocView,Spread* pSpread,DocRect* pDocRect);
	static void RenderGridBlobs(RenderRegion* pRender,NodeGrid* pGrid);
	static void RenderGridSelectBlobs(RenderRegion* pRender,NodeGrid* pGrid);
	static void RenderGridBlobs(NodeGrid* pGrid);
	static void RenderGridSelectBlobs(NodeGrid* pGrid);
	static void ClearSelection(Spread* pSpread);
	static BOOL GetGridBlobRenderVars(NodeGrid* pGrid,DocView** ppDocView,Spread** ppSpread,DocRect* pDocRect);
	static void FindCurrentSpread();
	static BOOL HasSpreadSelGrids(Spread* pSpread);

	BOOL WhichGridClicked(Spread* pSpread,const DocCoord& PointerPos,NodeGrid** ppGrid);
	BOOL WhichGridBlobClicked(Spread* pSpread,const DocCoord& PointerPos,NodeGrid** ppGrid,GridBlobType* pGridBlob);


	static Spread*  		SpreadClicked;			// The Spread the click started on
	static DocCoord 		PointClicked;			// The point where the drag started
	static NodeGrid* 		GridClicked;
	static GridBlobType 	GridBlobClicked;
	static NodeGrid*		LastGridClicked;
	//static BOOL 			CurrentTool;
	static UINT32				LastStatusID;
	static GridInfoBarOp*	pGridInfoBarOp;
	static Document* 		pDocument;

	Cursor* 		pcNormalGridCursor;
	Cursor* 		pcOverGridCursor;
	Cursor* 		pcOverBlobCursorUD;
	Cursor* 		pcOverBlobCursorLR;
	Cursor* 		pcOverBlobCursorTL;
	Cursor* 		pcOverBlobCursorTR;
	Cursor*			pcCurrentCursor;
	INT32 			CurrentCursorID;						// ID of the current cursor on the stack

	static 	char* FamilyName;	// The Tools Family Name
	static 	char* ToolName;		// The Tool Name
	static 	char* Purpose;		// What the tool is for
	static 	char* Author;		// Who wrote it
};


/********************************************************************************************

>	class OpGrid : public UndoableOperation

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/7/94
	Purpose:	Base class all grid operations are derived from

********************************************************************************************/

class OpGrid : public UndoableOperation
{

CC_DECLARE_DYNCREATE(OpGrid);

public:
	OpGrid() { PreOpDisplayedGrid = PostOpDisplayedGrid = NULL; }

	NodeGrid*	GetPreOpDisplayedGrid()		{ return PreOpDisplayedGrid; }
	NodeGrid*	GetPostOpDisplayedGrid()	{ return PostOpDisplayedGrid; }

	NodeGrid* DoDuplicateGrid(	NodeGrid* pGrid,
										AttachNodeDirection AttDir,
										Node* pContextNode,
										Spread* pSrcSpread,
										Spread* pDestSpread,
										BOOL	FRedraw,
										INT32	XDelta = 0,
										INT32	YDelta = 0);

protected:
	NodeGrid*	PreOpDisplayedGrid;
	NodeGrid*	PostOpDisplayedGrid;
};



#define OPTOKEN_GRIDNEWRESIZE _T("GridNewResize")


/********************************************************************************************

>	class OpGridNewResize : public OpGrid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/2/94
	Purpose:	Provides the operations behind the Grid Tool. These include blob dragging,
				creation of grid and addition of grids to the document tree.

********************************************************************************************/

enum OpGridOpType { NEW, RESIZE };

class OpGridNewResize : public OpGrid
{

CC_DECLARE_DYNCREATE(OpGridNewResize);

public:
	// Construction/Destruction
	OpGridNewResize();                     
	~OpGridNewResize();

	// The all important Do functions
	void DoDrag(Spread* pSpread,NodeGrid* pGrid,GridBlobType Blob,
				DocCoord PointClicked);
	
	// Virtual functions needed for the dragging operations to work
	virtual void DragPointerMove( DocCoord PointerPos, ClickModifiers ClickMods, Spread*, BOOL bSolidDrag);
	virtual void DragFinished(	DocCoord PointerPos, 
								ClickModifiers ClickMods, Spread*, 
								BOOL Success, BOOL bSolidDrag);

	// Some Render functions to will draw the EORed drag box
	void RenderMyDragBlobs();
	void RenderDragBlobs(DocRect Rect,Spread* pSpread, BOOL bSolidDrag);
		
	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);
	void GetOpName(String_256* OpName);

	static BOOL 	StartADrag;
	static BOOL 	EndTheDrag;

private:
	// Member vars of the operation 
	Spread*  		SpreadClicked;			// The Spread the click started on
	NodeGrid* 		GridClicked;		 	// The grid the click occurred on (or NULL if no grid clicked)
	GridBlobType	GridBlobClicked;		// The grid select blob clicked (or NoGridBlob if none clicked)
	DocCoord 		AnchorPoint;			// The point where the drag started
	DocCoord 		DragPoint;				// The last position the mouse was in

	OpGridOpType	OpType;
};


/********************************************************************************************

>	class OpGridSelection : public OpGrid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/2/94
	Purpose:	Provides the operations on the selected grids. These include dragging,
				cut copy paste etc.

********************************************************************************************/

#define OPTOKEN_GRIDSELECTION _T("GridSelection")

class OpGridSelection : public OpGrid
{

CC_DECLARE_DYNCREATE(OpGridSelection);

public:
	// Construction/Destruction
	OpGridSelection();
	~OpGridSelection();

	// The all important Do functions
	void DoDrag(Spread* pSpread,DocCoord PointClicked,NodeGrid* GridClicked);
	
	// Virtual functions needed for the dragging operations to work
	virtual void DragPointerMove( DocCoord PointerPos, ClickModifiers ClickMods, Spread*, BOOL bSolidDrag);
	virtual void DragFinished(	DocCoord PointerPos, 
								ClickModifiers ClickMods, Spread*, 
								BOOL Success, BOOL bSolidDrag);

	// Returns the union of all the selected grids in the given spread
	DocRect OpGridSelection::GetSelectedGridBounds(Spread* pSpread);

	// Some Render functions to will draw the EORed drag boxes
	void RenderMyDragBlobs();
	void RenderDragBlobs(DocRect Rect,Spread* pSpread, BOOL bSolidDrag);
		
	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);
	void GetOpName(String_256* OpName);

private:
	// Member vars of the operation 
	Spread*  		SpreadClicked;			// The Spread the click started on
	DocCoord 		StartPoint;				// The point where the drag started
	DocCoord 		DragPoint;				// The last position the mouse was in
	Spread*			SpreadDrag;				// Spread current DragPoint is over
	DocRect			StartRect;				// The union of selected grid bounds before the drag
	DocRect			DragRect;				// The union of selected grid bounds after  the drag

	BOOL Plural;
};

/********************************************************************************************

>	class OpGridChange : public OpGrid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/2/94
	Purpose:	Provides the operation for changing the selected grids.

********************************************************************************************/

#define OPTOKEN_GRIDCHANGE _T("GridChange")

class OpGridChange : public OpGrid
{

CC_DECLARE_DYNCREATE(OpGridChange);

public:
	// Construction/Destruction
	OpGridChange();
	~OpGridChange();

	// These functions required for the OpDescriptor class
	static 	BOOL Declare();
	static 	OpState GetState(String_256* Description, OpDescriptor*);
	void 	GetOpName(String_256* OpName);

	void 	DoChangeSelectedGrids(ChangeGrid* pChangeGrid);
	BOOL 	DoChangeGrid(NodeGrid* pOldGrid,ChangeGrid* pChangeGrid);

private:
	UINT32 		ChangeGridUndoIDS;
};

/********************************************************************************************

>	class OpGridDelete : public OpGrid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/7/93
	Purpose:	This class represents the grid Delete operation.

********************************************************************************************/

class OpGridDelete: public OpGrid
{         
CC_DECLARE_DYNCREATE(OpGridDelete)    

public:
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	
	void 			GetOpName(String_256* OpName);

private:
	BOOL Plural;
};  
 
/********************************************************************************************

>	class OpGridCut : public OpGrid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Purpose:	This class represents the grid Cut operation.
				Currently, it just greys out the menu/button/keypress associated with the op

********************************************************************************************/

class OpGridCut: public OpGrid
{         
CC_DECLARE_DYNCREATE(OpGridCut)    
};  
 
/********************************************************************************************

>	class OpGridCopy : public OpGrid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Purpose:	This class represents the grid Copy operation.
				Currently, it just greys out the menu/button/keypress associated with the op

********************************************************************************************/

class OpGridCopy: public OpGrid
{         
CC_DECLARE_DYNCREATE(OpGridCopy)
};  
 
/********************************************************************************************

>	class OpGridPaste : public OpGrid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Purpose:	This class represents the grid Paste operation.
				Currently, it just greys out the menu/button/keypress associated with the op

********************************************************************************************/

class OpGridPaste: public OpGrid
{         
CC_DECLARE_DYNCREATE(OpGridPaste)    
};  
 
/********************************************************************************************

>	class OpGridDuplicate : public OpGrid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Purpose:	This class represents the grid Duplicate operation.
				Currently, it just greys out the menu/button/keypress associated with the op

********************************************************************************************/

class OpGridDuplicate: public OpGrid
{         
CC_DECLARE_DYNCREATE(OpGridDuplicate)    

public:
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	
	void 			GetOpName(String_256* OpName);

private:
	BOOL Plural;
};  
 
//--------------------------------------------------------
//--------------------------------------------------------
//--------------------------------------------------------
//--------------------------------------------------------

/********************************************************************************************

>	class ChangeGrid :

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/3/94
	Purpose:	An abstract class used for changing aspects of a grid

********************************************************************************************/

class ChangeGrid : public SimpleCCObject
{
public:
	virtual void Change(NodeGrid* pGrid) = 0;
	virtual GridType GetGridType(NodeGrid* pGrid) = 0;
	virtual UINT32 GetUndoIDS() = 0;
};

/********************************************************************************************

>	class ChangeGridUnits : public Grid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/3/94
	Purpose:	An abstract class used for changing aspects of a grid

********************************************************************************************/

class ChangeGridUnits : public ChangeGrid
{
public:
	void Change(NodeGrid* pGrid);
	GridType GetGridType(NodeGrid* pGrid);
	UINT32 GetUndoIDS();
};

/********************************************************************************************

>	class ChangeGridDivisions : public Grid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/3/94
	Purpose:	An abstract class used for changing aspects of a grid

********************************************************************************************/

class ChangeGridDivisions : public ChangeGrid
{
public:
	void Change(NodeGrid* pGrid);
	GridType GetGridType(NodeGrid* pGrid);
	UINT32 GetUndoIDS();
};

/********************************************************************************************

>	class ChangeGridSubdivisions : public Grid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/3/94
	Purpose:	An abstract class used for changing aspects of a grid

********************************************************************************************/

class ChangeGridSubdivisions : public ChangeGrid
{
public:
	void Change(NodeGrid* pGrid);
	GridType GetGridType(NodeGrid* pGrid);
	UINT32 GetUndoIDS();
};

/********************************************************************************************

>	class ChangeGridType : public Grid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/3/94
	Purpose:	An abstract class used for changing aspects of a grid

********************************************************************************************/

class ChangeGridType : public ChangeGrid
{
public:
	void Change(NodeGrid* pGrid);
	GridType GetGridType(NodeGrid* pGrid);
	UINT32 GetUndoIDS();
};

//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------
//-----------------------------------------------


/********************************************************************************************

>	class GridInfoBarOp : public InformationBarOp

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/94
	Purpose:	Class for handling the grid tool's information bar.

********************************************************************************************/

class GridInfoBarOp : public InformationBarOp
{
	CC_DECLARE_DYNCREATE( GridInfoBarOp )  
public:
	GridInfoBarOp() {};				// Dummy default constructor for DYNCREATE

	MsgResult 	Message(Msg* Msg);	// All messages to the info bar come through here

	void		InitControls();		// Initialises the controls in the info bar
	void		EnableControls();	// Enables/disables the controls in the info bar

	// A set of routines for displaying information in the info bar
	void 		DisplayDefaultGridInfo();
	void 		DisplayGridInfo(double Divisions, UnitType Units, UINT32 Subdivisions, GridType GType);
	void 		DisplayGridInfo(NodeGrid* pGrid);

	NodeGrid*	GetLastGridDisplayed()	{ return LastGridDisplayed; }

private:
	NodeGrid*	LastGridDisplayed;
};
	

/********************************************************************************************

>	class GridInfoBarOpCreate : public BarCreate

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/94
	Purpose:	Class for creating GridInfoBarOps.
				Derived classes of BarCreate are used by DialogBarOp::ReadBarsFromFile()

********************************************************************************************/

class GridInfoBarOpCreate : public BarCreate
{
public:
	DialogBarOp*	Create() { return (new GridInfoBarOp); }
};


#endif 		// INC_GRIDTOOL

