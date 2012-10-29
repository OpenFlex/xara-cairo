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


// Implemetation of the following classes
/*
	OperationHistory : The operation history used to store undoable operations
	OpUndo           : The undo operation
	OpRedo           : The redo operation

	BlobbyOp         : Demonstration temporary operation which changes the colour of a
					   documents paper.

	UndoColAction    : BlobbyOp undo action
	RedoColAction    : BlobbyOp redo action
*/

/*
*/
#include "camtypes.h"


#include "selmedia.h"
#include "ophist.h"
#include "lineattr.h"
//#include "resource.h"
#include "page.h"
//#include "mario.h"
//#include "simon.h"
//#include "blobtab.h"
#include <stdlib.h>

#include "bfxatom.h"
#include "tracergn.h"
#include "bubbleid.h"

CC_IMPLEMENT_DYNCREATE(SelMediaDlg, DialogOp)
CC_IMPLEMENT_DYNAMIC(SelMediaDlgParam, OpParam)

#define new CAM_DEBUG_NEW

//------------------------------------------------------------------------------------------
// Demo Dialog

const CDlgMode SelMediaDlg::Mode = MODAL;// Mode of the dialog

const UINT32 SelMediaDlg::IDD = _R(IDD_SEL_MEDIA_APP_DIALOG);

SelMediaDlg::SelMediaDlg(): DialogOp(SelMediaDlg::IDD, SelMediaDlg::Mode), m_pOptions( NULL )
{
}

// -----------------------------------------------------------------------------------------

void SelMediaDlg::InitValues()
{
	bool				fItemSel = false;

	// Add possible replay apps
	SelMediaDlgParam::CMediaAppListIter	end( m_pOptions->m_pAppList->end() );
	SelMediaDlgParam::CMediaAppListIter	iter( m_pOptions->m_pAppList->begin() );
	for( INT32 ord = 0; iter != end; ++iter, ++ord )
	{
		SetStringGadgetValue( _R(IDC_LIST1), String_256(iter->first), FALSE, ord );

		if( m_pOptions->m_strSel != _T("") )
		{
			if( m_pOptions->m_strSel == iter->first )
			{
				fItemSel = true;
				SetSelectedValueIndex( _R(IDC_LIST1), ord );
			}
		}
		else
		if( iter->second )
		{
			fItemSel = true;
			SetSelectedValueIndex( _R(IDC_LIST1), ord );
		}
	}

	if( !fItemSel )
		SetSelectedValueIndex( _R(IDC_LIST1), 0 );
}

// -----------------------------------------------------------------------------------------

MsgResult SelMediaDlg::Message( Msg* Message)
{
	if (IS_OUR_DIALOG_MSG(Message))
	{
		DialogMsg* Msg = (DialogMsg*)Message;
		// Handle ok button
		if ((Msg->DlgMsg == DIM_COMMIT) || (Msg->DlgMsg == DIM_CANCEL))
		{
			m_pOptions->m_strSel = GetStringGadgetValue( _R(IDC_LIST1) );
			TRACEUSER( "jlh92", _T("Return sel is %s\n"), PCTSTR(m_pOptions->m_strSel) );

			m_pOptions->m_fValid = ( DIM_COMMIT == Msg->DlgMsg );

			Close(); // Hide the dialog
			End();
		}
		else
		if( DIM_SOFT_COMMIT == Msg->DlgMsg ||
			DIM_CREATE == Msg->DlgMsg )
			InitValues();

		return (DLG_EAT_IF_HUNGRY(Msg));
	}
	return OK;
}

// -----------------------------------------------------------------------------------------

OpState	SelMediaDlg::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;
	return(OpSt);
}

// -----------------------------------------------------------------------------------------

BOOL SelMediaDlg::Init()
{
	return (RegisterOpDescriptor(
 								0,
 								_R(IDS_SELMEDIADLG),
								CC_RUNTIME_CLASS(SelMediaDlg),
 								OPTOKEN_SELMEDIADLG,
 								SelMediaDlg::GetState,
 								0,	/* help ID */
 								_R(IDBBL_SELMEDIADLG),
 								0	/* bitmap ID */
								));
}

// -----------------------------------------------------------------------------------------

BOOL SelMediaDlg::Create()
{
	if (DialogOp::Create())
	{
		return TRUE;
    }
    else
		return FALSE;
}

// -----------------------------------------------------------------------------------------

void SelMediaDlg::Do(OpDescriptor*)
{
	Create();
	Open();
}

/******************************************************************************************

>	void BmpPrefsDlg::DoWithParam(OpDescriptor*)

	Author:		Luke_hart (Xara Group Ltd) <LukeH@xara.com>
	Created:	23/08/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Creates then opens the dialog in response to a request from the user and
				allows values to be passed in and returned to the caller via the
				SelMediaDlgParam class.
	Errors:		-
	SeeAlso:	-

******************************************************************************************/

void SelMediaDlg::DoWithParam(OpDescriptor*, OpParam* pParam)
{
	if (pParam == NULL)
	{
		ERROR3("SelMediaDlg::DoWithParam - NULL Args");
		return;
	}

	// Use the OpParam that has been passed in to us
	ERROR3IF( !pParam->IS_KIND_OF(SelMediaDlgParam), "pParam isn't" );
	m_pOptions = (SelMediaDlgParam*) pParam;

	// Force the dialog box to be created, as it is modal it will be opened via a message
	BOOL				fOk = Create();
	if( !fOk )
	{
		// Could not create the dialog box so call inform error 
		InformError();
  		End(); 		   // End the operation 
	}
}

