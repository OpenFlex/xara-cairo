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

#ifndef	OPTOKEN_BARDUPLICATIONOP

#include "cutop.h"

#define OPTOKEN_BARDUPLICATIONOP	_T("BarDuplicationOp")
#define OPTOKEN_SHORTENBAROP		_T("ShortenBarOp")
#define OPTOKEN_DELBAROP			_T("DeleteBarOp")
#define OPTOKEN_SHOWSTATE			_T("ShowStateOp")

#include "slicehelper.h"

class TemplateAttribute;
/********************************************************************************************

>	class OpBarDuplication : public CarbonCopyOp

	Author:		Simon_Knight (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/9/99
	Purpose:	Make a complete copy of the bar.
				Only the buttons names are made unique
				and there is a new bar name.
				It is positioned next to the original bar.
********************************************************************************************/
class CCAPI OpDuplicateBar: public CarbonCopyOp
{         
	CC_DECLARE_DYNCREATE( OpDuplicateBar )    

public:
	OpDuplicateBar();								
	static BOOL	Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	//virtual	void	Do(OpDescriptor* token);
    void			DoWithParam(OpDescriptor* token, OpParam* pOpParam);

	String_256 GetNewButtonName(String_256 &Name);
	void DuplicateBar(String_256 &OriginalBarName, String_256 &NewBarName, INT32 ButtonsToAdd = 0, INT32 Spacing = 0, BOOL IsHoriz = FALSE);
	Node * CopyBarMember(Node * pNode, const String_256 &OriginalBarName, const String_256 &NewBarName, Trans2DMatrix * pTransformer, const INT32 * pKnownButonIndex = NULL);

private:
	INT32 m_ButtonNumberList[MAX_BUTTONS_IN_A_BAR];
	TemplateAttribute ** m_ppFoundButton[MAX_BUTTONS_IN_A_BAR];
	INT32 m_ExistingButtonsInBar;
};    


class OpParamBarDuplication : public OpParam
{
public:
	OpParamBarDuplication()
			{	
				m_OldBarName = _T("Bar1");
				m_NewBarName = _T("Bar2");
				m_ButtonsToAdd = 0;
				m_Spacing = 0;
				m_IsHoriz = FALSE;
			}

	OpParamBarDuplication(String_256 OldBarName, String_256 NewBarName, INT32 ButtonsToAdd = 0, INT32 Spacing = 0, BOOL IsHoriz = FALSE)
			{	
				m_OldBarName = OldBarName;
				m_NewBarName = NewBarName;
				m_ButtonsToAdd = ButtonsToAdd;
				m_Spacing = Spacing;
				m_IsHoriz = IsHoriz;
			}

	String_256 m_OldBarName;
	String_256 m_NewBarName;
	INT32 m_ButtonsToAdd;
	INT32 m_Spacing;
	BOOL m_IsHoriz;
};



/********************************************************************************************

>	class CCAPI OpShortenBar: public CarbonCopyOp

	Author:		Simon_Knight (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/10/99
	Purpose:	Will cut down the size of a bar
				to the number of buttons requested by
				deleting the last buttons in the bar
********************************************************************************************/
class CCAPI OpShortenBar: public CarbonCopyOp
{
	CC_DECLARE_DYNCREATE( OpShortenBar )    

public:
	OpShortenBar();								
	static BOOL	Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
    void			DoWithParam(OpDescriptor* token, OpParam* pOpParam);
	BOOL TrimBarDownToThisManyButtons(const StringBase &BarName, INT32 NewNoOfButtons);
};    


class OpParamShortenBar : public OpParam
{
public:
	OpParamShortenBar()
			{	
				m_BarName = _T("Bar1");
				m_NoOfButtons = 4;
			}

	OpParamShortenBar(String_256 BarName, INT32 NoOfButtons)
			{	
				m_BarName = BarName;
				m_NoOfButtons = NoOfButtons;
			}

	String_256 m_BarName;
	INT32 m_NoOfButtons;
};



/********************************************************************************************

>	class CCAPI OpShortenBar: public CarbonCopyOp

	Author:		Simon_Knight (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/10/99
	Purpose:	Will cut down the size of a bar
				to the number of buttons requested by
				deleting the last buttons in the bar
********************************************************************************************/
class CCAPI OpDelBar: public CarbonCopyOp
{
	CC_DECLARE_DYNCREATE( OpDelBar )    

public:
	OpDelBar();								
	static BOOL	Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
    void			DoWithParam(OpDescriptor* token, OpParam* pOpParam);
	static BOOL DelBar(const StringBase &BarName, INT32 State, UndoableOperation * pOp);
};    


class OpParamDelBar : public OpParam
{
public:
	OpParamDelBar()
			{	
				m_BarName = _T("Bar1");
				m_State = 5; // 5 == all states
			}

	OpParamDelBar(String_256 BarName, INT32 State)
			{	
				m_BarName = BarName;
				m_State = State;
			}

	String_256 m_BarName;
	INT32 m_State;
};

/********************************************************************************************

>	class CCAPI OpShortenBar: public CarbonCopyOp

	Author:		Simon_Knight (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/10/99
	Purpose:	Will cut down the size of a bar
				to the number of buttons requested by
				deleting the last buttons in the bar
********************************************************************************************/
class CCAPI OpShowState: public UndoableOperation
{
	CC_DECLARE_DYNCREATE( OpShowState )    

public:
	OpShowState();								
	static	BOOL	Init();				
	static	OpState	GetState(String_256*, OpDescriptor*);		
    void	DoWithParam(OpDescriptor* token, OpParam* pOpParam);
	static void	ShowState(INT32 ShowLayer, UndoableOperation * pOp);
};    




#endif // OPTOKEN_BARDUPLICATIONOP
