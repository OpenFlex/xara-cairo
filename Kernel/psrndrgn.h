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


// Render region for rendering to PostScript devices.

#ifndef INC_PSRNDRGN
#define INC_PSRNDRGN

#include "cameleps.h"

class PrintView;
class PSPrintDC;

/********************************************************************************************

>	class PrintPSRenderRegion : public CamelotEPSRenderRegion

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/24/95
	Purpose:	Provide a render region for rendering to PostScript devices (usually via
				a PostScript printer driver).
	SeeAlso:	CamelotEPSRenderRegion

********************************************************************************************/

class PrintPSRenderRegion : public CamelotEPSRenderRegion
{
	CC_DECLARE_DYNAMIC(PrintPSRenderRegion)
	
	friend class PSPrintDC;

	public:
		PrintPSRenderRegion(DocRect ClipRect, Matrix ConvertMatrix, FIXED16 ViewScale);
		~PrintPSRenderRegion();

		virtual BOOL InitDevice();
		virtual BOOL StartRender();
		virtual BOOL StopRender();
		virtual BOOL CloseDown();
		virtual void ConditionalSuicide ( void );
		static BOOL InitPSDevice(CNativeDC * pDC, PrintView *pPrintView);
		virtual BOOL RenderChar(WCHAR ch, Matrix* pMatrix);

				BOOL PushClipRegion(KernelDC*, const DocRect& Rect);
				BOOL PopClipRegion(KernelDC*);
				BOOL WriteClipRegion(KernelDC *pDC, const DocRect& Rect);

	protected:
		virtual BOOL WriteProlog(KernelDC*);
		virtual BOOL WriteSetup(KernelDC*);
				BOOL OutputPSHeader();
		virtual void Initialise();
		virtual void DeInitialise();
		virtual BOOL WriteSepTables(KernelDC *pDC);
				BOOL WritePlateName(KernelDC *pDC);
				BOOL WritePlateScreen(KernelDC *pDC);
		virtual BOOL WriteSepFunctions(KernelDC *pDC);
				BOOL WritePhotoNegative(KernelDC *pDC);
				BOOL WriteRenderPaper(KernelDC *pDC);
				BOOL WriteFillPaper(KernelDC *pDC);
				BOOL WriteSetTransfer(KernelDC *pDC);
				
	private:
		BOOL WriteSepTablesHelper(KernelDC *pDC, BYTE* Table);
};


#endif  // INC_PSRNDRGN
