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

#ifndef INC_NATIVE
#define INC_NATIVE

//#include "camfiltr.h"	// 	BaseCamelotFilter - in camtypes.h [AUTOMATICALLY REMOVED]
#include "bmpprefs.h"	// SelectionType

class WebPrefsDlgParam;

/********************************************************************************************

>	class CamelotNativeFilter : public BaseCamelotFilter

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/5/96
	Purpose:	This filter is for the new Native file format which comes after the version
				1.1 ready for version 2.
				The BaseCamelotFilter provides common functionality for both this and the
				web file filter as they are essentially the same thing. 

********************************************************************************************/

class CamelotNativeFilter : public BaseCamelotFilter
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(CamelotNativeFilter);

public:
	// Construction and initialisation
	CamelotNativeFilter();
	~CamelotNativeFilter();
	BOOL Init();

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

	virtual INT32 HowCompatibleIsFileType(char* pFileType);

	virtual	double GetSimilarPathTolerance(NodePath* pPath);

	virtual INT32 GetMaxPathLookUp();

	virtual WebPrefsDlgParam* GetCachedExportOptions() { return NULL; }

protected:
	virtual BaseCamelotFilter* CreateNULLFilter(Document* pDocument);
	
	virtual char* GetExportFileType();	// Returns a three char long ASCII string

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

public:

};

/********************************************************************************************

>	class CamelotNULLNativeFilter : public CamelotNativeFilter

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/6/96
	Purpose:	This is a dummy filter that is used to calculate the size of the file 
				that will be exported.

				It's like a NULL byte sink, where no bytes are actually outputted anywhere

********************************************************************************************/

class CamelotNULLNativeFilter : public CamelotNativeFilter
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(CamelotNULLNativeFilter);

public:
	// Construction and initialisation
	CamelotNULLNativeFilter(BaseCamelotFilter* pParentFilter,Document* pDocument);

	// WEBSTER - markn 31/1/97
	// Replaced with general system
//	virtual void		AddTextStoryGroupRefToList(TextStory* pStory,NodeGroup* pGroup);
//	virtual NodeGroup*	FindTextStoryGroupRefGroup(TextStory* pStory);
//	virtual TextStory*	FindTextStoryGroupRefTextStory(NodeGroup* pGroup);

  	// WEBSTER - markn 29/1/97
	// Part of the general form of the system used to convert text to outlines in v1.5
	// Node & group references
	virtual void		AddNodeGroupRefToList(Node* pNode,NodeGroup* pGroup);
	virtual NodeGroup*	FindGroupForThisNode(Node* pNode);

	// WEBSTER - markn 11/2/97
	// System for writing tag descriptions to the file (introduced for the TAG_MOULD_BOUNDS record)
	virtual void AddTagDescription(UINT32 Tag, UINT32 ID);

protected:
	CXaraFile* CreateCXaraFile();

private:
	BaseCamelotFilter* pParentFilter;
};


#endif  // INC_NATIVE


