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

// NOTE: in separate module so it can replaced if needed.

#ifdef _ENSURES
int AssertBusy = FALSE;				  // for testing diagnostics			
#endif


/***********************************************************************************************

>	void EnsureFailedLine(LPCSTR AssertDescription, LPCSTR lpszFileName, int nLine)

	Author:		Simon M
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

void EnsureFailedLine(LPCTSTR AssertDescription, LPCSTR lpszFileName, int nLine)
{
#if 0 != wxUSE_UNICODE
	// Need to convert the filename string to TCHAR
	TCHAR tFile[512];
	camMbstowcs(tFile, lpszFileName, 512);
#else
	TCHAR * tFile = lpszFileName;
#endif

	TRACE(_T("Ensure failed at %s (%d): %s\n"), tFile, nLine, AssertDescription);
}
