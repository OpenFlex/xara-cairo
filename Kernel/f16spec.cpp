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


// fixed16 code that will probably need changing between platforms
// (portable code can be found in fixed16.cpp). This is the Windows version



#include "camtypes.h"
#include "f16spec.h"
//#include "source.h"
#include <math.h>
//#include "andy.h"


#define	TORADIANS(x)	((x)/180.0*PI)

/********************************************************************************************

>	BOOL MathCoprocInstalled;

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/93
	SeeAlso:	InitMaths() 
	Purpose:	
		Flag used to determine if there is a maths coprocessor present. Its default setting 
		is FALSE i.e. there is no coprocessor installed. This is mainly used to hint GDraw
		how to do things most efficiently.
	
	Errors:		None.

********************************************************************************************/

static BOOL MathCoprocInstalled = FALSE;

// set this to 1 for the test. Disabled because we have yet to get a Pentium to try it on
#define	PENTIUM_TEST	0


#if PENTIUM_TEST
// Pentium FDIV bug test code
//
// Here is a simple test  that will reproduce the bug, if present;
// if this gives "256.000000" as result, your system is affected; on a 486,
// this gives "0.000000". The fn returns true if the FPU is OK

// (Note we have never seen this check go off as we have no Pentium machines)

static volatile double IFPBFFOd0=0;

static volatile double * IsFloatingPointBugFreeFoolOptimiser(volatile double * pdbl)
{
	if (pdbl) pdbl++;
	IFPBFFOd0 = *(--pdbl);
	return (pdbl); // This function just returns its own value.
}

// (This code obtained by Alex from somewhere on the net)

static BOOL IsFloatingPointBugFree()
{
    volatile double *w,*x,*y,*z;

	volatile double wd,xd,yd,zd;

	w=&wd;
	x=&xd;
	y=&yd;
	z=&zd;

	w=IsFloatingPointBugFreeFoolOptimiser(w);
	x=IsFloatingPointBugFreeFoolOptimiser(x);
	y=IsFloatingPointBugFreeFoolOptimiser(y);
	z=IsFloatingPointBugFreeFoolOptimiser(z);

    (*x) = 4195835.0;
    (*y) = 3145727.0;
    (*z) = ((*x)/(*y));

	w=IsFloatingPointBugFreeFoolOptimiser(w);
	x=IsFloatingPointBugFreeFoolOptimiser(x);
	y=IsFloatingPointBugFreeFoolOptimiser(y);
	z=IsFloatingPointBugFreeFoolOptimiser(z);

	(*z) = (*z) * (*y);

	w=IsFloatingPointBugFreeFoolOptimiser(w);
	x=IsFloatingPointBugFreeFoolOptimiser(x);
	y=IsFloatingPointBugFreeFoolOptimiser(y);
	z=IsFloatingPointBugFreeFoolOptimiser(z);

	(*w) = (*x) - (*z);

	w=IsFloatingPointBugFreeFoolOptimiser(w);
	x=IsFloatingPointBugFreeFoolOptimiser(x);
	y=IsFloatingPointBugFreeFoolOptimiser(y);
	z=IsFloatingPointBugFreeFoolOptimiser(z);

	return ((*w)<128.0);
}
#endif		// PENTIUM_TEST


/********************************************************************************************

>	BOOL IsMathCoprocInstalled()

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/1/95
	Returns:	TRUE if the hardware supports a real FPU, FALSE if emulated.
	Purpose:	Gives a hint to those that need to know things about FPU performance.
	Errors:		None.

********************************************************************************************/

BOOL IsMathCoprocInstalled()
{
#if defined(__WXMSW__)
	// the theoretically proper way to detect an FPU is to delve into the reigstry thus:
	// NT  entry lives at HKEY_LOCAL_MACHINE\HARDWARE\DESCRIPTION\System\FloatingPointProcessor\0
	// W95 entry lives at HKEY_LOCAL_MACHINE\Enum\Root\*PNP0C01\0000NDP (M7 liable to change)
	// W32s is only available by thunking to WinFlags() (ug).
	// Instead, we use a tiny bit of .asm, as suggested by Mr-Asm himself, Gavin

	WORD RegCR0;
	_asm
	{
		smsw	RegCR0					// bit 2 of CR0 is the EM bit, set for emulation
	}

	return (RegCR0 & 4) ? FALSE : TRUE;
#else
	return TRUE;
#endif
}

/********************************************************************************************

>	BOOL InitMaths()

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/93
	Inputs:		None.
	Outputs:	None
	Returns:	A Boolean if initialisation was ok.
	Purpose:	Initialises the maths class. Windows version tests for maths coprocessor.
				Also sets up maths exception vectors.
	Errors:		None.

********************************************************************************************/

BOOL InitMaths()
{

	MathCoprocInstalled = IsMathCoprocInstalled();

	#if PENTIUM_TEST
	// now check for faulty Pentium
	if ( !IsFloatingPointBugFree() )
	{
		Error::SetError( _R(IDE_BAD_PENTIUM) );
		InformError();
	}
	#endif

	return TRUE;
}          


/********************************************************************************************

>	FIXED16& FIXED16::Sin() 

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/5/93
	SeeAlso:	Fixed16Sin() 
	Inputs:		None.
	Outputs:	None
	Returns:	A reference to an FIXED16 with result of sin. Input argument must be in
				DEGREES not radians.
	Purpose:	Performs sine on a FIXED16.
	Errors:		None.

********************************************************************************************/

fixed16& fixed16::Sin() 
{
#ifndef WIN32
	if (MathCoprocInstalled)					//Is MathCoprocessor installed
		*this = Fixed16Sin(*this);
	else
#endif
		*this = sin(TORADIANS(this->MakeDouble()));

ERROR3("Alex doubts whether this routine works");

	return *this;
}

/********************************************************************************************

>	FIXED16& FIXED16::Cos() 

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/5/93
	SeeAlso:	Fixed16Cos()
	Inputs:		None.
	Outputs:	None
	Returns:	A reference to an FIXED16 with result of Cos. Input argument must be in
				DEGREES not radians.
	Purpose:	Performs Cos on a FIXED16.
	Errors:		None.

********************************************************************************************/

fixed16& fixed16::Cos() 
{
#ifndef WIN32
	if (MathCoprocInstalled)				//Is MathCoprocessor installed
		*this = Fixed16Cos(*this);
	else
#endif
		*this = cos(TORADIANS(this->MakeDouble()));

ERROR3("Alex doubts whether this routine works");

	return *this;
}
