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

// ppvecstr - Definition of rendering PathProcessor classes for Vector Path Stroking

#ifndef INC_PPVECSTR
#define INC_PPVECSTR

#include "ppstroke.h"
#include "strkcomp.h"


/********************************************************************************************

>	class PathProcessorStrokeVector : public PathProcessorStroke

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/2/97

	Purpose:	A path processor which "moulds" vector clipart along a path.

				These classes are created by attributes (or similar) when rendered,
				and placed on a stack in the RenderRegion. Whenever RenderRegion::DrawPath
				is invoked to render a path, all stacked PathProcessors will be called in
				turn, and they call back to RenderRegion functions to render whatever they
				wish (usually a modified form of the original path).

				This can be used to "filter" almost any rendering, but is mainly intended
				for use by stroke and fill providers, which replace input paths with more
				suitable shapes to be rendered.

	Notes:		This processor is set up with a vector clipart "group" which it "moulds"
				along each stroke it renders in ProcessPath.

	SeeAlso:	RenderRegion::DrawPath; PathProcessor::ProcessPath;
				StrokeDefinition; StrokeComponent

********************************************************************************************/

class PathProcessorStrokeVector : public PathProcessorStroke
{
friend class RenderRegion;
CC_DECLARE_DYNAMIC(PathProcessorStrokeVector);

public:
	PathProcessorStrokeVector()		{ StrokeID = StrokeHandle_NoStroke; };

public:
	virtual void ProcessPath(Path *pPath,
							 RenderRegion *pRender,
							 PathShape ShapePath = PATHSHAPE_PATH);
	virtual BOOL WillChangeFillAndStrokeSeparately(void);
	virtual BOOL NeedsTransparency() const;
	virtual BOOL IsDifferent(PathProcessorStroke *pOther);
	virtual PathProcessorStroke *Clone(void);
	virtual BOOL AllowsPropertiesDialog(void) {return TRUE;}

public:
	void SetStrokeDefinition(StrokeHandle Handle);
	inline StrokeHandle GetStrokeDefinition(void) const		{ return(StrokeID); };

private:
	StrokeHandle StrokeID;
};


#endif

