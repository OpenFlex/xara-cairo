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

// Definition of Bar messages

#ifndef INC_BARMSG
#define INC_BARMSG

class DialogBarOp;

/******************************************************************************************

>	class BarMsg: public Msg

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/04/94
	Purpose:	This message is sent whenever some aspect of the bars system has changed.
				The Reason field specifies what changed and the pBar field points to the 
				DialogBarOp which changed.
	SeeAlso:	-

******************************************************************************************/

enum BarMsg_Reason { BAR_CREATE, BAR_DELETE, BAR_CHANGESTATE, BAR_OPEN, BAR_CLOSE};

class BarMsg: public Msg
{
	CC_DECLARE_DYNAMIC(BarMsg);

public:
	BarMsg_Reason	Reason;				// Reason for broadcast
	DialogBarOp*	pBar;				// Pointer to bar op which caused broadcast

	BarMsg(BarMsg_Reason ConsReason, DialogBarOp* pConsBar):
		Reason(ConsReason), pBar(pConsBar)
	{ }
};

#endif
