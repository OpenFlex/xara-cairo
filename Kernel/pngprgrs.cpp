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


// PNG progress bar code
// Jonathan Payne 8/2000

#include "camtypes.h"
#include "png.h"
#include "pngprgrs.h"
#include "progress.h"		// For hourglass stuff

// An implement to match the Declare in the .h file.
CC_IMPLEMENT_MEMDUMP(PNGProgressBar, CC_CLASS_MEMDUMP)

/********************************************************************************************

>	PNGProgressBar::PNGProgressBar(String_64 *ProgressString, bool new_interlaced, UINT32 new_height)

	Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/8/2000
	Inputs:		ProgressString
	Outputs:	Progress bar on screen
	Returns:	void
	Purpose:	Constructor.  Sets show_progress_bar.  If ProgressString != NULL, starts
				prorgress bar.
	Scope:		Public

********************************************************************************************/

PNGProgressBar::PNGProgressBar(String_64 *ProgressString, bool new_interlaced, UINT32 new_height)
{
	interlaced = new_interlaced;
	height = new_height;

	if (ProgressString != NULL)
	{
		show_progress_bar = true;
		if (interlaced)
		// An interlaced image
		{
			// PNG interlaced files always have 7 passes so use 7 as
			// final value for status bar
			BeginSlowJob(8, FALSE, ProgressString);

			// Next update the status bar at pass 0
			next_update = 0;
		}
		else
		// A non-interlaced image
		{
			BeginSlowJob(height, FALSE, ProgressString);
			
			// Update the status bar on row 0
			next_update = 0;
		}
	}
	else
	{
		show_progress_bar = false;
	}
}

/********************************************************************************************

>	PNGProgressBar::~PNGProgressBar()

	Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/8/2000
	Outputs:	Removes progress bar from screen
	Returns:	void
	Purpose:	Constructor.  Sets show_progress_bar.  If ProgressString != NULL, starts
				prorgress bar.
	Scope:		Public

********************************************************************************************/

PNGProgressBar::~PNGProgressBar()
{
	// If started, then stop then progress bar
	if (show_progress_bar)
		EndSlowJob();
}

void PNGProgressBar::UpdateCallback(png_structp png_ptr, png_uint_32 row_number, INT32 pass)
{
	if (show_progress_bar)
	{
		if (interlaced)
		// Interlaced image
		{
			if (pass + 1 >= next_update)
				ContinueSlowJob(pass + 1);
		}
		else
		// Non-interlaced image
		{
			if ((INT32)row_number >= next_update)
				ContinueSlowJob(row_number);
		}
	}
}
