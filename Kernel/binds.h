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
	This file binds various platform-indy identifiers to run-time constant numbers.
	It includes things like the identifiers describing different types of click, different
	types of modifiers, etc...

	You should only add things to this file if you know they are not going to change
	frequently. What I mean is don't put anything in here which is allocated on request from
	thrid-parties - things like Tool IDs should NOT go in this file.

*/

/*
 * */

#ifndef INC_BINDS
#define INC_BINDS

/*******************************************************************************************

< ClickType

	Comment:	The kernel only understands pointing-devices with ONE button! DON'T PANIC!
				If a pointing- device has more than one button then the functions of
				the other buttons are encoded as "modifiers" of the simple click state (See
				Modifiers below). The reason for doing things this way is not to be ready for
				the Mac but simply because functions which want to treat all clicks in the
				same way don't have to do any special tests.

				The model of clicking that the kernel expects is that it always receives a
				single-click whether or not further testing decides that a double-click or a
				drag follows. The kernel expects that it will always have received a
				single-click when dealing with a double-click or a drag. It is up to the OIL
				layer to guarantee this!

MonoOn
				enum ClickType { CLICKTYPE_NONE,
								 CLICKTYPE_SINGLE,
								 CLICKTYPE_DOUBLE,
								 CLICKTYPE_DRAG
							    };
MonoOff

	SeeAlso:	ClickModifiers; DocView::OnClick; Tool_v1::OnClick

********************************************************************************************/ 

enum ClickType
{
	CLICKTYPE_NONE, 			// what's this then?
	CLICKTYPE_SINGLE, 			// single click, any button
	CLICKTYPE_DOUBLE, 			// double click, any button
	CLICKTYPE_DRAG,				// mouse move
	CLICKTYPE_UP				// button up, any button
};




/*******************************************************************************************

< ButtonFunction

	Comment:	This enum lists the possible functions that can be assigned to each of the
				mouse buttons via the preferences system.
MonoOn
enum ButtonFunction {
						BUTTFUNC_NORMAL,
						BUTTFUNC_SHIFT,
						BUTTFUNC_CONSTRAIN,
						BUTTFUNC_ALTERNATIVE,
						BUTTFUNC_MENU,
						BUTTFUNC_EDITOBJECT,
						BUTTFUNC_FULLSCREEN,
						BUTTFUNC_ZOOMIN
					};
MonoOff

********************************************************************************************/ 

enum ButtonFunction {
						BUTTFUNC_NORMAL,
						BUTTFUNC_SHIFT,
						BUTTFUNC_CONSTRAIN,
						BUTTFUNC_ALTERNATIVE,
						BUTTFUNC_MENU,
//						BUTTFUNC_EDITOBJECT,
						BUTTFUNC_FULLSCREEN,
						BUTTFUNC_ZOOMIN,
						BUTTFUNC_PUSHCENTRE,

							BUTTFUNC_LAST
					};




/*******************************************************************************************

< DragType

	Comment:	When a drag is started there are various options which control the way
				scrolling occurs when the pointer moves outside the client area.

MonoOn
enum DragType { DRAGTYPE_NOSCROLL,
				DRAGTYPE_AUTOSCROLL,
				DRAGTYPE_DEFERSCROLL,
				DRAGTYPE_OLESCROLL
				};
MonoOff

	SeeAlso:	CCamView::StartDrag

********************************************************************************************/ 

enum DragType { DRAGTYPE_NOSCROLL,
				DRAGTYPE_AUTOSCROLL,
				DRAGTYPE_DEFERSCROLL,
				DRAGTYPE_OLESCROLL
				};




/*******************************************************************************************

< ToolKeyClaimDetails

	Comment:	When a tool claims a modifier key combination for temporary tool selection 
				(e.g. ALT for the selector tool), it uses this structure to indicate the 
				modifier key combination it wishes to claim.  For example, it can claim the 
				"right shift and right control key" combination, or the "left ALT key" 
				combination.
				Note that while control and shift are fairly constant, the "Alternative"
				fields may not always map onto ALT keys, e.g on the Mac, Alternative2
				might be the 'splat' key etc.

MonoOn
union ToolKeyClaimDetails
{
	struct
	{
		BOOL Alternative1 : 1;
		BOOL Alternative2 : 1;
		BOOL LeftShift	  : 1;
		BOOL RightShift   : 1;
		BOOL LeftControl  : 1;
		BOOL RightControl : 1;
	} Keys;

	// Used for direct comparisons
	UINT32 Value;
};
MonoOff

	SeeAlso:	Tool::ClaimToolKey

********************************************************************************************/
/*
union ToolKeyClaimDetails
{
	struct
	{
		BOOL LeftShift	  : 1;
		BOOL RightShift   : 1;
		BOOL LeftControl  : 1;		//	>	how you distinguish between
		BOOL RightControl : 1;		//  >	these is anyone's guess
		BOOL Alternative1 : 1;
		BOOL Alternative2 : 1;
	} Keys;

	// Used for direct comparisons
	UINT32 Value;
};
*/
#endif
