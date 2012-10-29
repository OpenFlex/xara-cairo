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

// Corel Palette file filter

#ifndef INC_COPLFILR
#define INC_COPLFILR

#include "colcomp.h"
#include "impcol.h"
#include "vector3d.h"

class String_64;
class SGDisplayLibColGroup;


// Palette file colour name prefixes. These are stored in the gallery as 
// a prefix ID and a suffix string - for thousands of entries this saves
// heaps of memory.
typedef enum
{
	PalettePrefix_None = 0,
	PalettePrefix_Pantone,
	PalettePrefix_PantoneSpot,
	PalettePrefix_Focoltone,
	PalettePrefix_Trumatch,
	PalettePrefix_RGB,
} PalettePrefix;


/********************************************************************************************
>	class PaletteFilter : public Filter

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/4/96
	Purpose:	Base class for all palette filters
********************************************************************************************/

class PaletteFilter : public Filter
{
	CC_DECLARE_DYNAMIC(PaletteFilter);

public:
	PaletteFilter();
	~PaletteFilter();
	
// Standard filter overrides
public:
	virtual BOOL IsDefaultDocRequired(const TCHAR* pcszPathName);

	virtual BOOL DoImport(SelOperation*, CCLexFile*, Document*, BOOL AutoChosen = FALSE,
							ImportPosition *Pos = NULL,
							KernelBitmap** ppImportedBitmap = NULL,
							DocCoord* pPosTranslate = NULL, String_256* = NULL);
	BOOL DoExport(Operation*, CCLexFile*, PathName*, Document*, BOOL);

	inline static double ClampZeroToOne(const double input) { return (input < 0 ? 0 : (input > 1 ? 1 : input)); }

// Lab to CIE helpers from Mike
public:
	static void ConvertLABToRGB(const Vector3D& icol, Vector3D* ocol);
protected:
	static void ConvertCIEtoXYZ(const Vector3D& icol, Vector3D& ocol);
	static void ConvertLABtoXYZ(const Vector3D& white, const Vector3D& icol, Vector3D& ocol);
	static void ConvertXYZToRGB(const Vector3D& icol, Vector3D& ocol);

// Processing functions
protected:
	virtual BOOL PreImport() = 0;
	virtual BOOL ImportPalette() = 0;
	virtual BOOL PostImport() = 0;

	BOOL StartPercentage(INT32 UpTo = -1);
	BOOL SetPercentage(INT32 GotTo = -1);
	BOOL ProcessRGBColour(double Red, double Green, double Blue, const StringBase* pColName = NULL);
	BOOL ProcessCMYKColour(double Cyan, double Magenta, double Yellow, double Key, const StringBase* pColName = NULL);
	BOOL ProcessHSVColour(double Hue, double Sat, double Value, const StringBase* pColName = NULL);
	BOOL ProcessLabColour(double Luminance, double A, double B, const StringBase* pColName = NULL);
	BOOL ProcessGreyColour(double Intensity, const StringBase* pColName = NULL);
	BOOL NameRGBColour(ColourRGBT* pColour, StringBase* pName);
	BOOL NameCMYKColour(ColourCMYK* pColour, StringBase* pName);
	BOOL NameHSVColour(ColourHSVT* pColour, StringBase* pName);
	BOOL NameGreyColour(ColourGreyT* pColour, StringBase* pName);
	BOOL UsePercentageColour();

protected:
	BOOL AddColourToGallery(PalettePrefix Prefix, String_64 *Name,
							ColourGeneric *Definition, ColourModel Model,
							BOOL NewlineAfter = FALSE, BOOL IsSpotColour = FALSE);

// Base class functionality hidden from derived classes
private:
	BOOL PrepareForImport();
	BOOL FinishImport(BOOL Success);

protected:
	ImportedColours* m_pNewColours;
	SelOperation* m_pImportOp;
	CCLexFile* m_pImportFile;
	Document* m_pImportDoc;

	BOOL ImportIntoGallery;			// TRUE if we import directly into the colour gallery
	SGDisplayLibColGroup *CurrentGalleryGroup;
};


/********************************************************************************************
>	class MSPaletteFilter : public PaletteFilter

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/4/96
	Purpose:	Microsoft Windows palette filter
********************************************************************************************/
class MSPaletteFilter : public PaletteFilter
{
	CC_DECLARE_DYNAMIC(MSPaletteFilter);

public:
	MSPaletteFilter();
	~MSPaletteFilter();

// Virtual overrides
	BOOL Init();
	INT32 HowCompatible(PathName& Filename, ADDR  HeaderStart, UINT32 HeaderSize, UINT32 FileSize);
	
// Processing functions
public:
	virtual BOOL PreImport();
	virtual BOOL ImportPalette();
	virtual BOOL PostImport();

protected:
	UINT32 m_NumToImport;
};


/********************************************************************************************
>	class PaintShopProPaletteFilter : public PaletteFilter

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/4/96
	Purpose:	Microsoft Windows palette filter
********************************************************************************************/
class PaintShopProPaletteFilter : public PaletteFilter
{
	CC_DECLARE_DYNAMIC(PaintShopProPaletteFilter);

public:
	PaintShopProPaletteFilter();
	~PaintShopProPaletteFilter();

// Virtual overrides
	BOOL Init();
	INT32 HowCompatible(PathName& Filename, ADDR  HeaderStart, UINT32 HeaderSize, UINT32 FileSize);
	
// Processing functions
public:
	virtual BOOL PreImport();
	virtual BOOL ImportPalette();
	virtual BOOL PostImport();

protected:
	UINT32 m_NumToImport;
};


/********************************************************************************************
>	class AdobeColourTableFilter : public PaletteFilter

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/96
	Purpose:	Adobe Colour Table palette filter
********************************************************************************************/
class AdobeColourTableFilter : public PaletteFilter
{
	CC_DECLARE_DYNAMIC(AdobeColourTableFilter);

public:
	AdobeColourTableFilter();
	~AdobeColourTableFilter();

// Virtual overrides
	BOOL Init();
	INT32 HowCompatible(PathName& Filename, ADDR  HeaderStart, UINT32 HeaderSize, UINT32 FileSize);
	
// Processing functions
public:
	virtual BOOL PreImport();
	virtual BOOL ImportPalette();
	virtual BOOL PostImport();
};



/********************************************************************************************
>	class AdobeColourSwatchFilter : public PaletteFilter

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/5/96
	Purpose:	Adobe Colour Swatch palette filter
********************************************************************************************/
class AdobeColourSwatchFilter : public PaletteFilter
{
	CC_DECLARE_DYNAMIC(AdobeColourSwatchFilter);

public:
	AdobeColourSwatchFilter();
	~AdobeColourSwatchFilter();

// Virtual overrides
	BOOL Init();
	INT32 HowCompatible(PathName& Filename, ADDR  HeaderStart, UINT32 HeaderSize, UINT32 FileSize);
	
// Processing functions
public:
	virtual BOOL PreImport();
	virtual BOOL ImportPalette();
	virtual BOOL PostImport();

protected:
	WORD ReverseWord(WORD Orig);

protected:
	UINT32 m_NumToImport;
	BOOL m_MetUnknownModel;
};




/********************************************************************************************
>	class CorelPaletteFilter : public PaletteFilter

	Author:		Ben_Summers (Xara Group Ltd) <camelotdev@xara.com>		
	Created:	15 03 95	
	Purpose:	Corel Palette file importing class	
********************************************************************************************/
class CorelPaletteFilter : public PaletteFilter
{
	CC_DECLARE_DYNAMIC(CorelPaletteFilter);

public:
	CorelPaletteFilter();

//	Virtual overrides
public:
	BOOL Init();
	INT32 HowCompatible(PathName& Filename, ADDR  HeaderStart, UINT32 HeaderSize, UINT32 FileSize);

// Processing functions
public:
	virtual BOOL PreImport();
	virtual BOOL ImportPalette();
	virtual BOOL PostImport();

protected:
	INT32 HowCompatible4(PathName& Filename, ADDR  HeaderStart, UINT32 HeaderSize,	UINT32 FileSize);
   	INT32 HowCompatible5(PathName& Filename, ADDR  HeaderStart, UINT32 HeaderSize,	UINT32 FileSize);
	BOOL DoImport4();
	BOOL DoImport5();

// Member variables
protected:
	INT32 m_FileVersion;
};


/********************************************************************************************

>	class JCWColourFilter : public PaletteFilter

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/8/96

	Purpose:	Load's Jason's private palette file format

********************************************************************************************/

class JCWColourFilter : public PaletteFilter
{
	CC_DECLARE_DYNAMIC(JCWColourFilter);

public:
	JCWColourFilter();
	~JCWColourFilter();

// Virtual overrides
	BOOL Init();
	INT32 HowCompatible(PathName& Filename, ADDR HeaderStart, UINT32 HeaderSize, UINT32 FileSize);
	
// Processing functions
public:
	virtual BOOL PreImport();
	virtual BOOL ImportPalette();
	virtual BOOL PostImport();

protected:
	UINT32 m_NumToImport;
	BOOL m_ColoursAreSpots;
};

#endif  // INC_COPLFILR
