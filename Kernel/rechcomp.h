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


// The compression record handler for native and web files.

#ifndef INC_COMPRESSIONRECORDHANDLER
#define INC_COMPRESSIONRECORDHANDLER

// Header for the attribute record handling classes for the v2 file format

class CXaraFileRecord;

/********************************************************************************************

>	class CompressionRecordHandler : public CamelotRecordHandler

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/6/96
	Purpose:	Provide a compression record handler for the new native and web file formats.
				This asks the ZLib code within side the CCFile class to turn compression
				on or off.
	SeeAlso:	

********************************************************************************************/

class CompressionRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(CompressionRecordHandler);

public:
	CompressionRecordHandler() : CamelotRecordHandler() {}
	~CompressionRecordHandler() {}

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);
	virtual BOOL	HandleStreamedRecord(CXaraFile * pCXFile, UINT32 Tag,UINT32 Size,UINT32 RecordNumber);

	// Find out if the record is streamed or not
	virtual BOOL IsStreamed(UINT32 Tag);

	virtual void IncProgressBarCount(UINT32 n) {};

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);
#endif

protected:

};

#endif  // INC_COMPRESSIONRECORDHANDLER
