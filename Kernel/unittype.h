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

// Definition of the default unit type enum

#ifndef INC_UNITTYPE
#define INC_UNITTYPE

// Units that Camelot can understand by default
typedef enum
{
	NOTYPE 		= -1,			// The type with no name
	AUTOMATIC 	= -2,			// Special type that can be used when setting the scale units
	MILLIMETRES = 0,
	CENTIMETRES,
	METRES,		
	INCHES,		
	FEET,		
	YARDS,
	COMP_POINTS,				// Computer Points (exactly 1/72 inch)
	PICAS,
	MILLIPOINTS,
	MILES,
	KILOMETRES,
	PIXELS,
	NUM_DEFAULT_UNIT_TYPES = 255	// Number of default unit types in Camelot
								// Add new ones before this value
								// (****NOTE****: remember to change/add the #defines below)
} UnitType;


// The following #defines echo the values defined in the above enum specification.
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

#endif // INC_UNITTYPE
