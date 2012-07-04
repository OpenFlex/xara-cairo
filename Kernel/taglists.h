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


#ifndef INC_TAGLISTS
#define INC_TAGLISTS

#include "cxftags.h"
//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/***********************************************************************************************

>	class AtomicTagListItem : public ListItem

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/96
	Purpose:	An item that appears in the AtomicTagList

***********************************************************************************************/

class AtomicTagListItem : public ListItem
{
CC_DECLARE_MEMDUMP(AtomicTagListItem)

public:
	AtomicTagListItem()				{ Tag = TAG_UNDEFINED; }
	AtomicTagListItem(UINT32 ThisTag) { Tag = ThisTag; }

	UINT32 GetTag() { return Tag; }
private:
	UINT32 Tag;
};

/***********************************************************************************************

>	class EssentialTagListItem : public ListItem

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/96
	Purpose:	An item that appears in the EssentialTagList

***********************************************************************************************/

class EssentialTagListItem : public ListItem
{
CC_DECLARE_MEMDUMP(EssentialTagListItem)

public:
	EssentialTagListItem()				{ Tag = TAG_UNDEFINED; }
	EssentialTagListItem(UINT32 ThisTag)	{ Tag = ThisTag; }

	UINT32 GetTag() { return Tag; }
private:
	UINT32 Tag;
};

/***********************************************************************************************

>	class TagDescriptionListItem : public ListItem

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/96
	Purpose:	An item that appears in the TagDescriptionList

***********************************************************************************************/

class TagDescriptionListItem : public ListItem
{
CC_DECLARE_MEMDUMP(TagDescriptionListItem)

public:
	TagDescriptionListItem()									{ Tag = TAG_UNDEFINED; pStr = NULL; }
	TagDescriptionListItem(UINT32 ThisTag, String_256* pThisStr)	{ Tag = ThisTag; pStr = pThisStr; }

	~TagDescriptionListItem()	{ if (pStr != NULL) delete pStr; }
	
	UINT32 GetTag()			{ return Tag; }
	String_256* GetString()	{ return pStr; }

private:
	UINT32		Tag;
	String_256* pStr;
};

/***********************************************************************************************

>	class AtomicTagList : public List

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/96
	Purpose:	Keeps a list of all the atomic tags present in the imported file.

				This only relates to new format files

				An atomic tag is a tag that represents the head of a sub-tree that should be
				taken as a single entity.
				E.g. a TextStory tag is an atomic tag because it, and all it's children, represent
				one object (same applies for mould & blend tags).

				If an importer reads a record that it doesn't understand, and it's been defined as
				an atomic record, then it should ignore the record AND ALL ITS CHILD RECORDS!

***********************************************************************************************/

class AtomicTagList : public List
{
CC_DECLARE_MEMDUMP(AtomicTagList)

public:
	AtomicTagList() {}

	void AddTail(AtomicTagListItem* pItem)				{ List::AddTail(pItem); };
	AtomicTagListItem* GetHead()						{ return (AtomicTagListItem*)List::GetHead(); }
	AtomicTagListItem* GetNext(AtomicTagListItem* pItem){ return (AtomicTagListItem*)List::GetNext(pItem); }
};


/***********************************************************************************************

>	class EssentialTagList : public List

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/96
	Purpose:	Keeps a list of all the essential tags present in the imported file.

				This only relates to new format files

				An essential tag is a tag that the importer must understand in order to successfully
				load the file.

				If the importer does not recognise the tag, and it's defined to be essential, the importer
				should abort the import.

				We have no examples of such a tag.  This mechanism is in place in case we wish to prevent
				old importers loading in newer versions of the file format.

***********************************************************************************************/

class EssentialTagList : public List
{
CC_DECLARE_MEMDUMP(EssentialTagList)

public:
	EssentialTagList() {}

	void AddTail(EssentialTagListItem* pItem)					{ List::AddTail(pItem); };
	EssentialTagListItem* GetHead()								{ return (EssentialTagListItem*)List::GetHead(); }
	EssentialTagListItem* GetNext(EssentialTagListItem* pItem)	{ return (EssentialTagListItem*)List::GetNext(pItem); }
};

/***********************************************************************************************

>	class TagDescriptionList : public List

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/96
	Purpose:	Keeps a list of all the tag descriptions present in the imported file.

				This only relates to new format files

				This will only come into use in newer versions of the file format.  It allows old importers
				to describe an unknown tag to the user.

***********************************************************************************************/

class TagDescriptionList : public List
{
CC_DECLARE_MEMDUMP(TagDescriptionList)

public:
	TagDescriptionList() {}

	void AddTail(TagDescriptionListItem* pItem)						{ List::AddTail(pItem); };
	TagDescriptionListItem* GetHead()								{ return (TagDescriptionListItem*)List::GetHead(); }
	TagDescriptionListItem* GetNext(TagDescriptionListItem* pItem)	{ return (TagDescriptionListItem*)List::GetNext(pItem); }
};

#endif	// INC_TAGLISTS
