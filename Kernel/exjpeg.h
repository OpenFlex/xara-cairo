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

#ifndef INC_EXJPEG
#define INC_EXJPEG

#include "bitfilt.h"
#include "jpglib_namespace.h"
//#include "filtrres.h"

class CXaraFileRecord;

typedef UINT32 JPEG_QUALITY;

/********************************************************************************************

>	class JPEGExportOptions : public BitmapExportOptions

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/10/96
	Purpose:   	Allows JPEG specific export options to be manipulated

********************************************************************************************/
class JPEGExportOptions : public BitmapExportOptions
{
	// Declare the class for memory tracking
	CC_DECLARE_DYNCREATE(JPEGExportOptions);
public:
	JPEGExportOptions();
	JPEGExportOptions(const FilterType FilterID, const StringBase* pFilterName);

	virtual BOOL	RetrieveDefaults();
	virtual BOOL	SetAsDefaults() const;

	// Save and load from named export set properties.
	virtual BOOL Write(CXaraFileRecord* pRec);
	virtual BOOL Read(CXaraFileRecord* pRec);

	virtual BOOL	GetSupportsImageMap() { return TRUE; }

	// Functions to edit actual options
	BOOL			DoAsProgressive() const;
	BOOL			SetMakeProgressive(BOOL bProgressive);

	JPEG_QUALITY	GetQuality() const;
	BOOL			SetQuality(const JPEG_QUALITY& Quality);

	libJPEG::J_DCT_METHOD	GetDCTMethod() const;
	BOOL			SetDCTMethod(const libJPEG::J_DCT_METHOD& DCTMethod);

	libJPEG::J_COLOR_SPACE	GetColourModel() const;
	UINT32			GetColourComponentCount() const;
	BOOL			SetColourModel(const libJPEG::J_COLOR_SPACE& ColourModel);

	static void	SetKernelBitmap (KernelBitmap* pBitmap) { pKernelBitmap = pBitmap; }
	static KernelBitmap* GetKernelBitmap ()				{ return pKernelBitmap; }

	static void SetJPEGPresentAndSelected(BOOL Value)	{ m_JPEGPresentAndSelected = Value; }
	static BOOL GetJPEGPresentAndSelected()				{ return m_JPEGPresentAndSelected;  }

	// for object copying and comparing
	virtual BOOL CopyFrom(BitmapExportOptions *pOther);

	//  Same as above, except it is used to copy information when changing file types
	virtual BOOL FileTypeChangeCopyFrom(BitmapExportOptions *pOther);
//	virtual BOOL Equal(BitmapExportOptions *pOther);

	// duplicating the static flag below - needed for the export preview
	BOOL			m_bJPEGPresentAndSelected;

	virtual UINT32 GetFilterNameStrID() { return _R(IDS_JPG_EXP_FILTERNAME);}

protected:
	
	JPEG_QUALITY			m_Quality;
	BOOL					m_DoAsProgressive;
	libJPEG::J_DCT_METHOD	m_DCTMethod;
	libJPEG::J_COLOR_SPACE	m_ColourModel;
	UINT32					m_ColourComponents;

	static KernelBitmap*	pKernelBitmap;
	static BOOL 			m_JPEGPresentAndSelected ;

};

class JPEGErrorManager;
class JPEGDataDestination;
class CCLexFile;


/**************************************************************************************

>	class JPEGExportFilter : public BaseBitmapFilter

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/10/96
	Purpose:	Provides an Accusoft-free JPEG export filter

**************************************************************************************/
class JPEGExportFilter : public BaseBitmapFilter
{
	// Declare the class for memory tracking
	CC_DECLARE_DYNAMIC(JPEGExportFilter);

public:
	JPEGExportFilter();
	~JPEGExportFilter();

	// Overrides from Filter class
	virtual BOOL Init();

	INT32 HowCompatible(PathName& Filename, ADDR HeaderStart, UINT32 HeaderSize, 
						UINT32 FileSize) {return 0;}	// dummy implementation

	virtual BOOL IsThisBppOk(UINT32 Bpp);

	virtual BOOL WriteBitmapToFile(KernelBitmap* pKernelBitmap, double Dpi);
	virtual BOOL WriteBitmapToFile(KernelBitmap* pKernelBitmap, BaseCamelotFilter *pFilter,
										CCLexFile *pFile, INT32 Compression);

	BOOL WriteBitmapSource(BitmapSource *Source, UINT32 Height, BaseCamelotFilter* pThisFilter, CCLexFile* pCCFile);

	BOOL DoExportBitmapWithOptions(Operation* pOp, CCLexFile* pFile, PathName* pPath,
									KernelBitmap* pBitmap, BitmapExportOptions *pOptions);

	virtual BitmapExportOptions* CreateExportOptions() const;
	virtual void PostGetExportOptions(BitmapExportOptions* pOptions);

protected:
// Overridden Functions
	virtual BOOL SetExportHint(Document* pDoc);
	
	virtual BOOL GetRenderBottomToTop();

	virtual BOOL GetExportOptions(BitmapExportOptions* pOptions);
//	virtual BOOL GetExportOptions(UINT32 *Depth, double *DPI, SelectionType *Selection,
//										Coord* pForceSize);

	virtual BOOL PrepareForOperation();
	virtual BOOL PrepareToExport(Spread *pSpread, UINT32 Depth, double DPI,
									SelectionType Selection, UINT32 Dither);
	BOOL InternalPrepareToExport();
	BOOL EndWriteToFile(void);

	virtual BOOL WriteFileHeader(void);
	virtual BOOL WriteFrame(void);
	virtual BOOL WritePostFrame(void);

	virtual void CleanUpAfterExport();

// Support Functions
	BOOL DoFilter(KernelBitmap* pKernelBitmap, CCLexFile *pFile);

	BOOL WriteRawBitmap(const ADDR& pBitmapData, 
						const BMP_SIZE& Width, const BMP_SIZE& Height,
						const BMP_DEPTH& Depth,
						DIBConvert* pConverter);

	BOOL	InitErrorHandler();
	BOOL	InitFileHandler();

	Filter*	GetFilterForUpdate() const;
	BOOL	SetFilterForUpdate(Filter* const pFilterForUpdate);

	BOOL	GetPostOperation() const			{return m_PostOperation;   }
	void	SetPostOperation(BOOL Value)		{ m_PostOperation = Value; }


protected:
	// Attributes
	// for the file we're exporting to
	BOOL							m_bOldReportErrors;
	BOOL							m_bOldThrowExceptions;
	BOOL							m_PostOperation;

	Filter*							m_pFilterForUpdate;

	// the IJG control structure
	struct libJPEG::jpeg_compress_struct m_cinfo;
	// ...and support
	JPEGErrorManager*				m_pErrorHandler;
	JPEGDataDestination*			m_pDestinationHandler;
};



#endif	// INC_EXJPEG
