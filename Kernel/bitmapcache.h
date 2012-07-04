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


#if !defined(AFX_BITMAPCACHE_H__41BFBD9B_A02E_4205_AE0A_4F6A5E0DC7D0__INCLUDED_)
#define AFX_BITMAPCACHE_H__41BFBD9B_A02E_4205_AE0A_4F6A5E0DC7D0__INCLUDED_

//#include <afxtempl.h>
#include "bitmapcachekey.h"
#include "bitmap.h"

#define CACHEPRIORITY_NORMAL 0
#define CACHEPRIORITY_TEMPBITMAP_LOW 0
#define CACHEPRIORITY_TEMPBITMAP_HIGH 1000
#define CACHEPRIORITY_PERMANENT 8000


class CCachedBitmap: public CCObject
{
public:
	CCachedBitmap();
	CCachedBitmap(LPBITMAPINFO pNewInfo, LPBYTE pNewBits, INT32 nNewPriority = CACHEPRIORITY_NORMAL);
	CCachedBitmap(const CCachedBitmap& cbmp);
	CCachedBitmap(UINT32 Width, UINT32 Height, UINT32 Depth, DocRect rect, INT32 nNewPriority = CACHEPRIORITY_NORMAL);
	~CCachedBitmap();

	bool operator==(const CCachedBitmap& cbmp) const;
	const CCachedBitmap& operator=( const CCachedBitmap& cbmp );

	void			Release();
	CCachedBitmap	Copy();
	void			Transform(TransformBase& Trans);
	DocRect			GetCachedRect();
	void			SetCachedRect(DocRect r);
	void			SetCachedParallelogram(DocCoord* pCoords, UINT32 numCoords);

	BOOL			IsValid() const;
	UINT32			GetBitmapSize() const;
	BOOL			IsTransparent() const;
	UINT32			GetBPP() const;

public:
	LPBITMAPINFO	pbmpInfo;
	LPBYTE			pbmpBits;
//	DocRect			rectCachedRect;
	DocCoord		coord0;				// Three coords representing a parallelogram alow the bitmap to be transformed
	DocCoord		coord1;				// (mainly for use with destructive liveffects but also good for quick blits
	DocCoord		coord2;				//  of cached info during dragging)
	INT32			nPriority;
	BOOL			bFullCoverage;		// TRUE when this bitmap fully covers the relevant object
};


// Declare global template-specific override for HashKey function...
struct LessBitmapCacheKey
{
  bool operator()(const CBitmapCacheKey &s1, const CBitmapCacheKey &s2) const
  {
	  return s1.Hash() < s2.Hash();
  }
};

typedef std::map<CBitmapCacheKey, CCachedBitmap, LessBitmapCacheKey> CCacheKeyMap;

class CBitmapCache
{
public:
	CBitmapCache();
//	virtual ~CBitmapCache();

// Methods
public:
	void			Initialise();
	void			DeInitialise();

	void			StoreBitmap(const CBitmapCacheKey& key, const CCachedBitmap& bitmap);
//	CCachedBitmap	FindBitmap(const CBitmapCacheKey& key);
	CCachedBitmap	RemoveBitmap(const CBitmapCacheKey& key);
	BOOL			RemoveAllOwnedBitmaps(	const CBitmapCacheKey& key,
											const BOOL bOpaqueOnly = FALSE,
											const INT32 maxpriority = CACHEPRIORITY_TEMPBITMAP_HIGH);
	void			RemoveLowPriorityBitmaps(const INT32 maxpriority = CACHEPRIORITY_TEMPBITMAP_HIGH);
	CCachedBitmap	FindNextOwnedBitmap(CCacheKeyMap::iterator &pos,
										CBitmapCacheKey &key,
										const BOOL bOpaqueOnly = FALSE,
										const INT32 maxpriority = CACHEPRIORITY_TEMPBITMAP_HIGH);
	void			SetMaximumDataSize(UINT64 maxsize);
	UINT64			GetMaximumDataSize();
	UINT32			GetCurrentDataSize();

#ifdef _DEBUG
	void			DebugDump();
#endif

	// Some CMap emulation functions
	BOOL Lookup( const CBitmapCacheKey &Key, CCachedBitmap &CachedBitmap )
	{
		CCacheKeyMap::iterator iter = m_map.find( Key );
		if( m_map.end() == iter )
			return false;
		
		CachedBitmap = iter->second;
		return true;
	}

	CCacheKeyMap::iterator GetStartPosition() {return m_map.begin();}

// Public helper functions
public:
	static UINT64 CalcRecommendedMaximumDataSize();

// Private helper functions
private:
//	UINT32			PrimeAbove(UINT32 number);
	CCachedBitmap	RemoveRandomBitmap(const INT32 maxpriority = CACHEPRIORITY_TEMPBITMAP_HIGH);			// Cache removal policy helper

// Internal members
private:
	CCacheKeyMap	m_map;

	UINT64		m_lMaxDataSize;
	UINT32			m_lCurrentDataSize;
	UINT32			m_lMaxHashTableLoad;

// Preferences
	static INT32 CacheRAMPercent;			// Amount of free RAM to grab for cacheing

};

#endif // !defined(AFX_BITMAPCACHE_H__41BFBD9B_A02E_4205_AE0A_4F6A5E0DC7D0__INCLUDED_)
