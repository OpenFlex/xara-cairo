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


/*
	monotime.cpp
	Created by Phil: 8th, July 1993

	Implements the MonotonicTime class
	This class stores samples of the ever-increasing system ticker (the "monotonic clock" in
	Archy speak) and stores them. The samples can then be manipulated by member functions.
	Where times are passed in and out of these functions they are alwasy given in
	milliseconds.

*/

/*
//*/

#include "camtypes.h"

DECLARE_SOURCE("$Revision: 1282 $");

wxStopWatch		MonotonicTime::s_stopwatch;

/********************************************************************************************

>	static void MonotonicTime::Init() 

	Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/02/2006
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	MonotonicTime initialiser
	Errors:		None

********************************************************************************************/

void MonotonicTime::Init()
{
	s_stopwatch.Start();
}




/********************************************************************************************

>	MonotonicTime::MonotonicTime() 

	Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	MonotonicTime class constructor
				Create an instance of the time class by taking a sample of MonotonicTime.
	Errors:		None

	
********************************************************************************************/
/*
	Technical notes:
	Calls Sample which in turn calls Windows 3.1 GetTickCount.

********************************************************************************************/

MonotonicTime::MonotonicTime()
{
	Sample();
}




/********************************************************************************************

>	MonotonicTime::MonotonicTime(MonotonicTime initialiser)

	Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	MonotonicTime class constructor
				Create an instance of the time class by setting it to the specified time
	Errors:		None

	
********************************************************************************************/
/*
	Technical notes:

********************************************************************************************/

MonotonicTime::MonotonicTime(UINT32 initialiser)
{
	SampleTime = initialiser;
}




/********************************************************************************************

>	UINT32 MonotonicTime::Sample()

	Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	The Sampled time
	Purpose:	Take a sample of "now" in monotonic time
	Errors:		None

	
********************************************************************************************/
/*
	Technical notes:
	Calls Windows 3.1 GetTickCount function.

********************************************************************************************/

UINT32 MonotonicTime::Sample()
{
#if defined(__WXMSW__)
	SampleTime = GetTickCount();
#elif defined(__WXGTK__) || defined(__WXMAC__)
//	SampleTime = count();
//	SampleTime = GetPosixTickCount();
	SampleTime = s_stopwatch.Time();
#else
	#pragma error( "Not impl'ed from this architechure" );
#endif

	return SampleTime;
}




/********************************************************************************************

>	BOOL MonotonicTime::Elapsed(UINT32 interval)

	Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	Flag saying whether interval has elapsed or not
	Purpose:	Test whether the given time interval has elapsed since the monotonic time was
				last sampled.
	Errors:		None

	
********************************************************************************************/
/*
	Technical notes:

********************************************************************************************/

BOOL MonotonicTime::Elapsed(UINT32 interval)
{
#if defined(__WXMSW__)
	return ( ( SampleTime + interval ) < GetTickCount() );
#elif defined(__WXGTK__) || defined(__WXMAC__)
//	return( ( SampleTime + ( interval * CLOCKS_PER_SEC / 1000 ) ) < (UINT32)clock() );
//	return ( ( SampleTime + interval ) < GetPosixTickCount() );
	return ((SampleTime +interval) < (UINT32)s_stopwatch.Time());
#else
	#pragma error( "Not impl'ed from this architechure" );
#endif
}




/********************************************************************************************

>	BOOL MonotonicTime::Elapsed(UINT32 interval, BOOL update)

	Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	Flag saying whether interval has elapsed or not
	Purpose:	Test whether the given time interval has elapsed since the monotonic time was
				last sampled. If the update flag is set then the sample time is reset to be
				the EXACT time when the interval was exceeded. This allows the interval to be
				regular and accurate in the long-term even though individual intervals will
				be subject to timing and sampling innaccuracies
	Errors:		None

	
********************************************************************************************/
/*
	Technical notes:

********************************************************************************************/

BOOL MonotonicTime::Elapsed(UINT32 interval, BOOL update)
{
	if ( Elapsed( interval ) )
	{
//#if defined(__WXGTK__)
//		interval = interval * CLOCKS_PER_SEC / 1000;
//#endif		

		if ( update )
			SampleTime += interval;

		return TRUE;
	}
	return FALSE;
}




/********************************************************************************************
>	UINT32 MonotonicTime::operator UINT32()

	Author: 	Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/12/95
	Inputs:		None
	Outputs:	None
	Returns:	The monotonic time expressed as a UINT32
	Purpose:	Cast operator that allows comparisons of MonotonicTime objects to be made
	Errors:		None
********************************************************************************************/
MonotonicTime::operator UINT32()
{
	return SampleTime;
}




/********************************************************************************************
>	UINT32 MonotonicTime::GetPosixTickCount() const

	Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/02/2006
	Inputs:		None
	Outputs:	None
	Returns:	The monotonic time extracted from the Posix library expressed as a UINT32
				in milliseconds
	Purpose:	Read high-quality monotonic timer value
	Errors:		None
********************************************************************************************/

//#if defined(__WXGTK__) || defined(__WXMAC__)
//// Should test that _POSIX_TIMERS > 0 && _POSIX_MONOTONIC_CLOCK > 0
//UINT32 MonotonicTime::GetPosixTickCount() const
//{
//	timespec ts;
//	clock_gettime(CLOCK_MONOTONIC, &ts);
//	return ts.tv_sec*1000+ts.tv_nsec/1000000;
//}
//#endif




