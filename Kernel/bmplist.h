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


// kernel class to encompass bitmaps lists

#ifndef	INC_BMPLIST
#define	INC_BMPLIST

#include "list.h"
#include "msg.h"
#include "ops.h"

class OILBitmap;
class BitmapList;
class Document;
class KernelBitmap;
class KernelBitmapRef;
class Node;
class Operation;
class Action;

/***********************************************************************************************

>	class GreyscaleBitmapList : public List

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Purpose:	A list of Greyscale bitmaps
	SeeAlso:	-

***********************************************************************************************/

/*class GreyscaleBitmapList : public List
{
	CC_DECLARE_MEMDUMP(GreyscaleBitmapList)

public:
	GreyscaleBitmapList();
	~GreyscaleBitmapList();

	static BOOL Init();
	static BOOL DeInit();

	BOOL AddItem(OILBitmap *NewBitmap);

	virtual void AddHead( ListItem* );	
	virtual void AddTail( ListItem* );

	virtual ListItem* RemoveHead();							
	virtual ListItem* RemoveTail();	
	
	virtual ListItem* RemoveItem(ListItem* Item);

	virtual LISTPOS InsertBefore(LISTPOS here, ListItem* item);
	virtual ListItem *InsertBefore(ListItem* here, ListItem* item);

	virtual LISTPOS InsertAfter(LISTPOS here, ListItem* item);
	virtual ListItem *InsertAfter(ListItem* here, ListItem* item);

	INT32 GetCurrentGreyscaleSize();

	void SetMaxGreyscaleSize(INT32);
	INT32 GetMaxGreyscaleSize();

#ifdef _DEBUG
	void DumpGreyscaleBitmapListToTrace();
#endif

protected:
	void CheckSizeIsOk();

protected:
	static INT32 m_lMaxSize;

private:
	INT32 m_CurrentSize;

};
*/

/***********************************************************************************************

>	class GlobalBitmapList : public List

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Purpose:	A list of all the OIL Bitmaps available in the application
	SeeAlso:	-

***********************************************************************************************/

class GlobalBitmapList : public List
{
	CC_DECLARE_MEMDUMP(GlobalBitmapList)

public:
	GlobalBitmapList();
	~GlobalBitmapList();

	static BOOL Init();
	static BOOL DeInit();

public:
	BOOL AddItem(OILBitmap *NewBitmap);

	void MakeNameUnique(String_256*);

	// Functions to iterate through the bitmaps
	ListItem* GetFirstBitmapName(String_256*);
	ListItem* GetNextBitmapName(ListItem*, String_256*);

	// Find a bitmap with a given name
	OILBitmap* GetBitmapFromName(String_256*);

	// Check to see if the bitmap exists already
	OILBitmap* FindDuplicateBitmap(OILBitmap* pBitmap);

	void DeleteAllUnusedBitmaps();
	BOOL IsBitmapOnClipBoard(OILBitmap* pOILBmp);
	BOOL IsUsedInDocument(Document * pDoc, OILBitmap* pOILBmp);

	// Functions to find statistics about the bitmap system
	INT32 GetDocumentBitmapCount(Document* pDoc);
	INT32 GetDocumentBitmapSize(Document* pDoc);

//	GreyscaleBitmapList* GetGreyscaleBitmapList();

#ifdef _DEBUG
	void DumpGlobalBitmapListToTrace();
#endif

protected:
//	GreyscaleBitmapList GreyscaleBitmaps;
};


/********************************************************************************************

>	class BitmapListChangedMsg: public Msg

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/8/94
	Purpose:	This message is sent whenever the document bitmap list changes in some way.
	SeeAlso:	-

********************************************************************************************/

class BitmapListChangedMsg: public Msg
{
	CC_DECLARE_DYNAMIC(BitmapListChangedMsg);

public:
	// BitmapList changing messages are sent on these events.
	enum BitmapListState
	{
		SELECTNEWBITMAP,			// Sent when a new bitmap has been added to the list and
									// this new bitmap should be the new selection in the
									// bitmap gallery.
		LISTCHANGED,				// Sent when the list has changed. This is the default message.
	};

	BitmapList* pChangedBmpList;	// The bitmap list being changed
	KernelBitmap* pNewBitmap;		// The new bitmap added
	BitmapListState  State;			// The message specifics, as enumerated above

	// Default message, just saying the bitmap list has changed and so update anything that
	// relies on it
	BitmapListChangedMsg(BitmapList* pList):
		pChangedBmpList(pList), pNewBitmap(NULL), State(LISTCHANGED)	{ } 
	
	// New message where a new bitmap has been added and this should become the new selection.
	// At present, just used by the PhotoShop plug-ins so that this bitmap can become selected
	// in the gallery.
	BitmapListChangedMsg(BitmapList* pList, KernelBitmap *pBitmap):
		pChangedBmpList(pList), pNewBitmap(pBitmap), State(SELECTNEWBITMAP) { } 
};


// Optoken for the delete bitmap operation
#define OPTOKEN_DELETEBITMAP _T("DeleteBitmap")	

/********************************************************************************************

>	class OpDeleteBitmap: public Operation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/2/95
	Purpose:	Removes all references to a bitmap, and deletes it from memory.
	SeeAlso:	-

********************************************************************************************/

class CCAPI OpDeleteBitmap: public Operation
{         
	CC_DECLARE_DYNCREATE( OpDeleteBitmap );

public:
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		

	// The 'do' function
	void DoDelete(OILBitmap*);

protected:
	void ForceRedrawOfNode(Document*, Node*, ObjChangeParam*);
};  

#endif
