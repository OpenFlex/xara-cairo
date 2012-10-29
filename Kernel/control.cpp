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
// Implementation of NodeController.
//

// header files.
#include "camtypes.h"
#include "control.h"
/*
#include "objchge.h" 
#include "textops.h"

// source-safe version number.

// dynamic runtime type info.
CC_IMPLEMENT_DYNAMIC(NodeController, NodeGroup)

// Use debugging 'new' when necessary.
#define new CAM_DEBUG_NEW
*/


/********************************************************************************************

>	virtual BOOL NodeController::AllowOp_AccountForCompound(ObjChangeParam* pParam,
															BOOL SetOpPermissionState,
															BOOL DoPreTriggerEdit)
	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/10/2000
	Inputs:		pParam					information about the requested change, eg which Op.
				SetOpPermissionState	whether flags should be set ready for OnChildChange.
				DoPreTriggerEdit		if TRUE then NameGallery::PreTriggerEdit is called.
										*Must* be TRUE if the calling Op may make any nodes
										change their bounds, eg move, line width, cut.
										Use TRUE if unsure.

	Returns:	TRUE if ANY of the objects in the compound node have allowed the op.

	Purpose:	Overrides Node::AllowOp_AccountForCompound - see definition of that function
				for a general explanation.

				Controller nodes need to inform all of their other children whenever one
				child is queried via AllowOp. This is because unlike a normal group, editing
				one child may well affect its siblings, who must be informed of the edit.

	See Also:	Node::AllowOp, Node::AllowOp_AccountForCompound

	Notes:		Karim 20/12/2000
				Added the OpTextFormat bodge for feathers on bevelled text - sorry!

********************************************************************************************/
/*BOOL NodeController::AllowOp_AccountForCompound(ObjChangeParam* pParam,
												BOOL SetOpPermissionState,
												BOOL DoPreTriggerEdit)
{
	BOOL AnyAllowed = FALSE;

	Node* pCallingChild = (pParam->GetDirection() == OBJCHANGE_CALLEDBYCHILD) ?
													pParam->GetCallingChild() : NULL;
	pParam->SetCallingChild(NULL);

	ObjChangeFlags Flags = pParam->GetChangeFlags();
	UndoableOperation* pChangeOp = pParam->GetOpPointer();

	if (Flags.Attribute || Flags.TransformNode || Flags.RegenerateNode ||
		(pChangeOp != NULL && pChangeOp->IS_KIND_OF(OpTextUndoable)) )
	{

		ObjChangeDirection OldDirection = pParam->GetDirection();
		pParam->SetDirection(OBJCHANGE_CALLEDBYPARENT);
		Node* pNode = FindFirstChild();

		BOOL InformGeomLinkedAttrs =	SetOpPermissionState &&
										pChangeOp != NULL &&
										pChangeOp->MayChangeNodeBounds();

		while (pNode != NULL)
		{
			if (pNode != pCallingChild)
			{
				if (pNode->IsAnObject())
					AnyAllowed |= pNode->AllowOp(pParam, SetOpPermissionState, DoPreTriggerEdit);
				else
				{
					if (pNode->IsAnAttribute() && ((NodeAttribute*)pNode)->IsLinkedToNodeGeometry())
						if (InformGeomLinkedAttrs)
							((NodeAttribute*)pNode)->LinkedNodeGeometryHasChanged(pChangeOp);
				}
			}

			pNode = pNode->FindNext();
		}

		pParam->SetDirection(OldDirection);
	}

	// if setting flags and any child allowed it, set this permission allowed
	if (SetOpPermissionState && AnyAllowed)
		SetOpPermission(PERMISSION_ALLOWED);

	return AnyAllowed;
}
*/
