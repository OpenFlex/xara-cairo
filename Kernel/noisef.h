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


#ifndef INC_NOISEFILL
#define INC_NOISEFILL

class KernelBitmap;

/********************************************************************************************

>	class NoiseFractalFill: public CCObject;

	Author:	   Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:   12/09/1994
	Purpose:   A noise based fill. Really simple

********************************************************************************************/

class NoiseFractalFill : public CCObject
{
	CC_DECLARE_DYNCREATE(NoiseFractalFill);

	public:
		NoiseFractalFill();

		BOOL DoFill(double scale, 
					UINT32 seed,
					KernelBitmap *pBitmap) const;
};



#endif



