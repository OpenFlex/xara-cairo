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

// A simple Dialog That does some Gavin Rendering into itself

#ifndef INC_RENDDLG
#define INC_RENDDLG


// Find out about the DialogOp Class

#define OPTOKEN_RENDERDEMODLG _T("RenderDemoDlg")

/********************************************************************************************

>	class RenderDemoDlg : public DialogOp

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/94
	Purpose:	A Sample dialog that renders stuff into itself using render regions

********************************************************************************************/

class RenderDemoDlg : public DialogOp
{
	// Give my name in memory dumps
	CC_DECLARE_DYNCREATE(RenderDemoDlg);

public:
	// Construction etc
	RenderDemoDlg();
	~RenderDemoDlg();
	static	BOOL Init();

	// Called when the dialog is to be displayed
	void	Do(OpDescriptor*);
	virtual	MsgResult Message(Msg* Message);

	// Find out about the state of the dlg
	static	OpState GetState(String_256*, OpDescriptor*);
	
protected:
	void RenderControl(ReDrawInfoType* ExtraInfo);

public:
	// Vars
	static const UINT32 IDD;
	static const CDlgMode Mode;

protected:
	// The colour swapping stuff
	DocColour	First;
	DocColour	Second;
	BOOL		ShowFirst;
};

#endif  // INC_RENDDLG


