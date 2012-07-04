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


// kernel class to encompass bitmaps lists
// This covers the bitmap document component related items
// The global bitmap lists are in bmplist.h 
// This file was broken off from bmplist 11/6/96

#ifndef	INC_BMPCOMP
#define	INC_BMPCOMP

//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "doccomp.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class OILBitmap;
class BitmapInfo;
class RenderRegion;
class Filter;
class FillGeometryAttribute;
class Document;
class EPSExportDC;
class KernelBitmap;
class KernelBitmapRef;

class ExportedBitmaps;
class ImportedBitmaps;
class CXaraFileRecord;
class CXaraFile;
class CXaraFileRecordHandler;



/***********************************************************************************************

>	class SaveBitmapsPool : public List

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Purpose:	A list of Kernel Bitmaps to save out
	SeeAlso:	-

***********************************************************************************************/

class BitmapSavePool : public List
{
	CC_DECLARE_MEMDUMP(BitmapSavePool)

public:
	BOOL AddBitmap(KernelBitmap* pBitmap);
	INT32 GetBitmapIndex(KernelBitmap* pBitmap);
};

/***********************************************************************************************

>	class BitmapList : public List

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Purpose:	A list of Kernel Bitmaps used by a document
	SeeAlso:	-

***********************************************************************************************/

class BitmapList : public List
{
CC_DECLARE_MEMDUMP(BitmapList)

	friend class GlobalBitmapList;

public:
	BitmapList();
	~BitmapList();

	void Init(BaseDocument *ParentDocument);

public:		// Access to special BitmapList data members
	BOOL AddItem(KernelBitmap *Item);
	BOOL RemoveItem(KernelBitmap *Item);

	BOOL MoveAfter(KernelBitmap *InsertPoint, KernelBitmap *ItemToMove);
	BOOL MoveBefore(KernelBitmap *InsertPoint, KernelBitmap *ItemToMove);

	BaseDocument *GetParentDocument(void);

	// Check to see if the bitmap exists already
	KernelBitmap* FindDuplicateBitmap(OILBitmap* pBitmap);

	// Find the default bitmap
	KernelBitmap* FindDefaultBitmap();

private:
	BaseDocument *ParentDoc;
};

/********************************************************************************************

>	class BitmapListComponentClass : public DocComponentClass

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/12/94
	Purpose:	Provide a class that will add Bitmap components to new documents.
	SeeAlso:	DocComponentClass

********************************************************************************************/

class BitmapListComponentClass : public DocComponentClass
{
	CC_DECLARE_DYNAMIC(BitmapListComponentClass)

public:
	static BOOL Init();

	BOOL AddComponent(BaseDocument *);
};

/********************************************************************************************

>	class BitmapListComponent : public DocComponent

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/12/94
	Purpose:	Provide a component that contains a list of kernel bitmaps in use by
				a document.
	SeeAlso:	DocComponent

********************************************************************************************/

class BitmapListComponent : public DocComponent
{
	CC_DECLARE_DYNAMIC(BitmapListComponent)

public:
	BitmapListComponent();
	BitmapListComponent(BitmapList *);
	virtual ~BitmapListComponent();
	BitmapList* GetBitmapList() { return pBitmaps; }

public:
	// Usual document component functions...
	virtual BOOL EPSStartImport(EPSFilter*);
	virtual void EPSEndImport(EPSFilter*, BOOL);
	virtual BOOL WriteEPSComments(EPSFilter*);
	virtual BOOL WriteScript(EPSFilter*);
	virtual ProcessEPSResult ProcessEPSComment(EPSFilter*, const char*);
	virtual void EndOfEPSComment(EPSFilter*);
	virtual INT32 GetSizeOfExport(Filter*);

	virtual BOOL EPSStartExport(EPSFilter*);
	virtual void EPSEndExport(EPSFilter*);

	ExportedBitmaps* GetBitmapExportPool() { return pBitmapsToExport; }
	ImportedBitmaps* GetImportList() { return pImportedBitmaps; }

protected:
	// Function to help with the exporting of the bitmap pool
	BOOL ExportBitmapPoolItem(INT32 BitmapNum, EPSFilter* pFilter, EPSExportDC* pDC, KernelBitmap* pBitmap);

protected:
	// This is the list of bitmaps that we need to export (used for EPS export only) ...
	ExportedBitmaps* pBitmapsToExport;

private:
	BitmapList* pBitmaps;

public:
	virtual BOOL StartComponentCopy();
	virtual BOOL EndComponentCopy();     
	virtual void AbortComponentCopy();

public:
	// These are the Camelot Version 2 Web and Native file related functions
	virtual BOOL StartImport(BaseCamelotFilter* pFilter);
	virtual BOOL EndImport(BaseCamelotFilter* pFilter, BOOL Success);
	virtual BOOL StartExport(BaseCamelotFilter* pFilter);
	virtual BOOL EndExport(BaseCamelotFilter* pFilter, BOOL Success);

	// The public way of importing and exporting bitmaps for the new native/web filters
	KernelBitmap* GetReadBitmapReference(INT32 BitmapRef);
	INT32 GetWriteBitmapReference(KernelBitmap* pBitmap, BaseCamelotFilter* pFilter);
	// Code to save out a bitmap definition
	INT32 SaveBitmapDefinition(KernelBitmap* pBitmap, BaseCamelotFilter* pFilter);
	BOOL LoadBitmapDefinition(CXaraFileRecordHandler* pXFileRecHandler, CXaraFile* pCXFile,
							  INT32 Tag, UINT32 Size, UINT32 RecordNumber);

	// Helper function for SaveBitmapDefinition: writes a bitmap properties record
	BOOL WriteBitmapPropertiesRecord(KernelBitmap* pBitmap, BaseCamelotFilter* pFilter, INT32 BmpRef);

protected:
	// Our list of bitmaps that we have currently exported from this document 
	ExportedBitmaps* pExportedBitmaps;

	// Our list of bitmaps that we have currently imported into this document 
	ImportedBitmaps* pImportedBitmaps;

private:	// Private link used during Importing to provide warnings to the user
	BaseCamelotFilter* pCamFilter;
	// Private variable which means that during Importing we only warn the user
	// once about problem bitmaps
	BOOL WarnedBefore;
};

#endif // INC_BMPCOMP
