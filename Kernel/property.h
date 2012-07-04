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

// 
// Header file for AppPrefs.cpp
//
// 

#ifndef INC_PropertyTabsS
#define INC_PropertyTabsS

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "unittype.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "units.h"		// units e.g. Millimeters - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************************************

>	class PropertyTabs : public ListItem

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	28/9/94
	Purpose:	These encompass some useful functionality which is required to get a property
				dialog tab up and running. This is the baseclass and should always be derived
				off from. Tabs currently available are:-
					- layer properties dialog box

	SeeAlso:	LayerPropertyTabs

********************************************************************************************/

class CCAPI PropertyTabs : public ListItem
{
	CC_DECLARE_DYNAMIC(PropertyTabs);

public:
	PropertyTabs();							// Constructor

	virtual BOOL Init();					// Initialisation

	// Function to declare a tab handling class to the property tabs system
//	static BOOL DeclarePropertyTab(PropertyTabs *pProperty);
//	static BOOL UndeclarePropertyTab(PropertyTabs *pProperty);
//
//	static PropertyTabs *GetFirst();
//	static PropertyTabs *GetNext(PropertyTabs*);

	virtual BOOL SetUpDocUnits();					// function to set up CurrentPageUnits

	static Document * pScopeDocument;				// current document (for message broadcasts) 

	virtual void SetCurrentDocAndSpread(Document *pDoc);	// set up the spread that we are currently workign on
	virtual void SetDefaultUnits();	  						// set up our default display units

	//MsgResult HandleMessage(Msg* Message);
	virtual DialogTabOp * GetTabbedDlg()			= 0;	// return pointer to the main dialog box

	//virtual BOOL SetTabbedDlg(DialogTabOp * pDlg)	= 0;	// return pointer to the main dialog box

	// Overridable by the tab section handlers. These are the must be specified functions
	// and so are pure.
	virtual CDlgResID GetPageID()					= 0;	// Return section/page id system
	virtual	BOOL InitSection()						= 0;	// Called when page first opened
	virtual BOOL CommitSection()					= 0;	// Called when ok action is required
	virtual BOOL HandleMsg(DialogMsg* Msg)			= 0;	// Called when messages arrive

	// Public access to the current layer.
	virtual void SetActiveLayer(Layer * pNewLayer);
	virtual Layer * GetActiveLayer();

	// Public access to the guide layer.
	virtual Layer * GetGuideLayer();

	// Public access to the current layer.
	virtual void SetCurrentLayer(Layer * pNewLayer);
	virtual Layer * GetCurrentLayer();

	// Some special handlers for things like new default units being specified or the last
	// document being closed.
	// These are the virtual handlers which each tab should specify, if not required then
	// these base class definitions can be used.
	virtual BOOL NewUnitsInSection();			// Called when new default units chosen
	virtual BOOL GreySection();					// Called when the user has closed all documents
	virtual BOOL UngreySection();				// Called when the user has opened a document
	virtual BOOL UpdateSection();				// Called when the user has switched to a new document

	// Virtual functions used to indicate that details on the current spread and current layer need updating
	virtual BOOL UpdateSpreadSection();			// Called when the user has switched to a new spread
	virtual BOOL UpdateLayerSection();			// Called when the user has switched to a new layer
	virtual BOOL UpdateGuidelineSection();		// Called when the user has changed guidelines on the active layer

	// Colour list functions
	virtual BOOL ColourListChanged(Document* pDoc);

	// Some functions to determine whether this particular property tab is required.
	virtual BOOL IsPropertyRequired();			// Return True if required


	// Functions for getting the message and appply now state for this tabbed dialog box
	virtual BOOL GetApplyNowState()						= 0;	// Get current state of ApplyNow flag
	virtual BOOL SetApplyNowState(BOOL NewState)		= 0;	// set new state for ApplyNow 

	virtual BOOL SetInitMessageState(BOOL NewState)		= 0;	// set new state of InitMessage
	virtual BOOL GetInitMessageState()					= 0;	// get current state of InitMessage

	virtual BOOL GreyApplyNow();						// grey the apply now button
	virtual BOOL UngreyApplyNow();						// grey the apply now button

	virtual BOOL SetOkState(BOOL Val);					// Set the state of the OK button on the tabbed dialog.

	Spread*	GetSpread()									{ return  pSpread; }

protected:
	// Allow the options tabs access but nobody else to these useful variables
	static Document *pDocument;					// The document we are working on
	static Spread   *pSpread; 					// The spread we are working on 

	static UnitType CurrentPageUnits;			// The units used to display page measurements

private:
	static Layer	*pActiveLayer;				// The active layer we are working on 
	static Layer 	*pCurrentLayer; 			// pointer to the layer to be used,

	// The list of property tabs that is understood.
	//static List PropertyTabsList;		// list of available tab handlers
};

#endif  // INC_PropertyTabsS


