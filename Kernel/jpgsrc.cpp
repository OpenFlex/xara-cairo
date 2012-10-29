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

#include "jpglib_namespace.h"
#include "jpgermgr.h"
//#include "andy.h"			// for _R(IDE_FILEREADERROR)

#include "jpgsrc.h"

// Place any IMPLEMENT type statements here
//CC_IMPLEMENT_MEMDUMP(CCWobJob, CC_CLASS_MEMDUMP)


// We want better memory tracking
#define new CAM_DEBUG_NEW


// Functions follow



/********************************************************************************************

>	JPEGDataSource::JPEGDataSource(CCFile* pInputFile)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/08/96
	Inputs:		pFile : a pointer to a CCFile providing the source for a JPEG filter
	Purpose:	Default consturctor for a JPEGDataSource.
				This constructor sets up the callback functions to be used when the IJG
				library requires more data to be read from the source given as the argument
				to this constructor.

********************************************************************************************/
JPEGDataSource::JPEGDataSource(CCFile* pInputFile) : m_pInputFile(pInputFile)
{
	m_bStartOfFile	= FALSE;	// Provide safe defaults
	m_pBuffer		= NULL;

	// Override default "methods"
	init_source			= InitSource;
	fill_input_buffer	= FillInputBuffer;
	skip_input_data		= SkipInputData;
	/*
	* An additional method that can be provided by data source modules is the
	* resync_to_restart method for error recovery in the presence of RST markers.
	* For the moment, this source module just uses the default resync method
	* provided by the JPEG library.  That method assumes that no backtracking
	* is possible.
	*/
	resync_to_restart	= libJPEG::jpeg_resync_to_restart;
	term_source			= TerminateSource;

	// Initialize base class!!
	bytes_in_buffer		= 0;		// forces fill_input_buffer on first read
	next_input_byte		= NULL;		// until buffer loaded
}


/********************************************************************************************

>	boolean	JPEGDataSource::InitBuffer(j_decompress_ptr cinfo)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/08/96
	Inputs:		cinfo : a pointer to a CCFile providing the source for a JPEG filter
	Purpose:	Initializes the buffer to be used by the m_pFile object.
	Notes:		Uses the IJG library for memory allocation

********************************************************************************************/
libJPEG::boolean	JPEGDataSource::InitBuffer(libJPEG::j_decompress_ptr cinfo)
{
	using namespace libJPEG;

	m_pBuffer = (JOCTET *) (*cinfo->mem->alloc_small) 
					((j_common_ptr) cinfo, JPOOL_PERMANENT, INPUT_BUF_SIZE * sizeof(JOCTET));
	return (m_pBuffer != NULL);
}


/********************************************************************************************

>	void JPEGDataSource::InitSource(j_decompress_ptr cinfo)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/08/96
	Inputs:		cinfo : a pointer to a j_decompress_ptr provided by the IJG routines
	Purpose:	Initialize source --- called by jpeg_read_header before any data is actually
				read.

	Notes:		We reset the empty-input-file flag for each image, but we don't clear the
				input buffer. This is correct behavior for reading a series of images from
				one source.

********************************************************************************************/
void JPEGDataSource::InitSource(libJPEG::j_decompress_ptr cinfo)
{
	JPEGDataSource* pThis = (JPEGDataSource*)cinfo->src;

	pThis->m_bStartOfFile = TRUE;
}



/********************************************************************************************

>	boolean JPEGDataSource::FillInputBuffer (j_decompress_ptr cinfo)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/08/96
	Inputs:		cinfo : a pointer to a j_decompress_ptr provided by the IJG routines
	Purpose:	Overrides the standard implementation using stdio with a CCFile version.

	Notes:		The following extract from the IJG library explains its purpose:

				Fill the input buffer --- called whenever buffer is emptied.

				In typical applications, this should read fresh data into the buffer
				(ignoring the current state of next_input_byte & bytes_in_buffer),
				reset the pointer & count to the start of the buffer, and return TRUE
				indicating that the buffer has been reloaded.  It is not necessary to
				fill the buffer entirely, only to obtain at least one more byte.

				There is no such thing as an EOF return.  If the end of the file has been
				reached, the routine has a choice of ERREXIT() or inserting fake data into
				the buffer.  In most cases, generating a warning message and inserting a
				fake EOI marker is the best course of action --- this will allow the
				decompressor to output however much of the image is there.  However,
				the resulting error message is misleading if the real problem is an empty
				input file, so we handle that case specially.

				In applications that need to be able to suspend compression due to input
				not being available yet, a FALSE return indicates that no more data can be
				obtained right now, but more may be forthcoming later.  In this situation,
				the decompressor will return to its caller (with an indication of the
				number of scanlines it has read, if any).  The application should resume
				decompression after it has loaded more data into the input buffer.  Note
				that there are substantial restrictions on the use of suspension --- see
				the documentation.

				When suspending, the decompressor will back up to a convenient restart point
				(typically the start of the current MCU). next_input_byte & bytes_in_buffer
				indicate where the restart point will be if the current call returns FALSE.
				Data beyond this point must be rescanned after resumption, so move it to
				the front of the buffer rather than discarding it.

********************************************************************************************/
libJPEG::boolean JPEGDataSource::FillInputBuffer (libJPEG::j_decompress_ptr cinfo)
{
	JPEGDataSource* pThis = (JPEGDataSource*)cinfo->src;
	CCFile* pFile = pThis->m_pInputFile;

	if (pFile->bad())
	{
		JPEGErrorManager* pError = (JPEGErrorManager*)cinfo->err;
		pError->ThrowError(_R(IDE_FILEREADERROR));
	}

	size_t start = pFile->tellIn();
	pFile->read(pThis->m_pBuffer, INPUT_BUF_SIZE);
	size_t nbytes = pFile->tellIn() - start;
	if (nbytes < INPUT_BUF_SIZE)
	{
		// For some reason trying to read too many bytes from a CCFile sets the stream bad
		// so don't let it stick some absurd message up
		Error::ClearError();
		// & clear any eof signal
		pFile->SetGoodState();
	}
	if (nbytes <= 0)
	{
		if (pThis->m_bStartOfFile)	// Treat empty input file as fatal error
		{
			using namespace libJPEG;
			ERREXIT(cinfo, JERR_INPUT_EMPTY);
		}
		
		using namespace libJPEG;
		WARNMS(cinfo, JWRN_JPEG_EOF);
		// Insert a fake EOI marker
		pThis->m_pBuffer[0] = (JOCTET) 0xFF;
		pThis->m_pBuffer[1] = (JOCTET) JPEG_EOI;
		nbytes = 2;
	}

	pThis->next_input_byte = pThis->m_pBuffer;
	pThis->bytes_in_buffer = nbytes;
	pThis->m_bStartOfFile = FALSE;

	return TRUE;
}


/********************************************************************************************

>	void JPEGDataSource::SkipInputData(j_decompress_ptr cinfo, INT32 num_bytes)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/08/96
	Inputs:		cinfo : a pointer to a j_decompress_ptr provided by the IJG routines
	Purpose:	Overrides the standard implementation using stdio with a CCFile version.
				Skip data --- used to skip over a potentially large amount of
				uninteresting data (such as an APPn marker).

				Writers of suspendable-input applications must note that skip_input_data
				is not granted the right to give a suspension return.  If the skip extends
				beyond the data currently in the buffer, the buffer can be marked empty so
				that the next read will cause a fill_input_buffer call that can suspend.
				Arranging for additional bytes to be discarded before reloading the input
				buffer is the application writer's problem.

********************************************************************************************/
void JPEGDataSource::SkipInputData(libJPEG::j_decompress_ptr cinfo, long /*TYPENOTE: Correct*/ num_bytes)
{
	JPEGDataSource* pThis = (JPEGDataSource*)cinfo->src;
  /* Just a dumb implementation for now.  Could use fseek() except
   * it doesn't work on pipes.  Not clear that being smart is worth
   * any trouble anyway --- large skips are infrequent.
   */
	if (num_bytes > 0)
	{
		while (num_bytes > (INT32) pThis->bytes_in_buffer)
		{
			num_bytes -= (INT32) pThis->bytes_in_buffer;
			(void)FillInputBuffer(cinfo);
			/* note we assume that fill_input_buffer will never return FALSE,
			* so suspension need not be handled.
			*/
		}
		pThis->next_input_byte += (size_t) num_bytes;
		pThis->bytes_in_buffer -= (size_t) num_bytes;
	}
}



/********************************************************************************************

>	void JPEGDataSource::SkipInputData(j_decompress_ptr cinfo, INT32 num_bytes)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/08/96
	Inputs:		cinfo : a pointer to a j_decompress_ptr provided by the IJG routines
	Purpose:	Overrides the standard implementation using stdio with a CCFile version.
				The following extract from the IJG library explains its purpose:
				Terminate source --- called by jpeg_finish_decompress
				after all data has been read.  Often a no-op.

				NB: *not* called by jpeg_abort or jpeg_destroy; surrounding
				application must deal with any cleanup that should happen even
				for error exit.

********************************************************************************************/
void JPEGDataSource::TerminateSource(libJPEG::j_decompress_ptr cinfo)
{
//	JPEGDataSource* pThis = (JPEGDataSource*)cinfo->src;
  /* no work necessary here */
}

