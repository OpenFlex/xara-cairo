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

// Header for dlg that controls the XS EPS options

#ifndef INC_XSEPSOPS
#define INC_XSEPSOPS

#define OPTOKEN_XSEPSEXPORTOPTIONS _T("XSEPSExpOpts")

/********************************************************************************************

>	class XSEPSExportOptions : public CDialog

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/5/95
	Purpose:	This gets options relevant to the export of XS EPS
	SeeAlso:	

********************************************************************************************/

class XSEPSExportOptions: public DialogOp
{         
	CC_DECLARE_DYNCREATE( XSEPSExportOptions )  
public:

	XSEPSExportOptions(); 
	MsgResult Message( Msg* Message );  
	void Do(OpDescriptor*);		// "Do" function        
	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);	

	static BOOL Aborted;
	static const UINT32 IDD;
	static const CDlgMode Mode;   
}; 

#endif  // INC_XSEPSOPS
