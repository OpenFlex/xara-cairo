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

//
//	Platform-dependent implementation of a function to determine the handle of a file.
//	Uses MFC 2.0
//
//

/*
*/

#include "camtypes.h"
//#include "ensure.h"
//#include "ccfile.h"	// main ccfile class definitions - in camtypes.h [AUTOMATICALLY REMOVED]
//#include <io.h>		// _get_osfhandle

// This is not compulsory, but you may as well put it in so that the correct version
// of your file can be registered in the .exe
DECLARE_SOURCE("$Revision: 1282 $");

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW


/********************************************************************************************

>	filedesc CCDiskFile::GetFileHandle( ) 

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/09/94
	Inputs:		None 
	Outputs:	None
	Returns:	The file handle (descriptor) for this file (really an INT32).
	Purpose:	Given an instance of a CCDiskFile, you can ask for the actual file handle
				that describes the associated file. Required for the external filters. 
	Errors:		None
	SeeAlso:	CCDiskFile::Size	

********************************************************************************************/
filedesc CCDiskFile::GetFileHandle() const 
{
	PORTNOTETRACE("other","CCDiskFile::GetFileHandle - do nothing");
#ifndef EXCLUDE_FROM_XARALX
	// Need to convert this into a real file handle rather than the descriptor.
	// At present there seems to be no legal way of doing this.
	return _get_osfhandle(GetFileStream().fd());
#endif

	return 0;
}
