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


// Line Gallery interface for Brush Attributes - header

#ifndef SGBRUSH
#define SGBRUSH

#include "sgline.h"
#include "brshattr.h"
#include "brshcomp.h"

/********************************************************************************************

>	class BrushAttrItem : public LineAttrItem

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/2000
	Purpose:	Represents a brush attribute user-interface item within the line gallery.

********************************************************************************************/

class BrushAttrItem : public LineAttrItem
{
CC_DECLARE_DYNAMIC(BrushAttrItem);

public:
	// Creation & destruction.
	BrushAttrItem(BrushAttrValue *pBrush, const String &strDescription);
	~BrushAttrItem();

public:
	// Access functions
	virtual BrushAttrValue *GetBrushAttrValue() { return m_pBrushAttrVal;}
	virtual BrushDefinition *GetBrushDefinition();
	virtual BrushHandle GetBrushHandle();
	
public: //various overridables
	virtual void RenderItem(RenderRegion *pRender, DocRect *pDocRect, INT32 Width = c_nDefaultLineWidth);
	virtual void UpdateGalleryItem();

	// performs various actions necessary prior to selection
	virtual BOOL ItemSelected(NodeAttribute* pNewAttr);


public:
	BOOL IsEqualValueToAny(NodeAttribute** ppOtherAttribs) const;	
	BOOL UpdateProcessor();
protected:
	// Overridables.
	virtual void SetAttributes(RenderRegion* pRegion) const;
	void DrawItem(RenderRegion* pRegion, const DocRect& drBounds) const;
	virtual NodeAttribute* CreateNewAttribute(BOOL fIsAdjust) const;
	virtual CCRuntimeClass** GetAttribRuntimeClasses() const;

	// finds the current default brush attribute
	BrushHandle GetCurrentDefaultBrushHandle();

private:
	BrushAttrValue *m_pBrushAttrVal;
};


#endif
