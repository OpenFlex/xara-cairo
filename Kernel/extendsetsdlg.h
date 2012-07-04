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

// Interface of the ExtendSetsDlg class.

#ifndef INC_EXTENDSETSDLG
#define INC_EXTENDSETSDLG

#include "chcklist.h"	// for CTextCheckListBox
#include "extender.h"	// for bitwise extend-type flags
//#include "dialogop.h"	// for DialogOp - in camtypes.h [AUTOMATICALLY REMOVED]

class SGNameItem;


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



/********************************************************************************************
>	class ExtendSetsDlg : public DialogOp

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/10/1999
	Purpose:	Dialog to allow the user to choose which named sets are extended
				by which other named sets.
********************************************************************************************/

#define OPTOKEN_EXTENDSETSDLG _T("ExtendSetsDlg")

class ExtendSetsDlg : public DialogOp
{
	// runtime class creation stuff.
	CC_DECLARE_DYNCREATE(ExtendSetsDlg);

/////////////////////////////////////////////////////////////////////////////////////////////
//
//	Member functions.
//

public:
	// constructor, destructor & initialisation.
	ExtendSetsDlg();
	~ExtendSetsDlg();
	static BOOL Init();

	// dialog creation.
	void Do(OpDescriptor*);
	void DoWithParam(OpDescriptor* pOp, OpParam* pParam);

	// Operations (functions that other objects call)
	virtual	MsgResult Message(Msg* Message);
	static	OpState GetState(String_256*, OpDescriptor*);

	// Ask this dialog for a list of named sets ticked in the checklist.
//	List* GetNamedSets();

protected:
	// dialog creation.
	BOOL Create();
	BOOL SetUpControls();

	// list-of-named-set manipulation.
	BOOL FillCheckListBox();
	void GenerateListOfSets();



/////////////////////////////////////////////////////////////////////////////////////////////
//
//	Member variables.
//

public:
	// Dialog ID and type (modal/modeless).
	static const UINT32 IDD;
	static const CDlgMode Mode;

protected:
	// pointer to the one and only instance of this dialog.
	// should this be used or dropped? not sure yet.
	static ExtendSetsDlg* TheDialog;

	// a pointer to the named set which defines the extension.
	BYTE*			m_bArrayExtendFlags;	// array of bytes describing which sets stretch.
	SGNameItem*		m_pDefineExtendSet;		// pointer to named set which defines extension.
	BOOL*			m_pbCommit;				// pointer we can use to flag OK or Cancel.
	BYTE*			m_pfExtendFlags;		// ptr to flags we can set for extend behaviour.

	// listbox of sets which the user can choose from.
	CTextCheckListBox m_tclbExtendingSets;

	// constants used as indices into the extend behaviour combo-boxes.
	static const INT32 EXTEND_BEHAVIOUR_NONE;
	static const INT32 EXTEND_BEHAVIOUR_EXTEND;
	static const INT32 EXTEND_BEHAVIOUR_STRETCH;
};



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



/********************************************************************************************
>	class OpParamExtendSetsDlg : public OpParam

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/11/1999
	Purpose:	A parameter class for creating the ExtendSetsDlg with.
	See also:	ExtendSetsDlg.
	Errors:		ERROR2RAW if the default constructor is called.
********************************************************************************************/

class OpParamExtendSetsDlg : public OpParam
{
public:
	OpParamExtendSetsDlg()
	{
		ERROR2RAW("OpParamExtendSetsDlg default constructor should not be called!");
		m_bArrayExtendFlags	= NULL;
		m_pDefineExtendSet	= NULL;
		m_pbCommit			= NULL;
		m_pfExtendFlags		= NULL;
	}

	OpParamExtendSetsDlg(	BYTE* bArrayExtendFlags, SGNameItem* pDefineExtendSet,
							BOOL* pbCommit, BYTE* pfExtendFlags )
	{
		m_bArrayExtendFlags	= bArrayExtendFlags;
		m_pDefineExtendSet	= pDefineExtendSet;
		m_pbCommit			= pbCommit;
		m_pfExtendFlags		= pfExtendFlags;
	}

	BYTE* m_bArrayExtendFlags;		// an array of bytes, one for each named set - whether it
									// should be ticked in the dialog, (visible? enabled?).
	SGNameItem* m_pDefineExtendSet;	// the named set which is being extended.
	BOOL* m_pbCommit;				// ptr to a BOOL denoting whether OK or Cancel pressed.
	BYTE* m_pfExtendFlags;			// ptr to a bitwise set of flags for extend behaviour.
};



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



#endif	// !INC_EXTENDSETSDLG
