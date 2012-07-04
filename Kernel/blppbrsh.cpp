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


// blended path processor brush implementation

#include "camtypes.h"
#include "blppbrsh.h"
#include "bldbrdef.h"

CC_IMPLEMENT_DYNAMIC(BlendedPathProcessorBrush, PathProcessorBrush);

#define new CAM_DEBUG_NEW  

/********************************************************************************************

>	BlendedPathProcessorBrush::BlendedPathProcessorBrush()

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/3/2000

	Purpose:	Constructor, mostly just calls the base class version

********************************************************************************************/

BlendedPathProcessorBrush::BlendedPathProcessorBrush() : PathProcessorBrush()
{
	m_pBlendedBrushDef = NULL;
}


/********************************************************************************************

>	BlendedPathProcessorBrush::~BlendedPathProcessorBrush()

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/3/2000

	Purpose:	Destructor
********************************************************************************************/

BlendedPathProcessorBrush::~BlendedPathProcessorBrush()
{

}

	
/********************************************************************************************

>	virtual BrushDefinition* BlendedPathProcessorBrush::GetOurBrushDefinition() 

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/99
	Returns:	if we have a blended brush definition then we will return that, otherwise
				we will use the base class
	Purpose:	As above

********************************************************************************************/

BrushDefinition* BlendedPathProcessorBrush::GetOurBrushDefinition()
{
	if (m_pBlendedBrushDef != NULL)
		return m_pBlendedBrushDef;

	return PathProcessorBrush::GetOurBrushDefinition();
}

	
/********************************************************************************************

>	void BlendedPathProcessorBrush::SetBlendedBrushDefinition(BlendedBrushDefinition* pDef) 

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/99
	Inputs:		A blended brush definition, this can be NULL
	Returns:	-
	Purpose:	As above

********************************************************************************************/

void BlendedPathProcessorBrush::SetBlendedBrushDefinition(BlendedBrushDefinition* pDef)
{
	m_pBlendedBrushDef = pDef;
}
	
	
/********************************************************************************************

>	void BlendedPathProcessorBrush::DeleteBlendedBrushDefinition()

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/99
	Inputs:		-
	Returns:	-
	Purpose:	Deletes the blended brush definition, use with caution, as the brush defintions
				are often used by multiple path processors

********************************************************************************************/

void BlendedPathProcessorBrush::DeleteBlendedBrushDefinition()
{
	if (m_pBlendedBrushDef != NULL)
		delete m_pBlendedBrushDef;
	m_pBlendedBrushDef = NULL;
}

/********************************************************************************************

>	BOOL BlendedPathProcessorBrush::SetBlendRatio(double Ratio) 

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/99
	Returns:	TRUE if Ratio is in the range 0-1, otherwise false
	Purpose:	As above

********************************************************************************************/

BOOL BlendedPathProcessorBrush::SetBlendRatio(double Ratio)
{
	if (Ratio < 0 || Ratio > 1)
		return FALSE;
	m_BlendRatio = Ratio;
	return TRUE;
}




/********************************************************************************************

>	virtual PathProcessorBrush *PathProcessorBrush::Clone(void)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99

	Returns:	NULL if we're out of memory, else
				a pointer to a clone (exact copy) of this object

	Purpose:	To copy BlendedPathProcessorBrush or derived-class object, exactly the same as
				the PPB fn. except for the BlendedBrushDef.

********************************************************************************************/

PathProcessorBrush *BlendedPathProcessorBrush::Clone(void)
{

	// Clone this object 
	BlendedPathProcessorBrush *pClone = new BlendedPathProcessorBrush;

	if (pClone == NULL)
		return NULL;

	// copy the data
	pClone->SetBrushDefinition(m_BrushHandle);
	pClone->SetPathOffsetType(m_PathOffsetType);
	pClone->SetPathOffsetValue(m_PathOffsetValue);
	pClone->SetRotated(m_bRotate);
	pClone->SetRotationAngle(m_RotateAngle);
	pClone->SetSpacing(m_BrushSpacing);
	pClone->SetTiling(m_bTile);
	pClone->SetBrushScaling(m_BrushScaling);
	pClone->SetBrushScalingIncr(m_BrushScalingIncr);
	pClone->SetSpacingIncrProp(m_BrushSpacingIncrProp);
	pClone->SetSpacingIncrConst(m_BrushSpacingIncrConst);
	pClone->SetPathOffsetIncrConst(m_PathOffsetIncrConst);
	pClone->SetPathOffsetIncrProp(m_PathOffsetIncrProp);
	pClone->SetSpacingMaxRand(m_BrushSpacingMaxRand);
	pClone->SetSpacingRandSeed(m_BrushSpacingRandSeed);
	pClone->SetScalingMaxRand(m_BrushScalingMaxRand);
	pClone->SetScalingRandSeed(m_BrushScalingRandSeed);
	pClone->SetSequenceType(m_SequenceType);
	pClone->SetSequenceSeed(m_SequenceRandSeed);
	pClone->SetOffsetValueMaxRand(m_OffsetValueMaxRand);
	pClone->SetOffsetValueRandSeed(m_OffsetValueRandSeed);
	pClone->SetOffsetTypeRandSeed(m_OffsetTypeRandSeed);

	pClone->SetRotationMaxRand(m_RotationMaxRand);
	pClone->SetRotationRandSeed(m_RotationRandSeed);

	pClone->SetUseLocalFillColour(m_bUseLocalFillColour);

	pClone->SetParentAttribute(m_pParentAttr);
	
	pClone->SetBlendedBrushDefinition(m_pBlendedBrushDef);

	return(pClone);
}
	
/********************************************************************************************

>	double BlendedPathProcessorBrush::GetBlendRatio() 

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/99
	Returns:	our blend ratio member
	Purpose:	As above

********************************************************************************************/

double BlendedPathProcessorBrush::GetBlendRatio()
{
	return m_BlendRatio;
}
