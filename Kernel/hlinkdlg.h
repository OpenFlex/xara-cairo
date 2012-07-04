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


//The Web Address dialog
#ifndef INC_WEBADDRESSDLG
#define INC_WEBADDRESSDLG

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "selop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "webattr.h"

#define OPTOKEN_WEBADDRESSDLG _T("WebAddressDlg")
#define OPTOKEN_HOTLINKOP _T("HotLinkOp")


/********************************************************************************************

>	typedef enum WebCommonAttributeResult

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/3/97
	Purpose:	This class shows what common WebAddressAttributes are applied
				to the selection, as follows:

  				WCA_NONE		Nothing is selected

				WCA_SINGLE		Identical attributes are applied to the entire selection

				WCA_MANY			Different attributes are applied to the selection

				WCA_DEFAULT		The default attribute is applied to the selection

				It's very similar to Range::CommonAttribResult, but with the extra
				"WCA_DEFAULT" member added in, because the Web Address dialog box
				treats the default attribute as a special case.
																				 
********************************************************************************************/

typedef enum 
{
	WCA_NOSELECTION,
	WCA_SINGLE,
	WCA_MANY,
	WCA_DEFAULT
} WebCommonAttributeResult;


/********************************************************************************************

>	class WebAddressDlg : public DialogOp

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/8/96 - rewritten by Graham 21/3/97
	Purpose:	The new Web Address dialog

				Note that the WebAddressDlg class does not use the WebAddress class
				in any way! (I did that to confuse you).

********************************************************************************************/

class WebAddressDlg : public DialogOp
{
	CC_DECLARE_DYNCREATE(WebAddressDlg);

	//Constructors, destructors and initialiser
public:
	WebAddressDlg();
	~WebAddressDlg();

	static	BOOL Init();

	// Creating the dialog
public:
	void Do(OpDescriptor*);
	void DoWithParam(OpDescriptor* pOp, OpParam* pParam);

protected:
	BOOL Create();

	// Operations (functions that other objects call)
public:
	virtual	MsgResult Message(Msg* Message);
	static	OpState GetState(String_256*, OpDescriptor*);

	//Message handling functions, called from ::Message
protected:
	void OnCreate();
	void OnAddButtonClicked();
	void OnRemoveButtonClicked();
	void OnAutoCorrectClicked();
	void OnDialogChange();
	void OnSelectionChange();

	//Actions (functions which do things to other objects)
protected:
	void SetDialogInitialState();
	void SetDialogChangedState();
	void SetDialogInitialControls();
	void ApplyWebAddress();
	void RemoveWebAddress();

	//Control functions (functions to display information in the dialog
	//box or to get information from the dialog box)
	void ShowURL(TCHAR* pcURL=NULL);
	void ShowURL(UINT32 uiURL);
	String_256 GetURL();

	void ShowCorrect(BOOL fValue=TRUE);
	BOOL GetCorrect();


	void ShowFrame(TCHAR* pcFrame=NULL);
	void ShowFrame(UINT32 uiFrame);
	String_256 GetFrame();

	void ShowClickableArea(UINT32 uiArea);
	UINT32 GetClickableArea();

	void EnableAdd(BOOL fValue=TRUE);
	void EnableRemove(BOOL fValue=TRUE);  

	void ShowWebAddressOnSelection(BOOL fValue=TRUE);

	//Toolkit functions (called by action functions)
protected:
	WebCommonAttributeResult FindCommonWebAttribute(WebAddressAttribute* pwaaReturn=NULL);

	BOOL SelectionConsistsOfText();


		
	//Member variables
protected:
	static WebAddressDlg   *TheDialog;	// Points to the only Web Address dialog object
	static BOOL				DontHandleNextTextMessage;
	BOOL fDialogIsInInitialState;
	
public:
	static const UINT32 IDD;
	static const CDlgMode Mode;

	//Variable used to store things in the registry
public:
	static BOOL ms_fCorrect;
		
};

#endif //INC_WEBADDRESSDLG

