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


// class to handle large memory blocks

#ifndef INC_MEMBLK
#define INC_MEMBLK

// there are two methods we can use: Global(Re)Alloc or VirtualAlloc. Currently we use
// the former under Win16 (& Mac), the latter under Win32s.
// Under non-windows we just use malloc and friends
#if !defined(__WXMSW__)
#define	USE_STD_ALLOC	1
#define	USE_VM_BLOCKS	0
#elif defined(WIN32) && !defined(_MAC)
#define	USE_VM_BLOCKS	1
#else
#define	USE_VM_BLOCKS	0
#endif

enum MemoryBlockType						// this enum is for the type of MemoryBlock
{											// don't add anything in here without asking
	MEMORYBLOCK_HANDLETABLE,   				// Andy
	MEMORYBLOCK_RELOCHEAP,
	MEMORYBLOCK_SCREENBUFFER
};

class MemoryBlock
{
public:


	MemoryBlock();
	~MemoryBlock();

	LPVOID Init( INT32 InitSize, BOOL AutoZero, MemoryBlockType );
	void DeInit();
	BOOL Grow( UINT32 OldSize, UINT32 NewSize, LPVOID *Pointer);
	BOOL Shrink( UINT32 OldSize, UINT32 NewSize, LPVOID *Pointer);

#if USE_STD_ALLOC
	UINT32 GetRoundedSize( UINT32 RawSize )
	{
		return( ( RawSize + 4096 - 1 ) & ~4095 );
	}
#elif USE_VM_BLOCKS
	UINT32 GetRoundedSize( UINT32 RawSize )
	{
		return ( ( (RawSize+PageSize-1) / PageSize ) * PageSize );
	}
#endif

private:

#if USE_STD_ALLOC
	UINT32				m_RoundedSize;				// current alloced size, rounded up
	PVOID				m_pMemBlk;
#elif USE_VM_BLOCKS
	LPVOID MemBase;
	UINT32 RoundedSize;								// current alloced size, rounded up
	static UINT32 PageSize;
#else
	HGLOBAL MemHandle;
	BOOL AutoZero;
#endif

};

#endif
