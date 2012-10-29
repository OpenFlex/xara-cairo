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
#include "urldlg.h"

//#include "urlres.h"		//URL dialog resources
//#include "resimmap.h"	//URL import string resources


#include "xshelpid.h"	//For the help ID



CC_IMPLEMENT_DYNCREATE(URLImportDlg, DialogOp)

#define new CAM_DEBUG_NEW

// Set up the dialog box details stored as statics in the class
CDlgResID URLImportDlg::IDD = _R(IDD_URLIMPORT);
const CDlgMode URLImportDlg::Mode = MODAL;

BOOL URLImportDlg::DontHandleNextMessage = FALSE;
BOOL URLImportDlg::DialogWasCancelled = FALSE;

WebAddress URLImportDlg::ms_url = WebAddress();
	


/******************************************************************************************

>	BOOL URLImportDlg::OpenAndGetURL(WebAddress* purlToReturn) 


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

BOOL URLImportDlg::OpenAndGetURL(WebAddress* purlToReturn) 
{
	//Say that the dialog wasn't cancelled
	DialogWasCancelled=FALSE;

	//Find the dialog's op descriptor
	OpDescriptor *OpDesc = OpDescriptor::FindOpDescriptor(CC_RUNTIME_CLASS(URLImportDlg));

	//And start up the dialog
	if (OpDesc != NULL)
		OpDesc->Invoke();

	//And return the member variable
	*purlToReturn=URLImportDlg::ms_url;

	return !DialogWasCancelled;
}


/******************************************************************************************

>	URLImportDlg::URLImportDlg(): DialogOp(URLImportDlg::IDD, URLImportDlg::Mode) 


	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Default constructor
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

URLImportDlg::URLImportDlg(): DialogOp(URLImportDlg::IDD, URLImportDlg::Mode) 
{

}

/******************************************************************************************

>	MsgResult URLImportDlg::Message(CDlgMessage DlgMsg, CGadgetID Gadget) 


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

MsgResult URLImportDlg::Message(Msg* Message)
{	
	//If the message came from within our dialog 
	if (IS_OUR_DIALOG_MSG(Message))
	{
		//Then cast it into a dialog message and handle it
		DialogMsg* Msg = (DialogMsg*)Message;

		//If this flag gets set, we should close the dialog
		BOOL EndDialog = FALSE;

		//Now pass the message to a message handling function
		switch (Msg->DlgMsg)
		{
			case DIM_CREATE:
				OnCreate();
				break;

			case DIM_COMMIT:
				OnCommit();
				EndDialog=TRUE;
				break;

			case DIM_CANCEL:
				DialogWasCancelled=TRUE;
				EndDialog = TRUE;
				break;

			case DIM_LFT_BN_CLICKED:
				// A control on the dialog box has been clicked...
				if(Msg->GadgetID==_R(IDC_URLIMPORT_IMPORT))
				{
					OnCommit();
					EndDialog=TRUE;
				}
				break;


			case DIM_TEXT_CHANGED:
				// The user has typed in an edit field
				switch (Msg->GadgetID)
				{
					case _R(IDC_URLIMPORT_URL):
						if (URLImportDlg::DontHandleNextMessage)
							URLImportDlg::DontHandleNextMessage=FALSE;
						else
							OnURLChanged();
						break;
										
				}
				break;

 		}

		//And end the dialog if necessary
		if (EndDialog) 
		{
			Close();		
			End();			
		}
	}

	//Now pass the message down to the base class
	return DialogOp::Message(Message); 
}

/********************************************************************************************

	URLImportDlg message handling functions

	The following group of functions are called from URLImportDlg::Message
	when a message is received.

	They call other functions which do whatever needs to be done.

********************************************************************************************/


/********************************************************************************************

	void URLImportDlg::OnCreate()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	
	Purpose:	Handles a message that the dialog has just been created.

	Errors:		-
	SeeAlso:	URLImportDlg::Message()

********************************************************************************************/

void URLImportDlg::OnCreate()
{	
	//Put the keyboard focus in the edit field
	SetKeyboardFocus(_R(IDC_URLIMPORT_URL));
}

/********************************************************************************************

	void URLImportDlg::OnCommit()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	
	Purpose:	Handles a message that the "Import" button has been clicked

	Errors:		-
	SeeAlso:	URLImportDlg::Message()

********************************************************************************************/

void URLImportDlg::OnCommit()
{	
	//Get the string from the edit field
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


}

/********************************************************************************************

	void URLImportDlg::OnURLChanged()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	
	Purpose:	Handles a message that the user has typed in the "URL" field

	Errors:		-
	SeeAlso:	URLImportDlg::Message()

********************************************************************************************/

void URLImportDlg::OnURLChanged()
{	
	//Does nothing at present
	//We may need to handle this if we want the Import... button to be greyed
	//until the user types in the field
}


/******************************************************************************************

>	static OpState	URLImportDlg::GetState(String_256*, OpDescriptor*)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	URLImportDlg GetState method
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

OpState	URLImportDlg::GetState(String_256*, OpDescriptor*)
{    
	OpState OpSt;
	return(OpSt);
}




/******************************************************************************************

>	BOOL URLImportDlg::Init()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	URLImportDlg Init method
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

BOOL URLImportDlg::Init()
{
	BOOL InitOK;

	InitOK = RegisterOpDescriptor(
								0,					/* Tool ID */
								_R(IDS_URLIMPORT),
								CC_RUNTIME_CLASS(URLImportDlg),
								OPTOKEN_URLIMPORTDLG,
								GetState,
								_R(IDH_Command_Import_from_Web),	/* help ID */
								0,  				/* bubble help */
								0,					/* resource ID */
								0					/* control ID */
								);

	return (InitOK);
}


/******************************************************************************************

>	void URLImportDlg::Do(OpDescriptor*)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Creates then opens the dialog in response to a request from the user.
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

void URLImportDlg::Do(OpDescriptor*)
{
	BOOL ok;
	
	// Force the dialog box to be created, as it is modal it will be opened via a message
	ok = Create();

	if ( !ok )
	{
		// Could not create the dialog box so call inform error 
		InformError();
  		End(); 		
	}
}

/******************************************************************************************

>	void URLImportDlg::DoWithParam(OpDescriptor*)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Creates then opens the dialog in response to a request from the user and
				allows values to be passed in and returned to the caller via the
				URLImportDlgParam class.
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

void URLImportDlg::DoWithParam(OpDescriptor*, OpParam* Param)
{
	BOOL ok;
	
	// Force the dialog box to be created, as it is modal it will be opened via a message
	ok = Create();

	if ( !ok )
	{
		// Could not create the dialog box so call inform error 
		InformError();
  		End(); 		   // End the operation 
	}
}
