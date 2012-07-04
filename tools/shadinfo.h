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

// Header for the Shadow Tool Info Bar implementation

#ifndef INC_SOFTSHADOWTOOLINFO
#define INC_SOFTSHADOWTOOLINFO

//#include "bars.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#ifdef BUILDSHADOWS


#include "biasgdgt.h"
// all necessary #includes are taken care of by pre-compiled header.

class SoftShadowTool;

/********************************************************************************************

>	class ShadowDragData : public CCObject

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/6/99
	Purpose:	For storing the data on given nodes for dragging

********************************************************************************************/
class ShadowDragData : public ListItem
{
	CC_DECLARE_DYNCREATE(ShadowDragData);

public:
	NodeShadowController * pNode;

	MILLIPOINT	PositionShadowX;
	MILLIPOINT	PositionShadowY;
	INT32			ShadowTransparency;
	MILLIPOINT	PenumbraSize;
	double		ShadowAngle;
	float		ShadowHeight;
	float		ShadowScale;
	MILLIPOINT  GlowWidth;
	MILLIPOINT  FeatherWidth;
};

/********************************************************************************************

>	class SoftShadowInfoBarOp : public InformationBarOp

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/10/96
	Purpose:	Class for handling the tool's information bar.

********************************************************************************************/

class SoftShadowInfoBarOp : public InformationBarOp
{
	CC_DECLARE_DYNCREATE( SoftShadowInfoBarOp )  
public:
	SoftShadowInfoBarOp();				

	MsgResult 	Message(Msg* Msg);		// All messages to the info bar come through here
	SoftShadowTool *pSoftShadowTool;	// Pointer to the shadow tool
	void Init();						// A few Initialisations

private:
	static Document			*pDoc;
	BOOL					ApplyButton;
	Spread*					CurrentSpread;
	BOOL					SliderDragged;
	NodePath*				CurrentNodePath;

public:
	// the current infobar object - allow static member access
	static InformationBarOp * pSoftShadowInfoBar;

	// Enable the gadgets
	void EnableGadgets(BOOL Enable);	

	// Update functions
	void UpdateGadgetPositionShadowX();
	void UpdateGadgetPositionShadowY();
	void UpdateGadgetBlurSlider(BOOL bUpdateSlider = TRUE);
	void UpdateGadgetTranspSlider(BOOL bUpdateSlider = TRUE);
	void UpdateGadgetPenumbraSize();
	void UpdateAllGadgets();
	void UpdateInfoBar();
	void UpdateGadgetHelp();
	void UpdateGadgetTypeButtons();

	// Update the document and the view according the new position of the shadow
	// Undoable!
	void DoChangeShadPos(INT32 x, INT32 y, BOOL UpdateX, BOOL UpdateY);
	void DoChangeShadowPosIncremental(MILLIPOINT incx, MILLIPOINT incy);
	void DoPenumbraSizeBumps(UINT32 Button);
	void DoChangeShadowDarkness(double dDarkness);
	void DoChangePenumbra(INT32 NewPenumbra);
	void DoChangeWidth(INT32 NewWidth);
	void DoChangeAngle(double Angle);
	void DoChangeHeight(double Height);
	void DoChangeScale(double Scale);

	// Non-undoable functions used during dragging/editing
	void ChangeShadowDarkness(double dDarkness);
	void ChangeShadowPenumbra(INT32 nBlur);
	void ChangeShadowPosIncremental(INT32 incx, INT32 incy);

	// Change the transparency of the selected object
	void SetBitmapUpdate(BOOL OnOrOff);
	BOOL SetPenumbraSize(MILLIPOINT PenumSize);

	BOOL ConvertValueToString(String_256 &In, const INT32 value, UnitType type=NOTYPE, TCHAR *unit=_T("pix"));
	BOOL ConvertStringToValue(CGadgetID ID, MILLIPOINT& value);

	// Inputs error
	// Make the error string and then display the error window
	void DoInputError(UINT32 GadgetID);

	// handles the user entering something into the editable control for the blur slider
	void HandleSliderEditChange();

	// handles the user entering something into the transparency slider edit
	void HandleSliderTranspEditChange();

	BOOL DoesWindowExist() { return m_bControlsExist; }

	// used to remove all data from the saved shadow data list
	void DeleteShadowDataList() { ShadowDataList.DeleteAll(); }

	void SaveShadowDragData(List *pList);
	void RestoreShadowDragData(List * pList, BOOL bRegen = FALSE, BOOL bForceRegen = FALSE);

	void HandleShadowTypeChange(ShadowType Type);
	void HandleShadowPosBump(DialogMsg* dmsg, INT32 incx, INT32 incy);

	BOOL SelectShadowsAlone();

private:

	// the stored data list for dragging the slider (so we can restore if necessary)
	List ShadowDataList;

	// the stored data list for dragging a blob
	ShadowDragData m_BlobDragData;

	BOOL m_bControlsExist;

	void HandleNoShadowBtnClicked();
	void HandleWallShadowBtnClicked();
	void HandleFloorShadowBtnClicked();
	void HandleGlowShadowBtnClicked();

	void SetDarknessEditGadget(double dDarkness);
	BOOL GetDarknessEditGadget(double& dDarkness, BOOL &bMany);
	void SetDarknessSlider(double dDarkness);
	double GetDarknessSlider(BOOL* pValid);

public:
	CBiasGainGadget  BiasGainGadget_m;

private:

	void ChangeProfile(CProfileBiasGain* Profile, CGadgetID GadgetID);	// DoChangeProfile

	// returns FALSE for no profile found
	virtual void HandleProfileSelChangingMsg(CBiasGainGadget& Gadget, CGadgetID ProfileGadgetID);
	CProfileBiasGain* GetProfileFromSelection(CGadgetID GadgetID, BOOL* bMany, BOOL* bAllSameType);

	MILLIPOINT GetGlowSliderValue();
	void SetGlowSliderValue(MILLIPOINT Value);

	BOOL m_bBumping;
};
	

/********************************************************************************************

>	class SoftShadowInfoBarOpCreate : public BarCreate

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/10/96
	Purpose:	Class for creating SoftShadowInfoBarOps.
				Derived classes of BarCreate are used by DialogBarOp::ReadBarsFromFile()

********************************************************************************************/

class SoftShadowInfoBarOpCreate : public BarCreate
{
public:
	DialogBarOp* Create() { return (new SoftShadowInfoBarOp); }
};

#endif		// BUILDSHADOWS

#endif 		// INC_SOFTSHADOWTOOLINFO

