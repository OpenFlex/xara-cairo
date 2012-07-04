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

// ppairbsh - Definition of rendering PathProcessor classes for Airbrushed Path Stroking

#ifndef INC_PPAIRBSH
#define INC_PPAIRBSH

#include "ppstroke.h"

class View;
class GRenderBitmap;
class ValueFunction;

/********************************************************************************************

>	class PathProcessorStrokeAirbrush : public PathProcessor

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com> & Richard
	Created:	20/12/96

	Purpose:	A path processor which renders paths as airbrushed strokes

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

class PathProcessorStrokeAirbrush : public PathProcessorStroke
{
friend class RenderRegion;
CC_DECLARE_DYNAMIC(PathProcessorStrokeAirbrush);


public:			// RenderRegion path-processing interface
	PathProcessorStrokeAirbrush()					{ pIntensityFunction = NULL; };
	~PathProcessorStrokeAirbrush();

	virtual void ProcessPath(Path *pPath,
							 RenderRegion *pRender,
							 PathShape ShapePath = PATHSHAPE_PATH);

	virtual BOOL WillChangeFillAndStrokeSeparately(void);


public:			// Specialised interface
	virtual BOOL IsDifferent(PathProcessorStroke *pOther);
			// Returns TRUE if the pOther is considered to be a different processor type

	virtual PathProcessorStroke *Clone(void);
			// Creates a copy of this object. Must be overridden by derived classes!

	virtual BOOL NeedsTransparency() const {return TRUE;};
			// This processor needs transparency (like no tomorrow, etc...)


protected:
	// Get the number of steps to use for this stroke
	virtual INT32 GetNumSteps(View *pView, INT32 LineWidth);

	// Construct a greyscale palette
	LOGPALETTE *MakeGreyScalePalette(void);

	// Actually render the airbrush
	virtual BOOL RenderAirBrush(Path *pPath, GRenderBitmap *pRegion, INT32 LineWidth,
			INT32 NumSteps, ValueFunction *pvValueFunction, RenderRegion *pDestRegion,
			PathShape ShapePath);

public:		// Specialised interface
	ValueFunction *GetIntensityFunction(void);
	void SetIntensityFunction(ValueFunction *pFunc);


private:
	ValueFunction *pIntensityFunction;			// A ValueFunction describing the airbrush intensity curve

};

#endif

