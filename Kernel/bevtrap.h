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

#ifndef _BEVTRAP_H
#define _BEVTRAP_H

#include "pathproc.h"
#include "pathtrap.h"


class CCreateBevelTrapezoids : public CCObject
{
	CC_DECLARE_DYNCREATE(CCreateBevelTrapezoids);

public:
	// creates the bevel trap list
	BOOL ProcessTrapsForBevelling(Path *pPath, TrapsList *RetnTraps, INT32 indent, JointType jType,
							BOOL bOuter);

	// gives the inner point from a trap edge and puts it in dc
	static void CalcInnerPoint(TrapEdge * pEdge, INT32 indent, DocCoord * dc, BOOL bOuter);
	
#ifdef _DEBUG
	static void DumpList(TrapsList * pList);
#endif

	static BOOL CalculateIntersection(const DocCoord * start1, const NormCoord * dir1,
												   const DocCoord * start2, const NormCoord * dir2,
												   DocCoord * point, double * p, double * q);

	static void GetPathFromTraps(TrapsList * pTraps, const MILLIPOINT Width, Path * pPath);

	// elimintates the multiple points in the path
	static BOOL EliminateMultpilePoints(Path * pSrc, Path * pDest);	

	// calculates the intersection between two lines
private:

	// is this an outer turn on the path ?
	BOOL IsOuterTurn(NormCoord * nc1, NormCoord * nc2);

	// adds a given edge to the list
	BOOL AddEdgeToList(TrapEdgeList * pList, DocCoord * Centre, NormCoord * Normal, double Position,
							NormCoord * pNormal2=NULL);

	// smooths off the corners (otherwise they come out as being jaggy
	BOOL SmoothCorners(TrapsList * pList, TrapsList * RetnList, double Indent, BOOL bOuterBevel);

	// offsets index by 'offset', with maximum value being max-1
	// used to circle around the paths
	INT32 AlterIndex(INT32 index, INT32 max, INT32 offset);

	// creates the traps from the path
	BOOL ProcessPath(Path * pPath, TrapsList *RetnTraps, INT32 indent, BOOL bOuter, JointType jType);

	// creates a round join (recursive)
	void CreateRoundJoin(TrapEdgeList * pList, DocCoord * pCentre, 
											 NormCoord * pStartNorm, NormCoord * pEndNorm, 
											 INT32 depth = 0);

	// makes sure all inner points are at a consistant distance from the original path
	// based on where the outer points are
	void FlattenInnerPoints(TrapEdgeList * pList, INT32 indent, BOOL bOuter);

	// adds edges between centre 1 and centre 2 with the same inner point
	void RecursivelyAddEdges(TrapEdgeList * pList, DocCoord * pCentre1, DocCoord * pCentre2,
							 DocCoord * pInnerPoint, double MOneDivIndent, INT32 depth = 0);

} ;

#endif
