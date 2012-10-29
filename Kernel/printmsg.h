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

// Printer message

#ifndef INC_PRINTMSG
#define INC_PRINTMSG



/*********************************************************************************************
>	class PrintMsg : public Msg

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/95
	Purpose:	This is sent when something to do with the printer has happend

*********************************************************************************************/
	

class PrintMsg : public Msg
{
	CC_DECLARE_DYNAMIC(PrintMsg)

public:

	// Print messages are send with these reasons
	enum PrintReason
	{
		SETTINGSCHANGED	// The printer settings have changed (via Print setup dialog - usually)
	};

	PrintReason	Reason;		// The message specifics, as enumerated above

	PrintMsg(PrintReason ThisReason) : Reason(ThisReason) { /* empty */ }
};


#endif	// INC_PRINTMSG

