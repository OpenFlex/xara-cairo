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

// pathpcs - Definition of rendering PathProcessor class

#ifndef INC_PATHPCS
#define INC_PATHPCS


class Path;
class RenderRegion;
class AttributeValue;


/********************************************************************************************

>	class PathProcessor : public CCObject

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

class PathProcessor : public CCObject
{
friend class RenderRegion;
CC_DECLARE_DYNAMIC(PathProcessor);

public:			// Construction/destruction
	PathProcessor();
	virtual ~PathProcessor();


public:			// RenderRegion path-processing interface
	virtual void ProcessPath(Path *pPath,
							 RenderRegion *pRender,
							 PathShape ShapePath = PATHSHAPE_PATH) = 0;
	virtual BOOL WillChangeFillAndStrokeSeparately(void);


public:			// "Parent Attribute" interface
	AttributeValue *GetParentAttr(void)				{ return(ParentAttr); };
	void SetParentAttr(AttributeValue *pParent)		{ ParentAttr = pParent; };
			// Set/Get the parent attribute pointer. Used by some derived classes to
			// remember the attribute which created this processor.


	virtual BOOL IsAPathProcessorBrush() { return FALSE;} // identifier
	virtual BOOL IsAPathProcessorStroke() { return FALSE;}

		// friend (RenderRegion) access functions - for stacking
	PathProcessor *GetNextProcessor(void)			{ return(NextProcessor); };
	void SetNextProcessor(PathProcessor *pNext)		{ ERROR3IF(pNext == this, "Awooga!"); NextProcessor = pNext; };

	virtual BOOL DoBecomeA(BecomeA* pBecomeA, Path* pPath, Node* pParent) {return FALSE;}

	virtual BOOL NeedsTransparency() const {return FALSE;};
			// Returns TRUE if this path processor makes use of transparency

	virtual BOOL DoesActuallyDoAnything(RenderRegion* pRender); 
			// returns TRUE if the PP actually alters the path to be rendered

	void SetDisabled(BOOL Value);
	BOOL IsDisabled();

public:
	virtual BOOL AllowsPropertiesDialog(void) {return FALSE;}
			// Returns TRUE if this path processor allows property editing via the gallery menu/dialog

private:
	PathProcessor *NextProcessor;			// 1-way linked list link for RenderRegion PP stack
	AttributeValue *ParentAttr;				// NULL, or pointer back to the AttributeValue which created us

	BOOL m_DisableMe; // flag which indicates whether or not we should disable ourselves
};

#endif

