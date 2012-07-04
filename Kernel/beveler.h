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


#ifndef _BEVELER_H
#define _BEVELER_H

#include "pathtrap.h"
//#include "bevtrap.h"
//#include "wincoord.h"
//#include "doccoord.h"
//#include "bitmap.h"

#define BEVEL_FLATNESS  200

// macro to turn the system time into an INT32 value which can be used for timings
#define LONGSYSTEMTIME(X) { SYSTEMTIME s; \
						    GetSystemTime(&s); \
							X = s.wMilliseconds + s.wSecond * 1000 + \
								s.wMinute * 60000 + \
								s.wHour   * 60000 * 60 ; }

#define WRITETIME(X, Y) { FILE * kxp = fopen("timings.txt", "a"); \
					   fprintf(kxp, X); fprintf(kxp, " %d\n", Y); \
						  fclose(kxp); }

class NodeBevel;
struct BEVEL_FACE ;

#define BEVELBITMAPSCALE 4
#define BEVELBITMAPSHIFT 2

/******************************************************************************************

>	class CBeveler : public SimpleCCObject

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/10/98

	Purpose:	Does the bevelling

******************************************************************************************/

class CBeveler : public CCObject
{
	// Give my name out in memory dumps
	CC_DECLARE_DYNAMIC(CBeveler);

public:
	CBeveler();
	CBeveler(Path * pPath);

	~CBeveler();

	void SetBevelType(INT32 t) { m_BevelType = t; }

	BOOL SetUpBeveler(MILLIPOINT Indent, JointType jtype, NormCoord * lightVec, BOOL bOuter,
					  INT32 Contrast, RenderRegion * pRegion, MILLIPOINT Flatness);
/*
	BOOL SetUpBeveler(MILLIPOINT Indent, JointType jtype, NormCoord * lightVec, BOOL bOuter,
					INT32 width, INT32 height, INT32 Contrast, RenderRegion * pRegion,
					MILLIPOINT Flatness, double dpi, BOOL bFlat = TRUE);
*/
	BOOL SetBevelerSize(INT32 Width, INT32 Height);

	DocRect GetSelectionRect() { return m_SelectionBounds; }
	void SetBevelAngle(double LightAngle) { m_LightAngle = LightAngle; }
	void SetBevelTilt(double Tilt)	{	 m_Tilt = Tilt; }

	// gets the flatness to use depending on the document
	static INT32 GetBevelFlatness();

	// render the bevel to a given bitmap
	BOOL RenderToBitmap(KernelBitmap * pBitmap, BOOL bResample = FALSE, DocCoord* pSubPixOffSet = NULL);

private:
	MILLIPOINT m_Indent;
	INT32 m_Contrast;
	INT32 m_BevelType;
	double m_LightAngle;
	double m_Tilt;

	// pointer to the path to be used in bevelling
	Path * m_pBevelPath;
	POINT* m_pBevelPoints ;
	BYTE * m_pBevelTypes ;
	UINT32  m_nBevelLength ;
	BYTE m_Transparency;

	// the selection's bounding rect in document coordinates
	DocRect m_SelectionBounds;
	DocRect m_BevelBounds;

	// sets up the above two scale factors
	void CalcSelectionBounds() ;
	void CalcInnerPath() ;
	void SetUpMapping();

	// transforms a win coord to a doc coord based on currently active spread and view
	void ToWinCoord(const DocCoord * dc, WinCoord * wc);

	// the width and height of the bitmap that we are to return
	INT32 m_Width;
	INT32 m_Height;

	KernelBitmap* m_pStrip32;
	KernelBitmap* m_pMaskBitmap;
	KernelBitmap* m_pNewMask;

	JointType   m_JointType;
	BOOL m_bOuter;

	INT32 SetDIBitmap( BITMAPINFOHEADER* pHeader, BYTE* pBits ) ;

	BEVEL_FACE* m_pFaceList;
	UINT32 m_NumFaces;

	// resamples the bitmap given into destination
	void ResampleBitmap(BYTE * p32BitDIB, UINT32 Width, UINT32 Height, BYTE * pDestBits,
								BYTE * pMaskBitmap);

	BOOL EmboldenBitmap(KernelBitmap* pImgBitmap, KernelBitmap* pMaskBitmap, KernelBitmap* pNewMaskBitmap);

	double m_dBmpToWinX;
	double m_dBmpToWinY;

	// renders the points list, resampling
	BOOL RenderWithResampling(KernelBitmap * pBitmap, INT32 OffsetX, INT32 OffsetY, DocCoord* pSubPixOffSet = NULL);
	
	// copy bitmap fn
	void CopyBitmapIntoBitmap(const KernelBitmap * pSrcBitmap, KernelBitmap * pDestBitmap,
						INT32 DestX, INT32 DestY);

	BOOL RenderInStripsToBitmap(KernelBitmap * pBitmap, DocCoord* pSubPixOffSet = NULL);
} ;


#endif
