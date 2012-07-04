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


CONST UINT32 FREE = 0xffffffff ;

struct CacheBlock {
	CacheBlock	*Prev ;
	CacheBlock	*Next ;
	union {
		struct {
			CacheBlock	*PrevFree ;
			CacheBlock	*NextFree ;
			UINT32		State ;
		} ;
		struct {
			CacheBlock	*PrevUsed ;
			CacheBlock	*NextUsed ;
			CacheBlock	*Link ;
			UINT32		Handle ;
			INT32		Object[1] ;
		} ;
	} ;
} ;

// For some reason the size of Object[] is not included in the latter calc, presumably because
// it's not really of size[1] - AMB
const size_t FreeCacheBlockSize = 4 * sizeof(CacheBlock *) + sizeof (UINT32) ;
const size_t UsedCacheBlockSize = 5 * sizeof(CacheBlock *) + sizeof (UINT32) ;

/////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************************************
// Gavin's original defaults
//GCache( size_t Size = 0x40000, UINT32 Log2MaxEntries = 12 ) ;

// The size of the cache is 128k, average character size = 1k, We allow a maximum of 1K entries
//GCache( size_t Size = 0x20000, UINT32 Log2MaxEntries = 10 ) ;


	Size specifies the byte size of the cache. Log2MaxEntries specifes the number of entries in
	the hash table. Note that the cache will still work even if there are more characters than
	the size of the hash table.

BOOL Verify() ;
	This will return TRUE if the cache is in use. Use after construction to ensure that
	construction succeeded.

BOOL FindPath( UINT32 Handle, INT32* &Points, BYTE* &Types, UINT32 &Length ) ;

	Searches for the given handle. If found it returns TRUE and returns the associated path in
	Points, Types and Length, else it returns FALSE.

void AddPath( UINT32 Handle, INT32*  Points, BYTE*  Types, UINT32  Length ) ;

	Stores the given path in the cache using the specified handle.

char* FindString( UINT32 Handle ) ;

	Searches for the given handle. If found it returns the string associated with the handle,
	else it returns FALSE.

void  AddString( UINT32 Handle, char* String ) ;

	Stores the given string in the cache using the specified handle.

************************************************************************************************/

class CamCache
{
#ifdef _DEBUG
	friend ostream& operator << ( ostream& os, CamCache& Cache ) ;
#endif

public:
	CamCache( size_t Size = 0x40000, UINT32 Log2MaxEntries = 12 ) ;
	~CamCache() ;
	BOOL Verify() ;

	BOOL FindPath( UINT32 Handle, INT32* &Points, BYTE* &Types, UINT32 &Length ) ;
	void  AddPath( UINT32 Handle, INT32*  Points, BYTE*  Types, UINT32  Length ) ;

	char* FindString( UINT32 Handle ) ;
	void   AddString( UINT32 Handle, char* String ) ;

private:
	size_t		HashTableSize ;
	UINT32		HashTableMask ;
	CacheBlock	**HashTable ;

	CacheBlock	*CacheStart ;
	CacheBlock	*CacheEnd ;

	CacheBlock	*LeastUsed ;
	CacheBlock	*MostUsed ;

	void* FindEntry( UINT32 Handle ) ;
	void*  AddEntry( UINT32 Handle, size_t ObjectSize ) ;

	inline size_t BlockSize( CacheBlock* Block )
	{
		return (size_t)((BYTE*)Block->Next-(BYTE*)Block) ;
	} ;
} ;

/////////////////////////////////////////////////////////////////////////////////////////////////
