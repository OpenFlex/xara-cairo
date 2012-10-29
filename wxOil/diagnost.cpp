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


// Diagnostic output routines to help in remote end-user debugging



#include "camtypes.h"
#include "diagnost.h"
#include "camelot.h"

static INT32 OutputDiagnostics = 0;

/********************************************************************************************

>	BOOL InitDiagnosticPrefs()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/93
	Returns:	TRUE if preferences retrieved correctly, FALSE otherwise
	Purpose:	To obtain the diagnostics preference from Camelot's ini file.
	SeeAlso:	Main.cpp

********************************************************************************************/

BOOL InitDiagnosticPrefs()
{
	Camelot.DeclarePref(TEXT("DebugFlags"), TEXT("OutputDiagnostics"), 
						&OutputDiagnostics, FALSE, TRUE);

	return TRUE;
}


/********************************************************************************************

>	void CDECL DiagnosticFn(LPCSTR FunctionStr, LPCSTR pszFormat, ...)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/11/93
	Inputs:		FunctionStr: (no space required at end, a space is inserted before being 
							  concatenated)
	`			pszFormat: Format string (no \n required at end)
				arguments
	Outputs:	-
	Returns:	-
	Purpose:	This function is the same as Diagnostic except that it takes an additional 
				function parameter which is concatenated with the format string. 

				*The idea of this function is to save space. The compiler settings will 
				recognise multiple  uses of the same constant string. 

	Errors:		-
	SeeAlso:	Diagnostic

********************************************************************************************/

void CDECL DiagnosticFn(LPCTSTR FunctionStr, LPCTSTR pszFormat, ...)
{
	UINT32					nBuf;
	TCHAR				szBuffer[512];
	const TCHAR		   *pszLocalFormat;

	pszLocalFormat = pszFormat;

	va_list args;
	va_start(args, pszFormat);

	nBuf = camVsnprintf( szBuffer, 512, pszLocalFormat, args );
	
	ASSERT(nBuf < sizeof(szBuffer));

#if 0
	if ((OutputDiagnostics == 1) && (AfxGetApp() != NULL))
		afxDump << AfxGetApp()->m_pszExeName << ": ";

	afxDump << FunctionStr << ": " << szBuffer << "\n";
#else
	String_256 DiagOutput;

	if( OutputDiagnostics == 1 )
	{
		DiagOutput = AfxGetApp().GetAppName().c_str();
		DiagOutput += wxT(": ");
	}

	DiagOutput += FunctionStr;
	DiagOutput += wxT(": ");
	DiagOutput += szBuffer;
	DiagOutput += wxT("\n");

#if defined(__WXMSW__)
	OutputDebugString(DiagOutput);
#elif defined(__WXMSW__)
#pragma error( "OutputDebugString equiv. for Linux" )
#endif

#endif

	va_end(args);
	
}

/********************************************************************************************

>	void CDECL Diagnostic(LPCSTR pszFormat, ...)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/11/93
	Inputs:		pszFormat: Format string (no \n required at end)
				arguments
	Outputs:	-
	Returns:	-
	Purpose:	This function is used in a similar way to TRACE, but exists in retail builds 
				also. It is designed to aid in technical support. It should be used when 
				resources get low, for example, when it might say: "CreatePen failed" or 
				"BitBlt failed", eg,

				if (!SelectPen(blobby))
					Diagnostic("SelectPen %d failed", PenIndex); 

				The strings used will always be in English, must be short & sweet, and must 
				never contain any words you would not say to your mother. 

	Errors:		-
	SeeAlso:	DiagnosticFn

********************************************************************************************/

void CDECL Diagnostic(LPCTSTR pszFormat, ...)
{
	UINT32					nBuf;
	TCHAR				szBuffer[512];
	const TCHAR		   *pszLocalFormat;

	pszLocalFormat = pszFormat;

	va_list args;
	va_start(args, pszFormat);

	nBuf = camVsnprintf( szBuffer, 512, pszLocalFormat, args );
	ASSERT(nBuf < sizeof(szBuffer));

#if 0

	if ((OutputDiagnostics == 1) && (AfxGetApp() != NULL))
		afxDump << AfxGetApp()->m_pszExeName << ": ";

	afxDump << szBuffer << "\n";
#else
	String_256 DiagOutput;

	if( OutputDiagnostics == 1 )
	{
		DiagOutput = AfxGetApp().GetAppName().c_str();
		DiagOutput += wxT(": ");
	}

	DiagOutput += szBuffer;
	DiagOutput += wxT("\n");

#if defined(__WXMSW__)
	OutputDebugString(DiagOutput);
#elif defined(__WXGTK__)
	camPrintf( DiagOutput );
#endif

#endif

	va_end(args);

}

