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
 */ 

/***********************************************************************************************

>	class List : public CCObject

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/4/1993
	Base Class:	CObject
	Friends:	ListItem
	Purpose:	

		The member functions are based on the MFC CObList class, though the
		implementation differs greatly. In particular no exceptions are thrown
		as all new items are allocated by someone else and some of the types 
		have changed. An instance of the list class will be something like a list
		of fonts, and list of undo records etc. Remove functions don't actually 
		de-allocate anything, they just remove items from the list.

	Notes:		Two ways of using a list item are provided: by pointer-to-item, and
				by item-index. The latter is very slow on average compared to the former
				because the list must be scanned each time to find a LISTPOS. Thus, use
				the pointer method where possible.

	Errors:		None.

***********************************************************************************************/

#ifndef INC_LIST
#define INC_LIST

// Set up a local debugging flag so that the debugging of lists can be turned off in normal
// debug builds and thus make things that use lists a lot faster!
// If you want the list debugging in then please make a local writable copy, uncomment the
// first #define and comment out the second.
#undef _SLOW_LIST_DEBUG
#ifdef _DEBUG
//	#define _SLOW_LIST_DEBUG						// Slow debugging as well as normal
	#undef _SLOW_LIST_DEBUG							// Omit slow (O(n)) debugging
#endif

#include "ensure.h"
#include "listitem.h"    

typedef INT32 LISTPOS;           					// 32-bit unsigned integer used to return
													// the position of a ListItem in a List

// LISTPOS values of ZERO or GREATER are valid
// LISTPOS values less than ZERO are invalid - Below is a list of LISTPOS error flags

const LISTPOS NOT_IN_LIST = -1;                     // Constant used to flag when a ListItem 
                                                    // is not found in a list
const LISTPOS EMPTY_LIST = -2;                     	// Constant used to flag when a List is  
                                                    // empty
const LISTPOS INVALID_LISTPOS = -3;                 // Constant used to flag when a LISTPOS 
                                                    // is does not exist in list
const LISTPOS INVALID_NEWITEM = -4;                 // Constant used to flag when new item to 
                                                    // be added to list is NULL

class CCAPI List : public CCObject
{   
	CC_DECLARE_DYNAMIC( List )

private:
	ListItem *HeadItem;								// pointer to head of list
	ListItem *TailItem;								// pointer to tail of list
	UINT32 ItemCount; 								// number of items in list

public:
	List();											// List constructor
	virtual ~List();								// List destructor

	virtual ListItem *RemoveHead();							
	virtual ListItem *RemoveTail();	
	virtual void DeleteAll(); 														
	
	virtual void AddHead( ListItem* );	
	virtual void AddTail( ListItem* );

	ListItem *GetHead( ) const;						
	LISTPOS GetHeadPosition() const;
	
	ListItem *GetTail( ) const;
	LISTPOS GetTailPosition() const;
	
	inline ListItem *GetNext( const ListItem* ) const;
	inline ListItem *GetPrev( const ListItem* ) const;

	ListItem *FindItem( LISTPOS ) const;
	LISTPOS FindPosition(ListItem *) const;

	virtual ListItem *RemoveItem( ListItem* );

	virtual LISTPOS InsertBefore(LISTPOS here, ListItem* item);
	virtual ListItem *InsertBefore(ListItem* here, ListItem* item);

	virtual LISTPOS InsertAfter(LISTPOS here, ListItem* item);
	virtual ListItem *InsertAfter(ListItem* here, ListItem* item);

	UINT32 GetCount() const;
	
	BOOL IsEmpty() const;     						

	// Creates a list of in-order pointers to each item in this list
	BOOL CreateIndex(List* IndexedList); 
	
#ifdef _DEBUG										// only required in DEBUG version
public:
	void AssertValid() const;

private:
	ListItem *LastItemRemoved;						// Used to check for stupidity
													// when deleteing items in a list
													// See GetNext/GetPrev

public:
	static INT32 ListDebugLevel;

#endif
};

/********************************************************************************************

>	class ListItemIdx: public ListItem

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/9/95
	Purpose:	A ListItem that points to another ListItem. Used to created list indexes
	SeeAlso:	List::CreateIndex

********************************************************************************************/

class ListItemIdx: public ListItem
{
public:
	ListItem* pItem; 
};

/********************************************************************************************

>	class ListListItem: public ListItem

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/10/95
	Purpose:	A ListItem with a 'list' in it. Useful for lists of lists.
				The destructor deletes all items in its List.
	SeeAlso:	ListItem

********************************************************************************************/

class ListListItem: public ListItem
{
public:
	virtual ~ListListItem() { list.DeleteAll(); };
	List list; // A list
};

/**********************************************************************************************

>	inline ListItem *List::GetNext( const ListItem* ) const

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/4/93
	Inputs:		pointer to ListItem
	Outputs:	None
	Returns:	ListItem if not empty
				NULL if list empty or if ListItem not found or end of list or input pointer
				is NULL
	Purpose:
		
		To allow access to the next ListItem in the list after the one that has been 
		passed in as input.

	Errors:		In the debug build, if SLOW_LIST_DEBUG is enabled (see list.h), this
				will check that the item is valid (is in the list etc), and generate
				ENSURE failures if not.
				In all debug builds, we will still check that the list is non-empty and
				that the passed ListItem is non-NULL.
				In debug, a check is also made that you are not trying to GetNext on the
				last item you removed from the list, as this is a common mistake to make

**********************************************************************************************/
/*
Technical notes: 

In debug builds the input ListItem is validated and its existence in the List is also checked.
In release build it is assume that the input parameter will be ok and that it is in the list.

**********************************************************************************************/

inline ListItem *List::GetNext( const ListItem* here ) const
{
#ifdef _DEBUG
	CC_ASSERT_VALID(this);

	ENSURE(!this->IsEmpty() && here != NULL,
			"List::GetNext(here) - The list is empty, or 'here' is NULL");

	ENSURE(here != LastItemRemoved, 
			"List::GetNext - Serious mistake! The item has just been removed from the list!!");

	if (ListDebugLevel > 1)
	{
		ListItem *listIter;								// list iterator 
                 
		listIter = HeadItem;
    
		while (listIter != here && listIter != NULL)	// iterate until input ListItem found
			listIter = listIter->Next;

		ENSURE(listIter != NULL, "List:GetNext(here) - 'here' isn't in the list!");                                
	}
#endif

    return here->Next;
}



/**********************************************************************************************

>	inline ListItem *List::GetPrev( const ListItem* here ) const

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/4/93
	Inputs:		pointer to a ListItem
	Outputs:	None
	Returns:	ListItem if found
				NULL if list empty or ListItem not found or beginning of list or input pointer
				is NULL.
	Purpose:	
		
		To allow access to the previous ListItem in the list before the one that has been 
		passed in as input.

	Errors:		In the debug build, if SLOW_LIST_DEBUG is enabled (see list.h), this
				will check that the item is valid (is in the list etc), and generate
				ENSURE failures if not.
				In all debug builds, we will still check that the list is non-empty and
				that the passed ListItem is non-NULL.
				In debug, a check is also made that you are not trying to GetNext on the
				last item you removed from the list, as this is a common mistake to make

**********************************************************************************************/

inline ListItem *List::GetPrev( const ListItem* here ) const
{
#ifdef _DEBUG
	CC_ASSERT_VALID(this);

	ENSURE(!this->IsEmpty() && here != NULL,
			"List::GetNext(here) - The list is empty, or 'here' is NULL");

	ENSURE(here != LastItemRemoved, 
			"List::GetPrev - Serious mistake! The item has just been removed from the list!!");

	if (ListDebugLevel > 1)
	{
		ListItem *listIter;								// list iterator 
                 
		listIter = HeadItem;
    
		while (listIter != here && listIter != NULL)	// iterate until input ListItem found
			listIter = listIter->Next;

		ENSURE(listIter != NULL, "List:GetPrev(here) - 'here' isn't in the list!");
	}

#endif

	return(here->Previous);
}




#endif
