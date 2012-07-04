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

// The FreeHand Tool
// Created by Rik on 2/9/93



#ifndef INC_FREEHAND
#define INC_FREEHAND


//#include "tool.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "selop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "doccoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "wrkrect.h"
//#include "binds.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "grndbrsh.h"
#include "brshcomp.h"
#include "brshdata.h"
#include "dragtool.h"

class NodePath;
class Cursor;
class FreeHandInfoBarOp;
class NodeBrushPath;
class Progress;
class Trans2DMatrix;
class BlendRef;
class GRenderBrush;

/********************************************************************************************

<	struct FreeHandJoinInfo

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/10/94
	Purpose:	Holds assorted data used to help join new path with existing paths

********************************************************************************************/

struct FreeHandJoinInfo
{
	NodePath* pJoinPath;			// The Path that we will try to join with
	BOOL 	  IsNearEndPoint;		// TRUE if we are to join at an open endpoint
	INT32	  CloseSlot;			// The element number we were closest to
	double    Into;					// The normalised distance along the element that we were closest to
	BrushHandle m_BrushHandle;        // if we are going to join to a brush, this identifies which one
	BrushData m_BrushData;			// likewise this holds data from the brush we ar about to join to 
	MILLIPOINT FirstBrushSpacing;  // the first spacing for the brush
	AttrBrushType* pAttrBrush;
	MILLIPOINT BrushDistance;	
	DocColour StrokeColour;
	BOOL UseLocalColour;
	BOOL UseNamedColour;
};


// flag which indicates when the offscreen buffer for the brush should be next updated.
typedef enum  UPDATE_STATE {
							UPDATE_NOW,
							UPDATE_ONIDLE,
							UPDATE_NEVER
							};


/********************************************************************************************
>	class FreeHandTool : public Tool_v1

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/7/93
	Purpose:	This class handles the Free Hand Tool that is used to draw lines that follow
				the path of the Mouse Pointer.
********************************************************************************************/

class CCAPI FreeHandTool : public DragTool
{
// Give my name in memory dumps
CC_DECLARE_MEMDUMP(FreeHandTool);

public:
	FreeHandTool();
	~FreeHandTool();
	BOOL Init();
	void Describe(void* InfoPtr);
	UINT32 GetID();
	
	// Event Handlers
	virtual void SelectChange(BOOL);
	virtual void OnClick( DocCoord, ClickType, ClickModifiers, Spread* );
	virtual void OnMouseMove(DocCoord, Spread*, ClickModifiers);
	virtual BOOL GetStatusLineText(String_256* ptext, Spread*, DocCoord, ClickModifiers);

	virtual BOOL OnIdle();

	// Rendering the blobs functions
	virtual void RenderToolBlobs(Spread*, DocRect*);

	// Communication with the InfoBar
	void SetSmoothness(INT32 Smooth);
	INT32  GetSmoothness();
	void PreviousPathInvalid();
	void SetPreviousPath(NodePath*, INT32 Start, INT32 Len);

	FreeHandInfoBarOp* GetInfoBar() { return pInfoBarOp;}

	// functions to deal with the retro path validation
	BOOL IsRetroPathStillValid();
	INT32  BuildPathCRC(NodePath*);
	void TranslateTrackData();

	// Retro Fitting functions
	void RetroFitChanging();
	void RetroFitFinished();


public: // brush functions
		
	void CreateBrush();
	void SetCurrentBrushHandle();
		// finds the current default brush attribute

	MILLIPOINT GetBrushSpacing();
	void SetBrushSpacing(MILLIPOINT Spacing);
	BrushHandle GetBrushHandle() { return m_BrushHandle;}
		
	void BrushFinished();
	BOOL BrushSelected(BrushHandle Handle, BOOL ApplyToSelection = TRUE);
		// tells the tool that the given brush has become the default attribute
	
	BOOL ApplyBrushToSelection(BrushHandle Handle);

	void ScreenChanged(BOOL WipeRegion = FALSE);
		// notifies the tool that the screen has changed

	void InitialiseJoinInfoForBrush(AttrBrushType* pAttrBrush, NodePath* pNodePath, DocCoord JoinPoint);
		// sets up JoinInfo to join with the given brush
	
	void BrushDeleted(BrushHandle Handle);  
		// lets the tool know we have deleted a brush

	BOOL SetBrushUpdateState(UPDATE_STATE State); // tells us when to next update the brush

protected:
		// the big bitmap that is passed to opdrawbrush
	GRenderBrush* GetBigGRenderBrush(Spread* pSpread);
	BOOL InitialiseBrushBitmaps(GRenderBrush* pGRender);

	GRenderBrush* m_pGRenderBrush;

	// gets the brush selected to be default current attribute 
	BrushDefinition* GetSelectedBrush();
	
	UPDATE_STATE m_UpdateBrushState; //indicates when we will update the offscreen buffer
protected:
	// Helper functions
	// Functions to load, remove and change the active cursor
	BOOL LoadCursors();
	void RemoveCursors();
	void ChangeCursor(Cursor* pCursor);

	// Functions to help decide what the mouse is over before the drag starts
	BOOL IsCursorNearEndPoint(NodePath* pPath, const DocRect& BlobRect);
	BOOL IsCursorNearPath(NodePath* pPath, INT32 Range, const DocCoord& PointerPos);

	// Functions to help manage the paths we control
	BOOL GetNewPaths();
	BOOL DeletePaths();

	BOOL InitialiseBlendRef(NodeRenderableInk* pInk);
	BOOL NodeHasLineWidth(NodeRenderableInk* pNode);

	void SetColourEditorProcessing(BOOL Value);
protected:
	DocRect GetLargestInkBoundingRect();  //retrieves the bounding rect of the largest brush ink node
	void InitialiseBrushInkNodeArray(UINT32 NumObjects);
	void LaunchBrushDefinitionDialog(BrushHandle Handle);

	static 	TCHAR* FamilyName;	// The Tools Family Name
	static 	TCHAR* ToolName;		// The Tool Name
	static 	TCHAR* Purpose;		// What the tool is for
	static 	TCHAR* Author;		// Who wrote it

	// The required smoothness
	INT32  Smoothness;

	// The status line text
	String_256 StatusMsg;

	// The coord of the initial click
	DocCoord StartPos;
	Spread*  StartSpread;

	// Data used to retro fit the path
	// The Mouse Track path that holds the last set of mouse move positions
	Path* 		TrackData;
	Path*		RetroPath;
	INT32  		StartSlot;
	INT32  		NumSlots;
	INT32			PathCRC;
	NodePath* 	PreviousPath;
	BOOL		AreWeRetroFitting;
	BOOL		IsPreviousPathValid;
	BOOL		IsRetroPathValid;
	BOOL 		IsSelectBlobsOnScreen;

	// The tools cursor
	Cursor* pNormalCursor;				// The normal cursor
	Cursor* pJoinCursor;				// The cursor used when Joining is possible
	Cursor* pActiveCursor;				// Whichever cursor is being displayed (see ChangeCursor).
	Cursor* pModifyCursor;				// The cursor that appears when it is possible to modify the line
	INT32 CurrentCursorID;				// ID of the current cursor on the stack

	// The path we need to join with if we start over one of its endpoints
	FreeHandJoinInfo JoinInfo;
	
	// The info bar
	FreeHandInfoBarOp* pInfoBarOp;

	std::vector< NodeRenderableInk * > m_BrushInkNodeArray;  
										 // as safer alternative to m_pBrushInkNodes

	BlendRef* m_pBlendRef;				 // the blendref also used to create a brush
	MILLIPOINT m_BrushSpacing;
	UINT32 m_NumInkNodes;                  // counts the number of ink nodes we will use
	BrushHandle m_BrushHandle;           // handle of the brush that we are going to draw with
	BOOL m_bBrushReady;

	String_256 m_LastBrushDocument;      // the name of the last document that the brush was used on

public:
	//Preference variable: determine whether freehand pointers have crosshairs
	static BOOL FreehandPtrCrosshair;

};


#endif  //INC_FREEHAND



