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

// InternalClipboardFormat - a simple class to describe an internal clipboard format
// (A class is used so that we need not change node.h if we wish to change the contents)


#ifndef INC_CLIPTYPE
#define INC_CLIPTYPE


// Clipboard formats. New formats can be used by external parties by defining an unused value
const INT32 CLIPTYPE_NONE		= 0;
const INT32 CLIPTYPE_VECTOR	= 1;
const INT32 CLIPTYPE_TEXT		= 2;
const INT32 CLIPTYPE_BITMAP	= 3;



/********************************************************************************************

>	class InternalClipboardType : public CC_CLASS_MEMDUMP

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/95
	
	Purpose:	This class is a very simple class which describes an internal clipboard
				data format. Each ClipboardMapping uses one of these to describe the type
				of input data they require in order to export, and thes export mappings
				will only be available to the clipboard if at least one node in the
				InternalClipboard supports output in this internal format.
				
				These formats are (currently):
					CLIPTYPE_VECTOR, CLIPTYPE_TEXT, CLIPTYPE_BITMAP.

				VECTOR includes all nodes, and is always assumed to be exportable.
				i.e. it's an "I can always export" thing.

				TEXT includes text characters only (text can be exported as paths or
				as unicode text). That is, an export mapping that supports Text can
				export text characters only, so will not be placed upon the clipboard
				unless there is some text somewhere on the clipboard.

				BITMAP is used for exporting bitmap fills as simple bitmaps. i.e. If no
				bitmap fills are on the clipboard, Bitmap mappings will not be available.

	SeeAlso:	ExternalClipboard; Node::SupportsClipboardFormat; ClipboardMapping

*********************************************************************************************/

class CCAPI InternalClipboardFormat : public CC_CLASS_MEMDUMP
{
// See clipext.cpp for the IMPLEMENT section
CC_DECLARE_MEMDUMP(InternalClipboardFormat)

public:
	InternalClipboardFormat() 				{ FormatID = CLIPTYPE_NONE; }
	InternalClipboardFormat(INT32 Format)		{ FormatID = Format; }

	BOOL IsSameFormat(InternalClipboardFormat &OtherFormat) const	\
											{ return(FormatID == OtherFormat.FormatID); }
		// Returns TRUE if the formats are the same

public:		// Intended only for use by ClipboardMapping class
	void SetFormatID(INT32 Format)			{ FormatID = Format; }
	INT32 GetFormatID(void)					{ return(FormatID); }


protected:
	INT32 FormatID;
};


#endif

