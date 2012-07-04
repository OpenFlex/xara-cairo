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

/*
 * */
// Definition of the Text tools FontCache
// See FNTCACHE.DOC	for an explanation




#ifndef INC_FNTCACHE
#define INC_FNTCACHE

//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "gcache.h"
//#include "txtattr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include <limits.h>


/********************************************************************************************

>	class FontCache

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>

	Created:	16/1/95
	
	Purpose:	The FontCache maps a character description to a  path for that character. 
				There only ever needs to be a single instance of the FontCache so all
				data and methods are static.
	
	Documentation:	specs\fntcache.doc
	
	SeeAlso:	CharDescription
	SeeAlso:	PathHandleItem

********************************************************************************************/


// The simpler FontCache defined below is simply a wrapper around a CamCache

class FontCache
{
	// All data/methods must be static

public:
	// This method must be called before we can use the CamCache
	static BOOL Init();

	static BOOL InitCalled; // = FALSE, set to TRUE only if Init function has been called

	// This function must be called to destroy the font cache
	static void DeInit(); 

	// Returns path for character specified by ChDesc 
	static BOOL GetPath(CharDescription& ChDesc, INT32** Points, BYTE** Types, UINT32 *Length);
	
	// The path cache is used to map a Path Handle to path data
	static CamCache* pPathCache;

	static BOOL  GetBounds(DocRect* pBounds, CharDescription& CharDesc);
	static BOOL  CalcDefaultCharBounds(DocRect* pRect, CharDescription& CharDesc);
	static Path* CreateDefaultCharPath(CharDescription& CharDesc);
private:
	static INT32 BoundsEntries;		// number of entries in the char bounds cache


};


#endif

#if 0

//
// WE ARE NOT USING THE HI-TECH FONT CACHE AT THE MOMENT
//
//

// ------------------------------------------------------------------------------------------
// Constants

// The cache size is the maximum number of characters to cache
#define CACHE_SIZE 255

// We will allocate two arrays CacheA, CacheB each of length CACHE_LIST_SIZE. Each of these arrays
// will never be more than 1/3 full
//#define CACHE_LIST_SIZE (1.5 * CACHE_SIZE); // This MUST be prime or performance is naff
#define CACHE_LIST_SIZE 383

//#define MAX_ITEMS_IN_CACHE_LIST = (CACHE_LIST_SIZE/3)
#define MAX_ITEMS_IN_CACHE_LIST	255

// We can never allocate a path handle larger than MAX_FONT_HANDLE 
#define MAX_PATH_HANDLE (UINT32_MAX - 1)


/********************************************************************************************

>	class ClassName : public CCObject

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/1/95
	Purpose:	Each character we need to render can be uniquely identified by a 16 bit 
				unicode character + various attributes which define the appearance of the 
				characters font. The CharDescription structure defined below is used to 
				identify a character. This structure is similar to the windows LOGFONT 
				structure.

	SeeAlso:	FontCache

********************************************************************************************/


class CharDescription : public CCObject
{
	// Important !!!
	// Whenever this structure is changed, you must remember to update the operator= and
	// operator== methods !!!
	CC_DECLARE_DYNAMIC(CharDescription)

	public:

	INT32 operator==(const CharDescription& ChDesc); 
	CharDescription& operator=(CharDescription& ChDesc);

	INT32 Height;
   	INT32 Width;
   	//INT32 lfEscapement;
  	//INT32 lfOrientation;
   	//INT32 lfWeight;
   	BYTE Italic;
  	//BYTE lfUnderline;
  	//BYTE lfStrikeOut;
  	//BYTE lfCharSet;
   	//BYTE lfOutPrecision;
   	//BYTE lfClipPrecision;
   	//BYTE lfQuality;
   	//BYTE lfPitchAndFamily;	
	WCHAR CharCode; 			// A 16 bit unicode value
}; 


/********************************************************************************************

>	class PathHandleItem: public CCObject

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/1/95
	Purpose:	We store PathHandle Items in lists pointed to by the CacheA and CacheB arrays
				within the FontCache.They associate a CharDescription with a unique path handle.

	SeeAlso:	FontCache
	SeeAlso:	CharDescription

********************************************************************************************/
/*
	Technical notes: We want to minimise the size of the PathHandleItem. This is why they are
	not derived from ListItem. Instead they store a single Next pointer so that they can be 
	linked together.

*/																									   


class PathHandleItem: public CCObject
{  
	CC_DECLARE_DYNAMIC(PathHandleItem)

	public:
	PathHandleItem(CharDescription& ChDesc, UINT32 PathHandle);

	CharDescription CharDesc;	// Identifies a character
	UINT32 PathHandle;
	// Removes this item from the specified list
	void RemoveItemFromList(PathHandleItem** pHead); 
	PathHandleItem* Next; 		// pointer to the Next PathHandleItem
};




class FontCache
{
	// All data/methods must be static

	public:
	
	// This method must be called before we can use the CamCache
	static BOOL Init();

	static BOOL InitCalled; // = FALSE, set to TRUE only if Init function has been called

	// This function must be called to destroy the font cache
	static void DeInit(); 

	// Returns path for character specified by ChDesc 
	static BOOL GetPath(CharDescription& ChDesc, INT32** Points, BYTE** Types, UINT32 *Length);
	
	#ifdef _DEBUG
	static void Test1();
	#endif


	private:
	
	static UINT32 GetPathHandle(CharDescription& ChDesc); 

	// Given a CharDescription returns an integer hash key in the range 0..CACHE_LIST_SIZE
	static UINT32 GetHashKey(CharDescription& ChDesc);

	// The two caches used to map a CharacterDescription to a Path Handle 
	static PathHandleItem* CacheA 	[CACHE_LIST_SIZE]; 
	static PathHandleItem* CacheB	[CACHE_LIST_SIZE]; 
	
	// Searches a PathHandleItem list for ChDesc item
	static PathHandleItem* GetPathHandleItem(PathHandleItem* ListHead, CharDescription&  ChDesc); 
	
	// Deletes all items in specified cache
	static void DeleteCacheLists(PathHandleItem** pCacheArray);
	
	static void TidyCache();

	static PathHandleItem** PrimaryC;   // Points to the current primary cache (CacheA or CacheB)
	static PathHandleItem** SecondaryC; // Points to the current secondary cache (CacheA or CacheB)


	static BOOL GetPathFromPathCache(UINT32 PathHandle, CharDescription& ChDesc, 
							  		INT32** Points, BYTE** Types, UINT32* Length);
	
	// The path cache is used to map a Path Handle to path data
	static CamCache* pPathCache;
	
	static PathHandleItem* AllocatePathHandle(UINT32 Key, CharDescription& ChDesc);

	// The next PathHandle to assign to a new CharDescPathHandleItem we add to the cache
	static UINT32 NextUniquePathHandle; 

	// The number of items stored in the primary cache
	static UINT32 NumItemsInPrimaryCache; 

	// Can be deleted
	#ifdef _DEBUG
	static UINT32 PHits;
	static UINT32 SHits;
	static UINT32 Misses;
	#endif

		
};

#endif
