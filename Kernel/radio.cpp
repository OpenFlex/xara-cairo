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


#include "camtypes.h"
#include "radio.h"


// Place any IMPLEMENT type statements here
CC_IMPLEMENT_MEMDUMP(RadioGroup, CC_CLASS_MEMDUMP)


// We want better memory tracking
#define new CAM_DEBUG_NEW


// Functions follow

/********************************************************************************************

>	BOOL RadioGroup::SetAssociations(DialogOp* pDialog, CGadgetAssociation* AssocArray, 
					UINT32 NumGadgets)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/05/96
	Inputs:		pDialog - The dialog in which this RadioGroup is
				AssocArray - the array of CGadgetID / CCObject associations
				NumGadgets - the number of radio items in the array
	Outputs:	-
	Returns:	TRUE if set OK
	Purpose:	Sets up the RadioGroup. Call prior to any other member.
	Errors:		ERROR2IF pDialog, AssocArray NULL or NumGadgets zero
	SeeAlso:	class RadioGroup

********************************************************************************************/
BOOL RadioGroup::SetAssociations(DialogOp* pDialog, CGadgetAssociation* AssocArray, UINT32 NumGadgets)
{
	ERROR2IF(pDialog == NULL, FALSE, "RadioGroup::SetAssociations() - pDialog NULL");
	ERROR2IF(AssocArray == NULL, FALSE, "RadioGroup::SetAssociations() - AssocArray NULL");
	ERROR2IF(NumGadgets == 0, FALSE, "RadioGroup::SetAssociations() - NumGadgets is zero");

	m_pDialog = pDialog;
	m_Associations = AssocArray;
	m_nNumAssociations = NumGadgets;
	return TRUE;
}


/********************************************************************************************

>	CCObject*	RadioGroup::GetDefault()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/05/96
	Inputs:		-
	Outputs:	-
	Returns:	NULL
	Purpose:	Allows the setting of a new ApplyNow state.
	Errors:		ERROR3IF always because its not implemented. Do not use
	SeeAlso:	class RadioGroup

********************************************************************************************/
CCObject*	RadioGroup::GetDefault()
{
	ERROR3IF(TRUE, "RadioGroup::GetDefault() - not implemented");

	return NULL;
}


/********************************************************************************************

>	BOOL RadioGroup::Disable()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/05/96
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if successful
				FALSE otherwise
	Purpose:	Disables all the radio items in this group
	Errors:		ERROR2IF no dialog associated with this RadioGroup
	SeeAlso:	Enable()

********************************************************************************************/
BOOL RadioGroup::Disable()
{
	ERROR2IF(m_pDialog == NULL, FALSE, "RadioGroup::Disable - m_pDialog not set");

	for (UINT32 i = 0; i < GetRadioBoxCount(); i++)
	{
		m_pDialog->EnableGadget(m_Associations[i].m_GadgetID, FALSE);
	}
	return TRUE;
}


/********************************************************************************************

>	BOOL RadioGroup::Enable()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/05/96
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if successful
				FALSE otherwise
	Purpose:	Disables all the radio items in this group
	Errors:		ERROR2IF no dialog associated with this RadioGroup
	SeeAlso:	Enable()

********************************************************************************************/
BOOL RadioGroup::Enable()
{
	ERROR2IF(m_pDialog == NULL, FALSE, "RadioGroup::Disable - m_pDialog not set");

	for (UINT32 i = 0; i < GetRadioBoxCount(); i++)
	{
		m_pDialog->EnableGadget(m_Associations[i].m_GadgetID, FALSE);
	}
	return TRUE;
}


/********************************************************************************************

>	BOOL RadioGroup::SetDefault(CCObject* pDefaultObject)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/05/96
	Inputs:		pDefaultObject - pointer to the object 
	Outputs:	-
	Returns:	TRUE if the gadget with which pDefaultObject is associated was set
				FALSE otherwise
	Purpose:	Sets the gadget associated with the given object as the default (using
				SetBoolGadgetSelected)
	Errors:		ERROR2IF no dialog associated with this RadioGroup
				ERROR3IF pDefaultObject is not associated with any gadget in this radio group
	SeeAlso:	class RadioGroup

********************************************************************************************/
BOOL RadioGroup::SetDefault(CCObject* pDefaultObject)
{
	ERROR2IF(m_pDialog == NULL, FALSE, "RadioGroup::SetDefault - m_pDialog not set");

	for (UINT32 i = 0; i < GetRadioBoxCount(); i++)
	{
		if (m_Associations[i].m_pObject == pDefaultObject)
			return (m_pDialog->SetBoolGadgetSelected(m_Associations[i].m_GadgetID, TRUE));
	}
	ERROR3IF(TRUE, "RadioGroup::SetDefault - pDefaultObject not in RadioGroup");
	return FALSE;
}	


/********************************************************************************************

>	CCObject* RadioGroup::GetSelected()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/05/96
	Inputs:		-
	Outputs:	-
	Returns:	Pointer to the Object associated with the radio box selected
	Purpose:	Allows the setting of a new ApplyNow state.
	Errors:		ERROR2IF no dialog associated with this RadioGroup
	SeeAlso:	class RadioGroup

********************************************************************************************/
CCObject* RadioGroup::GetSelected()
{
	ERROR2IF(m_pDialog == NULL, NULL, "RadioGroup::GetSelected - m_pDialog not set");

	for (UINT32 i = 0; i < GetRadioBoxCount(); i++)
	{
		if (m_pDialog->GetBoolGadgetSelected(m_Associations[i].m_GadgetID))
			return (m_Associations[i].m_pObject);

	}
	ERROR3IF(TRUE, "RadioGroup::GetSelected() - None selected");
	return NULL;
}	
