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

// Header file for the functions


#ifndef INC_FITCURVE
#define INC_FITCURVE

#include <math.h>

/********************************************************************************************

>	class FitPoint

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/03/94
	Purpose:	This class is really a vector class that is used by the curve fitting
				functions. It is also used as a coordinate class in the curve fitting
				functions, but these are really regarded as vectors from the origin.
				It has the following public member variables :-
				MonoOn double x;		- The X coord of the vector MonoOff
				MonoOn double y;		- The Y Coord of the vecotr MonoOff

********************************************************************************************/

class FitPoint : public CC_CLASS_MEMDUMP
{
	// Give my name in memory dumps
	CC_DECLARE_MEMDUMP(FitPoint);

public:
	// Construction
	FitPoint() {}
	FitPoint(double cx, double cy) { x=cx; y=cy;}
	FitPoint(DocCoord coord) { x=coord.x; y=coord.y; }
	FitPoint(const FitPoint& Other) {x=Other.x; y=Other.y;}

	// destruction
	~FitPoint() {}

	// operator =
	void operator = (const FitPoint& Other) { x=Other.x; y=Other.y; }
	void operator = (const DocCoord& Other) { x=Other.x; y=Other.y; }

	// Length Functions
	FitPoint SetLength( double NewLen );

	// Addition/Subtraction operators
	friend FitPoint operator + (const FitPoint& Point1, const FitPoint& Point2);
	friend FitPoint operator - (const FitPoint& Point1, const FitPoint& Point2);

	// Unary minus
	FitPoint operator - ();

	// Scale
	FitPoint operator * ( double Factor );

	// General geometry functions
	double SquaredLength()	{ return (x*x + y*y); }
	double Length()			{ return sqrt(x*x + y*y); }
	double Dot(const FitPoint& Other)	{ return (Other.x*x + Other.y*y); }

	// Debug functions
	void Dump();

public:
	double x;
	double y;
};





/********************************************************************************************

>	class CurveFitObject : public CC_CLASS_MEMDUMP

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/94
	Purpose:	Fits bezier curves to a serious of coordinates. Call the constructor,
				Initialise and finally FitCurve to fit a bezier curve to the coords.
	SeeAlso:	FitPoint

********************************************************************************************/

class CurveFitObject : public CC_CLASS_MEMDUMP
{
	// Give my name in memory dumps
	CC_DECLARE_MEMDUMP(CurveFitObject);

public:
	// Constructor that makes a note of things we will need to fit the curve
	CurveFitObject(Path* LongPath, double Error);
	~CurveFitObject();

	// Strip useful points out of the path and puts them in the array
	BOOL Initialise(Path* CopyPath, INT32 NumPoints);

	// Fit the curve
	void FitCurve();

// Private member functions to help out the above functions
private:
	// The heart of the curve fitting code
	void FitCubic( INT32 FirstPoint, INT32 LastPoint, FitPoint Tangent1, FitPoint Tangent2,
				   BOOL IsStartCusp = TRUE, BOOL IsEndCusp = TRUE);

	// The function that does the actual maths
	void GenerateBezier( INT32 FirstPoint, INT32 LastPoint, FitPoint Tangent1, FitPoint Tangent2, FitPoint* Bezier );

	// Functions to determine how close a fit we have
	FitPoint BezierPoint( FitPoint* Bez, double u );
	double   CalcMaxError( INT32 FirstPoint, INT32 LastPoint, FitPoint* Bezier, INT32* SplitPoint );

	// Functions to find the tangents to the curve at various points
	FitPoint LeftTangent(INT32 Start);
	FitPoint RightTangent(INT32 End);
	FitPoint CentreTangent(INT32 Centre);

	// Functions to evaluate various components of the bezier function
	double Bezier0(double u) { double t=1.0-u; return (t*t*t); }
	double Bezier1(double u) { double t=1.0-u; return (3*u*t*t); }
	double Bezier2(double u) { double t=1.0-u; return (3*u*u*t); }
	double Bezier3(double u) { return (u*u*u); }

	// Functions to put curve elements into the path
	void InsertBezier( FitPoint* Bezier, BOOL, BOOL);
	void InsertLine( const DocCoord& Start, const DocCoord& End, FitPoint Tangent1, FitPoint Tangent2, BOOL, BOOL);
	void InsertStraightLine(const DocCoord& End);

// Member vars
private:
	// Pointers to the actual path object to get and store the points in and an array to
	// hold the coords that we will use in the smoothing process
	Path* 		LongPath;
	DocCoord*	PathArray;
	INT32*		LineArray;

	// An array that holds the distance of each point from the start of the path
	INT32*		Distances;

	// The accuracy of the required fit. The larger this number, the smoother the fit.
	// Values of about 27,000,000 give smooth curves in millipoints at 100% zoom factor
	double		Error;

	// count of the total number of coordinates
	INT32 		TotalCoords;
	INT32			TotalStraightLines;
};

/********************************************************************************************

>	class FitCurveNoChangeGeometry : public CC_CLASS_MEMDUMP

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/1/2000
	Purpose:	This class uses the fit curve functionality to reduce the number of points
				in a path, whereas keeping the geometry as close to the original as possible

********************************************************************************************/
class FitCurveNoChangeGeometry : public CC_CLASS_MEMDUMP
{
	// Give my name in memory dumps
	CC_DECLARE_MEMDUMP(CurveFitObject);
public:
	static void SmoothPath(Path * pPath, double Error);
private:
	static void SmoothPathNoChangeGeometry(Path * pPath, double Error);
	static void EliminateColinearPointsFromPath(Path * pPath);
} ;

#endif


