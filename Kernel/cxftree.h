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


#ifndef INC_CXFTREE
#define INC_CXFTREE

//#include "dialogop.h"
//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "timdlg.h"

//#include "cxfrec.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "cxfrech.h" - in camtypes.h [AUTOMATICALLY REMOVED]

// -----------------------------------------------------------------------------------------
// CXFTreeDlg for displaying the Camelot v2 file format
 
#define OPTOKEN_CXFTREEDLG _T("CXFTreeDlg")    

class CXFTreeDlg;
class DebugTreeInfo;
class CXaraFileRecordHandler;
class CXaraFile;

class CXFNode : public CCObject
{
	CC_DECLARE_DYNAMIC( CXFNode )
public:

	CXFNode() {}
	CXFNode(CXaraFileRecord* pThisRecord);
	~CXFNode();

	void SetNext(CXFNode * pRecord)		{ pNext		= pRecord; }
	void SetPrevious(CXFNode* pRecord)	{ pPrevious = pRecord; }
	void SetParent(CXFNode* pRecord)	{ pParent	= pRecord; }
	void SetChild(CXFNode* pRecord)		{ pChild	= pRecord; }

	CXFNode* GetNext()			{ return pNext;		}
	CXFNode* GetPrevious()		{ return pPrevious; }
	CXFNode* GetParent()		{ return pParent;	}
	CXFNode* GetChild()			{ return pChild;	}

	CXaraFileRecord* GetCXaraFileRecord() { return pRecord; }

	UINT32 GetTag();
	UINT32 GetSize();
	void  ResetReadPos();

	BOOL HasChildren()			 { return pChild != NULL; }
	BOOL ShowChildren()			 { return DoShowChildren; }
	void SetShowChildren(BOOL b) { DoShowChildren = b; }

private:

	CXaraFileRecord* pRecord;

	CXFNode* pNext;
	CXFNode* pPrevious;
	CXFNode* pParent;
	CXFNode* pChild;

	BOOL DoShowChildren;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------

class CXFTreeDlgRecordHandler : public CXaraFileRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(CXFTreeDlgRecordHandler);

public:
	CXFTreeDlgRecordHandler(CXFTreeDlg* pDlg,CXaraFile* pCXFile);
	~CXFTreeDlgRecordHandler() {}

	virtual UINT32*	GetTagList() { return NULL; }
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);
	virtual BOOL	HandleStreamedRecord(CXaraFile * pCXFile, UINT32 Tag,UINT32 Size,UINT32 RecordNumber);
	virtual void	IncProgressBarCount(UINT32 n) {}
	virtual BOOL	IsStreamed(UINT32 Tag);

private:
	CXFTreeDlg* pCXFDlg;
	CXaraFile* pCXFile;
};


/********************************************************************************************

>	class CXFNodeTypeStatistics : public ListItem

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/10/96
	Purpose:	Holds info relating to a node of a particular type (i.e. tag value)
	SeeAlso:	CXFTreeDlg

********************************************************************************************/

class CXFNodeTypeStatistics : public ListItem
{
	CC_DECLARE_MEMDUMP( CXFNodeTypeStatistics )
public:

	CXFNodeTypeStatistics(UINT32 ThisTag) { Tag = ThisTag; NumOccurrences = 0; TotalSize = 0; }

	void	IncNumOccurances()		{ NumOccurrences++; }
	void	AddToTotalSize(INT32 s)	{ TotalSize += s; }

	UINT32	GetTag()				{ return Tag; }
	INT32	GetNumOccurances()		{ return NumOccurrences; }
	INT32	GetTotalSize()			{ return TotalSize; }

private:
	UINT32	Tag;
	INT32	NumOccurrences;
	INT32	TotalSize;
};

/********************************************************************************************

>	class CXFNodeTypeStatisticsList : public List

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/10/96
	Purpose:	Class that maintains statistics on the nodes added to the tree
	SeeAlso:	CXFTreeDlg

********************************************************************************************/

class CXFNodeTypeStatisticsList : public List
{
	CC_DECLARE_MEMDUMP( CXFNodeTypeStatisticsList )
public:

	void Update(CXFNode* pNode);
	void Dump(CXFTreeDlg* pDlg);

private:
	CXFNodeTypeStatistics*	FindNodeType(UINT32 Tag);
	void					Add(CXFNodeTypeStatistics* pNodeType);
	CXFNodeTypeStatistics*	GetHead();
	CXFNodeTypeStatistics*	GetNext(CXFNodeTypeStatistics* pItem);
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------




//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------

class CXFTreeDlg : public DialogOp
{
	CC_DECLARE_DYNCREATE( CXFTreeDlg )
public:

	CXFTreeDlg();
	~CXFTreeDlg();

	MsgResult Message( Msg* Message);
	void Do(OpDescriptor*);
	BOOL Create();

	static CDlgResID IDD() {return _R(IDD_NEWDEBUGTREE);}

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);
	static CXFTreeDlg* GetCurrentCXFTreeDlg() { return pCurrentCXFTreeDlg; }

	void SetFileName(String_256& FileName);

	void SetEndOfFile(BOOL b) { EndOfFile = b; }

	void AddNode(CXFNode *pNode);

	void ShowFile(TCHAR* pFileName);

	void GetTagText(UINT32 Tag,String_256& Str);

private:
	void DeInit();

	void CreateTree();
	void Delete(CXFNode* pNode);

	INT32 AddDisplayNode(CXFNode* pNode,INT32 Index,INT32 Depth,BOOL ExpandAll);
	void ShowNodeDebugInfoForNode(CXFNode *pNode);
	CXaraFileRecordHandler* FindHandler(UINT32 Tag);
	void GetTagText(CXFNode* pNode,String_256& Str);

	CXFNode* pRoot;
	CXFNode* pContextNode;
	BOOL AddNextAsChild;
	INT32 Level;
	INT32 MaxIndex;

	String_256 FileName;
	BOOL EndOfFile;

	StringBase* EditStr;

	CXFNodeTypeStatisticsList ListOfNodeTypeStats;

	static CXFTreeDlg* pCurrentCXFTreeDlg;
	static BOOL 	s_bExpandClicked;

	// New TreeView stuff
	CTreeItemID AddOneItem(CTreeItemID hParent, const StringBase& str, CTreeItemID hInsAfter, INT32 iImage, CXFNode *pNode);
	CTreeItemID AddItemToNewTreeControl(CTreeItemID hParentItem, CTreeItemID hInsAfterItem, CXFNode *pNode, BOOL bAddChildren);
	BOOL InitialiseNewTreeControl(void);
	INT32 GetImageForNode(CXFNode *pNode);
	BOOL GetInfoFromTreeItem(CTreeItemID hItem, CXFNode **pNode, INT32 *pChildren);
	void ExpandNewTree();

	// Pictures for tree view
	INT32 m_idxGeneralTag;
	INT32 m_idxDefineBitmap;
	INT32 m_idxDefineColour;
	INT32 m_idxCompression;
	INT32 m_idxDown;
	INT32 m_idxUp;
	INT32 m_idxGroup;
	INT32 m_idxPage;
	INT32 m_idxAttribute;
	INT32 m_idxShape;
	INT32 m_idxSentinelNode;
	INT32 m_idxSetProperty;
};

#endif // INC_CXFTREE

