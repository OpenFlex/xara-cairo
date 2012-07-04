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


#ifndef INC_DBUGTREE
#define INC_DBUGTREE

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]

// -----------------------------------------------------------------------------------------
// DebugTreeDlg for displaying the Camelot tree
 
#define OPTOKEN_DEBUGTREEDLG _T("DebugTreeDlg")    
    
class Document;
    
class DebugTreeDlg : public DialogOp
{
	CC_DECLARE_DYNCREATE(DebugTreeDlg)
public:

	DebugTreeDlg();      
	~DebugTreeDlg(); 

	MsgResult Message( Msg* Message); 
	void Do(OpDescriptor*);		// "Do" function        
	static BOOL Init();                        
	BOOL Create(); 
	static OpState GetState(String_256*, OpDescriptor*);

	static void TweeDump(BaseDocument *DocToDump = NULL);
	static void DumpSubTree(Node* pSubTree, INT32 FromParent=0, INT32 MaxDepth=9999);

	static CDlgResID IDD() {return _R(IDD_NEWDEBUGTREE);}

private:
	INT32 DisplayNodesChildren(Node *pNode, INT32 ListIndex, BOOL AddOnly = FALSE);
	INT32 GetTreeDepth(Node *pNode);
	void ShowNodeDebugInfo(INT32 ListIndex); 
	void ShowNodeDebugInfoForNode(Node *pNode);
    void ExpandTree();
	void DumpTree();
    void Refresh();
	void Initialise();
	void GetTree();
	void DeInit();

	BOOL ShouldBeHidden(Node*);
	BOOL IsChildOfHiddenNode(Node*);
	BOOL HasChildren(Node *pNode);
	void AddNode(Node *pNode, INT32 Index, INT32 Depth,
				 BOOL HasChildren, BOOL ChildrenAreDisplayed, 
				 BOOL IsAHiddenNode, BOOL IsHidden);
	void RemoveNode(INT32 Index);
	void UpdateNode(INT32 Index, StringBase *NewText);
	BOOL IsAHiddenNode(Node *pNode);

	void ShowHidden(BOOL);
	INT32 DeleteNode(INT32 Index, BOOL Recurse = FALSE, INT32 Count = 0);
	
	// New TreeView stuff
	CTreeItemID AddOneItem(CTreeItemID hParent, const StringBase& str, CTreeItemID hInsAfter, INT32 iImage, Node *pNode);
	CTreeItemID AddItemToNewTreeControl(CTreeItemID hParentItem, CTreeItemID hInsAfter, Node *pNodeToAdd, BOOL bAddChildren = TRUE);
	BOOL InitialiseNewTreeControl(void);
	INT32 GetImageForNode(Node *pNode);
	BOOL GetInfoFromTreeItem(CTreeItemID hItem, Node** pNode, size_t* pChildren);
	void DumpTreeTree();
	void ExpandNewTree();
	void RefreshNewTree();

	// Member vars
	StringBase*		m_pstrDetails;
	static BOOL		s_bShowHiddenNodes;
	static BOOL 	s_bSelectionOnly;
	static BOOL 	s_bExpandClicked;

	// Pictures for tree view
	INT32					m_idxNode;
	INT32					m_idxAttribute;
	INT32					m_idxRenderableInk;
	INT32					m_idxRenderablePaper;
	INT32					m_idxInsertionNode;
	INT32					m_idxHiddenNode;
	INT32					m_idxSentinelNode;
	INT32					m_idxUserAttr;
	INT32					m_idxSetProperty;
};

#endif
