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

#include "camtypes.h"
#include "pressure.h"

#include "pathtrap.h"
#include "valfunc.h"

DECLARE_SOURCE("$Revision: 1282 $");

CC_IMPLEMENT_MEMDUMP(PressureSmoother, CC_CLASS_MEMDUMP)


#define new CAM_DEBUG_NEW


/********************************************************************************************

>	PressureSmoother::PressureSmoother()

	Author;		Jason
	Created:	30/1/97
	Purpose:	Constructor

********************************************************************************************/

PressureSmoother::PressureSmoother()
{
}



/********************************************************************************************

>	PressureSmoother::~PressureSmoother()

	Author;		Jason
	Created:	30/1/97
	Purpose:	Destructor

********************************************************************************************/

PressureSmoother::~PressureSmoother()
{
}



/********************************************************************************************

>	ValueFunction *PressureSmoother::Smooth(Path *pSourceData, INT32 LineWidth)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/1/97
	Inputs:		pSourceData - The path containing the pressure data to smooth.
							  The pressure information should be held in the Width channel
							  in the ExtraInfo of the path

				LineWidth	- The maximum "radius" of the line (half the line width) which
							  will be used when stroking this path.

	Returns:	NULL if it failed (no error is set), else
				a pointer to a new ValueFunction object which represents the pressure
				information form this path. The caller is responsible for deleting this
				new object when they're finished with it.

	Purpose:	Reads raw recorded pressure information from a path and smooths it,
				creating a new ValueFunction object representing the pressure function.

	Notes:		Smoothing works as follows:
				1) Create a graph of the pressure samples, with pressure (y) versus
				   position along the path (x). Store this graph in a Path.

				2) Smooth the straight line segments in this graph into curve segments
				   At present, this is done by replacing everything between 2 local
				   minima/maxima by an S-shaped curve. This interpolation can be done by
				   a ValueFunctionPressureS object in real-time, so we create one of them.

********************************************************************************************/

ValueFunction *PressureSmoother::Smooth(Path *pSourceData, INT32 LineWidth)
{
	ERROR3IF(pSourceData == NULL, "Illegal NULL param");

	// Find the recorded pressure values (if any)
	PathWidth *pWidthArray = pSourceData->GetWidthArray();
	if (pWidthArray == NULL)
		return(NULL);

	const INT32 NumCoords	= pSourceData->GetNumCoords();
	DocCoord *pCoords	= pSourceData->GetCoordArray();

	if (NumCoords < 2)
		return(NULL);

	// Create a ValueFunction to return. We use an "S" curve interpolated pressure function
	ValueFunctionPressure *pValFunc = new ValueFunctionPressureS;
	if (pValFunc == NULL)
		return(NULL);

	// Calculate the maximum pressure value recorded. This should be EXTRAVALUEMAX
	// but sometimes we seem to get bigger values.
	INT32 MaxPressure = pWidthArray[0];
	for (INT32 i = 1; i < NumCoords; i++)
	{
		if (pCoords[i].y > MaxPressure)
			MaxPressure = pWidthArray[i];
	}

	// If this pressure was smaller than EXTRAVALUEMAX, then we use that as the maximum,
	// because we don't want to scale thin strokes up to max width!
	if (MaxPressure < (INT32)EXTRAVALUEMAX)
		MaxPressure = EXTRAVALUEMAX;

	float Position		= 0.0f;
	float LastPosition	= Position;
	INT32 Diff			= 0;
	INT32 LastDiff		= pWidthArray[1] - pWidthArray[0];

	pValFunc->AddPressure(Position, (float)pWidthArray[0] / (float)MaxPressure);

	// --- Now loop through the pressure samples, scaling them into the correct range, calculating
	// proper "position" values for them, and smoothing the data (by replacing all points between
	// minima and maxima with s-shaped interpolated segments)
	for (INT32 Index = 1; Index < NumCoords - 1; Index++)
	{
		// Record the pressure sample. We chuck away all samples between minima/maxima
		// as we go, and also wheedle out any zero-length sections that might crop up.
		// Then the ValueFunction will interpolate between the values as it sees fit (with S-shaped curves)
		if (Position > LastPosition)
		{
			LastPosition = Position;

			Diff = pWidthArray[Index] - pWidthArray[Index - 1];
			if ((Diff > 0 && LastDiff <= 0) || (Diff < 0 && LastDiff >= 0))
			{
				// We have found a min/maximum. Record this point.
				pValFunc->AddPressure(Position, (float)pWidthArray[Index] / (float)MaxPressure);
				LastDiff = Diff;
			}
		}

		// Work out approximate "travel" along the path so each width sample has a known position
		// [This should be calculated in the same way as in TrapEdgeList::ProcessEdgePositions, pathtrap.cpp]

#if TRUE
		// This now simply calculates distance down the centreline.
		// Much faster & simpler, and it turns out it gives better results after all!
		const double dx = (double) (pCoords[Index-1].x - pCoords[Index].x);
		const double dy = (double) (pCoords[Index-1].y - pCoords[Index].y);
		Position += (float) sqrt((dx * dx) + (dy * dy));
#else
	/*
		// Calculate the line normals to the left and right of the point
		NormCoord Normal1;
		NormCoord Normal2;
		Normal1.SetNormalToLine(pCoords[Index],		pCoords[Index - 1]);
		Normal2.SetNormalToLine(pCoords[Index + 1], pCoords[Index]);

		// Calculate the "left" parallel edge
		DocCoord P1(	pCoords[Index-1].x + (INT32)((double) LineWidth * Normal1.x),
						pCoords[Index-1].y + (INT32)((double) LineWidth * Normal1.y));
		DocCoord P2(	pCoords[Index  ].x + (INT32)((double) LineWidth * Normal2.x),
						pCoords[Index  ].y + (INT32)((double) LineWidth * Normal2.y));
		double dx = P1.x - P2.x;
		double dy = P1.y - P2.y;
		double LeftTravel = sqrt((dx * dx) + (dy * dy));

		// Calculate the "right" parallel edge
		P1 = DocCoord(	pCoords[Index-1].x - (INT32)((double) LineWidth * Normal1.x),
						pCoords[Index-1].y - (INT32)((double) LineWidth * Normal1.y));
		P2 = DocCoord(	pCoords[Index  ].x - (INT32)((double) LineWidth * Normal2.x),
						pCoords[Index  ].y - (INT32)((double) LineWidth * Normal2.y));
		dx = P1.x - P2.x;
		dy = P1.y - P2.y;
		double RightTravel = sqrt((dx * dx) + (dy * dy));

		// And increment Position by the larger of the 2 travel distances
		Position += (float)( (LeftTravel > RightTravel) ? LeftTravel : RightTravel );
*/
#endif
	}

	// And always add a knot at the very end of the curve
	pValFunc->AddPressure(Position, (float)pWidthArray[NumCoords - 1] / (float)MaxPressure);

	pValFunc->NormalisePositions();		// And normalise all positions to lie between 0.0 and 1.0

	return(pValFunc);
}

