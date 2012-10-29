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

class BevelTool;
class BevelInfo;
class BevelBlob;

/********************************************************************************************

>	class BevelInfoBarOp : public InformationBarOp

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/2/99
	Purpose:	Class for handling the Bevel tool's information bar.

********************************************************************************************/

class BevelInfoBarOp : public InformationBarOp
{
	CC_DECLARE_DYNCREATE( BevelInfoBarOp )  
public:
	// Dummy default constructor for DYNCREATE
	BevelInfoBarOp();

	// All messages to the info bar come through here
	MsgResult 	Message(Msg* Msg);

	// Functions to allow the tool to talk to the info bar
	void SetToolActiveState(BOOL IsToolActive);
	void SetRetroState(BOOL CanRetroFit);
	void SetRetroString();

	virtual void UpdateState(); // Called during idle processing to disable controls

	// this updates the controls depending on the current selection
	void UpdateControls();

	// updates the variables depending on the slider if bIntoVariables is TRUE,
	// if bIntoVariables is FALSE then updates the slider depending on the variables
	void SliderUpdate(BOOL bIntoVariables, BOOL bTestMany = TRUE);

	// Keep a pointer to the Freehand tool in here
	BevelTool	*	pTool;
	BOOL 			CanRetroFit;

	// Since we get Selection Changing message before the controls are made
	// we need to keep a flag to indicate if the controls have been built
	BOOL 			ControlsExist;

	// creates/updates bevel on selected objects
	void DoBevel();

	// slider values
	// public so external classes can set them
	INT32 m_Depth;
	INT32 m_LightAngle;
	INT32 m_Contrast;
	INT32 m_SliderComboIndex;
	INT32 m_LightTilt;

	// sets up a bevelinfo class dependent on the settings of the dialog
	// public because the tool needs to use this too for the blob dragging code
	void SetUpBevelInfo(BevelInfo * pBevelInfo);

	// used by the bevel controller node to determine if the bevel info bar
	// is active or not
	static BevelInfoBarOp * GetCurrentBevelInfoBar() { return pCurrentBar; }

	// starts the drag on a particular blob
	void BeginDrag(BevelBlob * pBlob);

	// deals with pointer movement messages when dragging
	void DragPointerMove( DocCoord PointerPos, ClickModifiers ClickMods, 
								   Spread* pSpread, BOOL bSolidDrag);

	// finishes the drag & updates the variables in the particular blobs list
	void DragFinished( DocCoord PointerPos, ClickModifiers ClickMods, 
								Spread* pSpread, BOOL Success, BOOL bSolidDrag);

	// returns TRUE for being in the middle of a drag
	BOOL AmDragging() { return m_bAmDragging; }

	// returns TRUE for dragging the slider
	BOOL AmDraggingSlider() { return m_bAmDraggingSlider; }

	void UpdateInnerOuterButtons(BOOL bMany, BOOL bOuter, BOOL bNoSelection);

	// when the slider is a depth slider, these set & get its values (the slider
	// is logarithmic)
	MILLIPOINT GetSliderDepth();
	void SetSliderDepth(MILLIPOINT Depth);

	static BevelInfoBarOp * pCurrentBar;

	BOOL m_BetweenViews;

private:
	// conversion functions for the edit box
	BOOL ConvertValueToString(String_256 &In, const INT32 value, UnitType type=NOTYPE);
	BOOL ConvertStringToValue(CGadgetID ID,INT32 &value);

	void HandleBevelTypeChanged();
	void HandleSliderChanged();
	void HandleBevelDirectionChanged();

	void HandleBevelDirectionsToInner();
	void HandleBevelDirectionsToOuter();

	/////////////////////////////////////////////////////////////////////////////////////////
	// Karim 11/09/2000
	// New methods to support the new join-type infobar buttons.

	void HandleJoinTypeMitreClicked();
	void HandleJoinTypeRoundClicked();
	void HandleJoinTypeBevelClicked();
	void ChangeJoinType(JointType jt);
	void UpdateJoinTypeControls();
	void EnableDisableJoinTypeControls();

	/////////////////////////////////////////////////////////////////////////////////////////

	// control enabling stuff
	BOOL m_bControlsEnabled;
	BOOL m_bComboChanged;

	void RedrawBlobs(BOOL bAngle = TRUE, BOOL bTilt = FALSE);

	BevelBlob * m_pDragBlob;

	// the angle of the blob before dragging
	INT32 m_BlobAngle;

	BOOL m_bAmDragging;

	void SetBlobNodesAngle(INT32 Angle);

	// does the AttributeSelected with the given parameters
	void DoBevelAttrChange(BevelInfo *pBI);

	// has the user set the inner/outer ?
	BOOL m_bUserSet;
	INT32 m_UserIndent;

	// functions for loading strings into combos
	void LoadBevelTypeComboStrings(BOOL bMany);
	void LoadBevelDirectionComboStrings(BOOL bMany);

	BOOL m_bButtonIsInner;
	BOOL m_bButtonIsOuter;

	BOOL m_bAmDraggingSlider;

	MILLIPOINT m_LastDragWidth;
};
	

/********************************************************************************************

>	class BevelInfoBarOpCreate : public BarCreate

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/4/94
	Purpose:	Class for creating BevelInfoBarOps.
				Derived classes of BarCreate are used by DialogBarOp::ReadBarsFromFile()

********************************************************************************************/

class BevelInfoBarOpCreate : public BarCreate
{
public:
	DialogBarOp*	Create() { return (new BevelInfoBarOp); }
};



#endif	// FREEINFO_INC






