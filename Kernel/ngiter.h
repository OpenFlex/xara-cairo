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
	$Header: /Camelot/kernel/ngiter.h 2     8/11/99 12:06 Justinf $
	Classes to iterate through the objects in the document and over Attribute gallery
	groups and items.
*/

#ifndef NGITER_H
#define NGITER_H

class Node;
class UndoableOperation;
class SGNameGroup;
class SGNameItem;


/***********************************************************************************************
>	class CCAPI NodeScan

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/99
	Purpose:	Abstract base class for scans over sequences of nodes.
	SeeAlso:	NameGallery; NodeScan::Source
***********************************************************************************************/

class CCAPI NodeScan
{
public:
	/******************************************************************************************
	>	class CCAPI NodeScan::Source

		Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
		Created:	27/7/99
		Purpose:	Abstract base class for interfaces to SelRanges, Document trees etc whose
					nodes can be scanned over.
		Notes:		If your derived class defines data members then remember to define a copy
					constructor and consider concurrency issues!
	******************************************************************************************/
	class CCAPI Source
	{
	public:
		// Creation & destruction.
		virtual ~Source()				{ /* empty */ }
		virtual Node* GetFirst() = 0;
		virtual Node* GetNext(Node* pLastNode) = 0;
	};

	// Creation & destruction.
	NodeScan(Source* ps);
	virtual ~NodeScan();

	// Scan through the source's nodes.
	BOOL Scan();

protected:
	// Called before, during and after the scan through the document's tree.
	virtual BOOL Pre();
	virtual BOOL Do(Node* pNode) = 0;
	virtual BOOL Post();

private:
	// Data.
	Source* m_pSource;		// where to get the nodes to scan
};



/********************************************************************************************
>	class CCAPI UndoableNodeScan : public NodeScan

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/11/96
	Purpose:	Base class for NodeScans which are used by UndoableOperations.
********************************************************************************************/

class CCAPI UndoableNodeScan : public NodeScan
{
public:
	UndoableNodeScan(UndoableOperation* pOp, Source* ps);
	
protected:
	UndoableOperation* m_pOp;
};



/***********************************************************************************************
>	class CCAPI DocTreeSource : public NodeScan::Source
	class CCAPI SelectDocSource : public DocTreeSource

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/99
	Purpose:	Concretisation of NodeScan::Source for all NodeRenderableInks in a
				document's object tree (generally), or in the 'selected' document's
				tree (specifically).
***********************************************************************************************/

class CCAPI DocTreeSource : public NodeScan::Source
{
public:
	// Creation & destruction.
	DocTreeSource(BaseDocument* pDoc = 0);

protected:
	virtual Node* GetFirst();
	virtual Node* GetNext(Node*);

	BaseDocument* m_pDoc;			// the document whose tree is to be scanned
};


class CCAPI SelectDocSource : public DocTreeSource
{
protected:
	virtual Node* GetFirst();
};



/***********************************************************************************************
>	class CCAPI RangeSource : public NodeScan::Source
	class CCAPI SelectObjSource : public RangeSource

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/99
	Purpose:	Concretisation of NodeScan::Source for all NodeRenderableInks in a Range
				(generally), or in the Application's SelRange object (specifically).
***********************************************************************************************/

class CCAPI RangeSource : public NodeScan::Source
{
public:
	// If pRange is supplied then use pRange, otherwise use Application::FindSelection.
	RangeSource(Range* pRange = 0);

protected:
	virtual Node* GetFirst();
	virtual Node* GetNext(Node*);

	Range* m_pRange;				// the range to be scanned
};


class CCAPI SelectObjSource : public RangeSource
{
protected:
	virtual Node* GetFirst();
};



/***********************************************************************************************
>	class CCAPI NotSelectSource : public SelectDocSource

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/99
	Purpose:	Concretisation of NodeScan::Source for all NodeRenderableInks NOT in the
				application's selection range.
***********************************************************************************************/

class CCAPI NotSelectSource : public SelectDocSource
{
protected:
	virtual Node* GetFirst();
	virtual Node* GetNext(Node*);
};



/***********************************************************************************************
>	class CCAPI SingleNodeSource : public NodeScan::Source
	class CCAPI SetSentinelSource : public SingleNodeSource

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/99
	Purpose:	Concretisation of NodeScan::Source for a "scan" over a single node
				(generally), and over the 'selected' document's NodeSetSentinel sentinel
				(specifically).
***********************************************************************************************/

class CCAPI SingleNodeSource : public NodeScan::Source
{
public:
	SingleNodeSource(Node* pNode = 0);

protected:
	virtual Node* GetFirst();
	virtual Node* GetNext(Node*);

	Node* m_pNode;
};


class CCAPI SetSentinelSource : public SingleNodeSource
{
protected:
	virtual Node* GetFirst();	
};



/***********************************************************************************************
>	extern SelectDocSource		theSelectedDocument;
	extern SelectObjSource		theSelectedObjects;
	extern NotSelectSource		theUnselectedObjects;
	extern SetSentinelSource	theSetSentinel;

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/99
	Purpose:	Predefined sources for NodeScans: the nodes in the tree of the 'selected'
				document; the nodes in the application's selection; the unselected nodes
				in the tree of the 'selected' document; the special NodeSetSentinel
***********************************************************************************************/

extern SelectDocSource		theSelectedDocument;
extern SelectObjSource		theSelectedObjects;
extern NotSelectSource		theUnselectedObjects;
extern SetSentinelSource	theSetSentinel;



/***********************************************************************************************
>	class CCAPI NameGroupIter

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/99
	Purpose:	Base classes for iterations and searches over all groups and all items in
				the name gallery.
***********************************************************************************************/

class CCAPI NameGroupIter
{
public:
	virtual ~NameGroupIter() { }
	// Calls Do() for each group in the name gallery.
	virtual SGNameGroup* ForEach();

private:
	// Returns TRUE if sucessful and iteration should continue.
	virtual BOOL Do(SGNameGroup* pGroup) = 0;
};



/***********************************************************************************************
>	class CCAPI NameItemIter

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/99
	Purpose:	Abstract base classes for iterations and searches over all groups and all
				items in the Name gallery.
***********************************************************************************************/

class CCAPI NameItemIter
{
public:
	virtual ~NameItemIter() { }
	// Only iterate over particular items - just highlighted ones, or just those of
	// the 'Used Names' group.
	enum Mask { ALL_ITEMS, ALL_NAMES, HIGHLIGHTED_ITEMS, HIGHLIGHTED_NAMES };
	NameItemIter(Mask mask = ALL_ITEMS);

	// Calls Do() for each item in the name gallery.
	virtual SGNameItem* ForEach();

protected:
	// Helper function for ForEach, above.
	SGNameItem* ForEachItem(SGNameGroup* pGroup);

private:
	// Returns TRUE if sucessful and iteration should continue.
	virtual BOOL Do(SGNameItem* pItem) = 0;
	Mask m_eMask;
};



/***********************************************************************************************
>	class CCAPI NameIterOp : public NameItemIter

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/99
	Purpose:	Specialisation of base class to combine a node and an operation.
***********************************************************************************************/

class CCAPI NameIterOp : public NameItemIter
{
public:
	NameIterOp(Node* pNode, UndoableOperation* pOp = 0, Mask mask = HIGHLIGHTED_NAMES);

protected:
	Node* m_pNode;
	UndoableOperation* m_pOp;
};

#endif	/* !NGITER_H */
