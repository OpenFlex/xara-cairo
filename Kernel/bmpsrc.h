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

#ifndef INC_BMPSRC
#define INC_BMPSRC

class CCBufferFile;

typedef UINT32	OFFSET;

/********************************************************************************************
 
>	class BitmapSource : public CC_CLASS_MEMDUMP
 
 	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
 	Created:	18/08/96
 	Purpose:   	Objects of this class encapsulate the original source for a bitmap.
 	Scope:		public
 
********************************************************************************************/
class BitmapSource : public CC_CLASS_MEMDUMP
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(BitmapSource);

public:
	BitmapSource(OFFSET Size);
	virtual ~BitmapSource();

	BOOL IsOK() const;

	virtual BOOL	GetByte(BYTE& byte);
	virtual BOOL	PutByte(const BYTE byte);
	virtual BOOL	SeekPos(OFFSET pos);
	BOOL			AttachToBufferFile(CCBufferFile* pFile) const;
	virtual BOOL	IsJPEG()	 { return FALSE; } 

	OFFSET			GetSize() const		{return m_nSize;}

protected:
	ADDR		m_pBuffer;
	OFFSET		m_nSize;
	OFFSET		m_ReadWritePosition;
};


class JPEGBitmapSource : public BitmapSource
{
public:
	JPEGBitmapSource(OFFSET Size) : BitmapSource(Size) {}
	virtual BOOL IsJPEG()	{ return TRUE; }
};


#endif	// INC_BMPSRC


