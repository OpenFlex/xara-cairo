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
	$Header: /wxCamelot/Kernel/ngscan.h 8     20/07/05 15:39 Luke $
	Scans and iterations to find, apply and hide Wix ObjectName attributes to nodes.
*/

#ifndef NGSCAN_H
#define NGSCAN_H

#include "ngiter.h"
#include <list>

class ObjectChangeParam;
class NodeSetProperty;
class NamedStretchProp;
class SGUsedNames;


/***********************************************************************************************
>	class CCAPI BaseSelectScan : public NodeScan

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/5/99
	Purpose:	Base class for scans which select objects which are in the SGNameItem sets.
	SeeAlso:	SelectScan; SelectUnionScan; SelectIntersectScan
***********************************************************************************************/

class CCAPI BaseSelectScan : public NodeScan
{
public:
	enum Change { TOGGLE = -1, DESELECT, SELECT, SELECT_EXCLUSIVE };

	BaseSelectScan(Change eChange, BOOL fQuiet = FALSE);

protected:
	virtual BOOL OnSelectable(NodeRenderable* pRender);
	Change m_eChange;
	BOOL m_fShout;
	INT32 m_nAffected;

private:
	virtual BOOL Pre();
	virtual BOOL Do(Node*);
	virtual BOOL Post();
};



/***********************************************************************************************
>	class CCAPI SelectScan : public BaseSelectScan

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/5/99
	Purpose:	Selects objects which are in the set item whose selection toggle has been
				clicked.
	SeeAlso:	BaseSelectScan
***********************************************************************************************/

class CCAPI SelectScan : public BaseSelectScan
{
public:
	SelectScan(SGNameItem* pItem, Change eChange, BOOL fQuiet = FALSE);

protected:
	virtual BOOL OnSelectable(NodeRenderable*);

	SGNameItem* m_pItem;
};



/***********************************************************************************************
>	class CCAPI SelectUnionScan : public BaseSelectScan

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/5/99
	Purpose:	Selects objects which are in any of the highlighted set items.
	SeeAlso:	BaseSelectScan
***********************************************************************************************/

class CCAPI SelectUnionScan : public BaseSelectScan
{
public:
	SelectUnionScan(Change eChange);

protected:
	class CCAPI Test : public NameItemIter
	{
	public:
		enum Question { IS_NON_MEMBER = FALSE, IS_MEMBER = TRUE };
		Test(NodeRenderable* pRender, Question eQ);

	protected:	
		virtual BOOL Do(SGNameItem*);

		NodeRenderable* m_pRender;
		BOOL m_nXor;
	};

	virtual BOOL OnSelectable(NodeRenderable*);
};



/***********************************************************************************************
>	class CCAPI SelectIntersectScan : public SelectUnionScan

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/5/99
	Purpose:	Selects objects which are in all of the highlighted set items.
	SeeAlso:	BaseSelectScan; SelectUnionScan
***********************************************************************************************/

class CCAPI SelectIntersectScan : public SelectUnionScan
{
public:
	SelectIntersectScan(Change eChange);

protected:
	virtual BOOL OnSelectable(NodeRenderable*);
};



/********************************************************************************************
>	class CCAPI AllowOpScan : public UndoableNodeScan
	class CCAPI AllowOpSingleScan : public AllowOpScan

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/5/99
	Purpose:	Performs an AllowOp test and update on all the objects which are members
				of highlighted 'Used Name' items in the Attribute gallery; performs the
				same, but only on members of a specified set.
	Notes:		The present implementation is not reentrant or thread-safe.
********************************************************************************************/

class CCAPI AllowOpScan : public UndoableNodeScan
{
public:
	AllowOpScan(UndoableOperation* pOp, Source* ps);
	virtual BOOL Update();

protected:
	class CCAPI IsLitUsedName : public NameIterOp
	{
	public:
		IsLitUsedName(Node* pNode);

	protected:
		virtual BOOL Do(SGNameItem*);
	};

	virtual BOOL Do(Node*);
	static ObjChangeParam m_OCP;
};



class CCAPI AllowOpSingleScan : public AllowOpScan
{
public:
	AllowOpSingleScan(UndoableOperation* pOp, Source* ps, const StringBase& strName);

protected:
	virtual BOOL Do(Node*);
	
	const StringBase& m_strName;
	SGUsedNames* m_pUsedNames;
};



/********************************************************************************************
>	class CCAPI ApplyScan : public UndoableNodeScan
	class CCAPI ApplySingleScan : public ApplyScan
	class CCAPI ApplyPropScan : public ApplySingleScan

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/5/99
	Purpose:	Applies all the highlighted 'Used Name' items in the Attribute gallery to
				all the selected objects (if they don't already have them); a single
				name to all the selected objects if they don't already have it; 'applies'
				a NodeSetProperty for a set, with default SGNameProps, to the NodeSetSentinel.
********************************************************************************************/

class CCAPI ApplyScan : public UndoableNodeScan
{
public:
	ApplyScan(UndoableOperation* pOp, Source* ps);

	// Unfortunately a bug in MSVC6 prevents this class being declared protected.
	class CCAPI ApplyItems : public NameIterOp
	{
	public:
		ApplyItems(Node* pNode, UndoableOperation* pOp);

	protected:
		virtual BOOL Do(SGNameItem*);
	};

protected:
	virtual BOOL Do(Node*);
};



class CCAPI ApplySingleScan : public ApplyScan
{
public:
	ApplySingleScan(UndoableOperation* pOp, Source* ps, const StringBase& strName);

protected:
	virtual BOOL Do(Node*);
	const StringBase& m_strName;
};



class CCAPI ApplyPropScan : public ApplySingleScan
{
public:
	ApplyPropScan(UndoableOperation* pOp, const StringBase& strName,
				  NodeSetProperty* pCopyPropNode = 0);

protected:
	virtual BOOL Do(Node*);
	NodeSetProperty* m_pCopyPropNode;
};



/********************************************************************************************
>	class CCAPI HideScan : public UndoableNodeScan
	class CCAPI HidePropScan : public HideScan
	class CCAPI HideSingleScan : public HideScan

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/5/99
	Purpose:	Hides names of objects and their properties which are highlighted members
				of the 'Used Names' group in the Attribute gallery; hides a specified
				name of objects.
********************************************************************************************/

class CCAPI HideScan : public UndoableNodeScan
{
public:
	HideScan(UndoableOperation* pOp, Source* ps);

	class CCAPI HideItems : public NameIterOp
	{
	public:
		HideItems(Node* pNode, UndoableOperation* pOp);

	private:
		virtual BOOL Do(SGNameItem*);
	};

protected:
	virtual BOOL Do(Node*);
};



class CCAPI HidePropScan : public HideScan
{
public:
	HidePropScan(UndoableOperation* pOp);

protected:
	class CCAPI HideProp : public HideScan::HideItems
	{
	public:
		HideProp(Node* pNode, UndoableOperation* pOp);

	private:
		virtual BOOL Do(SGNameItem*);
	};

	virtual BOOL Do(Node*);
};



class CCAPI HideSingleScan : public HideScan
{
public:
	HideSingleScan(UndoableOperation* pOp, Source* ps, const StringBase& strName);

protected:
	virtual BOOL Do(Node*);
	const StringBase& m_strName;
	SGUsedNames* m_pUsedNames;
};



/***********************************************************************************************
>	class CCAPI CreateDisplayScan : public NodeScan

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/5/99
	Purpose:	Scans the 'selected' document and creates/refreshes the groups and items of
				the Attribute gallery's display.
***********************************************************************************************/

class CCAPI CreateDisplayScan : public NodeScan
{
public:
	CreateDisplayScan();

protected:
	// Resets the counters in all the gallery's items.
	class CCAPI ClearCounters : public NameItemIter
	{
		virtual BOOL Do(SGNameItem*);
	};

	// Creates items for all the sets which include the given object.
	class CCAPI CreateItems : public NameGroupIter
	{
	public:
		CreateItems(Node* pNode);

	protected:
		virtual BOOL Do(SGNameGroup*);
		Node* m_pNode;
	};

	// Deletes all items with node counts of zero.
	class CCAPI DelItemIfUnref : public NameItemIter
	{
		virtual BOOL Do(SGNameItem*);
	};

	// Folds all groups which don't have items.
	class CCAPI FoldGroupIfEmpty : public NameGroupIter
	{
		virtual BOOL Do(SGNameGroup*);
	};

	virtual BOOL Pre();
	virtual BOOL Do(Node*);
	virtual BOOL Post();
};




// This stores delayed calls to the Extender::Extend function.
struct ExtParam
{
	NodeRenderableInk*	pInk;
	BYTE				nType;
	DocRect				drTriggerRef;
	DocRect				drTargetRef;
	DocRect				drNewTrigger;
	DocRect				drLastTarget;
	DocRect				drMinDiff;
};

#endif	/* !NGSCAN_H */
