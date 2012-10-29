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


#ifndef FREEINFO_INC
#define FREEINFO_INC

class FreeHandTool;

#include "brshgdgt.h"
#include "brshcomp.h"  // for brushhandle
#include "valfunc.h"  // for valuefunctionID
#include "bitmapgriddropdown.h"

#include <list>

// list to contain brushhandles in order of most recent use
typedef list<BrushHandle> BrushList;

/********************************************************************************************

>	class FreeHandInfoBarOp : public InformationBarOp

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/94
	Purpose:	Class for handling the FreeHand tool's information bar.

********************************************************************************************/

class FreeHandInfoBarOp : public InformationBarOp
{
	CC_DECLARE_DYNCREATE( FreeHandInfoBarOp )  
public:
	// Dummy default constructor for DYNCREATE
	FreeHandInfoBarOp();
	~FreeHandInfoBarOp();

	// All messages to the info bar come through here
	MsgResult 	Message(Msg* Msg);

	// Functions to allow the tool to talk to the info bar
	void SetToolActiveState(BOOL IsToolActive);
	void SetRetroState(BOOL CanRetroFit);
	void SetRetroString();

	void AddBrush();
	void AddBrush(BrushHandle Handle);

	virtual void UpdateState(); // Called during idle processing to disable controls

	BrushData GetBrushDataFromSelection(BOOL* pSelEmpty = NULL);
	void	  SetDefaultStrokeInCombo();

	void RemoveBrush(BrushHandle Handle);

PORTNOTE("other", "Disabled Brush editing")
#ifndef EXCLUDE_FROM_XARALX
	static CBrushGadget* GetBrushGadget() { return &BrushGadget;}
#endif

protected:
	BOOL InitBrushList();  // initialises the brush list
	BOOL ReInitBrushList(); // re-initialises but remembers the previous order
	BOOL SetBrushListToControl();
	BOOL SetStrokesToControl(); 
protected:  
	// in a vain attempt to clear up the message proc I'm farming out some of it here
	void	HandleBrushSelectChange();
	void	HandleCreate();
	void	HandleSliderPosChanging();
	void	HandleStrokeSelectChange();
	
	void	LaunchBrushEditDialog();
	void	SetHeadOfListSelected();
	void	SetDisplayBrush();
	void	SetBrushComboFromSelection();

	BrushHandle	GetBrushHandleFromSelection(BOOL* pSelEmpty = NULL);

	void	SetStrokeComboFromSelection();
	INT32		GetStrokeIndexFromValueFunctionID(ValueFunctionID ID);

protected: // helper functions dealing with the brush list
	BrushHandle	GetBrushHandleFromControlIndex(BrushHandle Index); 
	INT32 GetControlIndexFromBrushHandle(BrushHandle Handle);
	void		SetHeadOfList(BrushHandle Handle);		

public:	
	// Keep a pointer to the Freehand tool in here
	FreeHandTool*	pTool;
	BOOL 			CanRetroFit;
	
	
protected:
	// Since we get Selection Changing message before the controls are made
	// we need to keep a flag to indicate if the controls have been built
	BOOL 			ControlsExist;
	BOOL			DropDownInited;
	
/*	
	StrokeList*		m_pStrokeList;

	StrokeHandle	m_DisplayStroke;
*/
	INT32			m_LastSmoothness;

	BrushList*		m_pBrushList;

	BrushHandle		m_DisplayBrush;   // the currently displayed brush in the combo

	CBitmapGridDropDown m_bgddBrushType;
	CBitmapGridDropDown m_bgddStrokes;

PORTNOTE("other", "Disabled Brush editing")
#ifndef EXCLUDE_FROM_XARALX
	static CBrushGadget	BrushGadget; // we only ever want one version of the brush edit dialog
									 // hence the static gadget
#endif

	INT32			    m_SelectedStroke; // the last selected stroke
};
	

/********************************************************************************************

>	class FreeHandInfoBarOpCreate : public BarCreate

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/94
	Purpose:	Class for creating FreeHandInfoBarOps.
				Derived classes of BarCreate are used by DialogBarOp::ReadBarsFromFile()

********************************************************************************************/

class FreeHandInfoBarOpCreate : public BarCreate
{
public:
	DialogBarOp*	Create() { return (new FreeHandInfoBarOp); }
};



#endif	// FREEINFO_INC






