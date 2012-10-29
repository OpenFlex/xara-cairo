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

// cmx import filter

#ifndef CMXIFLTR_H
#define CMXIFLTR_H

//#include "cmxres.h"

#include "cmxistut.h"

class CMXImportFilterDataSet;
class CMXImportColourList;
class CMXImportRImage;
class CMXImportBitmap;
class Progress;
class SelOperation;

/********************************************************************************************

>	class CMXImportFilter : public VectorFilter

	Author:		Ben_Summers (Xara Group Ltd) <camelotdev@xara.com>
	Created:	05/08/96
	Purpose:	Import filter for CMX format (both 16 and 32 bit)

********************************************************************************************/

class CMXImportFilter : public VectorFilter
{
	CC_DECLARE_DYNAMIC(CMXImportFilter);
	friend class CMXImportRImage;
	friend class CMXImportBitmap;

public:
	CMXImportFilter();
	BOOL Init();
	
	INT32 HowCompatible(PathName& Filename, 
					ADDR  HeaderStart, 
					UINT32 HeaderSize,
					UINT32 FileSize);

	BOOL DoImport(SelOperation*, CCLexFile*, Document*, 
				BOOL AutoChosen = FALSE, ImportPosition *Pos = NULL,
				KernelBitmap** ppImportedBitmap = NULL,
				DocCoord* pPosTranslate = NULL, String_256* = NULL);

	BOOL DoExport(Operation*, CCLexFile*, PathName*, Document*, BOOL) {return FALSE;};

	virtual BOOL IsDefaultDocRequired(const TCHAR* pcszPathName) {return TRUE;};

	// Function used by the gallery thumb nail code to check the file is the native/web format
	// and then get to the preview bitmap record and leave the file pointer sitting at the bitmap image
	static BOOL SkipToPreviewBitmap(CCLexFile * pFile);

protected:
	// data reading things
	BOOL ReadData(void *Out, char *Instructions);
	BOOL ReadPointList(Path **ppPath);
	CMXImportColourList *ReadColourList(void);
	BOOL LocateRootLevelRIFFSection(DWORD Section);
	void Seek(INT32 to) {pFile->seekIn(to + StartPosition);};
	INT32 Tell(void) {return pFile->tellIn() - StartPosition;};
	BOOL GotoSectionFromIndex(INT32 MasterIndexEntry, DWORD PredictedRIFFType, BOOL NonExistanceIsFormatError, BOOL *Found = NULL, INT32 *Size = NULL);

	// do stuff functions
	BOOL Stage1_ReadHeader(Spread *pSpread);
	BOOL Stage2_ReadMasterIndex(void);
	BOOL Stage3_ConvertDescriptionSections(void);
	BOOL Stage4_ConvertPage(void);
	BOOL Stage5_PlaceObjectsInTree(Spread *pSpread, SelOperation *pOp, ImportPosition *pPos);
	BOOL ProcessCommand(INT32 *ProgressThingy = NULL);

	// command handling functions -- call new ones Process_<name of instruction in CMX spec>
	BOOL Process_BeginPage(void);
	BOOL Process_EndPage(void);
	BOOL Process_BeginLayer(void);
	BOOL Process_EndLayer(void);
	BOOL Process_BeginGroup(void);
	BOOL Process_EndGroup(void);
	BOOL Process_EndSection(void);
	BOOL Process_PolyCurve(void);
	BOOL Process_PolyCurveContainer(cmxiPolyCurve &pc);
	BOOL Process_Rectangle ( void );					// Graeme (1-2-00)
	BOOL Process_AddGlobalTransform(void);
	BOOL Process_SetGlobalTransform(void);
	BOOL Process_RestoreLastGlobalTransform(void);
	BOOL Process_DrawImage(void);
	BOOL Process_DrawImage_Cropped(cmxiDrawImage &db);
	BOOL Process_AddClippingRegion(void);
	BOOL Process_RemoveLastClippingRegion(void);
	BOOL Process_ClearClipping(void);
	BOOL Process_BeginTextStream(void);
	BOOL Process_TextFrame(void);
	BOOL Process_Characters(void);
	BOOL Process_CharInfo(void);
	BOOL Process_BeginParagraph(void);
	BOOL Process_EndParagraph(void);
	BOOL Process_EndTextStream(void);


	// object processing things
	BOOL TransformNode(Node *pNode);
	BOOL SetAttributesForNode(Node *pNode, void *pAttr, BOOL DeleteStuff = TRUE);
	BOOL ClipNode(Node **pNode);
	BOOL ApplyAttributesToNode(Node *pNode);

	// attribute stuff
	BOOL SetNoFill(Node *pNode);
	BOOL SetNoStroke(Node *pNode);
	BOOL SetAttributesFountain(Node *pNode, cmxiFillSpec *Fill);
	BOOL SetAttributesLinearGrad(Node *pNode, cmxiFillSpec *GFill, DocRect &BBox, DocColour *StartColour, DocColour *EndColour);
	BOOL SetAttributesConicalGrad(Node *pNode, cmxiFillSpec *GFill, DocRect &BBox, DocColour *StartColour, DocColour *EndColour);
	BOOL SetAttributesRadialGrad(Node *pNode, cmxiFillSpec *GFill, DocRect &BBox, DocColour *StartColour, DocColour *EndColour, BOOL IsSquare = FALSE);
	BOOL SetAttributesBitmapFill(Node *pNode, INT32 VectorReference, cmxiTiling *Tile);
	BOOL SetAttributesTwoColourBitmapFill(Node *pNode, cmxiFillSpec *Fill);
	BOOL GetCorelBBox(NodeRenderableBounded *pNode, DocRect *BBox);
	BOOL GetTilingPoints(DocRect *BBox, cmxiTiling *Tile, DocCoord *StartPoint, DocCoord *EndPoint, DocCoord *EndPoint2);
	void SetNonTextAttributeIgnore();
	void SetNonTextAttributeNotIgnore();
	void SetTextAttributeIgnore();
	void SetTextAttributeNotIgnore();


	// misc stuff
	void CleanUpAfterImport(void);

	// approximation things
	void AttributeApproximated(void);
	void ClippingApproximated(void);
	void ObjectApproximated(void);

	// referency type stuff
	BOOL ConvertColours(void);
	DocColour *GetColourFromReference(INT32 Ref);
	BOOL AddColoursToDocument(void);
	BOOL ConvertPens(void);
	BOOL ConvertOutlines(void);
	BOOL ConvertLineStyles(void);
	BOOL ConvertDotDashes(void);
	BOOL ConvertArrowShapes(void);
	BOOL ConvertArrowheads(void);
	BOOL ReadEmbeddedFileIndex(void);
	BOOL ReadProcedureIndex(void);
	BOOL ReadBitmapIndex(void);
	BOOL ConvertFonts(void);
	BOOL ReadFontIndex(void);

	// transform and clipping things
public:
	Matrix *GetBaseMatrix(void);
	Matrix *GetCurrentMatrix(void);
	void SetMatrix(Matrix *pNewMatrix);
	void SetClippingPath(Path *pClipper = NULL);

private:
	CCLexFile *pFile;
	BOOL Is32Bit;
	BOOL CorelDraw7;
	INT32 StartPosition;		// the offset of the start of the CMX file

	// all the data we're using
	CMXImportFilterDataSet *Data;

#ifdef _DEBUG
public:
	static void FormatErrorBreakingFunction(void);
#endif // _DEBUG
};

// use to mark an error in the CMX file we're importing
#ifdef _DEBUG
#define CMXFORMATERROR(ret)		{Error::SetError(IDT_CMXFILTER_CMXERROR, 0); \
								CMXImportFilter::FormatErrorBreakingFunction(); return ret;}
#else
#define CMXFORMATERROR(ret)		{Error::SetError(IDT_CMXFILTER_CMXERROR, 0); return ret;}
#endif



#endif // CMXIFLTR_H
