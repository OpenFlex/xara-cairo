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

// Operation to load and save in the Native EPS format.
// These ops are initiated from the File Save / Load menu options eventually

#ifndef INC_NATIVEOP
#define INC_NATIVEOP



#define	OPTOKEN_NATIVELOAD		wxT("NativeLoad")
#define	OPTOKEN_NATIVESAVE		wxT("NativeSave")
#define	OPTOKEN_SAVEASNATIVEV1	wxT("SaveAsNativeV1")
#define OPTOKEN_SAVEASDEFAULT	wxT("SaveAsDefault")

// Forward references.
class CCLexFile;


// These are the parameters that the native file Operations take.  They are passed by
// pointer to the Operations as the first parameter of the OpParam.
struct NativeFileOpParams
{
	CCLexFile* pFile;
	BOOL	   fStatus;
	UINT32	   nPrefFilter;
};


// This global function is a useful shorthand for the rigmarole you have to go through
// to invoke Operations.  It returns TRUE if the given Operation on the given file is
// successful.
BOOL InvokeNativeFileOp(const TCHAR* pOpName, CCLexFile* pFile, UINT32 nPrefFilter);



/********************************************************************************************

>	class OpMenuLoad : public SelOperation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/12/94
	Purpose:	Imports the specified file as NativeEPS.

********************************************************************************************/

class OpMenuLoad : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpMenuLoad)

public:
	virtual void DoWithParam(OpDescriptor*, OpParam* pOpParam);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }

protected:
	BOOL LoadFile(CCLexFile* pFileToLoad, UINT32 nPrefFilter);
};



/********************************************************************************************

>	class OpMenuSave : public Operation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/12/94
	Purpose:	Saves the document to the file specified in the params to the disk using the
				NativeEPS format.

********************************************************************************************/

class OpMenuSave : public Operation
{
	CC_DECLARE_DYNCREATE(OpMenuSave)

public:
	virtual void DoWithParam ( OpDescriptor*, OpParam* pOpParam );
	virtual void Do ( OpDescriptor* pOpDesc );

	static BOOL Init ();
	static OpState GetState (String_256*, OpDescriptor*);

protected:
	virtual BOOL FindFilterAndSave ( CCLexFile* pFile, UINT32 nPrefFilter );
	virtual Filter* FindFilter ( UINT32 nPrefFilter );
	virtual BOOL Save ( Filter *pFilter, CCLexFile* pFile );
	virtual BOOL SaveSpecificFile ( Filter*, CCLexFile* pFile );

	virtual UINT32 GetSearchFilterId ();
	virtual BOOL EnsureFileTypeCorrectId (Filter *pFilter, PathName& Path);
	virtual BOOL FixFileType ();
};

/********************************************************************************************

>	class OpSaveAsNativeV1 : public OpMenuSave

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/8/96
	Purpose:	Saves the document to the file specified in the params to the disk using the
				Version 1 Native format i.e. Native EPS.

********************************************************************************************/

class OpSaveAsNativeV1 : public OpMenuSave
{
	CC_DECLARE_DYNCREATE(OpSaveAsNativeV1)

public:
	// Use the base class versions of Do and DoWithParam

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);

protected:
	virtual UINT32 GetSearchFilterId();

	virtual BOOL FixFileType();
};



#endif  // INC_NATIVEOP

