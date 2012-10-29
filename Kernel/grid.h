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

// NodeGrid header

#ifndef INC_GRID_H
#define INC_GRID_H


// The following enum defines the eight select blobs of a grid in a specific way. These values are used to
// reference the coords available from NodeGrid::GetBlobCoords.
//
// Some code relies on the way the enum is defined...
//
//  Each grid has eight select blobs, four corner points and four mid line points
//  The four corner   points are numbered 0 to 3 in a clockwise direction around the grid rectangle
//  The four mid line points are numbered 4 to 7 in a clockwise direction around the grid rectangle
//  NoGridBlob must be negative
//  BottomLeft must be 0
//  LeftMiddle must be 4
enum GridBlobType
{
	NoGridBlob = -1,
	BottomLeft,
	TopLeft,
	TopRight,
	BottomRight,

	LeftMiddle,
	TopMiddle,
	RightMiddle,
	BottomMiddle,

	NumGridBlobTypes
};

struct GridFlagsType				// Grid flags type definition
{
	BOOL 	Selected 		: 1;	// TRUE if selected by grid tool
	BOOL	RelativeOrigin 	: 1;	// TRUE if origin relative to bottom left of grid bounds
	BOOL	DefaultGrid		: 1;	// TRUE if it's a Default grid that covers whole of spread
	BOOL	Disabled		: 1; 	// TRUE if the grid is disabled (i.e. can't snap, render, select, etc)
};

enum GridType { INVALID_GRID_TYPE,RECTANGULAR,ISOMETRIC};

#define NUM_GRID_TYPES 2

class ProcessGrid;

/***********************************************************************************************

>	 class NodeGrid : public NodeRenderablePaper

	 Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	 Created:		8/2/94
     Base Classes: 	NodeRenderablePaper, NodeRenderable, Node, CCObject        
	 Purpose:		An abstract class defining the common elements of grid nodes.

	   				See the Node class for an important note about producing derived 
	   				classes of Node. 

	 SeeAlso:		NodeRenderablePaper   
	
***********************************************************************************************/

class NodeGrid: public NodeRenderablePaper
{   
	CC_DECLARE_DYNAMIC( NodeGrid ) 

public:  
	NodeGrid(); 

	virtual SubtreeRenderState RenderSubtree(RenderRegion* pRender, Node** ppNextNode = NULL, BOOL bClip = TRUE);
			  
	virtual String Describe(BOOL Plural, BOOL Verbose);    		   	
		   		   
	virtual void Render( RenderRegion* pRender );
		
	#ifdef _DEBUG						  
	virtual void ShowDebugTreeDetails() const;   
	#endif
	
	virtual void GetDebugDetails(StringBase* Str);   // This is used by the Debug Tree dialog
													 // It will probably be deleted when we ship !. 
	virtual BOOL Snap(DocCoord* pDocCoord);
	virtual BOOL Snap(DocRect* pDocRect,const DocCoord& PrevCoord,const DocCoord& CurCoord);

	// MOVE THESE INTO GRID.CPP 
	BOOL IsGridSelected() const;
	void SetGridSelected(BOOL selected);
	BOOL IsDefault() const;
	void SetDefault(BOOL Default);
	BOOL IsDisabled() const;
	void SetDisabled(BOOL Disabled);
	virtual BOOL IsRenderedAsInk() const {return TRUE;}

	DocRect GetBoundingRect();
	void 	SetBoundingRect(const DocRect& BRect);
	DocRect GetBlobBoundingRect();

	DocCoord GetBlobCoord(GridBlobType GridBlob);

	void SetOrigin(MILLIPOINT X,MILLIPOINT Y);
	void GetOrigin(MILLIPOINT* pX,MILLIPOINT* pY);
	
	virtual BOOL SetGridParams(double,UINT32,UnitType,BOOL Scale=TRUE) { return FALSE; }

	virtual double   CalcDivisions(BOOL Scale);

	virtual double   GetDivisions(BOOL Scale=TRUE) { return 1.0;}
	virtual UnitType GetUnits(    BOOL Scale=TRUE) { return INCHES; }
	virtual UINT32   	 GetSubdivisions()	{ return 1;}
	virtual GridType GetGridType()		{ return INVALID_GRID_TYPE; }
	virtual double	 GetMainStep()		{ return 72000.0; }

	static void RecalcNumSelectedGrids(Spread* pSpread);
	static void ProcessAllGrids(ProcessGrid* pProcessGrid);
	static void ProcessGridsInSpread(ProcessGrid* pProcessGrid,Spread* pSpread);
	static void ForceRedrawAllGrids();
	static void MakeDefaultGrid(Spread* pSpread, BOOL Scale=TRUE);

	// Call this before starting a drag that will use the DocRect version of the snap function
	static void ResetDocRectSnap();

	//  A set of access functions to the various vars of the grid system
	static UINT32 	GetNumSelectedGrids();
	static UINT32 	GetNumNonDefaultSelectedGrids();
	static GridType	GetTypeForDefaultGrid();
	static BOOL		GetDefaultGridDisabled();
	static double	GetDefaultDivisions();
	static UINT32		GetDefaultSubdivisions();
	static UnitType	GetDefaultUnits();
	static GridType	GetDefaultGridType();

	static void		SetTypeForDefaultGrid(GridType GType);
	static void		SetDefaultGridDisabled(BOOL state);
	static void 	SetDefaultDivisions(double Div);
	static void		SetDefaultSubdivisions(UINT32 Sub);
	static void 	SetDefaultUnits(UnitType UType);
	static void		SetDefaultGridType(GridType	GType);

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

protected:
	// Functions to write the actual data out
	virtual BOOL WriteGridAndRulerSettings(BaseCamelotFilter* pFilter);
	virtual BOOL WriteGirdAndRulerOrigin(BaseCamelotFilter* pFilter);

protected:
	virtual Node* SimpleCopy();
	virtual UINT32 GetNodeSize() const				{ return sizeof(*this); }
	void CopyNodeContents(NodeGrid* NodeCopy);
	void UpdateBlobsData();		// Updates the internal select blob coords data

	void CalcGridRenderSteps(MILLIPOINT PixelWidth,double* pStep,double DomStep,UnitType Units);

	MILLIPOINT SnapOrdinate(MILLIPOINT ord,double Step,MILLIPOINT origin);

	// REMEMBER TO UPDATE CopyNodeContents

	MILLIPOINT	XOrigin;			// X origin of first grid point relative to spread's (0,0) coord
	MILLIPOINT	YOrigin;			// Y origin of first grid point relative to spread's (0,0) coord

	DocColour 		GridColour; 
	DocRect			GridBoundingRect;

	static INT32	LastXDir;
	static INT32	LastYDir;

private:
	GridFlagsType 	GridFlags;
	DocCoord 		BlobCoords[NumGridBlobTypes];

	static UINT32 NumSelected;
	static UINT32 NumNonDefaultSelected;

	static GridType	TypeForDefaultGrid;
	static BOOL		DefaultGridDisabled;
	static double	DefaultDivisions;
	static UINT32		DefaultSubdivisions;
	static UnitType	DefaultUnits;
	static GridType	DefaultGridType;

protected:
	void DumpRect(DocRect& R,TCHAR* S);
};

/***********************************************************************************************

>	 class NodeGridRect : public NodeGrid

	 Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	 Created:		8/2/94
     Base Classes: 	NodeGrid, NodeRenderablePaper, NodeRenderable, Node, CCObject        
	 Purpose:		A class defining a rectangular grid node.

	   				See the Node class for an important note about producing derived 
	   				classes of Node. 

	 SeeAlso:		NodeGrid, NodeRenderablePaper   
	
***********************************************************************************************/

class NodeGridRect: public NodeGrid
{   
	CC_DECLARE_DYNAMIC( NodeGridRect ) 

public:  
	NodeGridRect(); 
	
	String Describe(BOOL Plural, BOOL Verbose);    		   	
		   		   
	void Render( RenderRegion* pRender );
		
	#ifdef _DEBUG						  
	void ShowDebugTreeDetails() const;   
	#endif
	
	void GetDebugDetails(StringBase* Str);   // This is used by the Debug Tree dialog
													 // It will probably be deleted when we ship !. 

	BOOL Snap(DocCoord* pDocCoord);	
	BOOL Snap(DocCoord* pDocCoord,double XStep,double YStep);	
	BOOL Snap(DocRect* pDocRect,const DocCoord& PrevCoord,const DocCoord& CurCoord);


	BOOL SetGridParams(double Div,UINT32 SubDiv,UnitType Units, BOOL Scale=TRUE);

	double   GetDivisions(BOOL Scale=TRUE);
	UINT32     GetSubdivisions();
	UnitType GetUnits(BOOL Scale=TRUE);
	GridType GetGridType() { return RECTANGULAR; }

	double	 GetMainStep() { return MainXStep; }

	Node* SimpleCopy();   
	virtual UINT32 GetNodeSize() const				{ return sizeof(*this); }

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:
	void CopyNodeContents(NodeGridRect* NodeCopy);

private:
	
	void RenderMainPoints(RenderRegion* pRender,DocRect RendRect,MILLIPOINT pixelWidth);
	void RenderSubPoints(RenderRegion* pRender,DocRect RendRect,MILLIPOINT pixelWidth);

	// ***** REMEMBER TO UPDATE CopyNodeContents

	double 		MainXStep;	// X distance between each main grid point
	double	 	MainYStep;	// Y distance between each main grid point
	double 		SubXStep;	// X distance between each sub grid point
	double	 	SubYStep;	// Y distance between each sub grid point

	UnitType	Units;
	double		Divisions;		// defunct, now calc'ed from grid MainStep and units (so independent of scaling)
	UINT32		Subdivisions;
};

/***********************************************************************************************

>	 class NodeGridIso : public NodeGrid

	 Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	 Created:		8/2/94
     Base Classes: 	NodeGrid, NodeRenderablePaper, NodeRenderable, Node, CCObject        
	 Purpose:		A class defining an isometric grid node.

	   				See the Node class for an important note about producing derived 
	   				classes of Node. 

	 SeeAlso:		NodeGrid, NodeRenderablePaper   
	
***********************************************************************************************/

class NodeGridIso: public NodeGrid
{   
	CC_DECLARE_DYNAMIC( NodeGridIso ) 

public:  
	NodeGridIso(); 
	
	String Describe(BOOL Plural, BOOL Verbose);    		   	
		   		   
	void Render( RenderRegion* pRender );
		
	#ifdef _DEBUG						  
	void ShowDebugTreeDetails() const;   
	#endif
	
	void GetDebugDetails(StringBase* Str);   // This is used by the Debug Tree dialog
													 // It will probably be deleted when we ship !. 

	BOOL Snap(DocCoord* pDocCoord);	
	BOOL Snap(DocCoord* pDocCoord,double Step);	
	BOOL Snap(DocRect* pDocRect,const DocCoord& PrevCoord,const DocCoord& CurCoord);

	BOOL SetGridParams(double Div, UINT32 SubDiv, UnitType Units, BOOL Scale=TRUE);

	double   GetDivisions(BOOL Scale=TRUE);
	UINT32     GetSubdivisions();
	UnitType GetUnits(BOOL Scale=TRUE);
	GridType GetGridType() { return ISOMETRIC; }

	double	 GetMainStep() { return MainStep; }

	Node* SimpleCopy();   
	virtual UINT32 GetNodeSize() const				{ return sizeof(*this); }

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:
	void CopyNodeContents(NodeGridIso* NodeCopy);

private:
	
	void RenderPoints(RenderRegion* pRender,DocRect RendRect,MILLIPOINT pixelWidth);

	void RenderSubPoints(	RenderRegion* pRender,
							const DocCoord& MainGridPoint,
							MILLIPOINT MainRenderStep,
							MILLIPOINT SubRenderStep,
							MILLIPOINT pixelWidth,
							DocRect& ScaledBB);

	MILLIPOINT CalcYOrigin(MILLIPOINT x,double Step);

	// ***** REMEMBER TO UPDATE CopyNodeContents

	double 		MainStep;	// distance between each main grid point
	double	 	SubStep;	// distance between each sub grid point

	UnitType	Units;
	double		Divisions;		// defunct, now calc'ed from grid MainStep and units (so independent of scaling)
	UINT32		Subdivisions;
};


/********************************************************************************************

>	class ProcessGrid : SimpleCCObject

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/7/94
	Purpose:	An abstract class used for processing a grid

********************************************************************************************/

class ProcessGrid : public SimpleCCObject
{
public:
	virtual ~ProcessGrid() { }
	virtual void Process(NodeGrid* pGrid) = 0;

	Document* 	pDoc;
	Chapter*	pChapter;
	Spread*		pSpread;
};

/********************************************************************************************

>	class ProcessGridForceRedraw : ProcessGrid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/7/94
	Purpose:	Forces a redraw on the given grid

********************************************************************************************/

class ProcessGridForceRedraw : public ProcessGrid
{
public:
	void Process(NodeGrid* pGrid);
};


/********************************************************************************************

>	class ProcessGridUnitMsg : ProcessGrid

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/7/94
	Purpose:	Something has happened to the units system

********************************************************************************************/

class ProcessGridUnitMsg : public ProcessGrid
{
public:
	ProcessGridUnitMsg(UnitMsg* pThisUnitMsg);

	void Process(NodeGrid* pGrid);

private:
	UnitMsg* pUnitMsg;
};


#endif // INC_GRID_H
