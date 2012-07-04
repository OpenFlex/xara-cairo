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

#ifndef BRSHGDGT_H
#define BRSHGDGT_H

class CBrushEditDlg;
class BrushData;
class AttrBrushType;
#include "brshcomp.h"

class InformationBarOp;

class CBrushGadget
{
	private:
		InformationBarOp*	pOwningBar_m;
		DialogOp*			pOwningDialog_m;	// owner of me (when located on a dialog)
		CGadgetID			GadgetID_m;
		CGadgetID			InfobarGadgetID_m;	// owner of dialog
		UINT32				BubbleID_m;
		UINT32				StatusID_m;

		CBrushEditDlg*		pDialog_m;			// my linked dialog

		BOOL				DisableTimeStampingInDlg;
		BOOL				EditingBrushDefinition;

	
	public:
		CBrushGadget ();
		~CBrushGadget ();

		void		LinkControlButton (InformationBarOp* pOwner,
									   CGadgetID GadgetID, UINT32 BubbleID, UINT32 StatusID);

		void		Message (DialogMsg*);
		//void Message (DialogMsg*,  CProfileBiasGain const& );
		void		CloseDialog ();

		void		DialogHasOpened ();
		void		DialogHasClosed ();

		CGadgetID	GetGadgetID ()															const;
		void		GetDialogTitle ( String_256& DlgTitle )									const;
		
		void		HandleBrushButtonClick (BrushData* AppliedBrush, AttrBrushType* pBrush);
		void		HandleBrushButtonClick (BrushData* AppliedBrush, AttrBrushType* pBrush, AttrBrushType* pOrigBrush);
		void		HandleBrushButtonClick (BrushHandle Handle);

		// this allows the gadget to know abouts its linked dialog
		void SetCBrushEditDlg (CBrushEditDlg* pMyDlg) { pDialog_m = pMyDlg; }
		// allows us to query whether the gadgets linked dialog is open (i.e.  exists)
		BOOL IsDialogOpen () { if (pDialog_m != NULL) { return (TRUE); } else { return (FALSE); } }

		void		DisableTimeStamping () { DisableTimeStampingInDlg = TRUE; }
		BOOL		GetDisableTimeStamping () { return (DisableTimeStampingInDlg); }

		void		EnableEditingBrushDefinition () { EditingBrushDefinition = TRUE; }
		BOOL		GetEditingBrushDefinition () { return (EditingBrushDefinition); }

		// this allows us to reinit the linked dialog when the selection changes
		void ReInitialiseDialog (BrushData* pData);
		void SetBrushDialog(CBrushEditDlg* pDlg) { pDialog_m = pDlg;}
};

#endif
