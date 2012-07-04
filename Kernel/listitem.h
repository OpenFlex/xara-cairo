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

/**********************************************************************************************

>	class ListItem : public CCObject

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/4/1993
	Base Class:	CObject
	Purpose:	
		A list item is an abstract class which is used to derive all objects 
		which are linked together in lists.  It has no member functions because
		all useful operations are defined in the List class.  The reason 
		for doing this is that list operations may need to alter the list 
		header.

	Errors:		None.

**********************************************************************************************/
/*
  Technical notes:
  
  When using lists with derived listitems it is necessary to explicitly cast from a listitem 
  pointer to the 'derived listitem' pointer.  
  
  e.g.  List x;
  		MyListItem* y;
        ....              
        y = x.GetHead();					// Wrong!!! need to cast to MyListItem* because
        									//    GetHead() returns a ListItem*   
        
        y = (MyListItem*) x.GetHead();  	// This will work honest!
                                             
  (This is only necesary when retrieving items from the list because type convertion from a 
   derived class to a base class is automatic.)
   
   
  You also have to do the cast if the function call is nested within another function call.
  
  e.g.	void Display(MyListItem*);
  		....	
        Display(x.GetHead());				// Error!
        ....
        Display((MyListItem*)x.GetHead());	// OK!
        
  
**********************************************************************************************/

#ifndef INC_LISTITEM
#define INC_LISTITEM

#include "ccobject.h"

class CCAPI ListItem : public CCObject
{
CC_DECLARE_DYNCREATE(ListItem);
	
friend class List;								// The class list is a friend of 
												// ListItem 
friend class ActionList;                        // ActionList is also a friend

private:
	ListItem *Next;								// Pointer to NEXT ListItem in List
	ListItem *Previous;							//  "      "  PREVIOUS ListItem " "

public:
	ListItem();

	virtual ~ListItem() {}						// base classes must have a virtual destructor

	virtual ListItem *GetItem(void);			// For compatability with OrderedList
												// traversal methods

	virtual void ClearPointers();
};

#endif
