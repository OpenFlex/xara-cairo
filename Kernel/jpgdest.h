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

#ifndef INC_JPGDEST
#define INC_JPGDEST



/**************************************************************************************

>	class JPEGDataDestination : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/08/96
	Purpose:	Provides an overridden version of the IJG library source manager,
				using CCFile's.

**************************************************************************************/
class JPEGDataDestination : public CC_CLASS_MEMDUMP
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(JPEGDataDestination);

	class IJGDestMgr : public libJPEG::jpeg_destination_mgr
	{
	public:
		JPEGDataDestination*		pThis;
	};
	IJGDestMgr	m_DestMgr;

	CCFile*		m_pOutputFile;		// destination file
	libJPEG::JOCTET*		m_pBuffer;			// start of write buffer

public:
	JPEGDataDestination(CCFile* pOutputFile);

	BOOL Init(libJPEG::j_compress_ptr cinfo);

	enum
	{
		OUTPUT_BUF_SIZE = BUFSIZ	/* choose an efficiently fread'able size */
	};

protected:
	// Overrides for IJG callbacks
	static void		InitDestination(libJPEG::j_compress_ptr cinfo);
	static libJPEG::boolean	EmptyOutputBuffer(libJPEG::j_compress_ptr cinfo);
	static void		TerminateDestination(libJPEG::j_compress_ptr cinfo);

	// Helper functions
	static JPEGDataDestination* GetThis(libJPEG::j_compress_ptr cinfo);

	CCFile* GetFile() const;

};


#endif	// INC_JPGDEST
