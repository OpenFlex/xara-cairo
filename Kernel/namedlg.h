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

#ifndef INC_NAMEDLG
#define INC_NAMEDLG

#define OPTOKEN_NAMEDLG _T("NameDlg")


extern const String_8 NullString;

/********************************************************************************************

>	class NameDialogParam : public OpParam

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com> (from MarkN)
	Created:	20/07/97

	Purpose:	Allows a string (the Name) to enter and emerge from a NameDialog, and tells
				us if the dialog was cancelled.

	See Also:	NameDialog::Invoke()

********************************************************************************************/
class NameDialogParam : public OpParam
{
	CC_DECLARE_MEMDUMP(NameDialogParam);

public:
	NameDialogParam() : m_Cancelled(FALSE)	{}

	BOOL DialogCancelled()									{	return m_Cancelled;	}
	void SetDialogCancelled()								{	m_Cancelled = TRUE;	}

	BOOL SetNameGiven(const StringBase& StringEntered);
	const StringBase& GetNameEntered() const				{	return m_StringEntered;	}
	StringBase& GetNameEntered()							{	return m_StringEntered;	}

private:
	String_256	m_StringEntered;	// the string entered into the dialog (unless cancelled)
	BOOL		m_Cancelled;		// the dialog this was passed to was cancelled
};


/********************************************************************************************

>	class NameDialog : public DialogOp

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com> (from MarkN)
	Created:	20/07/97

	Purpose:	Allows the user to edit the parts of a layer.

********************************************************************************************/
class NameDialog : public DialogOp
{         
	CC_DECLARE_DYNCREATE( NameDialog )  

public:
	static BOOL Init();
	static BOOL Invoke(NameDialogParam& NameParam);
	static OpState GetState(String_256*, OpDescriptor*);	

	NameDialog();

	virtual void DoWithParam(OpDescriptor*,OpParam*);		// "DoWithParam" function        

	virtual MsgResult Message(Msg* Message);

	void ShowLayerDetails();
	void CommitDialogValues();

	static const INT32 IDD;
	static const CDlgMode Mode;

protected:
	virtual void OnCreate();
	virtual void OnCommit();
	virtual void OnCancel();

	const StringBase& GetName() const;
	BOOL SetName(const StringBase& StringEntered);
	BOOL SetCancelled();

	void SetNameParam(NameDialogParam& NameParam);

private:
	NameDialogParam*  	m_pNameParam;
}; 


#endif	//	OPTOKEN_NAMEDLG
