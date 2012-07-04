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

// This is the header file for the bitmap effect atom class

#ifndef INC_BFXATOM
#define INC_BFXATOM

#include "bfxbase.h"

class UndoableOperation;

/********************************************************************************************

>	class BitmapEffectAtom : public BitmapEffectBase

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Base class for all bitmap effect atoms

All bitmap effect atoms should be derived from this class

********************************************************************************************/

class BitmapEffectAtom : public BitmapEffectBase
{
	CC_DECLARE_DYNCREATE(BitmapEffectAtom);

	public:

	static void Test(INT32 Value);
	static void Test2(UndoableOperation * Op);

	protected:

	static INT32 TestValue;

};

/********************************************************************************************

>	class BitmapEffectSILT : public BitmapEffectAtom

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	SILT bitmap effect atom class provides class encapsulation for all SILT
				transforms

SILT = Spatially Invariant Linear Transform. These are implemented through McClellan transforms.
This includes many operations such as blur, sharpen, shadow etc. Each of these atoms is derived
from this class.

********************************************************************************************/

#define MAX_SILT_POINTS 32

class BitmapEffectSILT : public BitmapEffectAtom
{
	CC_DECLARE_DYNCREATE(BitmapEffectSILT);

	public:

	virtual BOOL Run();
/*
	virtual BOOL SetParameters();
	virtual BOOL GetEffectInfo(UINT32 * pOrderBitmap, UINT32 * pOrderEffect,
				   UINT32 * pPlotEstimate);
*/
//	static BOOL RunA();
	
	protected:
/*
	INT32 Points;

	double ContourSpacing;

	double ContourHeight[MAX_SILT_POINTS+1];
	double BVales[MAX_SILT_POINTS+1];
	double OutputGain;
	double OutputOffset;

	INT32 LogSpacing;
*/

};



#endif  // INC_BFXATOM


