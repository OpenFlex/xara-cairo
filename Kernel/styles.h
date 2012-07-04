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


// The document component for the document's unit list.

#ifndef INC_STYLES
#define INC_STYLES

class BaseCamelotFilter;
class CXaraFileRecord;


/********************************************************************************************

>	class Style : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/07/96

	Purpose:	

	SeeAlso:	Styles

********************************************************************************************/
class Style : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(Style)

public:
	virtual ~Style() = 0;
	virtual Style* CreateCopy(const StringBase& NewName) const = 0;
	virtual BOOL operator==(const Style& OtherStyle) const;

	const StringBase&	GetName() const;


protected:
	Style(const StringBase& Name);

	BOOL SetName(const StringBase& Name);

private:
	String_64		m_Name;
};


class StyleContainer;
class StyleContainerItem;
/**************************************************************************************

>	class StyleIterator

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/07/97

	Purpose:	Returns entries in a visible list

	See Also:	VisibleList::Begin(), End()

**************************************************************************************/
class StyleIterator
{
public:
	StyleIterator& operator ++();
	Style& operator*();
	BOOL operator!=(const StyleIterator& Other);

	StyleIterator(StyleContainer& Container, StyleContainerItem* const pPosition);

private:
	StyleContainerItem*	m_CurrentItem;
	StyleContainer&		m_Container;
};

class StylesExporter;
typedef INT32 XFileRef;
/********************************************************************************************

>	class Styles : public DocComponent

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/07/96

	Purpose:	This DocComponent is an abstract class for styles. I put it in 'cos 
				someone's bound to come along and want the functionality of the derived class
				WizOpStyleComponent

	SeeAlso:	StyleComponentClass

********************************************************************************************/
class Styles : public DocComponent
{
	CC_DECLARE_DYNAMIC(Styles)
public:
	virtual BOOL Init();

	virtual Style* AddStyle(const Style& NewStyle);
	virtual BOOL MergeStyles(Styles& OtherStyles);

// Examining the styles
	virtual StyleIterator Begin() const;
	virtual const StyleIterator& End() const;
	virtual Style* FindStyleFromName(const StringBase& StyleName) const;



//	Overridden methods called before and after a tree copy
	virtual BOOL StartComponentCopy();
	virtual BOOL EndComponentCopy(); 
	virtual void AbortComponentCopy();  

	virtual Style* CopyComponentData(const Style& NewStyle);

	virtual ~Styles();
protected:
	Styles();
	Styles(const Styles& OtherStyles);
	Styles& operator=(const Styles&);

	BOOL GenerateUniqueName(const StringBase& Prefix, StringBase* pResult);
	BOOL NameExists(const StringBase& Name) const;
	void SendStylesChangeMessage();
	
// Data access
	StyleContainer& GetContainer() const;
	Styles& GetStylesToAdd() const;
protected:
	StylesExporter*	m_pCurrentExporter;	// used when exporting
private:
	StyleContainer*	m_pStyleContainer;


	Styles*			m_pStylesToAdd;		// used when copying component
};



class WizOp;
class WizOpStyleRecordHandler;
/********************************************************************************************

>	class WizOpStyleComponentClass : public DocComponentClass

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/07/96

	Purpose:	Provide a class that will add document information components to new documents.

	SeeAlso:	DocComponentClass

********************************************************************************************/
class WizOpStyleComponentClass : public DocComponentClass
{
	CC_DECLARE_DYNAMIC(WizOpStyleComponentClass)

public:
	static BOOL Init();

	virtual BOOL AddComponent(BaseDocument*);
};


/********************************************************************************************

>	class WizOpStyle : public Style

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/07/96

	Purpose:	A WizOpStyle is a style solely for the purpose of naming WizOps

********************************************************************************************/
class WizOpStyle : public Style
{
	CC_DECLARE_MEMDUMP(WizOpStyle)
public:
	WizOpStyle(	const StringBase& Name, const StringBase& Question, 
				const WizOp& WizOpRef, const StringBase& Param);

	virtual Style* CreateCopy(const StringBase& NewName) const;
	virtual BOOL operator==(const Style& OtherStyle) const;

	const StringBase&	GetQuestion() const;
	BOOL				SetQuestion(const StringBase& NewQuestion);

	const WizOp&		GetWizOp() const;
	const StringBase&	GetParam() const;

protected:
	BOOL				SetParam(const StringBase& NewParam);

private:
	String_256			m_Question;
	const WizOp&		m_WizOp;
	String_256			m_Param;
};



/********************************************************************************************

>	class WizOpStyles : public Styles

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/07/96

	Purpose:	Provide a component that allows	us to save out the information for this document
				using the serialisation facilities of the DocComponent base class.
	SeeAlso:	DocComponent

********************************************************************************************/
class WizOpStyles : public Styles
{
	CC_DECLARE_DYNAMIC(WizOpStyles)

public:
	WizOpStyles()	{}
	// Usual document component functions...

// Import
	virtual BOOL StartImport(BaseCamelotFilter *pFilter);
	virtual BOOL EndImport(BaseCamelotFilter *pFilter, BOOL Success);

	WizOpStyle*	FindStyleFromRecordReference(XFileRef RecordRef) const;

	BOOL						SetRecordHandler(WizOpStyleRecordHandler& RecordHandler);
	WizOpStyleRecordHandler&	GetRecordHandler() const;

// Export
	virtual BOOL StartExport(BaseCamelotFilter *pFilter);
	virtual BOOL EndExport(BaseCamelotFilter *pFilter, BOOL Success);

	virtual XFileRef GetRecordRefForStyle(const WizOpStyle& Style);

private:
	WizOpStyleRecordHandler*	m_pImporter;
};


extern const INT32 XFILEREF_ERROR;

class RecordReferenceItem;
class List;

/********************************************************************************************

>	class RecordReferencingExporter : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/07/96

	Purpose:	

	SeeAlso:	Styles

********************************************************************************************/
class RecordReferencingExporter : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(RecordReferencingExporter)

protected:
	RecordReferencingExporter(BaseCamelotFilter& FilterToUse) : m_Filter(FilterToUse)	{}
	RecordReferencingExporter(const RecordReferencingExporter& Other);
	const RecordReferencingExporter& operator=(const RecordReferencingExporter& Other);

	virtual ~RecordReferencingExporter();

// Implementation
	virtual XFileRef WriteItem(const RecordReferenceItem& TentativeExportItem);

	virtual XFileRef WriteRecord(const RecordReferenceItem& ItemToExport) = 0;

// Support functions
	virtual BOOL AddExportedItem(RecordReferenceItem& NewItem);
	virtual const RecordReferenceItem* FindExportedItem(const RecordReferenceItem& ItemToFind);


// Data Access
	BaseCamelotFilter&	GetFilter()							{	return m_Filter;	}

private:
	BaseCamelotFilter&	m_Filter;
	List				m_ExportedItems;
};


/********************************************************************************************

>	class StylesExporter : public RecordReferencingExporter

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/07/96

	Purpose:	

	SeeAlso:	Styles

********************************************************************************************/
class StylesExporter : public RecordReferencingExporter
{
	CC_DECLARE_MEMDUMP(StylesExporter)

public:
	StylesExporter(Styles& StylesToExport, BaseCamelotFilter& FilterToUse);

// The entry point...
	virtual XFileRef WriteStyle(const WizOpStyle& StyleToWrite);

protected:
// Implemented pure
	virtual XFileRef WriteRecord(const RecordReferenceItem& ItemToExport);

private:
	Styles&				m_Styles;
};

/********************************************************************************************

>	class WizOpStyleRecordHandler : public CamelotRecordHandler

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/07/96

	Purpose:	Allows WizOpStyleComponent's to be read from the .xar/.web file formats.

********************************************************************************************/
class WizOpStyleRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(WizOpStyleRecordHandler);

public:
	WizOpStyleRecordHandler();
	virtual ~WizOpStyleRecordHandler();

	// overridden functions
	virtual UINT32*	GetTagList();
	virtual BOOL	Init(BaseCamelotFilter* pFilter);
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);
	virtual BOOL	EndImport();

	WizOpStyle* FindStyleFromRecordReference(XFileRef RecordRef) const;

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);
	virtual void GetTagText(UINT32 Tag,String_256& Str);
#endif

protected:
	WizOpStyleRecordHandler(const WizOpStyleRecordHandler& Other);
	WizOpStyleRecordHandler& operator=(const WizOpStyleRecordHandler& Other);

// Implementation
	WizOpStyle* AddStyle(	const StringBase& Name, const StringBase& Question, 
							const StringBase& WizOpName, const StringBase& Param);

	BOOL AddRecordReference(XFileRef RecordRef, const WizOpStyle& ImportedStyle);
// Data access
	WizOpStyles& GetTentativeStyles();


private:
//	WizOpStyles*	m_pStyleComponent;	// a pointer to the importing document's styles
	WizOpStyles*	m_pTentativeStyles;	// styles in & not in the importing document's styles
	List			m_ImportedItems;
};


/********************************************************************************************

>	class StylesMessage : public Msg

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/07/96

	Purpose:	Informs us that a Styles component has changed

	SeeAlso:	Styles

********************************************************************************************/
class StylesMessage : public Msg
{
	CC_DECLARE_DYNAMIC(StylesMessage);

public:
	StylesMessage(Styles& StylesChanging) :
		m_StylesChanging(StylesChanging)				{}

	Styles&	GetStylesChanging()							{	return m_StylesChanging;	}

private:
	Styles&	m_StylesChanging;
};

#endif  // INC_STYLES
