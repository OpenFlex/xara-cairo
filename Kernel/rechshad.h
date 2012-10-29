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


#ifndef INC_RECHSHADOW
#define INC_RECHSHADOW


class CXaraFileRecord;

/***********************************************************************************************

>	class ShadowRecordHandler : public CamelotRecordHandler

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/12/97
	Purpose:	Handles the reading of all shadow records in the v2 file format
	SeeAlso:	-

***********************************************************************************************/

class ShadowRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(ShadowRecordHandler);

public:
	ShadowRecordHandler() : CamelotRecordHandler() {}
	~ShadowRecordHandler();

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pRecord,StringBase* pStr);
#endif

private:
	BOOL HandleShadowControllerRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleShadowRecord(CXaraFileRecord* pCXaraFileRecord);

	Matrix	m_HoldMatrix;
};

#endif //INC_RECHSHADOW
