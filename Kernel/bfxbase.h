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

// This is the header file for the bitmap effect base class

#ifndef INC_BFXBASE
#define INC_BFXBASE


class KernelBitmap;
class BfxALU;

/********************************************************************************************

>	class BitmapEffectBase : public ListItem

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Base class for all bitmap effects

All bitmap effects and atoms are derived from this class.

********************************************************************************************/

class BitmapEffectBase : public ListItem
{
	CC_DECLARE_DYNCREATE(BitmapEffectBase);

	public:

	BitmapEffectBase();			 /* Constructor */
	virtual ~BitmapEffectBase();	     /* Destructor */

	virtual BOOL SetParameters(); /* Default */
	
	virtual BOOL SetSourceImage(KernelBitmap * theSource);
	virtual BOOL GetEffectInfo(UINT32 * pOrderBitmap, UINT32 * pOrderEffect, UINT32 * pPlotEstimate);

	virtual BOOL GetDestinationInfo(UINT32 * pDestinationSize,
									INT32 * pDestinationDepth,
									UINT32 * pDestinationWidth,
									UINT32 * pDestinationHeight);
	virtual BOOL UseDestinationBitmap(KernelBitmap * theDestination);

	virtual BOOL Run(/* BitmapEffectStatusMonitor * theMonitor */);

	virtual KernelBitmap * GetDestination();
	virtual BOOL IsSourceSpecified();
	virtual BOOL IsAbleToRun();

	static BOOL Init();
	static BOOL DeInit();

	static void TestGD();

	protected:

	KernelBitmap * Source;
	KernelBitmap * Destination;
	
	static BfxALU * ALU;

//	BitmapEffectStatusMonitor * Monitor;
	
};

#endif  // INC_BFXBASE


