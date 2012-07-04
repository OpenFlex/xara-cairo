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

// Implement the ops that are associated with snapping (e.g. the "snap to grid" menu op)

/*
*/

#include "camtypes.h"
#include "snapops.h"
//#include "markn.h"
//#include "docview.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "tool.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "grid.h"
//#include "bars.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "barsdlgs.h"
//#include "document.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "layer.h"
//#include "spread.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "sglayer.h"
#include "sprdmsg.h"
#include "bubbleid.h"

DECLARE_SOURCE("$Revision: 1785 $");

CC_IMPLEMENT_DYNCREATE(OpShowGrid, 		Operation)
CC_IMPLEMENT_DYNCREATE(OpSnapToGrid, 	Operation)
// WEBSTER - markn 15/1/97
// Removed some op that no longer used in Webster
#ifndef WEBSTER
CC_IMPLEMENT_DYNCREATE(OpShowGuides, 	Operation)
CC_IMPLEMENT_DYNCREATE(OpSnapToObjects, Operation)
CC_IMPLEMENT_DYNCREATE(OpSnapToGuides,  Operation)
#endif

#define new CAM_DEBUG_NEW

/********************************************************************************************

>	static BOOL OpShowGrid::Init()

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/2/94
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if worked, FALSE if failed (out of memory)
	Purpose:	Declares op descriptors for show grid toggle op
	Errors:		Returns FALSE on failure.
	Scope:		Static

********************************************************************************************/


BOOL OpShowGrid::Init()
{
	return RegisterOpDescriptor(	0,							// Tool ID
									_R(IDS_SHOWGRID),				// String resource ID
									CC_RUNTIME_CLASS(OpShowGrid),// Runtime class
									OPTOKEN_SHOWGRID,			// Token string
									GetState,					// GetState function									0,							// help ID
									0,							// help ID
									_R(IDBBL_SHOWGRIDOP),			// bubble help
									_R(IDD_BARCONTROLSTORE),		// resource ID
									_R(IDC_BTN_WINDOWGRID),			// control ID
									SYSTEMBAR_WINDOW,			// Bar ID
									TRUE,						// Recieve system messages
									FALSE,						// Smart duplicate operation
									TRUE,						// Clean operation
									0,							// No vertical counterpart
									0,							// String for one copy only error
									(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC), // Auto state flags
									TRUE						// fCheckable
								);
}

/********************************************************************************************

>	OpShowGrid::OpShowGrid()

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/2/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	Constructor for OpShowGrid operation. It is not undoable.
	Errors:		None

********************************************************************************************/

OpShowGrid::OpShowGrid()
{
}

/********************************************************************************************

>	void OpShowGrid::Do(OpDescriptor*)

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/2/94
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Forces a redraw of the selected DocView and toggles the NodeGrid::RenderFlag flag
	Errors:		None

********************************************************************************************/

void OpShowGrid::Do(OpDescriptor*)
{
	DocView *pDocView = DocView::GetSelected();

	if (pDocView != NULL)
	{
		if (Tool::GetCurrentID() != TOOLID_GRID)
			NodeGrid::ForceRedrawAllGrids();

		pDocView->SetShowGridState(!pDocView->GetShowGridState());
	}

	End();
}

/********************************************************************************************

>	OpState OpShowGrid::GetState(String_256*, OpDescriptor*)

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/2/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	This item is always available, so long as a document is visible.
	Errors:		None

********************************************************************************************/

OpState OpShowGrid::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;

	DocView *pDocView = DocView::GetSelected();
	if (pDocView != NULL)
		OpSt.Ticked = pDocView->GetShowGridState();

	return OpSt;
}


//--------------------------------------------------------------------------------------------


/********************************************************************************************

>	static BOOL OpSnapToGrid::Init()

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/2/94
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if worked, FALSE if failed (out of memory)
	Purpose:	Declares op descriptors for snap to grid toggle op
	Errors:		Returns FALSE on failure.
	Scope:		Static

********************************************************************************************/


BOOL OpSnapToGrid::Init()
{
	return RegisterOpDescriptor(0,							// tool id
								_R(IDS_SNAPTOGRID),				// String resource ID
								CC_RUNTIME_CLASS(OpSnapToGrid),// Runtime class
								OPTOKEN_SNAPTOGRID,			// Token string
								GetState,					// GetState function								0,							// help ID 
								0,								// help ID
								_R(IDBBL_SNAPTOGRIDOP),			// bubble help
								_R(IDD_BARCONTROLSTORE),		// resource ID
								_R(IDC_BTN_WINDOWSNAP),			// control ID
								SYSTEMBAR_WINDOW,			// Bar ID
								TRUE,						// Recieve system messages
								FALSE,						// Smart duplicate operation
								TRUE,						// Clean operation
								0,							// No vertical counterpart
								0,							// String for one copy only error
								(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC), // Auto state flags
								TRUE						// fCheckable
							  );
}

/********************************************************************************************

>	OpSnapToGrid::OpSnapToGrid()

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/2/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	Constructor for OpSnapToGrid operation. It is not undoable.
	Errors:		None

********************************************************************************************/

OpSnapToGrid::OpSnapToGrid()
{
}

/********************************************************************************************

>	void OpSnapToGrid::Do(OpDescriptor*)

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/2/94
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Toggles the "snap to grid" flag in the selected DocView
	Errors:		None

********************************************************************************************/

void OpSnapToGrid::Do(OpDescriptor*)
{
	DocView *pDocView = DocView::GetSelected();

	if (pDocView != NULL)
		pDocView->SetSnapToGridState(!pDocView->GetSnapToGridState());

	End();
}

/********************************************************************************************

>	OpState OpSnapToGrid::GetState(String_256*, OpDescriptor*)

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/2/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	This item is always available, so long as a document is visible.
	Errors:		None

********************************************************************************************/

OpState OpSnapToGrid::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;

	DocView *pDocView = DocView::GetSelected();
	if (pDocView != NULL)
		OpSt.Ticked = pDocView->GetSnapToGridState();
	
	return OpSt;
}

//--------------------------------------------------------------------------------------------

// WEBSTER - markn 15/1/97
// Removed some op that no longer used in Webster
#ifndef WEBSTER


/********************************************************************************************

>	static BOOL OpSnapToObjects::Init()

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/9/94
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if worked, FALSE if failed (out of memory)
	Purpose:	Declares op descriptors for snap to objects toggle op
	Errors:		Returns FALSE on failure.
	Scope:		Static

********************************************************************************************/


BOOL OpSnapToObjects::Init()
{
	return RegisterOpDescriptor(0,							// Tool ID
								_R(IDS_SNAPTOOBJECTS),			// String resource ID
								CC_RUNTIME_CLASS(OpSnapToObjects),// Runtime class
								OPTOKEN_SNAPTOOBJECTS,		// Token string
								GetState,					// GetState function
								0,							// help ID 
								_R(IDBBL_SNAPTOOBJECTS),		// Bubble ID 
								_R(IDD_BARCONTROLSTORE),		// resource ID
								0,							// control ID
								SYSTEMBAR_WINDOW,			// Bar ID
								TRUE,						// Recieve system messages
								FALSE,						// Smart duplicate operation
								TRUE,						// Clean operation
								0,							// No vertical counterpart
								0,							// String for one copy only error
								(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC), // Auto state flags
								TRUE						// fCheckable
							  );
}

/********************************************************************************************

>	OpSnapToObjects::OpSnapToObjects()

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/9/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	Constructor for OpSnapToObjects operation. It is not undoable.
	Errors:		None

********************************************************************************************/

OpSnapToObjects::OpSnapToObjects()
{
}

/********************************************************************************************

>	void OpSnapToObjects::Do(OpDescriptor*)

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/9/94
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Toggles the "snap to objects" flag in the selected DocView
	Errors:		None

********************************************************************************************/

void OpSnapToObjects::Do(OpDescriptor*)
{
	DocView *pDocView = DocView::GetSelected();

	if (pDocView != NULL)
	{
		// Find out the new value for the magnetic snapping
		BOOL NewState = !pDocView->GetSnapToObjectsState();
		pDocView->SetSnapToObjectsState(NewState);

		// update all slider controls that show the view quality
		OpDescriptor* pOpDesc = OpDescriptor::FindOpDescriptor(OPTOKEN_SNAPTOOBJECTS);
		if (pOpDesc!=NULL)
		{
			// Found the opdescriptor. Now find all the gadgets associated with it
			List Gadgets;
			if (pOpDesc->BuildGadgetList(&Gadgets))
			{
				// Found some. Set the controls position according to the quality
				GadgetListItem* pGadgetItem = (GadgetListItem*) Gadgets.GetHead();

				while (pGadgetItem!=NULL)
				{
					// Set the sliders position
					pGadgetItem->pDialogOp->SetLongGadgetValue(pGadgetItem->gidGadgetID, NewState, FALSE);

					// go find the next gadget
					pGadgetItem = (GadgetListItem*) Gadgets.GetNext(pGadgetItem);
				}
		
				// Clean out the list
				Gadgets.DeleteAll();
			}
		}
	}

	End();
}

/********************************************************************************************

>	OpState OpSnapToObjects::GetState(String_256*, OpDescriptor*)

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/9/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	This item is always available, so long as a document is visible.
	Errors:		None

********************************************************************************************/

OpState OpSnapToObjects::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;

	DocView *pDocView = DocView::GetSelected();
	if (pDocView != NULL)
		OpSt.Ticked = pDocView->GetSnapToObjectsState();
	
	return OpSt;
}

//--------------------------------------------------------------------------------------------

/********************************************************************************************

>	static BOOL OpSnapToGuides::Init()

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if worked, FALSE if failed (out of memory)
	Purpose:	Declares op descriptors for snap to guides toggle op
	Errors:		Returns FALSE on failure.
	Scope:		Static

********************************************************************************************/


BOOL OpSnapToGuides::Init()
{
	return RegisterOpDescriptor(0,							// Tool ID
								_R(IDS_SNAPTOGUIDES),			// String resource ID
								CC_RUNTIME_CLASS(OpSnapToGuides),// Runtime class
								OPTOKEN_SNAPTOGUIDES,		// Token string
								GetState,					// GetState function
								0,							// help ID 
								_R(IDBBL_SNAPTOGUIDES),			// Bubble ID 
								_R(IDD_BARCONTROLSTORE),		// resource ID
								0,							// control ID
								SYSTEMBAR_WINDOW,			// Bar ID
								TRUE,						// Recieve system messages
								FALSE,						// Smart duplicate operation
								TRUE,						// Clean operation
								0,							// No vertical counterpart
								0,							// String for one copy only error
								(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC), // Auto state flags
								TRUE						// fCheckable
							  );
}

/********************************************************************************************

>	OpSnapToGuides::OpSnapToGuides()

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Inputs:
	Outputs:
	Returns:
	Purpose:	Constructor for OpSnapToGuides operation. It is not undoable.
	Errors:		None

********************************************************************************************/

OpSnapToGuides::OpSnapToGuides()
{
}

/********************************************************************************************

>	void OpSnapToGuides::Do(OpDescriptor*)

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Toggles the "snap to guides" flag in the selected DocView
	Errors:		None

********************************************************************************************/

void OpSnapToGuides::Do(OpDescriptor*)
{
	DocView *pDocView = DocView::GetSelected();

	if (pDocView != NULL)
		pDocView->SetSnapToGuidesState(!pDocView->GetSnapToGuidesState());

	End();
}

/********************************************************************************************

>	OpState OpSnapToGuides::GetState(String_256*, OpDescriptor*)

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Inputs:
	Outputs:
	Returns:
	Purpose:	This item is always available, so long as a document is visible.
	Errors:		None

********************************************************************************************/

OpState OpSnapToGuides::GetState(String_256* pUIDescription, OpDescriptor*)
{
	OpState OpSt;

	DocView *pDocView = DocView::GetSelected();
	if (pDocView != NULL)
		OpSt.Ticked = pDocView->GetSnapToGuidesState();

	Spread* pSpread = Document::GetSelectedSpread();
	if (pSpread != NULL)
	{
		// if we have a guide layer, then make the menu item available, if not, grey it 
		//	and give a reason.
		if (pSpread->FindFirstGuideLayer() != NULL)
		{
			OpSt.Greyed = FALSE;
		}
		else
		{
			OpSt.Greyed = TRUE;
			*pUIDescription = String_256 (_R(IDS_NO_GUIDES));
		}
	}
	
	return OpSt;
}

//--------------------------------------------------------------------------------------------

/********************************************************************************************

>	static BOOL OpShowGuides::Init()

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/9/95
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if worked, FALSE if failed (out of memory)
	Purpose:	Declares op descriptors for show grid toggle op
	Errors:		Returns FALSE on failure.
	Scope:		Static

********************************************************************************************/


BOOL OpShowGuides::Init()
{
	return RegisterOpDescriptor(	0,							// Tool ID
									_R(IDS_SHOWGUIDES),				// String resource ID
									CC_RUNTIME_CLASS(OpShowGuides),// Runtime class
									OPTOKEN_SHOWGUIDES,			// Token string
									GetState,					// GetState function									0,							// help ID
									0,							// help ID
									_R(IDBBL_SHOWGUIDES),			// bubble help
									_R(IDD_BARCONTROLSTORE),		// resource ID
									_R(IDC_BTN_WINDOWGRID),			// control ID
									SYSTEMBAR_WINDOW,			// Bar ID
									TRUE,						// Recieve system messages
									FALSE,						// Smart duplicate operation
									TRUE,						// Clean operation
									0,							// No vertical counterpart
									0,							// String for one copy only error
									(DONT_GREY_WHEN_SELECT_INSIDE | GREY_WHEN_NO_CURRENT_DOC), // Auto state flags
									TRUE						// fCheckable
								);
}

/********************************************************************************************

>	OpShowGuides::OpShowGuides()

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/9/95
	Inputs:
	Outputs:
	Returns:
	Purpose:	Constructor for OpShowGuides operation. It is not undoable.
	Errors:		None

********************************************************************************************/

OpShowGuides::OpShowGuides()
{
}

/********************************************************************************************

>	void OpShowGuides::Do(OpDescriptor*)

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/9/95
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Forces a redraw of the selected DocView and toggles the view's ShowGuides flag
	Errors:		None

********************************************************************************************/

void OpShowGuides::Do(OpDescriptor*)
{
	DocView *pDocView = DocView::GetSelected();

	if (pDocView != NULL)
	{
		pDocView->SetShowGuidesState(!pDocView->GetShowGuidesState());

		Spread* pSpread = Document::GetSelectedSpread();
		Document* pDoc  = Document::GetSelected();
		if (pSpread != NULL && pDoc != NULL)
		{
			Layer* pLayer = pSpread->FindFirstGuideLayer();
			if (pLayer != NULL)
				LayerSGallery::ForceRedrawLayer(pDoc,pLayer);
		}

		BROADCAST_TO_ALL(SpreadMsg(pSpread,SpreadMsg::LAYERCHANGES));
	}

	End();
}

/********************************************************************************************

>	OpState OpShowGuides::GetState(String_256*, OpDescriptor*)

	Author: 	Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/9/95
	Inputs:
	Outputs:
	Returns:
	Purpose:	This item is always available, so long as a document is visible.
	Errors:		None

********************************************************************************************/

OpState OpShowGuides::GetState(String_256* pUIDescription, OpDescriptor*)
{
	OpState OpSt;

	DocView *pDocView = DocView::GetSelected();
	if (pDocView != NULL)
		OpSt.Ticked = pDocView->GetShowGuidesState();

	Spread* pSpread = Document::GetSelectedSpread();
	if (pSpread != NULL)
	{
		// if we have a guide layer, then make the menu item available, if not, grey it 
		//	and give a reason.
		if (pSpread->FindFirstGuideLayer() != NULL)
		{
			OpSt.Greyed = FALSE;
		}
		else
		{
			OpSt.Greyed = TRUE;
			*pUIDescription = String_256 (_R(IDS_NO_GUIDES));
		}

	}	// if (pSpread != NULL)

	return OpSt;
}

#endif // WEBSTER
