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


#ifndef INC_TIPSDLG
#define INC_TIPSDLG

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "tipsres.h"
//#include "fixst256.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "txtattr.h"		// for Justification


#define OPTOKEN_TIPSDLG _T("TipsDlg")
   
class OpDescriptor;
class Msg;
class DialogMsg;
class StringBase;
class CCStatic;

typedef UINT32	HelpID;

/********************************************************************************************

>	class TipsDlg: public DialogOp

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/08/96
	Purpose:	Provides a Tip of the Day dialog showing useful and inspirational tips
				for users young and old.

********************************************************************************************/

class TipsDlg: public DialogOp
{         
	CC_DECLARE_DYNCREATE( TipsDlg )  
public:
	// Metaclass members
	static BOOL		Init();
	static OpState	GetState(String_256*, OpDescriptor*);
	static BOOL		ShowAtStartUp();

public:
	TipsDlg();  // Constructor

	virtual ~TipsDlg();

	virtual void Do(OpDescriptor*);
	 
	static CDlgResID IDD() {return _R(IDD_TIP);}

	static const CDlgMode Mode;   

protected:
	static UINT32	g_uNextID;
	static BOOL	g_bStartUp;

	BOOL		m_bTipOK;
	String_256	m_strTip;
	INT32			m_iHashPosition;

	BOOL			m_bSentInvalid;

	DialogMsg*		m_pCurrentMsg;
	RenderRegion*	m_pRenderer;

	CCStatic*		m_pTipTextGadget;

protected:
	typedef UINT32	ResourceID;

	virtual BOOL Create();
	virtual BOOL OnInitDialog();
	// The message handler
	virtual MsgResult Message(Msg* pMessage);

	// Message Processing functions

	void OnNextTip();
	void OnCommit();
	void OnRedraw(ReDrawInfoType* pRedrawInfo);
	void OnMoreHelp();

	// Support functions
	BOOL	CreateTipGadget();

	void	GetNextTipString();
	void	GetTipString(ResourceID StringID);
	HelpID	GetTipHelpID();

	void	DrawTipString();
	BOOL	DrawBitmap(ResourceID BitmapID, DocRect& RedrawRect);


//	void	DrawText(StringBase* pString, DocRect& RedrawRect, Justification justification);
}; 

#endif
