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

// This file implents the BitmapEffect class

/*
*/

#include "camtypes.h"
#include "bfxbase.h"
#include "bfxalu.h"

// This is not compulsory, but you may as well put it in so that the correct version
// of your file can be registered in the .exe

// An implement to match the Declare in the .h file.
// If you have many classes, it is recommended to place them all together, here at the start of the file
CC_IMPLEMENT_DYNCREATE(BitmapEffectBase, ListItem)

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW

// statics
BfxALU * BitmapEffectBase::ALU = NULL;

/********************************************************************************************

>	BitmapEffectBase::BitmapEffectBase()
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/94
	Inputs:		None
	Outputs:	Constructs object
	Returns:	Nothing
	Purpose:	Default constructor for bitmap effect object
	Errors:		Causes a level 3 if the setting the parameters to the default fails
	SeeAlso:	-

This constructs an object and sets the parameters to the default set. As contructors can't fail
we explode if we can't set the parameters to the default set on the basis that this is an
operation defined algorithmically to work 100% of the time!

********************************************************************************************/

BitmapEffectBase::BitmapEffectBase()
{
	Source = NULL;
	Destination = NULL;
//	Monitor = NULL;

	if (!(SetParameters())) /* virtual */
	{
		ERROR3("Bitmap effect default parameter set failed in constructor");
	}
}

/********************************************************************************************

>	BitmapEffectBase::~BitmapEffectBase()
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/94
	Inputs:		None
	Outputs:	Constructs object
	Returns:	Nothing
	Purpose:	Default constructor for bitmap effect object
	Errors:		Causes a level 3 if the setting the parameters to the default fails
	SeeAlso:	-

This constructs an object and sets the parameters to the default set. As contructors can't fail
we explode if we can't set the parameters to the default set on the basis that this is an
operation defined algorithmically to work 100% of the time!

********************************************************************************************/

BitmapEffectBase::~BitmapEffectBase()
{
	ERROR3IF((Destination!=NULL),"Bitmap effect destructor called when destination exists");
	// Unforunately we habe to use ERROR3 not ERROR2 as we can't return a flag	
}

/********************************************************************************************

>	static BOOL BitmapEffectBase::Init()
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/10/94
	Inputs:		None
	Outputs:	Initialises subsystem
	Returns:	TRUE if succeeded, FALSE & error set if not
	Purpose:	Initialises the bitmap effect subsystem
	Errors:		None from this one as yet
	SeeAlso:	-

This call's primary purposes is to initialise the BfxALU, getting its static pointer.

********************************************************************************************/

BOOL BitmapEffectBase::Init()
{
	ALU=new BfxALU;
	return (ALU) ? (ALU->Init()) : FALSE;
}

void BitmapEffectBase::TestGD()
{
	ALU->TestGD();
}

/********************************************************************************************

>	static BOOL BitmapEffectBase::DeInit()
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/10/94
	Inputs:		None
	Outputs:	DeInitialises subsystem
	Returns:	TRUE if succeeded, FALSE & error set if not
	Purpose:	Initialises the bitmap effect subsystem
	Errors:		None from this one as yet
	SeeAlso:	-

This call's primary purposes is to deinitialise the BfxALU.

********************************************************************************************/

BOOL BitmapEffectBase::DeInit()
{
	if ( (ALU) && (ALU->DeInit()) )
	{
		delete(ALU);
		ALU=NULL;
		return TRUE;
	}
	else return FALSE;
}

/********************************************************************************************

>	BOOL BitmapEffectBase::SetParameters()
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/94
	Inputs:		None
	Outputs:	Sets up the parameters to the default
	Returns:	TRUE if succeeded, FALSE & error set if not
	Purpose:	Sets the bitmap effect params up to the default
	Errors:		None from this one as yet
	SeeAlso:	-

Normally this would be overridden to det a default set of parameters, but the base class
version might be used if the effect has no parameters

********************************************************************************************/

BOOL BitmapEffectBase::SetParameters()
{
	return TRUE;
}

/********************************************************************************************

>	BOOL BitmapEffectBase::SetSourceImage(KernelBitmap * theSource)
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/94
	Inputs:		theSource is pointer to the bitmap to use, or NULL to unset it
	Outputs:	Records a pointer to the bitmap
	Returns:	TRUE if succeeded, FALSE & error set if not
	Purpose:	Sets up the effect to use a chosen bitmap
	Errors:		None from this one as yet
	SeeAlso:	-

Normally this would be overridden to check the bitmap was suitable.

********************************************************************************************/

BOOL BitmapEffectBase::SetSourceImage(KernelBitmap * theSource)
{
	Source = theSource;
	return TRUE;
}

/********************************************************************************************

>	BOOL BitmapEffectBase::GetEffectInfo(UINT32 * pOrderBitmap, UINT32 * pOrderEffect,
				   UINT32 * pPlotEstimate)
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/94
	Inputs:		None
	Outputs:	pOrderBitmap filled in with the order of the operation wrt size of bitmap
				pOrderEffect filled in with the order of the operation wrt size of effect
				pPlotEstimate filled in with the number of sprite plots this is roughly
					equivalent to in time terms.
	Returns:	TRUE if succeeded, FALSE & error set if not
	Purpose:	Gets information about the given effect
	Errors:		None from this one as yet
	SeeAlso:	-

This should be overridden to give the user some idea of how long a bitmap operation is going
to take, so they can be marked as fast, slow or whatever. If the source image is not set up,
pPlotEstimate should be returned as zero.

Any parameters passed as NULL will not be filled

********************************************************************************************/

BOOL BitmapEffectBase::GetEffectInfo(UINT32 * pOrderBitmap, UINT32 * pOrderEffect,
				   UINT32 * pPlotEstimate)
{
	
	if (pOrderBitmap) *pOrderBitmap=0;
	if (pOrderEffect) *pOrderEffect=0;
	if (pPlotEstimate) *pPlotEstimate=0;
	return(TRUE);
}

/********************************************************************************************

>	BOOL BitmapEffectBase::GetDestinationInfo(UINT32 * pDestinationSize,
									INT32 * pDestinationDepth,
									UINT32 * pDestinationWidth,
									UINT32 * pDestinationHeight)
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/94
	Inputs:		None
	Outputs:	pDestinationSize filled with size in bytes of dest bitmap
				pDestinationDepth filled with bpp of dest bitmap
				pDestinationWidth|Height filled with width height of dest in pixels
	Returns:	TRUE if succeeded, FALSE & error set if not
	Purpose:	Gets information about the given effect
	Errors:		Error2 if source hasn't been set up
	SeeAlso:	-

This should be overridden to give an accurate representation of what the dest bitmap will
look like. It is an	error to call this without setting the source up.

********************************************************************************************/


BOOL BitmapEffectBase::GetDestinationInfo(UINT32 * pDestinationSize,
									INT32 * pDestinationDepth,
									UINT32 * pDestinationWidth,
									UINT32 * pDestinationHeight)
{
	
	ERROR2IF(!Source,FALSE,"No source for bitmap effect");

	if (pDestinationSize) *pDestinationSize=0;
	if (pDestinationDepth) *pDestinationDepth=0;
	if (pDestinationWidth) *pDestinationWidth=0;
	if (pDestinationHeight) *pDestinationHeight=0;
	
	return(TRUE);
}


/********************************************************************************************

>	BOOL BitmapEffectBase::UseDestinationBitmap(KernelBitmap * theDestination)
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/94
	Inputs:		theDestination is pointer to the bitmap to use, or NULL to unset it
	Outputs:	Records a pointer to the dest bitmap
	Returns:	TRUE if succeeded, FALSE & error set if not
	Purpose:	Indicates the Run method should use this bitmap for output
	Errors:		None from this one as yet
	SeeAlso:	-

Normally this would be overridden to check the bitmap was suitable. The bitmap specified will
be used if specified, else a new KernelBitmap will be used. If the KernelBitmap does not have
an OilBitmap attached and created of the correct size, it will be created and attached.	If a
NULL is passed (this is the default situation) then a new KernelBitmap will be created.

This routine can also be called with NULL to indicate that responsibility for an output image
after a run has been assumed by the caller. The object won't destruct when it has a destination
bitmap.

********************************************************************************************/

BOOL BitmapEffectBase::UseDestinationBitmap(KernelBitmap * theDestination)
{
	Destination = theDestination;
	return TRUE;
}

/********************************************************************************************

>	KernelBitmap * BitmapEffectBase::GetDestination();
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/94
	Inputs:		None
	Outputs:	None
	Returns:	Pointer to destination imagwe
	Purpose:	Returns a pointer to the destination image
	Errors:		None from this one as yet
	SeeAlso:	-

The dest image will be present if it has been set using UseDestinationBitmap, or if the
effect has been run and UseDestinationBitmap has not been set to NULL subsequently.

********************************************************************************************/

KernelBitmap * BitmapEffectBase::GetDestination()
{
	return (Destination);
}

/********************************************************************************************

>	BOOL BitmapEffectBase::IsSourceSpecified();
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/94
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if source image is specified else false
	Purpose:	Indicates whether or a source image has been specified yet
	Errors:		None from this one as yet
	SeeAlso:	-

The source image will be specified if the last call to SetSourceImage was non null. Overridden
if multiple source images need to be specified.

********************************************************************************************/

BOOL BitmapEffectBase::IsSourceSpecified()
{
	return (Source != NULL);
}
								

/********************************************************************************************

>	BOOL BitmapEffectBase::IsAbleToRun();
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/94
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if you've done enough setting up to do a Run
	Purpose:	Indicates whether you've done enough setting up to do a Run
	Errors:		None from this one as yet
	SeeAlso:	-
 
For now just requires IsSourceSpecified

********************************************************************************************/

BOOL BitmapEffectBase::IsAbleToRun()
{
	return IsSourceSpecified();
}
					
/********************************************************************************************

>	BOOL BitmapEffectBase::Run();
					
	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/94
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if succeeded, FALSE if failed
	Purpose:	Runs a transform!
	Errors:		ERROR2 if called when parameters aren't set up properly
	SeeAlso:	-

It's obviously important to override this!

********************************************************************************************/

BOOL BitmapEffectBase::Run()
{
	ERROR2IF(!IsAbleToRun(),FALSE,"BitmapEffectRun called at inappropriate time");
	return TRUE;
}
