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
// Header file for ToolDlg.CPP
//
// This file implements the dialog box that allows the user to configure which
// toolbars are shown around the edges of the main frame window.

#ifndef INC_TOOLDLG
#define INC_TOOLDLG

//#include "dialogop.h"
//#include "bars.h"
//#include "resource.h"
//#include "mario.h"

/******************************************************************************************

>	class ToolbarDlg: public DialogOp

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/03/94
	Purpose:	The Toolbars... dialog allows a user to 

				View all defined toolbars
				Create a new toolbar
				Delete a toolbar
				Make docking bars show large or small buttons
				
				
******************************************************************************************/

#define OPTOKEN_TOOLBARDLG _T("ToolbarDlg")

class ToolbarDlg: public DialogOp
{
	CC_DECLARE_DYNCREATE( ToolbarDlg )

public:
	ToolbarDlg();  						// Constructor 
	~ToolbarDlg();
	void Do(OpDescriptor*);				// "Do" function
	static BOOL Init();         		// Setup function
	BOOL Create();						// Create this dialog
	static OpState GetState(String_256*, OpDescriptor*);
										// Return the state of this operation
	virtual MsgResult Message(Msg* Message);
										// Message handler
	void ShowToolbarList(); 			// Reflect the current state of bars in the dialog
	void ShowToolbarSizes(); 			// Reflect the current state of bars in the dialog

	static ToolbarDlg* GetToolbarDlg();		// Get pointer to current toolbar dialog

// Public data members...
	static const INT32 IDD;
	static const CDlgMode Mode;			// ?

private:
	BOOL InitDialog(); 					// Standard setup function
	void DeleteSelectedBar();
	void TakeToolbarDetails();			// Set the current state of bars from the dialog
	void NewToolbar();					// Create a new toolbar and set it up

	void GetSelectedBarName(String_32 *Result);	// Get Name of selected bar

private:
	static ToolbarDlg* CurrentToolbarDlg;	// Pointer to current ToolbarDlg
	static String_16 InfoBarName;		// Internationalised name of infobar
	static String_16 ControlBankName;		// Internationalised name of ControlBank
	BOOL CanDeleteSelection();
};




/******************************************************************************************

>	class ToolnameDlg: public DialogOp

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/04/94
	Purpose:	The "New toolbar" dialog allows a user to 
				Create a new, named toolbar
				
				
******************************************************************************************/

#define OPTOKEN_TOOLBARNAMEDLG _T("ToolbarNameDlg")

class ToolnameDlg: public DialogOp
{
	CC_DECLARE_DYNCREATE( ToolnameDlg )

public:
	ToolnameDlg();					// Constructor 

	void Do(OpDescriptor*);			// "Do" function
	static BOOL Init();         	// Setup function
	BOOL Create();					// Create this dialog
	static OpState GetState(String_256*, OpDescriptor*);
									// Return the state of this operation
	virtual MsgResult Message(Msg* Message);
									// Message handler

// Public data members...
	static const INT32 IDD;
	static const CDlgMode Mode;		// ?
	
private:
	BOOL InitDialog(); 				// Standard setup function

//	DialogOp*	pToolbarDlg;

};




/******************************************************************************************

>	class CustomizeBarDlg: public DialogOp

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/04/94
	Purpose:	The "Customize toolbar" dialog allows a user to 
				Edit the controls on a toolbar
				
				
******************************************************************************************/

#define OPTOKEN_CUSTOMIZEBARDLG _T("ToolbarNameDlg")

class CustomizeBarDlg: public DialogOp
{
	CC_DECLARE_DYNCREATE( CustomizeBarDlg )

public:
	CustomizeBarDlg();			  	// Constructor 

	void Do(OpDescriptor*);			// "Do" function
	static BOOL Init();         	// Setup function
	BOOL Create();					// Create this dialog
	static OpState GetState(String_256*, OpDescriptor*);
									// Return the state of this operation
	virtual MsgResult Message(Msg* Message);
									// Message handler

// Public data members...
	static const INT32 IDD;
	static const CDlgMode Mode;		// ?
	
private:
	BOOL InitDialog(); 				// Standard setup function

	void	ShowOpsList();

};




#endif // INC_TOOLDLG
