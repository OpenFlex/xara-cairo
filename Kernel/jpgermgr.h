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

#ifndef INC_JPGERMGR
#define INC_JPGERMGR


//#include "filtrres.h"		// for Error string ID's

#include "jpglib_namespace.h"
#include "jerror.h"

typedef UINT32 StringID;
/********************************************************************************************

>	class JPEGErrorManager

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/08/96
	Purpose:   	Provides an error handler for the IJG JPEG Library.
				Specifically it uses standard Camelot practices to cope with errors
				generated within the library.
	Scope:		public

********************************************************************************************/
class JPEGErrorManager
{
public:
	enum ERROR_CLASS
	{
		ERR_NONE		= -1,
		ERR_STANDARD	= 0,
		ERR_TRACE		= 1,
		ERR_STRUCTURE	,//= _R(IDS_JPEG_ERROR_STRUCTURE),
		ERR_FORMAT		,//= _R(IDS_JPEG_ERROR_FORMAT),
		ERR_LIMITS		,//= _R(IDS_JPEG_ERROR_LIMITS),
		ERR_UNSUPPORTED ,//= _R(IDS_JPEG_ERROR_UNSUPPORTED),
		ERR_INTERNAL	,//= _R(IDS_JPEG_ERROR_INTERNAL)
	};

	JPEGErrorManager();

	void			ThrowError( StringID UserErrorMessage );

	ERROR_CLASS		GetLastErrorClass() const;
	J_MESSAGE_CODE	GetLastError() const;
	StringID		GetStringIDForError() const;
	const libJPEG::jpeg_error_mgr* GetErrorMgrStruct() const {return &m_errmgr;};
	libJPEG::jpeg_error_mgr* GetErrorMgrStruct() {return &m_errmgr;};

	static void		ErrorExit(libJPEG::j_common_ptr cinfo);
	static void		OutputMessage(libJPEG::j_common_ptr cinfo);
	static void		EmitMessage(libJPEG::j_common_ptr cinfo, INT32 msg_level);
	static void		ResetErrorManager(libJPEG::j_common_ptr cinfo);
protected:
	// Attributes
	libJPEG::jpeg_error_mgr		m_errmgr;
	ERROR_CLASS					m_ErrorClass;
	StringID					m_MessageID;

	static const ERROR_CLASS*	m_ErrorClassTable;
};



#endif	// INC_JPGERMGR
