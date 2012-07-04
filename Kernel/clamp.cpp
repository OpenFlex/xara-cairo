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





#include "camtypes.h"

#include "clamp.h"











///-------------------------------------------------------------------------------------------------
///	Author:			Harrison Ainsworth
///	Date:			05/99
///	Purpose:		Clamp a value to an interval.
///	Postconditions:	The return is within the interval [Min,Max]
///-------------------------------------------------------------------------------------------------

/*template< class T >
T  ClampBetween ( T ToBeClamped,  T Min, T Max )
{

	if( ToBeClamped < Min )
	{
		ToBeClamped = Min;
	}
	else
	if( ToBeClamped > Max )
	{
		ToBeClamped = Max;
	}

	return  ToBeClamped;

}*/


