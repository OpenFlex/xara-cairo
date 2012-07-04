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

// This is the header file for the bitmap effect ALU class

/*
*/

#ifndef INC_BFXALU
#define INC_BFXALU

//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]
class KernelBitmap;
class OILBitmap;

#ifndef EXCLUDE_FROM_RALPH

//#include "gconsts.h" // For GMATRIX - in camtypes.h [AUTOMATICALLY REMOVED]
#include "tracectl.h" // for enum TraceMethod - annoying...

class GDrawContext;
class BfxALULUT;
class Path;
class String_256;


typedef struct
{
	BYTE	R;
	BYTE	G;
	BYTE	B;
	BYTE	T;
} AluPix32;

enum BfxSpecialEffect { BFX_SFX_USER, BFX_SFX_ISOLATEPOINTS, BFX_SFX_EDGE, BFX_SFX_HEDGE,
						BFX_SFX_VEDGE, BFX_SFX_P45EDGE, BFX_SFX_N45EDGE, BFX_SFX_LAPLACIAN,
						BFX_SFX_DIALATION, BFX_SFX_ROBERTS };

class KernelStatistics /* should be a struct but the C compiler is crap*/
{
	public:

	 INT32  N  ;
	double R  ;
	double R2 ;
	double RX ;
	double RY ;
	double G  ;
	double G2 ;
	double GX ;
	double GY ;
	double B  ;
	double B2 ;
	double BX ;
	double BY ;
	double X  ;
	double Y  ;
	double X2 ;
	double Y2 ;
	double XY ;
	DWORD  Pixel;
	INT32  LowX;
	INT32  LowY;
};
		  
inline INT32 IntegerSquare(INT32 i) { return i*i; }
inline double DoubleSquare(double d) { return d*d; }

/********************************************************************************************

>	class BfxErrorRegionList : public CCObject

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/01/1995
	Purpose:	Stores error region list for tracing

********************************************************************************************/

typedef struct
{
	INT32 X;
	INT32 Y;
	INT32 Area;
} BfxErrorRegionListItem;

class BfxErrorRegionList : public CCObject
{
	CC_DECLARE_DYNCREATE(BfxErrorRegionList);

	public:

	BfxErrorRegionList();			 /* Constructor */
	~BfxErrorRegionList();	     /* Destructor */

	protected:
	
	BfxErrorRegionListItem * pList;
	INT32 ListLength;
	INT32 Used;
	
	INT32 CurrentRead;
	INT32 CurrentWrite;
	BOOL Sorted;

	void Swap( BfxErrorRegionListItem * A, BfxErrorRegionListItem * B) { BfxErrorRegionListItem T;
		T.X=A->X;T.Y=A->Y;T.Area=A->Area;A->X=B->X;A->Y=B->Y;A->Area=B->Area;B->X=T.X;B->Y=T.Y;B->Area=T.Area;};


	public:

	BOOL Next() {if (pList && pList[CurrentRead].Area) CurrentRead++;return TRUE;};
	BOOL Init(UINT32 Length);
	BOOL ResetRead();
	BOOL Empty();
	BOOL Insert(INT32 XCoord, INT32 YCoord, INT32 Area);
	BOOL Sort();
	BOOL IsSpace() { return (CurrentWrite<ListLength); };
	BOOL GetCurrent(INT32 * XCoord, INT32 * YCoord, INT32 * Area)
		{return ((pList) && (*XCoord=pList[CurrentRead].X,*YCoord=pList[CurrentRead].Y,*Area = pList[CurrentRead].Area));};
	BOOL MarkUsed() { return (pList && ((!pList[CurrentRead].Area) || (pList[CurrentRead].Area=/*assign*/1))); };
	INT32 GetSize() { return ListLength; };

};
#endif

/********************************************************************************************

>	class BfxALU : public CCObject

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Arithmetic and logic unit for bitmap effects

This class implements the Bitmap Effect ALU (Arithmetic and logic unit). You can think of
this as the Kernel i/f for GDraw when using bitmap effects, but that would be a bit of a
narrow view. The class is there to perform fast arithmetic and logical operations on bitmaps,
and at the moment, we reckon the fastest way to do that is to use GDraw.

The ALU works very like a processor ALU, except each register holds a bitmap (actually a
pointer to a bitmap which can cause some complications), and each operand (like Add) adds
two bitmaps, rather than two integers. In fact, some registers may be set to 'pseudo bitmaps'
like solid colour and linear fills, which are usefully expanded by the ALU at plot time without
occupying memory.

The ALU has the following registers:
	Name			Purpose
	====			=======
	A (Accumulator)	The accumulator is the destination register for all operands, and is the
					source register for many. The accumulator can be 32 bit or 8 bpp grey
					but at the moment only 32 bpp is supported. The T channel of the
					accumulator is always zero (well, that's how the plot operations leave
					it anyway).
	B (Bitmap)		A general purpose bitmap, normally used as a secondary source operand.
	T (Bitmap)		And 8 bit bitmap used for weigthing values on some calls.

Here are some example arithmetic operands:

AddpAqB	A <- pA+qB
AddApB	A <- A+pB
SubApB	A <- A-pB
InvA	A <- 255-A

Here are some example load & store operations

SetA(bitmap)
SetB(bitmap)
SetB(linear fill parameters)

********************************************************************************************/

class BfxALU : public CCObject
{
	CC_DECLARE_DYNCREATE(BfxALU);

	public:

	BfxALU();			 /* Constructor */
	virtual ~BfxALU();	     /* Destructor */

#ifndef EXCLUDE_FROM_RALPH
	virtual BOOL Init();
	virtual BOOL DeInit();

	virtual KernelBitmap * NewBitmap(KernelBitmap *pBitmap,INT32 XAdjust=0,INT32 YAdjust=0,
									 INT32 NewDepth=0, String_256 * pName =NULL, UINT32 ResID =0);

	virtual	BOOL SetA(KernelBitmap * pBitmap=NULL);
	virtual BOOL SetB(KernelBitmap *pBitmap=NULL,INT32 XOffset=0,INT32 YOffset=0,
					  const BYTE * pTable=NULL,DWORD Style=0);
	virtual BOOL SetB(DWORD Colour);
	virtual BOOL SetT(KernelBitmap *pBitmap=NULL,INT32 XOffset=0,INT32 YOffset=0,
					  const BYTE * pTable=NULL,DWORD Style=0);
	virtual BOOL SetT(DWORD Value);

	virtual BOOL PlotB();
	virtual BOOL PlotBLUT(BfxALULUT * LUT);
	
	virtual	BOOL PartTAB();
	virtual	BOOL PartMulTAB();
	virtual	BOOL PartRevMulTAB();
	virtual BOOL AddTAB();
	virtual BOOL SubTAB();

	virtual	BOOL PartKAB(DWORD Value);
	virtual	BOOL PartMulKAB(DWORD Value);
	virtual	BOOL PartRevMulKAB(DWORD Value);
	virtual BOOL AddKAB(DWORD Value);
	virtual BOOL SubKAB(DWORD Value);

	virtual BOOL MarkThresholdError(INT32 Value, DWORD MarkValue, DWORD ClearValue);
	virtual BOOL MarkColourThresholdError(INT32 Value, DWORD Colour, DWORD MarkValue, DWORD ClearValue,
							  double * pAError, double * pBError, INT32 * pTotalPixels, INT32 * pMarkedPixels);

	virtual BOOL MarkPositive(INT32 Value, DWORD MarkValue, DWORD ClearValue,
							  double * pAError = NULL, double * pBError = NULL,
							  INT32 * pTotalPixels = NULL, INT32 * pMarkedPixels = NULL);
	virtual BOOL MarkLargestArea(DWORD MarkValue, DWORD ClearValue, DWORD RegionValue,
								 BOOL * FoundRegion, INT32 * InitialX, INT32 * InitialY, INT32 * Area);
	virtual	BOOL MarkGivenArea(DWORD MarkValue, DWORD ClearValue, DWORD RegionValue,
						     BOOL * FoundRegion, INT32 * InitialX, INT32 * InitialY, INT32 * Area);
	virtual BOOL GradFillPath(Path * ThePath, DWORD StartColour, DWORD EndColour,
							  INT32 StartX, INT32 StartY, INT32 EndX, INT32 EndY,
							  BOOL AntiAlias = FALSE, BOOL ColoursAreDWORDs = FALSE);
	virtual BOOL GetStatistics(Path * ThePath, KernelStatistics * pStats);
	virtual BOOL MarkBitByWord(DWORD BitMask, DWORD TheWord);
	virtual BOOL ClearBitByWord(DWORD BitMask, DWORD TheWord);
	virtual BOOL MarkWordByBit(DWORD BitMask, DWORD MarkValue, DWORD ClearValue);
	virtual BOOL BuildErrorRegionList(DWORD MarkValue, DWORD ClearValue, DWORD RegionValue,
									  BfxErrorRegionList * pERL, INT32 MinimumArea);
	virtual BOOL ScanBit(DWORD BitMask, INT32 * X, INT32 * Y, INT32 *pPixel, BOOL * Found, BOOL CheckConnected=FALSE);
	virtual BOOL ScanThreshold(INT32 Value, INT32 * X, INT32 * Y, INT32 *pPixel, BOOL * Found, BOOL CheckConnected=FALSE);
			
	virtual BOOL GetSize(KernelBitmap * pBitmap, INT32 * pXSize=NULL, INT32 * pYSize=NULL, INT32 * pDepth=NULL);

	virtual BOOL ZeroA(DWORD FillValue = 0);
	virtual BOOL ByteCopyBA();

	virtual void TestGD();

#ifndef WEBSTER
PORTNOTE("other", "Remove accusoft effects")
#ifndef EXCLUDE_FROM_XARALX
	// Accusoft effects
	virtual BOOL FlipX(KernelBitmap * * ppOutput);
	virtual BOOL FlipY(KernelBitmap * * ppOutput);
	virtual BOOL Rotate90(KernelBitmap * * ppOutput);
	virtual BOOL Rotate180(KernelBitmap * * ppOutput);
	virtual BOOL Rotate270(KernelBitmap * * ppOutput);

	virtual BOOL Resize(KernelBitmap * * ppOutput, INT32 Width, INT32 Height, BOOL LinearInterpolation);

	virtual BOOL BrightnessContrast(KernelBitmap * * ppOutput, INT32 Brightness=0, INT32 Contrast=0, INT32 Colour=0);

	virtual BOOL BayerMono(KernelBitmap * * ppOutput);
	virtual BOOL HalftoneMono(KernelBitmap * * ppOutput);
	virtual BOOL DiffusionMono(KernelBitmap * * ppOutput);
	virtual BOOL BayerColour(KernelBitmap * * ppOutput);
	virtual BOOL DiffusionColour(KernelBitmap * * ppOutput);
	virtual BOOL PopularityColour(KernelBitmap * * ppOutput);
	virtual BOOL MakeGreyscale(KernelBitmap * * ppOutput);
#endif //XARALX
#endif //WEBSTER
	virtual BOOL MakeGreyscale32to8(KernelBitmap * * ppOutput);

#endif	
	static  BOOL IsGreyscaleBitmap(KernelBitmap * pKB);
	static  BOOL IsGreyscaleBitmap(OILBitmap * pOilBmp);
#ifndef EXCLUDE_FROM_RALPH
#ifndef WEBSTER
PORTNOTE("other", "Remove accusoft effects")
#ifndef EXCLUDE_FROM_XARALX
	virtual BOOL Octree (KernelBitmap * * ppOutput);

	virtual BOOL SharpenBlur(KernelBitmap * * ppOutput, INT32 Degree, INT32 Times);
#endif
	virtual BOOL RemoveDither(KernelBitmap * * ppOutput, INT32 Thresh, INT32 QuantCols, TraceMethod Method);
#ifndef EXCLUDE_FROM_XARALX
	virtual BOOL SpecialEffect(KernelBitmap * * ppOutput, double * Matrix, BfxSpecialEffect Type);
#endif
#endif //WEBSTER

	protected:

	virtual	BOOL DoRect();
	virtual BOOL UseBT(DWORD TransparencyStyle=0);
	virtual BOOL UseBK(DWORD TransparencyStyle,DWORD Value);

	virtual BOOL MarkRegions(DWORD MarkValue, DWORD ClearValue,
						     BOOL * FoundRegion, INT32 * InitialX, INT32 * InitialY, INT32 * Area,
							 INT32 * pSize, INT32 * pHighestChain, INT32 * pWidth, DWORD * * ppA);	

#ifndef WEBSTER
PORTNOTE("other", "Remove accusoft effects")
#ifndef EXCLUDE_FROM_XARALX
	virtual BOOL MakeAccusoftHandle(INT32 * pHandle, BOOL DoBodge = FALSE);
	virtual BOOL MakeKernelBitmap(INT32 Handle, KernelBitmap * * ppOutput, BOOL Make32Bits = FALSE,
								  String_256 * pName = NULL, UINT32 ResID = 0, BOOL DoBodge = FALSE);
#endif
	virtual BOOL AdjustBrightnessContrastColour(LPBYTE Source, LPBYTE Dest, INT32 Size, INT32 Width, INT32 Height,
							INT32 Brightness, INT32 Contrast, INT32 Colour, BOOL SingleChannel);
#ifndef EXCLUDE_FROM_XARALX
	BOOL MAH_BodgeCopyBitmap(INT32 Width, INT32 Height, INT32 Depth, LPBYTE pSourceBits, LPBYTE pDestBits);
	BOOL MKB_BodgeCopyBitmap(INT32 Width, INT32 Height, INT32 Depth, LPBYTE pSourceBits, LPBYTE pDestBits);
#endif
#endif //WEBSTER

	void ConvertScanLineToDWORD(KernelBitmap * pBitmap, INT32 Line, DWORD * pBuffer);
	void ConvertScanLineFromDWORD(KernelBitmap * pBitmap, INT32 Line, DWORD * pBuffer);

	void SlowRemoveDither(BYTE * ByteLine[5], INT32 NoiseMatrix[5][5],
						  BYTE * OutputLine, INT32 Width, INT32 Thresh, BOOL Mono);

	KernelBitmap * A;
	KernelBitmap * B;
	KernelBitmap * T;
	
	POINT BPoints[3];
	POINT TPoints[3];
	
	COLORREF BColour;
	DWORD TValue;

	const BYTE * BpTable;
	const BYTE * TpTable;

	DWORD BStyle;
	DWORD TStyle;

	GDrawContext * GC;	
	
	GMATRIX identity;

	BOOL ResetAccusoftDibsToRuns;
#endif
};

#ifndef EXCLUDE_FROM_RALPH
/********************************************************************************************

>	class BfxALULUT : public CCObject

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Lookup table

This class implements the Bitmap Effect ALU (Arithmetic and logic unit) LUT (look up table).
This isolates the kernel classes from th storage format of the LUT

********************************************************************************************/

class BfxALU;

class BfxALULUT : public CCObject
{
	CC_DECLARE_DYNCREATE(BfxALULUT);

	friend class BfxALU;

	//BfxALULUT(); constructors and destructors are simple
	//~BFXALULUT();

	public:
	
	BOOL LinearABK(double PropA, double PropB, double Offset);
	BYTE GetLUT(UINT32 A, UINT32 B);

	protected:

	BYTE Data[256*256];
};

#endif	// EXCLUDE_FROM_RALPH
#endif  // INC_BFXALU

