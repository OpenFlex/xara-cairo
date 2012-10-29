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

// More path releated operations - pathedit.cpp is getting big

#ifndef INC_PATHOPS
#define INC_PATHOPS

#define OPTOKEN_MOVEPATHPOINT	_T("MovePathPoint")
#define OPTOKEN_MAKELINESOP		_T("MakeLines")
#define OPTOKEN_MAKECURVESOP	_T("MakeCurves")
#define OPTOKEN_SELECTALLPATHPOINTS _T("SelectAllPathPoints")
#define OPTOKEN_DESELECTALLPATHPOINTS _T("DeSelectAllPathPoints")

#include "transop.h"


/********************************************************************************************

>	class OpBaseConvertPathSegment : public SelOperation

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/95
	Purpose:	This is the base class for the two operations that convert curve segments into
				line segments and vice-versa.
	SeeAlso:	OpMakeSegmentsCurves, OpMakeSegmentsLines

********************************************************************************************/

class OpBaseConvertPathSegment: public SelOperation
{         
	CC_DECLARE_DYNCREATE( OpBaseConvertPathSegment )    

public:
	OpBaseConvertPathSegment();
	void Do(OpDescriptor*);
	static OpState BaseGetState(INT32 PathType);

protected:
	virtual INT32 GetProcessPathType() { ERROR3("Dont call the base class"); return 0;}
	virtual INT32 GetPathType() { ERROR3("Dont call the base class"); return 0;}
	virtual BOOL ProcessSegment(NodePath* pPath, INT32* Index, INT32 PrevIndex) { ERROR3("Dont call the base class"); return 0;}
};  




/********************************************************************************************

>	class OpMakeSegmentsLines : public OpBaseConvertPathSegment

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/9/94
	Purpose:	This class will change all the selected segments in all selected paths from
				curves into lines (ignoring segments that are already lines!).
	SeeAlso:	OpMakeSegmentsCurves

********************************************************************************************/

class OpMakeSegmentsLines: public OpBaseConvertPathSegment
{         
	CC_DECLARE_DYNCREATE( OpMakeSegmentsLines )    

public:
	OpMakeSegmentsLines();								
	static BOOL	Init();
	static OpState GetState(String_256*, OpDescriptor*);		

protected:
	virtual INT32 GetProcessPathType() {return PT_BEZIERTO;}
	virtual INT32 GetPathType() {return PT_LINETO;}
	BOOL ProcessSegment(NodePath* pPath, INT32* Index, INT32 PrevIndex);
};



 /********************************************************************************************

>	class OpMakeSegmentsCurves : public OpBaseConvertPathSegment

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/9/94
	Purpose:	This class will change all the selected segments in all selected paths from
				lines into curves (ignoring segments that are already curves!).
	SeeAlso:	OpMakeSegmentsLines

********************************************************************************************/

class OpMakeSegmentsCurves: public OpBaseConvertPathSegment
{         
	CC_DECLARE_DYNCREATE( OpMakeSegmentsCurves )    

public:
	OpMakeSegmentsCurves();								
	static BOOL	Init();				
	static OpState GetState(String_256*, OpDescriptor*);		
	static BOOL CarryOut(INT32, INT32, NodePath*, UndoableOperation*, ActionList* pActions);

protected:
	virtual INT32 GetProcessPathType() {return PT_LINETO;}
	virtual INT32 GetPathType() {return PT_BEZIERTO;}
	virtual BOOL ProcessSegment(NodePath* pPath, INT32* Index, INT32 PrevIndex);
};  



/***********************************************************************************************

>	class MovePointsParams : public OpParam

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/11/94
	Purpose:	The OpParam to use when calling OpMovePathPoints.  Used to pass in the path to
				alter and which coords to change.
	SeeAlso:	OpMovePathPoint::DoWithParam

***********************************************************************************************/

struct ElementCoord
{
	INT32		Element;
	DocCoord	Coordinate;
};

class MovePointsParams : public OpParam
{
	CC_DECLARE_MEMDUMP(MovePointsParams)	

public:
	MovePointsParams(NodePath* pPath, ElementCoord* ChangeData, INT32 NumChanges);

	NodePath		*PathToEdit;
	ElementCoord	*PathChanges;
	INT32				ChangesCount;
};


/********************************************************************************************

>	class OpMovePathPoint : public TransOperation

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/10/94
	Purpose:	This operation allows the exact positioning of elements in a path.

********************************************************************************************/

class OpMovePathPoint: public TransOperation
{         
	CC_DECLARE_DYNCREATE( OpMovePathPoint )    

public:
	OpMovePathPoint();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			DoWithParam(OpDescriptor*, OpParam*);

private:
	BOOL ClearSmoothAndRotate(NodePath* pPath, INT32 PathIndex);
};  



/*********************************************************************************************
>	class NewPathCreatedMsg : public Msg

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/12/94
	Purpose:	This message is sent whenever a new path is created.  The only client of this
				message (at the moment) is the Line tool, which needs to clear it's floating
				endpoint when a new path is created.
	SeeAlso:	OpNewPath, BezierTool

*********************************************************************************************/

class NewPathCreatedMsg : public Msg
{
	CC_DECLARE_DYNAMIC(NewPathCreatedMsg)

public:
	NodePath*	NewPath;				// Points to the new path	
	Operation*	CurrentOp;				// Points to the active operation
	ActionList*	UndoActs;				// Points to the operations undo list

	NewPathCreatedMsg(NodePath* pPath, Operation* CurOp, ActionList* Undos);
};



/*********************************************************************************************
>	class PathEditedMsg : public Msg

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/12/94
	Purpose:	This message is sent whenever a single control point or an endpoint on a path
				is edited.  A client of this message is the Line tool, which uses the data in
				this message to update the edit fields in its infobar.
	SeeAlso:	OpEditControlPoint, OpEditEndPoint, BezierTool

*********************************************************************************************/

class PathEditedMsg : public Msg
{
	CC_DECLARE_DYNAMIC(PathEditedMsg)

public:
	Path*		EditPath;				// Points to the edited path	
	Spread*		EditSpread;				// The spread containing the path
	INT32		EndPoint;				// The edited endpoint OR the endpoint next to the
										// edited control point

	PathEditedMsg(Path* pPath, Spread* pSpread, INT32 Index);
};



/********************************************************************************************
>	class OpMenuSelectPathPoints : public Operation

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/04/95
	Purpose:	This operation is the base of select/deselect all endpoints in a path
********************************************************************************************/

class OpMenuSelectPathPoints: public Operation
{         
	CC_DECLARE_DYNCREATE( OpMenuSelectPathPoints )    

public:
	OpMenuSelectPathPoints() {};								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);	

protected:
	BOOL DoAction(BOOL SelectPoints);	
};  



/********************************************************************************************
>	class OpSelectAllPathPoints : public OpMenuSelectPathPoints

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/04/95
	Purpose:	This operation is used to select all endpoints in a path
********************************************************************************************/

class OpSelectAllPathPoints: public OpMenuSelectPathPoints
{         
	CC_DECLARE_DYNCREATE( OpSelectAllPathPoints )    

public:
	OpSelectAllPathPoints() {};								
	void Do(OpDescriptor*);
};  



/********************************************************************************************
>	class OpDeSelectAllPathPoints : public OpMenuSelectPathPoints

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/04/95
	Purpose:	This operation is used to deselect all endpoints in a path
********************************************************************************************/

class OpDeSelectAllPathPoints: public OpMenuSelectPathPoints
{         
	CC_DECLARE_DYNCREATE( OpDeSelectAllPathPoints )    

public:
	OpDeSelectAllPathPoints() {};								
	void Do(OpDescriptor*);
};



/********************************************************************************************

>	class OpChangeFillProfile : public SelOperation

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/2/2000
	Purpose:	The operation class that is responsible for changing fill profiles.
	SeeAlso:	-

********************************************************************************************/

#define OPTOKEN_REVERSEPATH	_T("ReversePath")				// our all important optoken!

class OpReversePath : public SelOperation
{
	CC_DECLARE_DYNCREATE (OpReversePath)

public:
	OpReversePath ();
	~OpReversePath ();
	
	static BOOL	Init();
	static OpState GetState (String_256* Description, OpDescriptor*);

	void Do (OpDescriptor*);
};



#endif  // INC_PATHOPS
