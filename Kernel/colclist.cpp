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

// colclist.cpp - the ColourContextList class

/*
*/


#include "camtypes.h"

#include "colcontx.h"
//#include "doccolor.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ensure.h" - in camtypes.h [AUTOMATICALLY REMOVED]



CC_IMPLEMENT_MEMDUMP(ColourContextList, List)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW



/*  ColContextList
 *
 *	This is a 'global' pointer to a list of colour context objects
 *	It is used to ensure that no colour contexts are ever repeated (i.e. they
 *	are shared wherever possible). Only users of this file have access to this
 *  list.
 *  Access is via the static function ColourContextList::GetList()
 */

ColourContextList *ColourContextList::ColContextList = NULL;



/********************************************************************************************

>	static BOOL ColourContextList::InitColourContexts(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/04/94
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if initialisation succeeded, else FALSE
				FALSE if it failed (most likely because of lack of memory)
	Purpose:	Initialises the Colour Context system, setting up the global list
				of default colour contexts which are shared by all documents.
				Called from app.cpp (must not be called more than once)
	Errors:		-

********************************************************************************************/

BOOL ColourContextList::InitColourContexts(void)
{
	ENSURE(ColContextList == NULL, "ColourContextList::InitColourContexts called more than once!");

	// First, create the global Colour context list in which all colour contexts
	// should be registered.
	ColContextList = new ColourContextList;
	if (ColContextList == NULL)
		return(FALSE);


	// Now, create an instance of each available colour context to provide the
	// global set of default colour contexts. Add each to the CCList.
	ColourContext *tempcc;

	tempcc = new ColourContextRGBT(NULL, 1.0);			// --- RGBT
	if (tempcc == NULL)
		return(FALSE);

	ColContextList->AddContext(&tempcc);
	ColourContext::SetGlobalDefault(COLOURMODEL_RGBT, tempcc);
	

	tempcc = new ColourContextCMYK(NULL);				// --- CMYK
	if (tempcc == NULL)
		return(FALSE);

	ColContextList->AddContext(&tempcc);
	ColourContext::SetGlobalDefault(COLOURMODEL_CMYK, tempcc);

	tempcc = new ColourContextHSVT(NULL);				// --- HSVT
	if (tempcc == NULL)
		return(FALSE);

	ColContextList->AddContext(&tempcc);
	ColourContext::SetGlobalDefault(COLOURMODEL_HSVT, tempcc);


	tempcc = new ColourContextGreyT(NULL);				// --- GreyT
	if (tempcc == NULL)
		return(FALSE);

	ColContextList->AddContext(&tempcc);
	ColourContext::SetGlobalDefault(COLOURMODEL_GREYT, tempcc);


#ifndef DISABLE_WEBRGBT
	tempcc = new ColourContextWebRGBT(NULL);			// --- WebRBGT
	if (tempcc == NULL)
		return(FALSE);

	ColContextList->AddContext(&tempcc);
	ColourContext::SetGlobalDefault(COLOURMODEL_WEBRGBT, tempcc);
#endif
														// --- etc...

	return(TRUE);
}



/********************************************************************************************

>	static void ColourContextList::DeinitColourContexts(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/04/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	De-initialises the Colour Context system, deleting the global list
				of default colour contexts which are shared by all documents.
				It is assumed that by this time the contexts should not be in use!
				Called from app.cpp (must not be caled more than once)
	Errors:		If any colour contexts are still in use when this function is
				called, you may get ENSURE failures.

********************************************************************************************/

void ColourContextList::DeinitColourContexts(void)
{
	ENSURE(ColContextList != NULL, "ColourContextList::DeinitColourContexts: but I haven't been initialised yet!");

	ColourContextArray	DefaultCCA;
	ColourContext		*DefaultCC;

	ColourContext::GetGlobalDefaults(&DefaultCCA);

	// Delete any of the default colour contexts that actually exist...
	for (INT32 cm = 0; cm < MAX_COLOURMODELS; cm++)
	{
		// Get the default colour context object for this colour model number
		// I do this via a copy of the real array to avoid the GetDefaultContext()
		// call giving an ENSURE failure in the case of a NULL context pointer.
		DefaultCC = DefaultCCA.Context[cm];
	
		if (DefaultCC != NULL)
		{
			// Set the default to NULL to ensure fewer rampant pointers are
			// left lying around (just to be on the safe side)
			ColourContext::SetGlobalDefault((ColourModel) cm, NULL);

			// Remove from the list. Note that we use RemoveItem to *force*
			// removal - RemoveContext only removes it if UsageCount == 0.
			ColContextList->RemoveItem(DefaultCC);

			// Decrement usage. This *should* take it down to zero usage, as
			// it is hoped that by the time we are called, all other users will
			// have released their claims. We do this to stop the ENSURE from
			// triggering when we delete the object.
			DefaultCC->DecrementUsage();

			// And delete the object
			delete DefaultCC;
		}
	}

	ENSURE(ColContextList->IsEmpty(), "ColourContextList::DeinitColourContexts: Some ColourContext(s) have not yet been released");

	// And delete the global list of contexts
	delete ColContextList;
	ColContextList = NULL;
}




/********************************************************************************************

>	void ColourContextList::AddContext(ColourContext **NewContext)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/04/94
	Inputs:		-
	Outputs:	An equivalent colour context that may now be used
	Returns:	-

	Purpose:	"Adds" the given colour context to the global list of available
				contexts. Note that if an identical context is already present in
				the list, the passed context will be DELETEd and the existing
				context will be returned in the given pointer. Thus, you must 
				only ever access the context through the returned pointer, rather
				than the pointer that you originally allocated with 'new'.

				i.e. to create and use a new context, you must:
				{
					ColourContext *MyContext;

					MyContext = new ColourContextABCD(1.0);		// Create new context
					if (MyContext == NULL)
						return(FAILED_MISERABLY);

					ColContextList->AddContext(&MyContext);		// MyContext may change!

					MyContext->DoSomething...					// Use the context

					ColContextList->RemoveContext(&MyContext);	// Have finished with it

					// MyContext is now a NULL pointer, so don't use it!
				}

	Notes:		You must NOT delete the context when you finish with it. Instead, you
				must call ColourContextList::RemoveContext() when you have finished with
				the context. The context will be automatically deleted when it is no
				longer in use by anyone.

				(Sharing of contexts is currently disabled - see the comment in the
				function for details)

	Errors:		-
	SeeAlso:	ColourContext::ConvertColour; ColourContext::ConvertColourInternal

********************************************************************************************/

void ColourContextList::AddContext(ColourContext **NewContext)
{
	ENSURE(NewContext != NULL && *NewContext != NULL,
				"ColourContextList::AddContext called with NULL parameter!");

#if FALSE
/*
	Jason 22/5/96
	We no longer merge contexts because this makes for danger with the new ColourPlate
	system - it's now too easy to change a colourcontext by altering its ColourPlate,
	in which case shared contexts will cause extreme grief.

	ColourContext *Item;

	Item = (ColourContext *) GetHead();

	while (Item)
	{
		if (!Item->IsDifferent(*NewContext))	// Have found identical context
		{
			delete *NewContext;			// Delete the new context
			Item->IncrementUsage();		// Increment the new context's usage count
			*NewContext = Item;			// And return the existing one for use
			return;
		}

		Item = (ColourContext *) GetNext(Item);
	}

	// We have searched the entore list now but still have no equivalent context
	// so it is necessary to add this context to the list, and return it.
*/
#endif

	// However, we do check that the given context is not already in the list,
	// and ignore the caller if it's already there.
	ColourContext *Item;

	Item = (ColourContext *) GetHead();

	while (Item)
	{
		if (Item == *NewContext)
		{
			Item->IncrementUsage();		// Increment the context's usage count
			return;
		}

		Item = (ColourContext *) GetNext(Item);
	}

	AddTail(*NewContext);
	(*NewContext)->Init();

	// And by leaving the contents of the passed pointer alone, we return it.
}



/********************************************************************************************

>	void ColourContextList::RemoveContext(ColourContext **OldContext)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/04/94
	Inputs:		-
	Outputs:	-
	Returns:	-

	Purpose:	"Removes" the given colour context to the global list of available
				contexts. If the context is now no longer in use by anyone, it will
				be 'delete'd. The context pointer passed in will be set to NULL.
	Errors:		-
	SeeAlso:	ColourContextList::AddContext; ColourContext

********************************************************************************************/

void ColourContextList::RemoveContext(ColourContext **OldContext)
{
	ENSURE(OldContext != NULL && *OldContext != NULL,
				"ColourContextList::RemoveContext called with NULL parameter!");

	if (!((*OldContext)->DecrementUsage()))		// Not still in use, so discard it
	{
		RemoveItem(*OldContext);
		delete *OldContext;
	}

	*OldContext = NULL;
}


