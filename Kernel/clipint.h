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
 * */
// Camelot's Internal clipboard

#ifndef INC_CLIPINT
#define INC_CLIPINT

//#include "document.h" - in camtypes.h [AUTOMATICALLY REMOVED]


class Layer;
class CCamDoc;
class Range; 


/********************************************************************************************
>	class InternalClipboard : public Document

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com> (Connection to ExternalClipboard by Jason, OLE stuff by JustinF)
	Created:	05/07/94 (19/4/95)

	Purpose:	Camelot's internal clipboard document.

				This is a cache, if you like, of the contents of the ExternalClipboard
				
				When Camelot "owns" the external clipboard, the InternalClipboard contains
				the objects which will be pasted into other applications. (When external
				apps paste, they will request that Camelot exports the InternalClipboard
				in some external exchange format)

				When Camelot doesn't own the external clipboard, the InternalClipboard
				will either be empty, or will be a cached copy of the external clipboard
				(if the user has pasted once into Camelot, while the clipboard remains
				unchanged, the internal clipboard will have the internal camelot tree
				representation of the clipboard cached - thus, pasting a .cdr file into
				camelot will only do the slow conversion once, and subsequent pastes
				will be 'native')

	SeeAlso:	ExternalClipboard; Document
*********************************************************************************************/

class InternalClipboard : public Document
{

/////////////////////////////////////////////////////////////////////////////////////////
//	Interface.

public:

	// The identifier's of the two clipboards.
	enum ID { CLIPBOARD, DRAGDROP };

	// Access the the two clipboards through these.
	static InternalClipboard* Instance()	{ return pInstance; }
	static InternalClipboard* Other()		{ return pOther; }
	static void Swap();
	static ID GetCurrentID();

	// Attributes.
	static BOOL IsEmpty(BOOL AskExternalClipboard = TRUE);
	static void DescribeContents(String_64* Result);
	static DocRect GetObjectsBounds();
	static Layer* GetInsertionLayer();
	static Range* GetClipboardRange()		{ return pInstance->pClipboardRange; }

	// Copying.
	static BOOL PrepareForCopy();
	static BOOL CopyInProgress();
	static BOOL CopyObjects(Range& RangeToCopy, Operation * pOp = NULL);
	static BOOL CopyComponentData(BaseDocument* pSrcDoc);
	static BOOL CopyCompleted();

	//Graham 24/4/97
	//A quick way of putting some text on the internal clipboard
	static BOOL CopyText(TCHAR* pBuffer);


	// Pasting.
	static BOOL PrepareForPaste(BOOL* pExternalSource = 0);
	static BOOL PasteCompleted();
	static DocCoord GetOriginalCentrePoint();
	static void SetOriginalCentrePoint(DocCoord NewCentre);
	// Notifications.
	static void Clear();
	static void AttrsHaveChanged(); 


/////////////////////////////////////////////////////////////////////////////////////////
//	Implementation.

public:

	// Startup / shutdown.  These manage the two internal clipboards, Instance and Other.
	static BOOL Initialise();
	static void Deinit();

protected:

	// Creation & destruction.
	InternalClipboard(ID id, BOOL fHide = TRUE);
	virtual ~InternalClipboard();
	virtual BOOL Init(CCamDoc* pOilDoc);

	// RTTI (of sorts).
	virtual BOOL IsNotAClipboard() const	{ return FALSE; };
	virtual BOOL IsAClipboard() const		{ return TRUE; };

private:

	// Helpers.
	BOOL OnNewClipboardObjects();
	static void DescribeContentsInternal(String_64* Result);

	// Data members.
	static	 InternalClipboard* pInstance;		// The only instance of the InternalClipboard
	static	 InternalClipboard* pOther;			// the other instance (temp save) of the clipboard
	Range*	 pClipboardRange;					// the other instance's range
	BOOL	 ClipOp;							// TRUE while we're doing a copy operation
	DocCoord dcCentre;							// centre of copied objects
	ID		 m_id;								// identifier of this clipboard
	BOOL		OriginalCentreLock;				// TRUE when calls to SetOriginalCentrePoint are disallowed
												// (only used when clipboard data was from an external source)

	CC_DECLARE_DYNAMIC(InternalClipboard);
		
	friend class ExternalClipboard;
	friend class OpDeleteBitmap;
};

#endif
