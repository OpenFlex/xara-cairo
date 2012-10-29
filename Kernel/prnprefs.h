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
// Header file for PrnPrefs.cpp
//
// 

//	WEBSTER-ranbirr-13/11/96
#ifndef WEBSTER

#ifndef INC_PRINTPREFS
#define INC_PRINTPREFS


/********************************************************************************************

>	class PrintPrefsDlg : public DialogTabOp

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	12/4/95
	Purpose:	The print preference's dialog box.

				Allows the user to set options like:-
				
				Uses the OptionsTabs class declared in AppPrefsDlg and
				any print options pages which have been declared to the
				options tabs list. The application options uses the same system.

	SeeAlso:	AppPrefsDlg; OptionsTabs;
	
********************************************************************************************/
#define OPTOKEN_PRINTOPTIONS	_T("PrintOptions")

class PrintPrefsDlg : public DialogTabOp
{
	CC_DECLARE_DYNCREATE( PrintPrefsDlg )

public:
	PrintPrefsDlg();									// constructor
	PrintPrefsDlg(INT32 StartingPage);					// constructor
	~PrintPrefsDlg();									// ~destructor

	void Do(OpDescriptor*);								// "Do" function

	static BOOL Init();								// Setup function
	static void Deinit();							// Remove function

	// No create function as this is handled by the main tab dialog code

	static OpState GetState(String_256*, OpDescriptor*);
													// Return the state of this operation
	virtual MsgResult Message(Msg* Message);		// Message handler
	virtual BOOL RegisterYourPagesInOrderPlease();	// Add in tab pages
	
	static BOOL InvokeDialog();						// Calls the DoWithParam

	static void SetCurrentDlg(PrintPrefsDlg* pDlg);	// Access to the current open dlg
	static void CloseCurrentDlg();					// Forces the dlg to close

	BOOL HasImages() {return TRUE;}
	TabType GetTabType() {return TABTYPE_TREE/*TABTYPE_LIST*/;}

private:
	// Set up explicit details about this dialog box such as the id and type
	static const CDlgResID IDD;				// Dialog box id
	static const CDlgMode Mode;				// Dialog box mode of operation (mode or modeless)

	// Functions to commit the values on the dialog box and its sections on ok
	BOOL CommitDialogValues();

	String_256 TitleString;					// title of dialog box

	// Parameter passing variables
	static BOOL				OkUsed;					// remember whether ok or cancel used		
	static BOOL				Open;					// Are we open?
	static PrintPrefsDlg*	pCurrentDlg;			// ptr to current print pref dlg that's open
};

/********************************************************************************************

>	class PrintTabPrintPrefsDlg : public PrintPrefsDlg

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	13/2/96
	Purpose:	To open up the print preference's dialog box with the print tab
				selected. This is used by the units button on the tool bars.

	SeeAlso:	AppPrefsDlg; OptionsTabs; PrintPrefsDlg;
	
********************************************************************************************/

class PrintTabPrintPrefsDlg : public PrintPrefsDlg
{
// Defines the OPTOKEN_PRINTOPTIONSDLG as this now links to the units tab in
// this document options dialog box.
#define OPTOKEN_PRINTOPTIONSDLG	_T("PrintOptionsDlg")

	CC_DECLARE_DYNCREATE( PrintTabPrintPrefsDlg )

public:
	PrintTabPrintPrefsDlg();					// constructor

	// All other functionality comes from the PrintPrefsDlg class.
};

#endif  // INC_PRINTPREFS

#endif //webster
