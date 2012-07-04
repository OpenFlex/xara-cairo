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


#ifndef BRUSHDLG_H
#define BRUSHDLG_H

#define OPTOKEN_BRUSHEDIT_DLG	_T("CBrushEditDlg")
#define OPTOKEN_OPBRUSHEDIT		_T("OpBrushEdit")

//#include "brshgdgt.h"
#include "brshdata.h"
#include "opdrbrsh.h"

enum RenderPreviewType { RT_LINE, RT_S, RT_LAST };
typedef enum RectSideInfo {WIDTH, HEIGHT, LONGEST};

class CBrushEditDlg : public DialogTabOp//DialogOp
{
	CC_DECLARE_DYNCREATE( CBrushEditDlg )
	
	private:

PORTNOTE("other", "Disabled CBrushGadget")
#ifndef EXCLUDE_FROM_XARALX
	// ptr to the owning gadget
		CBrushGadget*		m_pOwningGadget;
#endif		

	// identifier for this particular instance
		CGadgetID			Id_m;

	// our private brush data
		BrushData*			OriginalData;
		BrushData*			EditData;
			
		BrushData			m_LastData;
		BrushHandle         m_Handle;           // if we are editing a definition, this is its handle

		AttrBrushType*      pAttrBrush_m;		// pointer to the node we are altering
		AttrBrushType*      pOrigAttrBrush_m;	// pointer to a copy of the node we are altering

		ChangeBrushType     ChangeType_m;		// the change that we are going to commit
		ChangeBrushOpParam  ChangeParam_m;

		BOOL				FirstTime;			// is this the first time weve
												// shown the dialog (with the
												// brush preview)
	
		BOOL				EditingBrushDef;	// are we editing the brush definition?
		BOOL				m_bDisableOps;      // prevents us from launching operations
		RenderPreviewType	RenderType;			// what style we render previews in

		DocUnitList* pDocUnitList;				// ptr to document units
		UnitType 	 CurrentUserUnitType;		// the current unit type (for output in edit boxes)

		BOOL				m_bDisableGadgets;

		BOOL				m_bPreventUpdateSet;
		BOOL				m_SliderStarted;   // set when a slider movement begins

		static BOOL			m_bIsOpen;          // as we only ever want one instance of this so keep track of when we open it

		void HideShuffleIrrelevantButtons ();
		
		void InitBrushSpacing (BOOL OnlyForUnitChange = FALSE);
		void InitBrushOffset (BOOL OnlyForUnitChange = FALSE);
		void InitBrushScaling (BOOL OnlyForUnitChange = FALSE);
		void InitBrushEffects (BOOL OnlyForUnitChange = FALSE);
		void InitBrushSequence (BOOL OnlyForUnitChange = FALSE);
		void InitBrushFill (BOOL OnlyForUnitChange = FALSE);

		void ReInitBrushSpacing ();
		void ReInitBrushOffset ();
		void ReInitBrushScaling ();
		void ReInitBrushEffects ();
		void ReInitBrushSequence ();
		void ReInitBrushFill();
		void ReInitUnitDependantFields (CDlgResID ThePage);

		void InitComboPathOffsetType ();
		void InitSequenceType ();

		void HandleCommit (DialogMsg* Msg);
		void HandleSelectionChange (DialogMsg* Msg);
		void HandleButtonDown (DialogMsg* Msg);
		void HandleSliderPosChanging (DialogMsg* Msg);
		void HandleSliderPosSet (DialogMsg* Msg);

		void ReadButtons ( DialogMsg* Msg);
		void ReadRadios (DialogMsg* Msg);
		void ReadEditBox (DialogMsg* Msg);
		void ReadComboBox (DialogMsg* Msg);
		void ReadCheckBox (DialogMsg* Msg);
		void ReadSlider (DialogMsg* Msg);
		void WriteSliders (DialogMsg* Msg);

		BOOL UsingRandomSpacing;
		BOOL UsingRandomOffset;
		BOOL UsingRandomScaling;

		CGadgetID EditGadgetLostFocus;

		void UpdateEditBox (CGadgetID GadgetToUpdate);

		void LaunchOp();
		UINT32 GetNewRandomNumber(UINT32 OldNumber);
		void ReInitPage(CDlgResID PageID);
	
		BOOL GetAttributeNodeFromDefinition();

		void HandleDocSelectionChange();
		void RefreshActivePage();

		void GetSpacingRange(double*, double*);
		void SetSpacingSlider();
		void SetSpacingIncrSlider();
	
		void SetOffsetValSlider();
		void GetOffsetRange(double*, double*);

		MILLIPOINT GetSideOfBoundingBox(RectSideInfo RectInfo);
		double GetDistanceAsPercentageOfBBox(MILLIPOINT Distance, RectSideInfo RectInfo);
		MILLIPOINT GetPercentageAsDistance(double Percent, RectSideInfo RectInfo);
		void ChangeButtonText();

		void SetRandomRangeText(CGadgetID SliderID);
		String_32 GetRandomRangeText(INT32 SliderVal);
		String_32 GetRotationRandomText(INT32 SliderVal);
		String_32 GetRandomText(INT32 Value, INT32 MaxValue);

		// we need to subclass our edit boxes, so we'll use the helper
		virtual BOOL AddControlsToHelper();
		virtual void RemoveControlsFromHelper();

	public:
		// dialog constructor
		CBrushEditDlg ();
		// dialog destructor
		~CBrushEditDlg ();

		// dialog details ----------------------------------------
		
		static const		UINT32	IDD;
		static const		CDlgMode	Mode;

		// usual interface ----------------------------------------
		static	BOOL		Init ();
		static	OpState		GetState (String_256*,  OpDescriptor*);

		void				Do (OpDescriptor*);
	
		void				DoWithParam ( OpDescriptor*,  OpParam* OwningGadgetParams );
		virtual	MsgResult	Message( Msg* );

		void				CreateNewBrush();

		void HandleBrushEditSpacingMsg (DialogMsg* Msg);
		void HandleBrushEditOffsetMsg (DialogMsg* Msg);
		void HandleBrushEditScalingMsg (DialogMsg* Msg);
		void HandleBrushEditEffectMsg (DialogMsg* Msg);
		void HandleBrushEditSequenceMsg (DialogMsg* Msg);
		void HandleBrushFillMsg (DialogMsg* Msg);

PORTNOTE("other", "Disabled CBrushGadget")
#ifndef EXCLUDE_FROM_XARALX
		void InvokeVia (CBrushGadget& pInvokeWith, BrushData* pInvokeOn, 
						AttrBrushType* pBrush, BOOL& bMany);
		void InvokeVia (CBrushGadget& pInvokeWith, BrushData* pInvokeOn, 
						AttrBrushType* pBrush, AttrBrushType* pOrigBrush, BOOL& bMany);
		void InvokeVia (CBrushGadget& pInvokeWith, BrushHandle Handle);
#endif

		virtual BOOL RegisterYourPagesInOrderPlease ();	// Add in tab pages
		void ReInitialiseDialog (BrushData* pData);	
	
		void SetDialogTitle(String_256 Title);
		static AttrBrushType* GetSingleSelectedBrushAttribute();
		
};

#endif
