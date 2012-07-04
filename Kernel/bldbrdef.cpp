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


// Blended Brush Definition implementation

#include "camtypes.h"
#include "bldbrdef.h"
#include "brushref.h"

CC_IMPLEMENT_DYNAMIC(BlendedBrushDefinition, BrushDefinition);

#define new CAM_DEBUG_NEW  

/********************************************************************************************

>	BlendedBrushDefinition::BlendedBrushDefinition();

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/2/97

	Purpose:	Constructor

	SeeAlso:

********************************************************************************************/

BlendedBrushDefinition::BlendedBrushDefinition()
{
	// parent class fn. initialises all the data to defaults
	ResetMembers();
}

/********************************************************************************************

>	BlendedBrushDefinition::~BlendedBrushDefinition();

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/2/97

	Purpose:	Destructor, simply calls the parent class right now

	SeeAlso:   ~BrushDefinition()

********************************************************************************************/

BlendedBrushDefinition::~BlendedBrushDefinition()  
{
	// because we made all the attr maps by hand we must go through them and delete them individually
	for (INT32 i = 0; i < m_BrushRefPtrArray.GetSize(); i++)
	{
		BrushRef* pBrushRef = m_BrushRefPtrArray[i];
		if (pBrushRef != NULL)
			pBrushRef->DeleteAttributesAndPath();
	}
}


/********************************************************************************************

>	BOOL BlendedBrushDefinition::AllocateBrushRefArray(UINT32 NumObjects);

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/2/97
	Inputs:     the size of the array to allocatew
	Returns:	TRUE if it went alright, FALSE if not
	Purpose:	Allocates the brushref array.  Actually an interface to the parent class function,
				we need public access to it in this class because the brushrefs are generated 
				externally rather than internally in the parent class.

	SeeAlso:   

********************************************************************************************/

BOOL BlendedBrushDefinition::AllocateBrushRefArray(UINT32 NumObjects)
{
	InitialiseBrushArray(NumObjects);
	return TRUE;
}


/********************************************************************************************

>	BOOL BlendedBrushDefinition::AddBrushRef(BrushRef* pBrushRef);

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/2/97
	Inputs:     brushref to add to this definition
	Returns:	TRUE if it went alright, FALSE if not
	Purpose:	Adds a brushref to the next vacant spot in the array.  Once again a public fn. is
				needed as brushrefs for BlendedBD's are generated outside.

	SeeAlso:   

********************************************************************************************/

BOOL BlendedBrushDefinition::AddBrushRef(BrushRef* pBrushRef)
{
	if (pBrushRef == NULL)
	{
		ERROR3("Trying to add a NULL BrushRef");
		return FALSE;
	}
	m_BrushRefPtrArray[m_NumBrushObjects++] = pBrushRef;

	return TRUE;
}
