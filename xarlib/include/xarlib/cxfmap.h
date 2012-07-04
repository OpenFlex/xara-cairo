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


class CXaraFileRecordHandler;

/********************************************************************************************

>	class CXaraFileMapTagToHandler : public CCObject

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/8/96
	Base Class:	-
	Purpose:	This class implements a fast way of looking the handler that handles a given tag.

				It uses the MFC class CMapPtrToPtr to do the tricky bits.

	SeeAlso:	CMapPtrToPtr

********************************************************************************************/

class CXaraFileMapTagToHandler : public CCObject
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(CXaraFileMapTagToHandler);

public:
	CXaraFileMapTagToHandler();
	virtual ~CXaraFileMapTagToHandler();

	void Add(UINT32 Tag,CXaraFileRecordHandler* pHandler);

	CXaraFileRecordHandler* LookUp(UINT32 Tag);

private:
	CMapLongToPtr* pMap;
};
