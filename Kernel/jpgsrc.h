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

#ifndef INC_JPGSRC
#define INC_JPGSRC



/**************************************************************************************

>	class JPEGDataSource : public jpeg_source_mgr

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/08/96
	Purpose:	Provides an overridden version of the IJG library source manager,
				using CCFile's.

**************************************************************************************/
class JPEGDataSource : public libJPEG::jpeg_source_mgr
{
	// Declare the class for memory tracking
//	CC_DECLARE_MEMDUMP(CCWobJob);

	BOOL		m_bStartOfFile;		// Do we have any data yet?
	CCFile*		m_pInputFile;		// source file
	libJPEG::JOCTET *m_pBuffer;			// start of read buffer

public:
	JPEGDataSource(CCFile* pInputFile);

	enum
	{
		INPUT_BUF_SIZE = 4096	/* choose an efficiently fread'able size */
	};

	libJPEG::boolean	InitBuffer(libJPEG::j_decompress_ptr cinfo);
	static void	InitSource(libJPEG::j_decompress_ptr cinfo);
	static libJPEG::boolean	FillInputBuffer(libJPEG::j_decompress_ptr cinfo);
	static void	SkipInputData(libJPEG::j_decompress_ptr cinfo, long /*TYPENOTE: Correct*/ num_bytes);
	static void	TerminateSource(libJPEG::j_decompress_ptr cinfo);
};


#endif	// INC_JPGSRC
