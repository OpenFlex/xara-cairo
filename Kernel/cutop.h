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

// Clipboard operations

#ifndef INC_CUTOP
#define INC_CUTOP

//#include "selop.h"         - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "trans2d.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class DocCoord;

#define OPTOKEN_CUT _T("Cut")
#define OPTOKEN_COPY _T("Copy")
#define OPTOKEN_PASTE _T("Paste")
#define OPTOKEN_PASTEATSAMEPOS _T("PasteAtSamePos")
#define OPTOKEN_DELETE _T("Delete")
#define OPTOKEN_DUPLICATE _T("Duplicate")
#define OPTOKEN_CLONE _T("EditClone")
#define OPTOKEN_COPYANDTRANSFORM _T("CopyAndTransform")
#define OPTOKEN_PASTEATTRIBUTES _T("PasteAttributes")

   
/********************************************************************************************

>	class OpCut : public SelOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:    This class represents the Cut operation. When executed this operation hides
				all selected objects and places a copy of them on the Internal clipboard.

********************************************************************************************/

class CCAPI OpCut: public SelOperation
{         

	CC_DECLARE_DYNCREATE( OpCut )    

public:
	OpCut();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

};

/********************************************************************************************

>	class OpCopy : public SelOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the Copy operation. When executed this operation makes
				a copy of all selected objects and places them on the internal clipboard

********************************************************************************************/

class CCAPI OpCopy: public SelOperation
{         

	CC_DECLARE_DYNCREATE( OpCopy )    

public:
	OpCopy();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};  



/********************************************************************************************
>   class OpParamPasteAtPosition

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/10/96

	Purpose:	Holds information allowing the paste op to paste objects at a specific position

	SeeAlso:	Operation::OpParam

********************************************************************************************/

class OpParamPasteAtPosition : public OpParam
{
CC_DECLARE_DYNAMIC(OpParamPasteAtPosition)

public:
	OpParamPasteAtPosition()
			{ pSpread = NULL; Centre.x = Centre.y = 0; }

	OpParamPasteAtPosition(Spread* pTheSpread,DocCoord& TheCentre)
			{ pSpread = pTheSpread; Centre = TheCentre; }

	Spread*  GetSpread() { return pSpread; }
	DocCoord GetCentre() { return Centre; }

private:
	Spread* pSpread;
	DocCoord Centre;
};

/********************************************************************************************

>	class OpPaste : public SelOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the Paste operation. When executed this takes a copy
				of all objects on the internal clipboard and adds them to the visible spread.

********************************************************************************************/

class CCAPI OpPaste: public SelOperation
{         
	CC_DECLARE_DYNCREATE( OpPaste )    

public:
	OpPaste();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);
    void			DoWithParam(OpDescriptor*, OpParam* pOpParam);

	// Matt 22/01/2001 - Static function to remove names from pasted attribs if they would interfere with stretching info
	static BOOL RemoveNamesAlreadyUsedInStretching(Node * pAttrib, UndoableOperation* pOp);

protected:
	void DoPaste(OpDescriptor*,Spread* pSpread, DocCoord* pCentre);

	BOOL FindCentreInsertionPosition(Spread** Spread, DocCoord* Position);
	BOOL DoPasteStandard(BOOL PasteAtSamePos, BOOL ExternalData, Spread* pSpread = NULL, DocCoord* pCentre = NULL);
};

/********************************************************************************************

>	class OpPasteAttributes : public SelOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/08/95
	Purpose:	This class represents the PasteAttributes operation. The operation applies
				all attributes common to the objects on the clipboard. This operation is
				not in itself undoable. It invokes another UndoableOperation to actually
				apply the attributes.

				Phil 16/02/2005
				That is no longer true - the op is now derived from SelOperation and calls
				"Do" functions to add their actions to this operation.

********************************************************************************************/

class CCAPI OpPasteAttributes: public SelOperation 
{         
	CC_DECLARE_DYNCREATE( OpPasteAttributes )    

public:
	OpPasteAttributes();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);
};  
  
  
/********************************************************************************************

>	class OpDelete : public SelOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the Delete operation.	When executed this operation hides
				all selected objects.

********************************************************************************************/

class CCAPI OpDelete: public SelOperation
{         

	CC_DECLARE_DYNCREATE( OpDelete )    

public:
	OpDelete();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

private:
	// deletes fill ramp blobs
	// returns TRUE if any are deleted
	BOOL DeleteFillRampBlobs();

};


/********************************************************************************************

>	class CarbonCopyOp : public SelOperation

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/94
	Purpose:	This class allows OpClone and OpDuplicate to share common code.  Both are
				derived from it.
	SeeAlso:	OpDuplicate, OpClone

********************************************************************************************/
class CCAPI CarbonCopyOp: public SelOperation
{         
	CC_DECLARE_DYNCREATE( CarbonCopyOp )    

public:
	CarbonCopyOp();								
	static	OpState	GetState(String_256*, OpDescriptor*);		
	BOOL	DoProcessing(Trans2DMatrix Transformer, BOOL SelectCopy);
};    
 

/*********************************************************************************************

	Preference:	DuplicatePlacementX
	Section:	Attributes
	Range:		0..Maximum DocCoord
	Purpose:	Specifies where a duplicate copy of an object will be placed relative to the
				original object (X offset)

	SeeAlso:	DuplicatePlacementY

**********************************************************************************************/ 

/*********************************************************************************************

	Preference:	DuplicatePlacementY
	Section:	Attributes
	Range:		0..Maximum DocCoord
	Purpose:	Specifies where a duplicate copy of an object will be placed relative to the
				original object (Y offset)

	SeeAlso:	DuplicatePlacementX

**********************************************************************************************/ 


/********************************************************************************************

>	class OpDuplicate : public CarbonCopyOp

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the Duplicate operation. When executed this operation
				makes a copy of all selected objects, positioning the new objects a user
				prefered distance from the original.

********************************************************************************************/

#ifndef WEBSTER
// Set to (-.5cm,-.5cm)
#define DEFAULT_DUPLICATE_PLACEMENT_X (PX_MP_VAL*20)
#define DEFAULT_DUPLICATE_PLACEMENT_Y -(PX_MP_VAL*20)
#else
// WEBSTER - markn 6/12/96
// Changed default dup to be a round number of pixels
#define DEFAULT_DUPLICATE_PLACEMENT_X 15000
#define DEFAULT_DUPLICATE_PLACEMENT_Y -15000
#endif // WEBSTER

class CCAPI OpDuplicate: public CarbonCopyOp
{         
	CC_DECLARE_DYNCREATE( OpDuplicate )    

public:
	OpDuplicate();								
	static BOOL	Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	virtual	void	Do(OpDescriptor*);	

public:
	// Preference vars which specify the offset of the duplicate copy from the original
	// BODGE USING INT32 FOR NOW

	// Graham 5/6/97: Made these public, so that other features
	//can use the duplicate offset preference
	static INT32 DuplicatePlacementX;
	static INT32 DuplicatePlacementY;
};    
 

/********************************************************************************************

>	class OpClone : public CarbonCopyOp

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/94
	Purpose:	This class represents the Clone operation. When executed this operation
				makes a copy of all selected objects, leaving the new objects on top of the
				existing objects.

********************************************************************************************/

class CCAPI OpClone: public CarbonCopyOp
{         
	CC_DECLARE_DYNCREATE( OpClone )    

public:
	OpClone();								
	static BOOL	Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	virtual	void	Do(OpDescriptor*);	
};    


/********************************************************************************************

>	class OpCopyAndTransform : public CarbonCopyOp

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>, copying Peter's code heavily!
	Created:	25/6/96
	Purpose:	This operation creates a transformed copy of the selected objects.

********************************************************************************************/

class CCAPI OpCopyAndTransform: public CarbonCopyOp
{         
	CC_DECLARE_DYNCREATE( OpCopyAndTransform )    

public:
	OpCopyAndTransform();
	OpCopyAndTransform(Trans2DMatrix Transform, BOOL PassSelectCopy=FALSE);
	static BOOL	Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	virtual	void	Do(OpDescriptor*);	

protected:
	Trans2DMatrix CopyTransform;
	BOOL SelectCopy;
};    
#endif	// INC_CUTOP
