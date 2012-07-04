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
#include "bmpsrc.h"
#include "ccbuffil.h"


// Place any IMPLEMENT type statements here
CC_IMPLEMENT_MEMDUMP(BitmapSource, CC_CLASS_MEMDUMP)


// Declare smart memory handling in Debug builds
// We want better memory tracking
#define new CAM_DEBUG_NEW


// Functions follow

/********************************************************************************************

>	BitmapSource::BitmapSource(OFFSET Size)
 					
 	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
 	Created:	8/8/96
 
 	Inputs:		Size :	The size of the bitmap source (usually the file size). Must be
						greater than one.
 
 	Purpose:	Constructor providing BitmapSource objects of the given size.
				We construct objects of the required size, and associate bitmaps with
				them via SetOriginalSource
 
 	SeeAlso:	KernelBitmap::SetOriginalSource
 
********************************************************************************************/
BitmapSource::BitmapSource(OFFSET Size)
{
	m_pBuffer			= NULL;
	m_nSize				= 0;
	m_ReadWritePosition	= 0;	

	if (Size > 0)
	{
		m_pBuffer	= new BYTE[Size];
		m_nSize		= Size;
	}
}


/********************************************************************************************

>	BitmapSource::~BitmapSource()
 					
 	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
 	Created:	18/08/96
 
 	Purpose:	Destructor for BitmapSource objects
 
********************************************************************************************/
BitmapSource::~BitmapSource()
{
	if (m_pBuffer != NULL)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}		
	m_nSize = 0;
}


/********************************************************************************************

>	BOOL BitmapSource::IsOK() const
 					
 	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
 	Created:	8/8/96

	Returns:	TRUE if constructor succeeded
				FALSE otherwise
 
 	Purpose:	Since the constructor can fail, this member function determines whether or
				not it was wholly successful.
				Users should always call this function after constructing BitmapSource
				objects
 
 	SeeAlso:	BitmapSource::BitmapSource(...)
 
********************************************************************************************/
BOOL BitmapSource::IsOK() const
{
	return (m_pBuffer != NULL);
}


/********************************************************************************************
 
>	virtual BOOL BitmapSource::GetByte(BYTE& byte)
 					
 	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/08/96
 
 	Outputs:	byte :	Returns the byte from the current position in the BitmapSource
 
 	Purpose:	Allows this BitmapSource to be copied elsewhere (to disk) a byte at a time.
	Notes:		SeekPos() should be called to reset the current position
	Errors:		ERROR2 if trying to read beyond the end of this BitmapSource

 
********************************************************************************************/
BOOL BitmapSource::GetByte(BYTE& byte)
{
	ERROR2IF(m_ReadWritePosition > GetSize(), FALSE, "m_ReadWritePosition > GetSize()");

	byte = m_pBuffer[m_ReadWritePosition];
	++m_ReadWritePosition;

	return TRUE;
}


/********************************************************************************************

>	virtual BOOL BitmapSource::PutByte(const BYTE byte)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/08/96

	Inputs:		byte:	a BYTE to place at the current position in this BitmapSource

	Returns:	TRUE if put succeeded
				FALSE otherwise
	Errors:		ERROR2 if trying to put after end of BitmapSource
	Purpose:	Adds a byte to this BitmapSorce object.

********************************************************************************************/
BOOL BitmapSource::PutByte(const BYTE byte)
{
	ERROR2IF(m_ReadWritePosition > GetSize(), FALSE, "m_ReadWritePosition > GetSize()");

	m_pBuffer[m_ReadWritePosition] = byte;
	++m_ReadWritePosition;

	return TRUE;
}


/********************************************************************************************

>	virtual FilePos BitmapSource::SeekPos(FilePos nPos)


	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/08/96

	Inputs:		nPos:	The position to be set

	Returns:	TRUE : if successful
				FALSE:	otherwise

	Purpose:	Sets the position in the BitmapSource at which the next GetByte/PutByte will
				occur. Usually this function will just be used to start from the beginning
				of the BitmapSource, by passing zero for nPos.

	Errors:		ERROR2 if trying to seek after the end of this BitmapSource

********************************************************************************************/
BOOL BitmapSource::SeekPos(OFFSET nPos)
{
	ERROR2IF(nPos > GetSize(), FALSE, "nPos > GetSize()");

	m_ReadWritePosition = nPos;
	return TRUE;
}


/********************************************************************************************

>	BOOL BitmapSource::AttachToBufferFile(CCBufferFile* pFile) const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/08/96

	Returns:	A pointer to a CCBufferFile object which will provide a reference to this
				BitmapSource.
				NULL is returned if an error occurred

	Purpose:	The entry points to filters need a CCFile object. This function
				provides a CCFile object which uses this BitmapSource when calling the
				CCFile member functions.
	Notes:		The returned CCFile should be destroyed using delete when no longer
				needed

********************************************************************************************/
BOOL BitmapSource::AttachToBufferFile(CCBufferFile* pFile) const
{
	ERROR3IF(!pFile->IS_KIND_OF(CCBufferFile), "pFile is not");

	pFile->init(m_pBuffer, m_nSize);

	return TRUE;
}
