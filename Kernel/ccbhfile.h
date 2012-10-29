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


#ifndef INC_CCBHFILE
#define INC_CCBHFILE


const UINT32 BinHexMaxLineLength = 100;

/********************************************************************************************

>	class CCBinHexFile : public CCLexFile

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/97
	Base Class:	CCLexFile
	Purpose:	Translates data from binary to BinHex format.

	Notes:		This class only checks pCCFile in debug builds

********************************************************************************************/

class CCBinHexFile : public CCLexFile
{                                   
	CC_DECLARE_DYNAMIC(CCBinHexFile);
public:
	// Constructor with default parameters 
	CCBinHexFile(CCLexFile* pCCFile, BOOL ErrorReporting = TRUE, BOOL ExceptionThrowing = FALSE)
		: CCLexFile(ErrorReporting, ExceptionThrowing), m_pFile(pCCFile) { /* empty */ };
	virtual ~CCBinHexFile() { /* empty */ }
	
	// Switch between text and binary modes.
	virtual BOOL  setMode(INT32 fileMode = 0)
	{
		return(m_pFile->setMode(fileMode));
	};

	// Check if the file is open or not.
	virtual BOOL  	 isOpen() const { return(m_pFile->isOpen()); };

	// File pointer access/control.
	virtual CCFile&	 seekIn(FilePos Pos) { return(m_pFile->seekIn(Pos)); };
	virtual CCFile&	 seekIn(INT32 Offset, ios::seekdir Dir)
	{
		return(m_pFile->seekIn(Offset, Dir));
	};
	virtual FilePos  tellIn() { return(m_pFile->tellIn()); };
	virtual CCFile&	 seek(FilePos pos) { return(m_pFile->seek(pos)); };
	virtual FilePos	 tell() { return(m_pFile->tell()); };

	// Read functions.
	virtual CCFile&  read(void *buf, UINT32 length = 1)
	{
		return(m_pFile->read(buf, length));
	};
	virtual CCFile&  read(StringBase *buf)
	{
		return(m_pFile->read(buf));
	};
	virtual CCFile&  read(char& buf)
	{
		return(m_pFile->read(buf));
	};
	                                
	// Write functions.
	virtual CCFile&  write(const void *buf, UINT32 length = 1);
	virtual CCFile&  write(const StringBase& buf, UINT32 length = 0);
	virtual CCFile&  write(char& buf);

	// Get the size of an open file in bytes.
	virtual size_t   Size() { return(m_pFile->Size()); };

	// Status functions.
	virtual BOOL     eof() const { return(m_pFile->eof()); };

	// Close the file.
    virtual void     close() { m_pFile->close(); };

	// Non-pure status functions.
	virtual BOOL     good() const { return(m_pFile->good()); };
	virtual BOOL     bad() const { return(m_pFile->bad()); };
	virtual BOOL     fail() const { return(m_pFile->fail()); };

	// Pure status setting functions.
	virtual void	SetBadState() { m_pFile->SetBadState(); };
	virtual void	SetGoodState() { m_pFile->SetGoodState(); };

	// Allows access to the underlying fstream, is so required.
	// Mainly required for PNG/ZLib bits
	// All non-disk file classes just return NULL
	virtual iostream* GetIOFile() { return(m_pFile->GetIOFile()); };

	// Flush the file object's buffer (if any).
	virtual CCFile&	 flush() { return(m_pFile->flush()); };

	// Get access to the file descriptor or handle for the file
	virtual filedesc GetFileHandle() const { return(m_pFile->GetFileHandle()); };

	// Allow setting of compression of output data
	virtual BOOL IsCompressionSet( ) { return(FALSE); };
	virtual BOOL SetCompression( BOOL ) { return(FALSE); };

	virtual BOOL InitCompression(BOOL Header = FALSE) { return(TRUE); };
	virtual BOOL StartCompression() { return(TRUE); };
	virtual BOOL StopCompression() { return(TRUE); };

protected:
	void ByteToHex(BYTE b, char* pPtr);

protected:
	CCLexFile* m_pFile;

	BYTE m_Buffer[BinHexMaxLineLength];
};

#endif	// INC_CCBHFILE
