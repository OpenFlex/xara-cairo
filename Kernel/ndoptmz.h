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
// Declaration of classes required for attribute optimisation

#ifndef INC_NDOPTMZ
#define INC_NDOPTMZ											  

//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************************************

>	class RequiredAttributeItem: public ListItem


	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/2/94
	Purpose:	This ListItem holds an attribute's runtime class, plus a flag indicating 
				if we have found the attribute. It is used by NodeRenderable::MakeAttributeComplete
				 
	SeeAlso:	NodeRenderableInk::MakeAttributeComplete

********************************************************************************************/


class RequiredAttributeItem: public ListItem
{
	public:
	CCRuntimeClass* AttributeClass;  // The class of the attribute we need to find
	BOOL Found; 					 // A flag which indicates that we have found the 
									 // attribute. 
};

/********************************************************************************************

>	class NodeAttributePtrItem: public ListItem


	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/2/94
	Purpose:	This ListItem holds a ptr to an attribute 
				 
	SeeAlso:	NodeRenderable::MakeAttributeCompleteInk

********************************************************************************************/


class NodeAttributePtrItem: public ListItem
{
	public:
	NodeAttribute* NodeAttribPtr; 

}; 


/********************************************************************************************

>	class FactorOutCommonChildAttrAct: public Action

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/9/93
	Purpose:	When executed this action will factor out all attributes which are common 
				to all children of the compound object. All common attributes become first 
				children of the compound object.
				
				A LocaliseCommonAttrAct action twin is generated to redo
 

	SeeAlso:	UndoableOperation::DoLocaliseCommonAttributes

********************************************************************************************/


class CCAPI FactorOutCommonChildAttrAct: public Action
{                                
	CC_DECLARE_DYNCREATE( FactorOutCommonChildAttrAct )

public:
	FactorOutCommonChildAttrAct(); 

	virtual ActionCode Execute();  
	static ActionCode Init(Operation* const pOp, 
						   ActionList* pActionList, 
						   NodeRenderableInk* CompoundObject,
						   BOOL Global, 
						   AttrTypeSet* pAffectedAttrTypes, 
						   Action** NewAction);
						   
	virtual void Slaughter(); // Destroys the pSetOfAffectedAttrTypes 

private:
		
	NodeRenderableInk* CompoundObj; 
	AttrTypeSet* pSetOfAffectedAttrTypes;
	BOOL Global; 

};   
	
/********************************************************************************************

>	class LocaliseCommonAttrAct: public Action

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/9/93
	Purpose:	This action copies all attributes common to the group to each child object 
				within the group which requires each attribute. The groups common attributes 
				are deleted.

				A FactorOutCommonChildAttrAct action twin is generated to redo

	SeeAlso:	UndoableOperation::DoFactorOutCommonChildAttributes

********************************************************************************************/


class CCAPI LocaliseCommonAttrAct: public Action
{                                
	CC_DECLARE_DYNCREATE( LocaliseCommonAttrAct )

public:
	LocaliseCommonAttrAct(); 

	virtual ActionCode Execute();  
	static ActionCode Init(Operation* const pOp, 
						   ActionList* pActionList, 
						   NodeRenderableInk* CompoundObject,
						   BOOL global, 
						   AttrTypeSet* pAffectedAttrTypes,  
						   Action** NewAction); 

	virtual void Slaughter(); // Destroys the pSetOfAffectedAttrTypes 

private:
		
	NodeRenderableInk* CompoundObj;
	AttrTypeSet* pSetOfAffectedAttrTypes; 
	BOOL Global;
};   

#endif
