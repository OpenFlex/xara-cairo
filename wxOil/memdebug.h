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


#ifndef INC_MEMDEBUG
#define INC_MEMDEBUG

// TODO reporting macros
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOCMSG__ __FILE__ "("__STR1__(__LINE__)") : Port Message: "
#define __LOCWRN__ __FILE__ "("__STR1__(__LINE__)") : Warning: "

#define THIS_FILE		__FILE__

#if defined(__WXMSW__)

#include <crtdbg.h>

//  The debug memory tracking system (see afxmem.cpp for derivation of windows code)
// Don't complain that this is using malloc/free so opening, so does MFC! 
#if defined(_DEBUG)
inline void *operator new( size_t nSize, LPCSTR pszFile, INT32 nLine )
{
	return _malloc_dbg( nSize, _NORMAL_BLOCK, pszFile, nLine );
}

inline void operator delete(void* p, LPCSTR lpszFileName, INT32 nLine)
{
	_free_dbg( p, _NORMAL_BLOCK );
}
#endif

inline bool IsValidAddress( const void* p, size_t nBytes,
	BOOL bReadWrite = TRUE )
{
#if defined(_DEBUG)
	return ((p != NULL) && !IsBadReadPtr(p, nBytes) &&
		(!bReadWrite || !IsBadWritePtr(const_cast<LPVOID>(p), nBytes)));
#else
	nBytes,bReadWrite;
	return (p != NULL);
#endif
}

#elif defined(__WXGTK__)

#define _set_new_handler	set_new_handler
typedef void (*_PNH)( void );

// The debug memory tracking system
#if defined(_DEBUG)
inline void *operator new( size_t nSize, LPCSTR pszFile, INT32 nLine )
{
	return operator new( nSize );
}

inline void *operator new[]( size_t nSize, LPCSTR pszFile, INT32 nLine )
{
	return operator new[]( nSize );
}
#endif

inline bool IsValidAddress( const void* p, size_t nBytes,
	BOOL bReadWrite = TRUE )
{
	return true;
}

#elif defined(__WXMAC__)

PORTNOTE("MacPort", "Memory tracking is disabled on the Mac")
#define _set_new_handler	set_new_handler
typedef void (*_PNH)( void );

// The debug memory tracking system
//#if defined(_DEBUG)
//inline void *operator new( size_t nSize, LPCSTR pszFile, INT32 nLine )
//{
//	return operator new( nSize );
//}
//
//inline void *operator new[]( size_t nSize, LPCSTR pszFile, INT32 nLine )
//{
//	return operator new[]( nSize );
//}
//#endif

inline bool IsValidAddress( const void* p, size_t nBytes,
	BOOL bReadWrite = TRUE )
{
	return true;
}

#else
#pragma error( "wxCamelot is not supported on your platform" )
#endif

#endif
