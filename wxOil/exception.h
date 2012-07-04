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


// The ScreenView class - subclass of CamView used for screen display.

#ifndef INC_EXCEPTION
#define INC_EXCEPTION

class CMemoryException
{
};

class CFileException
{
protected:
	INT32					m_nErrCode;

public:
	CFileException( INT32 nErrCode ) : m_nErrCode( nErrCode )
	{
	}
};

#endif//INC_EXCEPTION
