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

/*
*/
#include "camtypes.h"

#include "localenv.h"


CC_IMPLEMENT_MEMDUMP(LocalEnvironment, CC_CLASS_MEMDUMP)
CC_IMPLEMENT_DYNAMIC(LocaleChangedMsg, Msg)

#define new CAM_DEBUG_NEW

UINT32 LocalEnvironment::MouseDoubleClickDelay;
UINT32 LocalEnvironment::XMouseDoubleClickMove;
UINT32 LocalEnvironment::YMouseDoubleClickMove;

PORTNOTE("other","Temporary ToUnicode, will be removed we Gerry checks in full impl.")
static inline TCHAR ToUnicode( char ch )
{
#if 0 != wxUSE_UNICODE
	TCHAR	tch;
	mbtowc( &tch, &ch, 1 );
	return tch;
#else
	return ch;
#endif
}

/********************************************************************************************

>	static void LocalEnvironment::GetNumberOfDecimalPlaces(UINT32* DecimalPlaces);

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/08/94
	Inputs:		DecimalPlaces - pointer to the UINT32 to store the number found in.
	Outputs:	-
	Returns:	-
	Purpose:	Call the OS to get the number of decimal places we should use to display
				numbers. Default is 2.
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
void LocalEnvironment::GetNumberOfDecimalPlaces(UINT32* DecimalPlaces)
{
	TCHAR TS[8];


PORTNOTE("other","Removed GetProfileString usage")
#if defined(__MSW__)
	GetProfileString("intl", "iDigits", "2", TS, sizeof(TS));
#else
#if 0
// AMB removed libiconv usage
	struct lconv *lc;
	lc = localeconv();
	TRACEUSER( "luke", _T("iDigits = %d\n"), lc->frac_digits );
	*DecimalPlaces = (UINT32)lc->frac_digits;
	return;
#else //0
	TS[0]=_T('2');
	TS[1]=0;
#endif //0
#endif

	// Convert the string into a number that the string represents which we
	// can then return to the caller.
	TCHAR* pszMark;
	*DecimalPlaces = camStrtol( TS, &pszMark, 10 );
}

/********************************************************************************************

>	static void LocalEnvironment::GetThousandsSeparator(StringBase* String)

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/08/94
	Inputs:		String - pointer to the string to store the separator in.
	Outputs:	-
	Returns:	-
	Purpose:	Call the OS to get the character used as a thousands separator.	 Default
				separator is ",".
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
void LocalEnvironment::GetThousandsSeparator(StringBase* String)
{
	*String = wxLocale::GetInfo(wxLOCALE_THOUSANDS_SEP, wxLOCALE_CAT_NUMBER);
}

/********************************************************************************************

>	static void LocalEnvrionment::GetDecimalPointChar(StringBase* String)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/1/95
	Inputs:		String - pointer to the string to store the decimal point character in.
	Outputs:	-
	Returns:	-
	Purpose:	Call the OS to get the character used as a decimal point character.	 Default
				decimal point character is ".".
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
void LocalEnvironment::GetDecimalPointChar(StringBase* String)
{
	*String = wxLocale::GetInfo(wxLOCALE_DECIMAL_POINT, wxLOCALE_CAT_NUMBER);
}

#if !defined(EXCLUDE_FROM_RALPH) && !defined(EXCLUDE_FROM_XARALX)
/********************************************************************************************

>	static void LocalEnvrionment::SystemDateToString(StringBase* String, time_t* Time)

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com> (but copied from Andy's code)
	Created:	31/08/94
	Inputs:		String - pointer to the string to store the time in.
				Time - the time and date in an ANSI time_t structure.
	Outputs:	-
	Returns:	-
	Purpose:	Produce a formatted string representing a date.  The format to use is read
				from the OS (and thus is locale dependent).
	Errors:		-
	SeeAlso:	SystemTimeToString
															
********************************************************************************************/
void LocalEnvironment::SystemDateToString(StringBase* String, time_t* Time)
{
	TCHAR c;
	TCHAR TimeFormat[40];
	TCHAR Temp[40];
	TCHAR Bodge[2];
	LPTCHAR p = TimeFormat;
	tm*	TimeParts = localtime(Time);
	INT32 digits;

	GetProfileString("Intl", "sShortDate", "dd/MM/yy", TimeFormat, sizeof(TimeFormat));
	String->Empty();
	Bodge[1] = 0;

	while (c=*p++)
	{
		Bodge[0] = c;
		TCHAR* AnotherBodge = CharUpper(Bodge);
		TCHAR uc = *AnotherBodge;
		digits = 1;

		// this code relies on the same case being used throughout the field (e.g. ddDD will fail)
		while (c == *p)
		{
			c = *p++;
			digits ++;
		}
		switch (uc)
		{
			case TEXT('D') :
				if (digits == 1)
				{
					wsprintf(Temp, "%d", TimeParts->tm_mday);
				}
				else
				{
					wsprintf(Temp, "%02d", TimeParts->tm_mday);
				}
				break;	
			case TEXT('M') :
				if (digits == 1)
				{
					wsprintf(Temp, "%d", TimeParts->tm_mon+1);
				}
				else
				{
					wsprintf(Temp, "%02d", TimeParts->tm_mon+1);
				}
				break;	
			case TEXT('Y') :
				if (digits == 2)
				{
					wsprintf(Temp, "%02d", TimeParts->tm_year % 100);
				}
				else
				{
					wsprintf(Temp, "%d", TimeParts->tm_year+1900);
				}
				break;
		}
		*String += Temp;
		if (*p != 0)
		{
			Bodge[0] = *p++;
			*String += Bodge;
		}
	}
}



/********************************************************************************************

>	static void LocalEnvrionment::SystemTimeToString(StringBase* String, time_t* Time)

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com> (but copied from Andy's code)
	Created:	31/08/94
	Inputs:		String - pointer to the string to store the time in.
				Time - the time and date in an ANSI time_t structure.
	Outputs:	-
	Returns:	-
	Purpose:	Produce a formatted string representing a time.  The format to use is read
				from the OS (and thus is locale dependent).
	Errors:		-
	SeeAlso:	SystemDateToString

********************************************************************************************/
void LocalEnvironment::SystemTimeToString(StringBase* String, time_t* Time)
{
	TCHAR Format[20];
	TCHAR Temp[40];
	TCHAR Separator[10];
	INT32 Hours;
	BOOL Trail = FALSE;
	tm*	TimeParts = localtime(Time);

	Hours = TimeParts->tm_hour;

	GetProfileString("Intl", "iTime", "", Format, sizeof(Format));
	if (Format[0]=='0')
	{	// 12 hour clock wanted
		if (Hours>=12)
		{
			Trail = TRUE;
		}
		if (Hours>12)
		{
			Hours -= 12;
		}
	}
	else
	{	// 24 hour format
		Trail = TRUE;				
	}
	GetProfileString("Intl", "iTLZero", "1", Format, sizeof(Format));
	if (Format[0]=='1')
	{	// leading zeros please
		wsprintf(Temp, "%02d", Hours);
	}
	else
	{
		wsprintf(Temp, "%d", Hours);
	}
	*String = Temp;
	GetProfileString("Intl", "sTime", ":", Separator, sizeof(Separator));
	wsprintf(Temp, "%s%02d%s%02d", Separator, TimeParts->tm_min,
															Separator, TimeParts->tm_sec);
	*String += Temp;
	if ((TimeParts->tm_hour < 12) && GetProfileString("Intl", "s1159", "",
																	Format, sizeof(Format)))
	{
		wsprintf(Temp, "%s", Format);
		*String += Temp;
	}
	if (Trail && GetProfileString("Intl", "s2359", "", Format, sizeof(Format)))
	{
		wsprintf(Temp, "%s", Format);
		*String += Temp;
	}
}
#endif


/********************************************************************************************
>	static BOOL LocalEnvironment::UpdateCachedInfo()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/95
	Inputs:		-
	Outputs:	-
	Returns:	TRUE/FALSE for success/failure
	Purpose:	Call to (re)cache info held in this class.  Obviously call on startup, and
				also when the user changes the machine settings
	Errors:		-
	SeeAlso:	-
********************************************************************************************/
BOOL LocalEnvironment::UpdateCachedInfo()
{
	// Get max time between two clicks making double clicks
PORTNOTE("other","Removed GetProfileString usage")
#ifndef EXCLUDE_FROM_XARALX
	MouseDoubleClickDelay = ::GetProfileInt("Windows","DoubleClickSpeed", 452);
#else
	MouseDoubleClickDelay = 452;
#endif

	// Get max movement between two clicks making double clicks
	XMouseDoubleClickMove = wxSystemSettings::GetMetric( wxSYS_DCLICK_X );
	YMouseDoubleClickMove = wxSystemSettings::GetMetric( wxSYS_DCLICK_X );

	return TRUE;
}



/********************************************************************************************
>	static UINT32 LocalEnvironment::GetMouseDoubleClickDelay()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/95
	Inputs:		-
	Outputs:	-
	Returns:	Max time (in milliseconds) allowed between two clicks composing a double click
	Purpose:	Gets the maximum time allowed between two clicks that make up a double click
	Errors:		-
	SeeAlso:	-
********************************************************************************************/
UINT32 LocalEnvironment::GetMouseDoubleClickDelay()
{
	return MouseDoubleClickDelay;
}



/********************************************************************************************
>	static UINT32 LocalEnvironment::GetXMouseDoubleClickMove()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/95
	Inputs:		-
	Outputs:	-
	Returns:	Max horizontal movement allowed between two clicks composing a double click
	Purpose:	Returns the maximum allowed movment (in mouse units) between two clicks that
				compose a double click
	Errors:		-
	SeeAlso:	-
********************************************************************************************/
UINT32 LocalEnvironment::GetXMouseDoubleClickMove()
{
	return XMouseDoubleClickMove;
}



/********************************************************************************************
>	static UINT32 LocalEnvironment::GetYMouseDoubleClickMove()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/95
	Inputs:		-
	Outputs:	-
	Returns:	Max vertical movement allowed between two clicks composing a double click
	Purpose:	Returns the maximum allowed movment (in mouse units) between two clicks that
				compose a double click
	Errors:		-
	SeeAlso:	-
********************************************************************************************/
UINT32 LocalEnvironment::GetYMouseDoubleClickMove()
{
	return YMouseDoubleClickMove;
}
