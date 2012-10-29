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


CC_IMPLEMENT_DYNAMIC(AnimPropertiesParam, OpParam)

// This line mustn't go before any CC_IMPLEMENT_... macros
#define new CAM_DEBUG_NEW


/********************************************************************************************

>	FramePropertiesParam::FramePropertiesParam()

	Author:		Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/05/97
	Scope:		public

********************************************************************************************/

FramePropertiesParam::FramePropertiesParam()
{
	m_FrameName = "";
	m_FrameDelay = 50;
	m_Overlay = FALSE;
	m_Solid = FALSE;
};




/********************************************************************************************

>	AnimPropertiesParam::AnimPropertiesParam()

	Author:		Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/05/97
	Scope:		public

********************************************************************************************/

AnimPropertiesParam::AnimPropertiesParam()
{
	m_Animloop			=	0;
	m_GlobalAnimDelay	=	50;
	m_Dither			=	XARADITHER_NONE;
	m_Palette			=	PAL_GLOBAL;
	m_PaletteColours	=	PALCOL_OPTIMIZED;
	m_NumColsInPalette	=	256;
	m_UseSystemColours	=	FALSE;
	m_BackGroundIsTransp =  FALSE;
};




/********************************************************************************************

>	AnimPropertiesParam& AnimPropertiesParam::operator=(const AnimPropertiesParam& obj)

	Author:		Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/05/97
	Scope:		public

********************************************************************************************/

AnimPropertiesParam& AnimPropertiesParam::operator=(const AnimPropertiesParam& obj)
{
	if (this == &obj)	return *this;

	m_Animloop			=	obj.m_Animloop;
	m_GlobalAnimDelay	=	obj.m_GlobalAnimDelay;
	m_Dither			=	obj.m_Dither;
	m_Palette			=	obj.m_Palette;
	m_PaletteColours	=	obj.m_PaletteColours;
	m_NumColsInPalette	=	obj.m_NumColsInPalette;
	m_UseSystemColours	=	obj.m_UseSystemColours;

	m_BoundingRect		=	obj.m_BoundingRect;

	return *this;
};




