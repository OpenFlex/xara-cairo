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

#ifndef INC_STACK
#define INC_STACK
// Declaration of the stack and MarkedStack classes

//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************************************

>	class Stack

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	A general purpose stack for storing ListItems. 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/


class Stack
{
public:
	Stack(); 				 // Constructor 
	~Stack(); 				 // Destructor
	void Push(ListItem* Item); 	 // Pushes item onto the stack
	ListItem* Pop(void); 	 // Pops item from the top of the stack	 
	ListItem* GetTop(void);  // Allows you to peek at the top item on the stack 
	INT32 Size();		 	 // Returns number of items on the stack   
	void DeleteAll(); 			 // Removes all stack items and calls their destructors
	
private:
	List stack;  		     // The stack  
	
};

/********************************************************************************************

>	class ListItemPtrItem: public ListItem

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Purpose:	A ListItem object which is a pointer to a ListItem, used by the MarkedStack 
				class. 
	SeeAlso:	MarkedStack

********************************************************************************************/

 
class ListItemPtrItem: public ListItem
{	
	public:
	ListItem* pListItem; 
};

/********************************************************************************************

>	class MarkedStack: public List 

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94

	Purpose:	A marked stack is a special purpose stack/list. Its properties are described: 

				It has Push and Pop methods 
				It inherits from list so it can easily be searched
				
				It has a Mark() method which marks the current top of stack. Mark() can be
				called more than once to insert a number of marks into the stack. 

				It has a Release() method which restores the state of the stack to the 
				position of the last mark. 

				eg. 

				MarkedStack MS(); 

				MS->Push(a)
				MS->Mark()
				MS->Push(b) 
				MS->Push(c)
				MS->Mark()
				MS->Push(d)

				The stack looks like this 
				
				d <- Tail 
				c <- Mark
				b
				a <- Mark

				If we now perform MS->Release() the stack will look like this 

				c
				b
				a  <- Mark

				If we perform MS->Release() a second time, the stack will look like this

				a

				
	SeeAlso:	-

********************************************************************************************/


class MarkedStack: public List 
{
	public:
	MarkedStack(); 			// constructor
	~MarkedStack(); 		// destructor
	
	void Push(ListItem* Item); 	// Pushes item onto the stack
	ListItem* Pop(void); 	// Pops item from the top of the stack

	BOOL Mark(); 			// Inserts a mark into the stack 
	void Release(); 		// pops and deletes items till we reach the first mark
	
	void DeleteAll(); 		// deletes all elements and marks
	
	private:
	Stack MarkStack; 		// A stack of pointers (marks) into the list 

};
#endif
