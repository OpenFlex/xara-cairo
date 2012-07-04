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


// fixed memory allocator (used in preference to malloc/free etc)


#include "camtypes.h"
//#include "fixmem.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#include <stdlib.h>

#if defined(__FreeBSD__)
#include <malloc_np.h>
#endif

#if defined(__linux__)
#include <malloc.h>
#endif


#if !defined(EXCLUDE_FROM_XARLIB)
#include "tunemem.h"
#endif

#if defined( __WXMSW__ )
#include <new.h>
#elif defined( __WXMAC__ )
#include <new>
#endif

//#include "ralphcri.h"	// for critical sections
//#define USE_CRIT 1

#if !defined(EXCLUDE_FROM_XARLIB)
static TunedMemory TheTunedMemoryManager;
#endif

// Happy chappie critical crappy (for ralphm, threads and so forth)
CRITICAL_SECTION CCMallocCriticalSection::sm_Section;
BOOL CCMallocCriticalSection::sm_bInit = FALSE;

#define	checksize(x)	FALSE

#ifdef _DEBUG

typedef struct CCMallocList
{
	UINT32				GuardWord;
	CCMallocList	   *Next;
	CCMallocList	   *Prev;
	size_t				Size;
	void			   *Start;
	char				Filename[22];
	INT32					LineNum;
} CCMallocList;

static CCMallocList *TraceListHead = NULL;


#define	MAGIC_LONGWORD	0xDEADBEEF
#define	MAGIC_EXTRA		sizeof(CCMallocList)


#ifdef _OUTPUT_DEBUG
static INT32 TotalMalloced = 0;
#endif

/********************************************************************************************

	static void *CheckMagic( void* Block, BOOL Destroy )

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/6/94
	Inputs:		Block - pointer to memory block. If Destroy is TRUE will remove magic
				marker so detect double-freeing.
	Outputs:	None
	Returns:	Pointer before magic in block. Returns NULL if Block was null on input, or
				if the block is not recognised as one of ours.
	Purpose:	For debug builds to ensure the magic longword marker is in the block.
				If Destroy is TRUE then removes block from memory tracing list.
				Stubbed away in retail builds.
	Scope:		Static to fixmem.cpp

********************************************************************************************/

static void *CheckMagic( void* Block, BOOL Destroy )
{
	if (Block != NULL)
	{
		CCMallocList *p = (CCMallocList*)Block;

		// decrement pointer by sizeof(CCMallocList)
		p--;

		if ( p->GuardWord == MAGIC_LONGWORD )
		{
			if (Destroy)
			{
				p->GuardWord = 0xF000BAAA;						// if it was our marker then destroy it

				if (p == TraceListHead)
					TraceListHead = p->Next;

				if (p->Next != NULL)
					p->Next->Prev = p->Prev;

				if (p->Prev != NULL)
					p->Prev->Next = p->Next;
			}
		}
		else
		{
			// if marker not there then either we didn't alloc it, or it has been freed for
			// the second time
			ENSURE (FALSE, "CCFree/realloc called on memory that was not CCMalloced");
			return NULL;								// so no-one tries to use it
		}
		Block = p;										// use real address to free
	}
	return Block;
}

/********************************************************************************************

	static void *StoreMagic( void *Block , UINT32 Size , LPCSTR Filename , INT32 Line )

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com> (and Gerry)
	Created:	15/6/94
	Inputs:		Block - pointer to memory block. Stores magic longword in there.
	Outputs:	None
	Returns:	The address just past that to the caller for use by the user.
	Purpose:	For debug builds to insert magic longword marker and other memory tracing
				info in the block. Stubbed away in retail builds.
	Scope:		Static to fixmem.cpp

********************************************************************************************/

static void *StoreMagic( void *Block , size_t Size , LPCSTR Filename , INT32 Line )
{
	if (Block != NULL)
	{
		CCMallocList *p = (CCMallocList*)Block;
		p->GuardWord = MAGIC_LONGWORD;		 							// store magic

		p->Size = Size;

		// Fill in the details about the file position
		if (Filename != NULL)
		{	
			// copy the string passed in and note the line number
			size_t		Count = strlen( Filename );
			if ( Count>21 )
			{
				// The string was too long, so we have to copy just the last 22 chars in it
				Filename += Count-21;
			}

			// copy the end of the string into the space I have for it
			strcpy( p->Filename, Filename );
			p->LineNum = Line;
		}
		else
		{
			// set the fields to null values
			strcpy( p->Filename, "Unknown File" );							// Was a IDS const, but too much effort for debug
			p->LineNum = 0;
		}

		p->Start = ((char*)Block) + MAGIC_EXTRA;  							// and return user bigger pointer
		return p->Start;
	}

	return NULL;
}


/********************************************************************************************

	static void LinkMagic( void *Block )

	Author: 	Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/9/94
	Inputs:		Block - pointer to memory block.
	Outputs:	None
	Purpose:	For debug builds to link the block into the tracking list. Stubbed away in
				retail builds.
	Scope:		Static to fixmem.cpp

********************************************************************************************/

static void LinkMagic( void *Block )
{
	if (Block != NULL)
	{
		CCMallocList *p = (CCMallocList*)Block;

		p->GuardWord = MAGIC_LONGWORD;		 	// store magic word

		p->Next = TraceListHead;
		p->Prev = NULL;

		if (TraceListHead != NULL)
			TraceListHead->Prev = p;

		TraceListHead = p;
	}
}


/********************************************************************************************

>	void DumpCCMallocTrace(void)

	Author: 	Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/9/94
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Lists any unreleased memory blocks
	Errors:		None
	SeeAlso:	LinkMagic;CheckMagic;StoreMagic
	
********************************************************************************************/

void DumpCCMallocTrace(void)
{
	if (TraceListHead != NULL)
	{
		TRACE( _T("\n\n...CCMalloc leaks detected...\n\n"));

		CCMallocList *Ptr = TraceListHead;

		while (Ptr != NULL)
		{
#if 0 != wxUSE_UNICODE
			TCHAR pFilename[22];
			camMbstowcs(pFilename, Ptr->Filename, 22);
#else
			TCHAR* pFilename = Ptr->Filename;
#endif
			TRACE( _T("%ld bytes allocated in %s at line %ld\n"),Ptr->Size, pFilename, Ptr->LineNum);
			Ptr = Ptr->Next;
		}

		TRACE( _T("\n...End of CCMalloc leaks...\n\n"));
	}
}


/********************************************************************************************

>	LPVOID DebugCCMalloc(UINT32 size, LPCSTR Filename, INT32 Line)

	Author: 	Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/9/94
	Inputs:		size of block required
				source filename called from (supplied by macro)
				line number of call (supplied by macro)
	Outputs:	None
	Returns:	None
	Purpose:	A version of malloc which does not throw exceptions and provides source file
				and line number tracing.
	Errors:		Out of memory
	SeeAlso:	RetailCCMalloc;malloc

********************************************************************************************/

LPVOID DebugCCMalloc(size_t Size, LPCSTR Filename, INT32 Line)
{
#ifdef USE_CRIT
	CCMallocCriticalSection Cs;
#endif

	if (Size==0L)															// size of 0 is illegal
	{
		ENSURE(FALSE, "Someone asked for 0 bytes");
		return NULL;
	}

#ifdef _OUTPUT_DEBUG
	TotalMalloced += Size;
	TRACE( _T("Malloced %ld (+%ld in %s at line %ld)\n"),TotalMalloced,Size, Filename, Line);
#endif

	size_t				NewSize = Size + MAGIC_EXTRA;

	if (checksize(NewSize))
		return NULL;														// if too big

	// save VC++s internal fail-memory pointer and reset it so nothing special occurs
	// if memory runs out
#if !defined(__WXMAC__)
	_PNH old_handler = _set_new_handler( NULL );
#else
	new_handler pnh = set_new_handler(NULL);
#endif

	// call malloc to get the memory or a NULL pointer
	void *p = malloc( (size_t)NewSize );

	// The next line is for debug purposes (comment out above line)
	//void *p = NULL;
	
	// repair the function pointer to its old value and return our pointer
#if !defined(__WXMAC__)
	_set_new_handler( old_handler );
#else
	set_new_handler(pnh);
#endif

	// set the error and return if it didn't work
	if (p == NULL)
	{
		Error::SetError(_R(IDS_OUT_OF_MEMORY));
		return NULL;
	}

	// Link block in to list
	LinkMagic(p);

//	TRACE( _T("CCMalloc at 0x%08x (0x%08x)\n"), (char*)p + MAGIC_EXTRA, p);

	// add the magic longword
	return StoreMagic(p, Size, Filename, Line);
}


/********************************************************************************************

	void DebugCCRealloc(LPVOID Buf, UINT32 Size, LPCSTR Filename, INT32 Line)

	Author: 	Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/9/94
	Inputs:		pointer to memory allocated with CCMalloc (or NULL)
				new size for block
				source filename called from (supplied by macro)
				line number of call (supplied by macro)
	Outputs:	None
	Returns:	None
	Purpose:	A version of realloc which does not throw exceptions and provides source file
				and line number tracing.  DO NOT CALL.  Use CCRealloc instead.
	Errors:		Out of memory
	SeeAlso:	RetailCCRealloc;realloc

********************************************************************************************/

LPVOID DebugCCRealloc(LPVOID Buf, size_t Size, LPCSTR Filename, INT32 Line)
{
#ifdef USE_CRIT
	CCMallocCriticalSection Cs;
#endif

	if (Size==0L)															// size of 0 is illegal
	{
		ENSURE(FALSE, "Someone asked for 0 bytes");
		return NULL;
	}

	// check magic longword (and remove it)
	const LPVOID NewBuf = CheckMagic(Buf, TRUE);	// Unlink block and set deleted
	if (
		(NewBuf==NULL) &&
		(Buf!=NULL)
	   )
	{
		// CheckMagic decided that it wasn't one of our blocks, so don't try to grow it
		return NULL;
	}

	size_t				NewSize = Size + MAGIC_EXTRA;

	if (checksize(NewSize))
		return NULL;															// if too big

	// save VC++s internal fail-memory pointer and reset it so nothing special occurs
	// if memory runs out
#if !defined(__WXMAC__)
	_PNH old_handler = _set_new_handler( NULL );
#else
	new_handler pnh = set_new_handler(NULL);
#endif

	// call realloc 
	void *p = realloc( NewBuf, (size_t)NewSize );

	// The next line is for test purposes (comment out above line)
	//void *p = NULL;
	
	// finally repair the function pointer to its old value and return our pointer
#if !defined(__WXMAC__)
	_set_new_handler( old_handler );
#else
	set_new_handler(pnh);
#endif

	// set the error and return if it didn't work
	if (p == NULL)
	{
		Error::SetError(_R(IDS_OUT_OF_MEMORY));

		// Re-link old block into list
		LinkMagic(NewBuf);

		// return NULL as realloc
		return NULL;
	}
	else
	{
//		TRACE( _T("CCRealloc at 0x%08x (0x%08x) is now 0x%08x (0x%08x)\n"), Buf, NewBuf, (char*)p+MAGIC_EXTRA, p);
		
		// Link new block into list
		LinkMagic(p);

		// return result, storing magic word
		return StoreMagic(p, Size, Filename, Line);
	}
}



/********************************************************************************************

>	INT32 DebugCCGetBlockSize(LPVOID Block)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/95
	Inputs:		Block - the alloc'ed block we want to know the size of
	Returns:	the size of the block that was asked for
	Purpose:	Finds out how big a block of ram someone asked for when they called CCMalloc

********************************************************************************************/

size_t DebugCCGetBlockSize(LPVOID Block)
{
	// default to 0
	size_t				Size = 0;

	// make sure it is OK
	if (Block != NULL)
	{
		// Find out the size
		CCMallocList *p = (CCMallocList*) (((char*)Block)-MAGIC_EXTRA);
		Size = p->Size;
	}

	// return it
	return Size;
}


#else
// retail builds stub out those fns just in case
// the only one that is used is CheckMagic (in CCFree)
#define	CheckMagic(p,k)	(p)
#define	StoreMagic(p,s,f,l)	(p)
#define LinkMagic(p)
#define	MAGIC_EXTRA		0

/********************************************************************************************

	LPVOID RetailCCMalloc( UINT32 size )

	Author: 	Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/9/94
	Inputs:		size of memory required (must be non-zero)
	Outputs:	None
	Returns:	Pointer to new block, or NULL if failed.
	Purpose:	Like malloc but does not throw exceptions.
	Errors:		None.
	SeeAlso:	CCFree;RetailCCRealloc;malloc

********************************************************************************************/

LPVOID RetailCCMalloc( UINT32 Size )
{
#ifdef USE_CRIT
	CCMallocCriticalSection Cs;
#endif

	if (Size==0L)															// size of 0 is illegal
		return NULL;

	if (checksize(Size))
		return NULL;														// if too big

	// save VC++s internal fail-memory pointer and reset it so nothing special occurs
	// if memory runs out
#if !defined(__WXMAC__)
	_PNH old_handler = _set_new_handler( NULL );
#else
	new_handler pnh = set_new_handler(NULL);
#endif

	// call malloc to get the memory or a NULL pointer
	void *p = malloc( (size_t)Size );
	
	// repair the function pointer to its old value and return our pointer
#if !defined(__WXMAC__)
	_set_new_handler( old_handler );
#else
	set_new_handler(pnh);
#endif

	// set the error if it didn't work
	if (p == NULL)
		Error::SetError(_R(IDS_OUT_OF_MEMORY));

	return p;
}




/********************************************************************************************

	LPVOID RetailCCRealloc( LPVOID buf, UINT32 size )

	Author: 	Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/9/94
	Inputs:		Pointer to block allocated with CCMalloc (can be NULL) and new size (must be non-zero)
	Returns:	Pointer to new block (might have changed) or NULL if cannot reallocate (old block
				will remain intact)
	Purpose:	Change size of memory block, similar to realloc but does not throw exceptions.
	Errors:		None.
	SeeAlso:	RetailCCMalloc;CCFree;realloc

********************************************************************************************/

LPVOID RetailCCRealloc( LPVOID Buf, UINT32 Size )
{
#ifdef USE_CRIT
	CCMallocCriticalSection Cs;
#endif

	if (Size==0L)															// size of 0 is illegal
		return NULL;

	if (checksize(Size))
		return NULL;															// if too big

	// save VC++s internal fail-memory pointer and reset it so nothing special occurs
	// if memory runs out
#if !defined(__WXMAC__)
	_PNH old_handler = _set_new_handler( NULL );
#else
	new_handler pnh = set_new_handler(NULL);
#endif

	// call realloc
	void *p = realloc( Buf, (size_t)Size );
	
	// finally repair the function pointer to its old value and return our pointer
#if !defined(__WXMAC__)
	_set_new_handler( old_handler );
#else
	set_new_handler(pnh);
#endif

	// set the error if it didn't work
	if (p == NULL)
		Error::SetError(_R(IDS_OUT_OF_MEMORY));

	// return result, storing magic word
	return p;
}




/********************************************************************************************

>	size_t RetailCCGetBlockSize(LPVOID Block)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/95
	Inputs:		Block - the alloc'ed block we want to know the size of
	Returns:	the size of the block that was asked for
	Purpose:	Finds out how big a block of ram someone asked for when they called CCMalloc

********************************************************************************************/

size_t RetailCCGetBlockSize(LPVOID Block)
{
#ifdef USE_CRIT
	CCMallocCriticalSection Cs;
#endif

	if (Block==NULL)
		return 0;

#if defined(__OpenBSD__)
	// OpenBSD, NetBSD, do not have a function for probing the size of a
	// reference returned by malloc
	return 0;
#elif defined(__linux__) || defined(__FreeBSD__)
	return malloc_usable_size(Block);
#elif defined(__WXMAC__)
	// MacOS X
	return malloc_size(Block);
#else
	return _msize(Block);
#endif
}


#endif



/********************************************************************************************

>	LPVOID CCMalloc( UINT32 size )

	Author: 	Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/9/94
	Inputs:		size of memory required (must be non-zero)
	Outputs:	None
	Returns:	Pointer to new block, or NULL if failed.
	Purpose:	Like malloc but does not throw exceptions.
	Errors:		None.
	SeeAlso:	malloc;CCFree;CCRealloc

********************************************************************************************/
/*
Technical notes:
This has been implemented as a macro which calls either RetailCCMalloc or DebugCCMalloc
depending on whether it is a retail or debug build.

********************************************************************************************/


/********************************************************************************************

>	LPVOID CCRealloc( LPVOID buf, UINT32 size )

	Author: 	Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/9/94
	Inputs:		Pointer to block allocated with CCMalloc (can be NULL) and new size (must be non-zero)
	Returns:	Pointer to new block (might have changed) or NULL if cannot reallocate (old block
				will remain intact)
	Purpose:	Change size of memory block, similar to realloc but does not throw exceptions.
	Errors:		None.
	SeeAlso:	RetailCCMalloc;CCFree;realloc

********************************************************************************************/
/*
Technical notes:
This has been implemented as a macro which calls either RetailCCRealloc or DebugCCRealloc
depending on whether it is a retail or debug build.

********************************************************************************************/


/********************************************************************************************

>	void CCFree( LPBYTE buf )

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/10/93
	Inputs:		pointer to memory allocated with CCMalloc (or NULL)
	Outputs:	None
	Returns:	None
	Purpose:	Like free.
	Errors:		None
	SeeAlso:	CCMalloc;free

********************************************************************************************/

void CCFree( LPVOID Buf )
{
#ifdef USE_CRIT
	CCMallocCriticalSection Cs;
#endif

#ifdef _OUTPUT_DEBUG
	if (Buf)
	{
		CCMallocList* p = (CCMallocList*) Buf;
		p--;
		TotalMalloced -= p->Size;
		TRACE( _T("UnMalloced %ld (-%ld in %s at %ld)\n"),TotalMalloced, p->Size, p->Filename, p->LineNum);
	}

#endif
	// check magic longword (and remove it to find double-frees)
	Buf = CheckMagic( Buf, TRUE );

//	TRACE( _T("CCFree at 0x%08x (0x%08x)\n"), Buf, ((char*)Buf - MAGIC_EXTRA));

	// then free it
	free( Buf );
}




#if !defined(EXCLUDE_FROM_XARLIB)
/********************************************************************************************

>	TunedMemory* GetTunedMemManager()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/5/95
	Returns:	A pointer to the tuned memory manager
	Purpose:	Finds the Tuned Memory manager so that people that need to know get ask
				it for memory etc

********************************************************************************************/

TunedMemory* GetTunedMemManager()
{
	return &TheTunedMemoryManager;
}
#endif

