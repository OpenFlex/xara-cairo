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


#ifndef INC_VISIATTR
#define INC_VISIATTR

class NodeAttribute;
/**************************************************************************************

>	class VisibleAttribute : public VisibleListItem

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/10/96

	Purpose:	Provides a user editable attribute (of sorts)

**************************************************************************************/
class VisibleAttribute : public UserInterface
{
	CC_DECLARE_MEMDUMP(VisibleAttribute)
public:
	virtual BOOL Interact(DialogOp& Dialog)			{	return TRUE;	}	// should be in UserInterface
	virtual StringBase& GetText(StringBase& Description) const = 0;
	virtual NodeAttribute*	CreateNewAttribute() = 0;

	BOOL IsNew() const			{	return m_IsNew;		}
	void MarkAsUsed()			{	m_IsNew = FALSE;	}

protected:
	VisibleAttribute() : m_IsNew(TRUE)	{}

private:
	BOOL				m_IsNew;
};


/**************************************************************************************

>	class VisibleUserAttribute : public VisibleAttribute

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/10/96

	Purpose:	Provides a user editable user attribute

**************************************************************************************/
class VisibleUserAttribute : public VisibleAttribute
{
	CC_DECLARE_MEMDUMP(VisibleUserAttribute)
public:
	VisibleUserAttribute(const StringBase& Key, const StringBase& Value);

//	Pure implementations
	virtual BOOL Display(DialogOp& Dialog);
	virtual BOOL Interact(DialogOp& Dialog);
	virtual void Hide();
	virtual StringBase& GetText(StringBase& Description) const;


// Data Member Access
	void SetLongKey(const StringBase& NewKey);
	void SetValue(const StringBase& NewValue)			{	m_Value = NewValue;	}

	const StringBase& GetKey();
	const StringBase& GetLongKey();
	const StringBase& GetValue();

	virtual NodeAttribute*	CreateNewAttribute();

private:
	String_64			m_Key;
	EditableText		m_LongKey;
	EditableText		m_Value;
};


class WizOp;
/**************************************************************************************

>	class VisibleTemplateAttribute : public VisibleUserAttribute

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/10/96

	Purpose:	Provides a user editable template attribute

**************************************************************************************/
class VisibleTemplateAttribute : public VisibleUserAttribute
{
	CC_DECLARE_MEMDUMP(VisibleTemplateAttribute)
public:
	VisibleTemplateAttribute(	const WizOp& Handler,
								const StringBase& Question = NullString, 
								const StringBase& Param = NullString);

	virtual StringBase& GetText(StringBase& Description) const;
	virtual BOOL Display(DialogOp& Dialog);
	virtual BOOL Interact(DialogOp& Dialog);
	virtual void Hide();

	virtual NodeAttribute*	CreateNewAttribute();

protected:
// Data Member Access
	const WizOp&	GetWizOp();
	VisibleLabel&	GetParamHint();
	void			SetParamHint(const StringBase& HintToShow);
	
private:
	const WizOp&	m_Handler;
	VisibleLabel	m_ParamHint;
};

class WizOpStyle;
/**************************************************************************************

>	class VisibleStyleReference : public VisibleAttribute

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/10/96

	Purpose:	Provides a user editable style reference

**************************************************************************************/
class VisibleStyleReference : public VisibleAttribute
{
	CC_DECLARE_MEMDUMP(VisibleStyleReference)

public:
	VisibleStyleReference(const WizOpStyle& Style);


	virtual BOOL Display(DialogOp& Dialog);
	virtual BOOL Interact(DialogOp& Dialog);
	virtual void Hide();

	virtual StringBase& GetText(StringBase& Description) const;
	virtual NodeAttribute*	CreateNewAttribute();

	VisibleLabel&	GetParamHintLabel();
	void			SetParamHintString(const StringBase& HintToShow);

	EditableText&	GetParamText();
	void			SetParamText(const StringBase& ParamToShow);

	const WizOpStyle&	GetStyle();

private:
	const WizOpStyle&	m_Style;
	EditableText		m_Question;
	VisibleLabel		m_ParamHintLabel;
	EditableText		m_Param;
};



#endif // INC_VISIATTR
