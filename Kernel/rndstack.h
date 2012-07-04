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


// A attribute stack to be used when rendering Camelot files.

#ifndef INC_RNDSTACK
#define INC_RNDSTACK

class AttributeValue;
class AttributeRec;
class RenderRegion;

/********************************************************************************************

>	class RenderStack : public CC_CLASS_MEMDUMP

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/01/94
	Purpose:	To provide a stack on which to save attribute values while rendering
				the Camelot tree.  The stack is optimised to minimise the amount of
				pushing and popping actually done.
	SeeAlso:	AttributeRec; RenderRegion; AttributeValue; NodeAttribute

********************************************************************************************/

class RenderStack : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(RenderStack)

public:
	RenderStack();
	~RenderStack();
	BOOL Push(AttributeValue *pAttrValue, BOOL Temporary = FALSE);

	// The Rendering Context (Attributes)
	void SaveContext() { ContextLevel++; }
	void RestoreContext(RenderRegion *pRegion);

	void CleanUpBeforeDestruct(RenderRegion *pRegion);
			// Restores the context stack to ContextLevel 0 by properly popping all
			// entries, allowing all attributes to clean up properly.
	
	// Function to copy one RenderStack to another
	BOOL Copy(const RenderStack *Other, RenderRegion *pRegion);

private:
	BOOL GrowStack();

	// Pointer to the attribute stack - it's treated as a variable size array.
	AttributeRec *TheStack;

	// Index of next empty item in stack; 0 => stack is empty.
	// (It's an 'empty' stack, i.e. Top points to the next free item in the stack).
	UINT32 Top;

	// Size of stack
	UINT32 StackLimit;

	// Current stack context level.
	UINT32 ContextLevel;
};

#endif // INC_RNDSTACK


