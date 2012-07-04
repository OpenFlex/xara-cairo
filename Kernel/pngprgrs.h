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


#ifndef INC_PNGPRGRS
#define	INC_PNGPRGRS

//#include "ccfile.h"

/********************************************************************************************

>	class PNGProgressBar : public CC_CLASS_MEMDUMP

	Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/8/2000
	Purpose:	Controls the status bar while loading / saving png files

********************************************************************************************/

class PNGProgressBar : public CC_CLASS_MEMDUMP
{
public:
	// Give name in memory dumps
	CC_DECLARE_MEMDUMP(PNGProgressBar);

	// Start status bar
	PNGProgressBar(String_64 *ProgressString, bool new_interlaced, UINT32 new_height);

	// Stop status bar
	~PNGProgressBar();

	// Function given as a pointer to libpng
	void UpdateCallback(png_structp png_ptr, png_uint_32 row_number, INT32 pass);

protected:
	PNGProgressBar();		// Default constructor - Do not use

private:
	bool	show_progress_bar;		// Show progress bar?
	bool	interlaced;			// Is the image interlaced
	UINT32	height;				// Image height
	INT32		next_update;		// Next value to update status bar at
								// For interlaced image this = pass
								// for non-interlaced image it is based on image height
//	const UINT32 updates = 10		// Number of updates of status bar (non-interlaced images
								// only)
};

#endif//INC_PNGPRGRS
