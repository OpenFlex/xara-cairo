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

#ifndef INC_IMJPEG
#define INC_IMJPEG

#include "bitfilt.h"
#include "jpglib_namespace.h"

class JPEGErrorManager;
class JPEGDataSource;
class JPEGProgressMonitor;
//class CCFile;
class CCLexFile;


/**************************************************************************************

>	class JPEGImportFilter : public BaseBitmapFilter

	Author:
	Created:
	Purpose:	Provides a JPEG import filter using the IJG JPEG LIBRARY

**************************************************************************************/

class JPEGImportFilter : public BaseBitmapFilter
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(JPEGImportFilter);

public:
	JPEGImportFilter();
	~JPEGImportFilter();

	// Overrides from Filter class
	virtual BOOL Init();

	virtual INT32 HowCompatible(PathName& Filename, ADDR HeaderStart, 
								UINT32 HeaderSize, UINT32 FileSize);


	// Only entry points: One for native format, one for BaseBitmapFilter
	// Naturally there should only be the second one.
    virtual BOOL ReadFromFile(OILBitmap* pOilBitmap, BaseCamelotFilter* pFilter,
							  CCLexFile* pFile, BOOL IsCompressed);

    virtual BOOL ReadFromFile(OILBitmap* pOilBitmap);

	static BOOL GetImportAt96dpi()						{ return m_fImportAt96dpi; }
	static void SetImportAt96dpi( BOOL fImportAt96 )	{ m_fImportAt96dpi = fImportAt96; }

protected:
	BOOL DoFilter(CCFile* pInputFile, OILBitmap* pOilBitmap);

// Overridden Functions
	virtual BOOL PrepareFilterForOperation();

	virtual BitmapImportOptions* GetImportOptions();	// ask them really

	virtual BOOL			IsFormatLossy() const;
	virtual OFFSET			GetDataStartOffset() const;
	virtual BitmapSource*	CreateBitmapSource(OFFSET Size) const;

	virtual void PrepareForImage(BitmapImportOptions* pOptions);
	virtual void ReadImage();
	virtual void OnImageCompletion();

	virtual BOOL OnFilterCompletion();

// Support Functions
	void	ReadHeader();
	BOOL	SetBitmapResolution();
	BOOL	ReadPalette();

	BOOL	InitErrorHandler();
	BOOL	InitFileHandler();
	BOOL	InitProgressMonitor();

protected:
	// Attributes
	// for the file we're importing from
	CCFile*							m_pFile;
	BOOL							m_bOldReportErrors;
	BOOL							m_bOldThrowExceptions;
	UINT32							m_uStartOffset;
	static BOOL						m_fImportAt96dpi;

	// the IJG control structure
	struct libJPEG::jpeg_decompress_struct	m_cinfo;
	// ...and support
	JPEGErrorManager*				m_pErrorHandler;
	JPEGDataSource*					m_pSourceHandler;
	JPEGProgressMonitor*			m_pProgressMonitor;

	// for progress
	CCLexFile*						m_pFileForProgress;
	Filter*							m_pFilterForProgress;
	UINT32							m_uImportSize;

	// Current Working Image Info (use JPEGImportResults!!)
	LPBITMAPINFO*	m_ppInfo;
	LPBYTE*			m_ppBytes;

	UINT32 m_uWidth;
	UINT32 m_uHeight;
	UINT32 m_uBitsPerPixel;

};


#endif	// INC_IMJPEG
