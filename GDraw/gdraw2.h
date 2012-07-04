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


enum eBevelStyle {
	BEVEL_FLAT,
	BEVEL_ROUND,
	BEVEL_HALFROUND,
	BEVEL_FRAME,
	BEVEL_MESA_1,
	BEVEL_MESA_2,
	BEVEL_SMOOTH_1,
	BEVEL_SMOOTH_2,
	BEVEL_POINT_1,
	BEVEL_POINT_2a,
	BEVEL_POINT_2b,
	BEVEL_RUFFLE_2a,
	BEVEL_RUFFLE_2b,
	BEVEL_RUFFLE_3a,
	BEVEL_RUFFLE_3b
} ;
/*
enum eError {
	GERROR_NO_ERROR,
	GERROR_BAD_BITMAP,
	GERROR_BAD_GRADUATION_STYLE,
	GERROR_BAD_GRADUATION_TABLE,
	GERROR_BAD_TILE_STYLE,
	GERROR_BAD_TRANSPARENCY_STYLE,
	GERROR_BAD_PARAMETERS,
	GERROR_BAD_PATH,
	GERROR_CORRUPT_EDGE_TABLE,
	GERROR_INCOMPATIBLE_BITMAPS,
	GERROR_INCOMPATIBLE_REGION,
	GERROR_INVALID_SCANLINE_ROUTINE,
	GERROR_NO_BITMAP,
	GERROR_NOT_32_BITS_PER_PIXEL,
	GERROR_OUT_OF_MEMORY,
	GERROR_OUTPUT_PATH_TOO_COMPLEX,
	GERROR_STACK_OVERFLOW,
	GERROR_UNDEFINED_FILL_STYLE,
	GERROR_UNDEFINED_MEMORY_HANDLERS,
	GERROR_UNIMPLEMENTED,
	GERROR_FAILED
} ;
*/
extern "C"
{
	extern INT32 GDraw2_GetVersion() ;

	extern INT32 GDraw2_ClearLastError() ;
	extern eError GDraw2_GetLastError() ;
/*
	extern INT32 GDraw2_SetMemoryHandlers(
		LPBYTE (*MemoryAlloc)( size_t Size ),
		void   (*MemoryFree) ( LPBYTE Address )
	) ;
	extern INT32 GDraw2_Terminate() ;
*/
	extern INT32 GDraw2_SetDIBitmap(
		CONST BITMAPINFOHEADER* pBitmapInfo,
		CONST BYTE* pBitmap,
		eBevelStyle nBevelStyle,
		float LightAngle1,
		float LightAngle2
	) ;
	extern INT32 GDraw2_FillTriangle(
		CONST POINT aPoints[3],
		double fNormalX,
		double fNormalY
	) ;
	extern INT32 GDraw2_FillTrapezium(
		CONST POINT aPoints[4],
		double fNormalX,
		double fNormalY
	) ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
