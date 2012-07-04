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

// This is the header file for the bitmap effect class

#ifndef INC_BFXTEST
#define INC_BFXTEST

#include "bitmapfx.h"

/********************************************************************************************

>	class TestBitmapEffect : public BitmapEffect

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Test class

This class is for test purposes only

********************************************************************************************/

class TestBitmapEffect : public BitmapEffect
{
	CC_DECLARE_DYNCREATE(TestBitmapEffect);

	public:

	BOOL Run();
	
	protected:

};

#endif  // INC_BFXTEST


