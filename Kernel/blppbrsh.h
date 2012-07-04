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


// Blended Path Processor Brush header

#ifndef INC_BLPPBRUSH
#define INC_BLPPBRUSH

#include "ppbrush.h"

class BlendedBrushDefinition;

/********************************************************************************************

>	class BlendedPathProcessorBrush : public PathProcessorBrush

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/3/2000

	Purpose:    This class of path processor is generated when two brushed nodes are blended.
				It differs from a regular PPB in that it does not retrieve its ink objects from
				a brush definition stored in the brush component, instead it has its own pointer
				to a BlendedBrushDefinition object.

	SeeAlso:	if you're not familiar with ppbrush.h/.cpp this will make little sense to you
********************************************************************************************/

class BlendedPathProcessorBrush : public PathProcessorBrush
{
	CC_DECLARE_DYNAMIC(BlendedPathProcessorBrush);

public: 
	BlendedPathProcessorBrush();
	~BlendedPathProcessorBrush();

public: // overrideables
	virtual BrushDefinition* GetOurBrushDefinition();
	virtual PathProcessorBrush *Clone(void);
	
	virtual BOOL IsBlended() { return TRUE;}
public: // access, etc


	void    SetBlendedBrushDefinition(BlendedBrushDefinition* pBrushDef);
	BOOL    SetBlendRatio(double Ratio);
	double  GetBlendRatio();
	void	DeleteBlendedBrushDefinition();

	
protected: // DATA
	BlendedBrushDefinition* m_pBlendedBrushDef;  // the brush definition that will give us our ink objects and attributes

	double					m_BlendRatio;     


};
	
#endif
