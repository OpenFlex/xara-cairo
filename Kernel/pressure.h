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

// Pressure - functions for smoothing freehand pressure data

#ifndef INC_PRESSURE
#define INC_PRESSURE

class ValueFunction;
class Path;


/********************************************************************************************

>	class PressureSmoother : public CC_CLASS_MEMDUMP

	Author;		Jason
	Created:	30/1/97

	Purpose:	Given a bunch of pressure samples (from a graphics tablet, or simulated
				from mouse movements) this class provides methods to produce a ValueFunction
				object representing the variable-pressure information. The pressure
				information is smoothed to reduce the amount of data that needs to be saved,
				and to improve the quality of the pressure information (e.g. to get smooth
				pressure-pen strokes)

********************************************************************************************/

class PressureSmoother : public CC_CLASS_MEMDUMP
{
CC_DECLARE_MEMDUMP(PressureSmoother);

public:		// Construction/Destruction
	PressureSmoother();
	~PressureSmoother();


public:		// Main interface
	ValueFunction *Smooth(Path *pSourceData, INT32 LineWidth);
};


#endif

