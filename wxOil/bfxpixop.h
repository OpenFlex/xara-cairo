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

// This is the header file for the bitmap effect pixop class

/*
*/

#ifndef INC_BFXPIXOP
#define INC_BFXPIXOP

//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class KernelBitmap;

typedef struct
{
	INT32 rsum;
	INT32 gsum;
	INT32 bsum;
	INT32 pixels;
	INT32 index;
} QuantisationCell;


/********************************************************************************************

>	class BfxPixelOp : public CCObject

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Pixel operator

The tracing stuff uses this class to determine whether or not a pixel should be traced or
not.

********************************************************************************************/

#define __bfxpixop_xy(x,y) Base[(x)+(y)*Width]

class BfxPixelOp : public CCObject
{
	CC_DECLARE_DYNCREATE(BfxPixelOp);

	public:

	BfxPixelOp();			 /* Constructor */
	virtual ~BfxPixelOp();	     /* Destructor */

	virtual BOOL Reset();

	virtual BOOL SetBitmap(KernelBitmap * pKB, DWORD theCacheStateMask, DWORD theCacheValueMask, BOOL theDefaultValue);
	
	virtual inline BOOL IsInRegion(INT32 x, INT32 y) {return DefaultValue;}

	virtual inline BOOL ClearCachedArea() {return TRUE;};
	virtual inline BOOL ClearEntireCache() {return TRUE;};
	virtual BOOL SetAuxilliaryBitmaps(KernelBitmap * pProposed /*A*/, KernelBitmap * pCurrent /*B*/,
							  KernelBitmap * pOriginal /*T*/, INT32 Threshold, DWORD theColour);

	virtual inline BOOL CheckMinimumArea(INT32 MinimumArea, INT32 InitialX, INT32 InitialY, BOOL * FoundRegion)
							{*FoundRegion = FALSE; return TRUE;};

	virtual inline DWORD ReadPixel(void * Image, INT32 p) { return 0; }
	virtual inline void TranslateToRGB(DWORD Colour, KernelBitmap * pKB, INT32 * R, INT32 * G, INT32 * B)
		{ *R = (INT32)(Colour >>16) & 0x0FF; *G = (INT32)(Colour>>8) & 0x0FF; *B = (INT32)(Colour/*>>0*/) & 0x0FF;return;};

	inline DWORD ReadOriginalPixel(INT32 x, INT32 y)
		{ return ReadPixel((void *)pT, x+y*WidthRounded); };

	virtual inline DWORD ReadBPixel(INT32 x, INT32 y)
		{ return ReadPixel((void *)pB, x+y*WidthRounded); };

	inline DWORD ReadPixel(void * Image, INT32 x, INT32 y) { return ReadPixel(Image, x+y*WidthRounded); };

	virtual inline void WritePixel(void * Image, INT32 p, DWORD Value) { return; }
	virtual inline DWORD TranslateToDWORD(KernelBitmap * pKB, INT32 R, INT32 G, INT32 B)
		{ return ((R & 0xFF)<<16) | ((G & 0xFF)<<8) | (B & 0xFF); };

	inline void WriteOriginalPixel(INT32 x, INT32 y, DWORD Value)
		{ WritePixel((void *)pT, x+y*WidthRounded, Value); return; };

	inline void WritePixel(void * Image, INT32 x, INT32 y, DWORD Value) { WritePixel(Image, x+y*WidthRounded, Value); return;};

	protected:

	virtual BOOL IsPixelReallyInRegion(INT32 x, INT32 y);

	DWORD * Base;
	INT32 Height;
	INT32 Width;
	INT32 WidthRounded;
	DWORD Size;
	BOOL DefaultValue;

	INT32 BPP;

	DWORD * pA;
	DWORD * pB;
	DWORD * pT;
	DWORD Colour;
	INT32 Value;

};

/********************************************************************************************

>	class BfxPixelOp32 : public BfxPixelOp

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	32 bit Pixel operator

This class caches the state of a pixel in 2 bits of an otherwised top byte of a 32 bit bitmap.

********************************************************************************************/

#define __bfxpixop_xy(x,y) Base[(x)+(y)*Width]

class BfxPixelOp32 : public BfxPixelOp
{
	CC_DECLARE_DYNCREATE(BfxPixelOp32);

	public:

	BfxPixelOp32();			 /* Constructor */
	virtual ~BfxPixelOp32();	     /* Destructor */

	virtual BOOL Reset();

	virtual BOOL SetBitmap(KernelBitmap * pKB, DWORD theCacheStateMask, DWORD theCacheValueMask, BOOL theDefaultValue);
	
	inline BOOL IsCached(INT32 x, INT32 y) { return (( (DWORD)x>=(DWORD)Width ) || ( (DWORD)y>=(DWORD)Height ) || (!Base))?
												DefaultValue:((__bfxpixop_xy(x,y) & CacheStateMask)!=0); };
	virtual inline BOOL IsInRegion(INT32 x, INT32 y) {
		if (( (DWORD)x>=(DWORD)Width ) || ( (DWORD)y>=(DWORD)Height ) || (!Base)) return DefaultValue;
		DWORD *pix = &__bfxpixop_xy(x,y);
		BOOL val;
		return (((*pix) & CacheStateMask)!=0)?(((*pix) & CacheValueMask)!=0):
		(val=GetValueAdjustCache(x,y),(*pix)=((*pix)&~CacheValueMask) | CacheStateMask | (val?CacheValueMask:0),val);
		};
	virtual BOOL ClearCachedArea();
	virtual BOOL ClearEntireCache();

	virtual inline DWORD ReadPixel(void * Image, INT32 p)
	{
		if ((((DWORD)p)>=Size)||!Image)
		{
			ERROR3("Out of range BfxPixOp::ReadPixel()");
			return 0;
		}
		return ((DWORD *) Image)[p];
	};

	virtual inline void WritePixel(void * Image, INT32 p, DWORD Value)
	{
		if ((((DWORD)p)>=Size)||!Image)
		{
			ERROR3("Out of range BfxPixOp::WritePixel()");
			return;
		}
		((DWORD *) Image)[p]=Value;
		return;
	};

	inline INT32 GetCacheMarks() { return CacheMarks; };

	virtual BOOL CheckMinimumArea(INT32 MinimumArea, INT32 InitialX, INT32 InitialY, BOOL * FoundRegion);

	protected:

	virtual BOOL GetValueAdjustCache(INT32 x, INT32 y);
	virtual BOOL FloodSearch(INT32 x, INT32 y, INT32 MinimumArea);

	DWORD CacheStateMask;
	DWORD CacheValueMask;
	INT32 CacheMarks;

	INT32 MinX;
	INT32 MinY;
	INT32 MaxX;
	INT32 MaxY;
};

/********************************************************************************************

>	class BfxPixelOpPseudo : public BfxPixelOp

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	32 bit Pixel operator

This pixcel op handles pseudocolour bitmaps on an equality basis

********************************************************************************************/

#define __bfxpixopl2_xy(x,y) (((Base[(x>>Log2BPP)+(y)*WidthRounded]) >> (x & XMask)) & BPPMask)

// this is the maximum minimum area that can be used
#define BFX_PSEUDOFLOODSIZE 256

class BfxPixelOpPseudo : public BfxPixelOp
{
	CC_DECLARE_DYNCREATE(BfxPixelOpPseudo);

	public:

	BfxPixelOpPseudo();			 /* Constructor */
	virtual ~BfxPixelOpPseudo();	     /* Destructor */

	virtual BOOL Reset();

	virtual BOOL SetBitmap(KernelBitmap * pKB, DWORD theCacheStateMask, DWORD theCacheValueMask, BOOL theDefaultValue);
	
	virtual inline BOOL IsInRegion(INT32 x, INT32 y) {
		if (( (DWORD)x>=(DWORD)Width ) || ( (DWORD)y>=(DWORD)Height ) ) return DefaultValue;
		else return IsPixelReallyInRegion(x, y);};

	virtual void TranslateToRGB(DWORD Colour, KernelBitmap * pKB, INT32 * R, INT32 * G, INT32 * B);

	virtual inline DWORD ReadPixel(void * Image, INT32 p)
	{
		if ( (((DWORD)p)>=Size)||!Image)
		{
			ERROR3("Out of range BfxPixOp::ReadPixel()");
			return 0;
		}
		return (DWORD)(((((BYTE *) Image)[p>>XShift])>>((XMask-(p & XMask))<<Log2BPP))&BPPMask);
	};

	virtual inline void WritePixel(void * Image, INT32 p, DWORD Value)
	{
		if ( (((DWORD)p)>=Size)||!Image)
		{
			ERROR3("Out of range BfxPixOp::ReadPixel()");
			return;
		}
		BYTE * thebyte = &(((BYTE *) Image)[p>>XShift]);
		INT32 shift = ((XMask-(p & XMask))<<Log2BPP);
		*thebyte = (BYTE)(((*thebyte) & ~(BPPMask<<shift)) | ((Value & BPPMask)<<shift));
		return;
	};

	virtual BOOL CheckMinimumArea(INT32 MinimumArea, INT32 InitialX, INT32 InitialY, BOOL * FoundRegion);

	protected:

	BOOL FloodSearch(INT32 x, INT32 y, INT32 MinimumArea,
				  INT32 FloodArray[BFX_PSEUDOFLOODSIZE][2], INT32 * FloodTop);


	INT32 Log2BPP;
	INT32 XShift;
	INT32 XMask;
	INT32 BPPMask;
};

/********************************************************************************************

>	class BfxPixelOp24 : public BfxPixelOp

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	32 bit Pixel operator

This pixcel op handles pseudocolour bitmaps on an equality basis

THIS PIXEL OP IS ONLY VERY PARTIALLY IMPLEMENTED - IT ONLY READS B PIXELS

********************************************************************************************/

#define __bfxpixopl2_xy(x,y) (((Base[(x>>Log2BPP)+(y)*WidthRounded]) >> (x & XMask)) & BPPMask)

class BfxPixelOp24 : public BfxPixelOp
{
	CC_DECLARE_DYNCREATE(BfxPixelOp24);

	BfxPixelOp24() : BfxPixelOp() { BPP=24; };

	public:

	virtual inline DWORD ReadBPixel(INT32 x, INT32 y)
		{ return *((DWORD *)&( ((BYTE *)(pB))[y*(((Width*3)+3)&~3)+(x*3)] ) ) &0x00FFFFFF; };
	
};

/********************************************************************************************

>	class BfxPositivePixelOp : public BfxPixelOp32

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Pixel operator

PixelOp that determines whether a pixel is better by more than a given amount in one bitmap
than in another

********************************************************************************************/

class BfxPositivePixelOp : public BfxPixelOp32
{
	CC_DECLARE_DYNCREATE(BfxPositivePixelOp);

	protected:
	
	virtual BOOL IsPixelReallyInRegion(INT32 x, INT32 y);
	
};

/********************************************************************************************

>	class BfxThresholdPixelOp : public BfxPixelOp32

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Pixel operator

PixelOp that determines whether a pixel is better by more than a given amount in one bitmap
than in another

********************************************************************************************/

class BfxThresholdPixelOp : public BfxPixelOp32
{
	CC_DECLARE_DYNCREATE(BfxThresholdPixelOp);

	protected:

	virtual BOOL IsPixelReallyInRegion(INT32 x, INT32 y);

};

/********************************************************************************************

>	class BfxColourThresholdPixelOp : public BfxPixelOp32

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Pixel operator

PixelOp that determines whether a pixel is better by more than a given amount in one bitmap
than in another

********************************************************************************************/

class BfxColourThresholdPixelOp : public BfxPixelOp32
{
	CC_DECLARE_DYNCREATE(BfxColourThresholdPixelOp);

	protected:

	virtual BOOL IsPixelReallyInRegion(INT32 x, INT32 y);

};

/********************************************************************************************

>	class BfxPositivePixelOpPseudo : public BfxPixelOpPseudo

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Pixel operator

PixelOp that determines whether a pixel is better by more than a given amount in one bitmap
than in another

********************************************************************************************/

class BfxPositivePixelOpPseudo : public BfxPixelOpPseudo
{
	CC_DECLARE_DYNCREATE(BfxPositivePixelOpPseudo);

	protected:
	
	virtual BOOL IsPixelReallyInRegion(INT32 x, INT32 y);
	
};

/********************************************************************************************

>	class BfxThresholdPixelOpPseudo : public BfxPixelOpPseudo

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Pixel operator

PixelOp that determines whether a pixel is better by more than a given amount in one bitmap
than in another

********************************************************************************************/

class BfxThresholdPixelOpPseudo : public BfxPixelOpPseudo
{
	CC_DECLARE_DYNCREATE(BfxThresholdPixelOpPseudo);

	protected:

	virtual BOOL IsPixelReallyInRegion(INT32 x, INT32 y);

};

/********************************************************************************************

>	class BfxColourThresholdPixelOpPseudo : public BfxPixelOpPseudo

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Pixel operator

PixelOp that determines whether a pixel is better by more than a given amount in one bitmap
than in another

********************************************************************************************/

class BfxColourThresholdPixelOpPseudo : public BfxPixelOpPseudo
{
	CC_DECLARE_DYNCREATE(BfxColourThresholdPixelOpPseudo);

	protected:

	virtual BOOL IsPixelReallyInRegion(INT32 x, INT32 y);

};

/********************************************************************************************

>	class Octree : public CCObject

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/1994
	Purpose:	Colour octree

********************************************************************************************/

class OctreeElement : public SimpleCCObject
{
	public:

	OctreeElement() { pParent=pListNext=pListPrev=NULL; for (INT32 c=0; c<8; c++) pChildren[c]=NULL;
					  Pixels=Depth=R=G=B=NumChildren=0;Index=-1;};
	~OctreeElement() {
			for (INT32 c=0; c<8; c++) if (pChildren[c])
			{
				delete (pChildren[c]);
				pChildren[c]=NULL;
			}
			pParent=pListNext=pListPrev=NULL;Pixels=Depth=R=G=B=NumChildren=0;Index=-1;
		};

	INT32 Depth;
	INT32 R;
	INT32 G;
	INT32 B;
	INT32 Index;
	INT32 Pixels;
	INT32 NumChildren;
	OctreeElement * pChildren[8];
	OctreeElement * pParent;
	OctreeElement * pListNext;
	OctreeElement * pListPrev;
};

class Octree : public CCObject
{
	CC_DECLARE_DYNCREATE(Octree);

	public:

	Octree();			 /* Constructor */
	~Octree();	     /* Destructor */

	BOOL Init(INT32 NumColours);
	BOOL Insert(INT32 r, INT32 g, INT32 b);
	BOOL Index(RGBQUAD * Palette, OctreeElement * pEl=NULL);
	INT32 GetIndex(INT32 r, INT32 g, INT32 b);

	private:

	OctreeElement * GetElement(INT32 r, INT32 g, INT32 b);
	void CheckIntegrity();
	void Unlink(OctreeElement * pEl);
	void Link(OctreeElement * pEl);

	INT32 MaxLeaves;
	INT32 CurrentLeaves;
	OctreeElement * pTopElement;
	INT32 CurrentIndex;

	OctreeElement * ListHead[9 /*depth 0-8*/ ][9 /*children 0-8*/ ];

};




#endif

