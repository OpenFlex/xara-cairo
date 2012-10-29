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


// The operations for importing and exporting using the filter system.

#ifndef INC_IMPORTEXPORTOP
#define INC_IMPORTEXPORTOP

//#include "bmpsdlg.h"

// These used to be are OILy as they used to invoke common dialogs etc
// and hence used to be in OilFltrs.h/cpp
// Moved to new kernel based impexpop.h/cpp 4/1/96 as there is now a class, BaseFileDialog
// and derived classes which handle all of the OILy based common dialog functionality

class BmpDlgParam;
class PathName;


/********************************************************************************************

>	class OpMenuImport : public SelOperation

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	Pops up a common dialog to allow the user to import a file into Camelot
				using any of the available import filters.
	SeeAlso:	OpMenuExport; OpDroppedFile

********************************************************************************************/

// Operation token for the OpMenuImport class
#define	OPTOKEN_MENUIMPORT	_T("Import")

class OpMenuImport : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpMenuImport)

public:
	OpMenuImport();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);
	void DoImport(PathName Path, Filter* pFilter, String_256* URL, ImportPosition* pImportPosition=NULL);
	void EndImport();

	virtual BOOL OnDocChangingMsg(Document* pChangingDoc, DocChangingMsg::DocState State);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }

private:
	TCHAR *FilterString;
	static UINT32 SelectedFilterID;
	static INT32 SelectedFilter;


public:
	// The preference for the import path
	static String_256 DefaultImportFilterPath;
};



/********************************************************************************************
>	class BitmapExportParam : public OpParam

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Purpose:	Passes infomation about bitmap(s) to export
	SeeAlso:	OpParam
********************************************************************************************/

class BitmapExportParam : public OpParam
{
	CC_DECLARE_DYNAMIC(BitmapExportParam);

public:
	BitmapExportParam();
	BitmapExportParam(UINT32 Count, KernelBitmap** pBitmap, BmpDlgParam* pParam);
	BmpDlgParam* GetBmpDlgParam()	{ return m_pBmpDlgParam; }
	BOOL SetBmpDlgParam (BmpDlgParam* pParam);

	// Access functions with helpful checking
	virtual UINT32 GetBitmapCount();
	virtual KernelBitmap* GetBitmap(UINT32 Index);

	// We cannot store layers but this removes IS_KIND_OFs when using GIFAnimationExportParam
	virtual Layer * GetLayer(UINT32 Index) { return NULL; }
	virtual UINT32 GetLayerCount() { return 0; }

protected:
	BmpDlgParam* m_pBmpDlgParam;
};



/********************************************************************************************

>	class OpMenuExport : public Operation

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	Pops up a common dialog to allow theuser to export a file from Camelot
				using any of the available import filters.
	SeeAlso:	OpMenuImport; OpDroppedFile

********************************************************************************************/

// Operation token for the OpMenuExport class
#define	OPTOKEN_MENUEXPORT	_T("Export")

class OpMenuExport : public SelOperation
{
public:
	void Do(OpDescriptor*);
	void DoWithParam(OpDescriptor*, OpParam*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);

	static void SaveSelection();
	static void NormaliseSelection();
	static void RestoreSelection();

protected:
	void CreateNamedSet(Filter* pFilter, const PathName& pthTarget);
	BOOL SetBitmapName(KernelBitmap* pTheBitmap, String_256* DefaultName, 	
					   BitmapExportParam* pExportParam = 0);

public:
	// The preference for the export path
	static String_256 DefaultExportFilterPath;

private:
	TCHAR* FilterString;

	static UINT32 SelectedFilterID;
	static INT32 SelectedFilter;
	static UINT32 DefaultBitmapFilterID;
	static INT32 SelectedBitmapFilter;
	static List* m_pSelNodeList;

	CC_DECLARE_DYNCREATE(OpMenuExport);
};



class FileDropInfo
{
public:
	FileDropInfo() {}
	FileDropInfo(WinCoord Point)
	{
		m_DropPoint = Point;
	}

	~FileDropInfo()
	{
		m_FileList.DeleteAll();
	}

	WinCoord GetDropPoint() { return(m_DropPoint); }
	List* GetFileList() { return(&m_FileList); }

protected:
	List m_FileList;
	WinCoord m_DropPoint;
};




/********************************************************************************************

>	class OpDroppedFile : public Operation

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	Responds to the user dragging and dropping a file onto Camelot - it 
				attempts to deduce which import filter should be used to load the file.
				If for any reason it cannot work out which filter to use, a dialog is
				popped up to allow the user to select the filter they want to use.
	SeeAlso:	OpMenuImport; OpMenuExport

********************************************************************************************/

// Operation token for the OpDroppedFile class
#define	OPTOKEN_DROPPEDFILE	_T("DroppedFile")

class OpDroppedFile : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpDroppedFile)

public:
	void DoWithParam(OpDescriptor*, OpParam*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const	{ return FALSE; }
};

#endif // !INC_IMPORTEXPORTOP
