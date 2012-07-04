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


// The preview filters. Basically the same as the normal filter but never puts
// a dialog up for the export options - always provides sensible defaults for
// the preview.


#ifndef INC_PREVIEWFILTERS
#define INC_PREVIEWFILTERS

#include "bmpfiltr.h"	// for BMP preview
#include "giffiltr.h"	// for GIF preview
#include "exjpeg.h"		// for JPEG preview
#include "pngfiltr.h"	// for, you guessed it.. PNG preview

// Forward definitions.
class AIEPSRenderRegion;

/********************************************************************************************

>	class PreviewFilter : public Filter

	Author:		Martin_Bell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01/01/97
	Purpose:	The filter's sole purpose is to hold the PreviewBitmapSize static. It can
				not import, export or appear on a menu.
	Notes:		20/01/97
				This class used to be derived from AccusoftFilters (but prob never should 
				have been). All other preview filters were derived from this, but are now
				derived from their respectively similar file filter i.e. PreviewFilterBMP
				is derived from BMPFilter. This causes a problem with FILTERIDs cos
				FILTERID_PREVIEW_TIFF is defined to be the same as FILTERID_PREVIEW obviously
				this won't work now that the filters are not all derived from PreviewFilter

********************************************************************************************/

class PreviewFilter : public Filter
{
	CC_DECLARE_DYNAMIC(PreviewFilter);
	
public:
	PreviewFilter();
	BOOL Init();

	// we will always be incompatible
	virtual INT32 HowCompatible( PathName&, ADDR, UINT32, UINT32 );

	// we will never import
	virtual BOOL DoImport(SelOperation*, CCLexFile*, Document*, 
						  BOOL AutoChosen = FALSE, ImportPosition *Pos = NULL,
						   KernelBitmap** ppImportedBitmap = NULL, 
						   DocCoord* pPosTranslate = NULL, String_256* = NULL);

	// we will never export
	virtual BOOL DoExport(Operation*, CCLexFile*, PathName*, Document*, BOOL);

public:
	// The Size of the Preview Bitmap Preference
	static MILLIPOINT PreviewBitmapSize;

};

/********************************************************************************************

>	class PreviewFilterBMP : public BMPFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/6/95
	Purpose:	The filter will save out the BMP Preview Bitmap. Overrides GetExportOptions
				so dialogs are not put up but returns preview export options.

********************************************************************************************/

class PreviewFilterBMP : public BMPFilter
{
	CC_DECLARE_DYNAMIC(PreviewFilterBMP);
	
public:
	PreviewFilterBMP();
	BOOL Init();
	virtual BOOL DoExport(Operation*, CCLexFile*, PathName*, Document*, BOOL);

protected:
	virtual BOOL GetExportOptions(BitmapExportOptions* pOptions);
};

/********************************************************************************************

>	class PreviewFilterGIF : public TI_GIFFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/6/95
	Purpose:	The filter will save out the GIF Preview Bitmap. Overrides GetExportOptions
				so dialogs are not put up but returns preview export options.

********************************************************************************************/

class PreviewFilterGIF : public TI_GIFFilter
{
	CC_DECLARE_DYNAMIC(PreviewFilterGIF);
	
public:
	PreviewFilterGIF();
	BOOL Init();
	virtual BOOL DoExport(Operation*, CCLexFile*, PathName*, Document*, BOOL);

protected:
	virtual BOOL GetExportOptions(BitmapExportOptions* pOptions);
};


/********************************************************************************************

>	class PreviewFilterJPEG : public JPEGExportFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/6/95
	Purpose:	The filter will save out the JPEG Preview Bitmap. Overrides GetExportOptions
				so dialogs are not put up but returns preview export options.
	Note:		22/01/97	Preview filters can generally import as well now (if their base 
				class can) but obviously this one can't - use JPEGImportFilter instead.

********************************************************************************************/

class PreviewFilterJPEG : public JPEGExportFilter
{
	CC_DECLARE_MEMDUMP(PreviewFilterJPEG);
	
public:
	PreviewFilterJPEG();
	BOOL Init();
	virtual BOOL DoExport(Operation*, CCLexFile*, PathName*, Document*, BOOL);

protected:
	virtual BOOL GetExportOptions(BitmapExportOptions* pOptions);
};


/********************************************************************************************

>	class PreviewFilterPNG : public PNGFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/6/95
	Purpose:	The filter will save out the PNG Preview Bitmap. Overrides GetExportOptions
				so dialogs are not put up but returns preview export options.

********************************************************************************************/

class PreviewFilterPNG : public PNGFilter
{
	CC_DECLARE_DYNAMIC(PreviewFilterPNG);
	
public:
	PreviewFilterPNG();
	BOOL Init();
	virtual BOOL DoExport(Operation*, CCLexFile*, PathName*, Document*, BOOL);

protected:
	virtual BOOL GetExportOptions(BitmapExportOptions* pOptions);
};

/********************************************************************************************

>	class ThumbnailFilterPNG : public PreviewFilterPNG

	Author:		Stefan_Stoykov (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/6/97
	Purpose:	The filter will save out the PNG Thumbnail Bitmap. Overrides DoExport
				so dialogs are not put up but returns preview export options.

********************************************************************************************/

class ThumbnailFilterPNG : public PreviewFilterPNG
{
	CC_DECLARE_DYNAMIC(ThumbnailFilterPNG);
	
public:
	ThumbnailFilterPNG() : PreviewFilterPNG() {};

	virtual BOOL DoExport(Operation* pOp, CCLexFile* pFile, PathName* pPath, 
								Document* TheDocument, BOOL ShowOptions);
};

#endif  // INC_PREVIEWFILTERS
