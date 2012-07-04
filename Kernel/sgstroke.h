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

// SGStroke.h - definitions for line gallery classes for handling new-style Stroke attributes

#ifndef INC_SGSTROKE
#define INC_SGSTROKE

#include "sgline.h"
#include "strkcomp.h" // for strokehandle


class StrokeTypeAttrValue;
class VariableWidthAttrValue;
class StrokeDefinition;

/********************************************************************************************

>	class StrokeTypeItem : public LineAttrItem

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/2/97
	Purpose:	Represents a stroke type user-interface item within the line gallery.

********************************************************************************************/

class StrokeTypeItem : public LineAttrItem
{
CC_DECLARE_DYNAMIC(StrokeTypeItem);

public:
	// Creation & destruction.
	StrokeTypeItem(StrokeTypeAttrValue *pStroke, const String &strDescription);
	~StrokeTypeItem();

public:
	// Access functions
	virtual StrokeTypeAttrValue *GetStrokeTypeAttrValue() {return pStrokeDef;}
	virtual StrokeDefinition *GetStrokeDefinition();
	virtual StrokeHandle GetStrokeHandle();
	virtual BOOL IsRepeating();
	virtual INT32 NumRepeats();
	virtual BOOL OverridesFill();
	virtual BOOL OverridesTrans();
	virtual void RenderItem(RenderRegion *pRender, DocRect *pDocRect, INT32 Width = c_nDefaultLineWidth);
	virtual void UpdateGalleryItem();

private:
	// Overridables.
	virtual void SetAttributes(RenderRegion* pRegion) const;
	virtual NodeAttribute* CreateNewAttribute(BOOL fIsAdjust) const;
	virtual MILLIPOINT GetWidth() const;
	virtual CCRuntimeClass** GetAttribRuntimeClasses() const;
	virtual BOOL IsEqualValueToAny(NodeAttribute** ppOtherAttribs) const;
	virtual MILLIPOINT GetHorzGap() const;
	
private:
	StrokeTypeAttrValue *pStrokeDef;
};



/********************************************************************************************

>	class VarWidthItem : public LineAttrItem

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/2/97
	Purpose:	Represents a stroke type user-interface item within the line gallery.

********************************************************************************************/

class VarWidthItem : public LineAttrItem
{
CC_DECLARE_DYNAMIC(VarWidthItem);

public:
	// Creation & destruction.
	VarWidthItem(VariableWidthAttrValue *pAttr, const String &strDescription);
	~VarWidthItem();

	void RenderAttributes (RenderRegion* pRegion) { SetAttributes (pRegion); }

private:
	// Overridables.
	virtual void SetAttributes(RenderRegion* pRegion) const;
	virtual NodeAttribute* CreateNewAttribute(BOOL fIsAdjust) const;
	virtual MILLIPOINT GetWidth() const;
	virtual CCRuntimeClass** GetAttribRuntimeClasses() const;
	virtual BOOL IsEqualValueToAny(NodeAttribute** ppOtherAttribs) const;
	virtual MILLIPOINT GetHorzGap() const;
	virtual BOOL ItemSelected (NodeAttribute* pAttr);
private:
	VariableWidthAttrValue *pAttrDef;
};

#endif

