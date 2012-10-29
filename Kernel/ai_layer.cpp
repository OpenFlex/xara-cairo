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
#include "ai5_eps.h"
#include "ai_layer.h"

CC_IMPLEMENT_DYNAMIC ( AILayerProcessor, CCObject )

/********************************************************************************************

>	AILayerProcessor::AILayerProcessor ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/4/00
	Purpose:	Default constructor.
	SeeAlso:	AILayerProcessor::~AILayerProcessor ()

********************************************************************************************/

AILayerProcessor::AILayerProcessor ( void )
{
	// Initialise all member variables to their default state.
	mLayerName.Empty ();			// Clear the layer name string.
	mIsLocked		= FALSE;		// Set the layer locked flag to FALSE.
	mIsPrintable	= FALSE;		// Set the layer printable flag to FALSE.
	mIsVisible		= FALSE;		// Set the layer visible flag to FALSE.
}

/********************************************************************************************

>	AILayerProcessor::~AILayerProcessor ( void )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/4/00
	Purpose:	Default destructor.
	SeeAlso:	AILayerProcessor::AILayerProcessor ()

********************************************************************************************/

AILayerProcessor::~AILayerProcessor ( void )
{
	// Nothing needs to be done.
}

/********************************************************************************************

>	BOOL AILayerProcessor::DecodeAI5Lb ( AI5EPSFilter	&Filter )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/4/00
	Inputs:		pFilter	- A pointer to the AI5EPSFilter being used for the export.
	Returns:	TRUE	- Success.
				FALSE	- An error has occurred.
	Purpose:	Extracts the layer information from the Lb record. The AI file format allows
				for more fine-grained control over the layers than the Camelot version, and
				so much of it is rejected.
	SeeAlso:	AILayerProcessor::DecodeLB (), AILayerProcessor::DecodeLn (),
				AI5EPSFilter::ProcessToken()

********************************************************************************************/

BOOL AILayerProcessor::DecodeAI5Lb ( AI5EPSFilter	&Filter )
{
	INT32	IsVisible	= 0;
	INT32	IsLocked	= 0;
	INT32	IsPrintable	= 0;
	
	// Pop the information off the stack.
	if ( !Filter.GetStack ().Discard ( 6 )			||	// Discard the unused data on the stack.
		 !Filter.GetStack ().Pop ( &IsPrintable )	||	// Extract whether it's printable.
		 !Filter.GetStack ().Pop ( &IsLocked )		||	// Extract whether the layer is locked.
		 !Filter.GetStack ().Discard ( 1 )			||	// Discard the unused flag.
		 !Filter.GetStack ().Pop ( &IsVisible ) )		// Extract the layer visibility data.
	{
		// There has been a problem extracting the data. Return a FALSE value to inform the
		// AIEPS filter.
		return FALSE;
	}

	// Set up the layer state flags from the information in the Lb operator. The default
	// state is false, so only one branch needs to be evaluated.
	if ( !IsLocked )
	{
		mIsLocked		= TRUE;							// Set the layer locked flag to TRUE.
	}

	if ( IsPrintable )
	{
		mIsPrintable	= TRUE;							// Set the printable flag to TRUE.
	}
	
	if ( IsVisible )
	{
		mIsVisible		= TRUE;							// Set the visible flag to TRUE.
	}

	// Success.
	return TRUE;
}

/********************************************************************************************

>	BOOL AILayerProcessor::DecodeAI8Lb ( AI5EPSFilter	&Filter )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/4/00
	Inputs:		pFilter	- A pointer to the AI5EPSFilter being used for the export.
	Returns:	TRUE	- Success.
				FALSE	- An error has occurred.
	Purpose:	The syntax of the Lb operator has changed in AI8, and this function is
				intended to handle the newer version.
	SeeAlso:	AILayerProcessor::DecodeAI5Lb (), AILayerProcessor::DecodeLB ()
				AILayerProcessor::DecodeLn (), AI8EPSFilter::ProcessToken ()

********************************************************************************************/

BOOL AILayerProcessor::DecodeAI8Lb ( AI5EPSFilter	&Filter )
{
	INT32	IsVisible	= 0;
	INT32	IsLocked	= 0;
	INT32	IsPrintable	= 0;
	
	// Pop the information off the stack.
	if ( !Filter.GetStack ().Discard ( 9 )			||	// Discard the unused data on the stack.
		 !Filter.GetStack ().Pop ( &IsPrintable )	||	// Extract whether it's printable.
		 !Filter.GetStack ().Pop ( &IsLocked )		||	// Extract whether the layer is locked.
		 !Filter.GetStack ().Discard ( 1 )			||	// Discard the unused flag.
		 !Filter.GetStack ().Pop ( &IsVisible ) )		// Extract the layer visibility data.
	{
		// There has been a problem extracting the data. Return a FALSE value to inform the
		// AIEPS filter.
		return FALSE;
	}

	// Set up the layer state flags from the information in the Lb operator. The default
	// state is false, so only one branch needs to be evaluated.
	if ( !IsLocked )
	{
		mIsLocked		= TRUE;							// Set the layer locked flag to TRUE.
	}

	if ( IsPrintable )
	{
		mIsPrintable	= TRUE;							// Set the printable flag to TRUE.
	}
	
	if ( IsVisible )
	{
		mIsVisible		= TRUE;							// Set the visible flag to TRUE.
	}

	// Success.
	return TRUE;
}

/********************************************************************************************

>	BOOL AILayerProcessor::DecodeLB ( AI5EPSFilter	&Filter )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/4/00
	Inputs:		pFilter	- A pointer to the AI5EPSFilter being used for the export.
	Returns:	TRUE	- Success.
				FALSE	- An error has occurred.
	Purpose:	Processes the LB command, which is the end of layer indicator.
	SeeAlso:	AILayerProcessor::DecodeLb (), AI5EPSFilter::ProcessToken()

********************************************************************************************/

BOOL AILayerProcessor::DecodeLB ( AI5EPSFilter	&Filter )
{
	// Push the insert point in the tree up a level, so that any future layers are inserted
	// in the correct place. This is done automatically by the EPSFilter class, so this
	// method is redundant.
	return TRUE;
}

/********************************************************************************************

>	BOOL AILayerProcessor::DecodeLn ( AI5EPSFilter	&Filter )

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/4/00
	Inputs:		pFilter	- A pointer to the AI5EPSFilter being used for the export.
	Returns:	TRUE	- Success.
				FALSE	- An error has occurred.
	Purpose:	Processes the Ln command, which is used to set the layer's name.
	SeeAlso:	AILayerProcessor::DecodeLb (), AI5EPSFilter::ProcessToken()

********************************************************************************************/

BOOL AILayerProcessor::DecodeLn ( AI5EPSFilter	&Filter )
{
	// Pop the layer's name off the stack, and store it in the mLayerName member variable.
	if ( !Filter.GetStack ().Pop ( &mLayerName ) )
	{
		// There's been a problem, so inform the filter that invoked this command.
		return FALSE;
	}

	// Create a new layer using the stored information.
	return Filter.CreateLayer ( mLayerName, mIsLocked, mIsPrintable, mIsVisible );
}
