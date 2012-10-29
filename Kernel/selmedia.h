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


// Declaration of the following classes
/*
	BlobbyOp         : Demonstration temporary operation which changes the colour of a 
					   documents paper. 
					   and it's actions

*/	



/*
 */        

#ifndef INC_SELMEDIA
#define INC_SELMEDIA
    
#include "dlgmgr.h"		// the dialogue box manager 

// -----------------------------------------------------------------------------------------
// SelMediaDlg used to test the Dialog system

#define OPTOKEN_SELMEDIADLG _T("SelMediaDlg")    


struct SelMediaDlgParam : public OpParam
{
CC_DECLARE_DYNAMIC(SelMediaDlgParam)

	typedef std::map<String_256, bool>	CMediaAppList;
	typedef CMediaAppList::iterator CMediaAppListIter;
	
	CMediaAppList*	m_pAppList;
	String_256		m_strSel;
	bool			m_fValid;

	SelMediaDlgParam() : m_pAppList( NULL ), m_fValid( false )
	{}
};

class SelMediaDlg: public DialogOp
{         
	CC_DECLARE_DYNCREATE( SelMediaDlg )  

protected:
	SelMediaDlgParam*	m_pOptions;

	void InitValues();

public:
	SelMediaDlg(); 
	MsgResult Message( Msg* Message );

	void Do(OpDescriptor*);		// "Do" function
	void DoWithParam(OpDescriptor*, OpParam* pParam);

	static BOOL Init();                        
	BOOL Create(); 
	static OpState GetState(String_256*, OpDescriptor*);	

	static const UINT32 IDD;    
	static const CDlgMode Mode;
};

#endif
                   
