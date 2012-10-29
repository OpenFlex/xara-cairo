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

/* $Log*/
// 

#ifndef IDTOHRESULT_H
#define IDTOHRESULT_H

//#include "mario.h"
//#include "andy.h"
//#include "will.h"
//#include "ben.h"
//#include "justin.h"
//#include "tim.h"
//#include "rik.h"
//#include "filtrres.h"
//#include "nev.h"


#ifdef RALPH
// This associates a Error ID with an suitable HRESULT

struct ErrorMap
{
	UINT32 Err;				// Err ID
	HRESULT hr;				// mapped HRESULT
};
ErrorMap ErrorToHRESULT[] =
{

_R(IDE_BADMETAFILE),					RALPH_E_LOADFAILED,
_R(IDE_FILTERDLL_BADLOAD),				RALPH_E_LOADFAILED,
_R(IDE_FILTERDLL_NOIMPORT),				RALPH_E_LOADFAILED,
_R(IDE_MF_NOCREATE),					RALPH_E_LOADFAILED,
_R(IDE_MF_NOMEMLOCK),					RALPH_E_LOADFAILED,
_R(IDE_BADFORMAT),						RALPH_E_BADFILE,
_R(IDE_FILEREADERROR),					RALPH_E_LOADFAILED,
_R(IDE_FORMATNOTSUPPORTED),				RALPH_E_NONSUPPORTEDTYPE,
_R(IDE_CORELPALETTEFILTER_FILEERR),		RALPH_E_BADFILE,
_R(IDE_CORELPALETTEFILTER_BADPALFILE),	RALPH_E_BADFILE,
_R(IDE_CORELPALETTEFILTER_BADCPLFILE),	RALPH_E_BADFILE,
_R(IDE_CORELPALETTEFILTER_NOTCPLORPAL),	RALPH_E_BADFILE,
_R(IDE_CDRFILTER_FORMATERROR),			RALPH_E_BADFILE,
_R(IDE_CDRFILTER_NOTCDR),				RALPH_E_BADFILE,
_R(IDE_LOADCAMELOTEPSITHINKNOT),		RALPH_E_LOADFAILED,
_R(IDE_LOADCAMELOTEPSITHINKNOTNAMED),	RALPH_E_LOADFAILED,
_R(IDE_PALETTEIMPORT_ACOUNKNOWN),		RALPH_E_LOADFAILED,
_R(IDE_CREATE_VIEW_FAILED),    			RALPH_E_INTERNAL,
_R(IDE_DOC_ALREADY_OPEN),				RALPH_E_INTERNAL,
_R(IDE_NOMORE_MEMORY),					RALPH_E_OUTOFMEMORY,
_R(IDE_PATH_ERROR),						RALPH_E_LOADFAILED,
_R(IDE_BUFFER_ERROR),					RALPH_E_LOADFAILED,
_R(IDE_CLOSE_ERROR),					RALPH_E_LOADFAILED,
_R(IDE_OPEN_ERROR),						RALPH_E_LOADFAILED,
_R(IDE_EOF_ERROR),						RALPH_E_LOADFAILED,
_R(IDE_FILEPOS_ERROR),					RALPH_E_LOADFAILED,
_R(IDE_NOTOPEN_ERROR),					RALPH_E_LOADFAILED,
_R(IDE_NULL_FILE),						RALPH_E_LOADFAILED,
_R(IDE_FILE_SIZE_ZERO),					RALPH_E_LOADFAILED,
_R(IDE_NO_DOC_VIEW),					RALPH_E_INTERNAL,
_R(IDE_IO_ERROR),						RALPH_E_LOADFAILED,
_R(IDE_ZOPEN_ERROR),					RALPH_E_LOADFAILED,
_R(IDE_ZFILE_READ_ERROR),				RALPH_E_LOADFAILED,
_R(IDE_ZFILE_WRITE_ERROR),				RALPH_E_LOADFAILED,
_R(IDE_ZFILE_BASEEERROR),				RALPH_E_LOADFAILED,
_R(IDE_ZFILE_ERRORNO),					RALPH_E_LOADFAILED,
_R(IDE_ZFILE_STREAMERROR),				RALPH_E_LOADFAILED,
_R(IDE_ZFILE_DATAERROR),				RALPH_E_LOADFAILED,
_R(IDE_ZFILE_MEMORYERROR),				RALPH_E_OUTOFMEMORY,
_R(IDE_ZFILE_BUFFERERROR),				RALPH_E_LOADFAILED,
_R(IDE_FILE_READ_ERROR),				RALPH_E_LOADFAILED,
_R(IDE_FILE_PERM_DENIED),				RALPH_E_LOADFAILED,
_R(IDE_FILE_BAD_FILE),					RALPH_E_BADFILE,
_R(IDE_FILE_NO_SPACE),					RALPH_E_LOADFAILED,
_R(IDE_FILE_UNKNOWN),	 				RALPH_E_LOADFAILED,
_R(IDE_UNKNOWN_EPSOBJECT),				RALPH_E_LOADFAILED,
NULL, NULL
};

/********************************************************************************************

>	HRESULT GetHRESULTFromID(UINT32 Err)

	Author:		Chris_Snook (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/96				
	Purpose:	Linear search throuh ErrorMap lookup table to find a suitable
				HRESULT for a  given ID
	Input :		A Error resource ID
	Return :	Err->HRESULT
********************************************************************************************/

HRESULT GetHRESULTFromID(UINT32 Err)
{
	// Scan through the whole table.
	for (ErrorMap* pErrMap = ErrorToHRESULT;
		 pErrMap->Err != NULL;
		 pErrMap++)
	{
		// If the Error matches return the HRESULT.
		if ( Err == pErrMap->Err)
		{
			return pErrMap->hr;
		}
	}

	return RALPH_E_UNEXPECTED;
}

#endif
#endif
