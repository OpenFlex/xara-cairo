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


#include "camtypes.h"

#include "ccbhfile.h"	// include the translating file proxy
//#include "tim.h"		// For error IDs

//-----------------------------------------------

CC_IMPLEMENT_DYNAMIC(CCBinHexFile, CCLexFile);

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW


/********************************************************************************************

>	virtual CCFile& CCBinHexFile::write(const void *buf, UINT32 length = 1)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/07/97
	Inputs:		buf - pointer to buffer to write
				length - number of bytes to write
	Purpose:	Writes the buffer to the file

********************************************************************************************/

CCFile& CCBinHexFile::write(const void *buf, UINT32 length)
{
	// Number of bytes we can translate in one go (half the buffer)
	UINT32 Blocklen = BinHexMaxLineLength / 2;
	UINT32 Index;
	char* pPtr;
	BYTE* pSrc = (BYTE*)buf;
	BOOL bCRLF = (length > Blocklen);

	while (length > 0)
	{
		if (Blocklen > length)
			Blocklen = length;

		if (bCRLF)
		{
			if (m_pFile->write("\r\n", 2).fail())
			{
				GotError(_R(IDE_FILE_WRITE_ERROR));
				break;
			}
		}

		pPtr = (char*)m_Buffer;

		for (Index = 0; Index < Blocklen; Index++)
		{
			ByteToHex(*pSrc, pPtr);
			pSrc += 1;
			pPtr += 2;
		}

		if (m_pFile->write(m_Buffer, Blocklen * 2).fail())
		{
			GotError(_R(IDE_FILE_WRITE_ERROR));
			break;
		}

		length -= Blocklen;
	}

	return(*this);
}


/********************************************************************************************

>	virtual CCFile& CCBinHexFile::write(const StringBase& buf, UINT32 length = 0)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/07/97
	Inputs:		buf - string reference to write
				length - number of characters to write
	Purpose:	Writes the buffer to the file

********************************************************************************************/

CCFile& CCBinHexFile::write(const StringBase& buf, UINT32 length)
{
	if (length == 0)
		length = buf.Length();


#if 0 != wxUSE_UNICODE
	size_t				cchTCSrc = camWcstombs( NULL, (const TCHAR *)buf, 0 ) + 1;
	PSTR				pTCSrc = PSTR( alloca( cchTCSrc ) );
	camWcstombs( pTCSrc, (const TCHAR *)buf, cchTCSrc );
#else
	const char* pTCSrc = buf;
#endif

	const char* pSrc = (const char*) pTCSrc;
	
	// Number of chars we can translate in one go (max half of buffer size)
	UINT32 Blocklen = BinHexMaxLineLength / 2;
	UINT32 Index;
	char* pPtr;
	BOOL bCRLF = (length > Blocklen);

	while (length > 0)
	{
		if (Blocklen > length)
			Blocklen = length;

		if (bCRLF)
		{
			if (m_pFile->write("\r\n", 2).fail())
			{
				GotError(_R(IDE_FILE_WRITE_ERROR));
				break;
			}
		}

		pPtr = (char*)m_Buffer;

		for (Index = 0; Index < Blocklen; Index++)
		{
			ByteToHex(*pSrc, pPtr);
			pSrc += 1;
			pPtr += 2;
		}

		if (m_pFile->write(m_Buffer, Blocklen * 2).fail())
		{
			GotError(_R(IDE_FILE_WRITE_ERROR));
			break;
		}

		length -= Blocklen;
	}

	return(*this);
}


/********************************************************************************************

>	void CCBinHexFile::ByteToHex(BYTE b, char* pPtr)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/07/97
	Inputs:		b - byte to convert
	Outputs:	pPtr - pointer to at least two characters
	Purpose:	Translates the byte to hex (always writes two chars)

********************************************************************************************/

void CCBinHexFile::ByteToHex(BYTE b, char* pPtr)
{
	char nibble = (b >> 4);
	if (nibble > 9)
		nibble += 55;		// ('A' - 10)
	else
		nibble += '0';
	pPtr[0] = nibble;
	nibble = b & 0xF;
	if (nibble > 9)
		nibble += 55;		// ('A' - 10)
	else
		nibble += '0';
	pPtr[1] = nibble;
}




/********************************************************************************************

>	virtual CCFile& CCBinHexFile::write(char& buf)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/07/97
	Inputs:		buf - char reference???
	Purpose:	Writes the char to the file

********************************************************************************************/


CCFile& CCBinHexFile::write(char& buf)
{
	char Trans[2];

	ByteToHex((BYTE)buf, Trans);
	
	return(m_pFile->write(Trans, 2));
}
