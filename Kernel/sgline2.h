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

/*

	sgline2.h

	This header contains declarations of the various classes derived from
	LineAttrItem, as used in the line-attributes gallery.
*/

#ifndef SGLINE2_H
#define SGLINE2_H

#include "sgline.h"
//#include "attr.h" - in camtypes.h [AUTOMATICALLY REMOVED]


/********************************************************************************************
>	class LineWidthItem : public LineAttrItem

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Purpose:	Represents a line-width user-interface item within the line gallery.
	SeeAlso:	-
********************************************************************************************/

class LineWidthItem : public LineAttrItem
{
public:
	// Creation & destruction.
	LineWidthItem(double nPointWidth, const String& strDescription);

private:
	// Overridables.
	virtual void SetAttributes(RenderRegion* pRegion) const;
	virtual NodeAttribute* CreateNewAttribute(BOOL fIsAdjust) const;
	virtual MILLIPOINT GetWidth() const;
	virtual CCRuntimeClass** GetAttribRuntimeClasses() const;
	virtual BOOL IsEqualValueToAny(NodeAttribute** ppOtherAttribs) const;

	// Data members.
	MILLIPOINT	m_nWidth;
};



/********************************************************************************************
>	class LineDashItem : public LineAttrItem

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Purpose:	Represents a line dash-pattern user-interface item within the line gallery.
	SeeAlso:	-
********************************************************************************************/

class LineDashItem : public LineAttrItem
{
public:
	// Creation & destruction.
	LineDashItem(StockDash nDashType, const String& strDescription);

private:
	// Overridables.
	virtual void SetAttributes(RenderRegion* pRegion) const;
	virtual NodeAttribute* CreateNewAttribute(BOOL fIsAdjust) const;
	virtual MILLIPOINT GetHeight() const;
	virtual CCRuntimeClass** GetAttribRuntimeClasses() const;
	virtual BOOL IsEqualValueToAny(NodeAttribute** pOtherAttribs) const;

	// Data members.
	StockDash	m_nDashType;
};



/********************************************************************************************
>	class LineArrowItem : public LineAttrItem

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Purpose:	Class to represent a arrowhead/tail user-interface item within the
				line gallery.
	SeeAlso:	-
********************************************************************************************/

class LineArrowItem : public LineAttrItem
{
public:
	// Creation & destruction.
	LineArrowItem(StockArrow nArrowType, double fpScale, const String& strDescription);

protected:
	// Implementation.
	virtual void SetAttributes(RenderRegion* pRegion) const;
	virtual void DrawItem(RenderRegion* pRegion, const DocRect& drBounds) const;
	virtual NodeAttribute* CreateNewAttribute(BOOL fIsAdjust) const;
	virtual MILLIPOINT GetWidth() const;
	virtual MILLIPOINT GetHeight() const;
	virtual MILLIPOINT GetHorzGap() const;
	virtual MILLIPOINT GetVertGap() const;
	virtual CCRuntimeClass** GetAttribRuntimeClasses() const;
	virtual BOOL IsEqualValueToAny(NodeAttribute** pOtherAttribs) const;

	// Override this to return TRUE if your item is a start arrow, FALSE if it is an
	// end-arrow.
	virtual BOOL IsStartArrow() const;

	// Data members.
	ArrowRec  m_arArrow;
	BOOL	  m_fCentred;

protected:
	// The base class returns TRUE, so that an item of this type will auto-close the gallery
	// when CTRL-double-clicked. However, this derived class (e.g. arrowheads) overrides
	// this to stop the gallery from auto-closing when a ctrl-double-click occurs.
	virtual BOOL ShouldCloseOnDoubleClick(void);
};



/********************************************************************************************
>	class LineNoArrowItem : public LineArrowItem

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/4/95
	Purpose:	Class to represent a no-arrowhead/tail user-interface item within the
				line gallery.  Only used as a base class for LineNoStartArrowItem and
				LineNoEndArrowItem
	SeeAlso:	-
********************************************************************************************/

class LineNoArrowItem : public LineArrowItem
{
protected:
	LineNoArrowItem(const String& strDescription);

private:
	virtual MILLIPOINT GetWidth() const;
	virtual MILLIPOINT GetHeight() const;
	virtual MILLIPOINT GetVertGap() const;
	virtual void SetAttributes(RenderRegion* pRegion) const;
	virtual void DrawItem(RenderRegion* pRegion, const DocRect& drBounds) const;
};



/********************************************************************************************
>	class LineNoStartArrowItem : public LineNoArrowItem

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/4/95
	Purpose:	Class to represent a no-start-arrowhead/tail user-interface item within the
				line gallery.
	SeeAlso:	-
********************************************************************************************/

class LineNoStartArrowItem : public LineNoArrowItem
{
public:
	LineNoStartArrowItem(const String& strDescription);

private:
	virtual BOOL IsEqualValueToAny(NodeAttribute** pOtherAttribs) const;
	virtual BOOL IsStartArrow() const;
};



/********************************************************************************************
>	class LineNoEndArrowItem : public LineNoArrowItem

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/4/95
	Purpose:	Class to represent a no-start-arrowhead/tail user-interface item within the
				line gallery.
	SeeAlso:	-
********************************************************************************************/

class LineNoEndArrowItem : public LineNoArrowItem
{
public:
	LineNoEndArrowItem(const String& strDescription);

private:
	virtual BOOL IsEqualValueToAny(NodeAttribute** pOtherAttribs) const;
	virtual BOOL IsStartArrow() const;
};



/********************************************************************************************
>	class LineCapItem : public LineAttrItem

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Purpose:	Represents a line-cap user-interface item within the line gallery.
	SeeAlso:	-
********************************************************************************************/

class LineCapItem : public LineAttrItem
{
public:
	// Creation & destruction.
	LineCapItem(LineCapType nCapType, const String& strDescription);

private:
	// Implementation.
	virtual void SetAttributes(RenderRegion* pRegion) const;
	virtual NodeAttribute* CreateNewAttribute(BOOL fIsAdjust) const;
	virtual CCRuntimeClass** GetAttribRuntimeClasses() const;
	virtual BOOL IsEqualValueToAny(NodeAttribute** pOtherAttribs) const;

	// Data members.
	LineCapType	m_nCapType;
};



/********************************************************************************************
>	class LineJoinTypeItem : public LineAttrItem

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Purpose:	Represents a line-join user-interface item within the line gallery.
	SeeAlso:	-
********************************************************************************************/

class LineJoinTypeItem : public LineAttrItem
{
public:
	// Creation & destruction.
	LineJoinTypeItem(JointType nJoinType, const String& strDescription);

private:
	// Overridables.
	virtual void SetAttributes(RenderRegion* pRegion) const;
	virtual void DrawItem(RenderRegion* pRegion, const DocRect& drBounds) const;
	virtual NodeAttribute* CreateNewAttribute(BOOL fIsAdjust) const;
	virtual CCRuntimeClass** GetAttribRuntimeClasses() const;
	virtual BOOL IsEqualValueToAny(NodeAttribute** pOtherAttribs) const;

	// Data members.
	JointType	m_nJoinType;
};

#endif	// !SGLINE2_H
