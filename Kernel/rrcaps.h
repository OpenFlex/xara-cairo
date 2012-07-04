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

// The render region Caps class. This allows render regions to say what they can and can not
// render.

#ifndef INC_RRCAPS
#define INC_RRCAPS



/********************************************************************************************

>	class RRCaps : public CC_CLASS_MEMDUMP

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/4/95
	Purpose:	This class has been designed to hold all the different things that a render
				region may or may not be able to render. eg. Some render regions can render
				transparency, while others can not. This class is used to record what your
				render region can do. It does this by having a flag for all the area of
				rendering that some regions can do and other can not. By default this
				class assumes that you can do nothing, so it is up to you to set the flags
				for the things you can do to TRUE. TRUE means you can render that type of
				thing, FALSE means that you can not. The flags to date are :-

						BOOL Transparency;
						BOOL GradFills;
						BOOL PerspectiveGradFills;
						BOOL BitmapFills;
						BOOL PerspectiveBitmapFills;
						BOOL LineAttrs;
						BOOL ArrowHeads;
						BOOL DashPatterns;

********************************************************************************************/

class RRCaps : public CC_CLASS_MEMDUMP
{
	// Give my name in memory dumps
	CC_DECLARE_MEMDUMP(RRCaps);

public:
	// Construction / destruction
	RRCaps();
	RRCaps(const RRCaps& Other);
	~RRCaps();

	// operator= thing for copying them
	RRCaps& operator=(const RRCaps &Other);

	// Functions to set the flag to defaults
	void CanDoAll();
	void CanDoNothing();

	// Function to see if the region is fabby
	BOOL DoesRegionDoAll();
	BOOL DoesRegionDoNothing();

	// This is really a struct, so all the members are public.
	// I have made it a class so we get all the MEMDUMP stuff
	// Don't forget to change the class comment if you add or remove one of these
	BOOL Transparency;
	BOOL GradFills;
	BOOL PerspectiveGradFills;
	BOOL BitmapFills;
	BOOL PerspectiveBitmapFills;
	BOOL SimpleBitmaps;
	BOOL ArbitraryBitmaps;
	BOOL ClippedSimpleBitmaps;
	BOOL ClippedArbitraryBitmaps;
	BOOL LineAttrs;
	BOOL ArrowHeads;
	BOOL DashPatterns;
	BOOL Grad3and4Fills;
	BOOL ClippedOutput;
};

#endif  // INC_RRCAPS
