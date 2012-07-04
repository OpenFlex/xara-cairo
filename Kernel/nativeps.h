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

// The Camelot Native File format for Studio (version 1)

#ifndef INC_NATIVEEPS
#define INC_NATIVEEPS

#include "cameleps.h"
class KernelBitmapRef;



// All the commands used by Camelot Native EPS files.
enum
{
	// Bitmap objects/bitmap fills
	EPSC_cbmp = EPSC_cameps_last,
};




/********************************************************************************************

>	class CamelotNativeEPSFilter : public CamelotEPSFilter

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/12/94
	Purpose:	This filter will be almost the same as Camelot EPS, only it will hold a
				little more information and store data slightly more efficiently. Mainly,
				it will save out bitmaps as binary. It won't really be valid EPS as it
				will not always be ascii. The Native file format is being done this way as
				it will take little or no effort to do this.

********************************************************************************************/

class CamelotNativeEPSFilter : public CamelotEPSFilter
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(CamelotNativeEPSFilter);

public:
	// Construction and initialisation
	CamelotNativeEPSFilter();
	~CamelotNativeEPSFilter();
	BOOL Init();

	// Exporting
	BOOL PrepareToExport(CCLexFile* pFile, Spread *pSpread);
	virtual EPSExportDC* CreateExportDC();
	virtual BOOL ExportBitmap(KernelBitmap&);

	// Importing
	BOOL PrepareToImport();
	virtual INT32 ImportBinary(ADDR pData, INT32 Length);
	virtual BOOL ProcessFilterComment();
	virtual void CleanUpAfterImport(BOOL Successful);
	BitmapFilterSupport GetBitmapSupportLevel();
	virtual void BitmapPoolAttach(KernelBitmap* pBitmap);

	// Flag to show if the pool is being saved or not	
	BOOL IsSavingBitmapPool;

	double SmartGetBuildNumber();
	double GetBuildNumber() { return BuildVersionNumber; }

protected:
	virtual void LookUpToken();
	virtual BOOL ProcessToken();
	INT32  EPSHeaderIsOk(ADDR pFileHeader, UINT32 HeaderSize);

	// Function to get export options, if any
	virtual BOOL GetExportOptions( );

	// Function to load in bitmaps
	virtual BOOL ReadBitmap();

	// Stuff to handle the bitmap pool
	INT32 BitmapCount;
	INT32 PendingBitmapNum;
	KernelBitmapRef* BitmapPoolRefs;

	// The old value of the Import With Layers Flag
	BOOL OldImportWithLayers;
	BOOL OldOpenWithLayers;

	static CommandMap NativeCommands[];

	// Items to handle the file compression
	INT32 CompressionType;	// type of compression in use (0 at present)
	BOOL CompressionOn;		// on/off flag

	virtual BOOL SetFileCompressionState(BOOL NewState); 
	virtual BOOL GetFileCompressionState(); 

	double FileVersionNumber;
	double BuildVersionNumber;

	INT32 OldMinLineWidth;		// because we need somewhere to store it as we set it to zero

public:
	// Control over whether we compress native files or not. 
	static BOOL SetNativeCompression(BOOL NewState);
	static BOOL GetNativeCompression();
	static BOOL CompressNative;	// compression preference flag
};





/********************************************************************************************

>	class NativeRenderRegion : public CamelotEPSRenderRegion

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/12/94
	Purpose:	The render region class for the native file save.

********************************************************************************************/

class NativeRenderRegion : public CamelotEPSRenderRegion
{
	CC_DECLARE_DYNAMIC(NativeRenderRegion)
	
public:
	NativeRenderRegion(DocRect ClipRect, Matrix ConvertMatrix, FIXED16 ViewScale);

	virtual void ConditionalSuicide ( void );	// Graeme (24-0-00).

	void GetRenderRegionCaps(RRCaps* pCaps);

protected:
	virtual BOOL WriteProlog(KernelDC*);
	virtual BOOL WriteSetup(KernelDC*);

	// File version saving. In anything but Native format does nothing
	virtual BOOL WriteFileVersion(KernelDC*);

	// Compressed saving. In anything but Native format does nothing
	virtual BOOL WriteCompressionState(KernelDC*);
	virtual BOOL WriteEndCompressionState(KernelDC*);

	// Flag to say that we started up the compressor ok
	BOOL CompressionInitedOk;

public:
	void GetValidPathAttributes();
	void GetValidTransparencyAttributes();
	virtual void GetValidTextAttributes();
	virtual BOOL RenderChar(WCHAR ch, Matrix* pMatrix);

// virtual Functions to help with rendering
	virtual BOOL WantsGrids();

	// (ChrisG - 30/01/01) Added so that we don't use the CamelotEPS (Xara X EPS) 
	//	version (which copes with RGB colours, not just CMYK ones).
	virtual void OutputFillColour ();
	virtual void OutputStrokeColour ();
	virtual BOOL OutputGradFillColours(DocColour* StartCol, DocColour* EndCol, ColourContext* pContext);
};




/********************************************************************************************

>	class NativeExportDC : public EPSExportDC

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/12/94
	Purpose:	This class makes use of the base class for almost everything. Its real
				purpose is just to overide the Binary and Bitmap areas of the DC. In
				EPSExportDC these are converted to Hex strings and here they are output
				directly as binary...
	SeeAlso:	EPSExportDC

********************************************************************************************/

class NativeExportDC : public EPSExportDC
{
public:
	NativeExportDC(Filter*);

	// This class want to overide the bitmap functions from the base class
	virtual INT32 OutputRawBinary(BYTE *Data, UINT32 Length, UINT32 Alignment = 1);
};


#endif  // INC_NATIVEEPS


