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


// Declaration of ArtWorks EPS filter.

#ifndef INC_AW_EPS
#define INC_AW_EPS

//#include "epsfiltr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "saveeps.h"
//#include "epsstack.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "fixstr64.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "colmodel.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "nodemold.h"

// A structure to hold details of the last grad fill end colour read.
struct GradEndCol {
	String_64	ColName;
	PColourCMYK	Col;
	TintType	Tint;
	FIXEDPOINT	TintVal;
};

/********************************************************************************************

>	class ArtWorksEPSFilter : public EPSFilter

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	A filter that imports EPS files in ArtWorks EPS format.
	SeeAlso:	EPSFilter

********************************************************************************************/

class ArtWorksEPSFilter : public EPSFilter
{
	CC_DECLARE_DYNAMIC(ArtWorksEPSFilter);
	
public:
	ArtWorksEPSFilter();
	BOOL Init();
	BOOL PrepareToExport(CCLexFile*, Spread *pSpread);
	TCHAR* GetEPSCommand(EPSCommand Cmd);
	virtual BOOL NeedsPrintComponents ( void );

	virtual BitmapFilterSupport GetBitmapSupportLevel();

protected:
	virtual void LookUpToken();
	virtual BOOL ProcessToken();
	INT32 EPSHeaderIsOk(ADDR pFileHeader, UINT32 HeaderSize);

	// The array of keyword names
	static CommandMap ArtWorksCommands[];

	// Blend and blender processing functions
	BOOL ProcessBlend();
	BOOL ProcessBlender();
	BOOL StartBlend();
	BOOL StartBlender();
	BOOL EndBlend();
	BOOL EndBlender();

	// Mould object processing functions
	BOOL ProcessEnvelope();
	BOOL ProcessPerspective();
	BOOL StartMould(MouldSpace mSpace);
	BOOL EndMould();
	BOOL ProcessMould();
	BOOL ProcessMouldShape();
	BOOL ProcessMangledObjs();
	BOOL ConvertArtMould(NodeMould*);
	BOOL ConvertMouldStyles(Node* pNode);
	void DeleteAllMangled(Node* pNode);
	BOOL DeleteAllNoneMangled(Node* pNode);
	BOOL PromoteMangled(Node* pNode);
	BOOL HandleMouldedFill();

private:
	// Mould related locals
	DocRect		MouldRect;			// used for importing mould shapes
	INT32		LastFillType;		// holds the last read grad fill type (lin or cir)
	GradEndCol	LastStartColour;
	GradEndCol	LastEndColour;
};

// All the commands used by ArtWorks EPS files.
enum
{
	EPSC_aoa = EPSC_EOF + 1,
	EPSC_aafs,
	
	// Path related procedures
	EPSC_ar,
	EPSC_arr,
	EPSC_ae,
	EPSC_apl,
	EPSC_apc,
	EPSC_aof,
	
	// Text related procedures
	EPSC_asto,
	EPSC_aeto,
	EPSC_aco,
	EPSC_atc,
	EPSC_atph,
	EPSC_atof,
	
	// Blend related procedures
	EPSC_asbd,
	EPSC_aebd,
	EPSC_asbr,
	EPSC_aebr,
	
	// Mould related procedures
	EPSC_asev,
	EPSC_aeev,
	EPSC_aspr,
	EPSC_aepr,
	EPSC_amm,
	EPSC_aml,
	EPSC_amc,
	EPSC_amcp,
	EPSC_amep,
	
	// Group related procedures
	EPSC_anu,
	
	// Linear/radial fills
	EPSC_az,
	EPSC_ax,
	EPSC_axm,
	
	// Overprint related procedures
	EPSC_axop,
	
	// Others(!)
	EPSC_awr,
	EPSC_asc,
	EPSC_aec,
	EPSC_aca,
	EPSC_asah,
	EPSC_aeah,
	EPSC_asat,
	EPSC_aeat,
	
	// Procedures that define a text object
	EPSC_atp,
	EPSC_atf,
	EPSC_atxy,
	EPSC_atrk,
	EPSC_akrn,
	
	// Layer procedure
	EPSC_alyr,
	
	// Sprite procedure
	EPSC_ass,
	EPSC_aes	
};

/********************************************************************************************

>	class ArtWorksEPSRenderRegion : public EPSRenderRegion

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	A render region for exporting ArtWorks EPS format files.
	SeeAlso:	EPSRenderRegion

********************************************************************************************/

class ArtWorksEPSRenderRegion : public EPSRenderRegion
{
	CC_DECLARE_DYNAMIC(ArtWorksEPSRenderRegion)
	
public:
	ArtWorksEPSRenderRegion(DocRect ClipRect, Matrix ConvertMatrix, FIXED16 ViewScale);
	virtual BOOL StartRender();

	virtual void OutputFillColour();
	virtual void OutputStrokeColour();

protected:
	// This version handles grad fills.
	void GetValidPathAttributes();
	virtual BOOL WriteEPSBoundingBox ( void );
	virtual BOOL WriteEPSTrailerComments ( void );
};

#endif  // INC_AW_EPS


