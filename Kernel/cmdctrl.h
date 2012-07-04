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
 *  */

/********************************************************************************************

>	Class CmdControl : public ListItem

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/93
	Purpose:	
		A CmdControl is an abstract class from which all types of interface controls inherit. 
		These controls include MenuItems, Keyboard Accelerators, Buttons etc. They all have 
		one main thing in common and that is that they are built out of Operations. Unlike 
		Tools Controls have only one operation behind them.

	Errors:		None yet.
	SeeAlso:	ListItem

********************************************************************************************/

#ifndef INC_CMD_CONTROL
#define INC_CMD_CONTROL

//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "listitem.h"  - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "opdesc.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/********************************************************************************************
>	class CCAPI CmdControl : public ListItem

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	sometime in 1993
	Purpose:	Base class for Camelot menu items.  Unfortunately neither Mario or Andy
				ever got round to documenting this stuff, ha ha ha
	SeeAlso:	-
********************************************************************************************/

class CCAPI CmdControl : public ListItem
{ 
public:
	
	CmdControl() { /* Empty */ }
	CmdControl(OpDescriptor* Owner);

	virtual BOOL IsEnabled();
	virtual void PerformAction();
	virtual BOOL UpdateControlState();
	virtual String_256* GetWhyDisabled();

	virtual OpDescriptor* GetOpDescriptor() const;

protected:                        
	UINT32 ControlId;
	String_256 WhyDisabled;
	OpState ControlState;
	OpDescriptor* OwnerOperation;

private:
	CC_DECLARE_MEMDUMP(CmdControl);
};

/********************************************************************************************

>	Class HotKeyO : public CmdControl

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Purpose:	
		The HotKey class represents keyboard accelerators for menu items and other short-cut 
		keys used for other types of controls. HotKey inherits from the CmdControl class 
		provides it with the ability to perform an operation which is the commonality between
		all types of CmdControls.

	Errors:		None yet.
	SeeAlso:	CmdControl

********************************************************************************************/

#if 0
// Not obvious when & why this was all disabled - AB20060106
class CCAPI HotKeyO : public CmdControl
{ 

	CC_DECLARE_MEMDUMP(HotKeyO);

private:
	// List of all Hotkeys
	static List HotKeys; 
	
	String_256 Description;
	String_256 MenuTextDesc;

public:
	
	HotKeyO() {}

	HotKeyO( OpDescriptor *Owner, String_256 *MenuText );

	BOOL UpdateControlState();

	UINT32 GetHotKeyId();
	
	String_256* GetDescription();
	String_256* GetMenuTextDesc();
	
   	static UINT32 AutomaticHotKeyID;
	static UINT32 GetNextAutomaticHotKeyID();

	// a search function that returns a pointer to the HotKey
	static HotKeyO* FindHotKey(UINT32 HotKeyId);
	
	static HotKeyO* FindHotKey(OpDescriptor* OpDesc);

	// Need a method of killing off all the HotKeys at program end
	static void DestroyAll();

/********************************************************************************************

>	static HotKey* HotKey::GetFirstHotKey()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Purpose:	returns the first HotKey in the list

********************************************************************************************/
	static HotKeyO* GetFirstHotKey()	
	{ 
		return (HotKeyO*) HotKeys.GetHead(); 
	}


	
/********************************************************************************************

>	static HotKey* HotKey::GetNextHotKey( HotKey* CurrHotKey )

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Inputs:		pointer to last HotKey return by GetFirst to GetNextHotKey
	Purpose:	return the next HotKey in the list

********************************************************************************************/
	static HotKeyO* HotKeyO::GetNextHotKey( HotKeyO* CurrHotKey )
	{ 
		return (HotKeyO*) HotKeys.GetNext( CurrHotKey ); 
	}



private:          

/********************************************************************************************

>	static void HotKey::LinkHotKey( HotKey* ThisHotKey )

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Inputs:		pointer to this HotKey
	Purpose:	Add the HotKey to the list of all HotKeys
	Scope:		private

********************************************************************************************/

	static void HotKeyO::LinkHotKey( HotKeyO* ThisHotKey )
	{ 
		HotKeys.AddTail(ThisHotKey); 
	}

};

/********************************************************************************************

>	Class Button : public CmdControl

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Purpose:	
		The Button class represents keyboard accelerators for menu items and other short-cut 
		keys used for other types of controls. Button inherits from the CmdControl class 
		provides it with the ability to perform an operation which is the commonality between
		all types of CmdControls.

	Errors:		None yet.
	SeeAlso:	CmdControl

********************************************************************************************/

class CCAPI Button : public CmdControl
{ 

	CC_DECLARE_MEMDUMP(Button);

private:
	// List of all Button Bar
	static List ButtonBar;

	static UINT32 NumberOfButtons;
	static UINT32 NumberOfSeparators;

	String_256 Description;
	
	BOOL FollowedBySeparator;
	
	UINT32 BitMapOffset;	

public:
	
	Button() {}

	Button( OpDescriptor *Owner, BOOL Separator, UINT32 BitMapNo = 0 );

	BOOL UpdateControlState();

	UINT32 GetButtonId();
	
	String_256* GetDescription();
	
   	static UINT32 AutomaticButtonID;
	static UINT32 GetNextAutomaticButtonID();

	// a search function that returns a pointer to the Button
	static Button* FindButton(UINT32 ButtonId);
	
	// Need a method of killing off all the Buttons at program end
	static void DestroyAll();

/********************************************************************************************

>	static Button* Button::GetFirstButton()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Purpose:	returns the first Button in the list

********************************************************************************************/
	static Button* GetFirstButton()	
	{ 
		return (Button*) ButtonBar.GetHead(); 
	}


	
/********************************************************************************************

>	static Button* Button::GetNextButton( Button* CurrButton )

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Inputs:		pointer to last Button return by GetFirst to GetNextButton
	Purpose:	return the next Button in the list

********************************************************************************************/
	static Button* Button::GetNextButton( Button* CurrButton )
	{ 
		return (Button*) ButtonBar.GetNext( CurrButton ); 
	}

/********************************************************************************************

>	static UINT32 Button::GetNumberOfButtons()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Outputs:	Number of buttons on button bar
	Purpose:	returns the number of buttons on the button bar

********************************************************************************************/
	static UINT32 Button::GetNumberOfButtons()
	{ 
		return NumberOfButtons; 
	}

/********************************************************************************************

>	static UINT32 Button::GetNumberOfSeparators()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Outputs:	Number of Separators on button bar
	Purpose:	returns the number of separators on the button bar

********************************************************************************************/
	static UINT32 Button::GetNumberOfSeparators()
	{ 
		return NumberOfSeparators; 
	}

/********************************************************************************************

>	BOOL Button::IsFollowedBySeparator()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Returns:	TRUE if Button is followed by a separatorand FALSE otherwise
	Purpose:	Determines whether a button is followed by a separator on the Button bar

********************************************************************************************/
	BOOL Button::IsFollowedBySeparator()
	{ 
		return FollowedBySeparator; 
	}

/********************************************************************************************

>	UINT32 Button::GetBitMapOffset()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/10/93
	Returns:	The Bitmap offset of the Button icon
	Purpose:	Determines the bitmap offset of the button's icon

********************************************************************************************/
	UINT32 Button::GetBitMapOffset()
	{ 
		return BitMapOffset; 
	}

private:          

/********************************************************************************************

>	static void Button::LinkButton( Button* ThisButton )

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Inputs:		pointer to this Button
	Purpose:	Add the Button to the list of all Buttons
	Scope:		private

********************************************************************************************/

	static void Button::LinkButton( Button* ThisButton )
	{ 
		ButtonBar.AddTail(ThisButton); 
	}

};

#endif

#endif
