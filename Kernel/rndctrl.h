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


// RNDCTRL.H
//
// Created: 29/6/93 by Will
//

#ifndef INC_RNDCTRL
#define INC_RNDCTRL


/********************************************************************************************

>	class RenderControl : public CCObject

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/5/93
	Purpose:	A RenderControl object is created to control the interruption of rendering.
				It provides a Stop function which can be called by a rendering routine to 
				determine whether or not it should stop.

********************************************************************************************/

class RenderControl : public CCObject
{
public:
	RenderControl();

	BOOL StopRendering();
};

#endif
