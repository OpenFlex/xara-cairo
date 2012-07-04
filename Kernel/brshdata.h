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


// object containing the data that control the brush

#ifndef BRUSHDATA_H
#define BRUSHDATA_H

#include "brshcomp.h"

class CCObject;

/***********************************************************************************************

>	class BrushData : public CCObject

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/3/2000

	Purpose:	A repository for all kinds of data that the brush uses.  More of a struct than
				a class at the moment

***********************************************************************************************/

class BrushData: public CCObject
{
public:
	BrushData();
	BrushData(const BrushData& Other);

	const BrushData& operator=(const BrushData& Other);
	BOOL operator==(const BrushData& Other);
public: // all data is public right now
	
	String_32           m_Name;	// the name

	BrushHandle			m_BrushHandle; // identifies which brush definition to use

	MILLIPOINT			m_BrushSpacing;  // the basic spacing along the path
						// edit field title - Brush spcaing
	
	double				m_BrushSpacingIncrProp; // the proportional spacing increment
						// edit title = proportional increase. Note this can never be negative and defaults to 1.0

	MILLIPOINT			m_BrushSpacingIncrConst; // the constant spacing increment
						// title = constant increase, defaults to 0

	UINT32				m_BrushSpacingMaxRand; // the upper bound for spacing randomness    
						// title ~ maximum random effect (%) defaults to 0, maybe use a slider?

	UINT32				m_BrushSpacingRandSeed; // the random seed for spacing
						// NO EDIT FIELD for random seeds, however need a 'Generate new random sequence' button will be needed

	BOOL				m_bTile;  // do we tile the fill attribute? - radio/tick box
	BOOL			    m_bRotate; //rotate tangentially to the path, perhaps Tangent is better title, or rotate along path
	double				m_RotateAngle;  // edit field - rotation angle
	double				m_RotAngleIncrConst;
	double				m_RotAngleIncrProp;
	UINT32				m_RotationMaxRand; // maximum randomness effect
	UINT32				m_RotationRandSeed; 
	UINT32				m_RotationMaxPressure;

	PathOffset			m_PathOffsetType;  // the type of offset pattern (see enum in brshcomp.h)
						/* This can take the following types:
						OFFSET_NONE,
						OFFSET_ALTERNATE,
						OFFSET_LEFT,
						OFFSET_RIGHT,
						OFFSET_RANDOM
						*/

	MILLIPOINT			m_PathOffsetValue; // size of the offset, maybe call it offset amount?
	
	double				m_PathOffsetIncrProp; // proportional offset increment
						// offset proportional increase

	MILLIPOINT			m_PathOffsetIncrConst; // Constant offset increment
						// offset constant increase
	UINT32				m_OffsetTypeRandSeed;  
	UINT32				m_OffsetValueMaxRand; // maximum random offset value
	UINT32				m_OffsetValueRandSeed;
	
	double				m_BrushScaling;    // how much to scale the objects by
						// edit title - object scaling, defaults to 1.0

	double				m_BrushScalingIncr; // the scaling increment
						// we only have a proportional scaling increment

	double				m_BrushScalingIncrConst; // now we have an all-new fixed increment

	UINT32				m_BrushScalingMaxRand; // the upper bound for scaling randomness    
						// maximum random effect on scaling, could maybe ues a slider for this

	UINT32				m_BrushScalingRandSeed; // the random seed for scaling
	
	UINT32				m_ScalingMaxPressure;   // the extent to which pressure affects scaling

	SequenceType		m_SequenceType;     // the type of sequence (if we have > 1 ink object)
						/* this is for brushes with multiple objects - the following sequence types are available:
						SEQ_FORWARD,
						SEQ_BACKWARD,
						SEQ_MIRROR,
						SEQ_RANDOM
						*/
	
	UINT32				m_SequenceRandSeed; // if we have a random sequence this is the seed
						// need a 'regenerate random sequence' button					

	MILLIPOINT          m_LineWidth;   // the line width of the path we are processing
						// not sure if we want to include this in the dialog?
	
	BOOL				m_bUseLocalFillColour;
	BOOL				m_bUseLocalTransp;
	BOOL				m_bUseNamedColour;

	BOOL				m_bTimeStampBrushes;  // are we using timestamping
						// not quite sure what to call this, but its a tick/radio
	UINT32				m_TimeStampPeriod; // in milliseconds, the time before another object is rendered
						// this field should only be available is m_bTimeStampBrushes is TRUE, likewise if it
						// is true then the Spacing options should be greyed out.
						// Note also that editing this field can not be performed on existing brushes in the selection

	double				m_BrushHueIncrement;  // the amount that the hue increases/decreases each time
	UINT32				m_BrushHueMaxRand;    // the maximum random amount of hue
	UINT32				m_BrushHueRandSeed;

	double				m_BrushSatIncrement;  // as above but for saturation
	UINT32				m_BrushSatMaxRand;
	UINT32				m_BrushSatRandSeed;

	INT32				m_BrushTransparency;
	UINT32				m_TranspMaxPressure;

	/* Possible extra things we might have:
	UINT32				ScalingMaxPressure;
	UINT32				SpacingMaxPressure;
	
	UINT32				TimeStampingMaxPressure;
	UINT32				OffsetMaxPressure;

	UINT32				ColourMaxRand;
	UINT32				ColourMaxPressure;
	*/
};

#endif
