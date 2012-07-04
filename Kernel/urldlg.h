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
//	URL dialog
// 

#ifndef INC_URLIMPORTDLG
#define INC_URLIMPORTDLG

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "webaddr.h"

/********************************************************************************************

>	class URLImportDlg : public DialogOp

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/3/97
	Purpose:	The "Import from URL..." dialog

********************************************************************************************/

#define OPTOKEN_URLIMPORTDLG _T("URLImportDlg")

class URLImportDlg : public DialogOp
{
	CC_DECLARE_DYNCREATE(URLImportDlg)

	//Constructors
public:
	URLImportDlg();

	//Initialiser
public:
	static BOOL Init();

	//Function to start the dialog
public:
	static BOOL OpenAndGetURL(WebAddress* purlToReturn);
	
	//Message handling functions
protected:
	void OnCreate();
	void OnCommit();

	void OnURLChanged();
	
	//Overridden virtual functions
public:
	void DoWithParam(OpDescriptor*, OpParam* Param); 
	void Do(OpDescriptor*); 						
						  	
	static OpState GetState(String_256*, OpDescriptor*);
													
	virtual MsgResult Message(Msg* Message);		

	//Member variables
protected:
	static WebAddress ms_url;

	static BOOL DialogWasCancelled;
	static BOOL DontHandleNextMessage;

	
	//Compulsory static member variables
public:
	static CDlgResID IDD;		
	static const CDlgMode Mode;

};

#endif
