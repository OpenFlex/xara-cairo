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
*/ 

// Stardate 070494.10:25. Captain's Log - supplementary
// ====================================================
//
// 		Pirated fixed16 code to base fixed24 upon
// 		This was from revision 1.24 of fixed16.cpp
//												  Jason



#include "camtypes.h"



/********************************************************************************************

>	FIXED24 Fixed24Mul(FIXED24 arg1, FIXED24 arg2)

	Author: 	Gavin_Theobald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/6/2005
	Inputs:		two fixed24s
	Outputs:	None
	Returns:	FIXED24 result (arg1 * arg2)
	Scope:		Only to be used in the FIXED24 class.
	Purpose:	signed multiplication
	Errors:		None (no overflow checks). Rounds

********************************************************************************************/

fixed24 Fixed24Mul( fixed24 a, fixed24 b )
{
	fixed24				result;
	result.all = INT32((Int32x32To64(a.all,b.all)+0x800000)>>24) ;
	return result;
}

/********************************************************************************************

>	FIXED24 Fixed24Div(FIXED24 arg1, FIXED24 arg2)

	Author: 	Gavin_Theobald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/6/2005
	Inputs:		two fixed24s
	Outputs:	None
	Returns:	FIXED24 result (arg1 / arg2)
	Scope:		Only to be used in the FIXED24 class.
	Purpose:	signed division
	Errors:		None (no overflow checks). No rounding either (should it?)
			Overflow will cause a DIV0 exception, as will divide by zero

Note that this is not very efficient as it forces a multiply that
could instead be performed by a shift. The alternative is to use
int64s but this would then compile as a 64bit/64bit division which
is worse.

Why isn't there a Int64div32to32 function?

********************************************************************************************/

fixed24 Fixed24Div(fixed24 a,fixed24 b)
{
	fixed24 result ;
	result.all = MulDiv(a.all,1<<24,b.all) ;
	return result ;
}

/********************************************************************************************

>	double Fixed24ToDouble( FIXED24 arg )

	Author: 	Gavin_Theobald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/6/2005
	Inputs:		FIXED24 argument
	Outputs:	None
	Returns:	double-precision value
	Scope:		Only to be used in the FIXED24 class.
	Purpose:	General type conversion
	Errors:		None

This code relies on the compiler efficiently replacing the division by a multiplication
of the reciprical.

********************************************************************************************/

double Fixed24ToDouble( fixed24 a )
{
	return (double)a.all/(1<<24) ;
}

/********************************************************************************************

>	fixed24 DoubleToFixed24( double arg )

	Author: 	Gavin_Theobald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/6/2005
	Inputs:		double-precision argument
	Outputs:	None
	Returns:	FIXED24 value
	Purpose:	General type conversion
	Errors:		None (overflow will cause exception)

********************************************************************************************/

fixed24 DoubleToFixed24( double arg )
{
	fixed24 result ;
#if 0 //defined(_M_IX86)
	//
	// This avoids the slow fix operation. Add a large number so that
	// the double always has the same exponent and the mantissa becomes,
	// in affect, a fixed point value with the value we want in the
	// bottom 32 bits.
	//
	// Note that we are relying on the compiler to convert this to
	// efficient code.
	//
	// TODO: Test!
	//
	static const double fFix = (XLONG)3<<(DBL_MANT_DIG-24-2);
	double F = arg+fFix;
	result.all = (INT32&)F ;
#else
	result.all = INT32(arg*(1<<24)) ;
#endif
	return result ;
}
