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

//

#ifndef INC_FILTRMGR
#define INC_FILTRMGR

#include "ccarray.h"
//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]

typedef UINT32 FileFormatID;

class Filter;
/**************************************************************************************

>	class FilterList : public List

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	Today
	Purpose:	Take out some of the functionality from filters

**************************************************************************************/
class FilterList : public List
{
	CC_DECLARE_MEMDUMP(FilterList)
public:
	FilterList();

	BOOL AddFilter(Filter* const pFilter, const UINT32 ID);
};


class FileFormat;
class FormatEntry;
class FilterEntry;
class FilterList;
class FilterSearchCriteria;

class FormatArray : public CCArray<FormatEntry*, FormatEntry*&>
{
};

class FileFormat;
/**************************************************************************************

>	class FilterManager : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	Today
	Purpose:	Take out some of the functionality from filters

**************************************************************************************/
class FilterManager : public CC_CLASS_MEMDUMP
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(FilterManager);

public:
	FilterManager();

	BOOL Init();
	INT32 DeInit();

	// Registering functions
	// What to do with filters, formats & families at the end of the day
	enum DESTRUCTION_METHOD
	{
		DM_INVALID			= 0,	// don't use this, it's for catching duff initialization
		DM_DELETE_WHEN_DONE	= 1,
		DM_KEEP_WHEN_DONE
	};

	UINT32			RegisterFilter(	Filter* const pFilter, 
									const DESTRUCTION_METHOD DestructMethod);
	FileFormatID	RegisterFileFormat(	FileFormat* const pFormat, 
										const DESTRUCTION_METHOD DestructMethod);

	// Aggregation functions
	BOOL	AssociateFilterWithFormat(	const UINT32 FilterID, 
										const FileFormatID FileFormatID);

	// Search functions
	// Filters...
	Filter*	FindFilterFromID(const UINT32 FilterID) const;

	Filter*	FindFilter(FilterSearchCriteria& Criteria) const;
	FilterList* ListMatchingFilters(FilterSearchCriteria& Criteria);

	// FileFormats...
	FileFormat*		FindFormatFromID(const FileFormatID FormatID) const;
	FileFormat*		FindFormatFromName(const StringBase& FormatName) const;
	FileFormatID	FindFormatIDFromName(const StringBase& Name) const;

protected:
	List&				GetFilters() const;
	const UINT32			FILTERID_START;
	UINT32				GetNewFilterID();

	FormatArray&		GetFormats();
	const FormatArray&	GetFormats() const	{	return m_Formats;	}
	const FileFormatID	FORMATID_START;
	FileFormatID		GetNewFormatID();
	FileFormatID		GetLastFormatID() const	{	return m_NextFormatID - 1;	}

	// And for searching
	FormatEntry*	FindFormatEntryFromID(const FileFormatID FormatID) const;
	FormatEntry*	FindFormatEntryFromName(const StringBase& FormatName) const;

private:
	// Lists of things the filter manager works with
	UINT32			m_NextFilterID;

	FormatArray		m_Formats;
	FileFormatID	m_NextFormatID;
};


/********************************************************************************************

>	class FilterEntry : public ListItem

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com> (from Tim)
	Created:	28/03/94
	Purpose:	A simple ListItem derived class to allow a list of filters to be
				maintained - the list holds all the filters that claim to understand a
				particular file (see FilterFamily).
				It is not derived from the Filter class itself because although the Filter 
				class is derived from ListItem too, we want to store a list of pointers to 
				existing filters, rather than actual instances of the Filter class.
				For each entry, a 'compatibility rating' is held, to allow the 
				FilterFamily class (the client of this class) to choose the most
				compatible filter from the list.
	SeeAlso:	CompatibleFilterList; Filter; ListItem

********************************************************************************************/
class FilterEntry : public ListItem
{
	CC_DECLARE_MEMDUMP(FilterEntry)

public:
	FilterEntry(Filter* const pFilter, const UINT32 ID);

protected:
	// Compatibility rating for this filter.
	Filter*		m_pFilter;
	UINT32		m_FilterID;

};

/********************************************************************************************

>	class FormatEntry : protected CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/11/96
	Purpose:	A simple ListItem derived class to allow a list of filters to be
				maintained
	SeeAlso:	FilterList
	Scope:		private to FilterManager

********************************************************************************************/
class FilterManager;

class FormatEntry : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(FormatEntry)

public:
	FormatEntry(const FileFormatID ID, FileFormat* const pFormat, 
				const FilterManager::DESTRUCTION_METHOD DestructMethod);

	~FormatEntry();

	FileFormat*			GetFormat() const				{ return m_pFormat;	}
	FileFormatID		GetID() const					{ return m_FormatID;	}
	FilterList&			GetFilters()					{ return m_AssociatedFilters;	}

	FilterManager::DESTRUCTION_METHOD	GetDestructionMethod() const 
														{ return m_DestructMethod;	}

protected:

	FileFormat*			m_pFormat;				// Pointer to the format in question.
	FileFormatID		m_FormatID;				// and it's ID
	FilterList			m_AssociatedFilters;	// A list of filters that think they can cope

	// What to do with the format at the end...
	FilterManager::DESTRUCTION_METHOD	m_DestructMethod;	
};


#endif	// INC_FILTRMGR
