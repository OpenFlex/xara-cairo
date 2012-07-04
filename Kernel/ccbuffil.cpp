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
#include "bmpsrc.h"		// for OFFSET - put it in camtypes!
#include "ccbuffil.h"


// Place any IMPLEMENT type statements here
CC_IMPLEMENT_DYNAMIC(CCBufferFile, CCStreamFile)


// Declare smart memory handling in Debug builds
// We want better memory tracking
#define new CAM_DEBUG_NEW


// Functions follow

/********************************************************************************************

>	CCBufferFile::CCBufferFile(CCLexFile* pFile, BOOL bReportErrors, BOOL bThrowExceptions)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/08/96
	Inputs:		pFile:				A pointer to the stream to use
				bReportErrors:		See CCStreamFile for details
				bThrowExceptions:	See CCStreamFile for details
	
	Purpose:	Provides objects representing in-memory files.

	Notes:		This class is only partially implemented to provide support for BitmapSource

********************************************************************************************/
CCBufferFile::CCBufferFile(CCLexFile* pFile, BOOL bReportErrors, BOOL bThrowExceptions)
	: CCStreamFile(pFile->GetIOFile(), 0, bReportErrors, bThrowExceptions)
{
	m_pTrueFile				= pFile;

	m_pBuffer				= NULL;

	m_pBufferFillPosition	= NULL;
	m_BytesToFillBuffer		= 0;

	m_pBufferWritePosition	= NULL;
	m_BytesToWrite			= 0;
}



/********************************************************************************************

>	virtual CCBufferFile::~CCBufferFile()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/08/96
	Purpose:	Destructor - stops the base class destructor from deleting the stream we
				borrowed

********************************************************************************************/
CCBufferFile::~CCBufferFile()
{
	IOFile = NULL;
}

/********************************************************************************************

>	virtual void CCBufferFile::init(BYTE* pBuffer, FilePos size)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/08/96
	Purpose:	Initializes the buffer associated with this CCBufferFile
				Having constructed a CCBufferFile object a user can initialize the buffer
				associated with it. Useful for BitmapSources

********************************************************************************************/
void CCBufferFile::init(BYTE* pBuffer, FilePos size)
{
	m_pBuffer				= pBuffer;

	m_pBufferFillPosition	= pBuffer;
	m_BytesToFillBuffer		= size;

	m_pBufferWritePosition	= pBuffer;
	m_BytesToWrite			= size;
}


/********************************************************************************************

>	virtual BOOL CCBufferFile::setMode(INT32 fileMode)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/08/96
	Returns:	TRUE
	Purpose:	Provides dummy implementation for pure function

********************************************************************************************/
BOOL CCBufferFile::setMode(INT32 fileMode)
{
	return TRUE;
}


/********************************************************************************************

>	virtual CCFile& CCBufferFile::read(void* pBuffer, UINT32 length)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/08/96
	Returns:	A reference to this CCFile
	Purpose:	Attempts to read the given number of bytes into the given buffer while at
				the same time builds up the whole stream in the buffer given in the
				constructor or via init()
	Errors:		ERROR3 if internal buffer not initialized

********************************************************************************************/
CCFile& CCBufferFile::read(void* pBuffer, UINT32 length)
{
	// Read in as many bytes as the internal buffer can take up to a maximum of the
	// number given in length
	INT32 BytesToRead = m_BytesToFillBuffer > length ? length : m_BytesToFillBuffer;

	ERROR3IF(m_pBufferFillPosition == NULL, "m_pBufferFillPosition == NULL");

	m_pTrueFile->read((BYTE*)m_pBufferFillPosition, BytesToRead);

	// Find the number of bytes actually read
	INT32 BytesRead = IOFile->gcount();

	// Copy the read data to the given buffer if any
	if (pBuffer != NULL)
	{
		memcpy(pBuffer, m_pBufferFillPosition, BytesRead);
	}

	// Update the internal buffer details
	m_pBufferFillPosition += BytesRead;
	m_BytesToFillBuffer -= BytesRead;

	return *this;
}



/********************************************************************************************

>	virtual BOOL CCBufferFile::bad() const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/08/96
	Returns:	TRUE if the CCBufferFile is bad
				FALSE otherwise
	Purpose:	Mimics the functionality of the stream class bad() function

********************************************************************************************/
/*BOOL CCBufferFile::bad() const
{
	return IOFile->bad();
}
*/

/********************************************************************************************

>	virtual BOOL CCBufferFile::fail() const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/08/96
	Returns:	TRUE if the CCBufferFile has failed
				FALSE otherwise
	Purpose:	Mimics the functionality of the stream class fail() function

********************************************************************************************/
/*BOOL CCBufferFile::fail() const
{
	return IOFile->fail();
}
*/

/********************************************************************************************

>	CCFile& CCBufferFile::write(const void* pBuffer, UINT32 length = 1)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/08/96
	Inputs:		pBuffer : Buffer to write from. If NULL internal buffer will be used
				length : the number of bytes to write
	Returns:	A reference to this CCFile
	Purpose:	Attempts to write out the given number of bytes to the CCFile given in the
				constructor.
				Supplying a pBuffer will cause the data in the given buffer to be copied to
				the internal buffer before it is written out. If the write to file is
				unsuccessful therefore, the internal buffer can be considered corrupt (much
				as the file would be).
	Errors:		ERROR3 if internal buffer not initialized

********************************************************************************************/
CCFile& CCBufferFile::write(const void* pBuffer, UINT32 length)
{
	// Write as many bytes as the internal buffer will allow up to a maximum of the
	// number given in length
	INT32 BytesToWrite = m_BytesToWrite > length ? length : m_BytesToWrite;

	ERROR3IF(m_pBufferWritePosition == NULL, "m_pBufferWritePosition == NULL");

	if (pBuffer != NULL)
	{
		// Overwrite the data in the internal buffer with that in the given buffer
		memcpy(m_pBufferWritePosition, pBuffer, BytesToWrite);
	}
	// Write out whatever's in that position
	m_pTrueFile->write((BYTE*)m_pBufferWritePosition, BytesToWrite);
		

	// Update the internal buffer details
	m_pBufferWritePosition += BytesToWrite;
	m_BytesToWrite -= BytesToWrite;

	return *this;
}


/********************************************************************************************

>	BOOL CCBufferFile::IsAllWritten() const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/08/96
	Returns:	TRUE : if all bytes in the buffer have been written
				FALSE : otherwise
	Purpose:	Determines whether write() has been called sufficiently often to have
				written out the whole buffer.

********************************************************************************************/
BOOL CCBufferFile::IsAllWritten() const
{
	return (m_BytesToWrite == 0);
}
