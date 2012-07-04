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

// Definition of various units related stuff

#ifndef INC_UNITRES
#define INC_UNITRES

/*---------------------------------------------------------------------------------

	The defines below were calculated using the following facts :

		1 mile = 1.60934 kilometres
		1 mile = 1760 yards

	They define the number of millipoints in each of the default unit types supported by Camelot.

	(MarkN 8/3/94 & 28/6/94)
*/

#define MM_MP_VAL 	2834.652715			// Num millipoints in a millimetre
#define CM_MP_VAL	(MM_MP_VAL*10)		// Num millipoints in a centimetre
#define  M_MP_VAL	(CM_MP_VAL*100)		// Num millipoints in a metre
#define KM_MP_VAL	( M_MP_VAL*1000)	// Num millipoints in a kilometre

#define MP_MP_VAL	1.0					// Num millipoints in a millipoint (well, it's consistant)
#define PT_MP_VAL	(MP_MP_VAL*1000)	// Num millipoints in a computer point
#define PI_MP_VAL  	(PT_MP_VAL*12)		// Num millipoints in a pica
#define IN_MP_VAL	(PI_MP_VAL*6)		// Num millipoints in an inch
#define FT_MP_VAL	(IN_MP_VAL*12)		// Num millipoints in a foot
#define YD_MP_VAL	(FT_MP_VAL*3)		// Num millipoints in a yard
#define MI_MP_VAL	(YD_MP_VAL*1760)	// Num millipoints in a mile
#define PX_MP_VAL 	750.0				// Num millipoints in a pixel (1/96 inch)


// The following #defines echo the values defined in the enum specification in unittype.h.
// They are used in the units.ini file to all the units to specified in a more readable and changable way.
//
// It is important that they have the same value as the enums above. 
// (The program won't start up if they don't due to a validity checking function called DocUnitList::CheckUnitTypesValid())

#define UNIT_NOTYPE 		-1
#define UNIT_AUTOMATIC 		-2
#define UNIT_MILLIMETRES 	0
#define UNIT_CENTIMETRES 	1
#define UNIT_METRES		 	2
#define UNIT_INCHES		 	3
#define UNIT_FEET		 	4
#define UNIT_YARDS		 	5
#define UNIT_COMP_POINTS 	6
#define UNIT_PICAS		 	7
#define UNIT_MILLIPOINTS 	8
#define UNIT_MILES		 	9
#define UNIT_KILOMETRES	 	10
#define UNIT_PIXELS		 	11

#define UNIT_NUM_DEFAULT_TYPES 255

#endif // INC_UNITRES
