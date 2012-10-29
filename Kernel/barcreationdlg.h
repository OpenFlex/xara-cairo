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


#ifndef INC_BARCREATIONDLG
#define INC_BARCREATIONDLG


#define OPTOKEN_BARCREATIONDLG _T("BarCreationDlg")
#define OPTOKEN_BARSTATESDLG _T("BarStatesDlg")
#define OPTOKEN_BARREDEFINESTATEDLG _T("BarRedefineStateDlg")



/********************************************************************************************

>	class BarCreationDlg : public DialogOp

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/8/99
	Purpose:	Dialog to make building button bar rollovers easier

********************************************************************************************/

class BarCreationDlg : public DialogOp
{
	CC_DECLARE_DYNCREATE(BarCreationDlg);

	//Constructors, destructors and initialiser
public:
	BarCreationDlg();
	~BarCreationDlg();

	static	BOOL Init();

	// Creating the dialog
public:
	void Do(OpDescriptor*);
	void DoWithParam(OpDescriptor* pOp, OpParam* pParam);

protected:
	BOOL Create();
	BOOL SetUpControls( BOOL DoScan = TRUE);
	BOOL SetUpDynamicControls();
	BOOL CreateBar();
	void ReadBarProperties();
	void WriteBarProperties();
	INT32 GetBarNumber();
	void EnableAllMyControls(BOOL enable);

	// Operations (functions that other objects call)
public:
	virtual	MsgResult Message(Msg* Message);
	static	OpState GetState(String_256*, OpDescriptor*);

	//Member variables
protected:
	static BarCreationDlg *TheDialog;	// Points to the only Web Address dialog object

	BOOL m_IsEditing;
	BOOL m_FirstIsEditing;
	String_256 m_BarName;
	String_256 m_FirstBarName;
	BOOL m_AlreadyInThisFunction;
	BOOL m_HasBackBar;
	BOOL m_ValidBar;
	
public:
	static const UINT32 IDD;
	static const CDlgMode Mode;

public:
	static BOOL ms_WantMouse;
	static BOOL ms_WantClicked;
	static BOOL ms_WantSelected;
	static BOOL ms_WantDefault;
	static BOOL ms_IsVertical;
	static BOOL ms_SuggestDesign;
	static INT32 ms_NoOfButtons;
	static INT32 ms_Mode;
	//static BOOL ms_SameSize;
	static INT32 ms_SizeJustification;
	static BOOL ms_Continuous;
	static INT32 ms_Spacing;
	static INT32 ms_Stretching;
	static BOOL ms_FromSelection;
	static INT32 ms_StateToCreate;
	static BOOL ms_GroupsStretch;
};



class OpParamBarCreationDlg : public OpParam
{
//CC_DECLARE_DYNAMIC(OpParamBarCreation)

public:
	OpParamBarCreationDlg()
			{	
				m_IsEditing = FALSE;
				m_BarName = "Bar1";
				m_ButtonsToEdit = 0;
			}

	OpParamBarCreationDlg(BOOL IsEditing, String_256 BarName = "Bar1", INT32 ButtonsToEdit = 0)
			{	
				m_IsEditing = IsEditing;
				m_BarName = BarName;
				m_ButtonsToEdit = ButtonsToEdit;
			}

	BOOL m_IsEditing;
	String_256 m_BarName;
	INT32 m_ButtonsToEdit;
};

/********************************************************************************************

>	class BarStatesDlg : public DialogOp

	Author:		Simon_Knight (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/5/00
	Purpose:	Dialog to make building button bar states

********************************************************************************************/

class BarStatesDlg : public DialogOp
{
	CC_DECLARE_DYNCREATE(BarStatesDlg);

	//Constructors, destructors and initialiser
public:
	BarStatesDlg();
	~BarStatesDlg();

	static	BOOL Init();

	// Creating the dialog
public:
	void Do(OpDescriptor*);
	void DoWithParam(OpDescriptor* pOp, OpParam* pParam);

protected:
	BOOL Create();
	void SetUpControls();
	BOOL ScanForBarDetails();
	BOOL CreateBarStates(BOOL ReCreate = FALSE);
	BOOL OnSelectionChanged();

	// Operations (functions that other objects call)
public:
	virtual	MsgResult Message(Msg* Message);
	static	OpState GetState(String_256*, OpDescriptor*);

	//Member variables
protected:
	static BarStatesDlg *TheDialog;	// Points to the only dialog object
	String_256 m_BarName;
	static INT32 m_State;
	static INT32 ms_SuggestDesign;
	BOOL m_StateExists[5];
	BOOL m_ValidBar;

public:
	static const UINT32 IDD;
	static const CDlgMode Mode;

};



class OpParamBarStatesDlg : public OpParam
{

public:
	OpParamBarStatesDlg()
			{	
				m_BarName = "Bar1";
			}

	OpParamBarStatesDlg(String_256 BarName)
			{	
				m_BarName = BarName;
			}

	String_256 m_BarName;
};






class BarRedefineStateDlg : public DialogOp
{
	CC_DECLARE_DYNCREATE(BarRedefineStateDlg);

	//Constructors, destructors and initialiser
public:
	BarRedefineStateDlg();
	~BarRedefineStateDlg();

	static	BOOL Init();

	// Creating the dialog
public:
	void Do(OpDescriptor*);
	void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	BOOL IsAttribInSelected(Node * pNode);

protected:
	BOOL Create();
	BOOL SetUpControls();
	BOOL RedefineState();

	// Operations (functions that other objects call)
public:
	virtual	MsgResult Message(Msg* Message);
	static	OpState GetState(String_256*, OpDescriptor*);

	//Member variables
protected:
	static BarRedefineStateDlg *TheDialog;	// Points to the only dialog object
	String_256 m_BarName;
	INT32 m_State;

public:
	static const UINT32 IDD;
	static const CDlgMode Mode;

};

class OpParamBarRedefineStateDlg : public OpParam
{

public:
	OpParamBarRedefineStateDlg()
			{	
				m_BarName = "Bar1";
				m_State	= 0;
			}

	OpParamBarRedefineStateDlg(String_256 BarName, INT32 State)
			{	
				m_BarName = BarName;
				m_State = State;
			}

	String_256 m_BarName;
	INT32 m_State;
};





#endif //INC_BARCREATIONDLG

