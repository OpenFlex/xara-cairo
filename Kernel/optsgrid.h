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

// Header for the handling code for the Page tab of the options dialog box 

#ifndef INC_OPTSGRID
#define INC_OPTSGRID

#include "appprefs.h"

//#include "undoop.h"
#include "transop.h"
#include "grid.h" 

#define OPTOKEN_OPGRIDRESIZE  _T("OpGridResize")    

typedef struct
{
	Spread 	*pSpread;					// The spread to be changed

	// Grid resize parameters
	double GridSpacing;					// The new grid spacing 
	double GridDivisions;				// The new number of grid divisions 
	UINT32 GridSubDivisions;				// The new number of grid subdivisions
	UnitType GridUnits;					// The new grid units
 	GridType TypeOfGrid;				// The new grid type

	MILLIPOINT OriginX;					// The new grid origin x
	MILLIPOINT OriginY;					// The new grid origin y

} GridResizeInfo;


/********************************************************************************************

>	class GridTab : public OptionsTabs

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	05/10/94
	Purpose:	Allows the user to set any options which are normally associated
				with the document's default grid and hence the page rulers.
				This includes such things as:-
					Grid and rulers origin
					Grid and rulers spacing and divisions
					Grid type

	SeeAlso:	OptionsTabs; AppPrefsDlg;

********************************************************************************************/

class GridTab: public OptionsTabs
{         
	CC_DECLARE_DYNCREATE( GridTab )  
public:

	GridTab();
	~GridTab();

	virtual BOOL Init();                        

	// Function to handle the messages for this tab/pane window
	virtual BOOL HandleMsg(DialogMsg* Msg);

	// Function to set up the values on this tab when being opened
	virtual BOOL InitSection();

	// Function to commit the values on this tab on ok
	virtual BOOL CommitSection();

	// Function called when new default units come into operation.
	virtual BOOL NewUnitsInSection();

	// Functions to handle document changing messages
	virtual BOOL GreySection();			// Called when the user has closed all documents
	virtual BOOL UngreySection();		// Called when the user has opened a document
	BOOL ChangeControlStatus(const BOOL Status); // used to grey/ungrey all controls
	virtual BOOL UpdateSection(String_256 *DocumentName);	// Called when the user has switched to a new document

	BOOL UpdateGridSection();			// Called when the user has undone a default grid resize

	virtual CDlgResID GetPageID();		// Return section/page id system

	virtual BOOL IsDocumentOption();	// Return True if document option  

	virtual BOOL IsProgramOption();		// Return True if program option

protected:
	BOOL InitGridSection();

public:
	// New function for doing the default grid resize as one operation.
	BOOL InvokeResize(GridResizeInfo *Param);

private:
	double OldGridSpacing; 		// entry default page grid divisions
	UINT32 OldGridSubDivisions;	// entry default page grid subdivisions
	UnitType OldGridUnits;		// entry default page grid units
	GridType OldTypeOfGrid;		// entry default grid type

	MILLIPOINT OldOriginX;		// entry grid origin x
	MILLIPOINT OldOriginY;		// entry grid origin y

	BOOL GreyStatus;			// Remember the state that we are currently in
}; 


/****************************************************************************

>	class OpGridResize: public UndoableOperation

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/10/95
	Purpose:	This class represents the Undo-able operation to resize the
				page and spread.
	SeeAlso:	ActionGridResize

****************************************************************************/
#define OPTOKEN_GRIDRESIZE _T("GridResize")	// Optoken for the grid resize operation

class OpGridResize: public UndoableOperation
{         
	CC_DECLARE_DYNCREATE(OpGridResize)

public:
	OpGridResize();	
	~OpGridResize();	

	static	BOOL Init();                        
	static	OpState GetState(String_256*, OpDescriptor*);

	void	Do(OpDescriptor *);
	void	DoWithParam(OpDescriptor* pOp, OpParam* pResizeParam);	     

protected:
	BOOL DoResizeGrid(GridResizeInfo* pResizeInfo);

private:
	DocRect PasteboardRect;

	MILLIPOINT OriginX;			// entry grid origin x
	MILLIPOINT OriginY;			// entry grid origin y
}; 


/********************************************************************************************

>	class ActionSetDefaultGrid: public Action

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/10/95
	Purpose:	When executed, this sets up an action to redo/undo a default grid resize.
	
	SeeAlso:	OpSetDefaultGrid

********************************************************************************************/

class CCAPI ActionSetDefaultGrid : public Action
{
	CC_DECLARE_DYNCREATE( ActionSetDefaultGrid )

public:
	ActionSetDefaultGrid();
	~ActionSetDefaultGrid();
	virtual ActionCode Execute();
	static ActionCode Init(Operation* const pOp,
							ActionList *pActionList,
							UINT32 ActionSize,
							Spread *pSpread,
							double GridDivisions,
							UINT32 GridSubDivisions,
							UnitType GridUnits,
							GridType TypeOfGrid,
							MILLIPOINT OriginX,
							MILLIPOINT OriginY,
							Action **NewAction);

protected:

private:
	Spread *pSpread;
	double GridDivisions;
	UINT32 GridSubDivisions;
	UnitType GridUnits;
	GridType TypeOfGrid;

	MILLIPOINT OriginX;			// entry grid origin x
	MILLIPOINT OriginY;			// entry grid origin y
};


#endif // INC_OPTSGRID
