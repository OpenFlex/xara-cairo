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

// WEBSTER - markn 15/1/97
// Don't need the layer properties dlg in Webster
//#ifdef WEBSTER
//#define INC_LAYERPROPERTYTABS
//#endif 

#ifndef INC_LAYERPROPERTYTABS
#define INC_LAYERPROPERTYTABS

#include "property.h"	// PropertyTabs class

class LayerPropertyTabs;

/********************************************************************************************

>	class LayerPropertyTabsDlg : public DialogTabOp

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	28/09/95
	Purpose:	The layer properties dialog box
	
				Allows the user to set options like:-
					The name of the layer
					The colour of the guides
					If a guide layer then all the guides on the layer

				Uses the LayerPropertyTabs class which is declared and initialised by this class.
				This uses any application options pages which have been declared to the
				options tabs list. The document options uses the same system.
				Also, declares the PageSizes class to the system so that they are available
				to all options tabs.

	SeeAlso:	LayerPropertyTabs;
	SeeAlso:	AppPrefsDlg; LayerPropertyTabs;
				
********************************************************************************************/
#define OPTOKEN_LAYERPROPERTYTABS	_T("LayerPropertyTabs")

class LayerPropertyTabsDlg : public DialogTabOp
{
	CC_DECLARE_DYNCREATE( LayerPropertyTabsDlg )

public:
	LayerPropertyTabsDlg();							// constructor
	LayerPropertyTabsDlg(INT32 StartingPage);			// constructor
	~LayerPropertyTabsDlg();							// destructor

	void Do(OpDescriptor*);							// "Do" function

	static BOOL Init();								// Setup function
	static void Deinit();							// Remove function

	// No create function as this is handled by the main tab dialog code

	static OpState GetState(String_256*, OpDescriptor*);
													// Return the state of this operation
	virtual MsgResult Message(Msg* Message);		// Message handler
	virtual BOOL RegisterYourPagesInOrderPlease();	// Add in tab pages
	
	// Set up explicit details about this dialog box such as id, type (MODE or MODELESS)
	static const CDlgResID IDD;						// Dialog box id
	static const CDlgMode Mode;						// Dialog box mode of operation (mode or modeless)

	// Functions to commit the values on the dialog box and its sections on ok
	BOOL CommitDialogValues();

	// returns pointer to the layer properties handling class
	static LayerPropertyTabs * GetLayerPropertiesTabs();

private:
	String_256 TitleString;							// title of dialog box

	static LayerPropertyTabs * pLayerProperties;	// pointer to the list class handling this tab
};


/********************************************************************************************

>	class LayerPropertiesDlg : public LayerPropertyTabsDlg

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	10/10/95
	Purpose:	To open up the layer properties tabbed dialog box with the layer's tab
				selected. This is used by the layers pop up menu.

	SeeAlso:	LayerPropertyTabsDlg; LayerPropertyTabs;
	
********************************************************************************************/

class LayerPropertiesDlg : public LayerPropertyTabsDlg
{
	// Defines the OPTOKEN_DLG as this now links to the units tab in
	// this document options dialog box.
#define OPTOKEN_LAYERPROPERTIESDLG	_T("LayerPropertiesDlg")

	CC_DECLARE_DYNCREATE( LayerPropertiesDlg )

public:
	LayerPropertiesDlg();					// constructor

	// All other functionality comes from the LayerPropertyTabsDlg class.
};

/********************************************************************************************

>	class GuidePropertiesDlg : public LayerPropertyTabsDlg

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	10/10/95
	Purpose:	To open up the layer properties tabbed dialog box with the guide's tab
				selected. This is used by the guides pop up menu.

	SeeAlso:	LayerPropertyTabsDlg; LayerPropertyTabs;
	
********************************************************************************************/

class GuidePropertiesDlg : public LayerPropertyTabsDlg
{
	// Defines the OPTOKEN_DLG as this now links to the units tab in
	// this document options dialog box.
#define OPTOKEN_GUIDEPROPERTIESDLG	_T("GuidePropertiesDlg")

	CC_DECLARE_DYNCREATE( GuidePropertiesDlg )

public:
	GuidePropertiesDlg();					// constructor

	// All other functionality comes from the LayerPropertyTabsDlg class.
};


/********************************************************************************************

>	class LayerPropertyTabs : public PropertyTabs

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	28/9/95
	Purpose:	These encompass all the tabs available for the layer properties dialog box
				to use. Derived off the baseclass which has a lot of globally useful
				functionality for all property tabbed dialog box handlers. This is just
				derived of the list class.

	SeeAlso:	PropertyTabs; ListItem;

********************************************************************************************/
class CCAPI LayerPropertyTabs : public PropertyTabs
{
	CC_DECLARE_DYNAMIC(LayerPropertyTabs);

public:
	LayerPropertyTabs();						// Constructor

	static BOOL InitLayerPropertyTabs();		// set up all option tabs available
	static BOOL DeinitLayerPropertyTabs();			// remove all option tabs available

	static LayerPropertyTabs *GetFirst();
	static LayerPropertyTabs *GetNext(LayerPropertyTabs*);

	virtual BOOL Init();						// Initialisation

	// Function to declare a tab/section to the options system
	static BOOL DeclareLayerProperty(LayerPropertyTabs *pLayerProperty);

	// Functions to handle the apply now and message state flags
	virtual BOOL GetApplyNowState();					// Get current state of ApplyNow flag
	virtual BOOL SetApplyNowState(BOOL NewState);		// set new state for ApplyNow 

	virtual BOOL SetInitMessageState(BOOL NewState);	// set new state of InitMessage
	virtual BOOL GetInitMessageState();					// get current state of InitMessage

	// Overridable by the tab section handlers. These are the must be specified functions
	// and so are pure.
	virtual CDlgResID GetPageID();				// Return section/page id system
	virtual	BOOL InitSection();					// Called when page first opened
	virtual BOOL CommitSection();				// Called when ok action is required
	virtual BOOL HandleMsg(DialogMsg* Msg);		// Called when messages arrive

	// The following are used to open the specific options tab 
	static UINT32 LayersTabNumber;				// Tab number assigned to the layers tab
	static UINT32 GuidesTabNumber;				// Tab number assigned to the guides tab

	virtual DialogTabOp * GetTabbedDlg(); 		 	// return pointer to the main dialog box
	
	static BOOL SetTabbedDlg(DialogTabOp * pDlg);	// return pointer to the main dialog box

protected:
	static DialogTabOp *pPropertiesDlg;		// pointer to the main dialog box

private:
	BOOL InitMessage;						// True if handling an init message
	BOOL ApplyNow; 							// True if Apply now should be ungreyed

	// The list of property tabs that is understood.
	static List LayerPropertyTabsList;		// list of available tabs
};

#endif  // INC_LAYERPROPERTYTABS


