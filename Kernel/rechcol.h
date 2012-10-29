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


// The colour record handler for native and web files.

#ifndef INC_COLOURRECORDHANDLER
#define INC_COLOURRECORDHANDLER

class ColourListComponent;

// Header for the attribute record handling classes for the v2 file format

class CXaraFileRecord;

/********************************************************************************************

>	class ColourRecordHandler : public CamelotRecordHandler

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/5/96
	Purpose:	Provide a colour record handler for the new native and web file formats.
				This asks the colour document component to import the colour definitions
				for us.
	SeeAlso:	ColourDocComponent;

********************************************************************************************/

class ColourRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(ColourRecordHandler);

public:
	ColourRecordHandler() : CamelotRecordHandler() { pColComponent = NULL; }
	~ColourRecordHandler() {}

	virtual BOOL BeginImport();

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);
	void DecodeColour(ColourModel ColModel, UINT32 Comp1, UINT32 Comp2, UINT32 Comp3, UINT32 Comp4,
					  BOOL Linked, StringBase* pStr);
	void DecodeComponent(UINT32 Comp, BOOL Linked, StringBase* pStr);
#endif

protected:
	// We will be using the colour list component class to handle the importing of
	// colours, so we must keep a pointer to it.
	ColourListComponent * pColComponent;	
};

#endif  // INC_COLOURRECORDHANDLER
