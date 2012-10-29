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

/*
 * */ 
					  
#ifndef INC_LAYERDLG
#define INC_LAYERDLG

class LyrDetails; 

#define OPTOKEN_LAYERDLG _T("LayerDlg")    
   

/********************************************************************************************

>	class LayerDlg: public DialogOp

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/93
	Purpose:	The Layer dialog allows a user to 

				View all layers for a spread 
				Change the relative z-order of the layers 
				Create a new layer 
				Delete a layer 
				Set various layer attributes 
				
				
	SeeAlso:	LayerManager

********************************************************************************************/

class LayerDlg: public DialogOp
{         
	CC_DECLARE_DYNCREATE( LayerDlg )  
public:

	LayerDlg();  // Constructor 
	void Do(OpDescriptor*);		// "Do" function        
	static BOOL Init();                        
	BOOL Create(); 
	static OpState GetState(String_256*, OpDescriptor*);	

	static const INT32 IDD;
	static const CDlgMode Mode;
	
	virtual MsgResult Message(Msg* Message);

private:

	BOOL InitDialog(); 
	void ShowLayerDetails(); 
	void ChangeAttribute(CGadgetID Gadget); 
	void DeleteSelectedLayer();
	BOOL CreateNewLayer();  
	void UpdateLayerID(); 
	void SetSelectedLayer(WORD Index);
	void SetSelectedLayerActive(); 
	BOOL ValidValues(); 

	LyrDetails* SelectedLyr; // Pointer to the currently selected layer 
	WORD		SelectedLyrIndex; // Index of the selected layer
	WORD NumLayers; 			  // The number of layers on the spread (excludes deleted layers)

}; 
#endif
