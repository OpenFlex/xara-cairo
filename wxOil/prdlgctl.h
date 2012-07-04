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

// The Print Dialog Class

#ifndef INC_PRDLGCTL
#define INC_PRDLGCTL

#include "printctl.h"	// Defines PrintControl
//#include "printprg.h"	// The print progress dialogue

class Document;
//	WEBSTER-ranbirr-12/11/96
#ifndef WEBSTER
class CCPrintDialog;
#endif //webster
class PrintPatchInfo;
//	WEBSTER-ranbirr-12/11/96
#ifndef WEBSTER
class PrintProgressDlg;
#endif //webster
class CDC;
class CCamView;


struct DOCINFO;
struct DEVMODE;

/********************************************************************************************

>	class CCPrintInfo : public wxPrintDialogData

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/3/95
	Purpose:	To provide a custom Print Info class

********************************************************************************************/
//	WEBSTER-ranbirr-12/11/96
#ifndef WEBSTER

class CCPrintInfo : public wxPrintDialogData
{
public:
	CCPrintInfo();	// Does nothing - do not use this constuctor
	CCPrintInfo(Document* pDoc,CCamView* pCCamView);

	~CCPrintInfo();

	BOOL StartPrinting();
	BOOL MorePaper() const;
	BOOL GetNextPaper();
	BOOL GetNextPatch(PrintPatchInfo* pPatchInfo);
	BOOL ReprintPaper();
	BOOL EndPrinting();

	BOOL StartPlatePrinting(PrintView *pPrintView, UINT32 *const pErrID);
	BOOL MorePlates();
	BOOL SetNextPlate(PrintView *pPrintView);
	void EndPlatePrinting(PrintView *pPrintView);

	void SetSliderSubRangeMax(INT32 Max);
	void SetSliderSubRangePos(INT32 Pos);

	void SetAnalysing();
	void SetPrinting();

	INT32  SetAbortProc(CDC* pCDC);			// Calls pCDC->SetAbortProc() with the appropriate abort proc
	BOOL Abort();							// TRUE if user has aborted the print job, FALSE otherwise
	BOOL SetUpDocInfo(DOCINFO** pDocInfo);	// Sets up the DOCINFO ready for a call to CDC::StartDoc()

	PrintControl *GetPrintControl()		{ return pPrCtrl;  }

	static CCPrintInfo* GetCurrent()	{ return pCurrent; }

	void LockProgressUpdate(BOOL Locked);

	wxDC * MakeDCFromPrintData(wxPrintData * pPrintData);
	wxPrintData	* m_pNativePrintData;
	Document * GetDocument() {return pDocument;}

	void SavePrintDialogData() {m_DefaultDialogData = *(wxPrintDialogData *)this; m_HaveSavedDefaultDialogData = TRUE;}

private:
	BOOL 			Initialised;	// TRUE if Init() has been successfully called
	BOOL			Printing;		// TRUE after StartPrinting() called - FALSE after EndPrinting()
	CCPrintDialog*	pOurPD;			// Ptr to one of our own print dialogs (derived from CPrintDialog)
	wxPrintDialog*	pOriginalPD;	// Original dlg created by base class constructor
	Document*		pDocument;		// Ptr to associated document
	String_256		DocTitle;		// The title of the assciated document
	PrintControl*	pPrCtrl;		// Ptr to print control that will control print layout
	PrintProgressDlg* pPrgDlg;		// Ptr to the print progress dlg, created by StartPrinting()

	CCDC * 			pCCDC;			// Ptr to ourx CCDC

	static CCPrintInfo*	pCurrent;	// Ptr to the last constructed CCPrintInfo
	static wxPrintDialogData m_DefaultDialogData;
	static BOOL m_HaveSavedDefaultDialogData;

// New methods for XaraLX

public:
	BOOL OnPreparePrinting(BOOL bPrintSetupOnly = FALSE);
	BOOL UpdatePrinterSettings(BOOL RedrawPrintBorders = TRUE);
	static BOOL HasPrintSetup();

	CCDC *	GetCCDC() const {return pCCDC;}
	CNativeDC * GetDC() const;

	BOOL	m_bContinuePrinting;

	wxRect	m_rectDraw;
};

#endif //webster

/********************************************************************************************

>	class CCPrintDialog : public wxPrintDialog

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/3/95
	Purpose:	To provide a custom Print Dialog

********************************************************************************************/
//	WEBSTER-ranbirr-12/11/96
#ifndef WEBSTER

class CCPrintDialog : public wxPrintDialog
{
// There is no memory stuff (Declare_Memdump etc) as this is an MFC derived class
public:
	CCPrintDialog(CCPrintInfo * pDialogData=NULL, Document* pDoc=NULL, BOOL PrintSetUpOnly = FALSE);
	~CCPrintDialog();

	// Functions for retrieving info on the default printer
	static BOOL GetPaperSize(wxSize* pPaperSize, BOOL RedrawPrintBorders = TRUE);
	static BOOL GetPrintableArea(DocRect* pPrintableArea);
	static BOOL GetPrintMargins(INT32* pLeft = NULL,INT32* pTop = NULL,INT32* pRight = NULL,INT32* pBottom = NULL);
	static BOOL GetResolution(INT32* pDPI,INT32* pXDPI = NULL,INT32* pYDPI = NULL);
	static BOOL GetScale(INT32* pScale);
	static BOOL CanMultiCopy(BOOL* pState);
	static BOOL IsPostscript();

	// Funcs to call when the printer settings change
	static BOOL UpdatePrinterSettings(wxPrintData * pPrintData, wxDC * pDC, Document* pDocument, BOOL RedrawPrintBorders);

	// Creates a DC using given global memory handles for DEVNAMES and DEVMODE structures
//	static HDC CreatePrinterDC(HGLOBAL hDevNames,HGLOBAL hDevMode);

	// Func that retrieves the print control func associated with attached doc
	PrintControl* GetPrintControl();

	// This group of functions are used to cope with the selected printer disappearing
	// For example, when the user closes a connection, or renames a printer via the printer manager
	static void		ResetToDefaultPrinter();
	static void		ClosePrintDialogs();
	static void		InformResetToDefaultPrinter(BOOL ClosingDlgs);
	static BOOL		IgnorePrintData()		{ return IgnorePrntData; }
	static void		ResetIgnorePrintData()	{ IgnorePrntData = FALSE; }
	static void		GetSelectedPrinterName(LPTSTR pName,INT32 BufferSize);

private:
	BOOL InitCustomDlg();	// Initialises the dlg to use our custom dlg. Called from DoModal()

	void 			Enable(UINT32 GadgetID,BOOL State);	// Func for enabling/disabling dlg controls
	BOOL 			ShowDetails();						// General func for showing print details in the dlg
	void			GetDetails(PrintControl *TargetPC);	// General func for getting print detail settings from the dlg

	Document* 		pDocument;				// The doc this dlg is associated with
	PrintControl	LocalPrintControl;		// Local print control settings, committed to doc if user clicks OK

	// Functions for collecting printer settings
	static BOOL GetPrinterSettings(BOOL RedrawPrintBorders = TRUE);
	static BOOL LookUpPaperSize(UINT32 PaperSizeID,wxSize * pPaperSize);

	// Current printer setting
	// All dimensions (paper size, margins, etc) are in MILLIPOINTS
	static BOOL		GotPrinterSettings;			// TRUE when we have a set of valid printer settings
	static wxSize 	PrPaperSize;				// Size (in MILLIPOINTS) of the printer's paper
	static BOOL  	PrPortrait;					// TRUE when the printer is set for portrait, FALSE for landscape
	static INT32		PrScale;					// Printer scale factor percentage (i.e. 100 = 100%)
	static BOOL		PrMultiCopies;				// TRUE when printer can do multiple copies itself
	static INT32		PrResolutionX;				// Printer X resolution
	static INT32		PrResolutionY;				// Printer Y resolution
	static INT32		PrResolution;				// Printer resolution (can be -ve) (min(xres,yres))
	static INT32		PrLeftMargin;				// Left margin of printable area
	static INT32		PrTopMargin;				// Top margin of printable area
	static INT32		PrRightMargin;				// Right margin of printable area
	static INT32		PrBottomMargin;				// Bottom margin of printable area
	static BOOL		PrPostscript;				// TRUE if the printer is a Postscript printer

//	static DEVMODE* GetSystemDevMode();
//	static DEVMODE* GetSystemDevMode(HWND hWnd,LPCTSTR pDriverName,LPCTSTR pDeviceName,LPCTSTR pPortName);

	BOOL PrintPrefsOpen;
	BOOL PrintPrefsChanged;

	static void DumpLastError(char* pStr1,char* pStr2);		// Dumps the last error returned by GetLastError()

	static BOOL ReopenMainDlg;

	static wxPrintDialog*  pDlgSetup;
	static CCPrintDialog* pCurrentCCPrintDialog;
	static BOOL InformPrinterReset;
	static BOOL IgnorePrntData;

protected:
	//{{AFX_MSG(CCPrintDialog)
//	afx_msg BOOL OnCommand(UINT32 GadgetID);
//	afx_msg void OnPrintSetup();				// Called when user clicks on the Setup... button
	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()

private:
	DECLARE_DYNAMIC_CLASS(CCPrintDialog)
};
#endif //webster

PORTNOTE("printing", "Disabled CCPrintToFileDialog")
#ifndef EXCLUDE_FROM_XARALX
/********************************************************************************************

>	class CCPrintToFileDialog : public CFileDialog

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/5/95
	Purpose:	To provide a custom PrintToFile Dialog

********************************************************************************************/

#define FILENAMEBUFSIZE 256

class CCPrintToFileDialog : public wxFileDialog
{
// There is no memory stuff (Declare_Memdump etc) as this is an MFC derived class
public:
	CCPrintToFileDialog(TCHAR *DefExt, TCHAR *FilterString);
	~CCPrintToFileDialog();

	virtual INT32 DoModal();
	LPSTR GetFullPathNamePtr();

private:
	static TCHAR FileName[FILENAMEBUFSIZE];
	String_64 Title;
};
#endif //EXCLUDE_FROM_XARALX

#endif  // INC_PRDLGCTL


