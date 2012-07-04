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

#ifndef INC_IMAGEMAPFILTER
#define INC_IMAGEMAPFILTER

#include "filtimop.h"	//For ImagemapFilterOptions
#include "filtirr.h"	//For ImagemapRenderRegion
//#include "filters.h"	//For AuldLangSyne - in camtypes.h [AUTOMATICALLY REMOVED]
#include "htmlexp.h"	//The HTML export filter
//#include "list.h"		//For the list class - in camtypes.h [AUTOMATICALLY REMOVED]

class CCLexFile;
class Operation;

/**************************************************************************************

>	class ImagemapFilter : public HTMLExportFilter

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Purpose:	The imagemap export filter class.

				This code contained in this class is called when

				a. The user selects the Imagemap filter class in the Export...
					dialog box.

				b. The user tells one of the bitmap filters to export an imagemap
					at the same time as it exports the bitmap

**************************************************************************************/
class ImagemapFilter : public HTMLExportFilter
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(ImagemapFilter);

	//Constructor and initialiser
public:
	ImagemapFilter();

	virtual BOOL Init();

	//Destructor
public:
	~ImagemapFilter();


	//Main entry points
public:
	virtual BOOL DoExport(Operation* pOp, CCLexFile* pFile, PathName* pPath, Document* pDoc,
						  BOOL ShowOptions);
	
	
	BOOL PrepareAndWriteData(Document* pDoc);

	BOOL PrepareData(Document* pDoc);
	BOOL WriteData();

	BOOL GetOptionsFromUser(ImagemapFilterOptions* pifoDefault, PathName* ppthFile, CCLexFile* pFile);
	
	//This function produces the "Do you want to replace file?" message
	BOOL WillAcceptExistingFile(PathName pthToReplace);

	void SearchFileForImagemaps(const PathName& pthSearch, List* plstToAdd);




	//Access functions
public:
	void SetFilterOptions(ImagemapFilterOptions ifoOptions);
	ImagemapFilterOptions GetFilterOptions();

	BOOL ExportSelectionOnly(BOOL MaskedRender = FALSE)
	{
		return (ms_Options.m_stExportArea==SELECTION);
	}

	//Action functions (called from the entry points to do things)
protected:
	void Write(CCLexFile* pfileToWrite);


	//Toolkit functions
protected:
	BOOL PrepareRenderRegion(Document* pDoc);
	void ForceBackgroundRedrawOff(DocView* pView);
	void RestoreBackgroundRedraw(DocView* pView);

	BOOL OpenImagemapFile(CCLexFile* pFile, PathName* pPath);
	BOOL CloseImagemapFile(CCLexFile* pFile);

	INT32 WriteHelper(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);
	INT32 WriteBitmapHTML(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);
	INT32 WriteImagemapHTML(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);
	INT32 WritePreamble(TCHAR* pcBuffer);

	void CopyToClipboard(TCHAR* pcBuffer=NULL);

	BOOL WriteDataToExistingFile(CCLexFile* pFile, PathName* pPath);
	BOOL WriteDataToNewFile(CCLexFile* pFile, PathName* pPath);

	BOOL WriteExistingDataHelper(CCLexFile* pfileTo, CCLexFile* pfileFrom, PathName* pPath);
	BOOL ContainsSameImagemapName(CCLexFile* pfileSearch);

	void BuildMapNamesList(CCLexFile* pfileSearch, PathName* ppthSearch, List* plstToAdd);







	//Member variables
protected:
	//This object should hold all the settings that can be set for the imagemap filter
	static ImagemapFilterOptions ms_Options;

	//The imagemap render region
	ImagemapRenderRegion* m_pRegion;

	//Some member variables to stop background rendering
	DocView* pView;
	BOOL BackgroundRedrawStateSet;
	BOOL BackgroundRedrawState;

	//Static member variables
private:
	//These strings are used to put preferences into the registry
	static TCHAR ms_strApprox[];
	static TCHAR ms_strAllRectangles[];
	static TCHAR ms_strClipboard[];	
	static TCHAR ms_strFile[];	
	static TCHAR ms_strInsert[];	
};

#endif	// INC_IMAGEMAPFILTER
