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

// The Cursor class (interface).

#ifndef	CURSOR__INC
#define	CURSOR__INC

// Forward references:-
class Tool_v1;

/***************************************************************************************************

>	class Cursor : public CC_CLASS_MEMDUMP

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15 November 1993
	Purpose:	Encapsulates OIL cursors, hiding OS specific functions behind a standard
				sensible interface.

***************************************************************************************************/

class Cursor : public CC_CLASS_MEMDUMP
{
public:
	static Cursor* Arrow;							// the standard arrow cursor
	static Cursor* Busy;							// the standard hour-glass cursor
	static Cursor* Insert;							// the standard I-beam cursor
	static Cursor* CrossHair;						// the standard crosshair cursor
	static Cursor* Progress;						// placeholder for the progress-counter cursor
	static Cursor* PointingHand;					// the Netscape-style pointing hand
	static Cursor* SizeNWSE;						// standard resize north-west / south-east

	static BOOL Init();								// creates platform-specific arrow and
	static void DeInit();							// hour-glass cursors etc.

	Cursor(LPCSTR lpStdCsrName);					// load a standard cursor, eg. the hour-glass
	Cursor(UINT32 wCsrID);							// load a cursor from the kernel's resources
	Cursor(Tool_v1* pTool, UINT32 wCsrID);			// load a cursor from a tool's resources
	Cursor(UINT32 wToolID, UINT32 wCsrID);				// ditto, but using the tool's ID
	Cursor(wxBitmap* pbmpAND, wxBitmap* pbmpXOR);		// create a cursor from a bitmap

	virtual ~Cursor();								// destroy a cursor

	BOOL IsValid() const;							// TRUE if cursor constructed OK
	void SetActive( bool fOnlyRendWnd = false ) const; // set the system's cursor to this
	wxCursor *Handle() {return &hCursor;}			// returns the (wxWindows) handle of the cursor

//	static BOOL Show();								// show the cursor, if invisible
//	static BOOL Hide();								// hide the cursor, if visible
	BOOL Show();									// show the cursor, if invisible
	BOOL Hide();									// hide the cursor, if visible
	
	static INT32 Width();								// width and height of cursors, in pixels,
	static INT32 Height();							// on this system.

private:
	CC_DECLARE_MEMDUMP(Cursor);

	wxCursor		   hCursor;					// the Windows handle of the cursor
	BOOL				bMustDestroy;				// whether to deallocate on destruction
};



#endif	// CURSOR__INC
