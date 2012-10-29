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
   
#ifndef INC_GROUPOPS
#define INC_GROUPOPS 

        
class NodeGroup;
class NodeGroupTransparency;

#define OPTOKEN_GROUP			_T("Group")
#define OPTOKEN_UNGROUP			_T("Ungroup")
#define OPTOKEN_UNGROUPSPECIAL	_T("UngroupSpecial")
#define OPTOKEN_GROUPTRANSP		_T("GroupTransparency")
#define OPTOKEN_UNGROUPTRANSP	_T("UnGroupTransparency")

/********************************************************************************************

>	class OpGroup : public SelOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the Group operation.
	SeeAlso:	OpUnGroup
	Documentation:  specs\grpzord.doc


********************************************************************************************/

class CCAPI OpGroup: public SelOperation
{
	friend class OpUngroup;

	CC_DECLARE_DYNCREATE( OpGroup )    

public:
	OpGroup();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }

private:
	BOOL NeedToInvalidateGroup();

// Preferences
	static BOOL bAskBeforeFactoringEffects;
	static BOOL bLocaliseEffects;
};  
 
/********************************************************************************************

>	class OpUngroup : public SelOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the UnGroup operation.
	SeeAlso:	OpGroup
	Documentation:  specs\grpzord.doc

********************************************************************************************/

class CCAPI OpUngroup: public SelOperation
{         
	CC_DECLARE_DYNCREATE( OpUngroup )    

public:
	OpUngroup();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	
protected:
	BOOL UngroupSelectedGroups(); 
	BOOL ParentAllowsUngroup(NodeGroup* pChild);
	BOOL FindSelectedEffectAttrs() const;
};        

/********************************************************************************************

>	class OpUngroupSpecial : public OpUngroup

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the UnGroup Special operation.
	SeeAlso:	OpGroup
	Documentation:  specs\grpzord.doc

********************************************************************************************/

class CCAPI OpUngroupSpecial: public OpUngroup
{         
	CC_DECLARE_DYNCREATE( OpUngroupSpecial)

public:
	OpUngroupSpecial();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);		   
}; 


#endif
