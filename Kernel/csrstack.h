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

// The Cursor Stack (interface).


#ifndef	CSRSTACK__INC
#define CSRSTACK__INC


class Cursor;


/********************************************************************************************

>	class CursorIdent : public CC_CLASS_MEMDUMP

	Author:		Jim_Lynn (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/1/95
	Purpose:	Used in the cursor stack - holds a pointer to a cursor and an identifying ID
	SeeAlso:	CursorStack

********************************************************************************************/

class CursorIdent : public CC_CLASS_MEMDUMP
{
public:
	Cursor* pCursor;				// The pointer to the cursor this object refers to
	INT32 UniqueID;					// Unique identifying ID that is used to reference objects
									// on the cursor stack
	static INT32 NextUniqueID;		// static variable holding next ID to be used

	CursorIdent(); 					// Default constructor
	~CursorIdent();					// Destructor

	INT32 StoreNewCursor(Cursor* NewCursor);

};

/************************************************************************************************

>	class CursorStack : public CC_CLASS_MEMDUMP

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15th November, 1993
	Purpose:	A stack of Cursor objects, which is part of the kernel (NB Cursor objects are
				part of the OIL).

************************************************************************************************/

class CursorStack : public CC_CLASS_MEMDUMP
{
	friend void BeginBusyCursor();
	friend void EndBusyCursor();
	friend void SmashBusyCursor();

	// Give my name in memory dumps
	CC_DECLARE_MEMDUMP(CursorStack);

public:
	CursorStack(INT32 maxdepth = 10);				// construct a (default-sized) stack of cursors
	virtual ~CursorStack();

	static BOOL Init();							// called upon application startup and shutdown
	static void DeInit();

// new static functions to replace accessing Global directly
	static BOOL GIsValid();
	static INT32 GPush(Cursor* pCursor, BOOL ActivateNow = TRUE);
	static Cursor* GPop(INT32 cursorID/* = 0 */);
	static Cursor* GSetTop(Cursor* pCursor, INT32 cursorID/*  = 0*/);
	static void GSetActive();
	static BOOL GIsActive(const Cursor* pCursor);

	static Cursor* GetActive();
	
	void BeginBusy();							// Set the busy cursor (and increment the busy count)
	void EndBusy();								// clear the busy cursor (if the busy count reaches zero)
	void SmashBusy();							// Smash the busy cursor (ensure it is off)

// these are the original member functions, which will probably go private in time
private:
	BOOL IsValid() const;

	INT32 Push(Cursor* pCursor, BOOL ActivateNow = TRUE);
	Cursor* Pop(INT32 cursorID = 0);
	Cursor* SetTop(Cursor* pCursor, INT32 cursorID = 0);

	void SetActive( bool fOnlyRendWnd = true ) const;
	BOOL IsActive(const Cursor* pCursor) const;

// IMPORTANT: DONT USE THIS VAR IN NEW CODE - IT IS DUE TO DIE SOON
	static CursorStack* Global;					// the stack shared by the whole application

	CursorIdent* pcStack;						// Pointer to array of CursorIdent objects
	INT32 nNextFreeSlot;							// index of the next available slot in the array
	INT32 nSentinel;								// one more than the last slot in the array

	INT32 BusyCount;								// if >0, show the busy cursor

};



// These global functions provide a convenient shorthand for common cursor functions.

void BeginBusyCursor();
void EndBusyCursor();
void SmashBusyCursor();


#endif	// CSRSTACK__INC
