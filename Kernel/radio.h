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

//

#ifndef INC_RADIO
#define INC_RADIO


/********************************************************************************************

>	typedef struct tagAssociations ... CGadgetAssociation

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/05/96
	Purpose:	A structure for use by the RadioGroup class
	Scope:		public
	SeeAlso:	class RadioGroup

********************************************************************************************/

typedef struct tagAssociations
{
	CGadgetID	m_GadgetID;
	CCObject*	m_pObject;
} CGadgetAssociation;



/********************************************************************************************

>	class RadioGroup : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/05/96
	Purpose:	Allows user interface gadgets (GadgetID) to be associated with objects 
				(CCObject), which can then respond to messages sent to the gadgets.

	Notes:		Subsequent to construction, but prior to any other member invocations,
				SetAssociations() must be called. The AssocArray argument should be declared
				something like:
				MonoOn:
					static const UINT32 NUM_GADGETS = 2;

					static CGadgetAssociation	ColourUnitAssociations[NUM_GADGETS] =
					{
						{_R(IDC_GADGET1),	PointerToObject1},
						{_R(IDC_GADGET2),	PointerToObject2}
					};
				MonoOff:

				This class is under construction and will probably change.

	Scope:		public
	SeeAlso:	CGadgetAssociation

********************************************************************************************/

class RadioGroup : public CC_CLASS_MEMDUMP
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(RadioGroup);
public:
	RadioGroup(DialogOp* pDialog = NULL, CGadgetAssociation* AssocArray = NULL, UINT32 NumGadgets = 0) : 
		m_pDialog(pDialog), m_Associations(AssocArray), m_nNumAssociations(NumGadgets) {}

	BOOL		SetAssociations(DialogOp* pDialog, CGadgetAssociation* AssocArray, UINT32 NumGadgets);
	CCObject*	GetDefault();
	BOOL		SetDefault(CCObject* pDefaultObject);
	UINT32		GetRadioBoxCount() {return m_nNumAssociations;}
	BOOL		Disable();
	BOOL		Enable();

	CCObject*	GetSelected();

protected:
	DialogOp*				m_pDialog;
	CGadgetAssociation*		m_Associations;
	UINT32					m_nNumAssociations;
};


#endif	// INC_RADIO
