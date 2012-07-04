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


#ifndef INC_RECHATTR
#define INC_RECHATTR

//#include "cxfrech.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class CXaraFileRecord;

/***********************************************************************************************

>	class LineAttrRecordHandler : public CamelotRecordHandler

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/96
	Purpose:	Handles the reading of all line attribute records in the v2 file format
	SeeAlso:	-

***********************************************************************************************/

class LineAttrRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(LineAttrRecordHandler);

public:
	LineAttrRecordHandler() : CamelotRecordHandler() {}
	~LineAttrRecordHandler() {}

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);
#endif

private:
	BOOL HandleLineColourRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleLineWidthRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleLineTransparencyRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleCapRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleJoinStyleRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleMitreLimitRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleWindingRuleRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleDashStyleRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleDefineDashRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleArrowHeadRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleArrowTailRecord(CXaraFileRecord* pCXaraFileRecord);
};

/***********************************************************************************************

>	class FillAttrRecordHandler : public CamelotRecordHandler

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/96
	Purpose:	Handles the reading of all fill attribute records in the v2 file format
	SeeAlso:	FlatFillAttribute

***********************************************************************************************/

class FillAttrRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(FillAttrRecordHandler);

public:
	FillAttrRecordHandler() : CamelotRecordHandler() {}
	~FillAttrRecordHandler() {}

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);
#endif

private:
	BOOL HandleFlatFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleLinearFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleMultiStageLinearFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleEllipticalFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleMultiStageCircularFillRecord(CXaraFileRecord * pCXaraFileRecord);
	BOOL HandleConicalFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleMultiStageConicalFillRecord(CXaraFileRecord * pCXaraFileRecord);
	BOOL HandleSquareFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleMultiStageSquareFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleThreeColFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleFourColFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleBitmapFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleFractalFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleNoiseFillRecord(CXaraFileRecord* pCXaraFileRecord);

	BOOL HandleFlatTransparentFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleLinearTransparentFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleEllipticalTransparentFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleConicalTransparentFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleSquareTransparentFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleThreeColTransparentFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleFourColTransparentFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleBitmapTransparentFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleFractalTransparentFillRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleNoiseTransparentFillRecord(CXaraFileRecord* pCXaraFileRecord);

	BOOL HandleFillRepeatRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleTransparentFillRepeatRecord(CXaraFileRecord* pCXaraFileRecord);

	BOOL HandleFillEffectRecord(CXaraFileRecord* pCXaraFileRecord);
};

/***********************************************************************************************

>	class GeneralAttrRecordHandler : public CamelotRecordHandler

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/7/96
	Purpose:	Handles the reading of all attribute records in the v2 file format
				that are not line or fill attributes
	SeeAlso:	-

***********************************************************************************************/

class GeneralAttrRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(GeneralAttrRecordHandler);

public:
	GeneralAttrRecordHandler() : CamelotRecordHandler() {}
	~GeneralAttrRecordHandler() {}

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);
#endif

private:
	BOOL HandleQualityRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleUserValueRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleWebAddressRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleWebAddressBoundingBoxRecord(CXaraFileRecord* pCXaraFileRecord);
};

#endif //INC_RECHATTR
