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
//*/

// Implementation of the Stack and MarkedStack classes 

#include "camtypes.h" 
#include "stack.h"

DECLARE_SOURCE("$Revision: 1282 $");

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	Stack::Stack()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Stack constructor
	Errors:		-
	SeeAlso:	-

********************************************************************************************/


Stack::Stack()
{
}

/********************************************************************************************

>	Stack::~Stack()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Stack destructor. The items on the stack are not deleted
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

Stack::~Stack()
{
	
}

/********************************************************************************************

>	void Stack::Push(ListItem* Item)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Pushes Item onto the stack 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void Stack::Push(ListItem* Item)
{
	stack.AddTail(Item); // Add the item to the top of the stack 
}

/********************************************************************************************

>	ListItem* Stack::Pop(void)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	The top item on the stack, or NULL if the stack is empty 
	Purpose:	Removes the item from the top of the stack, and returns it 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

ListItem* Stack::Pop(void)
{	
	return (stack.RemoveTail()); 
}

/********************************************************************************************

>	ListItem* Stack::GetTop(void)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/2/94
	Inputs:		-
	Outputs:	-
	Returns:	The item at the top of the stack
	Purpose:	Allows you to find out what item is on the top of the stack (the item is not
				removed). 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

ListItem* Stack::GetTop(void)
{
	return (stack.GetTail()); 
}


/********************************************************************************************

>	void Stack::DeleteAll()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Removes and deletes all items on the stack 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void Stack::DeleteAll()
{
	stack.DeleteAll(); // Call the list's DeleteAll method 
}

/********************************************************************************************

>	INT32 Stack::Size()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	The number of items on the stack 
	Purpose:	For finding the size of the stack 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

INT32 Stack::Size()
{
	return stack.GetCount(); 
}

// ------------------------------------------------------------------------------------------
// MarkedStack methods 

/********************************************************************************************

>	MarkedStack::MarkedStack()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	MarkedStack constructor 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

MarkedStack::MarkedStack()
{
}

/********************************************************************************************

>	MarkedStack::~MarkedStack()

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	MarkedStack destructor. The items on the stack are not deleted
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

MarkedStack::~MarkedStack()
{
}

/********************************************************************************************

>	MarkedStack::Push(ListItem* Item)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Pushes Item onto the stack 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/


void MarkedStack::Push(ListItem* Item)
{
	AddTail(Item); // Add the item to the top of the stack 
}

/********************************************************************************************

>	ListItem* MarkedStack::Pop(void)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	The top item on the stack, or NULL if the stack is empty 
	Purpose:	Removes the item from the top of the stack, and returns it 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

ListItem* MarkedStack::Pop(void)
{	
	return (RemoveTail()); 
}


/********************************************************************************************

>	BOOL MarkedStack::Mark(void)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if we could create Mark, FALSE if we are out of memory 

	Purpose:	Marks the current Top of the stack so that we can easily return to the 
				same state by calling Release(). 

	Errors:		ERRORIF is called if we are out of memory 
	SeeAlso:	MarkedStack::Release()

********************************************************************************************/

BOOL MarkedStack::Mark(void)
{			
	// Firstly create a mark 													
	ListItemPtrItem* pMark = new ListItemPtrItem(); 
	// Return with an error if we could not create the mark
	if (pMark == NULL)
		return FALSE; 
	pMark->pListItem = GetTail();	// This will be NULL if the list is empty 

   	// Push the mark onto the MarkStack
	MarkStack.Push(pMark); 
	return TRUE; // Success
} 	

/********************************************************************************************

>	void MarkedStack::Release(void)

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Pops and then deletes items from the stack until we find the first mark. 
				If there are no marks then all items on the stack are removed and deleted
	Errors:		-
	SeeAlso:	MarkedStack::Mark

********************************************************************************************/

		 
void MarkedStack::Release(void)
{
	// Find the mark to stop at 
	ListItemPtrItem* MarkRec = (ListItemPtrItem*)MarkStack.Pop();
	ListItem* Mark; 
	if (MarkRec == NULL) 						// There are no marks to find 
	{
		Mark = NULL; 
	} else 
	{
		Mark = MarkRec->pListItem; 
	}  
	ListItem* TopOfStack = GetTail(); 
	ListItem* AsGoodAsDead; 

	while (TopOfStack != Mark)			// Loop until we find Mark
	{
		ENSURE(TopOfStack != NULL, "A Mark could not be found in the Marked stack"); 
		TopOfStack = GetPrev(TopOfStack);
		AsGoodAsDead = RemoveTail();
		delete AsGoodAsDead; 
	}
	if (MarkRec != NULL)
	{
		delete (MarkRec); // Restored State to that pointed to by Mark, so delete it 
	}
} 

/********************************************************************************************

>	void MarkedStack::DeleteAll() 	

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/2/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Deletes all marks and elements in the MarkedStack
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void MarkedStack::DeleteAll()
{
	ListItem* TopOfStack;
	TopOfStack = GetTail(); 
	while (TopOfStack != NULL)	 // loop while the stack is not empty 
	{
		Release(); // Deletes mark and all items before the mark		
		TopOfStack = GetTail(); 
	}	
	// Make sure there are no marks left
	ENSURE(MarkStack.Pop() == NULL, "All marks have not been deleted from the MarkedStack"); 
}	

