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


// brush name dialog implementation
#ifndef BRSHNAME
#define BRSHNAME

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "brshcomp.h"

/********************************************************************************************
>	class CCAPI CBaseBrushNameDlg : public DialogOp
	class CCAPI CBrushNameDlg : public CBaseBrushNameDlg

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/2000
	Purpose:	Base class for the dialog that is used to name or rename brushes
	SeeAlso:	DialogOp
********************************************************************************************/

class CBaseBrushNameDlg : public DialogOp
{         
CC_DECLARE_DYNAMIC(CBaseBrushNameDlg)
static BOOL m_bModeless;
protected:
	// Creation & destruction.
	CBaseBrushNameDlg(CDlgResID idRes, CDlgMode nMode);

	// Description of what is to be (re)named.
	virtual StringBase* GetDescription(StringBase* pstrDesc) = 0;

	// A suggestion for the (re)name.
	virtual StringBase* GetSuggestion(StringBase* pstrDesc) = 0;

	// Returns zero if valid, the ID of an explanative error string if not.
	virtual UINT32 IsValid(const StringBase& strName);

	// This is called when the user enters a valid name and clicks the OK button.
	virtual BOOL DoCommit(const StringBase& strName) = 0;

	virtual void HandleCancel() {};

	// Event handlers.
	virtual void Do(OpDescriptor*);
	virtual void DoWithParam(OpDescriptor*,  OpParam* pParam);
	virtual MsgResult Message(Msg* pMessage);

	// Helper that sets the text in the static and edit controls, the initial focus etc.
	virtual void InitGadgetText(String_32* pString = NULL, BOOL resizeDialog = TRUE) = 0;

protected: //data
	BrushHandle m_BrushHandle;

	// Data.
	String_32 m_strSuggest;

	
};


/********************************************************************************************
	class CBrushNameDlg : public CBaseBrushNameDlg
	class  CRenameBrushDlg : public CBaseBrushNameDlg

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/2000
	Purpose:	dialog that is used to name brushes
	SeeAlso:	DialogOp
********************************************************************************************/

#define OPTOKEN_NAME_BRUSH_DLG			_T("NameBrushDlg")

class CNameBrushDlg  : public CBaseBrushNameDlg
{	
	CC_DECLARE_DYNCREATE(CNameBrushDlg);

public:
	static BOOL Init();
	static	OpState		GetState (String_256*,  OpDescriptor*);
protected:
	CNameBrushDlg();

	virtual StringBase* GetDescription(StringBase* pstrDesc);
	virtual StringBase* GetSuggestion(StringBase* pstrDesc);
	virtual UINT32 IsValid(const StringBase& strName);
	virtual BOOL DoCommit(const StringBase& strName);
	virtual void InitGadgetText(String_32* pString = NULL, BOOL resizeDialog = TRUE);
};



/********************************************************************************************
	class CInitBrushNameDlg : public CNameBrushDlg


	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/2000
	Purpose:	this is the initial dialog that is brought up to name the brush upon creation
				it differs from the above class in that this naming is not undoable
	SeeAlso:	DialogOp
********************************************************************************************/

#define OPTOKEN_INITNAME_BRUSH_DLG			_T("InitNameBrushDlg")

class CInitBrushNameDlg : public CNameBrushDlg
{
	CC_DECLARE_DYNCREATE(CInitBrushNameDlg)
	
public:
	static BOOL Init();
	static	OpState		GetState (String_256*,  OpDescriptor*);

protected:
	CInitBrushNameDlg();
	virtual BOOL DoCommit(const StringBase& strName);
	virtual void HandleCancel();
	virtual void InitGadgetText(String_32* pString = NULL, BOOL resizeDialog = TRUE);
};
#endif
