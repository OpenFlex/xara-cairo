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

#ifndef _BITMAPSHADOW_H_
#define _BITMAPSHADOW_H_

#include "bshadow2.h"

#ifdef BUILDSHADOWS

//const UINT32 MAX_SHADOW_BLUR	= 100 ;		// Maximum amount of blur
//const UINT32 MAX_CONTOUR		= 100 ;		// Maximum contour pixel size.
//const double MIN_BLUR_DIAMETER = 0.71;	// Minimum blur diameter is sqrt(0.5), rounded up
										// a little to safely avoid boundary conditions.

class ShadowBitmap : public CCObject
{
// CC_DECLARE_DYNCREATE(ShadowBitmap);
public:
	ShadowBitmap();
	~ShadowBitmap();

	BOOL CreateFilled(INT32 Width, INT32 Height, BYTE value, UINT32 Depth = 32);
	
	BOOL Create8BitBitmap(UINT32 * pBits, UINT32 Width, UINT32 Height);

	HRESULT Create(INT32 Width, INT32 Height, UINT32 Depth = 32);
	LPBYTE GetBytes() { return (LPBYTE)m_Bytes; }

	INT32 GetWidth() { return m_Width; }
	INT32 GetHeight() { return m_Height; }
	UINT32 GetDepth() { return m_Depth; }

private:
	INT32 m_Width;
	INT32 m_Height;
	BYTE * m_Bytes;
	UINT32 m_Depth;
} ;

class CBitmapShadow : public ShadowBitmap
{
	friend class NodeFeatherEffect;

// CC_DECLARE_DYNCREATE(CBitmapShadow);
public:
	enum {
//		MAX_ROW_OFFSETS = MAX_SHADOW_BLUR*2+1,	// Maximum size of shadow mask.
//		TABLE_SIZE = 0x800						// Maximum lookup table size for shadow generation.
	} ;

	CBitmapShadow();
		
	BOOL CreateShadow(const BOOL bIsWallShadow,
											const double dProjection,
											const double dTiltAngle,
											const double dBlurriness,
											const double dDarknessCoeff,
											const double dPositionX,
											const double dPositionY,
											UINT32* pForegroundBits,
											const CNativeSize ForegroundSize
											);

	void GetShadowOffset(INT32* pOffsetX, INT32* pOffsetY)
	{
		*pOffsetX = m_OffsetX;
		*pOffsetY = m_OffsetY;		
	}

	BOOL IsWallShadow(void) const
	{
		return m_bIsWallShadow;
	}

	double GetBlurriness(void) const
	{
		return m_dBlurriness;
	}

	double GetDarknessCoeff(void) const
	{
		return m_dDarknessCoeff;
	}

private:
	BOOL MakeWallShadow (const UINT32* pForegroundBits,
									const CNativeSize ForegroundSize,
									const INT32 nXPosition,
									const INT32 nYPosition,
									const double fBlur,
									INT32 *pOffsetX,
									INT32 *pOffsetY,
									const double dDarknessCoeff = 1.0);

	BOOL MakeCastShadow (UINT32* pForegroundBits,
								const CNativeSize ForegroundSize,
								const double fBlur,									 
								const double dTiltAngle, 
								const double dProjection,
								const double dDarknessCoeff = 1.0 );

	BOOL m_bIsWallShadow;
	double m_dProjection;
	double m_dTiltAngle;
	double m_dBlurriness;
	double m_dDarknessCoeff;
	double m_dPositionX;
	double m_dPositionY;
	INT32 m_OffsetX;
	INT32 m_OffsetY;

protected:
	ShadowBitmap* Tilt(BYTE* pSourceBits, const INT32 nSourceWidth, const INT32 nSourceHeight, const double dTiltDegrees);
	static bool ProjectShadow(BYTE* pSBitmap, BYTE* pDBitmap, UINT32 nWidth, UINT32 nSHeight, UINT32 nDHeight);


// Karim 02/08/2000
// made this static so it can be accessed by the public static feathering
// function.

public:
	// Karim 08/08/2000
	// Blur the source bitmap, storing the result in the destination bitmap.

	static void Blur8BppBitmap(	LPBITMAPINFOHEADER pSrcBMIHeader,	LPBYTE pSrcBits,
								LPBITMAPINFOHEADER pDestBMIHeader,	LPBYTE pDestBits,
								const UINT32 DWordBitmapWidth, const double fBlur );

	// Karim 17/08/2000
	// Determine whether the resultant bitmap for this blur setting
	// will be offset up and right by half a pixel.
	static BOOL BlurringWillOffsetBitmap(double fBlurDiameter)
	{
		// bitmap will be offset if the blur diameter is even,
		// and is not smaller than the minimum blur diameter.
		return (	((UINT32)(fBlurDiameter + 0.5) % 2 == 0) &&
					!(fBlurDiameter < MIN_BLUR_DIAMETER)	);
	}

	static UINT32 GetWholePixelBlurDiameter(double fBlurDiameter)
	{
		double fNewBlur = fBlurDiameter / 2.0;
		if (fNewBlur > MAX_SHADOW_BLUR)
			fNewBlur = MAX_SHADOW_BLUR;

		return (UINT32)(2 * fNewBlur + 0.5);
	}

	static LPBITMAPINFO Feather8BppBitmap(
		const double fBlur,
		LPBITMAPINFO pSrcInfo,
		LPBYTE pSrcBits32,
		LPBYTE* pDestBits
	) ;

	//
	// Gavin 24/11/2004
	//
	// Contour the 32bpp source bitmap, putting the result into the 32bpp destination bitmap.
	//
	static bool ContourBitmap(
						const LPBITMAPINFO	pSrcInfo32,
						const LPBYTE		pSrcBits32,
						const double		fContour,
						const BYTE			uThreshold,
						LPBITMAPINFO*		ppDestInfo32,
						LPBYTE*				ppDestBits32,
						double*				pfOffsetX,
						double*				pfOffsetY
					) ;
	//
	// Gavin 20/04/2005
	//
	// Contour the 8bpp source bitmap, putting the result into the 8bpp destination bitmap.
	//
	static bool ContourBitmap(
						const LPBITMAPINFO	pSrcInfo8,
						const LPBYTE		pSrcBits8,
						const double		fContour,
						const bool			bInside,
						const BYTE			uThreshold,
						LPBITMAPINFO*		ppDestInfo8,
						LPBYTE*				ppDestBits8,
						double*				pfOffsetX,
						double*				pfOffsetY
					) ;

protected:
} ;

#endif

#endif //_BITMAPSHADOW_H_




