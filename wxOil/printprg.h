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


// Holds most of the OIL-y printing facilities used by ScreenCamView.

//	WEBSTER-ranbirr-12/11/96
#ifndef WEBSTER

#ifndef INC_PRINTPRG
#define INC_PRINTPRG

#define OPTOKEN_PRINT_PROGRESS _T("PrintProgress")

/********************************************************************************************

>	class PrintProgressDlg : public CDialog

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/95
	Purpose:	Maintains the print progress dialog which shows the user how the print is
				going and also allows them to cancel the print at any time.

				I copied Tim's stuff in prncamvw.h & .cpp and developed this lot from there.
	SeeAlso:	

********************************************************************************************/

class PrintProgressDlg : public DialogOp
{
	CC_DECLARE_DYNCREATE( PrintProgressDlg )  
public:
	PrintProgressDlg();
	virtual ~PrintProgressDlg() { pPrintProgressDlg = NULL; if (pDisabler) { delete pDisabler; pDisabler=NULL;} }

	MsgResult Message( Msg* Message );  
	void Do(OpDescriptor*);		// "Do" function        
	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);	

	static const UINT32 IDD;
	static const CDlgMode Mode;
	static BOOL Aborted;

public:
//	virtual BOOL OnInitDialog();
//	virtual void OnCancel();

	void SetSliderMax(INT32 max);
	void SetSliderPos(INT32 pos);

	void SetSliderSubRangeMax(INT32 Max);
	void SetSliderSubRangePos(INT32 Pos);


public:
	void SetDocName(LPCTSTR pDocName);
	void SetPrinterName(LPCTSTR pPrinterName);
	void SetPortName(LPCTSTR pPortName);
	void SetPageNumber( INT32 PageNumber,  INT32 MaxPageNumber,
						INT32 PlateNumber, INT32 MaxPlateNumber, LPCTSTR pPlateName,
						INT32 TileNumber,  INT32 MaxTileNumber);

	// While the dlg is Locked, calls to SetPageNumber functions will be ignored
	void LockProgressUpdate(BOOL Locked) { IgnoreUpdates = Locked; }

	void Done() {Close(); End();}

public:
	void SetAnalysing()	{ Printing = FALSE; }
	void SetPrinting()  { Printing = TRUE;  }


private:
	INT32 SliderMax;
	INT32 SliderCurPercent;	// Current percentage the slider is representing (between 0 to 100)

	INT32 SliderSubRangeMax;
	INT32 SliderSubRangeBase;
	INT32 SliderSubRangeStep;

	BOOL Printing;

	BOOL IgnoreUpdates;				// TRUE if the dlg is locked against showing any updated info

	MonotonicTime UpdateTime;

public:
	// The call back function for the print dialog.
	static BOOL AbortProc();

private:
	static PrintProgressDlg* pPrintProgressDlg;		// Ptr to dlg used by AbortProc()

	wxWindowDisabler * pDisabler;

public:
	static PrintProgressDlg * Get() {return pPrintProgressDlg;}
};


#endif  // INC_PRINTPRG

#endif //webster
