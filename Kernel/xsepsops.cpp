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
// XSEPSExportOptions - implements the options relevant to the export of XS EPS

/*
*/

#include "camtypes.h"
#include "xsepsops.h"
//#include "printdlg.h"
#include "epsfiltr.h"
//#include "markn.h"
//#include "resource.h"
#include "helpuser.h"


CC_IMPLEMENT_DYNCREATE(XSEPSExportOptions, DialogOp)

#define new CAM_DEBUG_NEW

const CDlgMode XSEPSExportOptions::Mode = MODAL ;// Mode of the dialog
const UINT32 XSEPSExportOptions::IDD = _R(IDD_XSEPSOPS);
BOOL XSEPSExportOptions::Aborted = FALSE;

/********************************************************************************************

>	XSEPSExportOptions::XSEPSExportOptions()

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	14/06/2006
	Inputs:		-
	Returns:	-
	Purpose:	Constructs the dlg.
	SeeAlso:	-

********************************************************************************************/


XSEPSExportOptions::XSEPSExportOptions(): DialogOp(XSEPSExportOptions::IDD, XSEPSExportOptions::Mode)
{
}


/********************************************************************************************

>	BOOL XSEPSExportOptions::Do(OpDescriptor*)

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	14/06/2006
	Inputs:		-
	Returns:	TRUE if OK, FALSE otherwise
	Purpose:	Inits the dialog's controls, and calls the base classes OnInitDialog() function
	SeeAlso:	-

********************************************************************************************/

void XSEPSExportOptions::Do(OpDescriptor*)
{
	Create(); // Modal dialog, so this will actually run the dialog
}

/********************************************************************************************

>	BOOL XSEPSExportOptions::GetState(String_256*, OpDescriptor*)

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	14/06/2006
	Inputs:		-
	Returns:	TRUE if OK, FALSE otherwise
	Purpose:	Inits the dialog's controls, and calls the base classes OnInitDialog() function
	SeeAlso:	-

********************************************************************************************/

OpState	XSEPSExportOptions::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;
	return(OpSt);
}

/********************************************************************************************

>	BOOL XSEPSExportOptions::XSEPSExportOptions::Init()

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	14/06/2006
	Inputs:		-
	Returns:	TRUE if OK, FALSE otherwise
	Purpose:	Inits the dialog's controls, and calls the base classes OnInitDialog() function
	SeeAlso:	-

********************************************************************************************/

BOOL XSEPSExportOptions::Init()
{
	return (RegisterOpDescriptor(
									0,
									_R(IDD_XSEPSOPS),
									CC_RUNTIME_CLASS(XSEPSExportOptions),
									OPTOKEN_XSEPSEXPORTOPTIONS,
									XSEPSExportOptions::GetState,
									0,	/* help ID */
									0, 	/* bubble help*/
									0	/* bitmap ID */
									));
}

/********************************************************************************************

>	MsgResult XSEPSExportOptions::Message( Msg* Message)

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	14/06/2006
	Inputs:		-
	Returns:	-
	Purpose:	Overrides the default OnOK() func so that we can check the values set by the user.
				If dodgy values have been put in, the user is warned.
	SeeAlso:	-

********************************************************************************************/

MsgResult XSEPSExportOptions::Message( Msg* Message)
{

	if (IS_OUR_DIALOG_MSG(Message))
	{
		DialogMsg* Msg = (DialogMsg*)Message;
		// Handle ok button
		if (Msg->DlgMsg == DIM_CREATE)
		{
			SetLongGadgetValue(_R(IDC_DPIEDIT), 150, FALSE, 0);
			SetLongGadgetValue(_R(IDC_DPIEDIT), 200, FALSE, 1);
			SetLongGadgetValue(_R(IDC_DPIEDIT), 300, FALSE, 2);
			SetLongGadgetValue(_R(IDC_DPIEDIT), (INT32) EPSFilter::XSEPSExportDPI, FALSE, -1);
	
			/*
			SetBoolGadgetSelected(_R(IDC_PSLEVELAUTO),	EPSFilter::XSEPSExportPSType == 0);
			SetBoolGadgetSelected(_R(IDC_PSLEVEL1),	EPSFilter::XSEPSExportPSType == 1);
			SetBoolGadgetSelected(_R(IDC_PSLEVEL2),	EPSFilter::XSEPSExportPSType == 2);
			*/
	
			SetBoolGadgetSelected(_R(IDC_EXPORTTEXTASCURVES), EPSFilter::XSEPSExportTextAsCurves);
		}
		else if (Msg->DlgMsg == DIM_COMMIT)
		{
			Aborted = FALSE;
			// DPI ed field
			UINT32 DPI = GetLongGadgetValue(_R(IDC_DPIEDIT),10,2400);
			if (DPI < 10)
				DPI = 10;
		
			if (DPI > 600)
				DPI = 600;

			if (DPI > 300)
			{
				INT32 b = InformWarning(_R(IDS_EXPORT_BIGDPI),_R(IDS_OK),_R(IDS_CANCEL));
				if (b != 1)
					Aborted = TRUE;
			}

			if (Aborted)
			{
				Msg->DlgMsg=DIM_NONE; // prevent dialog from going away
			}
			else
			{
				/*
				// Job 10463: remove PS Level bits - default to Level 2
				INT32 ps = 0;
				if (GetBoolGadgetSelected(_R(IDC_PSLEVEL1)))
					ps = 1;
				if (GetBoolGadgetSelected(_R(IDC_PSLEVEL2)))
					ps = 2;
				*/
			
				EPSFilter::XSEPSExportDPI 	 = DPI;
				// EPSFilter::XSEPSExportPSType = ps;
			
				EPSFilter::XSEPSExportTextAsCurves = GetBoolGadgetSelected(_R(IDC_EXPORTTEXTASCURVES));
			}	
		}
	}
	return DialogOp::Message(Message);
}

