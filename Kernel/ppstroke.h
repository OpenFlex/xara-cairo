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

// ppstroke - Definition of rendering PathProcessor classes for path Stroking

#ifndef INC_PPSTROKE
#define INC_PPSTROKE

#include "pathpcs.h"


class TrapsList;
class BecomeA;
class ValueFunction;
class CCAttrMap;

/********************************************************************************************

>	class PathProcessorStroke : public PathProcessor

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/12/96

	Purpose:	This is the abstract base class for all PathProcessors.

				These classes are created by attributes (or similar) when rendered,
				and placed on a stack in the RenderRegion. Whenever RenderRegion::DrawPath
				is invoked to render a path, all stacked PathProcessors will be called in
				turn, and they call back to RenderRegion functions to render whatever they
				wish (usually a modified form of the original path).

				This can be used to "filter" almost any rendering, but is mainly intended
				for use by stroke and fill providers, which replace input paths with more
				suitable shapes to be rendered.

	SeeAlso:	RenderRegion::DrawPath; PathProcessor::ProcessPath

********************************************************************************************/

class PathProcessorStroke : public PathProcessor
{
friend class RenderRegion;
CC_DECLARE_DYNAMIC(PathProcessorStroke);

public:
	PathProcessorStroke();

public:			// RenderRegion path-processing interface
	virtual void ProcessPath(Path *pPath,
							 RenderRegion *pRender,
							 PathShape ShapePath = PATHSHAPE_PATH);
	virtual BOOL WillChangeFillAndStrokeSeparately(void);

public:			// Specialised interface
	virtual BOOL IsDifferent(PathProcessorStroke *pOther);
			// Returns TRUE if the pOther is considered to be a different processor type

	virtual PathProcessorStroke *Clone(void);
			// Creates a copy of this object. Must be overridden by derived classes!

	virtual BOOL NeedsTransparency() const {return FALSE;};
			// Returns TRUE if this path processor makes use of transparency

	virtual BOOL DoBecomeA(BecomeA* pBecomeA, Path* pPath, Node* pParent);

	virtual BOOL DoesActuallyDoAnything(RenderRegion* pRender);

	virtual BOOL IsAPathProcessorStroke() {return TRUE;}

	NodePath*	GetProcessedPath(Path* pPath, Node* pParent);
	Path*		GetProcessedPath(Path* pPath, CCAttrMap* pAttrMap);

	NodePath* GetSmoothProcessedPath(Path* pPath, Node* pParent);

protected:	// Internal & derived-class helper functions
	TrapsList *PrepareTrapsForStroke(Path *pPath, RenderRegion *pRender, INT32 LineWidth);
			// Prepares a TrapsList structure for use with CreateVarWidthStroke

	Path *CreateVarWidthStroke(Path *pPath, RenderRegion *pRender, INT32 LineWidth,
								TrapsList *pTrapezoids = NULL);
			// Strokes pPath to produce an outline path for the stroke

	BOOL GetRequiredAttributes(	CCAttrMap* pAttrMap,
								INT32* pLineWidth,
								LineCapType* pLineCap,
								ValueFunction** ppValFunc,
								JointType* pJoinStyle );

	Path *CreateSmoothVarWidthStroke(Path *pPath, RenderRegion *pRender, INT32 LineWidth,
								TrapsList *pTrapezoids = NULL);
			// As above but creates a smoothed version of the stroke - better but slower

};

#endif

