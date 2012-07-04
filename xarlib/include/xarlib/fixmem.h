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


// header file for fixed memory allocator

/*
*/

#ifndef INC_FIXMEM
#define	INC_FIXMEM

// the Tuned memory manager
class TunedMemory;

#ifdef _DEBUG

	void DumpCCMallocTrace(void);

	LPVOID DebugCCMalloc( size_t Size, LPCSTR Filename, INT32 Line);
	LPVOID DebugCCRealloc( LPVOID Buf, size_t Size, LPCSTR Filename, INT32 Line);
	size_t DebugCCGetBlockSize(LPVOID Buf);
	#define CCMalloc(size) DebugCCMalloc((size), THIS_FILE, __LINE__)
	#define CCRealloc(buf, size) DebugCCRealloc((buf), (size), THIS_FILE, __LINE__)
	#define CCGetBlockSize(buf) DebugCCGetBlockSize(buf);

#else

	LPVOID RetailCCMalloc( UINT32 size );
	LPVOID RetailCCRealloc( LPVOID buf, UINT32 size );
	size_t RetailCCGetBlockSize(LPVOID Buf);

	#define CCMalloc(size) RetailCCMalloc( (size) )
	#define CCRealloc(buf, size) RetailCCRealloc((buf), (size))
	#define CCGetBlockSize(buf) RetailCCGetBlockSize(buf);

#endif	// _DEBUG

void CCFree( LPVOID buf );


#if !defined(EXCLUDE_FROM_XARLIB)
TunedMemory* GetTunedMemManager();
#endif

class CCMallocCriticalSection
{
public:
	CCMallocCriticalSection()
	{
#ifdef RALPH
		Temp = 0;
		::EnterCriticalSection(&sm_Section);
#endif
	}

	~CCMallocCriticalSection()
	{
#ifdef RALPH
		::LeaveCriticalSection(&sm_Section);
#endif
	}

	static void Init()
	{
#ifdef RALPH
		if (!sm_bInit)
		{
			::InitializeCriticalSection(&sm_Section);
			sm_bInit = TRUE;
		}
#endif
	}

	static void DeInit()
	{
#ifdef RALPH
		if (sm_bInit)
		{
			::DeleteCriticalSection(&sm_Section);
			sm_bInit = FALSE;
		}
#endif
	}


private:
	DWORD Temp;
	static CRITICAL_SECTION sm_Section;
	static BOOL sm_bInit;
};


#endif
