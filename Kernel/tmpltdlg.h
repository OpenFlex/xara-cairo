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


// Attribute Template Dialog
#ifndef INC_TMPLTDLG
#define INC_TMPLTDLG

#define OPTOKEN_TEMPLATEDLG		_T("TemplateDlg")

class OpDescriptor;
class Msg;
class WizOps;
class WizOpStyles;
class Style;
class ListControl;
class TextControl;
class Button;
class StaticTextControl;
class AvailablePropertiesList;
class UsedPropertiesList;
class RenderableNodeEnumerator;
class BaseDocument;

/********************************************************************************************

>	class TemplateDialog : public DialogOp


	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com> (from assorted dialog classes)
	Created:	09/06/97

	Purpose:	Allows intelligent users to make attributes changeable via templates.

********************************************************************************************/
PORTNOTE("dialog","Removed TemplateDialog - UI class")
#ifndef EXCLUDE_FROM_XARALX
class TemplateDialog : public DialogOp
{
	CC_DECLARE_DYNCREATE(TemplateDialog);

	//Constructors, destructors and initialiser
public:
	// Metaclass members
	static BOOL		Init();
	static OpState	GetState(String_256*, OpDescriptor*);

public:
	TemplateDialog();
	virtual ~TemplateDialog();

	// Creating the dialog
public:
	// Overridden 
	virtual void Do(OpDescriptor*);

	TextControl& GetKeyControl() const;
	TextControl& GetValueControl() const;
	StaticTextControl& GetParamHintControl() const;

	void SetUserCanModifyQuestion(BOOL TheyAre);

protected:
	// Overridden 
	virtual	MsgResult Message(Msg* Message);

	virtual void OnCreate();
	virtual void OnTextChange();
	virtual void OnParamChange();
	virtual void OnAddButtonClicked();
	virtual void OnRemoveButtonClicked();
	virtual void OnRemoveAllButtonClicked();
	virtual void OnUsedListHighlightChanged();
	virtual void OnAvailableListHighlightChanged();
	virtual void OnAvailableListDoubleClicked();
	virtual void OnSelectionChange();
	virtual void OnMakeStyleClicked();
	virtual void OnApplyClicked();

	void OnAvailableSelectionChange();
	void OnUsedSelectionChange();

protected:
	// Implementation
	void SetDialogInitialState(BaseDocument* const pSelectedDocument);
	void InitializeControls();
	void ReflectControlAvailability();
	void ShowInitialControlAvailablity();

	RenderableNodeEnumerator* CreateEnumerator() const;
	Style* AddNewStyle(const Style& NewStyle) const;

	BOOL BuildUsedPropertiesList();
	BOOL BuildAvailablePropertiesList(BaseDocument* const pSelectedDocument);
	void MakePropertyUsed();
	void RemoveUsedProperty();
	void RemoveAllUsedProperties();
	BOOL CreateGadgets();

protected:
	void ApplyUsedAttributes();

protected:
	// Data Member Access
	AvailablePropertiesList&	GetAvailableProperties();
	UsedPropertiesList&			GetUsedProperties();
	BOOL UserCanModifyQuestion() const;

	static BOOL ShowCustomProperty();

	WizOps& GetWizOps() const;
	WizOpStyles* GetStyles() const;

public:
	static const CDlgResID	s_IDD;
	static const CDlgMode	s_Mode;

private:
//	Should generate these dynamically...
	ListControl*		m_pUsedListGadget;
	ListControl*		m_pAvailableListGadget;
	TextControl*		m_pQuestionGadget;
	StaticTextControl*	m_pParamHintGadget;
	TextControl*		m_pParamGadget;
	Button*				m_pAddButton;
	Button*				m_pRemoveButton;
	Button*				m_pRemoveAllButton;
	Button*				m_pApplyButton;
	Button*				m_pMakeStyleButton;

	AvailablePropertiesList*	m_pAvailableProperties;
	UsedPropertiesList*			m_pUsedProperties;

// yuck! a state variable telling us we may want to enable the apply button if the text changes
	BOOL				m_UserCanModifyQuestion;

// preferences
	static String_32	s_PreferenceSection;	// all preferences go here
	static const UINT32	s_NumberOfPreferences;

	static String_16	s_ShowCustom;			// preference name
	static BOOL			s_ShowCustomProperty;	// ...and the var (ooh nasty no serialization)
};
#endif
#endif //INC_TMPLTDLG

