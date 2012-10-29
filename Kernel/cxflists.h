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


// Defines the various lists and list items used by the new file format


class NodePath;
class TextStory;
class NodeGroup;
class Node;
class CXaraFileRecordHandler;
class BaseCamelotFilter;

/***********************************************************************************************

>	class CXaraFilePathRecordRefListItem : public ListItem

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/8/96
	Purpose:	An item that appears in the CXaraFilePathRecordRefList

***********************************************************************************************/

class CXaraFilePathRecordRefListItem : public ListItem
{
CC_DECLARE_MEMDUMP(CXaraFilePathRecordRefListItem)

public:
	CXaraFilePathRecordRefListItem(NodePath* pPath,UINT32 RecNum) { pNodePath = pPath; RecordNumber = RecNum; }

	NodePath*	GetNodePath()		{ return pNodePath; }
	UINT32		GetRecordNumber()	{ return RecordNumber; }

private:
	NodePath*	pNodePath;
	UINT32		RecordNumber;
};

/***********************************************************************************************

>	class CXaraFilePathRecordRefList : public List

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/8/96
	Purpose:	Holds a list of node path objects, and the corresponding record numbers of the
				records that represent the paths in the file

***********************************************************************************************/

class CXaraFilePathRecordRefList : public List
{
CC_DECLARE_MEMDUMP(CXaraFilePathRecordRefList)

public:
	CXaraFilePathRecordRefList() {}

	void AddTail(CXaraFilePathRecordRefListItem* pItem)								{ List::AddTail(pItem); };
	CXaraFilePathRecordRefListItem* GetHead()										{ return (CXaraFilePathRecordRefListItem*)List::GetHead(); }
	CXaraFilePathRecordRefListItem* GetTail()										{ return (CXaraFilePathRecordRefListItem*)List::GetTail(); }
	CXaraFilePathRecordRefListItem* GetNext(CXaraFilePathRecordRefListItem* pItem)	{ return (CXaraFilePathRecordRefListItem*)List::GetNext(pItem); }
	CXaraFilePathRecordRefListItem* GetPrev(CXaraFilePathRecordRefListItem* pItem)	{ return (CXaraFilePathRecordRefListItem*)List::GetPrev(pItem); }
};

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

/***********************************************************************************************

>	class CXaraFileTextStoryGroupRefListItem : public ListItem

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/8/96
	Purpose:	An item that appears in the CXaraFileTextStoryGroupRefList

				The group node that is in this object is assumed to be deletable and not in the tree.
				The destructor will CascadeDelete() the group, then delete the group itself

***********************************************************************************************/

// WEBSTER - markn 31/1/97
// Replaced with general system
/*
class CXaraFileTextStoryGroupRefListItem : public ListItem
{
CC_DECLARE_MEMDUMP(CXaraFileTextStoryGroupRefListItem)

public:
	CXaraFileTextStoryGroupRefListItem(TextStory* pStory,NodeGroup* pGroup) { pTextStory = pStory; pNodeGroup = pGroup; }

	// NOTE! The destructor deletes the group and all it's children
	~CXaraFileTextStoryGroupRefListItem();

	TextStory*	GetTextStory()	{ return pTextStory; }
	NodeGroup*	GetNodeGroup()	{ return pNodeGroup; }

private:
	TextStory* pTextStory;
	NodeGroup* pNodeGroup;
};
*/

/***********************************************************************************************

>	class CXaraFileTextStoryGroupRefList : public List

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/8/96
	Purpose:	Holds a list of text stories and corresponding group objects.

				When automatically converting text to outlines during export of the web format,
				an out-of-tree group of paths is generated for each text story converted to outlines.

				This list allows the group of paths to be generated once during the export process
				(instead of once for calc of file size, then again for actual output)
				It also allows the paths to exist for the entire export lifetime, so that the paths
				can safely be used during export for other processes (such as the smart path similarity
				code that detects paths that differ only by a transformation).

***********************************************************************************************/

// WEBSTER - markn 31/1/97
// Replaced with general system
/*
class CXaraFileTextStoryGroupRefList : public List
{
CC_DECLARE_MEMDUMP(CXaraFileTextStoryGroupRefList)

public:
	CXaraFileTextStoryGroupRefList() {}

	void AddTail(CXaraFileTextStoryGroupRefListItem* pItem)									{ List::AddTail(pItem); };
	CXaraFileTextStoryGroupRefListItem* GetHead()											{ return (CXaraFileTextStoryGroupRefListItem*)List::GetHead(); }
	CXaraFileTextStoryGroupRefListItem* GetNext(CXaraFileTextStoryGroupRefListItem* pItem)	{ return (CXaraFileTextStoryGroupRefListItem*)List::GetNext(pItem); }
};
*/

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

/***********************************************************************************************

>	class CXaraFileNodeGroupRefListItem : public ListItem

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/1/97
	Purpose:	An item that appears in the CXaraFileNodeGroupRefList

				The group node that is in this object is assumed to be deletable and not in the tree.
				The destructor will CascadeDelete() the group, then delete the group itself

  				WEBSTER - markn 29/1/97
				Part of the general form of the system used to convert text to outlines in v1.5

***********************************************************************************************/

class CXaraFileNodeGroupRefListItem : public ListItem
{
CC_DECLARE_MEMDUMP(CXaraFileNodeGroupRefListItem)

public:
	CXaraFileNodeGroupRefListItem(Node* pThisNode,NodeGroup* pGroup) { pNode = pThisNode; pNodeGroup = pGroup; }

	// NOTE! The destructor deletes the group and all it's children
	~CXaraFileNodeGroupRefListItem();

	Node*		GetNode()	{ return pNode; }
	NodeGroup*	GetNodeGroup()	{ return pNodeGroup; }

private:
	Node*		pNode;
	NodeGroup*	pNodeGroup;
};

/***********************************************************************************************

>	class CXaraFileNodeGroupRefList : public List

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/1/97
	Purpose:	Holds a list of nodes and corresponding group objects.

				When automatically converting a node to outlines during export of the web format,
				an out-of-tree group of paths is generated for each node converted to outlines.

				This list allows the group of paths to be generated once during the export process
				(instead of once for calc of file size, then again for actual output)
				It also allows the paths to exist for the entire export lifetime, so that the paths
				can safely be used during export for other processes (such as the smart path similarity
				code that detects paths that differ only by a transformation).

  				WEBSTER - markn 29/1/97
				Part of the general form of the system used to convert text to outlines in v1.5

***********************************************************************************************/

class CXaraFileNodeGroupRefList : public List
{
CC_DECLARE_MEMDUMP(CXaraFileNodeGroupRefList)

public:
	CXaraFileNodeGroupRefList() {}

	void AddTail(CXaraFileNodeGroupRefListItem* pItem)								{ List::AddTail(pItem); };
	CXaraFileNodeGroupRefListItem* GetHead()										{ return (CXaraFileNodeGroupRefListItem*)List::GetHead(); }
	CXaraFileNodeGroupRefListItem* GetNext(CXaraFileNodeGroupRefListItem* pItem)	{ return (CXaraFileNodeGroupRefListItem*)List::GetNext(pItem); }
};

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

/********************************************************************************************

>	class InsertLevelStackItem : public ListItem

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/96
	Purpose:	This item holds all the info for a given insert level of the tree.
				It is used when building the tree on import

				Use it on conjunction with the InsertLevelStack class

********************************************************************************************/

class InsertLevelStackItem : public ListItem
{
	// Give my name in memory dumps
	CC_DECLARE_MEMDUMP(InsertLevelStackItem);

public:
	InsertLevelStackItem(BaseCamelotFilter* pFilter);

	UINT32 GetNumNodesInserted() { return NumNodesInserted; }

	BOOL  SetLastInsertedNode(Node* pNode);
	Node* GetLastInsertedNode()				{ return pLastInsertedNode; }

	void SetLastHandler(CXaraFileRecordHandler* pHandler, UINT32 Tag) { pLastHandler = pHandler; LastHandledTag = Tag; }
	CXaraFileRecordHandler* GetLastHandler()	{ return pLastHandler; }
	UINT32					GetLastHandledTag()	{ return LastHandledTag; }

	BOOL InformLastInsertedNodeChildrenComplete();

private:
	void IncNumNodesInserted() { NumNodesInserted++; }

	UINT32					NumNodesInserted;
	Node*					pLastInsertedNode;
	CXaraFileRecordHandler* pLastHandler;
	UINT32					LastHandledTag;
	BaseCamelotFilter*		pFilter;
	BOOL					LastNodeInformedChildrenComplete;
};

/***********************************************************************************************

>	class InsertLevelStack : public List

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/9/96
	Purpose:	Holds a list of level items
				The class gives the list a stack-like interface

				Each item holds info on a particular level during import.

				The list is actually treated as a stack, where the tail item is the item on the
				top of the stack, and items are only added and removed from the tail of the list

***********************************************************************************************/

class InsertLevelStack : public List
{
CC_DECLARE_MEMDUMP(InsertLevelStack)

public:
	InsertLevelStack();
	~InsertLevelStack();

	void Add(InsertLevelStackItem* pItem);
	InsertLevelStackItem* Get();
	InsertLevelStackItem* Pop();

private:
	UINT32 InsertLevel;
};

