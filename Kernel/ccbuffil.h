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

#ifndef INC_CCBUFFIL
#define INC_CCBUFFIL


/********************************************************************************************

>	class CCBufferFile : public CCStreamFile

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/08/96
	Purpose:	Provides a CCStreamFile which can fills two buffer's simultaneously on
				reading: one is the working buffer (passed to read()), the other is an
				accumulative buffer (passed in init()).
				This provides a useful interface with which to fill BitmapSource's
	Notes:		The current implementation follows iostream's handling of eof() and
				provides only a read() member to fill the buffers.

********************************************************************************************/

class CCAPI CCBufferFile : public CCStreamFile
{                             
	CC_DECLARE_DYNAMIC(CCBufferFile);

public:  
	CCBufferFile(CCLexFile* pFile, BOOL bReportErrors = FALSE, BOOL bThrowExceptions = FALSE);
	// Second half of two part constructor
	virtual void	init(BYTE* pBuffer, FilePos size);

	virtual ~CCBufferFile();

	// Implementation of pure functions	                                   
	virtual BOOL	setMode(INT32 fileMode = ios::binary);

	// Overridden functions
	virtual CCFile&	read(void* pBuffer, UINT32 length = 1);
	virtual CCFile&	write(const void* pBuffer, UINT32 length = 1);

//	virtual BOOL	bad() const;
//	virtual BOOL	fail() const;

	BOOL			IsAllWritten() const;

	enum
	{
		DEFAULT_BUFSIZ = BUFSIZ
	};

protected:
	// Given buffer management members
	ADDR	m_pBuffer;

	ADDR	m_pBufferFillPosition;
	OFFSET	m_BytesToFillBuffer;

	ADDR	m_pBufferWritePosition;
	OFFSET	m_BytesToWrite;
	
	CCLexFile*	m_pTrueFile;
};


#endif	// INC_CCBUFFIL


