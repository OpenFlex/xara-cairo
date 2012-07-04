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
#include "webparam.h"

// This is not compulsory, but you may as well put it in so that the correct version
// of your file can be registered in the .exe
DECLARE_SOURCE("$Revision: 820 $");

// An implement to match the Declare in the .h file.
// If you have many classes, it is recommended to place them all together, here at the start of the file
CC_IMPLEMENT_MEMDUMP	( WebPrefsDlgParam,	OpParam )

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW

/******************************************************************************************

>	WebPrefsDlgParam::WebPrefsDlgParam()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/04/2006
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	WebPrefsDlgParam constructor
	Errors:		-
	Notes:		Seems that GCC needs to have at least one non-inline function or
				else it gets confused.

******************************************************************************************/

WebPrefsDlgParam::WebPrefsDlgParam()
{
	ViewportSel				= DRAWING;
	ExportSel				= DRAWING;
	BmpCompression			= 100;
	Compression				= TRUE;
	ExportPreviewBitmap		= FALSE;
	ConvertTextToOutlines	= TRUE;
	WebOk					= FALSE;
	HTMLToClipboard			= FALSE;
	ConvertBlendsToOutlines	= FALSE;
};




