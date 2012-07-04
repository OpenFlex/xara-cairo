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

// ppbevel - Definition of bevel PathProcessor class

#ifndef INC_PPBEVEL
#define INC_PPBEVEL

#include "beveler.h"
#include "pathpcs.h"

/********************************************************************************************

>	class BevelPathProcessor : public CCObject

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com> Mc
	Created:	12/11/98

	Purpose:	This is the bevel path processor. It is used to combine all the paths
				rendered so that the next bevel node can render them

	SeeAlso:	RenderRegion::DrawPath; PathProcessor::ProcessPath

********************************************************************************************/

class BevelPathProcessor : public PathProcessor
{
CC_DECLARE_DYNAMIC(BevelPathProcessor);

public:			// Construction/destruction
	BevelPathProcessor(BOOL bShrinkPath);
	~BevelPathProcessor();

	// The meaty bit !
	virtual void ProcessPath(Path *pPath,
							 RenderRegion *pRender,
							 PathShape ShapePath = PATHSHAPE_PATH);

	BOOL GetPathIsClosed() { return m_bIsPathClosed; }

protected:
	BOOL m_bShrinkPath;
	BOOL m_bIsPathClosed;
	
} ;

/********************************************************************************************

>	class BevelAttributePathProcessor : public CCObject

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com> Mc
	Created:	12/12/99

	Purpose:	This is the path processor which is used by the AttrBevelType node to
				do passbacks etc

	SeeAlso:	RenderRegion::DrawPath; PathProcessor::ProcessPath

********************************************************************************************/

class BevelAttributePathProcessor : public PathProcessor
{
CC_DECLARE_DYNAMIC(BevelAttributePathProcessor);
public:
	BevelAttributePathProcessor();
	~BevelAttributePathProcessor();

	void SetIndent(MILLIPOINT Indent) { m_Indent = Indent; }

	// The meaty bit !
	virtual void ProcessPath(Path *pPath,
							 RenderRegion *pRender,
							 PathShape ShapePath = PATHSHAPE_PATH);

	Path * GetSummedPath() { return &m_SummedPath; }
	Path * GetStrokedPath() { return & m_StrokedPath; }
private:
	Path m_SummedPath;
	Path m_StrokedPath;
	MILLIPOINT m_Indent;
};

class BevelHelpers : public CCObject
{
public:
	// helper function to shrink paths before rendering
	static void ShrinkPath(Path * pSrcPath, double amountX, double amountY,
									Path * pRetnPath, BOOL bTest = TRUE);

	// function to tell if the path is to be reversed
	static BOOL IsPathToBeReversed(Path * pPath);

	// eliminates the multiple points on the given path
	static void EliminateMultiplePoints(Path * pPath);
} ;

#endif
