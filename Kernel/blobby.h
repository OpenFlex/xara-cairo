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

#ifndef INC_BLOBBY
#define INC_BLOBBY
    
//#include "undoop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "opdesc.h"    - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "doccolor.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ops.h"  	   	// Operation class   - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "dlgtypes.h"  	// The DialogOp types - in camtypes.h [AUTOMATICALLY REMOVED]
#include "dlgmgr.h"		// the dialogue box manager 
//#include "convert.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#define OPTOKEN_BLOBBY _T("Blobby")

class CCAPI BlobbyOp: public UndoableOperation
{                             
	CC_DECLARE_DYNCREATE( BlobbyOp )

public:
	BlobbyOp();								// Constructor

	static BOOL		Init();					// Register an OpDescriptor
	                                        // Read the state of an operation
	static OpState	GetState(String_256*, OpDescriptor*);		
    
	void			Do(OpDescriptor*);		// "Do" function
    

};
     
class RedoColAction;      
     
/********************************************************************************************

>	class UndoColAction : public Action

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/93
	Purpose:	Simple BlobbyOp action which restores the colour of a documents page to 
				the  colour it was prior to the operation being performed. 
	SeeAlso:	BlobbyOp

********************************************************************************************/

class CCAPI UndoColAction: public Action
{                                
	CC_DECLARE_DYNCREATE( UndoColAction )
    friend class RedoColAction;
    friend class BlobbyOp; 

public:
	UndoColAction(); 
	virtual ActionCode Execute();    
	static ActionCode Init(Operation* const pOp, 
						   ActionList* pActionList, 	
						   UINT32 ActionSize,    
						   Action** NewAction);   
private:
	DocColour Color;  
};
  

/********************************************************************************************

>	class RedoColAction : public Action

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/93
	Purpose:	Simple BlobbyOp action which restores the colour of a documents page to 
				the  colour it was prior to the operation being undone. 
	SeeAlso:	BlobbyOp

********************************************************************************************/

  
class CCAPI RedoColAction: public Action
{              
	CC_DECLARE_DYNCREATE( RedoColAction )  
	friend class UndoColAction; 

public:
	RedoColAction(); 
	virtual ActionCode Execute();    
	static ActionCode Init(Operation* const pOp, 
						   ActionList* pActionList, 
						   UINT32 ActionSize, 
						   Action** NewAction);
private:
	DocColour Color; 
};
       

/********************************************************************************************

>	class RedoAction2 : public Action

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/93
	Purpose:	Dummy BlobbyOp REDO action. Does nothing when it executes.
	SeeAlso:	BlobbyOp

********************************************************************************************/

class CCAPI RedoAction2: public Action
{              
	CC_DECLARE_DYNCREATE( RedoAction2 )  
	friend class UndoColAction; 

public:
	RedoAction2(); 
	virtual ActionCode Execute();    
	static ActionCode Init(Operation* const pOp, 
						   ActionList* pActionList, 
						   UINT32 ActionSize, 
						   Action** NewAction);
private:
	DocColour Color; 
};

 

/********************************************************************************************

>	class RedoAction3 : public Action

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/93
	Purpose:	Dummy BlobbyOp REDO action. Does nothing when it executes.
	SeeAlso:	BlobbyOp

********************************************************************************************/
 
  
class CCAPI RedoAction3: public Action
{              
	CC_DECLARE_DYNCREATE( RedoAction3 )  
	friend class UndoColAction; 

public:
	RedoAction3(); 
	virtual ActionCode Execute();    
	static ActionCode Init(Operation* const pOp, 
						   ActionList* pActionList, 
						   UINT32 ActionSize, 
						   Action** NewAction);
private:
	DocColour Color; 
};
               

/********************************************************************************************

>	class UndoAction2 : public Action

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/93
	Purpose:	Dummy BlobbyOp UNDO action. Does nothing when it executes.
	SeeAlso:	BlobbyOp

********************************************************************************************/
               
               
class CCAPI UndoAction2: public Action
{              
	CC_DECLARE_DYNCREATE( UndoAction2 )  
	friend class UndoColAction; 

public:
	UndoAction2(); 
	virtual ActionCode Execute();    
	static ActionCode Init(Operation* const pOp, 
						   ActionList* pActionList, 
						   UINT32 ActionSize, 
						   Action** NewAction);
private:
	DocColour Color;                           
	
};


/********************************************************************************************

>	class UndoAction3 : public Action

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/8/93
	Purpose:	Dummy BlobbyOp UNDO action. Does nothing when it executes.
	SeeAlso:	BlobbyOp

********************************************************************************************/

  
class CCAPI UndoAction3: public Action
{              
	CC_DECLARE_DYNCREATE( UndoAction3 )  
	friend class UndoColAction; 

public:
	UndoAction3(); 
	virtual ActionCode Execute();    
	static ActionCode Init(Operation* const pOp, 
						   ActionList* pActionList, 
						   UINT32 ActionSize, 
						   Action** NewAction);
private:
	DocColour Color; 
};       


// -----------------------------------------------------------------------------------------
// BlobbyDlg used to test the Dialog system

#define OPTOKEN_BLOBBYDLG _T("BlobbyDlg")    
   
class BlobbyDlg: public DialogOp
{         
	CC_DECLARE_DYNCREATE( BlobbyDlg )  
public:

	BlobbyDlg(); 
	MsgResult Message( Msg* Message );  
	void Do(OpDescriptor*);		// "Do" function        
	static BOOL Init();                        
	BOOL Create(); 
	static OpState GetState(String_256*, OpDescriptor*);	

	static const UINT32 IDD;
//	enum { IDD = _R(IDD_BLOBBYDLG) };     
	static const CDlgMode Mode;   
	
	String_256 UnitStrList[9];    
	UnitType UnitList[9];   
	UnitType DefaultUnit; 
	UnitType ConvUnit; 
}; 

// -----------------------------------------------------------------------------------------
// BlobbyBar used to test the Dialog system

#define OPTOKEN_BLOBBYBAR _T("BlobbyBar")    
   
class BlobbyBar: public DialogOp
{         
	CC_DECLARE_DYNCREATE( BlobbyBar )  
public:

	BlobbyBar(); 
	MsgResult Message( Msg* Message );  
	void Do(OpDescriptor*);		// "Do" function        
	static BOOL Init();
	BOOL Create(); 
	static OpState GetState(String_256*, OpDescriptor*);	

	static const UINT32 IDD;
	static const CDlgMode Mode;   

	BOOL IsABar() { return TRUE; }

}; 

// -----------------------------------------------------------------------------------------

// BlobbyTabDlg used to test the Dialog system

#define OPTOKEN_BLOBBYTABDLG _T("BlobbyTabDlg")    
   
class BlobbyTabDlg: public DialogTabOp
{         
	CC_DECLARE_DYNCREATE( BlobbyTabDlg )  
public:

	BlobbyTabDlg(); 
	MsgResult Message( Msg* Message ); 
	 
	void Do(OpDescriptor*);		// "Do" function        
	static BOOL Init();                        
	static OpState GetState(String_256*, OpDescriptor*);	
	virtual BOOL RegisterYourPagesInOrderPlease(); 
	static const CDlgMode Mode; 

	// We need to give our Tab dialog's a unique resource ID as this is used to 
	static const UINT32 IDD;
private:
	// Message handlers for each page in the tabbed dialog
	void HandleCoordsMsg(DialogMsg* Msg); 
	void HandleRadioDazeMsg(DialogMsg* Msg); 
	void HandleConvertMsg(DialogMsg* Msg);

  	// Used by Convert page	
	String_256 UnitStrList[9];    
	UnitType UnitList[9];   
	UnitType DefaultUnit; 
	UnitType ConvUnit; 

}; 
                   

       
#endif
                   
