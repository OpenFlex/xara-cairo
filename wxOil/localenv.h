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

// Calls to the host OS for environment infomation

#ifndef INC_LOCALENV
#define INC_LOCALENV


/********************************************************************************************

>	class LocalEnvironment : public CCObject

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>		
	Created:	30/08/94	
	Purpose:	Provide access to the locale settings Camelot is running under.	

********************************************************************************************/

class LocalEnvironment : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(LocalEnvironment);
public:
	static BOOL UpdateCachedInfo();

	static void GetNumberOfDecimalPlaces(UINT32* DecimalPlaces);
	static void GetThousandsSeparator(StringBase* String);
	static void GetDecimalPointChar(StringBase* String);
	static void SystemDateToString(StringBase* String, time_t *Time);
	static void SystemTimeToString(StringBase* String, time_t *Time);
	static UINT32 GetMouseDoubleClickDelay();
	static UINT32 GetXMouseDoubleClickMove();
	static UINT32 GetYMouseDoubleClickMove();

protected:
	static UINT32 MouseDoubleClickDelay;
	static UINT32 XMouseDoubleClickMove;
	static UINT32 YMouseDoubleClickMove;
};


/*********************************************************************************************
>	class LocaleChangedMsg : public Msg

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/95
	Purpose:	This message is sent whenever the locale information changes, eg keyboard
				layout, decimal character, etc...
	SeeAlso:	CMainFrame::OnWinIniChange
*********************************************************************************************/

class LocaleChangedMsg : public Msg
{
	CC_DECLARE_DYNAMIC(LocaleChangedMsg)

public:
	LocaleChangedMsg() {};
};


#endif  
