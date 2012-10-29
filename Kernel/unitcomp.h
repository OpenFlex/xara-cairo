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

#ifndef INC_UNITCOMP
#define INC_UNITCOMP


class BaseCamelotFilter;
class CXaraFileRecord;

/********************************************************************************************

>	class UnitListComponentClass : public DocComponentClass

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/07/96
	Purpose:	Provide a class that will add Unit List components to new documents.
	SeeAlso:	DocComponentClass

********************************************************************************************/

class UnitListComponentClass : public DocComponentClass
{
	CC_DECLARE_DYNAMIC(UnitListComponentClass)

public:
	static BOOL Init();

	BOOL AddComponent(BaseDocument *);
};

/********************************************************************************************

>	class UnitListComponent : public DocComponent

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/07/96
	Purpose:	Provide a component that allows	us to save out the units for this document
				using the serialisation facilities of the DocComponent base class.
	SeeAlso:	DocComponent

********************************************************************************************/

class UnitListComponent : public DocComponent
{
	CC_DECLARE_DYNAMIC(UnitListComponent)

public:
	UnitListComponent();
	//UnitListComponent(ColourList *);
	virtual ~UnitListComponent();

public:
	// Usual document component functions...

	// These are the Camelot Version 2 Web and Native file related functions
	virtual BOOL StartImport(BaseCamelotFilter *pFilter);
	virtual BOOL EndImport(BaseCamelotFilter *pFilter, BOOL Success);
	virtual BOOL StartExport(BaseCamelotFilter *pFilter);
	virtual BOOL EndExport(BaseCamelotFilter *pFilter, BOOL Success);

	BOOL ImportDefaultDisplayUnits(CXaraFileRecord* pCXaraFileRecord, Document * pDoc);
	BOOL ImportUserUnitDefinition(CXaraFileRecord* pCXaraFileRecord, Document * pDoc, INT32 Tag);

	// The public way of importing and exporting units and thier references for the new native/web filters
	Unit* GetReadUnitReference(INT32 UnitRef);
	INT32 GetWriteUnitReference(Unit* pUnit, BaseCamelotFilter *pFilter);
	INT32 GetWriteUnitReference(UnitType type, BaseCamelotFilter *pFilter);

private:
	UnitType GetUnitType(INT32 ExportUnitType);

	BOOL ExportUserUnits(BaseCamelotFilter *pFilter);
	INT32 ExportUnitDefinition(BaseCamelotFilter *pFilter, Unit* pUnit);
	BOOL ExportDefaultDisplayUnits(BaseCamelotFilter *pFilter);
	INT32 GetExportUnitType(UnitType type);

	// The current unit list and document we are supposed to be working with
	DocUnitList* pDocUnitList;
	Document*	pDocument; 

	// A hash table from unit pointers to thier exported references.
	CMapPtrToLong	   *pExpUserUnitMap;
	CMapLongToPtr	   *pImpUserUnitMap;

private:	// Private link used during Importing to provide warnings to the user
	BaseCamelotFilter *pCamFilter;
	BOOL WarnedBefore;
};

#endif  // INC_UNITCOMP


