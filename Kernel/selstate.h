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


// Declaration of the following classes:
/*
 	
		SelectionState 
		SelNdRng
		SelNd
*/ 

// Check in comments
/*
*/         
      
#ifndef INC_SELSTATE
#define INC_SELSTATE

class Node;

/********************************************************************************************

>	class SelNdRng

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/93
	Purpose:	SelNdRng objects are stored in an array within SelectionState objects, they 
				record a range of upto 255 contiguous nodes as being selected.  
	SeeAlso:	SelectionState      

********************************************************************************************/

class SelNdRng : public CC_CLASS_MEMDUMP
{
CC_DECLARE_MEMDUMP(SelNdRng);

public:
	Node* FirstNode;        // First selected node in a contiguous range of selected nodes
	BYTE NumSelected;        // Number of selected nodes including first (Max 255) 
							 // Stored as a byte to minimise space. If there are >  
							 // 255 selected nodes then > 1 SelNdRng should be created. 	
};        

/********************************************************************************************

>	class SelectionState

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/93
	Purpose:	Used to record and restore all selections in the Camelot tree. 
				 
	SeeAlso:	-

********************************************************************************************/

class SelectionState : public CC_CLASS_MEMDUMP
{
CC_DECLARE_MEMDUMP(SelectionState);

public:  
	SelectionState(); 
	BOOL Record(); 	     						 // Records the current selected state
	void Restore(BOOL RestoreSelBlobs = FALSE, BOOL RemoveBlobs = TRUE); // Restores the recorded selected state   
    ~SelectionState(); 	 						 // Deletes lists 
	UINT32 GetSize(); 							 // For finding the size of the Selection
												 // state in bytes
	BOOL operator==(SelectionState& SelState); 	 // Compares this SelectionState with another to determine
												 // if they are the same. 

	SelNdRng* GetSelectionList();              // Diccon 9/99 access functions
	UINT32 GetNumRanges();
	Node** GetNodeList();                       
	UINT32 GetNumNodes();                         
private:	
	// Funcs called from Restore() to ensure every single node in the selected spread is deselected.
	void DeselectAll(BOOL RemoveBlobs = TRUE);
	void DeselectAll(Node* pNode);

	// When Record() is invoked all selected nodes will be recorded on either the SelNdRng 
	// list, or the SelNdLst. If a node is contiguous with other selected nodes then it 
	// will be stored on the SelNdRngList (Therby reducing the amount of storage required for 
	// recording selected nodes). Otherwise the node is stored on the SelNdLst. 
	
	UINT32 NumNdRng; 		  // The number of SelNdRng items in the SelNdRngList
	UINT32 NumNd; 			  // The number of Node* items in the SelNdList
	SelNdRng* SelNdRngList;   // An array of node ranges 
	Node** SelNdList; 		  // An array of pointers to nodes in the selection 
}; 


#endif
