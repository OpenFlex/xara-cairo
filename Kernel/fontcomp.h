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

/********************************************************************************************

>	fontcomp.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/08/96
	Purpose:	The document font component

********************************************************************************************/

#ifndef INC_FONT_COMPONENT
#define INC_FONT_COMPONENT

/********************************************************************************************

>	class FontComponentClass : public DocComponentClass

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/08/96
	Base Class:	DocComponentClass
	Purpose:	A class that will add Font Components to new documents
	SeeAlso:	class DocComponentClass, class FontComponent

********************************************************************************************/

class FontComponentClass : public DocComponentClass
{
	CC_DECLARE_DYNAMIC(FontComponentClass)

public:
	static BOOL Init();

	BOOL AddComponent(BaseDocument *pDoc);
};

/********************************************************************************************

>	FontComponentListItem : public ListItem

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/08/96
	Base Class:	public ListItem
	Purpose:	List item object used by class FontComponentList
	SeeAlso:	class ListItem, class FontComponentList

********************************************************************************************/

class FontComponentListItem : public ListItem
{
	CC_DECLARE_DYNAMIC(FontComponentListItem);

	friend class FontComponentList;
	friend class FontComponent;
	
public:
	FontComponentListItem();
	~FontComponentListItem();
private:
	// mIsBold			- echo's IsBold flag in typeface attributes
	// mIsItalic		- echo's IsItalic flag in typeface attributes
	// mRecentlyCreated	- set to TRUE by the constructor, FALSE before any import and export.
	//					  hence we can find the new items created during an import or export
	//					  should we have to remove them (the import/export operated failed.)
	// mFontHandle		- echo's the FontHandle in the typeface attribute
	// mRecordNumber	- Record number of font definition record while loading or saving.
	// mFontName		- Full font name (currently set to "" since we've can't find it)
	// mFaceName		- Face name of the font, i.e. "Arial" or "Times New Roman"
	// mFontClass		- Font class of font - from font manager
	// mCCPanose		- Panose number of font.
						 
	BOOL mIsBold;
	BOOL mIsItalic;
	BOOL mRecentlyCreated;
	WORD mFontHandle;
	INT32 mRecordNumber;
	String_64 mFullFontName;
	String_64 mTypeFaceName;
	FontClass mFontClass;
	CCPanose mPanoseNumber;
};

/********************************************************************************************

>	class FontComponentList : public List

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/08/06
	Base Class:	public List
	Purpose:	List header object for the list of font information held by FontComponent objects
	SeeAlso:	class FontComponentListItem, class FontComponent

********************************************************************************************/

class FontComponentList : public List
{
	CC_DECLARE_DYNAMIC(FontComponentList);

// constructor, destructor
public:
	FontComponentList();
	~FontComponentList();

// New file format export related functions
public:
	BOOL ExportStart();
	BOOL ExportEnd(BOOL Success);
	FontComponentListItem *ExportFind(WORD FontHandle, BOOL IsBold, BOOL IsItalic);
private:
	FontComponentListItem *ExportFindAux(FontComponentListItem *pItem, WORD FontHandle, BOOL IsBold, BOOL IsItalic);
	BOOL ExportInitialised;

// New file format import related functions
public:
	BOOL ImportStart();
	BOOL ImportEnd(BOOL Success);
	FontComponentListItem *ImportFind(INT32 RecordNumber);
private:
	FontComponentListItem *ImportFindAux(FontComponentListItem *pItem, INT32 RecordNumber);
	BOOL ImportInitialised;
};

/********************************************************************************************

>	class FontComponent : public DocComponent

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	06/08/96
	Base Class:	public DocComponent
	Purpose:	Provides a compoent to the document that handles the saving and loading of
				font definitions to and from the new file format.
	SeeAlso:	class FontComponentList, class DocComponent

********************************************************************************************/

class FontComponent : public DocComponent
{
	CC_DECLARE_DYNAMIC(FontComponent);

// constructor, destructor
public:
	FontComponent();
	~FontComponent();

// new file format export related functions
public:
	BOOL StartExport(BaseCamelotFilter *pFilter);
	BOOL EndExport(BaseCamelotFilter *pFilter, BOOL Success);
	INT32 WriteFontDefinition(BaseCamelotFilter *pFilter, WORD FontHandle, BOOL IsBold, BOOL IsItalic);
private:
	INT32 WriteFontRecord(BaseCamelotFilter *pFilter, FontComponentListItem *pItem);
	INT32 WriteTrueTypeRecord(BaseCamelotFilter *pFilter, FontComponentListItem *pItem);
	INT32 WriteATMRecord(BaseCamelotFilter *pFilter, FontComponentListItem *pItem);
	INT32 WriteUnknownRecord(BaseCamelotFilter *pFilter, FontComponentListItem *pItem);
	BOOL ExportInitialised;

// new file format import related functions
public:
	BOOL StartImport(BaseCamelotFilter *pFilter);
	BOOL EndImport(BaseCamelotFilter *pFilter, BOOL Success);
	BOOL ReadFontDefinition(CXaraFileRecord *pRec);
	BOOL GetFontInformation(INT32 RecordNumber, WORD *pFontHandle, BOOL *pIsBold, BOOL *pIsItalic);
private:
	BOOL ReadFontTrueType(CXaraFileRecord *pRec);
	BOOL ReadFontATM(CXaraFileRecord *pRec);
	BOOL ReadFontUnknown(CXaraFileRecord *pRec);
	BOOL ImportInitialised;

// new file format export and import related members
public:
	FontComponentList *pFontList;
	FontManager *pFontManager;
private:
	BOOL ExportCacheFont(FontComponentListItem *pItem);
	
	BOOL ExportCacheFullFontName(FontComponentListItem *pItem);
	BOOL ExportCacheTypeFaceName(FontComponentListItem *pItem);
	BOOL ExportCacheFontClass(FontComponentListItem *pItem);
	BOOL ExportCacheCCPanose(FontComponentListItem *pItem);

	OUTLINETEXTMETRIC *ExportGetOutlineTextMetricStage1(FontComponentListItem *pItem);
	OUTLINETEXTMETRIC *ExportGetOutlineTextMetricStage2(FontComponentListItem *pItem);
		
	BOOL ImportCacheFont(FontComponentListItem *pItem);

private:	// Private link used during Importing to provide warnings to the user
	BaseCamelotFilter *pCamFilter;
	// Private variable which means that during Importing we only warn the user
	// once about problem fonts
	BOOL WarnedBefore;
};

#endif	// INC_FONT_COMPONENT
