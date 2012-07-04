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
//	URL dialog
// 

#ifndef INC_DaveDlg
#define INC_DaveDlg

//#include "dialogop.h"
//#include "selop.h"
#include "webaddr.h"

class CBeveler;

/********************************************************************************************

>	class DaveDlg : public DialogOp

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/3/97
	Purpose:	The "Import from URL..." dialog

********************************************************************************************/

#define OPTOKEN_DAVEDLG _T("DaveDlg")

class DaveDlg : public DialogOp
{
	CC_DECLARE_DYNCREATE(DaveDlg)

	//Constructors
public:
	DaveDlg();
	~DaveDlg();

	//Initialiser
public:
	static BOOL Init();

	//Function to start the dialog
public:
	BOOL DoCreate();

	void UpdateControls();
	
	//Message handling functions
protected:
	void OnCreate();
	void OnCommit();

	void OnURLChanged();
	
	//Overridden virtual functions
public:
	void DoWithParam(OpDescriptor*, OpParam* Param); 
	void Do(OpDescriptor*); 						
						  	
	static OpState GetState(String_256*, OpDescriptor*);
													
	virtual MsgResult Message(Msg* Message);		

	//Member variables
protected:
	static WebAddress ms_url;

	static BOOL DialogWasCancelled;
	static BOOL DontHandleNextMessage;
	
	// overrides for virtual functions

	void DoChangeInValue();
	
	BOOL DoBevel();
	BOOL RemoveBevel();
	
	//Compulsory static member variables
public:
	static CDlgResID IDD;		
	static const CDlgMode Mode;
private:
	INT32 m_Angle;
	INT32 m_Type;
	INT32 m_Indent;
	INT32 m_Contrast;
	BOOL m_bFirst;

};

#endif
