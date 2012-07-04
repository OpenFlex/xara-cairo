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


#ifndef INC_INFOBAR
#define INC_INFOBAR

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]


#define OPTOKEN_INFOBAR _T("InfoBar")       
class InfoBarOp: public DialogOp
{         
	CC_DECLARE_DYNCREATE(InfoBarOp)
public:
	InfoBarOp(CDlgResID DialogID = 0); 
		
	virtual MsgResult Message(Msg* Msg);
	void Do(OpDescriptor*);		// "Do" function        
	static BOOL Init();                        
	BOOL Create(); 
	BOOL Create(UINT32 DialogID);
	
	static OpState GetState(String_256*, OpDescriptor*);	

//	enum { IDD = _R(IDD_INFOBAR) };     
	static UINT32 IDD;
	static const CDlgMode Mode;   

	// Specific to this dialog...
	
	void OnSizeParent(WPARAM, LPARAM lParam);
	void Toggle();

	// The layer manager will call this function for the info bar when the current spread changes. 
	// The 	InfoBar needs to know that the current spread has changed so that the layer list control 
	// can be updated. 
	void NewCurrentSpread(); 

	void DisableLayerControl(); 
	void EnableLayerControl(); 

	// Preference variable - determines whether or not info bar is on or off.
	static BOOL Visible;
	
private:
	wxPoint				DragPos;
	BOOL				DraggingBar;

	void ChangeActiveLayer(WORD LayerIndex); // Called when a new active layer is selected 

}; 

#define OPTOKEN_VIEWINFOBAR _T("ViewInfoBar")    
   
class InfoBarViewOp: public Operation
{         
	CC_DECLARE_DYNCREATE( InfoBarViewOp )

public:
	InfoBarViewOp();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);	
}; 

#endif
