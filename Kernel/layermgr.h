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
*/ 

/* Declaration of the following classes
	LyrDetails
	LayerManager
	OpLayerChange
*/

#ifndef INC_LAYERMGR
#define INC_LAYERMGR

// Include files 
#include "layer.h"

#define OPTOKEN_LYRCHNG _T("LayerChange")	// Optoken for the layer change operation 
#define OPTOKEN_MOVE_SEL_TO_ACTIVE_LAYER _T("MoveSelToActiveLayer")

class String_256; 


/********************************************************************************************

>	class LyrDetails: public ListItem 

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/1/94
	Purpose:	LyrDetails objects are stored in a list within the LayerManager. 
				They record changes made to a layer. 

	SeeAlso:	LayerManager

********************************************************************************************/


class LyrDetails: public ListItem 
{
	CC_DECLARE_MEMDUMP(LyrDetails);

public:
	LyrDetails(); 		// Constructor 
	Layer *m_pLayer; 	// A pointer to the Layer that the LyrDetails record describes. 
						// NULL if the layer is New

	LayerStatus Status; // The LayerStatus structure contains all the layer details which the 
						// user can change 

	BOOL New; 	 	    // Flag indicating if the layer is new. i.e. it does not exist in the 
					    // Camelot tree. 

	BOOL Deleted; 	    // Flag indicating if the layer has been deleted 

};

/********************************************************************************************

>	class LayerManager: public CCObject

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/94
	Purpose:	The LayerManager is used to make changes to layers in the document tree. It 
				holds a pointer to a current spread, and a list of layer details for the 
				current spread (LyrDetLst). The layerDlg and InfoBar make changes to layers 
				in the current spread indirectly by changing the LyrDetList. Layer changes 
				are deferred until the CommitLayerChanges() method is called. Changes made 
				to the LyrDetList can also be cancelled by calling the CancelLayerChanges() 
				method.  

	SeeAlso:	LyrDetails
	SeeAlso:	LayerDlg
	SeeAlso:	OpLayerChange 

********************************************************************************************/

class LayerManager:public CCObject
{
public:

	LayerManager();			 // Constructor 
	~LayerManager();			 // Destructor 
	
	String_256 CreateUniqueLayerID(); 		 // Creates a layer name which is unique for 
											 // the current spread.  
											 	
   	BOOL CommitLayerChanges(); 				 // Performs a LayerChangeOp which modifies the 
   											 // layers in the Camelot tree based on changes 
   											 // made to the LyrDetList. 

	BOOL NewCurrentSpread(Spread* NewCurrentSpread); // NewCurrentSpread becomes the 
													 // new current spread 

	Spread* GetCurrentSpread(); 			 // Returns the current spread 

	BOOL CancelLayerChanges(); 				 // Causes the changes made to the LyrDetList 
											 // to be discarded and new values read. 

	BOOL RefreshLayerDetails(); 			 // Refreshes the layer details list 

	void UpdateInterface(); 				 // Called to update the interface 



	// The layer details list is a list of LyrDetails for the current spread.
	List LyrDetList; 

private:	
	Spread* CurrentSpread;			 // The current spread 

	void DeleteLayerDetList();  	 // Deletes the contents of the LyrDetList 
	BOOL ReadSpreadLayerDetails();   // Read the current spread's layer details into the 
									 // LyrDetList
	void BroadcastNewCurrentSpread();// Makes calls to other subsystems that need to know 
									 // that the current spread has changed. 
	BOOL LayerDetailsChanged(); 	 // Used to determine if the layer details have been 
									 // changed. We don't want to generate a LayerChangeOp
									 // if nothing has changed. 

};


   
/********************************************************************************************

>	class OpLayerChange: public UndoableOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the LayerChange operation which is created by the 
				LayerManager to make changes to the layers of the current spread. 
	SeeAlso:	LayerManager

********************************************************************************************/

class CCAPI OpLayerChange: public UndoableOperation
{         

	CC_DECLARE_DYNCREATE( OpLayerChange );

public:
	OpLayerChange();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);

	virtual BOOL Undo(); 
	virtual BOOL Redo(); 	
};  

/********************************************************************************************

>	class ChangeLyrAttribAction: public Action

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/1/94
	Purpose:	When executed the ChangeLyrAttribAction	changes a layer's Status
	SeeAlso:	-

********************************************************************************************/

class CCAPI ChangeLyrAttribAction: public Action
{                                
	CC_DECLARE_DYNCREATE( ChangeLyrAttribAction )

public:
	ChangeLyrAttribAction(); 
	~ChangeLyrAttribAction();
	virtual ActionCode Execute();    
	static ActionCode Init(Operation* const pOp, 
						   ActionList* pActionList, 	
						   UINT32 ActionSize,
						   LayerStatus& Status,  // The layer status which is restored 
						   					     // when we execute the action. 
						   Layer* Layer, 		 // The layer to change when we execute 
						   Action** NewAction); 

private:
	Layer* ChangeLayer; // The layer to change 
	LayerStatus Status; // the new attributes of the layer 
};   
       




/********************************************************************************************

>	class CCAPI OpMoveToLayer: public UndoableOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com> K
	Created:	3/5/00
	Purpose:	An op to move the selection from where-ever it is to the active layer.

********************************************************************************************/
class CCAPI OpMoveToLayer: public SelOperation
{         

	CC_DECLARE_DYNCREATE( OpMoveToLayer );

public:
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);
};  





#endif
					

