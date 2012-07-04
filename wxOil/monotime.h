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
	monotime.h
	Created by Phil: 8th, July 1993

	Implements the MonotonicTime class

*/

/*
 * */

#ifndef INC_MONOTIME
#define INC_MONOTIME

/********************************************************************************************

>	class MonotonicTime

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/1993
	Base Class:	None
	Friends:	None
	Purpose:

	This class stores samples of the ever-increasing system ticker (the "monotonic clock" in
	Archy speak) and stores them. The samples can then be manipulated by member functions.

	Where times are passed in and out of these functions they are always given in
	milliseconds.

********************************************************************************************/

class CCAPI MonotonicTime
{
public:
	static	void	Init();		// Global initialisation
	
			MonotonicTime();					// Constructor that samples
			MonotonicTime(UINT32);				// Constructor that you set
//			~MonotonicTime();					// Destructor

	UINT32	Sample();							// Take a sample
	BOOL	Elapsed(UINT32);						// Test whether an amount of time has passed
	BOOL	Elapsed(UINT32, BOOL);				// Test whether an amount of time has passed

	operator UINT32();							// Cast to a UINT32 so math operations can be done

private:
	UINT32	SampleTime;							// The time the last sample was taken

	static wxStopWatch	s_stopwatch;

//#if defined(__WXGTK__) || defined(__WXMAC__)
//	UINT32	GetPosixTickCount() const;
//#endif

};



#endif
