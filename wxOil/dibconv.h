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


// class used to convert DIBs from one depth to another

#ifndef INC_DIBCONV
#define	INC_DIBCONV

class GDrawContext;

// Some enums for the different dithering types
enum DITHER
{
	XARADITHER_SIMPLE,
	XARADITHER_ORDERED,
	XARADITHER_ORDERED_GREY,
	XARADITHER_ERROR_DIFFUSION,
	XARADITHER_NONE
};

#define XARADITHER_MAX XARADITHER_NONE

class DIBConvert : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(DIBConvert)

public:
	DIBConvert();
	virtual ~DIBConvert();

	virtual BOOL Convert( LPBYTE Input, LPBYTE Output, UINT32 Height, BOOL FirstStrip = TRUE ) = 0;

	static BOOL Init();
	static void DeInit();

	static DIBConvert *Create( UINT32 SourceDepth, UINT32 DestDepth, UINT32 Width, LPLOGPALETTE DestPal, 
							   UINT32 DitherType = XARADITHER_ORDERED_GREY);

	static DIBConvert* Create( LPBITMAPINFO pSourceHeader, UINT32 DestDepth, 
								UINT32 DitherType = XARADITHER_ORDERED_GREY);

protected:
	static GDrawContext *GetConvertContext(void);
	static GDrawContext *ConvertContext;				// ptr to special context for conversions
};

#endif
