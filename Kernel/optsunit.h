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

// Header for the handling code for the unit setup tab of the options dialog box 

#ifndef INC_OPTSUNITS
#define INC_OPTSUNITS

//#include "unittype.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "units.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "appprefs.h"
#include "radio.h"

class ScaleUnit;
/********************************************************************************************

>	class UnitsTab: public OptionsTabs

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/12/94
	Purpose:	Allows the user to define the default units that are used for displaying size
				information, font size information and general display information.
				Also, alllows them to define their own units and edit the scaling factor
				applied to the spread, layer, or whatever.
				Based on the old UnitsDlg code.				
	SeeAlso:	UnitsDlg;
	SeeAlso:	OptionsTabs; AppPrefsDlg; DocPrefsDlg;

********************************************************************************************/

class UnitsTab: public OptionsTabs
{         
	CC_DECLARE_DYNCREATE( UnitsTab )  
public:
//WEBSTER-ranbirr-13/11/96
#ifndef WEBSTER

	UnitsTab();
	~UnitsTab();

	virtual BOOL Init();                        

	// Function to handle the messages for this tab/pane window
	virtual BOOL HandleMsg(DialogMsg* Msg);

	// Function to set up the values on this tab when being opened
	virtual BOOL InitSection();

	// Function to commit the values on this tab on ok
	virtual BOOL CommitSection();

	// Functions to handle document changing messages
	virtual BOOL GreySection();			// Called when the user has closed all documents
	virtual BOOL UngreySection();		// Called when the user has opened a document
	BOOL ChangeControlStatus(const BOOL Status); // used to grey/ungrey all controls
	virtual BOOL UpdateSection(String_256 *DocumentName);	// Called when the user has switched to a new document

	virtual CDlgResID GetPageID();		// Return section/page id system

	virtual BOOL IsDocumentOption();	// Return True if document option  

	virtual BOOL IsProgramOption();		// Return True if program option
#endif //webster
	static	ScaleUnit*		GetColourUnitPreference();
//WEBSTER-ranbirr-13/11/96
#ifndef WEBSTER
protected:
	// Lots of controlling and handling functions specific to this section
	BOOL CommitDialogValues();

	BOOL SelectCurrentUserUnit();

	BOOL InitControls();
	BOOL InitUnitListControls();

	BOOL EnableControls();

	void SetUnitToken(CGadgetID ID,UnitType ThisUnitType,INT32 Index = -1,BOOL EndOfList=FALSE);
	void ShowUnitDetails(CGadgetID ID,UnitType ThisUnitType,INT32 Index = -1,BOOL EndOfList=FALSE);

	BOOL UpdateUnitListControls();

	BOOL CreateNewUnit();
	BOOL DeleteUnit();
	BOOL ShowUnitProperties();

// Colour Unit data members...	
	ScaleUnit*		m_pOldColourUnit;	// default colour unit on entry to dialog

	RadioGroup		m_ColourUnitRadioGroup;

private:
	DocUnitList* pDocUnitList;
	UnitType 	 CurrentUserUnitType;

	BOOL GreyStatus;			// Remember the state that we are currently in

	// Remember the entry default units states
	UnitType OldPageUnits;		// The units used to display page measurements
	//UnitType OldScaledUnits;	// The units to display scaled measurements
	UnitType OldFontUnits;		// The units to display font measurements
#endif //webster
}; 


/********************************************************************************************

>	class UnitPropertiesDlg: public DialogOp

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/11/95
	Purpose:	Allows the user to define the properties of a user unit. This includes such 
				details as:-
					the name
					the abbreviation
					what units it is based on
					the scaling for the base unit to this unit
					prefix or suffix unit

	SeeAlso:	UnitsDlg;
	SeeAlso:	OptionsTabs; AppPrefsDlg; UnitsTab

********************************************************************************************/
#define OPTOKEN_UNITPROPERTIESDLG _T("UnitPropertiesDlg")

class UnitPropertiesDlg : public DialogOp
{         
	CC_DECLARE_DYNCREATE( UnitPropertiesDlg )  
public:
	UnitPropertiesDlg();					// constructor

	void DoWithParam(OpDescriptor*, OpParam* pOpParam); // "DoWithParam" function
	void Do(OpDescriptor*); 				// "Do" function

	static BOOL Init();						// Setup function
	BOOL Create();							// Create this dialog
	static OpState GetState(String_256*, OpDescriptor*);
											// Return the state of this operation
	virtual MsgResult Message(Msg* Message);
											// Message handler
	
	// Set up explicit details about this dialog box such as the id and type
	static CDlgResID IDD;					// Dialog box id
	static const CDlgMode Mode;				// Dialog box mode of operation (mode or modeless)

public:
	static BOOL InvokeDialog(UnitType CurrentUserUnitType);

private:
	BOOL InitDialog();						// Standard set up function
	BOOL CommitDialogValues();				// Standard commit function

	UnitType 	 CurrentUserUnitType;		// Current unit being edited
	DocUnitList* pDocUnitList;				// Pointer to the current document unit list
	BOOL* pIsOk;							// Pointer to the return state BOOLean

	void SetUnitToken(CGadgetID ID,UnitType ThisUnitType,INT32 Index = -1,BOOL EndOfList=FALSE);
	BOOL DisplayUserUnitDetails();			// Show the details on the current user unit
}; 

#endif // INC_OPTSUNITS
