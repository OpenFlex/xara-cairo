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


#include "camtypes.h"  

#include "camelot.h"
//#include "andy.h"
//#include "simon.h"				// for _R(IDS_CONTINUE)
//#include "errorbox.h"			// for CInformErrorDialog::GetSafeParent

#ifdef AFX_DBG1_SEG                                               
#pragma code_seg(AFX_DBG1_SEG)
#endif

// NOTE: in separate module so it can replaced if needed.
#if 0
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif      
#endif

#ifdef _ENSURES
INT32 			AssertBusy = FALSE;				  // for testing diagnostics			
#endif

// Setup DEBUGBREAK macro
#ifdef _DEBUG
	#ifdef __WXMSW__
		#define DEBUGBREAK DebugBreak()
	#else
		#define DEBUGBREAK ::wxTrap()
	#endif
#else
	#define DEBUGBREAK {}
#endif

static void InternalAssert(const TCHAR * AssertDescription, const char * lpszFileName, INT32 nLine, BOOL UseMFC)
{
	if (!UseMFC)
#if defined(__WXMSW__)
		MessageBeep(MB_ICONASTERISK);
#else
		::wxBell();
#endif


#ifdef _ENSURES

	TCHAR				sz[256];
	static TCHAR BASED_CODE szTitle[] = wxT("Ensure Failed!");

	// In Unicode we need to convert the filename to TCHAR
#if 0 != wxUSE_UNICODE
	TCHAR szRealFile[256];
	size_t count = camMbstowcs(szRealFile, lpszFileName, 255);
	if (count == (size_t)-1)
		count = 0;
	szRealFile[count] = (TCHAR)0;
	const TCHAR* lpszRealFile = szRealFile;
#else
	const TCHAR* lpszRealFile = lpszFileName;
#endif

	static TCHAR BASED_CODE szMessage[] = wxT("%s, File %s, Line %d");
	static TCHAR BASED_CODE szMessageNoReason[] = wxT("Error %d@%s");			// note number first

	// get app name or NULL if unknown (don't call assert)
//	const TCHAR		   *pszAppName = wxGetApp().GetAppName();

	if (AssertDescription != NULL)
	{
		camSnprintf(sz, 255,
			szMessage,                       
			AssertDescription, 
			lpszRealFile, 
			nLine);    
	}
	else   
	{
		camSnprintf(sz, 255,
			szMessageNoReason,
			nLine,
			lpszRealFile);
	}
	
#ifdef _DEBUG
//PORTNOTE("other","Remove afxTraceEnabled")
//#ifndef EXCLUDE_FROM_XARALX
//	if (afxTraceEnabled)
#if defined(__WXMSW__)
	{
		// assume the debugger or auxiliary port
		#ifndef _MAC
		::OutputDebugString(sz);
		::OutputDebugString(_T(", "));
		::OutputDebugString(szTitle);
		::OutputDebugString(_T("\n\r"));
		#else
		// Mac version needs them all together
		camStrcat(sz, _T(", "));
		camStrcat(sz,szTitle);
		camStrcat(sz,_T("\n\r"));
		::OutputDebugString(sz);
		#endif
	}
#endif
#endif


	if (AssertBusy > 0)
	{
		// getting assertion while inside an assertion
		//  - it has already been traced, but 
		// break into the debugger (or Dr Watson log)
		DEBUGBREAK;									// else Win32s might die (just beeps)
		return;
	}

	AssertBusy++;

	if ( Error::IsInRenderThread() )
	{
		TRACE( wxT("In RenderThread so clearing up system") );
		Error::RenderThreadReset();
													// Commented out - no problem using wx for render errors
//		UseMFC = FALSE;								// mustn't use MFC for render errors 
	}

	INT32					result;

	TCHAR				RealErrorMsg[256];

	if (UseMFC)
	{
		// use our error handler to report ensures as it is more robust instead of MessageBox
		// The arrangement of buttons is the same as the exception handler dialog, not the same
		// as the original Ensure dialog (which was Abort/Retry/Ignore)
		ErrorInfo Info;

		// try to preserve original error message
		camStrcpy( RealErrorMsg, Error::GetErrorString() );

		Error::SetErrorSerious( sz );			// set error msg (vaping any previous one)
		Info.ErrorMsg = 0;
		Info.Button[0] = _R(IDS_CONTINUE);
		Info.Button[1] = _R(IDS_QUIT);
#ifndef EXCLUDE_FROM_XARALX
		if (IsWin32NT())
		{
#endif
			// only NT can cope with an Abort button
			Info.Button[2] = _R(IDS_ABORT);
			Info.Button[3] = _R(IDS_DEBUG);
#ifndef EXCLUDE_FROM_XARALX
		}
		else
		{
			Info.Button[2] = _R(IDS_DEBUG);
		}
#endif
													// no default button (or Help)
		Info.Cancel = 1;							// Esc = Continue

		result = InformGeneral( ERRORTYPE_ENSURE, &Info );
	}
	else

	{
		CCamApp::DisableSystem();

		// e.g. if this an MFC assert, don't use our lovely error handler becuase that itself
		// uses MFC. Instead we use good old MessageBox

#if !defined(EXCLUDE_FROM_RALPH) && !defined(EXCLUDE_FROM_XARALX)
		wxWindow	   *pParent = AfxGetApp().GetTopWindow(); 
PORTNOTE("other","Use CInformErrorDialog::GetSafeParent() when implemented")
#ifndef EXCLUDE_FROM_XARALX
		CInformErrorDialog::GetSafeParent();
#endif
#else
		wxWindow	   *pParent = NULL;
#endif

		wxMessageDialog	Dialog( pParent, sz, szTitle, wxICON_HAND | wxYES_NO | wxCANCEL );
		INT32 nCode = Dialog.ShowModal();

		CCamApp::EnableSystem();

		// convert MessageBox return value into a sane button ID
		switch (nCode)
		{
			case wxID_NO:
				result = _R(IDS_ABORT);
				break;
			case wxID_YES:
				result = _R(IDS_DEBUG);
				break;
			case wxID_CANCEL:
			default:
				result = _R(IDS_CONTINUE);
				break;
		}
	}

	AssertBusy--;

	if ((ResourceID)result == _R(IDS_DEBUG))
	{
		DEBUGBREAK;
	}
	// no action on _R(IDS_CONTINUE))
	else if ((ResourceID)result == _R(IDS_QUIT))
	{
		// quit in a slightly nice way
		wxWindow *MainWnd = AfxGetApp().GetTopWindow();
		if( MainWnd && MainWnd->IsShown() )
		{
			MainWnd->Destroy();
		}
	} // drop through
	if (((ResourceID)result == _R(IDS_ABORT)) || ((ResourceID)result == _R(IDS_QUIT)))
	{
		// if no window, try nasty exit
		AfxAbort();
		return; // how did we get here?
	}

	// if we ever get here we just carry on as if nothing happened

PORTNOTE("other","We can never use MFC again")
#ifndef EXCLUDE_FROM_XARALX
	if (UseMFC)
	{
		if (RealErrorMsg[0])
			Error::SetErrorSerious( RealErrorMsg );		// restore previous error msg
		else
			Error::ClearError();
	} 
#endif
#else
	// parameters not used if non-debug
	(void)lpszFileName;
	(void)nLine;
#endif // _ENSURES

}


/***********************************************************************************************

>	void EnsureFailedLine(LPCSTR AssertDescription, LPCSTR lpszFileName, INT32 nLine)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/5/93
	Inputs:		AssertDescription: Reason for failure description  
				lpszFileName:      Filename of file that caused failure
				nLine:             Line number that caused failure
	Outputs:	-
	Returns:	-     
	Purpose:    This function should only ever be invoked from the ENSURE macro 
				which is similar to the ASSERT macro, the only difference being that 
				it takes a parameter which describes the reason for the failure. 
	Errors:		-
	SeeAlso:	-

***********************************************************************************************/
/* Technical notes: 

This function is an almost direct copy of the AfxAssertFailedLine function which is
called from the ASSERT macro.
*/ 

void EnsureFailedLine(const TCHAR * AssertDescription, const char * lpszFileName, INT32 nLine)
{
	InternalAssert( AssertDescription, lpszFileName, nLine, TRUE );
}

/***********************************************************************************************

>	void AfxAssertLineFailed(LPCSTR lpszFileName, INT32 nLine)

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/2/94
	Inputs:		lpszFileName:      Filename of file that caused failure
				nLine:             Line number that caused failure
	Outputs:	-
	Returns:	-     
	Purpose:    This is a more robust version than MFC provides.
	Errors:		-
	SeeAlso:	-

***********************************************************************************************/

#if COMPILER_REVISION >= 3
// VC2 Beta
BOOL AFXAPI AfxAssertFailedLine(LPCSTR lpszFileName, INT32 nLine)
#else
// VC1 or Chicago pre-Beta VC2
void AFXAPI AfxAssertFailedLine(LPCSTR lpszFileName, INT32 nLine)
#endif
{
	#ifdef _MAC
	// ignore an incredibly annoying Mac assert which is something to do with rendering
	// the icons on our scroll bars
	if ( (nLine==119) && (camStrcmp(lpszFileName, "winbtn.cpp")==0) )
		return FALSE;
	#endif

	// must NOT use MFC for reporting this
	InternalAssert( _T("MFC Ensure"), lpszFileName, nLine, FALSE );

	#if COMPILER_REVISION >= 3
	return FALSE;
	#endif
}




