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

/*$Log*/

#ifndef INC_ZORDOPS
#define INC_ZORDOPS


//#include "selop.h"         - in camtypes.h [AUTOMATICALLY REMOVED]

#define OPTOKEN_BRINGTOFRONT _T("BringToFront")
#define OPTOKEN_PUTTOBACK _T("PutToBack")  
#define OPTOKEN_MOVEFORWARDS _T("MoveForwards")
#define OPTOKEN_MOVEBACKWARDS _T("MoveBackwards")
#define OPTOKEN_MOVELAYERBEHIND _T("MoveBackwardsALayer")
#define OPTOKEN_MOVELAYERINFRONT _T("MoveForwardsALayer") 


enum MODE { LAYER, FRAME };

   
/********************************************************************************************

>	class OpBringToFront : public SelOperation

	Author:			Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:		9/7/93
	Purpose:		This class represents the BringToFront operation.
	SeeAlso:		OpPutToBack
	SeeAlso:    	OpMoveForwards
	SeeAlso: 		OpMoveBackwards
	Documentation:  specs\grpzord.doc

********************************************************************************************/

class CCAPI OpBringToFront: public SelOperation
{         

	CC_DECLARE_DYNCREATE( OpBringToFront )    

public:
	OpBringToFront();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

};


/********************************************************************************************

>	class OpPutToBack : public SelOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the PutToBack operation.
	SeeAlso:	OpBringToFront
	SeeAlso:    OpMoveForwards
	SeeAlso: 	OpMoveBackwards
	Documentation:  specs\grpzord.doc


********************************************************************************************/

class CCAPI OpPutToBack: public SelOperation
{         

	CC_DECLARE_DYNCREATE( OpPutToBack )    

public:
	OpPutToBack();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};  
 
/********************************************************************************************

>	class OpMoveForwards : public UndoableOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the OpMoveForwards operation.
	SeeAlso:	OpBringToFront
	SeeAlso:	OpPutToBack
	SeeAlso: 	OpMoveBackwards
	Documentation:  specs\grpzord.doc


********************************************************************************************/

class CCAPI OpMoveForwards: public SelOperation
{         

	CC_DECLARE_DYNCREATE( OpMoveForwards )    

public:
	OpMoveForwards();								
	static BOOL		Init();				
//	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
}; 

/********************************************************************************************

>	class OpMoveBackwards : public SelOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the MoveBackwards operation.
	SeeAlso:	OpBringToFront
	SeeAlso:	OpPutToBack
	SeeAlso:    OpMoveForwards
	Documentation:  specs\grpzord.doc


********************************************************************************************/

class CCAPI OpMoveBackwards: public SelOperation
{         
	CC_DECLARE_DYNCREATE( OpMoveBackwards )    

public:
	OpMoveBackwards();								
	static BOOL		Init();				
//	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};   


/********************************************************************************************

>	class OpMoveToLyrInFront : public SelOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/05/94
	Purpose:	This class represents the move to layer in front operation.
	SeeAlso:	OpBringToFront
	SeeAlso:	OpPutToBack
	SeeAlso:    OpMoveForwards
	SeeAlso:	OpMoveBackwards
	SeeAlso:	OpMoveToLyrBehind
	Documentation:  specs\grpzord.doc


********************************************************************************************/

class CCAPI OpMoveToLyrInFront: public SelOperation
{         
	CC_DECLARE_DYNCREATE( OpMoveToLyrInFront )    

public:
	OpMoveToLyrInFront();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};   


/********************************************************************************************

>	class OpMoveToLyrBehind : public SelOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the move to layer behind operation.
	SeeAlso:	OpBringToFront
	SeeAlso:	OpPutToBack
	SeeAlso:    OpMoveForwards
	SeeAlso:	OpMoveBackwards
	SeeAlso:	OpMoveToLyrInFront
	Documentation:  specs\grpzord.doc


********************************************************************************************/

class CCAPI OpMoveToLyrBehind: public SelOperation
{         
	CC_DECLARE_DYNCREATE( OpMoveToLyrBehind )    

public:
	OpMoveToLyrBehind();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};   

/********************************************************************************************

>	class OpCombineLayersToFrameLayer : public SelOperation

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/6/97
	Purpose:	This class represents the OpCombineLayersToFrameLayer operation.

********************************************************************************************/

#define OPTOKEN_COMBINELAYERSTOFRAMELAYER _T("CombineLayersToFrameLayer")

class CCAPI OpCombineLayersToFrameLayer: public SelOperation
{         
	CC_DECLARE_DYNCREATE( OpCombineLayersToFrameLayer )    

public:
	OpCombineLayersToFrameLayer();
	
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		

	virtual void Do( OpDescriptor * pOpDesc );
	virtual void DoWithParam(OpDescriptor* pOpDesc, OpParam* pParam);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};   

/********************************************************************************************

>	class FrameInFrontOpDescriptor : public OpDescriptor

	Author:		Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/10/97
	Purpose:	New FrameInFrontOpDescriptor class whose purpose is to allow an OpDescriptor
				to be created which allows us to over-ride the virtual function GetText.

********************************************************************************************/

class FrameInFrontOpDescriptor : public OpDescriptor
{
	CC_DECLARE_DYNAMIC( FrameInFrontOpDescriptor );

public:
	FrameInFrontOpDescriptor(	const TCHAR* pcszToken,
								CCRuntimeClass* pClass = CC_RUNTIME_CLASS(FrameInFrontOpDescriptor),
								pfnGetState gs = FrameInFrontOpDescriptor::GetState
							);

	// This will use the TextID to obtain a string resource text description of the operation. 
	virtual BOOL GetText(String_256* Description, OpTextFlags WhichText);

	static OpState GetState(String_256* psName, OpDescriptor* pOpDesc);
};


/********************************************************************************************

>	class FrameBehindOpDescriptor : public OpDescriptor

	Author:		Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/10/97
	Purpose:	New FrameBehindOpDescriptor class whose purpose is to allow an OpDescriptor
				to be created which allows us to over-ride the virtual function GetText.

********************************************************************************************/

class FrameBehindOpDescriptor : public OpDescriptor
{
	CC_DECLARE_DYNAMIC( FrameBehindOpDescriptor );

public:
	FrameBehindOpDescriptor(	const TCHAR* pcszToken,
								CCRuntimeClass* pClass = CC_RUNTIME_CLASS(FrameBehindOpDescriptor),
								pfnGetState gs = FrameBehindOpDescriptor::GetState
							);

	// This will use the TextID to obtain a string resource text description of the operation. 
	virtual BOOL GetText(String_256* Description, OpTextFlags WhichText);

	static OpState GetState(String_256* psName, OpDescriptor* pOpDesc);
};

#endif
 

 
