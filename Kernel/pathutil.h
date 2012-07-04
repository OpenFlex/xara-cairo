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


// Header file for PathUtil.Cpp. Defines a class of related static
// functions which can be used for path element manipulation.

#ifndef INC_PATHUTILS
#define INC_PATHUTILS

const double SPLIT_EPSILON = 0.00005;

// define a structure to hold a single set of curve coefficients

typedef struct {
	double ax,ay;
	double bx,by;
	double cx,cy;
} PtCoefs;

// define a structure for single points

typedef struct { 
	double x, y; 
} Point2;

typedef Point2 Vector2;

#define SGN(a) (((a)<0) ? -1 : 0)		// Used by SqrDistanceToCurve only!
#define MIN(a,b) (((a)<(b))?(a):(b))	// "
#define MAX(a,b) (((a)>(b))?(a):(b))	// "

/********************************************************************************************

>	class PathUtil

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/8/94
	Purpose:   	Base class for path utility static functions. These functions operate on
				sections of paths, ie lists of doc coords, but do not process complete paths
				and hence cannot be included as member functions of the paths class.
				The class contains no member variables, just static member functions which
				would otherwise be global if not for the fabby idea of encompasing them
				together under a class structure.
	
********************************************************************************************/

class PathUtil 
{
public:
	static BOOL SplitLine(const double, const DocCoord*, UINT32*, PathVerb*, DocCoord* );
	static BOOL SplitCurve(const double, const DocCoord*, UINT32*, PathVerb*, DocCoord* );
	static void GetCurveCoefs(const DocCoord*, PtCoefs* );

	static DocCoord PointOnLine(const double, const DocCoord*);
	static DocCoord PointOnSemiCircle(const DocCoord& centre, const DocCoord& radialp, double t);
	static DocCoord PointOnCurve(double, const DocCoord*);

	static double SqrDistance(const DocCoord& p1, const DocCoord& p2);
	static double SqrDistanceToLine(const DocCoord*, const DocCoord&, double* );
	static double SqrDistanceToSemiCircle(const DocCoord*, const DocCoord&, double*);
	static double SqrDistanceToCurve(const UINT32, const DocCoord*, const DocCoord&, double* );

// old square distance to curve code
//	static double SqrDistanceToCurve(const UINT32, const DocCoord*, const DocCoord&, double* );
//	static double CurveClosestRange(const UINT32, PtCoefs*, const DocCoord&, double dx, double dy ,double* t,double* t0,double* t1);

};


#endif
