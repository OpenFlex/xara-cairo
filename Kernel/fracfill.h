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

// Short Description of what this file is for

#ifndef INC_FRACFILL
#define INC_FRACFILL


class KernelBitmap;

/********************************************************************************************

>	class PlasmaFractalFill: public CCObject;

	Author:			   Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:		   12/09/1994
	Purpose:		   A fractal fill class. Static fns only.

********************************************************************************************/


class PlasmaFractalFill: public	CCObject
{
	CC_DECLARE_DYNCREATE(PlasmaFractalFill);

	public:

	PlasmaFractalFill(
		INT32 tSeed = 0,
		BOOL tTileable = TRUE,
		fixed16 tSquash = 0,
		fixed16 tGraininess = 1,
		fixed16 tGravity = 0
		);

	static INT32 GetDimension(INT32 x, INT32 y);

	BOOL DoFill(KernelBitmap * pBitmap, INT32 Dimension=0, INT32 tOx=0, INT32 tOy=0);

	static void Test(KernelBitmap * pB,
		INT32 tSeed = 0,
		BOOL tTileable = TRUE,
		fixed16 tSquash = 0,
		fixed16 tGraininess = 1,
		fixed16 tGravity = 0
		);
	
	private:

	BOOL SubDivide(INT32 x1, INT32 y1, INT32 x2, INT32 y2,
		   						 	  INT32 p11, INT32 p12, INT32 p21, INT32 p22, BOOL PlotNow);

	inline INT32 Adjust(INT32 pa,INT32 pb,INT32 x, INT32 y,
					   INT32 aGraininess, INT32 aGravity);

	void SetSeed(INT32 NewSeed);
	inline INT32 GetRandom();


	KernelBitmap * pBitmap;

	INT32 Seed;
	UINT32 CurrentSeed;
	UINT32 CurrentSeed2;

	INT32 EigenValue;
	
	UINT32 xGraininess;
	UINT32 yGraininess;
	UINT32 xGravity;
	UINT32 yGravity;
	UINT32 CoordinateMask;
	
	INT32 MaxPotential;
	INT32 RecursionLevel;

	INT32 Width;
	INT32 Height;
	INT32 Ox;
	INT32 Oy;

	fixed16 Squash;

	BOOL ForceCornersToZero;
	BOOL Tileable;
 };



#endif  // INC_FRACFILL


