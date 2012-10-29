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


// Camelot Native EPS format filter

#ifndef INC_CAMELEPS
#define INC_CAMELEPS

#include "aw_eps.h"
#include "saveeps.h"
#include "nodemold.h"

class KernelBitmap;
class OILBitmap;
class NodeRegularShape;
class CCAttrMap;
class ColourContext;

typedef enum
{
	PENDING_BITMAP_NONE,
	PENDING_BITMAP_FILL,
	PENDING_BITMAP_TRANSPFILL,
	PENDING_BITMAP_OBJECT,
	PENDING_BITMAP_POOLITEM,
	PENDING_BITMAP_OBJECT_FILL
} PendingBitmap;

typedef enum
{
	CAMEPS_FILL_LINEAR = 1,
	CAMEPS_FILL_ELLIPTICAL,
	CAMEPS_FILL_CIRCULAR,
	CAMEPS_FILL_CONICAL,
	CAMEPS_FILL_BITMAP,
	CAMEPS_FILL_FRACTAL,
	CAMEPS_FILL_NEWLINEAR,
	CAMEPS_FILL_NEWBITMAP
} CamelotEPSFillType;


// cso/ceo enumerated tags
enum
{
	EOTAG_FONTFLAGS = 1,
	EOTAG_BITMAPFLAGS,
	EOTAG_TEXTWRAPPED,
	EOTAG_FONTTYPE,
	EOTAG_GUIDELAYER,
	EOTAG_GUIDELINE,
	EOTAG_MOULDTHRESHOLD
};


// All the commands used by Camelot EPS files.
enum
{
	// Chromatic fill geometries
	EPSC_caz = EPSC_aes + 1,
	EPSC_cax,

	// Transparent fill geometries
	EPSC_cxt,

	// Chromatic fill effects
	EPSC_cxe,

	// Chromatic fill mappings
	EPSC_cxm,

	// Transparent fill mappings
	EPSC_cxmt,

	// Bitmap objects/bitmap fills
	EPSC_cbm,
	EPSC_csbm,
	EPSC_cebm,

	// Line/Fill colours
	EPSC_cx,
	EPSC_cX,
	EPSC_ck,
	EPSC_cK,

	// Stroke transparency
	EPSC_cst,

	// Arrow heads
	EPSC_csah,
	EPSC_ceah,

	// Dash Patterns
	EPSC_cdp,

	// Blends
	EPSC_csbd,
	EPSC_cebd,
	EPSC_csbr,
	EPSC_cebr,

	// Regular shapes
	EPSC_csrs,
	EPSC_crsp,
	EPSC_crstm,
	EPSC_crsp1,
	EPSC_crsp2,
	EPSC_cers,

	// Mould commands
	EPSC_csev,
	EPSC_ceev,
	EPSC_cspr,
	EPSC_cepr,
	EPSC_csmp,
	EPSC_cemp,
	EPSC_csso,
	EPSC_ceso,
	EPSC_csdo,
	EPSC_cedo,

 	// Text native commands
 	EPSC_ctf,
 	EPSC_ctb,
	EPSC_cti,
	EPSC_cts,
	EPSC_ctp,
	EPSC_ctls,

	EPSC_cso,
	EPSC_ceo,
	EPSC_cfft,	// font flags token
	EPSC_cftf,	// Type of font
	EPSC_cbot,	// Bitmap object token

	// Renderable bitmap tokens
	EPSC_cpal,	// Bitmap palette token

	// Guide layer & guidelines
	EPSC_glyr,
	EPSC_glne,

	EPSC_cmth,	// mould threshold token

	EPSC_cag,	// new grey level geometric fill operator

	// Another bitmap token
	EPSC_cbti,	// Bitmap transparency index

	// Sentinel - leave this one last
	EPSC_cameps_last
};


/********************************************************************************************

>	class CamelotEPSFilter : public ArtWorksEPSFilter

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	A filter that imports EPS files in Camelot EPS format.
	SeeAlso:	EPSFilter; ArtWorksEPSFilter

********************************************************************************************/

class CamelotEPSFilter : public ArtWorksEPSFilter
{
	CC_DECLARE_DYNAMIC(CamelotEPSFilter);
	
public:
	CamelotEPSFilter();
	BOOL Init();
	BOOL IsDefaultDocRequired(const TCHAR* pcszPathName);
	BOOL PrepareToExport(CCLexFile*, Spread* pSpread);
	TCHAR* GetEPSCommand(EPSCommand Cmd);
	BOOL ExportBitmap(KernelBitmap&);
	
	// This filter can include a Preview Bmp
	virtual BOOL CanIncludePreviewBmp();

protected:
	virtual void LookUpToken();
	virtual BOOL ProcessToken();
	INT32 EPSHeaderIsOk(ADDR pFileHeader, UINT32 HeaderSize);
	BOOL PrepareToImport();
	void CleanUpAfterImport(BOOL Successful);

	virtual BOOL GetExportOptions( );

	PendingBitmap		m_PendingBitmap;
	INT32				BitmapTransparencyIndex;
	virtual BOOL ReadBitmap();
	virtual void BitmapPoolAttach(KernelBitmap* pBitmap);
	KernelBitmap *pBitmap;

	NodeRegularShape *pRegularShape;
	BOOL RegularShapeIsFilled;
	BOOL RegularShapeIsStroked;

	struct _BitmapAttrs
	{
		DocCoord Coords[3];

		DocColour StartCol;
		DocColour EndCol;

		UINT32	 TranspType; 	// Only needed for transparent bitmap fills
		UINT32	 Transp; 		// Only needed for transparent bitmap fills
		UINT32	 EndTransp; 	// Only needed for transparent bitmap fills

	} BitmapAttrs;

	// Blend and blender processing functions
	BOOL ProcessBlend();
	BOOL ProcessBlender();
	BOOL StartBlend();
	BOOL StartBlender();
	BOOL EndBlend();
	BOOL EndBlender();

	// Regular shape processing functions
	BOOL ProcessRegularShape();
	BOOL ProcessRegularShapeParams();

	// Mould processing functions
	BOOL ProcessEnvelope();
	BOOL ProcessPerspective();
	BOOL StartMould(MouldSpace mSpace);
	BOOL EndMould();
	BOOL RemoveUnwantedAttributes(NodeMould* pNodeMould);
	void BuildSubtreeAttrMap(CCAttrMap *pAttribMap, Node* pNode);
	BOOL ProcessMould();
	BOOL ProcessMouldTokens();
	BOOL ProcessMouldShape();
	BOOL ProcessMouldSourceObjs();
	BOOL ProcessMouldDestinObjs();
	BOOL ProcessMouldThreshold();
	BOOL ReadSimplePath(Path* TempPath);

	BOOL ProcessFontFlags();
	BOOL ProcessBitmapFlags();
	BOOL ProcessFontType();
	BOOL FindEndOfTag();

	// Guide layer && guideline processing
	BOOL ProcessGuideLayer();
	BOOL ProcessGuideline();

	// The array of keyword names
	static CommandMap CamelotCommands[];
};

class EPSFontCache
{
public:
	EPSFontCache();

public:
	BOOL Valid;
	BOOL Complex;
	WORD Typeface;
	BOOL Bold;
	BOOL Italic;
	MILLIPOINT Size;
	FIXED16 a, b, c, d;
};

/********************************************************************************************

>	class CamelotEPSRenderRegion : public ArtWorksEPSRenderRegion

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	A render region for exporting files in the native EPS format.
	SeeAlso:	EPSRenderRegion; ArtWorksEPSRenderRegion

********************************************************************************************/

class CamelotEPSRenderRegion : public ArtWorksEPSRenderRegion
{
	CC_DECLARE_DYNAMIC(CamelotEPSRenderRegion)
	
public:
	CamelotEPSRenderRegion(DocRect ClipRect, Matrix ConvertMatrix, FIXED16 ViewScale);

	virtual ~CamelotEPSRenderRegion();

	// This version handles grad fills.
	void GetValidPathAttributes();
	void GetRenderRegionCaps(RRCaps* pCaps);

	BOOL StartRender();
	BOOL StopRender();

	void DrawPathToOutputDevice(Path *DrawPath, PathShape shapePath=PATHSHAPE_PATH);
	BOOL DrawTransformedBitmap(NodeBitmap *pNodeBitmap);

	// Function to draw a bitmap into the render region using a mask
	virtual SlowJobResult DrawMaskedBitmap(const DocRect &Rect, KernelBitmap* pBitmap, 
								  		   MaskedRenderRegion* pMask, ProgressDisplay *Progress);

	virtual BOOL RenderChar(WCHAR ch, Matrix* pMatrix);

	// Must it export the print componets?
	virtual BOOL NeedsPrintComponents ( void );

	// Commit suicide - used instead of if ( IS_A (...) )
	virtual void ConditionalSuicide ( void );

	// write out a return character (\r). Used in Wrap-around text, etc...
	virtual BOOL WriteNewLine ( void );

	// these two functions are used to call the base EPS Output commands.
	virtual void OutputStrokeColour ();
	virtual void OutputFillColour ();

	virtual BOOL DrawParallelogramBitmap(DocCoord *Coords, OILBitmap *pBitmap, EFFECTTYPE Effect = EFFECT_RGB,
				 DocColour *StartCol = NULL, DocColour *EndCol = NULL);

protected:
	virtual BOOL WriteEPSBoundingBox ( void );
	virtual BOOL WriteProlog(KernelDC*);
	virtual BOOL WriteSetup(KernelDC*);
	virtual BOOL WriteEPSTrailerComments ( void );

	BOOL DrawClippedBitmap(Path *DrawPath);

	BOOL SelectNewFont(WORD Typeface, BOOL Bold, BOOL Italic, MILLIPOINT Size);
	BOOL SelectNewFont(WORD Typeface, BOOL Bold, BOOL Italic, FIXED16 *abcd);

	// (ChrisG - 30/01/01) Changed to virtual, so that the pre-1.5 export can use CMYK colours, instead
	//	of RGB ones (as used by the Xara X EPS export) .
	virtual BOOL OutputGradFillColours(DocColour* StartCol, DocColour* EndCol, ColourContext* pContext=NULL);
	BOOL GetCurrFillEffect(UINT32& EffectType);

	// Used for rendering text via PostScript fonts
	EPSFontCache FontInfo;

	// Colour separation - bitmap support stuff
	void ColourSeparateScanline24(BYTE *DestBuffer, BYTE *SrcBuffer, INT32 PixelWidth);

	// Separation look-up tables for bitmap output (or NULL if not separating) -  This references
	// a set of 5 256-byte lookup tables (C, M, Y, UCR, BlackGen), or is NULL if not separating
	BYTE *SepTables;
};



#endif  // INC_CAMELEPS


