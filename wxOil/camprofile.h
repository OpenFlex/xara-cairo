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


#ifndef INC_CAMPROFILE
#define	INC_CAMPROFILE

//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]

typedef enum
{
	CAMPROFILE_OTHER = 0,
	CAMPROFILE_GDRAW,
	CAMPROFILE_SHADOW,
	CAMPROFILE_BEVEL,
	CAMPROFILE_BLIT,

	CAMPROFILE_NONE				// Must be the last in the list
} CamProfileMode;

class CamProfiler;

/*******************************************************************************************

>	class CamProfile : public CCObject

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	24/11/2005
	Purpose:	To time various bits of the Camelot subsytem
	Notes:		In the OIL
	See Also:	CamProfiler

This class allows a limited degree of built in profiling of Camelot operations.

Around something you want to time, construct a new CamProfile object

So for instance:

	void myslowfunc()
	{
	... do something ...
	CamProfile myCamProfile(CAMPROFILE_MYSLOWFUNC)l

	... do the thing you want timed ...

	// Object destroyed as it goes out of scope.
	}

Note that you do not need a specific destructor. We cope with nested profiles in the
obvious manner. When an exception is thrown, Camelot at various points cleans off the
list of nested profiles. This may make them inaccurate.

********************************************************************************************/


class CamProfile : public CCObject
{
	CC_DECLARE_DYNCREATE( CamProfile )

	friend class CamProfiler;

public:
	CamProfile(CamProfileMode myMode = CAMPROFILE_NONE );
	virtual ~CamProfile();

	void SetMode(CamProfileMode myMode, BOOL Base = FALSE);

	static BOOL Init();
	static BOOL ClearList();
	static BOOL ResetCounters();
	static BOOL ActivateProfiling(BOOL Run = TRUE);
	static void AtBase(CamProfileMode myMode=CAMPROFILE_NONE);
	static void UpdateOilTimes();
	static void GetTimeString(TCHAR * pTime, UINT32 length);

private:
	// Prev and next pointers - don't use list class for speed and as lists are one obvious
	// thing we might wish to profile
	CamProfile* pPrev; // The next one on the list
	CamProfile* pNext; // The previous one the list

	CamProfileMode Mode;

	static CamProfile* pHead; // The head of the list
	static CamProfile* pTail; // The tail of the list
	static CamProfile* pCurrent; // The current profiler - almost inevitably the tail unless it's not running

	static BOOL Running;	
	static BOOL Inited;

	static CamProfile * OurHead; // Base member we allocate and thus can free

	UINT64 OilTime;
	static UINT64 LastOilTime;

	BOOL Zombie;	// Set on objects created whilst profiling isn't running

	static UINT64 OilTimeArray[CAMPROFILE_NONE];

};

/*******************************************************************************************

>	class CamProfiler : public CCObject

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	24/11/2005
	Purpose:	To report on time taken in various CamProfile sections
	Notes:		In the OIL
	See Also:	CamProfile

This class allows the user to maintain a set of timers that will be updated depending
on the time spent in Camelot in various CamProfile sections (see header for CamProfile).

To use:
	CamProfiler myProfile;

	... do some stuff ...

	double results[CAMPROFILE_NONE]
	myProfile->Read(results); // Read results in microseconds

All this class actually does is store the values of CamProfile::OilTimeArray array
when it's created, Read() then performs a subtraction to give the elapsed time
in each element.

********************************************************************************************/


class CamProfiler : public CCObject
{
	CC_DECLARE_DYNCREATE( CamProfiler )

public:
	CamProfiler();

	void Reset();
	double Read(double Results[CAMPROFILE_NONE]);

private:
	UINT64 OilTimeArray[CAMPROFILE_NONE];
	UINT64 FirstOilTime;
};


#endif

