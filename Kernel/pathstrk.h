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

// Definition of Path Stroking classes (used in stroke providing)

#ifndef INC_PATHSTRK
#define INC_PATHSTRK

#include "pathtrap.h"

#include "strkcomp.h"

class DocCoord;
class ValueFunction;
class Node;


///////////////////////////////////////////////////////////////////////////////////////////
// Base class
///////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************************

>	class PathStroker : public CC_CLASS_MEMDUMP

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/12/96

	Purpose:	Abstract Base class
				Converts a Trapezoid (See ProcessPathToTrapezoids, pathtrap.h) stroke
				definition into an output path.

				The base class strokes a path with variable-width

******************************************************************************************/

class PathStroker : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(PathStroker);

public:			// Construction/Destruction
	PathStroker();
	PathStroker(ValueFunction *WidthFunction, INT32 LineWidth, LineCapType CapType);
	virtual ~PathStroker() { }

public:			// Public interface
	virtual BOOL StrokePath(TrapsList *pTraps, Path *pOutput);
			// Go forth and stroke thine path

	// Smoothed version of above...
	virtual BOOL StrokeSmoothPath(TrapsList *pTraps, Path *pOutput);


protected:		// Internal helper functions
	BOOL MapLineForwards(TrapEdgeList *Traps, Path *pOutput);
	void RecursiveMapLineForwards(	TrapEdge *pEdge1, DocCoord &Point1,
									TrapEdge *pEdge2, DocCoord &Point2,
									Path *pOutput);

	BOOL MapLineBackwards(TrapEdgeList *Traps, Path *pOutput);
	void RecursiveMapLineBackwards(	TrapEdge *pEdge1, DocCoord &Point1,
									TrapEdge *pEdge2, DocCoord &Point2,
									Path *pOutput);

	BOOL MapLineCap(LineCapType CapType, TrapEdge *pEdge, BOOL IsStartCap,
									Path *pOutput);

protected:
	ValueFunction *pWidthFunction;					// ValueFunction providing width information
	INT32 MaxWidth;									// Maximum width (in millipoints) of the stroke
	LineCapType CapStyle;							// Line cap style (butt, round, or square)
	INT32 RecursionDepth;							// Recursion depth counter to avoid stack overflows
};





///////////////////////////////////////////////////////////////////////////////////////////
// Derived classes
///////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************************

>	class PathStrokerVector : public PathStroker

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/2/97

	Purpose:	Path stroker
				Converts a Trapezoid (See ProcessPathToTrapezoids, pathtrap.h) stroke
				definition into an output path.

				This "moulds" all the elements (beziers/lines) of a given path to lie
				within a stroke envelope defined by the provided trapezoid list

******************************************************************************************/

class PathStrokerVector : public PathStroker
{
	CC_DECLARE_MEMDUMP(PathStrokerVector);

public:
	PathStrokerVector(ValueFunction *WidthFunction, INT32 LineWidth,
						LineCapType CapType, DocRect *pSourceBounds);

public:			// Public interface
	void PrepareToStroke(TrapEdgeList *pTraps);
			// Prepare for stroking. Must be called before StrokePath/MapCoord

	virtual BOOL StrokePath(TrapsList *pTraps, Path *pOutput);	// DO NOT USE this version!
	virtual BOOL StrokePath(Path *pSourceVector, Path *pOutput);
			// Go forth and stroke thine path

	DocCoord MapCoord(DocCoord *pCoord);
			// Maps a coordinate across from the source space to the output space
			// Called internally, and also from FillGeometryAttribute::MouldIntoStroke

	double GetScaleFactor(void);
			// Returns a scaling factor indicating how much larger/smaller the mapped
			// brush is than it was in the original brush definition. This is used
			// to scale line widths etc to keep aspect ratios approximately correct.

protected:		// Internal helper functions
	void FindEdgeForCoord(DocCoord *pCoord, UINT32 StartIndex, INT32 Direction,
							/* TO */ TrapEdge *pOutput);
			// Computes a TrapEdge structure for the exact Position of a source Coord

	void MapMove(DocCoord *pCoord);
	void MapLine(DocCoord *pCoord1, DocCoord *pCoord2);
	void MapBezier(DocCoord *pCoords);
			// Map a Move/Line/BezierTo into the output path

	void RecursiveMapLine(TrapEdge *pEdge1, DocCoord &Point1, double Width1,
						  TrapEdge *pEdge2, DocCoord &Point2, double Width2,
						  INT32 Direction, Path *pOutput);
			// Recursively maps points from a straight line onto the stroke

	void RecursiveMapBezier(DocCoord *pCoords,	DocCoord *p1, double t1,
												DocCoord *p2, double t2);
			// Recursively maps points from a bezier onto the stroke

//////////////////////////////////////////////////////////////////////////////
public:
	static StrokeHandle GetCurrentBrush(void);
			// Returns the current brush. If there isn't one, it builds one

	static void BodgeRipSelection(BOOL Repeating = FALSE);
			// ****!!!! BODGE - will be moved elsewhere later. Rips the selection
			// out of the document and uses it as the new stroke brush
	static StrokeHandle CurrentStroke;
//////////////////////////////////////////////////////////////////////////////


private:		// Member globals to save passing loads of parameters
	Path		*pPath;								// Current source path from the brush
	DocRect		*pBounds;							// Bounds of the brush
	double		BoundsWidth;						// Cached width of the bounds
	double		BoundsHalfHeight;					// Cached half-height of the bounds
	double		BoundsYCentre;						// Cached centre (Y) of the bounds

	Path		*pOutput;							// Path to recieve mapped output data

	TrapEdgeList*pCurrentEdgeList;					// Currently active trapezoid edge list
	UINT32 FirstEdge;									// First trapedge containing the current path
	UINT32 LastEdge;									// Last trapedge containing the current path
};


#endif

