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

// Header for the attribute record handling classes for the v2 file format

#ifndef INC_RECHDOC
#define INC_RECHDOC


class CXaraFileRecord;
class Document;
class Chapter;
class Spread;
class Layer;

/***********************************************************************************************

>	class DocumentRecordHandler : public CamelotRecordHandler

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/6/96
	Purpose:	Handles the reading of all document records in the v2 file format
	SeeAlso:	-

***********************************************************************************************/

class DocumentRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(DocumentRecordHandler);

public:
	DocumentRecordHandler();
	~DocumentRecordHandler() {}

	virtual BOOL BeginImport();

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);
#endif

private:
	void InitVars();

	BOOL HandleSpreadRecord(CXaraFileRecord*);
	BOOL HandleSpreadInformationRecord(CXaraFileRecord*);
	BOOL HandleDocumentRecord(CXaraFileRecord*);
	BOOL HandleChapterRecord(CXaraFileRecord*);
	BOOL HandleLayerRecord(CXaraFileRecord*);
	BOOL HandleLayerDetailsRecord(CXaraFileRecord*);
	BOOL HandleGuidelineRecord(CXaraFileRecord*);
	BOOL HandleSetSentinelRecord(CXaraFileRecord*);
	BOOL HandleSetPropertyRecord(CXaraFileRecord*);
	BOOL HandleBarPropertyRecord(CXaraFileRecord*);
	BOOL HandleCurrentAttrsRecord(CXaraFileRecord*);
	BOOL HandleDuplicationOffsetRecord(CXaraFileRecord*);

	Layer* FindThisLayer(UINT32 n);

	// These are spread related rather than document or view related
	BOOL HandleGridAndRulerSettingsRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleGridAndRulerOriginRecord(CXaraFileRecord* pCXaraFileRecord);

	BOOL HandleSpreadScalingRecord(CXaraFileRecord* pCXaraFileRecord, INT32 Tag);

	BOOL HandleSpreadAnimPropertiesRecord(CXaraFileRecord* pRec);
	BOOL HandleFramePropertiesRecord(CXaraFileRecord* pRec);
};

#endif //INC_RECHDOC
