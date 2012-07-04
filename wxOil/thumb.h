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


// Thumbnail cache class for the library system
// Cheap 'n' Cheesy version knocked up by Richard
/***********************************************************************/

#ifndef INC_THUMB
#define INC_THUMB

#include "bitmap.h"
//#include "pathname.h"

typedef void * LP_SGTHUMBS_MOREINFO;

/***********************************************************************/

class Library;
class PathName;

// All the types of library
enum SGLibType
{
	SGLib_Blank = 0,	// Unknown library type
	SGLib_ClipArt,		// Clipart libraries
	SGLib_Font,			// Font libraries
	SGLib_Bitmap,		// Bitmap libs
	SGLib_Texture,		// Texture libs
	SGLib_Colour,		// Colour libs
	SGLib_Fractal,		// Fractal fill libs
	SGLib_ClipArt_WebThemes
};

// All thumbnail sizes
enum SGThumbSize
{
	SGThumb_Small = 0,	// Small thumbnails
	SGThumb_Medium,
	SGThumb_Large
};	


/***********************************************************************/

class SGThumbs : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(SGThumbs)

public:

	SGThumbs();

	// Destructor - calls DeleteThumbnails() - returns all memory
	~SGThumbs();

	// Constructor which sets the Size of thumbnails as well
	SGThumbs(PathName *Dir, SGLibType Type, SGThumbSize Size);
									
	// Get a thumbnail from the cache, disk, or if Directory == NULL try and generate it.
	BOOL GetThumbnail(UINT32 ID, BOOL Urgent, KernelBitmap **Result, PathName *File = NULL, LP_SGTHUMBS_MOREINFO MoreInfo = NULL);
	
	// Set thumbnail size - all returned thumbnails will be this size after this call
	BOOL SetSize(SGThumbSize Size);

	// Get current thumbnail size setting
	BOOL GetSize(SGThumbSize *Size);

	// Delete all thumbnail cache entries and return the memory
	BOOL DeleteThumbnails(void);

	// Debugging stuff - do not call
	void DumpCache(char *DumpFile);

	// Called when we want to change MaxThumbnails;
	static BOOL ResizeAllThumbCaches(INT32 Entries);

	// Access to the protected members
	inline PathName *GetDirectory() {return Directory;}
	inline SGLibType GetType() {return ThumbnailsLibType;}

protected:

	// Return encrypted thumbnail filename
	BOOL GetThumbnailName(UINT32 ID, String_8 *Result);

	// Sets the internal structures to sensible values
	// Assumes pointers not pointing to NULL are not pointing to memory
	BOOL InitThumbnails(SGLibType Type, SGThumbSize Size);

	// Return TRUE and an offset if ID is in cache
	BOOL OffsetInCache(UINT32 ID, UINT32 *Offset);
	
	// Find an unused slot, if there are non, use the one with the least Usage
	BOOL FindNewSlotInBuffer(UINT32 *Slot);

	// Load a thumbnail into a given slot
	BOOL LoadThumbnailIntoSlot(UINT32 Slot, UINT32 ID, PathName *ActualFile = NULL);

private:

	// Implementation helper function to check file existence
	BOOL OpenThumbnailFile( CCDiskFile* pFile, const PathName& ThumbFileName ) const;

protected:

	// Use a more fabby data-structure when we've got CCList access
	struct TN {
		UINT32 ID;				// ID for thumbnail held below
		UINT32 Usage;			// Usage count - used for finding new slots
		BOOL Valid;				// Are buffer and ID valid ?
		SGThumbSize Size;		// Size of thumbnail
		KernelBitmap *buffer;	// Pointer to actual data
	};

	// Array of thumbnails
	TN *Thumbnails;

	// Number of thumbnails in array
	INT32 Entries;

	// Place where all the thumbnails are being stored
	PathName *Directory;
	
	// Have we initialised the data-structures yet ?
	BOOL ThumbnailsInitialised;

	// Size of thumbnail to load, cache and return
	SGThumbSize ThumbnailsSize;

	// Type of library we're dealing with here
	SGLibType ThumbnailsLibType;

public:
	// Maximum number of entries in thumbnail cache
	static INT32 MaxThumbnails;
};

/***********************************************************************/

#endif
