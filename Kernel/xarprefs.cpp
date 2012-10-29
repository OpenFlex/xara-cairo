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


/*
*/

//
// This file implements the dialogue box that allows the user to set the export native file
// preferences.

#include "camtypes.h"
#include "page.h"
#include "layer.h"

#include "webparam.h"
//#include "xardlg.h"
#include "xarprefs.h"
//#include "filtrres.h"	// _R(IDS_NativePrefsDlg)

//#include "resource.h"

#include "dlgmgr.h"		// Dialogue manager class
 	 
// This is not compulsory, but you may as well put it in so that the correct version
// of your file can be registered in the .exe

// An implement to match the Declare in the .h file.
CC_IMPLEMENT_DYNCREATE ( NativePrefsDlg, DialogOp )

// This is necessary to persuade the compiler that we are calling the correct constructor.
const CDlgResID NativeID = _R(IDD_EXPORTNATIVEOPTS);

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW

/******************************************************************************************

>	NativePrefsDlg::NativePrefsDlg() : DialogOp ( _R(IDD_EXPORTNATIVEOPTS), MODAL )

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	NativePrefsDlg constructor. Creates a non-undoable operation
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

NativePrefsDlg::NativePrefsDlg () : DialogOp ( NativeID, MODAL )
{
	// The base class does all the work.
}

/******************************************************************************************

>	NativePrefsDlg::~NativePrefsDlg()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/03/2006
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	NativePrefsDlg destructor.
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

NativePrefsDlg::~NativePrefsDlg ()
{
	// The base class does all the work.
}

/******************************************************************************************

>	NativePrefsDlg::NativePrefsDlg ( CDlgResID IDD )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/10/00
	Inputs:		IDD	- The ID of the dialogue being created.
	Purpose:	NativePrefsDlg constructor. Creates a non-undoable operation

******************************************************************************************/

NativePrefsDlg::NativePrefsDlg ( CDlgResID IDD ) : DialogOp ( IDD, MODAL )
{
	// The base class does all the work.
}

/******************************************************************************************

>	void NativePrefsDlg::DoWithParam(OpDescriptor*)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Creates then opens the dialog in response to a request from the user and
				allows values to be passed in and returned to the caller via the
				WebPrefsDlgParam class.
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

void NativePrefsDlg::DoWithParam(OpDescriptor*, OpParam* Param)
{
	ERROR3IF(Param == NULL, "NativePrefsDlg::DoWithParam - NULL Param passed in");

	// Use the OpParam that has been passed in to us
	mpParams = (WebPrefsDlgParam *) Param;

	// Call the Do function to finish the job off.
	Do ( NULL );
}

/******************************************************************************************

>	void NativePrefsDlg::Do(OpDescriptor*)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Creates then opens the dialog in response to a request from the user.
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

void NativePrefsDlg::Do ( OpDescriptor* )
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
/******************************************************************************************

>	BOOL NativePrefsDlg::Init()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	NativePrefsDlg Init method
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

BOOL NativePrefsDlg::Init()
{
	BOOL InitOK;

	InitOK = RegisterOpDescriptor(
								0,					/* Tool ID */
								_R(IDS_NATIVEPREFSDLG),
								CC_RUNTIME_CLASS ( NativePrefsDlg ),
								OPTOKEN_NATIVEPREFSDLG,
								GetState,
								0,					/* help ID */
								0,  				/* bubble help */
								0,					/* resource ID */
								0					/* control ID */
								);

	return (InitOK);
}

/********************************************************************************************

>	BOOL NativePrefsDlg::Create()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/96
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if successful, else FALSE
	Purpose:	NativePrefsDlg create method 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
	   
BOOL NativePrefsDlg::Create ()
{                     
	// Pass the responsibility to the baseclass.
	return DialogOp::Create ();
}

/******************************************************************************************

>	static OpState	NativePrefsDlg::GetState(String_256*, OpDescriptor*)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	NativePrefsDlg GetState method
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

OpState	NativePrefsDlg::GetState(String_256*, OpDescriptor*)
{    
	OpState OpSt;
	return(OpSt);
}

/******************************************************************************************

>	MsgResult NativePrefsDlg::Message(CDlgMessage DlgMsg, CGadgetID Gadget) 

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/96
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Handles all the web preferences dialog's messages
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

MsgResult NativePrefsDlg::Message(Msg* Message)
{
	if (IS_OUR_DIALOG_MSG(Message) && mpParams)
	{
		DialogMsg* Msg = (DialogMsg*)Message;

		MsgResult Result;

		// Should now handle the required messages that we respond to
		switch (Msg->DlgMsg)
		{
			case DIM_CREATE:
				{
					InitDialog();
				}
			break;

			case DIM_COMMIT:
				{
					// (ok) accept all changes that the user has made to the settings
					// brackets make the ok local to this case 
					BOOL ok;
					ok = CommitDialogValues ();
					if (ok)
					{
						// Values found ok so quit dialogue then go ahead and export
						if ( mpParams != NULL )
						{
							mpParams->SetWebOk( TRUE );	// Flag ok used.
						}
						else
						{
							ERROR3 ( "mpParams is not set!" );
						}

					}
				}
			break;

			case DIM_CANCEL:
				// Cancel all changes that the user has made to the settings
				if ( mpParams != NULL )
				{
					mpParams->SetWebOk(FALSE);			// Flag cancel used
				}
				else
				{
					ERROR3 ( "mpParams is not set!" );
				}

			break;

			default:
				break;
		}

		// Allow the base class access to the message, it will do the
		// DLG_EAT_IF_HUNGRY(Msg) for us
		// Must do this before the Close and End
		Result = DialogOp::Message ( Message );

		// The message was for our dialog box so return that we have handled it, if necessary
		return Result;
	}

	return DialogOp::Message(Message); 
}

/******************************************************************************************

>	SelectionType NativePrefsDlg::GetExportSelection ( UINT32 ControlID )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/10/00
	Inputs:		ControlID		- The ID number of the control being examined.
	Returns:	SelectionType	- (DRAWING or SELECTION) Whether to export the entire
								  drawing, or just the selected parts.
	Purpose:	Works out what the current export selection state is.

******************************************************************************************/

SelectionType NativePrefsDlg::GetExportSelection ( UINT32 ControlID )
{
	// If the dialogue box has had the "Drawing" selection chosen, this function will
	// return TRUE, which, in turn, will cause this method to return DRAWING.
	BOOL IsValid = FALSE;

	if ( GetLongGadgetValue ( ControlID, 0, 1, 0, &IsValid ) )
	{
		return DRAWING;
	}
	else
	{
		return SELECTION;
	}
}	

/******************************************************************************************

>	BOOL NativePrefsDlg::CommitDialogValues ()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/96
	Inputs:		pointer to the dialogue box
	Outputs:	-
	Returns:	True if values in dialog box ok, False otherwise.	  
	Purpose:	Takes the values in the dialog box and sets the return values accordingly
				Called when ok is pressed on the dialog box.
	Errors:		-
	SeeAlso:	NativePrefsDlg::CommitDialogValues;

******************************************************************************************/

BOOL NativePrefsDlg::CommitDialogValues ()
{
	ERROR2IF(mpParams == NULL, FALSE, "NativePrefsDlg::CommitDialogValues called after duff initialisation?!");

	// What export selection has been made?
	mpParams->SetExportSel ( GetExportSelection ( _R(IDC_NATIVEOPTS_DRAWING) ) );  

	return TRUE;
}

/******************************************************************************************

>	BOOL NativePrefsDlg::InitDialog(NativePrefsDlg* pWebPrefs)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/96
	Inputs:		pointer to the dialog box
	Outputs:	-
	Returns:	TRUE if successful, else FALSE
	Purpose:	Sets initial dialog values 
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

BOOL NativePrefsDlg::InitDialog ()
{
	ERROR2IF ( mpParams == NULL, FALSE,
			   "NativePrefsDlg::InitDialog called after duff initialisation?!" );

	//First, do we have a selection?
	Application *pApp = GetApplication();

	ERROR2IF(pApp == NULL, FALSE,"NativePrefsDlg::InitDialog -  no application!");
	
	SelRange *pRange = pApp->FindSelection();
	
	ERROR2IF(pRange == NULL, FALSE,"NativePrefsDlg::InitDialog - no selection range!");
	DocRect ClipRect = pRange->GetBoundingRect();

	BOOL fThereIsASelection=!ClipRect.IsEmpty();

	//Now, is there a selection?
	if (fThereIsASelection)
	{
		// Yes. So ungrey both the buttons for selecting the nodes to export.
		EnableGadget(_R(IDC_NATIVEOPTS_SELECT), TRUE);
		EnableGadget(_R(IDC_NATIVEOPTS_DRAWING), TRUE);

		//Now, which of those buttons should be selected?
		switch ( mpParams->GetExportSel () )
		{
		case SELECTION:
			// Choose the export pair of buttons.
			SetLongGadgetValue(_R(IDC_NATIVEOPTS_SELECT), FALSE);
			SetLongGadgetValue(_R(IDC_NATIVEOPTS_DRAWING), TRUE);
			break;

		default:
		case DRAWING:
			// Choose the export pair of buttons.
			SetLongGadgetValue(_R(IDC_NATIVEOPTS_SELECT), TRUE);
			SetLongGadgetValue(_R(IDC_NATIVEOPTS_DRAWING), FALSE);
			break;
		}
	}
	else
	{
		//No. So grey the SELECTION button and ungrey
		//the DRAWING button
		EnableGadget(_R(IDC_NATIVEOPTS_SELECT), FALSE);
		EnableGadget(_R(IDC_NATIVEOPTS_DRAWING), TRUE);

		// And we must select the DRAWING button for the export area controls.
		SetLongGadgetValue(_R(IDC_NATIVEOPTS_SELECT), TRUE);
		SetLongGadgetValue(_R(IDC_NATIVEOPTS_DRAWING), FALSE);
	}

	return TRUE;
}

