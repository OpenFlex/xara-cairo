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

// Created by Markn 11/1/96
// Defines a class that will encapsulate lists of attributes.
//
// NOTE: It is derived from the MFC class CMapPtrToPtr.  This breaks rules to do with winoil/kernel cross-over
// but it doesn't make the old system any worse, which insidently, uses CMapPtrToPtr directly.
// This new class will allow common functions to be put in one place, and will also aid reimplementation
// if this becomes necessary.

#ifndef INC_ATTRMAP
#define INC_ATTRMAP

//#include "rndrgn.h"

class NodeRenderableInk;
class TransformBase;
class RenderRegion;


/********************************************************************************************

>	class CCAttrMap: public CMapPtrToPtr

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/1/95
	Purpose:	Class that encapsulates lists of attributes in Camelot

********************************************************************************************/

class CCAttrMap : public CCObject
{
	CC_DECLARE_DYNAMIC(CCAttrMap)

public:
	CCAttrMap(size_t nBlockSize = 10) { attrMapCreator = NULL; }

	// CMapPtrToPtr emulation
	typedef CMapPtrToPtr::iterator	iterator;
	inline iterator GetStartPosition()
	{
		return m_mapAttr.begin();
	}
	inline iterator GetEndPosition()
	{
		return m_mapAttr.end();
	}

	inline void GetNextAssoc( iterator &iter, CCRuntimeClass *&pClass, void *&pValue ) const
	{
		pClass	= (CCRuntimeClass *)iter->first;
		pValue	= iter->second;
		++iter;
	}

	inline bool Lookup( CCRuntimeClass *pKey, void *&pVal )
	{
		iterator	iter = m_mapAttr.find( pKey );
		if( m_mapAttr.end() == iter )
			return false;

		pVal = iter->second;
		return true;
	}

	bool RemoveKey( CCRuntimeClass *pKey )
	{
		iterator	iter = m_mapAttr.find( pKey );
		if( m_mapAttr.end() == iter )
			return false;

		m_mapAttr.erase( iter );
		return true;
	}

	void SetAt( CCRuntimeClass *pKey, void *pValue )
	{
		m_mapAttr[pKey] = pValue;
	}

	size_t GetCount() const
	{
		return m_mapAttr.size();
	}

	void RemoveAll()
	{
		return m_mapAttr.clear();
	}

	void DeleteAttributes();
	CCAttrMap* Copy();

	static CCAttrMap* MakeAppliedAttrMap(NodeRenderableInk* pInkNode,
										 BOOL ExcludeIndirectlyAppliedGLAs = TRUE,
										 BOOL bStrictEffectStatus = TRUE);

	// DMc 9/8/99
	void Render(RenderRegion* pRegion, BOOL RenderOffscreenAttributes = TRUE);

	void BuildListOfAttributes(List* pList);

	void Transform(TransformBase& Trans);

	// find me the attribute of type Class please (and return it)
	NodeAttribute* FindAttribute (NodeAttribute* pTypeAttr);

	// replaces an attribute reference in the map
	// returns the old attribute
	NodeAttribute* ReplaceAttribute(NodeAttribute* pNewAttr);

	// Removes and deletes 
	void RemoveAttribute(CCRuntimeClass* pAttrClass);

	//transformation function used for blends on paths and brushes
	void TransformForBrush(TransformBase& Trans);

	// special fn. for brushes - transforms the attributes not transformed in TransformForBrush
	void TransformBrushFills(TransformBase& Trans);

	BOOL WillScaleLineWidthToZero(TransformBase& Trans);

	// makes an attribute map from a render region
	static CCAttrMap* MakeAttrMapFromRenderRegion(RenderRegion* pRegion);

	// applies all attributes in the map to the node
	// NOTE doesn't normalise !
	void ApplyAttributesToNode(NodeRenderableInk* pNode);

	// Ilan 4/5/00
	void PostBlendInit(Path* pPath, CCRuntimeClass* pCreatorClass);
	void PostBlendDeinit();
	void AttachGeometryLinkedAttrs(Node* pContext);
	void RemoveGeometryLinkedAttrs();

	BOOL IsSeeThrough();

	Node* attrMapCreator;			// (test code):  whoever created the attrmap

private:
	CMapPtrToPtr		m_mapAttr;
};

#endif  // INC_ATTRMAP
