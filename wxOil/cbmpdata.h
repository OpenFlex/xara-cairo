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


// A dialog box for previwing bitmaps

#ifndef INC_BitmapPreviewData
#define INC_BitmapPreviewData

#include "filtimop.h"	//class ImagemapFilterOptions

class DocColour;
class KernelBitmap;
class PathName;
class BitmapExportOptions;
class BmapPrevDlg;
class Spread;

// define the different ways to specify the background
typedef enum {BROWSER_BGR_NONE, BROWSER_BGR_DOC, BROWSER_BGR_BITMAP, BROWSER_BGR_CHECKER} 
	BrowserBackground;


// class encapsulating the different options for displaying a browser preview of a bitmap
class BrowserPreviewOptions : public CCObject
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(BrowserPreviewOptions);

	friend class BitmapPreviewData;
public:
	//constructors
	BrowserPreviewOptions();
	BrowserPreviewOptions(BrowserBackground Bgr, BOOL bInfo, BOOL bImagemap, 
		ImagemapFilterOptions ifoToSet=ImagemapFilterOptions());
	BrowserPreviewOptions(const BrowserPreviewOptions& obj);

	// get/set functions
	void Get(BrowserBackground *pBgr, BOOL *pbInfo, BOOL *pbImagemap, 
		ImagemapFilterOptions* pifoToGet=NULL);

	void Set(BrowserBackground Bgr, BOOL bInfo, BOOL bImagemap,
		ImagemapFilterOptions ifoToSet=ImagemapFilterOptions());

	Spread * GetSpread() { return m_pSpread; }
	void  SetSpread(Spread * pSpread) { m_pSpread = pSpread; }

protected:
	BrowserBackground	m_Background;	// the background
	BOOL				m_bInfo;		// display additional bitmap info
	BOOL				m_bImagemap;	// include the imagemap as well
	Spread *			m_pSpread;		// the spread which the background is defined on 
	ImagemapFilterOptions m_ifoImagemapOptions;	//Graham 25/7/97: Options for the imagemap
};

// a class which just keeps data for each of the two bitmaps being previewed - kernel bitmap, file name, etc.
class BitmapPreviewData : public CCObject
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(BitmapPreviewData);

friend class BitmapExportPreviewDialog;
friend class BmapPrevDlg;

public:
	BitmapPreviewData();
	~BitmapPreviewData();

	void DeleteBitmapData();

	void SetNewBitmap(KernelBitmap *pKernelBitmap, UINT32 FileSize, BitmapExportOptions *pOptions);

	void GenerateBitmapInfoStrings(String_64 &ImageSize, String_64 &FileSize, BOOL bIncludeBpp = FALSE);
	void CalculateTime(String_64 &timestring,double);
	BOOL GenerateHTMLStub(BrowserPreviewOptions BrowserOptions);

	static BOOL ComposeHTMLColour(DocColour *pColour, String_32 &OutColour);
	static BOOL ExportBrowserTypeBitmap(KernelBitmap *pBmp,PathName *pOutFile);
	static BOOL ExportImagemap(CCDiskFile &DiskFile, PathName *pPath, SelectionType Sel, DPI dpi,
		ImagemapFilterOptions ifoOptionsToUse);
	static BOOL SetBackgroundFromPage(CCDiskFile &DiskFile, Spread * pSpread = NULL);

private:
	KernelBitmap *m_pBitmap;
	UINT32 m_FileSize;
	BitmapExportOptions *m_pOptions;
	PathName *m_pTempHTMLPath;

	BOOL m_bIsSameBitmap; // indicate whether the data should be deleted when replaced
	static PathName *pPagePath; // pointer to the page background bitmap
};


#endif // INC_BitmapPreviewData
