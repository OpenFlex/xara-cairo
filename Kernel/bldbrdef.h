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


// Blended Brush Definition header

#ifndef INC_BLBRUSHDEF
#define	INC_BLBRUSHDEF

#include "brshcomp.h"


/********************************************************************************************

>	class BlendedBrushDefinition : public BrushDefinition

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99

	Purpose:	Stores a vector Brush definition created by blending two other brush definitions.
				Unlike regular brush definitions these are not stored in the brush component, 
				instead they are attached to a BlendPathProcessorBrush for the purposes of rendering
				and are then destroyed
				They are also created differently, rather than passing in a subtree of nodes
				instead they are given already blended blendpaths and attribute maps.

	SeeAlso:	BrushDefinition (brshcomp.h/.cpp)

********************************************************************************************/

class BlendedBrushDefinition : public BrushDefinition
{
CC_DECLARE_DYNAMIC(BlendedBrushDefinition)	

public:
	BlendedBrushDefinition();
	~BlendedBrushDefinition();

	BOOL AllocateBrushRefArray(UINT32 NumObjects);
	BOOL AddBrushRef(BrushRef* pBrushRef);
};

#endif
