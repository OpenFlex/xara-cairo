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

//
// Declaration of NodeController.
//

#ifndef INC_CONTROL
#define INC_CONTROL

//#include "group.h"		// derivation from NodeGroup



/********************************************************************************************

>	class NodeController : public NodeGroup

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/10/2000

	Purpose:	Shadow, bevel and contour controllers are finally getting a base class,
				in which common code can now live. These nodes are distinct from other
				group nodes, in that:
				
					i)	the user is (just about) completely unaware of them - objects
						'grouped' within them don't appear to be grouped together.

					ii) when the user edits one node within the controller, eg they resize
						a shadowed circle, the other node often needs to know of the change,
						eg the shadow needs to regenerate. This behaviour does not apply to
						normal groups.

********************************************************************************************/
/*class NodeController : public NodeGroup
{
// runtime type info please.
CC_DECLARE_DYNCREATE(NodeController);

public:
	NodeController() : NodeGroup() {}
	NodeController(	Node* ContextNode,
					AttachNodeDirection Direction,
					BOOL Locked=FALSE,
					BOOL Mangled=FALSE,
					BOOL Marked=FALSE,
					BOOL Selected=FALSE) :
				NodeGroup(ContextNode, Direction, Locked, Mangled, Marked, Selected) {}

//	virtual BOOL AllowOp_AccountForCompound(ObjChangeParam* pParam,
//											BOOL SetOpPermissionState = TRUE,
//											BOOL DoPreTriggerEdit = TRUE);
};
*/


#endif
