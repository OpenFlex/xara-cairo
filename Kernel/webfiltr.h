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
// The Web file format for Camelot first version.
// This is the minimalistic form of the new native file filter 

#ifndef INC_WEBFILTER
#define INC_WEBFILTER

#include "bmpprefs.h"	// SelectionType

class WebPrefsDlgParam;
class NodePath;

/********************************************************************************************

>	class CamelotWebFilter : public BaseCamelotFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/5/96
	Purpose:	This filter is for the new web file format which is the minimilistic form of
				the new version 2 native file filter.
				The BaseCamelotFilter provides common functionality for both this and the
				web file filter as they are essentially the same thing. 

********************************************************************************************/

class CamelotWebFilter : public BaseCamelotFilter
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(CamelotWebFilter);

public:
	// Construction and initialisation
	CamelotWebFilter();
	~CamelotWebFilter();
	BOOL Init();

	virtual BOOL IsWebFilter()				{ return BaseCamelotFilter::GetMinimalWebFormat(); } // FALSE by default
	virtual BOOL IsCompactNativeFilter()	{ return !BaseCamelotFilter::GetMinimalWebFormat(); } // TRUE by default

	virtual BOOL IsDefaultDocRequired(const TCHAR* pcszPathName);

	virtual INT32 HowCompatibleIsFileType(char* pFileType);

	virtual	double GetSimilarPathTolerance(NodePath* pPath);

	// WEBSTER - markn 11/2/97
	// Added to Webster so saving .web files isn't so slow for certain git files
	virtual INT32 GetMaxPathLookUp();

	//Graham 22/5/97 Functions for exporting HTML tags to the clipboard
	virtual BOOL ShouldExportHTMLTag();

protected:
	virtual BaseCamelotFilter* CreateNULLFilter(Document* pDocument);

	virtual char* GetExportFileType(); // Returns a three char long ASCII string

	virtual BOOL BeginDocumentExport();
	virtual BOOL EndDocumentExport();
	virtual OpDescriptor* GetDialogueOp ( void );

	// Resource IDs of the strings that describe this filter.
	UINT32 FilterNameID;
	UINT32 FilterInfoID;

	// The string to display when actually exporting rather than rendering.
	// 0 if we're not an export filter.
	// ExportMsgID is used in ExportRender when we are rendering the bitmap
	UINT32 ExportingMsgID;

private:
	BOOL MinWebFormat;
};

/********************************************************************************************

>	class CamelotNULLWebFilter : public CamelotWebFilter

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/6/96
	Purpose:	This is a dummy filter that is used to calculate the size of the file 
				that will be exported.

				It's like a NULL byte sink, where no bytes are actually outputted anywhere

********************************************************************************************/

class CamelotNULLWebFilter : public CamelotWebFilter
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(CamelotNULLWebFilter);

public:
	// Construction and initialisation
	CamelotNULLWebFilter(BaseCamelotFilter* pParentFilter,Document* pDocument);

  	// WEBSTER - markn 29/1/97
	// Part of the general form of the system used to convert text to outlines in v1.5
	// Node & group references
	virtual void		AddNodeGroupRefToList(Node* pNode,NodeGroup* pGroup);
	virtual NodeGroup*	FindGroupForThisNode(Node* pNode);

	// WEBSTER - markn 11/2/97
	// System for writing tag descriptions to the file (introduced for the TAG_MOULD_BOUNDS record)
	virtual void AddTagDescription(UINT32 Tag, UINT32 ID);

	//Graham 22/5/97	We don't export HTML tags to the clipboard in this filter:
	virtual BOOL ShouldExportHTMLTag()
	{
		return FALSE;
	}

	virtual void ExportHTMLTag()
	{
	}

protected:
	CXaraFile* CreateCXaraFile();

private:
	BaseCamelotFilter* pParentFilter;
};

#endif  // INC_WEBFILTER


