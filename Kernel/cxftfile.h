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


#ifndef INC_CXFTFILE
#define INC_CXFTFILE

#include "cxfile.h"

/********************************************************************************************

>	class CXaraTemplateFile : public CXaraFile

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/7/97
	Purpose:	CXaraFile derived class for handling Flare template files
				This translates the records written by the standard native format export
				into the text based format.

				It achieves this by overriding certain functions to maintain a "type list"
				of the contents of the record so it can translate it when the record is 
				written to the file.

				Streamed records also need to be translated and this is achieved by returning
				a proxy CCFile derived class (CCBinHexFile) which translates all data written
				from binary to the BinHex format (a stream of hexadecimal digits where
				each pair of digits represents a byte e.g.

				void Translate(const BYTE* pBuf, char* pStr);
				{
					for (i = 0; i < BUFSIZE; i++)
					{
						sprintf(pStr, "%02x", pBuf[i]);
						pStr += 2;
					}
				}

				(Not that it'll actually use that code, rampant as it is... 8-)

	SeeAlso:	CCBinHexFile

********************************************************************************************/


class CXaraTemplateFile : public CXaraFile
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(CXaraTemplateFile);

public:
	CXaraTemplateFile();
	virtual ~CXaraTemplateFile() { /* empty */ }

	virtual BOOL OpenToWrite(CCLexFile* pCCFile);
	virtual BOOL OpenToRead(CCLexFile* pThisCCFile);
	virtual BOOL Close(void);

	// This is overriden to return our special CCBinHexFile
	virtual CCLexFile* GetCCFile(void) const;

	virtual INT32 StartRecord(UINT32 Tag, INT32 Size);
	virtual BOOL EndRecord(void);
	virtual INT32 StartStreamedRecord(UINT32 Tag, INT32 Size);
	virtual BOOL EndStreamedRecord(UINT32 *RecordSize);
	virtual UINT32 Write(CXaraFileRecord* pRecord);	// Writes a complete record out to file
	virtual UINT32 WriteDefinitionRecord(CXaraFileRecord* pRecord);	// Writes a complete record out to file
	virtual BOOL Write(BYTE b);

	virtual BOOL StartCompression() { return(TRUE); };
	virtual BOOL StopCompression() { return(TRUE); };
	virtual BOOL IsCompressionOn() { return(FALSE); };


protected:
	// Should only be used by people who know what they are doing e.g. compression
	// Hence why it is protected
	UINT32 WriteRecordHeader(UINT32 Tag, INT32 Size);
	virtual BOOL FixStreamedRecordHeader(UINT32 *RecordSize);

protected:	
	// Functions for translating binary into text
	BOOL WriteAsText(CXaraFileRecord* pRecord);
	BOOL WriteBinHex(BYTE* pBuf, UINT32 BufSize);
	BOOL WriteLabel(void);
	BOOL IsSimpleUnicode(UINT16* pStr);
	BOOL WriteSimpleUnicode(UINT16* pStr);
	BOOL WriteSimpleASCII(char* pStr);
	UINT32 WriteMultipleWCHARs(BYTE* pTypes, DWORD Count, UINT16* pChars);
	BOOL WriteSingleWCHAR(WCHAR ch);

	inline BOOL IsPrint(WCHAR wc)
	{
		return(((wc) > 31) && ((wc) < 127));
	};

protected:
	PathName m_TempPath;
	CCDiskFile* m_pTempFile;
	CCLexFile* m_pBinHexFile;
	CCLexFile* m_pOrigCCFile;
};

#endif	// INC_CXFTFILE
