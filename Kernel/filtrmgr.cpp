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
#include "filtrmgr.h"

#include "fileform.h"

#if defined(DEBUG_THIS)
#include "plgnfltr.h"
#endif


CC_IMPLEMENT_MEMDUMP(FilterManager, CC_CLASS_MEMDUMP)
CC_IMPLEMENT_MEMDUMP(FileFormat, CC_CLASS_MEMDUMP)
CC_IMPLEMENT_MEMDUMP(FilterList, List)
CC_IMPLEMENT_MEMDUMP(FormatEntry, CC_CLASS_MEMDUMP)
CC_IMPLEMENT_MEMDUMP(FilterEntry, CC_CLASS_MEMDUMP)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	FilterManager::FilterManager()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/02/94
	Purpose:	Set the Filter object up to be in a clean state.
	SeeAlso:	Filter; Filter::~Filter; OILFilter

********************************************************************************************/
FilterManager::FilterManager() :
	FILTERID_START(FILTERID_ALDUS_END + 1),
	FORMATID_START(1)
{
	m_NextFilterID		= FILTERID_START;
	m_NextFormatID		= FORMATID_START;
}


/********************************************************************************************

>	FilterID FilterManager::GetNewFilterID()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Returns:	A FilterID unique to this FilterManager for each call to the function
	Purpose:	Support function providing an unique ID for each newly registered Filter

********************************************************************************************/
UINT32 FilterManager::GetNewFilterID()
{
	ERROR3IF(!m_NextFilterID, "Creating duff FilterID");

	return m_NextFilterID++;
}


/********************************************************************************************

>	FilterID FilterManager::RegisterFilter(	const Filter* const pFilter, 
											const DESTRUCTION_METHOD DestructMethod)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/12/94
	Inputs:		pFilter:	pointer to the filter to register
	Returns:	FilterID that uniquely identifies the given filter within the scope of this
				FilterManager and allows for fast retrieval of the filter.
	Purpose:	Permits the filter to be used by the FilterManager.
				For an import filter to be present on the Import dialog the filter should
				associate itself with the requisite FileFormats via AssociateFilterWithFormat()

********************************************************************************************/

UINT32 FilterManager::RegisterFilter(	Filter* const pFilter, 
									const DESTRUCTION_METHOD DestructMethod)
{
	//DestructMethod; // This line just read "DestructMethod;" - what's that meant to do then?
	UINT32 newID = Filter::RegisterFilter(pFilter);

	return newID;
}



/********************************************************************************************

>	BOOL FilterManager::Init()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/96
	Returns:	TRUE if initialised ok, FALSE if not.
	Purpose:	Initializes the filter manager
				Currently just does some tests

********************************************************************************************/

BOOL FilterManager::Init()
{
#if defined(DEBUG_THIS)

	String_256 MyFormatName = _T("myFormat");
	String_256 MyFormatDesc = _T("Format (*.frm)");
	XtraFileFormat* pFormat = new XtraFileFormat(MyFormatName, MyFormatDesc);
	FileFormatID myFormatID = RegisterFileFormat((FileFormat*)pFormat, FilterManager::DM_DELETE_WHEN_DONE);
	MyFormatDesc = _T(".fm1");
	pFormat->AddExtension(MyFormatDesc);
	MyFormatDesc = _T(".fm2");
	pFormat->AddExtension(MyFormatDesc);
	MyFormatDesc = _T(".fm3");
	pFormat->AddExtension(MyFormatDesc);
	MyFormatDesc = _T(".fm2");
	pFormat->AddExtension(MyFormatDesc);
	MyFormatDesc = _T(".one long mother of an extension well beyond thirty-two");
	pFormat->AddExtension(MyFormatDesc);

#endif

	// All ok
	return TRUE;
}


/********************************************************************************************

>	BOOL FilterManager::DeInit()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/12/96
	Purpose:	Destroy all the FileFormat objects, maybe

********************************************************************************************/

BOOL FilterManager::DeInit()
{
	for (UINT32 index = 0; index < GetLastFormatID(); index++)
	{
		FormatEntry* pEntry = GetFormats()[index];
		ERROR2IF(pEntry == NULL, FALSE, "pEntry NULL");

		FileFormat* pFormat = pEntry->GetFormat();
		ERROR2IF(pFormat == NULL, FALSE, "pFormat NULL");

		if (pEntry->GetDestructionMethod() == DM_DELETE_WHEN_DONE)
		{
			delete pFormat;
		}
		delete pEntry;
		GetFormats()[index] = NULL;
	}

	// All ok
	return TRUE;
}



#define ADD_FILTER(Classname, FilterIDConst) \
	/* Create, initialise and install the Generic import filter */					\
	pFilter = new Classname;														\
	if (pFilter == NULL) return FALSE;												\
																					\
	if (!pFilter->Init())															\
	{																				\
		/* Error occured - report it and stop trying to initialise filters. */		\
		InformError();																\
		return TRUE;																\
	}																				\
																					\
	FilterIDConst = RegisterFilter(pFilter, DM_DELETE_WHEN_DONE);					\
	if (FilterIDConst == NULL)														\
	{																				\
		return FALSE;																\
	}																				\


/********************************************************************************************

>	Filter* FilterManager::FindFilterFromID(const UINT32 FilterID) const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Purpose:	Provides the Filter given its ID

********************************************************************************************/
Filter* FilterManager::FindFilterFromID(const UINT32 FilterID) const
{
	Filter* pFilter = Filter::GetFirst();
	while (pFilter != NULL)
	{
		if (pFilter->FilterID == FilterID)
		{
			break;
		}
		pFilter = Filter::GetNext(pFilter);
	}
	return pFilter;
}


////////////////////////////// Format Related Functions /////////////////////////////////////

/********************************************************************************************

>	FormatArray& FilterManager::GetFormats()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Returns:	A reference to the FormatArray
	Purpose:	Support function providing access to the FileFormats

********************************************************************************************/
FormatArray& FilterManager::GetFormats()
{
	return m_Formats;
}
	
/********************************************************************************************

>	FileFormatID FilterManager::GetNewFormatID()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Returns:	A FileFormatID unique to this FilterManager for each call to the function
	Purpose:	Support function providing an unique ID for each newly registered FileFormat

********************************************************************************************/
FileFormatID FilterManager::GetNewFormatID()
{
	return m_NextFormatID++;
}


/********************************************************************************************

>	FileFormatID FilterManager::RegisterFileFormat(const FileFormat* pFormat, 
												const DESTRUCTION_METHOD dm)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Inputs:		pFormat:	A pointer to the FileFormat to register
	Returns:	A FileFormatID by which the given FileFormat can be uniquely identified and
				quickly retrieved.
	Purpose:	Registers the given FileFormat with this FilterManager

********************************************************************************************/
FileFormatID FilterManager::RegisterFileFormat(	FileFormat* const pFormat, 
												const DESTRUCTION_METHOD DestructMethod)
{
	ERROR2IF(pFormat == NULL, 0, "NULL Args");

	// Look for one we might already have
	FileFormatID IDToReturn = FindFormatIDFromName(pFormat->GetName());
	if (IDToReturn == 0)
	{
		// Have to add a new one
		IDToReturn = GetNewFormatID();
		FormatEntry* pFormatEntry = new FormatEntry(IDToReturn, pFormat, DestructMethod);
		if (pFormatEntry == NULL)
		{
			goto AddFormatError;
		}

		if (!GetFormats().Add(pFormatEntry))
		{
			delete pFormatEntry;
			goto AddFormatError;
		}
	}
	else
	{
		// Use the duplicate then
	}
	
	return IDToReturn;

AddFormatError:

	return 0;
}


/********************************************************************************************

>	BOOL FilterManager::AssociateFilterWithFormat(	const FilterID FilterID, 
													const FileFormatID FileFormatID)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Inputs:		FilterID:	The FilterID (returned by RegisterFilter()) of the filter to
							associate with the given FileFormatID
				FileFormatID:	Like FilterID
	Purpose:	Tells this FilterManager that the given filter wishes to be considered when
				doing things with the given format.

********************************************************************************************/
BOOL FilterManager::AssociateFilterWithFormat(	const UINT32 FilterID, 
												const FileFormatID FileFormatID)
{
	BOOL Successful = TRUE;		// value to return

	Filter*	pFilter				= FindFilterFromID(FilterID);
	FormatEntry* pFormatEntry	= FindFormatEntryFromID(FileFormatID);

	if (pFilter != NULL && pFormatEntry != NULL)
	{
		// We found both the filter & format so create a new association entry
		Successful = pFormatEntry->GetFilters().AddFilter(pFilter, FilterID);
	}
	else
	{
		Successful = FALSE;
	}
	
	return Successful;
}


/********************************************************************************************

>	FileFormatID FilterManager::FindFormatIDFromName(const StringBase& FormatName) const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Purpose:	Relief function returning the FileFormat ID instead of the FileFormat per se
	See Also:	Other overloaded function

********************************************************************************************/
FileFormatID FilterManager::FindFormatIDFromName(const StringBase& FormatName) const
{
	FileFormatID FoundID = 0;
	FormatEntry* pFoundEntry = FindFormatEntryFromName(FormatName);

	if (pFoundEntry != NULL)
	{
		FoundID = pFoundEntry->GetID();
	}
	else
	{
		FoundID = 0;
	}

	return FoundID;
}
		
/********************************************************************************************

>	FileFormat* FilterManager::FindFormatFromName(const StringBase& FormatName) const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Inputs:		FormatName:	The name of a FileFormat given in the FileFormat's constructor
							which has subsequently been Added to this FilterManager.
	Returns:	A pointer to the FileFormat with the name given or NULL if none was found
	Purpose:	Finds the one & only FileFormat with the given FormatName
				Used by Xtra's mainly

********************************************************************************************/
FileFormat* FilterManager::FindFormatFromName(const StringBase& FormatName) const
{
	FormatEntry* pEntry = FindFormatEntryFromName(FormatName);
	if (pEntry != NULL)
	{
		return pEntry->GetFormat();
	}
	return NULL;
}


/********************************************************************************************

>	FileFormat* FilterManager::FindFormatFromID(const FileFormatID FormatID) const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Purpose:	Provides the FileFormat given its ID
	See Also:	FindFormatEntryFromID

********************************************************************************************/
FileFormat* FilterManager::FindFormatFromID(const FileFormatID FormatID) const
{
	FileFormat* pReturnedFormat;

	FormatEntry* pEntry = FindFormatEntryFromID(FormatID);
	if (pEntry != NULL)
	{
		pReturnedFormat = pEntry->GetFormat();
	}
	else
	{
		pReturnedFormat = NULL;
	}

	return pReturnedFormat;
}


/********************************************************************************************

>	FormatEntry* FilterManager::FindFormatEntryFromID(const FileFormatID) const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Purpose:	Internally does the actual finding by ID
	See Also:	FindFormatFromID

********************************************************************************************/
FormatEntry* FilterManager::FindFormatEntryFromID(const FileFormatID FormatID) const
{
	ERROR2IF(FormatID == 0 || FormatID > GetLastFormatID(), NULL, 
				"Invalid FileFormatID");

	return GetFormats()[FormatID - 1];
}


/********************************************************************************************

>	FormatEntry* FilterManager::FindFormatEntryFromName(const StringBase& FormatName) const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Inputs:		FormatName:	The name of a FileFormat given in the FileFormat's constructor
							which has subsequently been Added to this FilterManager.
	Returns:	A pointer to the FileFormat with the name given or NULL if none was found
	Purpose:	Finds the one & only FileFormat with the given FormatName
				Used by Xtra's mainly

********************************************************************************************/
FormatEntry* FilterManager::FindFormatEntryFromName(const StringBase& FormatName) const
{
	for (UINT32 index = 0; index < GetLastFormatID(); ++index)
	{
		FormatEntry* pFormatEntry = GetFormats()[index];
		if (pFormatEntry != NULL)
		{
			FileFormat* pFormat = pFormatEntry->GetFormat();
			if (pFormat->GetName() == FormatName)
			{
				return pFormatEntry;
			}
		}
		else
		{
			// we'll ignore this one
		}
	}

	return NULL;
}



/********************************************************************************************

>	Filter* FilterManager::FindMatchedFilter(SearchCriteria)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Purpose:	To find a filter with the given SearchCriteria
	Notes:		Returns the first matching filter within the context of the given
				SearchCriteria (the SearchContext is contained within the SearchCriteria)

********************************************************************************************/
Filter*	FilterManager::FindFilter(FilterSearchCriteria& Criteria) const
{
	return NULL;
}


/********************************************************************************************

>	FilterList* FilterManager::ListMatchingFilters(FilterSearchCriteria& Criteria)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Purpose:	Creates a list of filters matching the given FilterSearchCriteria
	Returns:	A list of filters matching the given FilterSearchCriteria. The list IsEmpty
				if no filters matched
				NULL if failed
	Notes:		The returned list should be deleted when finished with.

********************************************************************************************/
FilterList* FilterManager::ListMatchingFilters(FilterSearchCriteria& Criteria)
{
	FilterList* pList = new FilterList;

	return pList;
}



/********************************************************************************************

>	FormatEntry::FormatEntry(const FileFormatID ID, const FileFormat* pFormat, 
				const FilterManager::DESTRUCTION_METHOD DestructMethod)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Inputs:		ID:				The FileFormat's ID
				pFormat:		A pointer to the FileFormat
				DestructMethod:	Whether or not the FileFormat should be deleted when this
								FormatEntry is.
	Purpose:	Provides an entry for the FilterManager's database of FileFormats

********************************************************************************************/
FormatEntry::FormatEntry(const FileFormatID ID, FileFormat* const pFormat, 
				const FilterManager::DESTRUCTION_METHOD DestructMethod)
{
	m_pFormat			= pFormat;
	m_FormatID			= ID;
	m_DestructMethod	= DestructMethod;
}



/********************************************************************************************

>	FormatEntry::~FormatEntry()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/12/96
	Purpose:	Default constructor deleting associated FilterEntry items

********************************************************************************************/
FormatEntry::~FormatEntry()
{
	GetFilters().DeleteAll();
}


/********************************************************************************************

>	FilterList::FilterList()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com> (from Tim)
	Created:	28/03/94
	Purpose:	Initialises a list

********************************************************************************************/
FilterList::FilterList()
{
}


/********************************************************************************************

>	FilterEntry::FilterEntry(Filter* pFilter, FilterID ID)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com> (from Tim)
	Created:	28/03/94
	Inputs:		pFilter: the filter contained within this FilterItem
				ID - a unique ID for the given filter
	Purpose:	Initialises a list item for a Filter

********************************************************************************************/
FilterEntry::FilterEntry(Filter* const pFilter, const UINT32 ID)
{
	ERROR3IF(pFilter == NULL || !ID, "FilterListItem - pFilter NULL");

	m_pFilter	= pFilter;
	m_FilterID	= ID;
}


/********************************************************************************************

>	BOOL FilterList::AddFilter(Filter* const pFilter, const FilterID ID)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com> (from Tim)
	Created:	28/03/94
	Inputs:		pEntry: the FilterEntry to add to the list.
	Returns:	TRUE if the filter was added to the list ok; FALSE if not.
	Purpose:	Add a new item to the compatible filter list, which points to the given
				filter, and stores the given compatibility rating in the list entry.
				The list is kept in sorted order, i.e. the list item is added to the list
				according to its compatibility rating; the higher the rating, the closer
				it is to the head of the list.
	Errors:		Out of memory.
	SeeAlso:	ComaptibleFilterList; CompatibleFilter

********************************************************************************************/
BOOL FilterList::AddFilter(Filter* const pFilter, const UINT32 ID)
{
	// Make a new list item for this filter.
	FilterEntry* pEntry = new FilterEntry(pFilter, ID);
	if (pEntry == NULL)
	{
		return FALSE;
	}

	AddTail(pEntry);	// can't fail

	// All ok
	return TRUE;
}
