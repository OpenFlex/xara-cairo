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

//
// Header for the print document component classes

#ifndef INC_PRINCOMP
#define INC_PRINCOMP


class EPSExportDC;
class PrintControl;
class CXaraFileRecord;
class CamelotRecordHandler;
class ColourPlate;

//--------------------------------------

/********************************************************************************************

>	class PrintComponentClass : public DocComponentClass

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/3/95
	Purpose:	Provide a class that will add print components to new documents.
	SeeAlso:	DocComponentClass

********************************************************************************************/

class PrintComponentClass : public DocComponentClass
{
	CC_DECLARE_DYNAMIC(PrintComponentClass)

public:
	static BOOL Init();

	BOOL AddComponent(BaseDocument *);
};

enum PCToken
{
	PCTOKEN_SECTIONNAME,
	PCTOKEN_WHOLESPREAD,
	PCTOKEN_SCALE,
	PCTOKEN_ORIENTATION,
	PCTOKEN_FITTYPE,
	PCTOKEN_TOPMARGIN,
	PCTOKEN_LEFTMARGIN,
	PCTOKEN_WIDTH,
	PCTOKEN_HEIGHT,
	PCTOKEN_ROWS,
	PCTOKEN_COLUMNS,
	PCTOKEN_GUTTER,
	PCTOKEN_LAYERS,
	PCTOKEN_PSLEVEL,
	PCTOKEN_PRINTMETHOD,
	PCTOKEN_BITMAPRESMETHOD,
	PCTOKEN_DOTSPERINCH,
	PCTOKEN_COLLATED,
	PCTOKEN_NUMCOPIES,
	PCTOKEN_PRINTTOFILE,
	PCTOKEN_OBJPRINTRANGE,
	PCTOKEN_DPSPRINTRANGE,
	PCTOKEN_ALLTEXTASSHAPES,

	PCTOKEN_UNKNOWN
};

#define PC_BUFFERSIZE 32

/********************************************************************************************

>	class PrintComponent : public DocComponent

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/3/95
	Purpose:	Provide a component that contains a ptr to the document's PrintControl object
	SeeAlso:	DocComponent

********************************************************************************************/

class PrintComponent : public DocComponent
{
	CC_DECLARE_DYNAMIC(PrintComponent)

public:
	PrintComponent();
	PrintComponent(PrintControl *);
	~PrintComponent();

	PrintControl* GetPrintControl() { return pPrCtrl; }

	// Usual document component functions...
	virtual BOOL WriteEPSComments(EPSFilter *);
	virtual ProcessEPSResult ProcessEPSComment(EPSFilter *, const char *);

	// Camelot Version 2 Web and Native file related functions
	// We only bother with EndExport, at which point we dump everything out
	virtual BOOL EndExport(BaseCamelotFilter *pFilter, BOOL Success);

	// Export record handlers, called from princomp.cpp (EndExport)
	BOOL ExportPrintSettings(BaseCamelotFilter *pFilter);
	BOOL ExportImagesetting(BaseCamelotFilter *pFilter);
	BOOL ExportColourPlate(BaseCamelotFilter *pFilter, ColourPlate *pPlate);

	// Import record handlers, called from rechprnt.cpp
	void ImportPrintSettings(CXaraFileRecord* Rec);
	void ImportImagesetting(CXaraFileRecord* Rec);
	void ImportColourPlate(CXaraFileRecord* Rec, CamelotRecordHandler *pHandler);


private:
	// EPS output functions
	BOOL OutputValue(UINT32 Token,INT32 Value);
	BOOL OutputValue(UINT32 Token,FIXED16 Value);

	// PCToken routines
	PCToken GetToken(const char* pComment);
	INT32	GetTokenValINT32(const char* pComment);
	FIXED16 GetTokenValFIXED16(const char* pComment);
	void 	ExtractTokenValStr(const char* pComment);

	PrintControl* 	pPrCtrl;
	EPSExportDC*	pExportDC;
	TCHAR			Buffer[PC_BUFFERSIZE];
};


#endif // INC_PRINCOMP
