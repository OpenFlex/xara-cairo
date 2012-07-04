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

// SGLBase.h - SuperGallery Library Base class

#ifndef INC_SGLBASE
#define INC_SGLBASE

//#include "sgallery.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "sgtree.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "msg.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "thumb.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "sgscan.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "inetop.h"
//#include "stl.h"
#include <list>

class PathName;
class List;
class LibraryFile;
/***********************************************************************************************

>	class LibraryGallery : public SuperGallery

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/5/95 (Finally)
	Purpose:	A base library gallery class with common library gallery stuff in

	Notes:		SuperGalleries are specced in a number of docs including
					specs\sgallery.doc ("super" gallery extensions)
					specs\propui.doc  (gallery basic ui)
				There is also howtouse\sgallery.doc which describes creating a supergallery

	SeeAlso:	SuperGallery; SGDisplayLibClipart

***********************************************************************************************/

class LibraryGallery : public SuperGallery
{
	CC_DECLARE_DYNCREATE(LibraryGallery)

public:
	LibraryGallery();
	~LibraryGallery();

	// TRUE if the SuperGallery is also a LibraryGallery, which it is !
	virtual BOOL IsLibraryGallery(void) {return TRUE;};

public:
	// Library Galleries must override these

	// TRUE if the SuperGallery is also a LibraryGallery & has no non-library groups
	virtual BOOL IsLibraryGalleryWithNonLibraryGroups(void) {return FALSE;};

	// Can we create indexes ?
	virtual BOOL CanCreateIndexes(void);

	// Get various default bits 'n' pieces
	virtual BOOL GetDefaults(String_256 *DefaultIndex, String_256 *IndexDesc, SGLibType *Type);

	// Get the default CD directory name for the gallery
	virtual BOOL GetLibraryDirectoryName(String_256 *LibDirName);

	// Check the entry in the index.txt file with our gallery, and return TRUE if it's a match
	virtual BOOL CheckForIndexMatch(StringBase *Txt);

	// Return a Section name for this gallery...
	virtual void WorkOutSectionName(String_256 *Section);

	// Return a Description Section name for the gallery
	virtual void WorkOutDescriptionSectionName(String_256 *Section);

	// Return a Library Type Section name for the gallery
	virtual void WorkOutLibraryTypeSectionName(String_256 *Section);

	// Override for creating clipart library groups rather than display groups
	virtual SGDisplayGroup *AddLibraryGroup(Library *LibraryToDisplay, INT32 NumItems);

	// Get the quiet status of the gallery
	virtual BOOL GetQuietStatus(void);

	// Set the quiet status of the gallery
	virtual void SetQuietStatus(BOOL Status);

	// Scan for location of default CD library
	virtual BOOL ScanForLocation(SGLibType Type, StringBase *Result);

public:
	// Library Galleries should override these

	// Can we support keywords ?
	virtual BOOL CanSearchKeywords(void);

	// Message handler
	virtual MsgResult Message(Msg* Message);

	// Override for button greying
	virtual void SelectionHasChanged(void);

protected:
	virtual void DoShadeGallery(BOOL ShadeIt);	
	virtual BOOL PreCreate(void);
	virtual BOOL ApplyAction(SGActionType Action);
	virtual BOOL AddNewLibrary(PathName *LibPath, BOOL WipeOld, SGLibType LibType, BOOL Update = FALSE);
	virtual SGDisplayItem *AddLibraryItem(SGDisplayGroup *LibraryGroup, Library *ParentLib, LibraryIndex ItemIndex, BOOL bNew = FALSE);
	virtual void HandleDragStart(DragMessage *DragMsg);
	virtual SGDisplayItem *CopyDisplayItem(SGDisplayItem *SourceItem, 
								SGDisplayGroup *DestGroup, SGDisplayItem *TargetPosition);
	virtual void AllItemsCopied(SGDisplayGroup *DestGroup) {};

	// These could probably go in the library gallery base class if we ever create one

	// Handle clicks on the browse button
	virtual BOOL BrowseClicked(void);
	BOOL BrowseClicked(String_256 *DefaultPath, SGLibType Type, INT32 Message);

	// Sort the entire gallery alphabetically
	virtual void SortGallery(void);

	// Called by AddLibraryGroup to Scroll, redraw and shuffle about the groups after an add..
	BOOL SortOutGroupsAfterLibraryAdd(LibraryFile *LibFile, BOOL Update);

public:
	// Add the library groups as described by the GRM file. If there were non there,
	// use the given path
	BOOL AddLibraryGroups(SGLibType LibType, String_256 *DefaultLibraryPath);

	// Use the indexes listed in the GRM file to add to the gallery
	BOOL AddGRMGroups(SGLibType LibType);

	// Helper function for AddGRMGroups which actually does the addition
	BOOL ActuallyAddGRMGroups(/*SGLibType LibType*/ List *TypeList, List *PathList, List *DescList, BOOL DescPresent,
		String_256 *SectionName, String_256 *DescriptionSectionName);
	// This is the same function but does not try and read from the GRM ini file if the lists are
	// empty as this is deprecated functionality.
	BOOL GoAndAddGRMGroups(/*SGLibType LibType*/ List *TypeList, List *PathList, List *DescList, BOOL DescPresent,
		String_256 *SectionName, String_256 *DescriptionSectionName);

	// Function to remove all the current gallery settings
	static BOOL WipeGallerySettings(void);

	// Return the current display mode identifier - needed for sorting
	INT32 GetDisplayMode(void);

	// Remove any selected gallery groups
	void RemoveSelectedLibraries(BOOL Warn);

	// Update the GRM file to reflect the new state of the gallery
	void UpdateGRMFile(void);

	// Count library groups in gallery
	INT32 LibraryGroupsInGallery(void);

	// The gallery is closing
	void GalleryAboutToClose(void);

	// The gallery is (re)opening
	void GalleryAboutToReOpen(void);

	// Remove all duplicate groups with the same file path and index name as the specified...
	INT32 RemoveSimilarLibraryGroups(PathName *FilesPath, String_256 *IndexFileName, BOOL RemoveFirstOne = TRUE, BOOL Redraw = TRUE, Library *DontKill = NULL);

	// >>webster (adrian 15/12/96)

	virtual void SuspendThumbnailDownloading();

	virtual void ResumeThumbnailDownloading();

	inline BOOL IsThumbDownloadingSuspended() {return !bThumbDownloading;}

	virtual SGLibType GetGalleryType() { return SGLib_Blank;}

	virtual String_256* GetDefaultLibraryPath() {return NULL;}


	Library* FindLibrary(const String_256& rLibPath);

	// Called in response to the user clicking the "Get X..." (X = "clipart","fonts", etc.) button in one of the online galleries 
	virtual BOOL OnGetButtonClicked();

// <<webster


protected:
	// Whizz through the gallery tree and virtualise all the folded groups which can be
	virtual void VirtualiseAllFoldedGroups();

	// Recursively remove web folders for the specified gallery - used by the Internet galleries
	BOOL RemoveWebFolders(SGLibType type);

public:

	// All LibraryFiles we currently have open
	List OpenLibFiles;

	// List of pending thumb downloads 
	std::list<OpThumbDownload*> m_lstPendingThumbs;

	// Flag indicating whether this gallery's web folders have been discarded since last update (or beginning of session)
	// A value of TRUE indicates that we should attempt to download the indexes before any web folder operation
	BOOL m_bDiscardWebFolders;


public:	// statics

	// Ask the user if they want to 'remove all existing groups before adding this one or not'
	static BOOL AskAboutRemoving;

	// Offset into folders of the first one removed by RemoveSimilarLibraryGroups
	static INT32 OffsetOfFirstGroupRemoved;

	// Was the first removed group selected or not ?
	static BOOL FirstGroupRemovedSelectionState;

	// Copy of bitmap used for dragging
	static KernelBitmap* TmpDraggingBitmap;

	// Flag indicating whether we should attempt to download thumnails not found locally - makes sense only for Internet galleries
	BOOL bThumbDownloading;

};

#endif

