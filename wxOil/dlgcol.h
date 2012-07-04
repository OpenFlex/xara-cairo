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

// Support for kernel use of host Operating System dialogue rendering colours


#ifndef INC_DLGCOL
#define INC_DLGCOL


//#include "doccolor.h" - in camtypes.h [AUTOMATICALLY REMOVED]


/***********************************************************************************************

>	class DialogColourInfo : public CC_CLASS_MEMDUMP

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/11/94

	Purpose:	Most host operating systems supply applications with a set of colours
				to be used for rendering special parts of dialogues, e.g. window
				background, plinth colours, default text foreground/background colours,
				selection highlight colours, etc.
				
				This class provides a means by which kernel entities can find out the
				required colours for various standard dialogue components.

				The methods provided by this class return a reference to a static DocColour,
				as in:	DocColour &DialogBack(void);
				DO NOT alter the contents of any of these colours!

				Note that if you create a DialogColourInfo on the fly each time you redraw,
				the colours are guaranteed to be kept up to date; but if you keep one around
				permanently, then they may not be updated correctly if the host OS changes
				its colour scheme (As can be done under Windows with the control panel).
				Hence, you should either recreate the object, or call its RecacheColours
				method before each redraw.

				The methods provide the following colours:
				MonoOn
					DialogBack()			// Dialogue window background colour

					TextBack()				// Text background colour
					TextFore()				// Text foreground colour

					DisabledTextFore()		// Text foreground colour (when shaded)

					HighlightedTextBack()	// Text background colour (when selected)
					HighlightedTextFore()	// Text foreground colour (when selected)

					ButtonFace()			// Button face colour
					ButtonHighlight()		// Button/plinth highlight colour
					ButtonShadow()			// Button/plinth shadow colour
				MonoOff
				
				Example:
				MonoOn
					if (pRender != NULL)
					{
						DialogColourInfo RedrawColours;
						pRender->SetLineColour(RedrawColours.DialogBack());
						...
					}
				MonoOff

	
	SeeAlso:	DialogOp::GetHostColours

***********************************************************************************************/


class DialogColourInfo : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(DialogColourInfo)

public:
	// Constructor
	DialogColourInfo();

	
	// Call which recaches all the OS colours. Called on windows WM_SYSCOLORCHANGE message
	static void RecacheColours(void);


	// External methods to retrieve the colours
	inline DocColour &DialogBack(void)			{ return mDialogBack; };

	inline DocColour &TextBack(void)			{ return mTextBack; };
	inline DocColour &TextFore(void)			{ return mTextFore; };

	inline DocColour &DisabledTextFore(void)	{ return mDisabledTextFore; };

	inline DocColour &HighlightedTextBack(void)	{ return mHighlightedTextBack; };
	inline DocColour &HighlightedTextFore(void)	{ return mHighlightedTextFore; };

	inline DocColour &ButtonFace(void)			{ return mButtonFace; };
	inline DocColour &ButtonHighlight(void)		{ return mButtonHighlight; };
	inline DocColour &ButtonShadow(void)		{ return mButtonShadow; };


private:
	static DocColour mDialogBack;				// Dialogue window background colour

	static DocColour mTextBack;					// Text background colour
	static DocColour mTextFore;					// Text foreground colour

	static DocColour mDisabledTextFore;			// Text foreground colour (when shaded)

	static DocColour mHighlightedTextBack;		// Text background colour (when selected)
	static DocColour mHighlightedTextFore;		// Text foreground colour (when selected)

	static DocColour mButtonFace;				// Button face colour
	static DocColour mButtonHighlight;			// Button/plinth highlight colour
	static DocColour mButtonShadow;				// Button/plinth shadow colour
};

#endif

