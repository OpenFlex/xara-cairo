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


// dragmsg.h - Definitions for global dragging system messages

#ifndef INC_DRAGMSG
#define INC_DRAGMSG


//#include "pump.h" - in camtypes.h [AUTOMATICALLY REMOVED]


class DragManagerOp;
class DragInformation;



/*********************************************************************************************

>	class DragMessage : public Msg

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/1/95
	Purpose:	This message is sent to inform the system of important global drag events.
				Currently the only such event is DRAGSTARTING, sent whenever a global drag
				is started by calling DragManagerOp::StartDrag. It informs all interested
				parties that they should register DragTarget objects with the drag manager
				to handle the drag.

	Notes:		The IMPLEMENT_DYNAMIC can be found in kernel\draginfo.cpp

	SeeAlso:	DragManagerOp::StartDrag; DragTarget

	Documentation:	Docs\Specs\DragMan.doc

*********************************************************************************************/

class DragMessage : public Msg
{
	CC_DECLARE_DYNAMIC(DragMessage)

public:
	// drag messages are sent on these events.
	typedef enum DragState
	{
		DRAGSTARTED
	} DragState;
	
	DragState		State;				// The state, as defined above
	DragManagerOp	*pDragManager;		// The object responsible for managing the drag
	DragInformation	*pInfo;				// Information definining what is being dragged

										// Constructor
	DragMessage(DragState TheState, DragManagerOp *pTheManager, DragInformation *pTheInfo)
				: State(TheState), pDragManager(pTheManager), pInfo(pTheInfo)
		{ /* empty */ }
};


#endif

