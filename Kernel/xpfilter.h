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

// The Camelot Native File format for Studio (version 1)

#ifndef INC_XPFILTER
#define INC_XPFILTER

#include "native.h"	// 	CamelotNativeFilter

class WebPrefsDlgParam;
class CapabilityTree;

/********************************************************************************************

>	class PluginNativeFilter : public CamelotNativeFilter

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/01/05
	Purpose:	This is the plugin import/export filter that passes Xar format data to an 
				external object for further processing.

********************************************************************************************/

class PluginNativeFilter : public CamelotNativeFilter
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(PluginNativeFilter);

public:
	// Construction and initialisation
	PluginNativeFilter();
	~PluginNativeFilter();
	BOOL Init( xmlNode* pFilterNode );

	// HowCompatible() returns value in range 0 to 10:
	//   0 => "Definitely Not"
	//  10 => "Yes Sir, that's my file format"
	virtual INT32 HowCompatible( PathName& Filename, ADDR  HeaderStart, UINT32 HeaderSize,
							   UINT32 FileSize );

	// We need to override DoImport to handle the translation
	virtual BOOL DoImport(SelOperation*, CCLexFile*, Document*, 
						  BOOL AutoChosen = FALSE, ImportPosition *Pos = NULL,
						  KernelBitmap** ppImportedBitmap = NULL,
						  DocCoord* pPosTranslate = NULL, String_256* = NULL);

	// We need to override DoExport to handle the translation
	virtual BOOL DoExport(Operation*, CCLexFile*, PathName*, Document*, BOOL);

	// Override these so that the output files aren't compressed
	virtual BOOL StartCompression() { return(TRUE); }
	virtual BOOL StopCompression() { return(TRUE); }

	virtual BOOL GetExportOptions( WebPrefsDlgParam *pPrefs );

	virtual BOOL IsWebFilter() { return FALSE; }
	virtual BOOL IsCompactNativeFilter() { return FALSE; }

	// Find out how much compression is required for bitmaps
	virtual INT32 GetBitmapCompression(); 

	// Find out whether the user has requested a preview bitmap
	virtual BOOL GetPreviewBitmapExport(); 

	// Find out whether the user has requested convert text to outlines
	virtual BOOL GetConvertTextToOutlines(); 
	
	// Find out whether the user has requested remove invisible layers
	virtual BOOL GetRemoveInvisibleLayers(); 

	// Find out whether the user has requested to remove unused colours
	virtual BOOL GetRemoveUnusedColours(); 

	// Find out whether the user has requested to save XPE bitmaps
	virtual BOOL GetSaveXPEBitmaps(); 
	virtual BOOL SetSaveXPEBitmaps(BOOL NewSaveXPEBitmaps);

	virtual INT32 HowCompatibleIsFileType(char* pFileType);

	virtual	double GetSimilarPathTolerance(NodePath* pPath);

	virtual INT32 GetMaxPathLookUp();

	virtual WebPrefsDlgParam* GetCachedExportOptions() { return NULL; }

	virtual BOOL WriteSpecificRegularShapes() { return(TRUE); }

	// This function allows derived filters to cause objects to output
	// bounding box records
	virtual BoundsWriteLevel GetBoundsWriteLevel() { return(m_BoundsLevel); }

	BOOL SetProgressBarCount(UINT32 n);

	void AddBitmapToList(KernelBitmap* pBmp)
	{
		KernelBmpListItem* pItem = new KernelBmpListItem(pBmp);
		if (pItem)
			m_BitmapList.AddTail(pItem);
	}

	String_256 GetNewBitmapName();

protected:
//	virtual BaseCamelotFilter* CreateNULLFilter(Document* pDocument);
	
	virtual char* GetExportFileType();	// Returns a three char long ASCII string

	BOOL GenerateExportData(CapabilityTree* pPlugCaps);
	BOOL DoConversionPassN(CapabilityTree* pPlugCaps, INT32 ConvertPass);
	BOOL DoBitmapResamplePass(CapabilityTree* pPlugCaps);
	virtual Node* GetExportNode();
	virtual BOOL BeginDocumentExport();
	virtual BOOL EndDocumentExport();
	virtual BOOL WriteCurrentAttributes();

	// Resource IDs of the strings that describe this filter.
	UINT32 FilterNameID;
	UINT32 FilterInfoID;

	// The string to display when actually exporting rather than rendering.
	// 0 if we're not an export filter.
	// ExportMsgID is used in ExportRender when we are rendering the bitmap
	UINT32 ExportingMsgID;

	Node* m_pNewTree;

	UINT32 m_ProgressOffset;
	BOOL m_bSaveXPEBitmaps;
	BOOL m_bPreviewBitmap;

	BoundsWriteLevel m_BoundsLevel;
	INT32 m_BitmapCompression;

	List m_BitmapList;
	INT32 m_BitmapCount;
};


#endif  // INC_XPFILTER
