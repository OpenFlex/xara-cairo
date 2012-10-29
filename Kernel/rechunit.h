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


// The units record handler for native and web files.

#ifndef INC_UNITSRECORDHANDLER
#define INC_UNITSRECORDHANDLER

class UnitListComponent;

// Header for the attribute record handling classes for the v2 file format

class CXaraFileRecord;

/********************************************************************************************

>	class UnitsRecordHandler : public CamelotRecordHandler

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/96
	Purpose:	Provide a units record handler for the new native and web file formats.
				This asks the units document component to import the unit definitions
				for us.
	SeeAlso:	UnitListDocComponent;

********************************************************************************************/

class UnitsRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(UnitsRecordHandler);

public:
	UnitsRecordHandler() : CamelotRecordHandler() {}
	~UnitsRecordHandler() {}

	virtual BOOL BeginImport();

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);
	void DescribeDefaultUnit(INT32 ExportUnitType, StringBase* pStr);
#endif

protected:
	// We will be using the units list component class to handle the importing of
	// units, so we must keep a pointer to it.
	UnitListComponent * pUnitsComponent;	
};

#endif  // INC_UNITSRECORDHANDLER
