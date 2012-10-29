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

// Key press message

#ifndef INC_KEYMSG
#define INC_KEYMSG



/*********************************************************************************************
>	class KeyMsg : public Msg

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/8/94
	Purpose:	This is sent when a key press occurs that hasn't yet been processed by other
				parts of the key press handing system, such as the current too, temporary 
				tool switching, and the hot-key system.

*********************************************************************************************/

	

class KeyMsg : public Msg
{
	CC_DECLARE_DYNAMIC(KeyMsg)

public:

	// Key messages are send with these reasons
	enum KeyReason
	{
		KEYPRESS,			// A key has been pressed and the resulting KeyPress object is 
							// pointed to by KeyMsg::pKeyPress
		MODIFIERCHANGED
	};

	KeyReason 		Reason;		// The message specifics, as enumerated above
	KeyPress*		pKeyPress;

	KeyMsg(KeyReason ThisReason,KeyPress* pThisKeyPress) : Reason(ThisReason), pKeyPress(pThisKeyPress) { /* empty */ }
};


#endif	// INC_KEYMSG

