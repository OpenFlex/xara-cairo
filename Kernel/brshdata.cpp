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



#include "camtypes.h"
#include "brshdata.h"



/***********************************************************************************************

>	BrushData::BrushData()

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/3/2000

	Purpose:	Constructor

***********************************************************************************************/
BrushData::BrushData()
{
	m_BrushHandle			= BrushHandle_NoBrush;

	m_BrushSpacing			= 10000;
	m_BrushSpacingIncrProp  = 1.0; 
	m_BrushSpacingIncrConst = 0;
	m_BrushSpacingMaxRand   = 0;
	m_BrushSpacingRandSeed  = 0;
	
	m_bTile                 = TRUE;
	m_bRotate               = FALSE;
	m_RotateAngle			= 0.0;
	m_RotAngleIncrConst		= 0;
	m_RotAngleIncrProp      = 1.0;
	m_RotationMaxRand		= 0;	
	m_RotationRandSeed		= 0; 
	m_RotationMaxPressure		= 0;

	m_PathOffsetType		= OFFSET_NONE;  
	m_PathOffsetValue		= 0;
	m_PathOffsetIncrProp	= 1.0;
	m_PathOffsetIncrConst	= 0;
	m_OffsetTypeRandSeed    = 0;
	
	m_OffsetValueMaxRand	= 0;
	m_OffsetValueRandSeed	= 0;
	
	m_BrushScaling			= 1.0;
	m_BrushScalingIncr      = 1.0;
	m_BrushScalingIncrConst = 0.0;
	m_BrushScalingMaxRand	= 0;
	m_BrushScalingRandSeed	= 0;
	
	m_SequenceType			= SEQ_FORWARD;
	m_SequenceRandSeed		= 0;

	m_LineWidth				= -1;

	m_bUseLocalFillColour	= FALSE;
	m_bUseLocalTransp       = FALSE;
	m_bUseNamedColour       = TRUE;
	m_bTimeStampBrushes     = FALSE;
	m_TimeStampPeriod       = 0;

	m_BrushTransparency     = -1;
	m_TranspMaxPressure     = 0;

}


/***********************************************************************************************

>	BrushData::BrushData(BrushData Other)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/3/2000

	Purpose:	copy Constructor

***********************************************************************************************/

BrushData::BrushData(const BrushData &Other)
{
	this->operator =(Other);
}

/***********************************************************************************************

>	BrushData::operator=(BrushData Other)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/3/2000

	Purpose:	assignment operator

***********************************************************************************************/

const BrushData& BrushData::operator =(const BrushData& Other)
{
	m_Name                  = Other.m_Name;
	m_BrushHandle			= Other.m_BrushHandle;

	m_BrushSpacing			= Other.m_BrushSpacing;
	m_BrushSpacingIncrProp  = Other.m_BrushSpacingIncrProp;
	m_BrushSpacingIncrConst = Other.m_BrushSpacingIncrConst;
	m_BrushSpacingMaxRand   = Other.m_BrushSpacingMaxRand;
	m_BrushSpacingRandSeed  = Other.m_BrushSpacingRandSeed;
	
	m_bTile                 = Other.m_bTile;
	m_bRotate               = Other.m_bRotate;
	m_RotateAngle			= Other.m_RotateAngle;
	m_RotAngleIncrProp      = Other.m_RotAngleIncrProp;
	m_RotAngleIncrConst     = Other.m_RotAngleIncrConst;
	m_RotationMaxRand		= Other.m_RotationMaxRand;	
	m_RotationRandSeed		= Other.m_RotationRandSeed;
	m_RotationMaxPressure   = Other.m_RotationMaxPressure;

	m_PathOffsetType		= Other.m_PathOffsetType; 
	m_PathOffsetValue		= Other.m_PathOffsetValue;
	m_PathOffsetIncrProp	= Other.m_PathOffsetIncrProp;
	m_PathOffsetIncrConst	= Other.m_PathOffsetIncrConst;
	m_OffsetTypeRandSeed    = Other.m_OffsetTypeRandSeed;
	
	m_OffsetValueMaxRand	= Other.m_OffsetValueMaxRand;
	m_OffsetValueRandSeed	= Other.m_OffsetValueRandSeed;
	
	m_BrushScaling			= Other.m_BrushScaling;
	m_BrushScalingIncr      = Other.m_BrushScalingIncr;
	m_BrushScalingIncrConst = Other.m_BrushScalingIncrConst;
	m_BrushScalingMaxRand	= Other.m_BrushScalingMaxRand;
	m_BrushScalingRandSeed	= Other.m_BrushScalingRandSeed;
	m_ScalingMaxPressure    = Other.m_ScalingMaxPressure;
	
	m_SequenceType			= Other.m_SequenceType;
	m_SequenceRandSeed		= Other.m_SequenceRandSeed;

	m_LineWidth				= Other.m_LineWidth;

	m_bUseLocalFillColour	= Other.m_bUseLocalFillColour;
	m_bUseLocalTransp       = Other.m_bUseLocalTransp;
	m_bUseNamedColour       = Other.m_bUseNamedColour;
	m_bTimeStampBrushes     = Other.m_bTimeStampBrushes;
	m_TimeStampPeriod       = Other.m_TimeStampPeriod;

	m_BrushSatIncrement		= Other.m_BrushSatIncrement;
	m_BrushSatMaxRand		= Other.m_BrushSatMaxRand;
	m_BrushSatRandSeed		= Other.m_BrushSatRandSeed;
	m_BrushHueIncrement		= Other.m_BrushHueIncrement;
	m_BrushHueMaxRand		= Other.m_BrushHueMaxRand;
	m_BrushHueRandSeed		= Other.m_BrushHueRandSeed;

	m_BrushTransparency     = Other.m_BrushTransparency;
	m_TranspMaxPressure     = Other.m_TranspMaxPressure;

	return *this;
}

/***********************************************************************************************

>	BOOL BrushData::operator ==(const BrushData& Other)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/3/2000

	Purpose:	equality operator

***********************************************************************************************/

BOOL BrushData::operator ==(const BrushData& Other)
{
	if (
		m_Name                  != Other.m_Name ||
		m_BrushHandle			!= Other.m_BrushHandle ||

		m_BrushSpacing			!= Other.m_BrushSpacing ||
		m_BrushSpacingIncrProp  != Other.m_BrushSpacingIncrProp ||
		m_BrushSpacingIncrConst != Other.m_BrushSpacingIncrConst ||
		m_BrushSpacingMaxRand   != Other.m_BrushSpacingMaxRand ||
		m_BrushSpacingRandSeed  != Other.m_BrushSpacingRandSeed ||
		
		m_bTile                 != Other.m_bTile ||
		m_bRotate               != Other.m_bRotate ||
		m_RotateAngle			!= Other.m_RotateAngle ||
		m_RotAngleIncrProp      != Other.m_RotAngleIncrProp ||
		m_RotAngleIncrConst     != Other.m_RotAngleIncrConst ||
		m_RotationMaxRand		!= Other.m_RotationMaxRand ||	
		m_RotationRandSeed		!= Other.m_RotationRandSeed ||
		m_RotationMaxPressure   != Other.m_RotationMaxPressure ||

		m_PathOffsetType		!= Other.m_PathOffsetType || 
		m_PathOffsetValue		!= Other.m_PathOffsetValue ||
		m_PathOffsetIncrProp	!= Other.m_PathOffsetIncrProp ||
		m_PathOffsetIncrConst	!= Other.m_PathOffsetIncrConst ||
		m_OffsetTypeRandSeed    != Other.m_OffsetTypeRandSeed ||
		
		m_OffsetValueMaxRand	!= Other.m_OffsetValueMaxRand ||
		m_OffsetValueRandSeed	!= Other.m_OffsetValueRandSeed ||
		
		m_BrushScaling			!= Other.m_BrushScaling ||
		m_BrushScalingIncr      != Other.m_BrushScalingIncr ||
		m_BrushScalingIncrConst != Other.m_BrushScalingIncrConst ||
		m_BrushScalingMaxRand	!= Other.m_BrushScalingMaxRand ||
		m_BrushScalingRandSeed	!= Other.m_BrushScalingRandSeed ||
		m_ScalingMaxPressure    != Other.m_ScalingMaxPressure ||
		
		m_SequenceType			!= Other.m_SequenceType ||
		m_SequenceRandSeed		!= Other.m_SequenceRandSeed ||

		m_LineWidth				!= Other.m_LineWidth ||

		m_bUseLocalFillColour	!= Other.m_bUseLocalFillColour ||
		m_bUseLocalTransp       != Other.m_bUseLocalTransp ||
		m_bUseNamedColour       != Other.m_bUseNamedColour ||
		m_bTimeStampBrushes     != Other.m_bTimeStampBrushes ||
		m_TimeStampPeriod       != Other.m_TimeStampPeriod ||

		m_BrushSatIncrement		!= Other.m_BrushSatIncrement ||
		m_BrushSatMaxRand		!= Other.m_BrushSatMaxRand ||
		m_BrushSatRandSeed		!= Other.m_BrushSatRandSeed ||
		m_BrushHueIncrement		!= Other.m_BrushHueIncrement ||
		m_BrushHueMaxRand		!= Other.m_BrushHueMaxRand ||
		m_BrushHueRandSeed		!= Other.m_BrushHueRandSeed ||

		m_BrushTransparency     != Other.m_BrushTransparency ||
		m_TranspMaxPressure     != Other.m_TranspMaxPressure
		)
		return FALSE;
	else
		return TRUE;
}
