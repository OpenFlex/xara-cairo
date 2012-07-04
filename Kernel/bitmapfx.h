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

#ifndef INC_BITMAPFX
#define INC_BITMAPFX

#include "bfxbase.h"

class KernelBitmap;

/********************************************************************************************

>	class BitmapEffect : public BitmapEffectBase

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Base class for all bitmap effects

This class is intended to provide a usefully organised chain of BitmapEffectAtoms to the user.
The chain may be of length 1. The user should be able to use all of these classes.

All BitmapEffects should be derived from this class.

Though this class has nothing in it at the moment, it should have things to register it with
the main list, to read the format of parameters etc. It's also useful for as a pointer type,
i.e. the rest of the program should use BitmapEffect * when they want to refer to a bitmap
effect.

********************************************************************************************/

class BitmapEffect : public BitmapEffectBase
{
	CC_DECLARE_DYNCREATE(BitmapEffect);

	public:

	
	protected:

};

/********************************************************************************************

>	class AccusoftBitmapEffect : public BitmapEffect

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Base class for all accusoft bitmap effects

This class provides a bit of ALU interface

********************************************************************************************/

class AccusoftBitmapEffect : public BitmapEffect
{
	CC_DECLARE_DYNCREATE(AccusoftBitmapEffect);

	public:

	AccusoftBitmapEffect():BitmapEffect() {SetParameters();};
	virtual KernelBitmap * GetProcessedBitmap(KernelBitmap * pOriginal);

	virtual BOOL SetParameters(INT32 p1=0, INT32 p2=0, INT32 p3=0, double * pD=NULL)
					{ Param1=p1; Param2=p2; Param3=p3; pDouble=pD; return TRUE;};

	protected:
	INT32 Param1;
	INT32 Param2;
	INT32 Param3;
	double * pDouble;
	
	virtual KernelBitmap * DoALUWork();
};


// Here's a derived class macro
#define MakeABFX(Class) \
class ABFX##Class : public AccusoftBitmapEffect \
{ \
	CC_DECLARE_DYNCREATE(ABFX##Class); \
	protected: \
	virtual KernelBitmap * DoALUWork(); \
}

MakeABFX(FlipX);
MakeABFX(FlipY);
MakeABFX(Rotate90);
MakeABFX(Rotate180);
MakeABFX(Rotate270);
MakeABFX(BayerMono);
MakeABFX(HalftoneMono);
MakeABFX(DiffusionMono);
MakeABFX(BayerColour);
MakeABFX(DiffusionColour);
MakeABFX(PopularityColour);
MakeABFX(MakeGreyscale);
MakeABFX(Octree);
MakeABFX(Resize);
MakeABFX(BrightnessContrast);
MakeABFX(SharpenBlur);
MakeABFX(SpecialEffect);
MakeABFX(RemoveDither);

#endif  // INC_BITMAPFX


