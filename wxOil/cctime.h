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

// A time related class.

#ifndef INC_CCTIME
#define INC_CCTIME

class String_64;
class String_256;

struct cctime 
{
	INT32 tm_sec;     // seconds after the minute - [0,59]
	INT32 tm_min;     // minutes after the hour - [0,59]
	INT32 tm_hour;    // hours since midnight - [0,23]
	INT32 tm_mday;    // day of the month - [1,31]	
	INT32 tm_mon;     // months since January - [0,11]
	INT32 tm_year;    // years since 1900
	INT32 tm_wday;    // days since Sunday - [0,6]
	INT32 tm_yday;    // days since January 1 - [0,365] 
	INT32 tm_isdst;   // daylight savings time flag 
};


/*********************************************************************************************
           
>	class CCTimeBase : public CCObject

    Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
    Created:	21/08/96
    Purpose:	The base class local time generator. Normal time generators should be
				derived from this
	
**********************************************************************************************/  

class CCTimeBase : public CCObject
{
	CC_DECLARE_DYNCREATE(CCTimeBase)

	public:
		CCTimeBase();
		virtual ~CCTimeBase();

		virtual INT32 GetDay();
		virtual INT32 GetDayOfWeek();
		virtual INT32 GetMonth();
		virtual INT32 GetYear();
		virtual INT32 GetHour();
		virtual INT32 Get12Hour();
		virtual INT32 Get24Hour();
		virtual INT32 GetMinute();
		virtual INT32 GetSecond();
		
		virtual void GetCurrentTime() {};
		virtual void ConvertStandardDateAndTime(const String_64 *pFormat, String_256 *pOutput);

		const CCTimeBase& operator=(const CCTimeBase& timeSrc);

	protected:
		cctime* GetTimeStruct();

	private:
		cctime TheTime;
};



/*********************************************************************************************
           
>	class CCTime : public CCTimeBase

    Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
    Created:	21/08/96
    Purpose:	Creates a time object which can be interogated about the current time.
				If you create a static version of this object you will most likely need to
				use the GetCurrentTime() function on the object from time to time, otherwise
				it will inevitable become out of date as time and tide waits for no man.
				This is not a class to use to time funtions and such. Its accuracy is to
				the nearest second only.
				This version returns local time.
	SeeAlso:	CCGmtTime
	
**********************************************************************************************/  

class CCTime : public CCTimeBase
{
	CC_DECLARE_DYNCREATE(CCTime)

	public:
		CCTime();

		virtual void GetCurrentTime();
		virtual INT32  GetMonth();
};




/*********************************************************************************************
           
>	class CCGmtTime : public CCTimeBase

    Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
    Created:	21/08/96
    Purpose:	Creates a time object which can be interogated about the current time.
				If you create a static version of this object you will most likely need to
				use the GetCurrentTime() function on the object from time to time, otherwise
				it will inevitable become out of date as time and tide waits for no man.
				This is not a class to use to time funtions and such. Its accuracy is to
				the nearest second only.
				This version returns Greenwich Mean Time rather than Local time
	SeeAlso::	CCTime
	
**********************************************************************************************/  

class CCGmtTime : public CCTimeBase
{
	CC_DECLARE_DYNCREATE(CCGmtTime)

	public:
		CCGmtTime();

		virtual INT32 GetMonth();
		virtual INT32 GetYear();

		virtual void GetCurrentTime();
};



#endif



