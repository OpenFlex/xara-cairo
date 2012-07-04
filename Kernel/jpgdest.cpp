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


#include "camtypes.h"
//#include "ccfile.h" - in camtypes.h [AUTOMATICALLY REMOVED]

//#include "jinclude.h"
#include "jpglib_namespace.h"
#include "jpgermgr.h"

//#include "errors.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "tim.h"			// for _R(IDE_FILE_WRITE_ERROR)

#include "jpgdest.h"


// Place any IMPLEMENT type statements here
CC_IMPLEMENT_MEMDUMP(JPEGDataDestination, CC_CLASS_MEMDUMP)


// We want better memory tracking
#define new CAM_DEBUG_NEW


// Functions follow



/********************************************************************************************

>	JPEGDataDestination::JPEGDataDestination(j_compress_ptr cinfo, CCFile* pOutputFile)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/10/96
	Inputs:		pOutputFile : a pointer to a CCFile providing the destination for the JPEG
				output
	Purpose:	Default constructor

********************************************************************************************/
JPEGDataDestination::JPEGDataDestination(CCFile* pOutputFile)
{
	ERROR3IF(pOutputFile == NULL || !pOutputFile->IS_KIND_OF(CCFile), "pOutputFile isn't");


	m_DestMgr.pThis	= this;

	m_DestMgr.init_destination		= InitDestination;
	m_DestMgr.empty_output_buffer	= EmptyOutputBuffer;
	m_DestMgr.term_destination		= TerminateDestination;

	m_pOutputFile	= pOutputFile;
	m_pBuffer		= NULL;
}


/********************************************************************************************

>	BOOL JPEGDataDestination::Init(j_compress_ptr cinfo)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/10/96
	Inputs:		cinfo : a pointer to the IJG compression structure
	Purpose:	Initializes the given compression structure with this JPEGDataDestination

********************************************************************************************/
BOOL JPEGDataDestination::Init(libJPEG::j_compress_ptr cinfo)
{
	ERROR3IF(cinfo == NULL, "cinfo NULL");

	cinfo->dest = &m_DestMgr;

	return TRUE;
}


/********************************************************************************************

>	void JPEGDataDestination::InitDestination(j_compress_ptr cinfo)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/10/96
	Inputs:		cinfo : a pointer to the IJG compression control structure
	Purpose:	Callback for IJG destination file handler
				Initialize destination --- called by jpeg_start_compress
				before any data is actually written.

********************************************************************************************/
void JPEGDataDestination::InitDestination(libJPEG::j_compress_ptr cinfo)
{
	using namespace libJPEG;

	JPEGDataDestination* pThis = GetThis(cinfo);

	/* Allocate the output buffer --- it will be released when done with image */
	pThis->m_pBuffer = (JOCTET *)(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  OUTPUT_BUF_SIZE * sizeof(JOCTET));

	pThis->m_DestMgr.next_output_byte = pThis->m_pBuffer;
	pThis->m_DestMgr.free_in_buffer = OUTPUT_BUF_SIZE;
}


/********************************************************************************************

>	boolean	JPEGDataDestination::EmptyOutputBuffer(j_compress_ptr cinfo)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/10/96
	Inputs:		cinfo : a pointer to the IJG compression control structure
	Purpose:	Callback for IJG destination file handler
				Empty the output buffer --- called whenever buffer fills up.
	Notes:		Says IJG docs,
				"In typical applications, this should write the entire output buffer
				(ignoring the current state of next_output_byte & free_in_buffer),
				reset the pointer & count to the start of the buffer, and return TRUE
				indicating that the buffer has been dumped."
	Scope:		static

********************************************************************************************/
libJPEG::boolean	JPEGDataDestination::EmptyOutputBuffer(libJPEG::j_compress_ptr cinfo)
{
	JPEGDataDestination* pThis = GetThis(cinfo);
	CCFile* pFile = pThis->GetFile();

	// Write out the full buffer
	pFile->write(pThis->m_pBuffer, OUTPUT_BUF_SIZE);

	// Check written OK
	if (pFile->bad() || pFile->fail())
	{
		JPEGErrorManager* pError = (JPEGErrorManager*)cinfo->err;
		pError->ThrowError(_R(IDE_FILE_WRITE_ERROR));
	}

	pThis->m_DestMgr.next_output_byte	= pThis->m_pBuffer;
	pThis->m_DestMgr.free_in_buffer	= OUTPUT_BUF_SIZE;

  return TRUE;
}


/********************************************************************************************

>	void JPEGDataDestination::TerminateDestination(j_compress_ptr cinfo)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/10/96
	Inputs:		cinfo : a pointer to the IJG compression control structure
	Purpose:	Terminate destination --- called by jpeg_finish_compress
				after all data has been written.  Usually needs to flush buffer.
	Notes:		*not* called by jpeg_abort or jpeg_destroy; surrounding
				application must deal with any cleanup that should happen even
				for error exit.

********************************************************************************************/
void JPEGDataDestination::TerminateDestination(libJPEG::j_compress_ptr cinfo)
{
	JPEGDataDestination* pThis = GetThis(cinfo);
	CCFile* pFile = pThis->GetFile();

	size_t DataCount = OUTPUT_BUF_SIZE - pThis->m_DestMgr.free_in_buffer;

	// Write any data remaining in the buffer
	if (DataCount > 0)
	{
		// Write out the full buffer
		pFile->write(pThis->m_pBuffer, DataCount);
	}
	pFile->flush();

	// Make sure we wrote the output file OK
	if (pFile->bad() || pFile->fail())
	{
		JPEGErrorManager* pError = (JPEGErrorManager*)cinfo->err;
		pError->ThrowError(_R(IDE_FILE_WRITE_ERROR));
	}
}



/********************************************************************************************

>	JPEGDataDestination* JPEGDataDestination::GetThis(j_compress_ptr cinfo)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/10/96
	Inputs:		cinfo : a pointer to the IJG compression control structure
	Purpose:	Helper function to return the this pointer buried in the cinfo structure

********************************************************************************************/
JPEGDataDestination* JPEGDataDestination::GetThis(libJPEG::j_compress_ptr cinfo)
{
	JPEGDataDestination* pThis = ((IJGDestMgr*)(cinfo->dest))->pThis;
	ERROR3IF(!pThis->IS_KIND_OF(JPEGDataDestination), "GetThis - pThis isn't");

	return pThis;
}


/********************************************************************************************

>	CCFile* JPEGDataDestination::GetFile() const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/10/96
	Purpose:	Helper function to return the CCFile associated with this JPEGDataDestination

********************************************************************************************/
CCFile* JPEGDataDestination::GetFile() const
{
	return m_pOutputFile;
}
