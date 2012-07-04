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


#ifndef INC_ABOUTDLG
#define INC_ABOUTDLG

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]


#define OPTOKEN_ABOUTDLG _T("AboutDlg")    
   
/********************************************************************************************

>	class AboutDlg: public DialogOp

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/02/94
	Purpose:	The about dialogue shows information on the Camelot program version number
				and details on the environment in which Camelot is executing
	SeeAlso:	-

********************************************************************************************/

#if defined(DIALOGOP_ABOUT_BOX)
class AboutDlg: public DialogOp
{         
	CC_DECLARE_DYNCREATE( AboutDlg )  

public:
	AboutDlg();		// The constructor
	~AboutDlg();	// and it's friend

	void Do(OpDescriptor*);		// "Do" function        
	static BOOL Init();                        

	BOOL Create(); 
	static OpState GetState(String_256*, OpDescriptor*);	
	// The message handler
	virtual MsgResult Message(Msg* Message);

	virtual BOOL OnIdleEvent();

	static const INT32 IDD;
	static const CDlgMode Mode;   

private:
	BOOL InitDialog(); 

private:
	static AboutDlg *TheDlg;
	static double CurrentAngle;
};
#else
class AboutDlg: public Operation
{         
	CC_DECLARE_DYNCREATE( AboutDlg )  

public:
	AboutDlg();		// The constructor
	~AboutDlg();	// and it's friend

	void Do(OpDescriptor*);		// "Do" function        
	static BOOL Init();                        

	static OpState GetState(String_256*, OpDescriptor*);	
};
#endif//

#endif
