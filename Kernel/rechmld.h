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


#ifndef INC_RECHMLD
#define INC_RECHMLD

//#include "cxfrech.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class CXaraFileRecord;

/***********************************************************************************************

>	class MouldRecordHandler : public CamelotRecordHandler

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/7/96
	Purpose:	Handles the reading of all mould records in the v2 file format
	SeeAlso:	-

***********************************************************************************************/

class MouldRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(MouldRecordHandler);

public:
	MouldRecordHandler() : CamelotRecordHandler() {}
	~MouldRecordHandler() {}

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pRecord,StringBase* pStr);
#endif

private:
	BOOL HandleMouldRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleMouldGroupRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleMouldPathRecord(CXaraFileRecord* pCXaraFileRecord);
};

#endif //INC_RECHMLD
