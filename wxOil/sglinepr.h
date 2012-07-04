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

// SGLinePr.h - the LineGallery property dialog classes

#ifndef INC_SGLINEPR
#define INC_SGLINEPR

//#include "bars.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "dlgtypes.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "sgallery.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "strkcomp.h" // for strokehandle

/***********************************************************************************************

>	class SGalleryLinePropertiesDlg : public DialogOp

	Author:		Richard_Millican (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/3/97

	Purpose:	A dialogue box allowing the user to set the line/stroke properties for the
				line gallery

	SeeAlso:	SuperGallery; SGalleryOptionsDlg::InvokeDialog

***********************************************************************************************/

#define OPTOKEN_SGLINEPROPERTIESDLG _T("GalleryLinePropertiesDlg")


class SGalleryLinePropertiesDlg : public DialogOp
{
	CC_DECLARE_DYNCREATE(SGalleryLinePropertiesDlg)

public:
	SGalleryLinePropertiesDlg();
	~SGalleryLinePropertiesDlg();

	MsgResult Message(Msg *Message);

	void Do(OpDescriptor*);
	void DoWithParam(OpDescriptor*, OpParam *Param);

	static BOOL Init();
	BOOL Create();
	static OpState GetState(String_256*, OpDescriptor*);

	static const UINT32 IDD;
	static const CDlgMode Mode;

	static void InvokeDialog(SuperGallery *Parent);
		// Call this method to create and display a gallery options dialogue

	void SetNameEditField(String_256 *pString);
	void GetNameEditField(String_256 *pString);
		// Sets and gets the name text from the dialog

	void SetRepeatingBool(BOOL Repeating);
	BOOL GetRepeatingBool();
		// Sets and gets the repeating button state from the dialog

	void SetRepeatingLong(INT32 Repeats);
	INT32 GetRepeatingLong();
		// Sets and gets the fixed number of repeats values

	void SetSliderMinMax(INT32 Min, INT32 Max);
	void SetSliderPos(INT32 Value);
		// Sets the slider's position and min/max values

	void GreyRepeats(BOOL Grey);
		// Grey's / un-grey's the repeat section

	void SetOverrideFillBool(BOOL OverrideFill);
	BOOL GetOverrideFillBool();
		// Sets and gets the override fill button state from the dialog

	void SetOverrideTransBool(BOOL OverrideTrans);
	BOOL GetOverrideTransBool();
		// Sets and gets the override fill button state from the dialog


	void RedrawStrokesInDocuments(StrokeHandle Handle);


protected:
	virtual void RedrawDiagram(ReDrawInfoType* ExtraInfo);

public:
	SGDisplayNode *m_pItem;

protected:
	SuperGallery *ParentGallery;

	void InitValues(void);
	void SetControls(void);

	void Commit(BOOL RedrawDocument = TRUE);
};

#endif
