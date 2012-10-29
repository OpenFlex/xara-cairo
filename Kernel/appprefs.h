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

#ifndef INC_APPPREFS
#define INC_APPPREFS

//#include "prefsdlg.h"
#include "pagesize.h"	// page sizes
//#include "nev.h"		// _R(IDN_APPLICATIONOPTS)

/********************************************************************************************

>	class AppPrefsDlg : public DialogTabOp

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	23/08/94
	Purpose:	The application preference's dialog box
	
				Allows the user to set options like:-
					Nudge distance, constraint angle, Duplicate distance x,y
					Page sizes in document
					Document units
					Colour bar display mode

				Uses the OptionsTabs class which is declared and initialised by this class.
				This uses any application options pages which have been declared to the
				options tabs list. The document options uses the same system.
				Also, declares the PageSizes class to the system so that they are available
				to all options tabs.

	SeeAlso:	DocPrefsDlg; OptionsTabs; PageSize; PageSizesList;
				
********************************************************************************************/
#define OPTOKEN_UTILOPTIONS	_T("UtilOptions")
//#define OPTOKEN_APPPREFSDLG "AppPrefsDlg"

class AppPrefsDlg : public DialogTabOp
{
	CC_DECLARE_DYNCREATE( AppPrefsDlg )

public:
	AppPrefsDlg();									// constructor
	AppPrefsDlg(INT32 StartingPage);					// constructor
	~AppPrefsDlg();									// destructor

	void Do(OpDescriptor*);							// "Do" function

	static BOOL Init();								// Setup function
	static void Deinit();							// Remove function

	// No create function as this is handled by the main tab dialog code

	static OpState GetState(String_256*, OpDescriptor*);
													// Return the state of this operation
	virtual MsgResult Message(Msg* Message);		// Message handler
	virtual BOOL RegisterYourPagesInOrderPlease();	// Add in tab pages
	
	// Set up explicit details about this dialog box such as id, type (MODE or MODELESS)
	static const CDlgResID IDD;				// Dialog box id
	static const CDlgMode Mode;				// Dialog box mode of operation (mode or modeless)

	// Function to allow the application exiting code to work out if save preferences
	// on exit option is set.
	static BOOL IsSaveOnExitSet();			// Returns state of save on exit flag
	static BOOL SetSaveOnExit(BOOL NewState);// Allows new state of save on exit flag to be set

	static PageSizesList *pPageSizesList;	// List of available page sizes

	// Functions to commit the values on the dialog box and its sections on ok
	BOOL CommitDialogValues();

	BOOL HasImages() {return TRUE;}
	TabType GetTabType() {return TABTYPE_TREE/*TABTYPE_LIST*/;}

private:
	String_256 TitleString;					// title of dialog box
};


/********************************************************************************************

>	class UnitsTabAppPrefsDlg : public DialogTabOp

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	14/12/94
	Purpose:	To open up the document preference's dialog box with the units tab
				selected. This is used by the units button on the tool bars.

	SeeAlso:	AppPrefsDlg; OptionsTabs; PageSize; PageSizesList;
	
********************************************************************************************/

class UnitsTabAppPrefsDlg : public AppPrefsDlg
{
// Defines the OPTOKEN_UNITDLG as this now links to the units tab in
// this document options dialog box.
#define OPTOKEN_UNITDLG	_T("UnitSetupDlg")

	CC_DECLARE_DYNCREATE( UnitsTabAppPrefsDlg )

public:
	UnitsTabAppPrefsDlg();					// constructor

	// All other functionality comes from the DocPrefsDlg class.
};

/********************************************************************************************

>	class ScaleTabDocPrefsDlg : public AppPrefsDlg 

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	14/12/94
	Purpose:	To open up the application preference's dialog box with the scale tab
				selected. This is used by the scale button on the tool bars.

	SeeAlso:	AppPrefsDlg; OptionsTabs; PageSize; PageSizesList;
	
********************************************************************************************/

class ScaleTabAppPrefsDlg : public AppPrefsDlg
{
// Defines the OPTOKEN_UNITDLG as this now links to the units tab in
// this document options dialog box.
#define OPTOKEN_SCALEDLG _T("ScaleFactorDlg")

	CC_DECLARE_DYNCREATE( ScaleTabAppPrefsDlg )

public:
	ScaleTabAppPrefsDlg();					// constructor

	// All other functionality comes from the AppPrefsDlg class.
};

/********************************************************************************************

>	class PageTabDocPrefsDlg : public AppPrefsDlg 

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	12/4/95
	Purpose:	To open up the application preference's dialog box with the page tab
				selected. This is used by the pop up menu when on the page.

	SeeAlso:	AppPrefsDlg; OptionsTabs; PageSize; PageSizesList;
	
********************************************************************************************/

class PageTabAppPrefsDlg : public AppPrefsDlg
{
// Defines the OPTOKEN_UNITDLG as this now links to the units tab in
// this document options dialog box.
#define OPTOKEN_PAGESIZEDLG _T("PageSetupDlg")

	CC_DECLARE_DYNCREATE( PageTabAppPrefsDlg )

public:
	PageTabAppPrefsDlg();					// constructor

	// All other functionality comes from the AppPrefsDlg class.
};

/********************************************************************************************

>	class GridTabDocPrefsDlg : public AppPrefsDlg 

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	5/10/95
	Purpose:	To open up the application preference's dialog box with the grid tab
				selected. This is used by the pop up menu when on the ruler.

	SeeAlso:	AppPrefsDlg; OptionsTabs; PageSize; PageSizesList;
	
********************************************************************************************/

class GridTabAppPrefsDlg : public AppPrefsDlg
{
// Defines the OPTOKEN_GRIDANDRULERSDLG as this now links to the units tab in
// this document options dialog box.
#define OPTOKEN_GRIDANDRULERSDLG _T("GridRulersDlg")

	CC_DECLARE_DYNCREATE( GridTabAppPrefsDlg )

public:
	GridTabAppPrefsDlg();					// constructor

	// All other functionality comes from the AppPrefsDlg class.
};

/********************************************************************************************

>	class PlugsTabAppPrefsDlg : public AppPrefsDlg

	Author:		Priestley (Xara Group Ltd) <camelotdev@xara.com> - from Neville's UnitsTabAppPrefsDlg class (above)
	Created:	13/09/2000
	Purpose:	To open up the document preference's dialog box with the plug-ins tab
				selected. This is used by the plug-ins menu item (under 'Bitmap Effects & Plug-Ins').

	SeeAlso:	AppPrefsDlg; OptionsTabs; PageSize; PageSizesList;
	
********************************************************************************************/

class PlugsTabAppPrefsDlg : public AppPrefsDlg
{
// Defines the OPTOKEN_UNITDLG as this now links to the units tab in
// this document options dialog box.
#define OPTOKEN_PLUGSDLG	_T("PlugSetupDlg")

	CC_DECLARE_DYNCREATE( PlugsTabAppPrefsDlg )

public:
	PlugsTabAppPrefsDlg();					// constructor

	// All other functionality comes from the DocPrefsDlg class.
};


/********************************************************************************************

>	class OptionsTabs : public ListItem

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	07/12/94
	Purpose:	These encompass all the tabs available for the options dialog box to use.

********************************************************************************************/
class CCAPI OptionsTabs : public ListItem
{
	CC_DECLARE_DYNAMIC(OptionsTabs);

public:
	OptionsTabs();							// Constructor

	static BOOL InitOptionsTabs();			// set up all option tabs available
	static BOOL DeinitOptionsTabs();		// remove all option tabs available
	static OptionsTabs *GetFirst();
	static OptionsTabs *GetNext(OptionsTabs*);

	virtual BOOL Init();					// Initialisation

	// Function to declare a tab/section to the options system
	BOOL DeclareOptionsTab(OptionsTabs *pOptionsTab);

	// Overridable by the tab section handlers
	virtual CDlgResID GetPageID()			=0;	// Return section/page id system
	virtual	BOOL InitSection()				=0;	// Called when page first opened
	virtual BOOL CommitSection()			=0;	// Called when ok action is required
	virtual BOOL HandleMsg(DialogMsg* Msg)	=0;	// Called when DIALOG messages arrive

	virtual MsgResult Message(Msg *pMessage);	// Called when ANY unhandled messages arrive
												// (see below for special message upcalls)

	// Some special handlers for things like new default units being specified or the last
	// document being closed.
	// These are the virtual handlers which each tab should specify, if not required then
	// these base class definitions can be used.
	virtual BOOL NewUnitsInSection();		// Called when new default units chosen
	virtual BOOL GreySection();				// Called when the user has closed all documents
	virtual BOOL UngreySection();			// Called when the user has opened a document
	virtual BOOL UpdateSection(String_256 *DocumentName);	// Called when the user has switched to a new document

	// Some functions to determine whether this is a Document or Program option
	virtual BOOL IsDocumentOption()			=0;	// Return True if document option  
	virtual BOOL IsProgramOption()			=0;	// Return True if program option
	virtual BOOL IsPrintingOption();			// Return True if printing option

	static DialogTabOp *pPrefsDlg;			// pointer to the main dialog box

	static BOOL SetUpDocUnits();			// function to set up CurrentPageUnits

	static BOOL GetApplyNowState();			// Get current state of ApplyNow flag
	static BOOL SetApplyNowState(BOOL NewState);	// set new state for ApplyNow 
	static BOOL GreyApplyNow();				// grey the apply now button
	static BOOL UngreyApplyNow();			// grey the apply now button

	static BOOL SetInitMessageState(BOOL NewState);	// set new state of InitMessage
	static BOOL GetInitMessageState();		// get current state of InitMessage

	// The following are used to open the specific options tab
	// These are the main application/document based options dialog box
	static UINT32 UnitsAppTabNumber;			// Tab number assigned to the units tab
	static UINT32 ScaleAppTabNumber;			// Tab number assigned to the scale tab
	static UINT32 PageAppTabNumber;			// Tab number assigned to the page tab
	static UINT32 GridAppTabNumber;			// Tab number assigned to the grid and rulers tab

	static UINT32 PlugsAppTabNumber;			// Tab number assigned to the plug-ins tab

	// These are the print options dialog box
	static UINT32 PrintTabNumber;				// Tab number assigned to print tab in print options term 	

	static Document	*pScopeDocument;		// current document (for message broadcasts) 

	static String_256 *GetDocumentName();	// returns the name of the selected document
	static void SetDocumentName(Document *pDoc);	// reads the current name of the selected document
											// and stores this in the class variable
	static void SetDocumentName(String_256 *DocumentName);	// sets the name of the selected document

	static void SetCurrentDocAndSpread(Document *pDoc);	// set up the spread that we are currently workign on
	static void SetDefaultUnits();	  		// set up our default display units

	virtual BOOL PageSizeHasChanged();		// sent when the page size has been changed

protected:
	// Allow the options tabs access but nobody else to these useful variables
	static Document *pDocument;				// The document we are working on
	static Spread   *pSpread; 				// The spread we are working on 

	static UnitType CurrentPageUnits;		// The units used to display page measurements
	static UnitType CurrentScaledUnits;		// The units to display scaled measurements
	static UnitType CurrentFontUnits;		// The units used to display font measurements

private:
	static BOOL InitMessage;				// True if handling an init message
	static BOOL ApplyNow;					// True if Apply now should be ungreyed

	// The list of options tabs that is understood.
	static List OptionsTabsList;			// list of available tabs

	static String_256 DocName;				// name of current document
};

#endif  // INC_APPPREFS


