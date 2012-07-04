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

//
// The Flare Template format

#ifndef INC_FTFILTER
#define INC_FTFILTER

#include "native.h"
//#include "webfiltr.h"	// 	CamelotWebFilter

/********************************************************************************************

>	class FlareTemplateFilter : public CamelotWebFilter

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/07/97
	Purpose:	A filter for the new flare template format (text based form of the the new
				version 2 native file filter.

				The CamelotWebFilter provides most of the implementation.

********************************************************************************************/

class FlareTemplateFilter : public CamelotNativeFilter
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(FlareTemplateFilter);

public:
	// Construction and initialisation
	FlareTemplateFilter();
	~FlareTemplateFilter();
	BOOL Init();

	virtual BOOL IsWebFilter()
		{ return BaseCamelotFilter::GetMinimalWebFormat(); } // FALSE by default
	virtual BOOL IsCompactNativeFilter()
		{ return !BaseCamelotFilter::GetMinimalWebFormat(); } // TRUE by default

	virtual INT32 HowCompatible(PathName& Filename, ADDR HeaderStart, UINT32 HeaderSize,
							   UINT32 FileSize);

protected:
	// Override this to not bother with any of that filesize rubbish
//	virtual BaseCamelotFilter* CreateNULLFilter(Document* pDocument) { return(NULL); };

	virtual CXaraFile* CreateCXaraFile();

	// We don't want to change the file length... (just yet 8-)
	virtual BOOL CorrectFileHeader(CCLexFile* pFile) { return(TRUE); };

	virtual BOOL SetTotalProgressBarCount(UINT32 n);

	// Resource IDs of the strings that describe this filter.
	UINT32 FilterNameID;
	UINT32 FilterInfoID;

	// The string to display when actually exporting rather than rendering.
	// 0 if we're not an export filter.
	// ExportMsgID is used in ExportRender when we are rendering the bitmap
	UINT32 ExportingMsgID;

protected:
	// Preferences for Flare template filter (separate from the base class)
	static INT32 FTBitmapCompression;
	static BOOL FTPreviewBitmapExport;
	static BOOL FTConvertTextToOutlines;
	static BOOL FTHTMLToClipboard;
	static BOOL FTConvertBlendsToOutlines;

public:
	// Find out how much compression is required for bitmaps
	virtual INT32 GetBitmapCompression(); 
	virtual INT32 SetBitmapCompression(INT32 NewBmpComp);

	// Find out whether the user has requested a preview bitmap
	virtual BOOL GetPreviewBitmapExport(); 
	virtual BOOL SetPreviewBitmapExport(BOOL NewExportPreviewBmp);

	// Find out whether the user has requested convert text to outlines
	virtual BOOL GetConvertTextToOutlines(); 
	virtual BOOL SetConvertTextToOutlines(BOOL NewConvertTextToOutlines);
	
	// WEBSTER - markn 28/1/97
	// Find out whether the user has requested convert blends to outlines
	virtual BOOL GetConvertBlendsToOutlines(); 
	virtual BOOL SetConvertBlendsToOutlines(BOOL NewConvertBlendsToOutlines);
	
	// Find out whether the user has requested remove invisible layers
	virtual BOOL GetRemoveInvisibleLayers(); 
	virtual BOOL SetRemoveInvisibleLayers(BOOL NewRemoveInvisibleLayers);

	// Find out whether the user has requested to remove unused colours
	virtual BOOL GetRemoveUnusedColours(); 
	virtual BOOL SetRemoveUnusedColours(BOOL NewRemoveUnusedColours);

	// Find out whether the user has requested to remove unused colours
	virtual BOOL GetMinimalWebFormat(); 
	virtual BOOL SetMinimalWebFormat(BOOL NewMinimalWebFormat);

	// Find out whether the user wants an HTML tag put on the clipboard
	virtual BOOL ShouldExportHTMLTag();
	virtual BOOL GetHTMLToClipboard();
	virtual BOOL SetHTMLToClipboard(BOOL NewHTMLToClipboard);
};

#endif  // INC_FTFILTER
