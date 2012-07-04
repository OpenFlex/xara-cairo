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


#ifndef INC_PATHTYPE
#define INC_PATHTYPE


// This file describes the PathFlags and PathVerb types used by the path system
// This enables me to reduce the number of dependencies we have.

typedef BYTE PathVerb;

/********************************************************************************************

<	struct
<	PathFlags

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/94
	Comment:	The various flags associated with each control point on the path. They
				are as follows :-
				IsSelected - TRUE if the control point is selected
				IsSmooth - TRUE if the control point should be smoothed when the path is
				edited
				IsRotate - TRUE if this bezier control point should be kept colinear with
				its partner
				NeedToRender - TRUE if we need to render this control point during an edit
				IsEndPoint - TRUE if this control point is an EndPoint
				Spare1-3 - No specific use as yet but can be used for any localised task
				you perform on a path

********************************************************************************************/

struct PathFlags
{
	PathFlags();

	// Is this element of the path selected
	BYTE IsSelected : 1;

	// Flags to aid with the smoothing of curves
	BYTE IsSmooth : 1;
	BYTE IsRotate : 1;

	// Flags that help with the EORed rendering as the path is edited
	BYTE NeedToRender : 1;

	// All Endpoints in the path have this flag set
	BYTE IsEndPoint : 1;

	// May as well use up the spare bits in this byte for the future
	BYTE Spare1 : 1;
	BYTE Spare2 : 1;
	BYTE Spare3 : 1;
	inline INT32 operator ==(const PathFlags&);
	inline INT32 operator !=(const PathFlags&);
};

INT32 PathFlags::operator==(const PathFlags& rhs)
{
	if ((IsSelected == rhs.IsSelected) && 
		(IsSmooth == rhs.IsSmooth) &&
		(IsRotate == rhs.IsRotate) &&
		(NeedToRender == rhs.NeedToRender) &&
		(IsEndPoint == rhs.IsEndPoint) &&
		(Spare1 == rhs.Spare1) &&
		(Spare2 == rhs.Spare2) &&
		(Spare3 == rhs.Spare2)
	   )
	   		return 1;
	else
			return 0;

}

INT32 PathFlags::operator!=(const PathFlags& rhs)
{
	if ((IsSelected != rhs.IsSelected) || 
		(IsSmooth != rhs.IsSmooth) ||
		(IsRotate != rhs.IsRotate) ||
		(NeedToRender != rhs.NeedToRender) ||
		(IsEndPoint != rhs.IsEndPoint) ||
		(Spare1 != rhs.Spare1) ||
		(Spare2 != rhs.Spare2) ||
		(Spare3 != rhs.Spare2)
	   )
	   		return 1;
	else
			return 0;

}

#endif		// INC_PATHTYPE
