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

#ifndef INC_FILEFORM
#define INC_FILEFORM

typedef UINT32 OFFSET;	// get rid of this

/********************************************************************************************

>	class FileFormat : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/11/96
	Purpose:	Dabbling with filters

********************************************************************************************/
class FileFormat : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(FileFormat)

public:
	FileFormat(const StringBase& Name);

	typedef INT32 COMPATIBILITY;

//	virtual COMPATIBILITY	HowCompatible(const ADDR pBytes, OFFSET Size) const = 0;
//	virtual UINT32			BytesRequiredForMatch() const = 0;

//	virtual BOOL			IsLossy(const ADDR pBytes, OFFSET Size) const = 0;

	// Data member access functions
	BOOL				SetName(const StringBase& Name);
	const StringBase&	GetName() const		{	return m_Name;	}

protected:
	String_256	m_Name;


};


inline FileFormat::FileFormat(const StringBase& Name)
{
	SetName(Name);
}


inline BOOL FileFormat::SetName(const StringBase& Name)
{
	m_Name = Name;
	return TRUE;
}


#endif	// INC_FILEFORM
