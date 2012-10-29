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

#include "camtypes.h" 
#include "davedlg.h"

//#include "bevres.h"		//URL dialog resources
//#include "resimmap.h"	//URL import string resources


#include "xshelpid.h"	//For the help ID

// includes for additions to the rendering tree
#include "lineattr.h"

#include "page.h"
#include "nodebmp.h"
#include "bitmpinf.h"
#include "bmpfiltr.h"

#include "grnddib.h"

#include "bmpexdoc.h"


#include "chapter.h"

#include "beveler.h"


//#include "justin3.h"

#include "mkshapes.h" 
#include "groupops.h"


CC_IMPLEMENT_DYNCREATE(DaveDlg, DialogOp)

#define new CAM_DEBUG_NEW

// Set up the dialog box details stored as statics in the class
CDlgResID DaveDlg::IDD = _R(IDD_DAVES_DLG);
const CDlgMode DaveDlg::Mode = MODELESS;

BOOL DaveDlg::DontHandleNextMessage = FALSE;
BOOL DaveDlg::DialogWasCancelled = FALSE;

WebAddress DaveDlg::ms_url = WebAddress();

/******************************************************************************************

>	BOOL DaveDlg::OpenAndGetURL(WebAddress* purlToReturn) 


	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/97
	Inputs:		-

	Outputs:	purlToReturn	Pointer to a Web Address object

	Returns:	TRUE - Import was pressed
				FALSE - Cancel was pressed
	Purpose:	Starts up the Import from Internet dialog box
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

BOOL DaveDlg::DoCreate() 
{
	return TRUE;
}


/******************************************************************************************

>	DaveDlg::DaveDlg(): DialogOp(DaveDlg::IDD, DaveDlg::Mode) 


	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Default constructor
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

DaveDlg::DaveDlg(): DialogOp(DaveDlg::IDD, DaveDlg::Mode) 
{
	m_Indent = 0;
	m_Contrast = 0;
	m_Angle = 0;
	m_Type = 0;
}

DaveDlg::~DaveDlg()
{
}

/******************************************************************************************

>	MsgResult DaveDlg::Message(CDlgMessage DlgMsg, CGadgetID Gadget) 


	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Handles all messages.

				This function simply maps the message to one of our message handling
				functions below.

	Errors:		-
	SeeAlso:	-

******************************************************************************************/

MsgResult DaveDlg::Message(Msg* Message)
{	
	return DialogOp::Message(Message); 
}

/********************************************************************************************

	DaveDlg message handling functions

	The following group of functions are called from DaveDlg::Message
	when a message is received.

	They call other functions which do whatever needs to be done.

********************************************************************************************/


/********************************************************************************************

	void DaveDlg::OnCreate()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	
	Purpose:	Handles a message that the dialog has just been created.

	Errors:		-
	SeeAlso:	DaveDlg::Message()

********************************************************************************************/

void DaveDlg::OnCreate()
{	
	//Put the keyboard focus in the edit field
	// SetKeyboardFocus(_R(IDC_DAVE_LW_EDIT));
}

/********************************************************************************************

	void DaveDlg::OnCommit()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	
	Purpose:	Handles a message that the "Import" button has been clicked

	Errors:		-
	SeeAlso:	DaveDlg::Message()

********************************************************************************************/

void DaveDlg::OnCommit()
{	
	//Get the string from the edit field
	/*
	String_256 strUser=GetStringGadgetValue(_R(IDC_URLIMPORT_URL));

	//Now we want to correct this string. To do this we
	//need to set up some correction flags
	WebCorrectFlags wcfToUse;
	wcfToUse.SetForURLImport();

	//Now make a Web Address object out of the string
	//This will correct the string appropriately
	WebAddress urlToFetch(strUser, wcfToUse);

	//And set our member variable
	ms_url=urlToFetch;
	*/


}

/********************************************************************************************

	void DaveDlg::OnURLChanged()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	
	Purpose:	Handles a message that the user has typed in the "URL" field

	Errors:		-
	SeeAlso:	DaveDlg::Message()

********************************************************************************************/

void DaveDlg::OnURLChanged()
{	
	//Does nothing at present
	//We may need to handle this if we want the Import... button to be greyed
	//until the user types in the field
}


/******************************************************************************************

>	static OpState	DaveDlg::GetState(String_256*, OpDescriptor*)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	DaveDlg GetState method
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

OpState	DaveDlg::GetState(String_256*, OpDescriptor*)
{    
	OpState OpSt;
	return(OpSt);
}




/******************************************************************************************

>	BOOL DaveDlg::Init()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	DaveDlg Init method
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

BOOL DaveDlg::Init()
{
	BOOL InitOK;

	InitOK = RegisterOpDescriptor(
								0,					/* Tool ID */
								_R(IDS_DAVEDLG),
								CC_RUNTIME_CLASS(DaveDlg),
								OPTOKEN_DAVEDLG,
								GetState,
								_R(IDH_Command_Import_from_Web),	/* help ID */
								0,  				/* bubble help */
								0,					/* resource ID */
								0					/* control ID */
								);

	return (InitOK);
}


/******************************************************************************************

>	void DaveDlg::Do(OpDescriptor*)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Creates then opens the dialog in response to a request from the user.
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

void DaveDlg::Do(OpDescriptor*)
{
	
}

/******************************************************************************************

>	void DaveDlg::DoWithParam(OpDescriptor*)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Creates then opens the dialog in response to a request from the user and
				allows values to be passed in and returned to the caller via the
				DaveDlgParam class.
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

void DaveDlg::DoWithParam(OpDescriptor*, OpParam* Param)
{
	
}

/******************************************************************************************

>	void DaveDlg::DoChangeInValue()

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/12/98
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Changes the attribute value/s
	Errors:		-
	SeeAlso:	-

******************************************************************************************/


void DaveDlg::DoChangeInValue()
{
}

BOOL DaveDlg::DoBevel()
{
	return TRUE;
}

BOOL DaveDlg::RemoveBevel()
{
	return TRUE;
}

void DaveDlg::UpdateControls()
{
}


