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
	$Header: /Camelot/kernel/ngdialog.h 5     15/03/00 13:52 Justinf $
	Attribute gallery dialog operations
*/

#ifndef NGDIALOG_H
#define NGDIALOG_H

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]


/********************************************************************************************
>	class CCAPI BaseNameObjectsDlg : public DialogOp
	class CCAPI NameObjectsDlg : public BaseNameObjectsDlg
	class CCAPI RenameObjectsDlg : public BaseNameObjectsDlg

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/6/99
	Purpose:	Base class UI dialogs which create and rename sets of objects in 
				the Attribute gallery.
	SeeAlso:	DialogOp
********************************************************************************************/

class CCAPI BaseNameObjectsDlg : public DialogOp
{         
protected:
	// Creation & destruction.
	BaseNameObjectsDlg(CDlgResID idRes, CDlgMode nMode);

	// Description of what is to be (re)named.
	virtual StringBase* GetDescription(StringBase* pstrDesc) = 0;

	// A suggestion for the (re)name.
	virtual StringBase* GetSuggestion(StringBase* pstrDesc) = 0;

	// Returns zero if valid, the ID of an explanative error string if not.
	virtual UINT32 IsValid(const StringBase& strName);

	// This is called when the user enters a valid name and clicks the OK button.
	virtual BOOL DoCommit(const StringBase& strName) = 0;

	// Event handlers.
	virtual void Do(OpDescriptor*);
	virtual MsgResult Message(Msg* pMessage);

private:
	// Helper that sets the text in the static and edit controls, the initial focus etc.
	void InitGadgetText();

	// Data.
	String_256 m_strSuggest;
};



#define OPTOKEN_NAME_OBJECTS_DLG			_T("NameObjectsDlg")

class CCAPI NameObjectsDlg : public BaseNameObjectsDlg
{	
	CC_DECLARE_DYNCREATE(NameObjectsDlg);
	static BOOL m_fModeless;

public:
	static BOOL Init();

protected:
	NameObjectsDlg();

	virtual StringBase* GetDescription(StringBase* pstrDesc);
	virtual StringBase* GetSuggestion(StringBase* pstrDesc);
	virtual UINT32 IsValid(const StringBase& strName);
	virtual BOOL DoCommit(const StringBase& strName);
};



#define OPTOKEN_RENAME_OBJECTS_DLG			_T("RenameObjectsDlg")

class CCAPI RenameObjectsDlg : public BaseNameObjectsDlg
{
	CC_DECLARE_DYNCREATE(RenameObjectsDlg);

protected:
	RenameObjectsDlg();

	virtual StringBase* GetDescription(StringBase* pstrDesc);
	virtual StringBase* GetSuggestion(StringBase* pstrDesc);
	virtual BOOL DoCommit(const StringBase& strName);
};



/********************************************************************************************
>	class CCAPI OpNameGalleryPropIndexDesc : public OpDescriptor

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/2/99
	Purpose:	Manages the Name gallery's property index combo-box.
	SeeAlso:	NameGallery; OpDescriptor
********************************************************************************************/

#define OPTOKEN_NAME_GALLERY_PROP_INDEX		_T("NameGalleryPropertyIndex")

class CCAPI OpNameGalleryPropIndexDesc : public OpDescriptor
{
public:
	// Creation & destruction.
	OpNameGalleryPropIndexDesc();

private:
	// Event handlers.
	virtual void OnControlCreate(OpDescControlCreateMsg* pCreateMsg);
	virtual void OnSelectionChange(OpDescControlMsg* pSelChangedMsg, List* pGadgetList);

	// Helpers.
	void UpdateGadgets();

	CC_DECLARE_DYNCREATE(OpNameGalleryPropIndexDesc);
};




/********************************************************************************************
>	class CCAPI OpDisplayNameGallery: public Operation

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/5/99
	Purpose:	Displays the Name gallery.  This op can be attached to a menu, button
				or keypress.
	SeeAlso:	NameGallery
********************************************************************************************/

#define OPTOKEN_DISPLAY_NAME_GALLERY		_T("DisplayNameGallery")

class CCAPI OpDisplayNameGallery: public Operation
{         
	CC_DECLARE_DYNCREATE(OpDisplayNameGallery);

public:
	static BOOL	Init();				
	static OpState GetState(String_256*, OpDescriptor*);		

protected:
    virtual void Do(OpDescriptor*);
	static SuperGallery* FindGallery();
};  

#endif	/* !NGDIALOG_H */
