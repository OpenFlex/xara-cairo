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


// thumbmsg.h - Definitions for thumbnail cache messages

#ifndef INC_THUMBMSG
#define INC_THUMBMSG


class DragManagerOp;
class DragInformation;

/*********************************************************************************************

>	class ThumbMessage : public Msg

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/3/95
	Purpose:	This message is sent to inform the system of important global thumbnail events.
				Currently the only such event is CACHESIZECHANGED, sent whenever the thumbnail
				cache wants its size changing.

	Notes:		The IMPLEMENT_DYNAMIC can be found in winoil\thumb.cpp
	SeeAlso:
	Documentation:
	
*********************************************************************************************/

class ThumbMessage : public Msg
{
	CC_DECLARE_DYNAMIC(ThumbMessage)

public:
	// thumb messages are sent on these events.
	enum ThumbState
	{
		CACHESIZECHANGED,
		KILLCACHE
	};
	
	ThumbState		State;				// The state, as defined above
	INT32				NewSize;			// The new size of the thumbnail caches
	SGLibType		Type;				// The lib type we want this message to apply to

	// Constructor for CacheSizeChanged
	ThumbMessage(ThumbState TheState, INT32 Size)
				: State(TheState), NewSize(Size), Type(SGLib_Blank)
		{ /* empty */ }

	// Constructor for KillCache
	ThumbMessage(ThumbState TheState, SGLibType LibType)
				: State(TheState), NewSize(0), Type(LibType)
		{ /* empty */ }

};


#endif

