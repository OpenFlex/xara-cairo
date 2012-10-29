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
// PrintProgressDlg - implements the print progress dialog displayed during printing

/*
*/

#include "camtypes.h"

//	WEBSTER-ranbirr-12/11/96
#ifndef WEBSTER

#include "printprg.h"
//#include "printdlg.h"
//#include "custmsg.h"
//#include "markn.h"
//#include "simon.h"
//#include "andy.h"
#include "camelot.h"
//#include "justin2.h"
#include "prncamvw.h"


CC_IMPLEMENT_DYNCREATE(PrintProgressDlg, DialogOp)

#define new CAM_DEBUG_NEW

const CDlgMode PrintProgressDlg::Mode = MODELESS ;// Mode of the dialog
const UINT32 PrintProgressDlg::IDD = _R(IDD_PRINTPROGRESS);
BOOL PrintProgressDlg::Aborted = FALSE;
PrintProgressDlg* PrintProgressDlg::pPrintProgressDlg = NULL;

const INT32 SLIDER_MAX = 0x08000000;

/********************************************************************************************

>	PrintProgressDlg::PrintProgressDlg()

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	14/06/2006
	Inputs:		-
	Returns:	-
	Purpose:	Constructs the dlg.
	SeeAlso:	-

********************************************************************************************/


PrintProgressDlg::PrintProgressDlg(): DialogOp(PrintProgressDlg::IDD, PrintProgressDlg::Mode)
{
	if (pPrintProgressDlg)
	{
		pPrintProgressDlg->Done();
		pPrintProgressDlg = NULL;
	}

	SliderMax = SLIDER_MAX;
	SliderCurPercent = -1;
	SliderSubRangeMax = SLIDER_MAX;
	SliderSubRangeBase = 0;
	SliderSubRangeStep = 1;

	pPrintProgressDlg = this;
	pDisabler = NULL;

	Printing = FALSE;
	IgnoreUpdates = FALSE;
	Aborted = FALSE;

	UpdateTime.Sample();
}


/********************************************************************************************

>	BOOL PrintProgressDlg::Do(OpDescriptor*)

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	14/06/2006
	Inputs:		-
	Returns:	TRUE if OK, FALSE otherwise
	Purpose:	Inits the dialog's controls, and calls the base classes OnInitDialog() function
	SeeAlso:	-

********************************************************************************************/

void PrintProgressDlg::Do(OpDescriptor*)
{
	Create();
	Open();
}

/********************************************************************************************

>	BOOL PrintProgressDlg::GetState(String_256*, OpDescriptor*)

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	14/06/2006
	Inputs:		-
	Returns:	TRUE if OK, FALSE otherwise
	Purpose:	Inits the dialog's controls, and calls the base classes OnInitDialog() function
	SeeAlso:	-

********************************************************************************************/

OpState	PrintProgressDlg::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;
	return(OpSt);
}

/********************************************************************************************

>	BOOL PrintProgressDlg::PrintProgressDlg::Init()

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	14/06/2006
	Inputs:		-
	Returns:	TRUE if OK, FALSE otherwise
	Purpose:	Inits the dialog's controls, and calls the base classes OnInitDialog() function
	SeeAlso:	-

********************************************************************************************/

BOOL PrintProgressDlg::Init()
{
	return (RegisterOpDescriptor(
									0,
									_R(IDD_PRINTPROGRESS),
									CC_RUNTIME_CLASS(PrintProgressDlg),
									OPTOKEN_PRINT_PROGRESS,
									PrintProgressDlg::GetState,
									0,	/* help ID */
									0, 	/* bubble help*/
									0	/* bitmap ID */
									));
}

/********************************************************************************************

>	MsgResult PrintProgressDlg::Message( Msg* Message)

	Author:		Alex Bligh <alex@alex.org.uk>
	Created:	14/06/2006
	Inputs:		-
	Returns:	-
	Purpose:	Overrides the default OnOK() func so that we can check the values set by the user.
				If dodgy values have been put in, the user is warned.
	SeeAlso:	-

********************************************************************************************/

MsgResult PrintProgressDlg::Message( Msg* Message)
{
	if (IS_OUR_DIALOG_MSG(Message))
	{
		DialogMsg* Msg = (DialogMsg*)Message;
		// Handle ok button
		if (Msg->DlgMsg == DIM_CREATE)
		{
			SetSliderMax(SLIDER_MAX);
			SetSliderPos(0);
			IgnoreUpdates = FALSE;
			UpdateTime.Sample();

			if (pDisabler)
				delete pDisabler;
			pDisabler = new wxWindowDisabler(WindowID);
			::wxYield(); // flush anything out the system
		}
		else if (Msg->DlgMsg == DIM_CANCEL)
		{
			if (CCamApp::IsDisabled())
				return OK;

			INT32 b = InformWarning(_R(IDS_PRINT_SUSPEND),_R(IDS_ABORT),_R(IDS_CONTINUE));
	
			if (b == 1)
			{
				Aborted = TRUE;
			}
			return OK; // Do not pass to the base class as this will destroy the dialog - we do that elsewhere
		}
	}
	return DialogOp::Message(Message);
}





//--------------------------------------------

void PrintProgressDlg::SetSliderMax(INT32 max)
{
	SliderMax 	  	 = max;
	SliderCurPercent = -1;

	SetGadgetRange(_R(IDC_PRINTPROGSLIDER), 0, max);
}

//--------------------------------------------

void PrintProgressDlg::SetSliderPos(INT32 pos)
{
	if (pos == -1)
		pos = SliderMax;

	if (pos < 0) pos = 0;
	if (pos > SliderMax) pos = SliderMax;

	INT32 p;
	double ratio = double(SliderMax) / 100.0;
	if (ratio != 0.0)
		p = INT32 ((double(pos) / ratio)+0.5);
	else
		p = 0;

	if (p != SliderCurPercent)
	{
		SliderCurPercent = p;

		SetLongGadgetValue(_R(IDC_PRINTPROGSLIDER), (INT32)pos);
	
		String_32 Percent;
		Percent.MakeMsg(_R(IDS_PRINT_PROG_PERCENT), (INT32) p);
		SetStringGadgetValue(_R(IDC_CURRENTPERCENTAGE), Percent);
		PaintGadgetNow(_R(IDC_CURRENTPERCENTAGE));
		PaintGadgetNow(_R(IDC_PRINTPROGSLIDER));
	}
}

//--------------------------------------------

void PrintProgressDlg::SetSliderSubRangeMax(INT32 max)
{
	if (max < 1) max = 1;
	SliderSubRangeMax = max;
}

//--------------------------------------------

void PrintProgressDlg::SetSliderSubRangePos(INT32 pos)
{
	if (pos > SliderSubRangeMax) pos = SliderSubRangeMax;
	if (pos < 0) 				 pos = 0;

	double ratio = double(pos)/double(SliderSubRangeMax);

	SetSliderPos(SliderSubRangeBase+INT32(double(SliderSubRangeStep)*ratio));
}

//--------------------------------------------

void PrintProgressDlg::SetDocName(LPCTSTR pDocName)
{
	if (pDocName != NULL)
	{
		SetStringGadgetValue(_R(IDC_DOCNAME), String_256(pDocName));
		PaintGadgetNow(_R(IDC_DOCNAME));
	}
}

//--------------------------------------------

void PrintProgressDlg::SetPrinterName(LPCTSTR pPrinterName)
{
	if (pPrinterName != NULL)
	{
		SetStringGadgetValue(_R(IDC_PRINTERNAME), String_256(pPrinterName));
		PaintGadgetNow(_R(IDC_PRINTERNAME));
	}
}

//--------------------------------------------

void PrintProgressDlg::SetPortName(LPCTSTR pPortName)
{
// Phil has decided that the port name is a bit too tecchie and not
// really very useful info, so we've removed it to simplify the dialog
//
//	if (pPortName != NULL)
//	{
//		SetStringGadgetValue(_R(IDC_PORTNAME), String_256(pPortName));
//		PaintGadgetNow(_R(IDC_PORTNAME));
//	}

}

//--------------------------------------------

/********************************************************************************************

>	void PrintProgressDlg::SetPageNumber(INT32 PageNumber,  INT32 MaxPageNumber,
									 INT32 PlateNumber, INT32 MaxPlateNumber, LPCTSTR pPlateName,
									 INT32 TileNumber,  INT32 MaxTileNumber)

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>/Jason
	Created:	? (93 or 94 ish)
	Inputs:		PageNumber		- The page being printed in the range 1..MaxPageNumber
				MaxPageNumber	- Total number of pages being printed (minimum of 1)
				PlateNumber		- If separating, the current plate number in range 1..MaxPlateNumber
									else ignored
				MaxPlateNumber	- If separating, the number of plates being printed (minimum of 1)
								  If not separating, this MUST be set to 0.
				pPlateName		- If separating, the name of the plate,
									else NULL
				TileNumber		- The current tile in the range 1..MaxTileNumber
				MaxTileNumber	- The number of tiles being printed (minimum of 1)
	Returns:	-
	Purpose:	Dumps the last error returned by GetLastError() using the FormatMessage() command
	SeeAlso:	CPrintDialog::DoModal

********************************************************************************************/

void PrintProgressDlg::SetPageNumber(INT32 PageNumber,  INT32 MaxPageNumber,
									 INT32 PlateNumber, INT32 MaxPlateNumber, LPCTSTR pPlateName,
									 INT32 TileNumber,  INT32 MaxTileNumber)
{
	// If the dlg is tem,porarily locked to stop screen updates, just return immediately.
	if (IgnoreUpdates)
		return;

	String_256 Str;

	// Set the page info
	Str.MakeMsg(_R(IDS_PRINT_PROG_PAGE), PageNumber, MaxPageNumber);
	SetStringGadgetValue(_R(IDC_PAGENUMBER), Str);
	PaintGadgetNow(_R(IDC_PORTNAME));

	// Set the plate info
	if (MaxPlateNumber > 0 && pPlateName != NULL)
		Str.MakeMsg(_R(IDS_PRINT_PROG_PLATE), PlateNumber, MaxPlateNumber, pPlateName);
	else
		Str.MakeMsg(_R(IDS_PRINT_PROG_COMPOSITE));

	SetStringGadgetValue(_R(IDC_PLATENUMBER), Str);
	PaintGadgetNow(_R(IDC_PLATENUMBER));

	// Set the tile info
	if (MaxTileNumber > 1)
	{
		Str.MakeMsg(_R(IDS_PRINT_PROG_TILE), TileNumber, MaxTileNumber);
		SetStringGadgetValue(_R(IDC_TILENUMBER), Str);
	}

	HideGadget(_R(IDC_TILETITLE), (MaxTileNumber <= 1));
	HideGadget(_R(IDC_TILENUMBER), (MaxTileNumber <= 1));
	PaintGadgetNow(_R(IDC_TILETITLE));
	PaintGadgetNow(_R(IDC_TILENUMBER));

	// Make sure we don't get a div by zero or a nasty negative in the calculations below
	if (MaxPageNumber < 1)		MaxPageNumber = 1;
	if (PageNumber < 1)			PageNumber = 1;
	if (MaxPlateNumber < 1)		MaxPlateNumber = 1;
	if (PlateNumber < 1)		PlateNumber = 1;
	if (MaxTileNumber < 1)		MaxTileNumber = 1;
	if (TileNumber < 1)			TileNumber = 1;

	// And set the slider position accordingly - divide the 100% up into ranges for each page,
	// subdivided into ranges for each plate, subdivided into ranges for each tile.
	INT32 SliderPerPage  = SliderMax / MaxPageNumber;
	INT32 SliderPerPlate = SliderPerPage / MaxPlateNumber;
	INT32 SliderPerTile  = SliderPerPlate / MaxTileNumber;

	SliderSubRangeBase = (SliderPerPage  * (PageNumber-1))  +
						 (SliderPerPlate * (PlateNumber-1)) +
						 (SliderPerTile  * (TileNumber-1));
	SliderSubRangeStep = SliderPerTile;

	SetSliderPos(SliderSubRangeBase);
}


//--------------------------------------------
//--------------------------------------------

BOOL PrintProgressDlg::AbortProc()
{
	if (CCamApp::IsDisabled() || !pPrintProgressDlg)
		// Ignore
		return TRUE;

	// Note this only paints the gadget if it is invalidated
	pPrintProgressDlg->PaintGadgetNow(0);

	// Only sample if 750ms of printing has elapsed as the yield can take a while
	if (!PrintMonitor::IsYieldDisabled() && (pPrintProgressDlg->UpdateTime.Elapsed(750)))
	{
		// Save current doc view etc. around yield as paint can destroy them.
		View * pCurrentView = View::GetCurrent();
		Document * pCurrentDocument = Document::GetCurrent();
		AfxGetApp().Yield(TRUE);
		pCurrentDocument->SetCurrent();
		pCurrentView->SetCurrent();

		// resample after the yield
		pPrintProgressDlg->UpdateTime.Sample();
	}

	return Aborted;
}


#endif //webster
