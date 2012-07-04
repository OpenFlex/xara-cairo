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


#include "camtypes.h"
//#include <afxwin.h>
#include <iostream>
//#include "gcmaths.h"
#include "gcache.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

CamCache::CamCache( size_t Size, UINT32 Log2MaxEntries )
{
	HashTableSize = 1<<Log2MaxEntries ;
	HashTableMask = HashTableSize-1 ;
	HashTable	  = NULL ;
	CacheStart	  = NULL ;

	HashTable	= new ( CacheBlock* [HashTableSize] ) ;
	CacheStart	= (CacheBlock*) new BYTE[Size+2*FreeCacheBlockSize] ;

	if (!HashTable || !CacheStart)
	{
		if (HashTable)
		{
			delete [] HashTable  ; HashTable  = NULL ;
		}
		if (CacheStart)
		{
			delete [] CacheStart ; CacheStart = NULL ;
		}
		return ;
	}
	for ( size_t i=0 ; i<HashTableSize ; i++ )
		HashTable[i] = NULL ;
	CacheBlock *FreeBlock ;
	FreeBlock	= (CacheBlock*) ((BYTE*)CacheStart+FreeCacheBlockSize) ;
	CacheEnd	= (CacheBlock*) ((BYTE*)CacheStart+Size-FreeCacheBlockSize) ;
	CacheStart->Prev		= CacheStart ;
							  CacheEnd->Next		= CacheEnd ;
	CacheStart->Next		= CacheEnd->Prev		=
	CacheStart->NextFree 	= CacheEnd->PrevFree	= FreeBlock ;
	CacheStart->PrevFree 	= CacheEnd->NextFree	= NULL ;
	CacheStart->State		= CacheEnd->State		= 0 ;
	FreeBlock->Prev			= FreeBlock->PrevFree	= CacheStart ;
	FreeBlock->Next			= FreeBlock->NextFree	= CacheEnd ;
	FreeBlock->State		= FREE ;
	LeastUsed = MostUsed = NULL ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// Verify should be used after creation of a CamCache object to ensure that it was created OK.
//
BOOL CamCache::Verify()
{
	return HashTable && CacheStart ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

CamCache::~CamCache()
{
	delete [] HashTable  ; HashTable  = NULL ;
	delete [] CacheStart ; CacheStart = NULL ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CamCache::FindPath( UINT32 Handle, INT32* &Points, BYTE* &Types, UINT32 &Length )
{
	INT32 *Object = (INT32*) FindEntry( Handle ) ;
	if ( Object )
	{
		Length = *Object ;
		Points = ++Object ;
		Types = (BYTE*) (Object+2*Length) ;
	}
	return Object!=NULL ;
}

void CamCache::AddPath( UINT32 Handle, INT32* Points, BYTE* Types, UINT32 Length )
{
	INT32 *DPtr = (INT32*) AddEntry( Handle,Length*9+4 ) ;
	*DPtr++ = Length ;
	INT32 *SPtr = Points ;
	size_t i;
	for ( i=0 ; i<2*Length ; i++ )
		*DPtr++ = *SPtr++ ;
	SPtr = (INT32*) Types ;
	Length = (Length+3)>>2 ;					/* Word length */
	for ( i=0 ; i<Length ; i++ )
		*DPtr++ = *SPtr++ ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

PORTNOTE("other","not used - removed because AddString looks dodgy")
#ifndef EXCLUDE_FROM_XARALX

char* CamCache::FindString( UINT32 Handle )
{
	return (char*) FindEntry( Handle ) ;
}

void CamCache::AddString( UINT32 Handle, char* String )
{
	size_t StringLength = cc_strlenBytes(String)+1 ;	/* Byte length */
	INT32 *SPtr = (INT32*) String ;
	INT32 *DPtr = (INT32*) AddEntry( Handle,StringLength ) ;
	StringLength = (StringLength+3)>>2 ;		/* Word length */
	for ( size_t i=0 ; i<StringLength ; i++ )
		*DPtr++ = *SPtr++ ;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

// converted from asm function in gcmaths
UINT32 Hash(UINT32 val)
{
	val ^= (val <<  7) | (val >> 25);
	val ^= (val << 11) | (val >> 21);
	val ^= (val << 19) | (val >> 13);
	val ^= (val << 16) | (val >> 16);
	return val;
}

void* CamCache::FindEntry( UINT32 Handle )
{
	UINT32 HashIndex = Hash( Handle ) & HashTableMask ;
	CacheBlock *Ptr = HashTable[HashIndex] ;
	while ( Ptr )
		if ( Ptr->Handle == Handle )
		{
			if ( Ptr != MostUsed )
			{
				/* Make this the most recently used object */
				if ( Ptr==LeastUsed )
					LeastUsed = Ptr->NextUsed ;
				else
					Ptr->PrevUsed->NextUsed = Ptr->NextUsed ;
				Ptr->NextUsed->PrevUsed = Ptr->PrevUsed ;
				Ptr->NextUsed = NULL ;
				Ptr->PrevUsed = MostUsed ;
				MostUsed->NextUsed = Ptr ;
				MostUsed = Ptr ;
			}
			return Ptr->Object ;
		}
		else
			Ptr = Ptr->Link ;

	return NULL ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void* CamCache::AddEntry( UINT32 Handle, size_t ObjectSize )
{
	UINT32 HashIndex = Hash( Handle ) & HashTableMask ;
	CacheBlock *Ptr = HashTable[HashIndex] ;
	while ( Ptr )
		if ( Ptr->Handle == Handle )
			return Ptr->Object ;					/* Entry already exists */
		else
			Ptr = Ptr->Link ;
	CacheBlock *FreeBlock = CacheStart->NextFree ;
	size_t ObjectBlockSize = (ObjectSize+UsedCacheBlockSize+3) & ~3 ;
	while ( ObjectBlockSize > BlockSize(FreeBlock) )
		if ( !(FreeBlock=FreeBlock->NextFree) )
		{
			/* Remove least recently used object from hash table */
			UINT32 HashIndex = Hash( LeastUsed->Handle ) & HashTableMask ;
			CacheBlock *Ptr = HashTable[HashIndex] ;
			if ( Ptr == LeastUsed )
				HashTable[HashIndex] = LeastUsed->Link ;
			else
			{
				while ( Ptr->Link != LeastUsed )
					Ptr = Ptr->Link ;
				Ptr->Link = LeastUsed->Link ;
			}				
			/* Merge least recently used object with adjacent free blocks and try again */
			FreeBlock = LeastUsed ;
			LeastUsed = LeastUsed->NextUsed ;
			LeastUsed->PrevUsed = NULL ;
			FreeBlock->State = FREE ;
			CacheStart->NextFree->PrevFree = FreeBlock ;
			FreeBlock->NextFree = CacheStart->NextFree ;
			FreeBlock->PrevFree = CacheStart ;
			CacheStart->NextFree = FreeBlock ;
			CacheBlock *NextBlock = FreeBlock->Next ;
			CacheBlock *PrevBlock = FreeBlock->Prev ;
			if ( NextBlock->State == FREE )
			{
				NextBlock->PrevFree->NextFree = NextBlock->NextFree ;
				NextBlock->NextFree->PrevFree = NextBlock->PrevFree ;
				FreeBlock->Next = NextBlock->Next ;
				NextBlock->Next->Prev = FreeBlock ;
			}
			if ( PrevBlock->State == FREE )
			{
				FreeBlock->PrevFree->NextFree = FreeBlock->NextFree ;
				FreeBlock->NextFree->PrevFree = FreeBlock->PrevFree ;
				PrevBlock->Next = FreeBlock->Next ;
				FreeBlock->Next->Prev = PrevBlock ;
				FreeBlock = PrevBlock ;
			}
		}
	/* Add object */
	if ( ObjectBlockSize+FreeCacheBlockSize > BlockSize(FreeBlock) )
	{
		FreeBlock->PrevFree->NextFree = FreeBlock->NextFree ;
		FreeBlock->NextFree->PrevFree = FreeBlock->PrevFree ;
	}
	else
	{
		CacheBlock *NewBlock = (CacheBlock*) ((BYTE*)FreeBlock+ObjectBlockSize) ;
		NewBlock->Prev		= FreeBlock ;
		NewBlock->Next		= FreeBlock->Next ;
		NewBlock->State		= FREE ;
		NewBlock->NextFree	= FreeBlock->NextFree ;
		NewBlock->PrevFree	= FreeBlock->PrevFree ;
		NewBlock->NextFree->PrevFree = NewBlock->PrevFree->NextFree = NewBlock ;
		FreeBlock->Next		= NewBlock->Next->Prev = NewBlock ;
	}
	FreeBlock->Link		= HashTable[HashIndex] ;
	FreeBlock->PrevUsed	= MostUsed ;
	FreeBlock->NextUsed	= NULL ;
	FreeBlock->Handle	= Handle ;
	HashTable[HashIndex] = FreeBlock ;
	if ( MostUsed )
		MostUsed->NextUsed = FreeBlock ;
	MostUsed = FreeBlock ;
	if ( !LeastUsed )
		LeastUsed = FreeBlock ;
	return FreeBlock->Object ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG

ostream& operator << ( ostream& os, CamCache& Cache )
{
	for ( size_t i=0 ; i<Cache.HashTableSize ; i++ )
	{
		os << Cache.HashTable[i] << " " ;
		if ( (i & 7) == 7 )
			os << endl ;
	}
	os << "Start : " << Cache.CacheStart
					 << ", " << Cache.CacheStart->Prev	   << "," << Cache.CacheStart->Next
					 << ", " << Cache.CacheStart->PrevFree << "," << Cache.CacheStart->NextFree << endl ;
	CacheBlock *Ptr = Cache.CacheStart->Next ;
	while ( Ptr != Cache.CacheEnd )
	{
		if ( Ptr->State == FREE )
			cout << "FREE  : " << Ptr << ", " << Ptr->Prev	   << "," << Ptr->Next
									  << ", " << Ptr->PrevFree << "," << Ptr->NextFree
									  << " (" << hex
									  << Cache.BlockSize(Ptr)-FreeCacheBlockSize
									  << dec << ")" << endl ;
		else
			cout << "USED  : " << Ptr << ", " << Ptr->Prev	   << "," << Ptr->Next
									  << ", " << Ptr->PrevUsed << "," << Ptr->NextUsed
									  << ", " << Ptr->Link	   << "," << Ptr->Handle
									  << ", " << (char*) Ptr->Object << " (" << hex
#ifndef EXCLUDE_FROM_XARALX
									  << Cache.BlockSize(Ptr)-UsedCacheBlockSize-cc_strlenBytes((char*)Ptr->Object)-1
#endif
									  << dec << ")" << endl ;
		Ptr = Ptr->Next ;
	}
	os << "End   : " << Cache.CacheEnd
				     << ", " << Cache.CacheEnd->Prev	 << "," << Cache.CacheEnd->Next
				     << ", " << Cache.CacheEnd->PrevFree << "," << Cache.CacheEnd->NextFree << endl ;
	os << "LeastUsed : " << Cache.LeastUsed << endl ;
	os << " MostUsed : " << Cache. MostUsed << endl ;
	return os ;
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////
