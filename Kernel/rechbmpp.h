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


#ifndef INC_RECHBMPP
#define INC_RECHBMPP




/***********************************************************************************************

>	class BitmapPropertiesRecordHandler : public CamelotRecordHandler

	Author:		Andy_Hills (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/10/00
	Purpose:	Handles the reading of bitmap properties records
	SeeAlso:	-

***********************************************************************************************/

class BitmapPropertiesRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(BitmapPropertiesRecordHandler);

public:
	BitmapPropertiesRecordHandler() : CamelotRecordHandler() {}
	~BitmapPropertiesRecordHandler() {}

	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);
	virtual BOOL	IsStreamed(UINT32 Tag);
	virtual BOOL	HandleStreamedRecord(CXaraFile* pCXFile, UINT32 Tag, UINT32 Size, UINT32 RecordNumber);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pRecord, StringBase* pStr);
#endif

};

#endif //INC_RECHBMPP
