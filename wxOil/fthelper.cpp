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

#include "fthelper.h"
#include "fileutil.h"
#define NO_CAMTYPES
#include "templman.h"	// Scary bits

#include "txtmacro.h"	// MFC/ATL text converion macros
//#include "resource.h"	// out of memory error
//#include "filtrres.h"

extern "C"
{
//	const IID IID_IFTManipulator = {0x31A6E651,0xEBA2,0x11D0,{0x8C,0x33,0x00,0xA0,0x24,0x72,0x9D,0xDE}};
	const IID IID_IFTManipulator = {0x7B14A5DD,0xAA72,0x403b,{0xB0,0x1C,0x12,0x56,0xCA,0xF6,0x9D,0x67}};
//	const CLSID CLSID_FTManipulator = {0x31A6E652,0xEBA2,0x11D0,{0x8C,0x33,0x00,0xA0,0x24,0x72,0x9D,0xDE}};
	const CLSID CLSID_FTManipulator = {0x424C099D,0x6A26,0x4fea,{0xA5,0x66,0x45,0xCD,0xB0,0xEF,0x06,0x94}};
}


//-----------------------------------------------

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW

/********************************************************************************************

>	CCLexFile* FlareTemplateHelper::ConvertFile(CCLexFile* pFile)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/97
	Purpose:	Default constructor
	SeeAlso:	-

********************************************************************************************/

CCLexFile* FlareTemplateHelper::ConvertFile(CCLexFile* pFile)
{
	ERROR2IF(pFile == NULL, FALSE, "NULL file in FTHelper::ConvertFile");

	String_256 InputFile = pFile->GetPathName().GetPath();

	if (InputFile.IsEmpty())
		return(NULL);

	BSTR pInputName = T2BSTR((TCHAR*)InputFile);
	if (pInputName == NULL)
	{
		Error::SetError(_R(IDS_OUT_OF_MEMORY));
		return(NULL);
	}

	HRESULT hr = S_OK;
	CCDiskFile* pNewFile = NULL;

	IFTManipulator* pTemplMan = CreateTemplMan();
	if (pTemplMan != NULL)
	{
		// Initialise the manipulator object
		HRESULT hr = pTemplMan->Init(pInputName);
		if (SUCCEEDED(hr))
		{
			PathName TempPath = FileUtil::GetTemporaryPathName();
			String_256 OutFile = TempPath.GetPath();
			if (!OutFile.IsEmpty())
			{
				// Get file name as a BSTR
				BSTR pOutputName = T2BSTR((TCHAR*)OutFile);
				// And process it (will fail if NULL)
				hr = pTemplMan->ProcessTemplateToFile(pOutputName);
				if (SUCCEEDED(hr))
				{
					// Create a default diskfile
					pNewFile = new CCDiskFile();
					if (pNewFile != NULL)
					{
						if (!pNewFile->open(TempPath, ios::in | ios::binary))
						{
							// If we failed then delete the file
							// and set the pointer to NULL for return
							delete pNewFile;
							pNewFile = NULL;
						}
					}
				}
				SysFreeString(pOutputName);
			}
		}
		// Release the interface
		pTemplMan->Release();
		pTemplMan = NULL;
	}

	if (FAILED(hr))
	{
		SetHResultError(hr);		// set the error
		ERROR3IF(pNewFile != NULL, "ConvertFile failed but created new file");
	}

	// Free the input BSTR
	SysFreeString(pInputName);

	return(pNewFile);
}


/********************************************************************************************

>	static IFTManipulator* FlareTemplateHelper::CreateTemplMan(void)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/97
	Returns:	IFTManipulator pointer or NULL if error
	Purpose:	Creates a FlareTemplateManipulator object
	Errors:		

********************************************************************************************/

IFTManipulator* FlareTemplateHelper::CreateTemplMan(void)
{
	IFTManipulator* pTemplMan = NULL;
		
	// Create an FTManipulator object
	HRESULT hr = CoCreateInstance(CLSID_FTManipulator,
									NULL,
									CLSCTX_INPROC_SERVER,
									IID_IFTManipulator,
									(void**)&pTemplMan);

	if (SUCCEEDED(hr))
	{
		return(pTemplMan);
	}
	else
	{
		SetHResultError(hr);
		return(NULL);
	}
}

/********************************************************************************************

>	static void FlareTemplateHelper::SetHResultError(HRESULT hr)

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/97
	Purpose:	Sets an error from a TemplMan error HRESULT

********************************************************************************************/

void FlareTemplateHelper::SetHResultError(HRESULT hr)
{
	if (SUCCEEDED(hr))
		return;

	INT32 ErrorID = _R(IDS_TEMPLMAN_BAD_TEMPLATE);	// Default error
	INT32 PostFixID = 0;

	switch (hr)
	{
		case REGDB_E_CLASSNOTREG:
			ErrorID = _R(IDS_TEMPLMAN_NOT_INSTALLED);
			break;
	
		case E_OUTOFMEMORY:
			ErrorID = _R(IDS_OUT_OF_MEMORY);
			break;

		case E_BADTEMPLATE:
			break;

		case E_BADRECORD:
			{
				PostFixID = _R(IDS_TEMPLMAN_BAD_RECORD);
				break;
			}
		case E_BADDATAITEM:
			{
				PostFixID = _R(IDS_TEMPLMAN_BAD_DATA_ITEM);
				break;
			}
		default:
			{
				Error::SetError(_R(IDS_NOT_A_FLARETEMPLATE_FILE));
				return;
			}
	}

	String_256 strError;

	if (!strError.Load(ErrorID))			// Try to load the string
	{
		Error::SetError(ErrorID);			// Just set the error if it fails
		return;
	}

	if (PostFixID != 0)
	{
		String_256 strPostFix;
		if (!strPostFix.Load(PostFixID))	// Load the postfix string
		{
			Error::SetError(ErrorID);		// Just set the error if it fails
			return;
		}
		strError += strPostFix;				// and append it
	}

	// And set the error
	Error::SetError(ErrorID, strError, 0);		// Why doesn't the module param default to 0
}
