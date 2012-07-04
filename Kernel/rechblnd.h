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


#ifndef INC_RECHBLND
#define INC_RECHBLND

//#include "cxfrech.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class CXaraFileRecord;
class NodeBlender;
class NodeBlend;
class NodeBlendPath;
/***********************************************************************************************

>	class BlendRecordHandler : public CamelotRecordHandler

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/6/96
	Purpose:	Handles the reading of all blend records in the v2 file format
	SeeAlso:	-

***********************************************************************************************/

class BlendRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(BlendRecordHandler);

public:
	BlendRecordHandler() : CamelotRecordHandler() { m_pLastInsertedNodeBlender = NULL; 
													m_pLastInsertedNodeBlend = NULL;
													m_pLastNodeBlendPath = NULL;
													m_bLoadedProfiles    = FALSE;}
	~BlendRecordHandler() {}

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pRecord,StringBase* pStr);
#endif

	static void SetLastInsertedNodeBlender(NodeBlender* pNodeBlender)	{ m_pLastInsertedNodeBlender = pNodeBlender; }
	static void SetLastInsertedNodeBlend(NodeBlend* pNodeBlend) { m_pLastInsertedNodeBlend = pNodeBlend; }
	static void SetLastInsertedNodeBlendPath(NodeBlendPath* pNodeBlendPath) { m_pLastNodeBlendPath = pNodeBlendPath; }

private:
	static NodeBlender* GetLastInsertedNodeBlender()					{ return m_pLastInsertedNodeBlender; }
	static NodeBlend* GetLastInsertedNodeBlend()						{ return m_pLastInsertedNodeBlend; }
	static NodeBlendPath* GetLastInsertedNodeBlendPath()               { return m_pLastNodeBlendPath; }


	BOOL HandleBlendRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleBlenderRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleBlenderCurvePropRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleBlenderCurveAnglesRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleBlendPathRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleBlendProfileRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleBlenderExtraRecord(CXaraFileRecord* pCXaraFileRecord);
	BOOL HandleBlendPathFlags(CXaraFileRecord* pCXaraFileRecord);
	
	static NodeBlender* m_pLastInsertedNodeBlender;
	static NodeBlend* m_pLastInsertedNodeBlend;
	static NodeBlendPath* m_pLastNodeBlendPath;

	// DY 12/7/2000 Due to problems loading v.3 files into the browser plug in I had to 
	// reverse the order in which blend data was saved and loaded.  We now need to cache
	// profile data as it comes in and give it to the next blend to be loaded
	static BOOL m_bLoadedProfiles;
	static CProfileBiasGain m_LastObjectProfile;
	static CProfileBiasGain m_LastAttrProfile;
	static CProfileBiasGain m_LastPositionProfile;
};

#endif //INC_RECHBLND
