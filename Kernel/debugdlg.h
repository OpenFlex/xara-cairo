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

// debugdlg.h - The DebugDlg class

#ifndef INC_DEBUGDLG
#define INC_DEBUGDLG




#define OPTOKEN_DEBUGDLG _T("DebugDlg")


// This class only occurs in debug builds
#if _DEBUG

/********************************************************************************************

>	class DebugDlg: public DialogOp

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/5/96
	Purpose:	Allows us to invoke simple debug options without having to write entire Ops

	Notes:		See these functions for details:
	SeeAlso:		DebugDlg::InvokeCommand;
					DebugDlg::SetCommandList;
					DebugDlg::SetCommandValue;

********************************************************************************************/

class DebugDlg : public DialogOp
{         
CC_DECLARE_DYNCREATE(DebugDlg)

public:		// DialogOp interface
	DebugDlg();
	virtual ~DebugDlg();

	BOOL Create(); 

	static const INT32 IDD;
	static const CDlgMode Mode;

	static OpState GetState(String_256*, OpDescriptor*);	
	static BOOL Init();                        

	void Do(OpDescriptor*);

	virtual MsgResult Message(Msg* Message);

protected:
	void SetGroupList(void);
	void SetCommandList(INT32 GroupIndex);
	void SetCommandValue(INT32 GroupIndex, INT32 CommandIndex);
	void InvokeCommand(INT32 GroupIndex, INT32 CommandIndex, StringBase *NewValue);
	void InvokeLateCommand(INT32 GroupIndex, INT32 CommandIndex);
};

#endif		// if _DEBUG

#endif		// INC_DEBUGDLG

