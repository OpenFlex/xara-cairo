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


// Operations to save in the version 2 Native/Web format.
// Loading ops are not required as the general open operation will open any format file.

#ifndef INC_WEBOP
#define INC_WEBOP

#include "nativeop.h"

#define	OPTOKEN_SAVEASWEB			_T("SaveAsWeb")
#define	OPTOKEN_SAVEASNATIVEV2		_T("SaveAsNativeV2")

/********************************************************************************************

>	class OpSaveAsWeb : public OpMenuSave

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/96
	Purpose:	Saves the document to the file specified in the params to the disk using the
				Web format.

********************************************************************************************/

class OpSaveAsWeb : public OpMenuSave
{
	CC_DECLARE_DYNCREATE(OpSaveAsWeb)

public:
	// Use the base class versions of Do and DoWithParam

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);

protected:
	virtual UINT32 GetSearchFilterId();
	virtual BOOL FixFileType();
};

/********************************************************************************************

>	class OpSaveAsNativeV2 : public OpMenuSave

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/96
	Purpose:	Saves the document to the file specified in the params to the disk using the
				Version 2 Native format.

********************************************************************************************/

class OpSaveAsNativeV2 : public OpMenuSave
{
	CC_DECLARE_DYNCREATE(OpSaveAsNativeV2)

public:
	// Use the base class versions of Do and DoWithParam

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);

protected:
	virtual UINT32 GetSearchFilterId();
	virtual BOOL FixFileType();
};


#endif  // INC_WEBOP

