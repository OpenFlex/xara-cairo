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

// CMX (Corel Metafile) Filter

/*
*/

#ifndef INC_CMXFILTER
#define INC_CMXFILTER


class CMXExportDC;
class CMXRenderRegion;

/********************************************************************************************

>	class CMXFilter : public VectorFilter

	Author:		Ben_Summers (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/6/96
	Purpose:	Import filter for CMX format

********************************************************************************************/

class CMXFilter : public VectorFilter
{

CC_DECLARE_DYNAMIC(CMXFilter);

public:
	CMXFilter();
	
	INT32 HowCompatible(PathName& Filename, 
					ADDR  HeaderStart, 
					UINT32 HeaderSize,
					UINT32 FileSize);

	BOOL DoImport(SelOperation*, CCLexFile*, Document*, 
				BOOL AutoChosen = FALSE, ImportPosition *Pos = NULL,
				KernelBitmap** ppImportedBitmap = NULL,
				DocCoord* pPosTranslate = NULL, String_256* = NULL);

	// Export related functions
	BOOL DoExport(Operation*, CCLexFile*, PathName*, Document*, BOOL);
	virtual BOOL PrepareToExport(CCLexFile*, Spread *pSpread);
	virtual void CleanUpAfterExport();
	virtual CMXExportDC* CreateExportDC();
	virtual BOOL FinishExport(void);

	void SetIsDoingClipboardExport(BOOL dopb) {IsDoingClipboardExport = dopb;};
	BOOL GetIsDoingClipboardExport(void) {return IsDoingClipboardExport;};

protected:
	virtual CMXRenderRegion *CreateRenderRegion(Matrix *pM);
	virtual Matrix GetExportTransform(Spread *pSpread) = 0;

	BOOL DisplaySquishyWarning;

	BOOL IsDoingClipboardExport;

private:
	// Used to export CMX files.
	CMXExportDC		*ExportDC;
	CMXRenderRegion *ExportRegion;
};

class CMXFilter16 : public CMXFilter
{

	CC_DECLARE_DYNAMIC(CMXFilter16);

public:
	CMXFilter16();
	BOOL Init();

protected:
	Matrix GetExportTransform(Spread *pSpread);
};

class CMXFilter32 : public CMXFilter
{

	CC_DECLARE_DYNAMIC(CMXFilter32);

public:
	CMXFilter32();
	BOOL Init();

protected:
	Matrix GetExportTransform(Spread *pSpread);

};


#endif  // INC_CMXFILTER
