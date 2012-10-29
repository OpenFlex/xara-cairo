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


// Classes to implement the graduation tables required for special path filling attributes

#ifndef INC_GRADTBL
#define INC_GRADTBL


class DocColour;
class ColourContext;
class View;
class ColourRamp;
class TransparencyRamp;

/********************************************************************************************

>	class GradTable: public CCObject

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/94
	Purpose:	A kernel representation of a graduation table.
				(This is a table of 8-bpp dither pattern specifiers for GDraw)

	SeeAlso:	GradTable32

	Notes:		There are now 3 base functions in GradTable and GradTable32 which build
				graduation tables. The tables are actually identical in meaning, but are
				encoded as:
					(a) Gavin 8bpp dither patterns,
					(b) RGBQUAD RGB structures,
					(c) COLORREF RGB values
				this is because the different places that use these tables demand the
				different formats, and converting all the code to use only one table
				format is non-trivial and/or inefficient.

********************************************************************************************/

class GradTable: public CCObject
{
	CC_DECLARE_DYNCREATE(GradTable)

public:
	GradTable(BOOL LargeTable = FALSE);
	~GradTable();

	void SetTableSize(BOOL LargeTable);
			// Set the overall size of the table

	INT32 GetTableLength(void) { return(m_pTable->Length); };

	BOOL BuildTable(DocColour &StartCol, DocColour &EndCol,
					View *ContextView, EFFECTTYPE Effect,
					BOOL LargeTable = FALSE);
			// Set table size, and build a single-stage gradfill in it

	BOOL BuildTable(DocColour &StartCol, DocColour &EndCol,
					View *ContextView, EFFECTTYPE Effect,
					CProfileBiasGain& BiasGain, BOOL LargeTable = FALSE);
			// Set table size, and build a single-stage gradfill in it
			// This version takes into account the new profile stuff (CGS - 4/2/2000)

	BOOL BuildTable(DocColour &StartCol, DocColour &EndCol,	ColourRamp *pColourRamp,
					View *ContextView, EFFECTTYPE Effect,
					BOOL LargeTable = FALSE);
			// Set table size, and build a multi-stage gradfill in it

	BOOL BuildHighQualityRepeatTable(DocColour &StartCol, DocColour &EndCol, ColourRamp *pColourRamp,
					View *ContextView, EFFECTTYPE Effect);
			// Set table size, and build a multi-stage gradfill in it
			// This version build a high quality (aliasing free) repeating fill table.
			// This version handles fills with colour ramps, and those without

	BOOL BuildHighQualityRepeatTable(DocColour &StartCol, DocColour &EndCol,
					View *ContextView, EFFECTTYPE Effect,
					CProfileBiasGain& BiasGain);
			// Set table size, and build a multi-stage gradfill in it
			// This version build a high quality (aliasing free) repeating fill table.
			// This version handles profiled fills

	BOOL BuildTable(DocColour &StartCol, DocColour &EndCol,
					View *ContextView, EFFECTTYPE Effect,
					DWORD FirstEntry, DWORD LastEntry);
			// Build graduations between StartCol and EndCol, filling the given 
			// portion of the table - used for one stage of a multi-stage fill

	BOOL AddToTable(DocColour &NewCol, View *ContextView, DWORD Index);
			// Adds the given colour as entry 'Index' in the table

	GraduationTable *GetTable(void) { return(m_pTable); };
			// Proper access function for finding our Table data member

	BOOL IsLarge(void) { return(m_bLargeTable); };

protected:
	void FillTable(DWORD StartIndex, DWORD EndIndex,
					PColourRGBT *StartDef, PColourRGBT *EndDef);
			// Internal helper function for linearly interpolating between 2 RGB values

	INT32 GetTableSize(GDrawContext* GD, BOOL LargeTable);
			// Returns the size (bytes) of the structure required

	INT32 GetTableLength(GDrawContext* GD, BOOL LargeTable);
			// Returns the size (entries) of the structure required

private:
	BOOL m_bLargeTable;
	GraduationTable* m_pTable;
};



/********************************************************************************************

>	class TranspGradTable: public CCObject

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/94
	Purpose:	A kernel representation of a transparent graduation table.
	SeeAlso:	-

********************************************************************************************/

class TranspGradTable: public CCObject
{
	CC_DECLARE_DYNCREATE(TranspGradTable)

public:
	TranspGradTable(BOOL LargeTable = FALSE);
	~TranspGradTable();

	
	void SetTableSize(BOOL LargeTable);
			// Set the overall size of the table

	BOOL BuildTable(INT32 StartTransp, INT32 EndTransp);
	BOOL BuildTable(INT32 StartTransp, INT32 EndTransp, CProfileBiasGain& BiasGain);
	BOOL BuildTable(INT32 StartTransp, INT32 EndTransp, TransparencyRamp *pTranspTable);
	BOOL BuildHighQualityRepeatTable(INT32 StartTransp, INT32 EndTransp, CProfileBiasGain& BiasGain);
	BOOL BuildHighQualityRepeatTable(INT32 StartTransp, INT32 EndTransp, TransparencyRamp *pTranspTable);
	BOOL BuildBitmapTable(INT32 StartTransp, INT32 EndTransp, CProfileBiasGain& BiasGain);
	BOOL BuildBitmapTable(INT32 StartTransp, INT32 EndTransp, TransparencyRamp *pTranspTable, CProfileBiasGain& BiasGain);

	TransparentGradTable* GetTable(void) const { return(m_pTable); };
	BOOL IsLarge(void) const { return(m_bLargeTable); };

protected:
	INT32 GetTableSize(GDrawContext* GD, BOOL LargeTable);
			// Returns the size (bytes) of the structure required

	INT32 GetTableLength(GDrawContext* GD, BOOL LargeTable);
			// Returns the size (entries) of the structure required

private:
	void FillSection(INT32 startindex, INT32 endindex, INT32 starttransp, INT32 endtransp);

private:	
	BOOL m_bLargeTable;
	TransparentGradTable* m_pTable;
};



/********************************************************************************************

>	class GradTable32: public CCObject

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/94
	Purpose:	A kernel representation of a 32 bpp graduation table.
				(This is a table of COLORREF RGB values for GDraw)

	SeeAlso:	GradTable

	Notes:		There are now 3 base functions in GradTable and GradTable32 which build
				graduation tables. The tables are actually identical in meaning, but are
				encoded as:
					(a) Gavin 8bpp dither patterns,
					(b) RGBQUAD RGB structures,
					(c) COLORREF RGB values
				this is because the different places that use these tables demand the
				different formats, and converting all the code to use only one table
				format is non-trivial and/or inefficient.

********************************************************************************************/

class GradTable32: public CCObject
{
	CC_DECLARE_DYNCREATE(GradTable32)

public:
	GradTable32();
	~GradTable32();


public:		// GradTable32 sepcific methods
	void SetTableSize(BOOL LargeTable);
			// Set the overall size of the table

	BOOL BuildTable(DocColour &StartCol, DocColour &EndCol,
					View *ContextView, EFFECTTYPE Effect,
					DWORD TableSize = 0x100);
			// Set table size, and build a single-stage gradfill in it

	BOOL BuildTable(DocColour &StartCol, DocColour &EndCol,
					View *ContextView, EFFECTTYPE Effect,
					DWORD FirstEntry, DWORD LastEntry);
			// Build graduations between StartCol and EndCol, filling the given 
			// portion of the table - used for one stage of a multi-stage fill

public:		// Generic graduation-building methods - produce tables of RGB values
			// These are used internally to build the GradTable32, but are also exported
			// for GRenderRegion, OSRenderRegion, OILBitmap, etc for generating
			// fill/contone tables with.
	static BOOL BuildGraduatedPalette(DocColour &StartCol, DocColour &EndCol,
										View *ContextView, EFFECTTYPE Effect,
										DWORD TableSize, COLORREF *pTable);
			// Builds a table of graduated RGBQUADs between StartCol and EndCol

	static BOOL BuildGraduatedPalette(DocColour &StartCol, DocColour &EndCol,
										View *ContextView, EFFECTTYPE Effect,
										DWORD FirstEntry, DWORD LastEntry,
										COLORREF *pTable);
			// Builds a portion of a table of graduated RGBQUADs between StartCol and EndCol

	static BOOL BuildGraduatedPalette(DocColour &StartCol, DocColour &EndCol,
										View *ContextView, EFFECTTYPE Effect,
										DWORD TableSize, RGBQUAD *pTable);
			// Builds a table of graduated RGBQUADs between StartCol and EndCol

	static BOOL BuildGraduatedPalette(DocColour &StartCol, DocColour &EndCol,		// CGS
										View *ContextView, EFFECTTYPE Effect,
										DWORD TableSize, RGBQUAD *pTable,
										CProfileBiasGain& BiasGain);
			// Builds a portion of a table of graduated RGBQUADs between StartCol and EndCol

	static BOOL BuildGraduatedPalette(DocColour &StartCol, DocColour &EndCol,
										View *ContextView, EFFECTTYPE Effect,
										DWORD FirstEntry, DWORD LastEntry,
										RGBQUAD *pTable);
			// Builds a portion of a table of graduated RGBQUADs between StartCol and EndCol

protected:
	static BOOL BuildPaletteInternal(DocColour &StartCol, DocColour &EndCol,
										View *ContextView, EFFECTTYPE Effect,
										DWORD FirstEntry, DWORD LastEntry,
										void *pTable, BOOL IsColorRef, CProfileBiasGain& BiasGain);		// CGS
			// Internal function called by all of the above variants

	// ---
	static BOOL BuildPaletteInternalRGB(DocColour &StartCol, DocColour &EndCol, View *ContextView,
											DWORD FirstEntry, DWORD LastEntry,
											void *pTable, BOOL IsColorRef, CProfileBiasGain& BiasGain);	// CGS
			// Internal helper function for optimised RGB Mix GradTable32 generation

	static BOOL BuildPaletteInternalHSV(DocColour &StartCol, DocColour &EndCol,
											View *ContextView, EFFECTTYPE Effect,
											DWORD FirstEntry, DWORD LastEntry,
											void *pTable, BOOL IsColorRef,CProfileBiasGain& BiasGain);	// CGS
			// Internal helper function for optimised HSV Mix GradTable32 generation

	// ---
	static BOOL BuildPaletteInternalRGBComposite(DocColour &StartCol, DocColour &EndCol, View *ContextView,
											DWORD FirstEntry, DWORD LastEntry,
											void *pTable, BOOL IsColorRef);
			// Internal helper function for optimised RGB Mix GradTable32 generation

};

#endif  // INC_GRADTBL

