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


#include "camtypes.h"
#include "gla.h"

CC_IMPLEMENT_DYNAMIC( GeometryLinkedAttrValue, AttributeValue )

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************
>	GeometryLinkedAttrValue::
	Author:		Ilan_Copelyn (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/06/2000
	Purpose:	
	SeeAlso:	
********************************************************************************************/



/********************************************************************************************

>	virtual void GeometryLinkedAttrValue::SetLinkedNode(NodeRenderableBounded* pNode)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/10/2000
	Purpose:	Set our linked node.
				This fn is virtual so that subclasses, ie FeatherAttrValue, can do link-node
				dependent initialisation.
	Errors:		
	See also:	

********************************************************************************************/
void GeometryLinkedAttrValue::SetLinkedNode(NodeRenderableBounded* pNode)
{
	m_pLinkedNode = pNode;
}
