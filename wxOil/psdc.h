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


// Device context used for printing to PostScript devices.

#ifndef INC_PSDC
#define INC_PSDC

#include "kerneldc.h"

// Size of buffer used to xfer PostScript data to device.
#define MAX_PSBUF (512)

class PrintPSRenderRegion;

/********************************************************************************************

>	class PassThruBuffer

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/24/95
	Purpose:	A simple structure for passing data to PostScript devices under Windows.
				It holds the number of bytes in the buffer followed by the data.
				(See SDK/MFC docs for Escape() function)
	SeeAlso:	PSPrintDC

********************************************************************************************/

class PassThruBuffer
{
public:
	INT32 nCount;
	TCHAR  Data[MAX_PSBUF + 1];
	char   CharData[MAX_PSBUF+1];
};

// Used for rendering text via GDI
// (It is a simple cache system).
class PSDCFontInfo
{
public:
	PSDCFontInfo();

public:
	WORD Typeface;
	BOOL Bold;
	BOOL Italic;
	MILLIPOINT Width;
	MILLIPOINT Height;
	ANGLE Rotation;
	wxFont * pRenderFont;
	wxFont * pOldFont;
};

/********************************************************************************************

>	class PSPrintDC : public KernelDC

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/03/94
	Purpose:	Provide a device context for printing to a PostScript printer.
	SeeAlso:	KernelDC; PSPrintRenderRegion

********************************************************************************************/

class PSPrintDC : public KernelDC
{
	CC_DECLARE_DYNAMIC(PSPrintDC)
public:
	PSPrintDC(CNativeDC *pDC);
	~PSPrintDC();

	// Functions to do the actual output to the PostScript printer.
	virtual BOOL OutputNewLine();
	virtual BOOL OutputToken(TCHAR*);
	virtual BOOL OutputDirect(BYTE *, INT32);

	// Handles the change of co-ordinate system that GDI introduces to PS devices.
	virtual BOOL OutputCoord(DocCoord&, EPSAccuracy Accuracy = ACCURACY_NORMAL);
	virtual BOOL OutputUserSpaceValue(MILLIPOINT, EPSAccuracy Accuracy = ACCURACY_NORMAL);

	void SetDCTransforms(Matrix RenderMatrix, View *pView);
	WinCoord TransformCoord(const DocCoord&);

	void AttachRenderRegion(PrintPSRenderRegion *pRegion)
		{	pPSRegion = pRegion;   }
	void DetachRenderRegion() { pPSRegion = NULL; }

	// Function to call when using OS functions to render.
	BOOL StartOSOutput();
	BOOL EndOSOutput();

	// Function to call when printing is finished
	BOOL FlushDC();

	// Flushes pending PostScript output to device.
	BOOL FlushPSBuffer();

	BOOL SelectNewFont(WORD Typeface, BOOL Bold, BOOL Italic, 
					   MILLIPOINT Width, MILLIPOINT Height, ANGLE Rotation);

	// Functions to setup the use of a Postscript clipping rectangle
	BOOL SetClipping(BOOL NewState);
	BOOL OutputPSClipping();

protected:

	BOOL MakeRoomInBuffer(INT32);
	void WritePSchar(char * pBuf, INT32 nBytes);
	void WritePSTCHAR(TCHAR * pBuf, INT32 nBytes);
	
	// Used for pending output.
	PassThruBuffer Buffer;

	// The transforms to use when outputting user space values.
	// The matrix is used for co-ordinates; the FIXED16 is used to convert distances
	// (e.g. linewidths).
	Matrix RenderMatrix;
	MILLIPOINT PixelSize;
	View *pView;

	// If zero, then it is not safe to do GDI output; if non-zero then it is.
	INT32 SafeToUseGDI;

	// Initialised to true on contruction of this DC. It will be set to FALSE as
	// soon as we attempt to output a token. We can use this to control once only
	// startofpage output data such as DSC comments.
	BOOL StartOfPage;

	// If TRUE, then the current PS context is the one set up by GDI, otherwise it is the
	// context used by Camelot.
	BOOL GDIContextIsCurrent;

	// Specifies whether to output the current clipping region to Postscript in order to
	// clip our PostScript graphics output. This defaults to TRUE.
	BOOL UsePSLevelClipping;

	// Used to cache GDI fonts.
	PSDCFontInfo FontInfo;

	// Used for outputing postscript header.
	PrintPSRenderRegion *pPSRegion;
};



#endif  // INC_PSDC


