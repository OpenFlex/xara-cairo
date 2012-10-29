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

//

#ifndef INC_GLA
#define INC_GLA

/////////////////////////////
// Geometry Linked Attributes
// Ilan 22/5/00
/////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////
//
//								AttributeValue classes
//
/////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************
>	class GeometryLinkedAttrValue : public AttributeValue
	Author:		Ilan_Copelyn (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/06/2000
	Purpose:	
	SeeAlso:	
 ********************************************************************************************/

class GeometryLinkedAttrValue : public AttributeValue
{
	CC_DECLARE_DYNAMIC(GeometryLinkedAttrValue)

public:
	GeometryLinkedAttrValue() { m_pLinkedNode = NULL; m_bDefault = FALSE; }
	~GeometryLinkedAttrValue() {};

	// preserves default flag to avoid confusion when copying CCAttrMaps
	virtual void SimpleCopy(AttributeValue *pOther)
		{ m_bDefault = ((GeometryLinkedAttrValue*)pOther)->m_bDefault; }

	virtual BOOL CanBeRenderedDirectly() { return (m_pLinkedNode!=NULL); }

	// Setting up geometry linkage - called via NodeAttribute::LinkToGeometry()
	virtual void SetLinkedNode(NodeRenderableBounded* pNode);
	NodeRenderableBounded* GetLinkedNode() { return m_pLinkedNode; }

	// Ensuring default attrs which are dynamic copied in CCAttrMaps dont get incorrectly linked
	// to nodes in the tree
	void SetDefault() { m_bDefault = TRUE; }
	BOOL IsDefaultFlagSet() { return m_bDefault; }

	// Member variables
protected:
	NodeRenderableBounded*		m_pLinkedNode;
private:
	BOOL						m_bDefault;
};

#endif //INC_GLA
