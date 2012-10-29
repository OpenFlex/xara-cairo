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

// Header file for Camelots Print Marks Doc component classes

/*
*/

#ifndef INC_DOCPRINTMARKS
#define INC_DOCPRINTMARKS


class BaseCamelotFilter;
class CXaraFileRecord;
class CamelotRecordHandler;
class PrintMarkItem;


/********************************************************************************************

>	class DocPrintMark : public ListItem

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/07/96
	Purpose:	A document print mark item. This item references a cached print mark held
				by the print mark manager
	SeeAlso:	PrintMarksMan, ListItem

********************************************************************************************/

class DocPrintMark : public ListItem
{
	CC_DECLARE_DYNCREATE(DocPrintMark);
	
	public:
		 DocPrintMark();
		 DocPrintMark(UINT32 hndle);
		~DocPrintMark();

		inline UINT32 GetHandle() const { return Handle; }

	private:
		UINT32	Handle;		// That is all!
};


/********************************************************************************************

>	class DocPrintMarkList : public List

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/07/96
	Purpose:	Provide a class that will add Print mark components to new documents.
	SeeAlso:	DocComponentClass

********************************************************************************************/

class DocPrintMarkList : public List
{
	CC_DECLARE_DYNAMIC(DocPrintMarkList)
	
	public:
		 DocPrintMarkList();
		~DocPrintMarkList();

		BOOL AddMark(UINT32 handle);
		void RemoveMark(UINT32 handle);
		void RemoveAllMarks();
		BOOL IsVirgin() const { return Virgin; }

		inline DocPrintMark* GetFirstMark() const;
		inline DocPrintMark* GetNextMark(DocPrintMark* pItem) const;

		DocPrintMark* FindMark(UINT32 SearchHandle) const;

	private:
		BOOL Virgin;
};


/********************************************************************************************
>	inline DocPrintMark* DocPrintMarkList::GetFirstMark() const
	inline DocPrintMark* DocPrintMarkList::GetNextMark(DocPrintMark* pItem) const
	Purpose - Quick inline mark access functions.
********************************************************************************************/

inline DocPrintMark* DocPrintMarkList::GetFirstMark() const
{
	return ((DocPrintMark*)GetHead());
}
		
inline DocPrintMark* DocPrintMarkList::GetNextMark(DocPrintMark* pItem) const
{
	return ((DocPrintMark*)GetNext(pItem));
}



/********************************************************************************************

>	class PrintMarkComponentClass : public DocComponentClass

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/07/96
	Purpose:	The class that gets a print mark doc component going on start up
				We need to register our class as a document component and this is where
				we do it all.
	SeeAlso:	DocComponentClass

********************************************************************************************/

class PrintMarkComponentClass : public DocComponentClass
{
	CC_DECLARE_DYNAMIC(PrintMarkComponentClass)

	public:
		static BOOL Init();

		BOOL AddComponent(BaseDocument *);
};



/********************************************************************************************

>	class PrintMarksComponent : public DocComponent

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/07/96
	Purpose:	An actual print mark document component. This component contains a list of
				handles which refer to print marks cached by the print marks manager. On
				saving, the mark handles will be resolved into physical marks which will be
				exported and subsequently imported and registered.
	SeeAlso:	DocComponent

********************************************************************************************/

class PrintMarksComponent : public DocComponent
{
	CC_DECLARE_DYNAMIC(PrintMarksComponent)

	public:
		PrintMarksComponent();
		virtual ~PrintMarksComponent();

		BOOL AddMark(UINT32 handle);
		void RemoveMark(UINT32 handle);
		void RemoveAllMarks();
		BOOL IsVirgin() const;
		
			   DocPrintMark* FindMark(UINT32 SearchHandle) const;
		inline DocPrintMark* GetFirstMark() const;
		inline DocPrintMark* GetNextMark(DocPrintMark* pItem) const;

	public:			// External V2 native file import/export handlers
		virtual BOOL StartImport(BaseCamelotFilter *pFilter);
		virtual BOOL EndImport(BaseCamelotFilter *pFilter, BOOL Success);
		virtual BOOL StartExport(BaseCamelotFilter *pFilter);
		virtual BOOL EndExport(BaseCamelotFilter *pFilter, BOOL Success);

		void ImportDefaultPrintMark(CXaraFileRecord* Rec);
		void StartImportCustomPrintMark(CamelotRecordHandler *pHandler, CXaraFileRecord* Rec);
		void EndImportCustomPrintMark(CamelotRecordHandler *pHandler);

	private:
		Node *CustomPreviousContext;
		Node *CustomCurrentContext;
		PrintMarkItem *pNewMark;

	private:		// Internal native file handlers
		BOOL ExportPrintMark(BaseCamelotFilter *pFilter, PrintMarkItem *pMarkItem);

	private:
		DocPrintMarkList DocMarks;
};


/********************************************************************************************
>	inline DocPrintMark* PrintMarksComponent::GetFirstMark() const
	inline DocPrintMark* PrintMarksComponent::GetNextMark(DocPrintMark* pItem) const
	Purpose - Quick inline mark access functions.
********************************************************************************************/

inline DocPrintMark* PrintMarksComponent::GetFirstMark() const
{
	return DocMarks.GetFirstMark();
}

inline DocPrintMark* PrintMarksComponent::GetNextMark(DocPrintMark* pItem) const
{
	return DocMarks.GetNextMark(pItem);
}

#endif
