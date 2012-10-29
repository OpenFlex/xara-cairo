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

// FreeHand Tool Info bar operations


#ifndef LIVEEFFECTSINFO_INC
#define LIVEEFFECTSINFO_INC

#include "xmlutils.h"
#include "valfunc.h"  // for valuefunctionID

class LiveEffectsTool;
class EffectsStack;




/********************************************************************************************

>	class LiveEffectsInfoBarOp : public InformationBarOp

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/94
	Purpose:	Class for handling the FreeHand tool's information bar.

********************************************************************************************/

class LiveEffectsInfoBarOp : public InformationBarOp
{
	CC_DECLARE_DYNCREATE( LiveEffectsInfoBarOp )  
public:
	// Dummy default constructor for DYNCREATE
	LiveEffectsInfoBarOp();
	~LiveEffectsInfoBarOp();

	// All messages to the info bar come through here
	MsgResult 			Message(Msg* Msg);

	// Functions to allow the tool to talk to the info bar
	void				SetToolActiveState(BOOL IsToolActive);
	virtual void		UpdateState(); // Called during idle processing to disable controls
	virtual void		HandleCreate();

// LiveEffect Tool specific functionality
protected:
	void				SetGadgetWritable(INT32 id, BOOL enable);
	void				GadgetMessage_Label(DialogMsg* Message);
	void				GadgetMessage_Order(DialogMsg* Message);
	void				GadgetMessage_Edit(DialogMsg* Message);
	void				GadgetMessage_Add(DialogMsg* Message);
	void				GadgetMessage_Insert(DialogMsg* Message);
	void				GadgetMessage_Remove(DialogMsg* Message);
	void				GadgetMessage_RemoveAll(DialogMsg* Message);
	void				GadgetMessage_Setup(DialogMsg* Message);
	void				GadgetMessage_Resolution(DialogMsg* Message);
	void				GadgetMessage_ToggleLock(DialogMsg* Message);
	void				GadgetMessage_ToggleLockAll(DialogMsg* Message);

	void				PopulateOrderDropdown(EffectsStack* pPPStack, INT32 iSelectedStackPos = -1);
	void				PopulateResolutionDropdown(EffectsStack* pStack, 
													ListRange* pLevelRange,
													BOOL bUpdateList = TRUE);
	void				UpdateAddButton(EffectsStack* pStack, ListRange* pLevelRange);
	void				UpdateEditButton(EffectsStack* pStack, ListRange* pLevelRange);
	void				UpdateLockButton(ListRange* pLevelRange);
	void				UpdateRemoveButton(ListRange* pLevelRange);
	void				UpdateLockAllButton();
	void				UpdateRemoveAllButton();
	void				UpdateSetupButton();

public:	
	// Keep a pointer to the Freehand tool in here
	LiveEffectsTool*	m_pTool;
	
protected:
	// Since we get Selection Changing message before the controls are made
	// we need to keep a flag to indicate if the controls have been built
	BOOL 				m_bControlsExist;
	BOOL				m_bDropDownInited;
	BOOL				m_bLockSwitchState;
	BOOL				m_bLockAllSwitchState;
};
	

/********************************************************************************************

>	class LiveEffectsInfoBarOpCreate : public BarCreate

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/94
	Purpose:	Class for creating LiveEffectsInfoBarOps.
				Derived classes of BarCreate are used by DialogBarOp::ReadBarsFromFile()

********************************************************************************************/

class LiveEffectsInfoBarOpCreate : public BarCreate
{
public:
	DialogBarOp*	Create() { return (new LiveEffectsInfoBarOp); }
};



#endif	// LIVEEFFECTSINFO_INC






