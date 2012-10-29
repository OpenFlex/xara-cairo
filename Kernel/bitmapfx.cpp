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

// This file implents the BitmapEffect class

/*
*/

#include "camtypes.h"
#include "bitmapfx.h"
#include "bfxalu.h"

// This is not compulsory, but you may as well put it in so that the correct version
// of your file can be registered in the .exe

// An implement to match the Declare in the .h file.
// If you have many classes, it is recommended to place them all together, here at the start of the file
CC_IMPLEMENT_DYNCREATE(BitmapEffect, BitmapEffectBase)
CC_IMPLEMENT_DYNCREATE(AccusoftBitmapEffect, BitmapEffect)

CC_IMPLEMENT_DYNCREATE(ABFXFlipX, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXFlipY, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXRotate90, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXRotate180, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXRotate270, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXBayerMono, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXHalftoneMono, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXDiffusionMono, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXBayerColour, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXDiffusionColour, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXPopularityColour, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXMakeGreyscale, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXOctree, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXResize, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXBrightnessContrast, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXSharpenBlur, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXSpecialEffect, AccusoftBitmapEffect)
CC_IMPLEMENT_DYNCREATE(ABFXRemoveDither, AccusoftBitmapEffect)

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	KernelBitmap * AccusoftBitmapEffect::DoALUWork()
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/01/95
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if succeeded, FALSE & error set if not
	Purpose:	Overridden by derived classes
	Errors:		None
	Scope:		Public
	SeeAlso:	-

********************************************************************************************/

KernelBitmap *  AccusoftBitmapEffect::DoALUWork()
{
	ERROR2(FALSE, "Base class AccusoftBitmapEffect::DoALUWork() called");
}

/********************************************************************************************

>	BOOL AccusoftBitmapEffect::SetParameters(INT32 p1=0, INT32 p2=0, INT32 p3=0, double * pD=NULL)
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/01/95
	Inputs:		The generic parameters to set
	Outputs:	None
	Returns:	TRUE if succeeded, FALSE & error set if not
	Purpose:	Overridden by derived classes
	Errors:		None
	Scope:		Public
	SeeAlso:	-

********************************************************************************************/

/* inline */

/********************************************************************************************

>	KernelBitmap * AccusoftBitmapEffect::GetProcessedBitmap(KernelBitmap * pOriginal)
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/01/95
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if succeeded, FALSE & error set if not
	Purpose:	Overridden by derived classes
	Errors:		None
	Scope:		Public
	SeeAlso:	-

********************************************************************************************/

KernelBitmap * AccusoftBitmapEffect::GetProcessedBitmap(KernelBitmap * pOriginal)
{
	KernelBitmap * pDest;
	if (!ALU->SetB(pOriginal)) return FALSE;
	pDest=DoALUWork();
	if (!pDest) return FALSE;
	return pDest;
}

// Now the DoALUWork functions. These are so obvious and repetitive I'm not going to doc them all

#define MakeDoALUWork(ALUFunction) \
KernelBitmap * ABFX##ALUFunction::DoALUWork() { KernelBitmap * Result = NULL; \
if (!ALU->ALUFunction(&Result)) return NULL; return Result; }

#define MakeDoALUWorkL2(ALUFunction) \
KernelBitmap * ABFX##ALUFunction::DoALUWork() { KernelBitmap * Result = NULL; \
if (!ALU->ALUFunction(&Result, Param1, Param2)) return NULL; return Result; }

#define MakeDoALUWorkL3(ALUFunction) \
KernelBitmap * ABFX##ALUFunction::DoALUWork() { KernelBitmap * Result = NULL; \
if (!ALU->ALUFunction(&Result, Param1, Param2, Param3)) return NULL; return Result; }

#define MakeDoALUWorkL1(ALUFunction) \
KernelBitmap * ABFX##ALUFunction::DoALUWork() { KernelBitmap * Result = NULL; \
if (!ALU->ALUFunction(&Result, Param1)) return NULL; return Result; }

#define MakeDoALUWorkLP(ALUFunction) \
KernelBitmap * ABFX##ALUFunction::DoALUWork() { KernelBitmap * Result = NULL; \
if (!ALU->ALUFunction(&Result, pDouble, (enum BfxSpecialEffect) (INT32) Param1)) return NULL; return Result; }

#define MakeDoALUWorkL2B(ALUFunction) \
KernelBitmap * ABFX##ALUFunction::DoALUWork() { KernelBitmap * Result = NULL; \
if (!ALU->ALUFunction(&Result, Param1, Param2, (BOOL)Param3)) return NULL; return Result; }

#define MakeDoALUWorkL2T(ALUFunction) \
KernelBitmap * ABFX##ALUFunction::DoALUWork() { KernelBitmap * Result = NULL; \
if (!ALU->ALUFunction(&Result, Param1, Param2, (enum TraceMethod)(INT32)Param3)) return NULL; return Result; }

MakeDoALUWork(FlipX)
MakeDoALUWork(FlipY)
MakeDoALUWork(Rotate90)
MakeDoALUWork(Rotate180)
MakeDoALUWork(Rotate270)
MakeDoALUWork(BayerMono);
MakeDoALUWork(HalftoneMono);
MakeDoALUWork(DiffusionMono);
MakeDoALUWork(BayerColour);
MakeDoALUWork(DiffusionColour);
MakeDoALUWork(PopularityColour);
MakeDoALUWork(MakeGreyscale);
MakeDoALUWork(Octree);
MakeDoALUWorkL2B(Resize);
MakeDoALUWorkL3(BrightnessContrast);
MakeDoALUWorkL2(SharpenBlur);
MakeDoALUWorkLP(SpecialEffect);
MakeDoALUWorkL2T(RemoveDither);
