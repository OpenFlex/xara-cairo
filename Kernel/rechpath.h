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


#ifndef INC_RECHPATH
#define INC_RECHPATH

//#include "cxfrech.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class CXaraFileRecord;
class NodePath;

/***********************************************************************************************

>	class PathRecordHandler : public CamelotRecordHandler

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/96
	Purpose:	Handles the reading of all fill attribute records in the v2 file format
	SeeAlso:	-

***********************************************************************************************/

class PathRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(PathRecordHandler);

public:
	PathRecordHandler() {}
	~PathRecordHandler() {}

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

//	virtual BOOL BeginImport();

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pRecord,StringBase* pStr);
#endif

private:
	BOOL HandlePathRecord(CXaraFileRecord* pCXaraFileRecord,BOOL Filled,BOOL Stroked);
	BOOL HandlePathRelativeRecord(CXaraFileRecord* pCXaraFileRecord,BOOL Filled,BOOL Stroked);
	BOOL HandlePathRefRecord(CXaraFileRecord* pCXaraFileRecord);

//	void SetLastInsertedPath(NodePath* pNodePath) { pLastInsertedPath  = pNodePath; }
//	NodePath* GetLastInsertedPath() { return pLastInsertedPath ; }

//	NodePath* pLastInsertedPath;
};

/***********************************************************************************************

>	class PathFlagsRecordHandler : public CamelotRecordHandler

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/5/99
	Purpose:	Handles the reading of the path flag record in the v2 file format
	SeeAlso:	-

***********************************************************************************************/

class PathFlagsRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(PathFlagsRecordHandler);

public:
	PathFlagsRecordHandler() {}
	~PathFlagsRecordHandler() {}

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pRecord,StringBase* pStr);
#endif
};

#endif //INC_RECHPATH
