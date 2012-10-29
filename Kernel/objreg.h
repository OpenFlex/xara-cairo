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

#ifndef INC_OBJREG
#define INC_OBJREG



/********************************************************************************************

>	Class NodeAttributeClassItem: public ListItem

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/2/94
	Purpose:	This ListItem holds an attribute's runtime class 
	SeeAlso:	ObjectRegistry

********************************************************************************************/


class NodeAttributeClassItem: public ListItem
{
	CC_DECLARE_MEMDUMP(NodeAttributeClassItem);

	public:
	CCRuntimeClass* AttributeClass; 
};

/********************************************************************************************

>	class NodeRenderableInkDetailsItem: public ListItem

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/2/94
	Purpose:	This ListItem is used by the Object Registry. It has the RuntimeClass of 
				a NodeRenderableInk node, along with the following information which is
				likely to grow. 
				
				A list of the runtime classes of attributes that the NodeRenderableInk 
				class requires.  
				A Flag which indicates if the node can have NodeRenderableInk children
	SeeAlso:	-

********************************************************************************************/

class NodeRenderableInkDetailsItem: public ListItem
{
	CC_DECLARE_MEMDUMP(NodeRenderableInkDetailsItem);

	public:
		NodeRenderableInkDetailsItem() { IsABaseClass = FALSE; }
		BOOL AddAttribClass(CCRuntimeClass* pAttribClass);
		void RemoveAttribClass(CCRuntimeClass* pAttribClass);

	public:
		BOOL IsABaseClass; // When set to TRUE IsKindOf(NodeRenderableInkClass) will be called
						   // on the object's runtime class, if set to FALSE 
						   // IS_A will be called.  

		CCRuntimeClass* NodeRenderableInkClass;
		List NodeAttributeClassList; 			// A list of attribute classes that the 
												// node requires
};


/********************************************************************************************

>	class ObjectRegistry: public CCObject

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/2/94

	Purpose:	The object registry currently records the attributes which are required by
				each NodeRenderableInk node in Camelot. Such a list is required during
				attribute optimisation, to determine the attributes to collect to make a
				subtree attribute complete. 

				In future the object registry may contain other information we need to 
				record, such as the number of attributes defined (lots of silly DLL stuff).  

				There should never be an instance of the ObjectRegistry it is a static object

	SeeAlso:	-

********************************************************************************************/

class ObjectRegistry: public CCObject
{
	public:


		// Init Sets up the RequiredAttribList for all NodeRenderableInkNodes defined
		// in Camelot. 
		static BOOL Init(); 

		// RegisterReqdAttribs can be called to register extra NodeRenderableInkNodes 
		// if they get added in new tools.  
		static void RegisterNodeRenderableInkDetails(NodeRenderableInkDetailsItem* ReqdAttribItem);  
		
		// GetRequiredAttribs returns a list of attribute classes which are required by 
		// the NodeRenderableInk class.  
		static List* GetRequiredAttribs(CCRuntimeClass* NodeRenderableInkClass); 

		static NodeRenderableInkDetailsItem* GetAttribDetails(CCRuntimeClass* pInkClass);

		static void Delete(); // Deletes the registry 

		static BOOL RegisterShadowDetails();
		

	private:
		static List NodeRenderableInkDetailsList; // A list of NodeRenderableInkDetailsItems.  
}; 				
#endif
