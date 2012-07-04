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
//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "gadget.h"


// Place any IMPLEMENT type statements here
CC_IMPLEMENT_MEMDUMP(CCCoreUI, CC_CLASS_MEMDUMP);
CC_IMPLEMENT_MEMDUMP(Gadget, CCCoreUI);
CC_IMPLEMENT_MEMDUMP(NotifyingGadget, Gadget);
CC_IMPLEMENT_MEMDUMP(DialogMgrGadget, NotifyingGadget);
CC_IMPLEMENT_MEMDUMP(Button, DialogMgrGadget);
CC_IMPLEMENT_MEMDUMP(ListControl, DialogMgrGadget);
CC_IMPLEMENT_MEMDUMP(TextControl, DialogMgrGadget);
CC_IMPLEMENT_MEMDUMP(StaticTextControl, DialogMgrGadget);


// We want better memory tracking
// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW


// Functions follow


/*******************************************************************************************

>	Button::Button( DialogOp* const pDialog, CGadgetID ControlID,
					Notifiable* pNotify = &Nobody )

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Default destructor for a Button. Does nothing


*******************************************************************************************/
Button::Button( DialogOp* const pDialog, CGadgetID ControlID, Notifiable* const pNotify): 
		DialogMgrGadget(pDialog, ControlID), m_pNotifyOnPress(pNotify)
{
}


/*******************************************************************************************

>	Button::~Button()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Default destructor for a Button. Does nothing


*******************************************************************************************/
Button::~Button()
{
}


/*******************************************************************************************

>	void Button::OnClicked()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Notifies the Notifiable that this Button has been clicked


*******************************************************************************************/
void Button::OnClicked()
{
	Notify(m_pNotifyOnPress);
}


/*******************************************************************************************

>	TextControl::TextControl(	DialogOp* const pDialog, CGadgetID ControlID,
								const StringBase& InitialText = EmptyString,
								Notifiable* const pTell = &Nobody )

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97

	Purpose:	Default constructor for a TextControl

*******************************************************************************************/
TextControl::TextControl(	DialogOp* const pDialog, CGadgetID ControlID,
							const StringBase& InitialText,
							Notifiable* const pTell ) :
		DialogMgrGadget(pDialog, ControlID),
		m_pObserver(pTell)
{
	// The SetWindowText sends an EN_CHANGE, which calls OnChange, which
	// notifies the Text_control, which updates the String, which notifies
	// the Text_control, which updates the window text, and around and
	// and around. Solve the problem in the OnChange() function, but set
	// "initializing" true to tell OnChange what's going on. Turn off
	// notification to prevent this.
	//
	// I'm assuming synchronous behavior; I don't expect SentWindowText
	// to return until AFTER the EnChange() handler has been executed.
	// If this turns out not to be the case in the future, you'll have
	// to modify this code: add an "initializing" field to the class,
	// set it true instead of calling notify_off, set it false instead
	// of calling notify_on, and modify OnChange to not notify anybody
	// if "initializing" is true.


	if (!InitialText.IsEmpty())
	{
		NotifyOff();
		pDialog->SetStringGadgetValue(m_ControlID, InitialText);
		NotifyOn();
	}
}


const TextControl& TextControl::operator=(const TextControl& OtherControl)
{
	ERROR3("TextControl assignment not implemented\n");

	return *this;
}

TextControl::TextControl(const TextControl& OtherControl) :
	DialogMgrGadget(NULL, 0)
{
	ERROR3("TextControl copy constructor not implemented\n");
}


/*******************************************************************************************

>	void TextControl::UpdateText(const StringBase &NewString)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Default destructor for a TextControl

	Input:		NewString : the string to set in the text control

*******************************************************************************************/
void TextControl::UpdateText(const StringBase &NewString)
{
	ASSERT(m_ControlID != 0 && m_pDialog != NULL);

	m_pDialog->SetStringGadgetValue(m_ControlID, NewString);
	Notify(m_pObserver);
}


/*******************************************************************************************

>	void TextControl::RetrieveText(String* pDisplayedString) const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Default destructor for a TextControl

	Outputs:	pDisplayedString : the string to set in the text control

*******************************************************************************************/
void TextControl::RetrieveText(StringBase* const pDisplayedString) const
{
	ASSERT(m_ControlID != 0 && m_pDialog != NULL);

	if (pDisplayedString != NULL)
	{
		*pDisplayedString = m_pDialog->GetStringGadgetValue(m_ControlID);
	}
}


/*******************************************************************************************

>	void TextControl::OnChange() 

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Default destructor for a TextControl

	Outputs:	pDisplayedString : the string to set in the text control

*******************************************************************************************/
void TextControl::OnChange() 
{
	Notify(m_pObserver);
}




// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
//	StaticTextControl
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //




/*******************************************************************************************

>	StaticTextControl::StaticTextControl(	DialogOp* const pDialog, CGadgetID ControlID,
									const StringBase& InitialText = EmptyString,
									Notifiable* const pTell = &Nobody )

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97

	Purpose:	Default constructor for a TextControl

*******************************************************************************************/
StaticTextControl::StaticTextControl(	DialogOp* const pDialog, CGadgetID ControlID,
										const StringBase& InitialText,
										Notifiable* const pTell ) :
	DialogMgrGadget(pDialog, ControlID),
	m_pObserver(pTell)
{
	if (!InitialText.IsEmpty())
	{
		pDialog->SetStringGadgetValue(m_ControlID, InitialText);
	}
}


/*******************************************************************************************

>	void StaticTextControl::UpdateText(const StringBase &NewString)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Sets the text in this control

	Input:		NewString : the string to set in the static control (label)

*******************************************************************************************/
void StaticTextControl::UpdateText(const StringBase &NewString)
{
	ASSERT(m_ControlID != 0 && m_pDialog != NULL);

	m_pDialog->SetStringGadgetValue(m_ControlID, NewString);
	Notify(m_pObserver);
}


/*******************************************************************************************

>	void StaticTextControl::RetrieveText(String* pDisplayedString) const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Gets the text currently displayed in this StaticTextControl

	Outputs:	pDisplayedString : the string to set in the text control

*******************************************************************************************/
void StaticTextControl::RetrieveText(StringBase* const pDisplayedString) const
{
	ASSERT(m_ControlID != 0 && m_pDialog != NULL);

	if (pDisplayedString != NULL)
	{
		*pDisplayedString = m_pDialog->GetStringGadgetValue(m_ControlID);
	}
}


/*******************************************************************************************

>	void StaticTextControl::OnChange() 

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Don't use this (yet!)

*******************************************************************************************/
inline void StaticTextControl::OnChange() 
{
	Notify(m_pObserver);
}


const StaticTextControl& StaticTextControl::operator=(const StaticTextControl& OtherControl)
{
	ERROR3("StaticTextControl assignment not implemented\n");

	return *this;
}

StaticTextControl::StaticTextControl(const StaticTextControl& OtherControl) :
	DialogMgrGadget(NULL, 0)
{
	ERROR3("StaticTextControl copy constructor not implemented\n");
}

