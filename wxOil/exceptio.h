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



/////////////////////////////////////////////////////////////////////////////
// operations to help in debugging. They are present in both retail and debug
// builds

class OpException : public Operation
{
	CC_DECLARE_DYNCREATE( OpException )

public:
	OpException();

	void Do(OpDescriptor*);

	static OpState GetState(String_256*, OpDescriptor*);

	static BOOL Init();
    inline static void BlowUpOnCrashMe()
		{
			if	( RenderTrap )
			{
				RenderTrap = FALSE ;
				volatile BYTE data;
				volatile BYTE * p = &data;
				*p = *lpByte;
			}
		}


private:
	static LPBYTE lpByte;
	static INT32 iZero[2];
	static double dZero[2];
	static BOOL	RenderTrap;
};

/*******************************************************************

>	void OpException::BlowUpOnCrashMe()

	Author: 	Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/02/94
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Cause an exception in rendering if we were meant to
	Errors:		-

This function is declared inline so it doesn't slow down every render
call

*******************************************************************/

#define	OPTOKEN_EXCEPTION_PTR	_T("CrashPtr")
#define	OPTOKEN_EXCEPTION_INT	_T("CrashInt")
#define	OPTOKEN_EXCEPTION_DBL	_T("CrashDbl")
#define OPTOKEN_EXCEPTION_REN	_T("CrashRen")


