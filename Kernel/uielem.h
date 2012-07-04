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

//

#ifndef INC_UIELEM
#define INC_UIELEM


/**************************************************************************************

>	class UserInterface : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/10/96

	Purpose:	Allows a user to edit a list of items

**************************************************************************************/
class UserInterface : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(UserInterface);
public:
	virtual ~UserInterface() { };
	virtual BOOL Display(DialogOp& Dialog) = 0;
	virtual BOOL Interact(DialogOp& Dialog) = 0;
	virtual void Hide() = 0;
};


class ListControl;
class TextControl;
/**************************************************************************************

>	class VisibleListItem : public UserInterface

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/10/96

	Purpose:	Allows a user to edit a list of items

**************************************************************************************/
class VisibleListItem : public UserInterface
{
	CC_DECLARE_MEMDUMP(VisibleListItem);

public:
	virtual ~VisibleListItem()	{}

// Overridden implementation does nothing
	virtual BOOL Display(DialogOp& Dialog)		{	return TRUE;	}
	virtual BOOL Interact(DialogOp& Dialog)		{	return TRUE;	}
	virtual void Hide()							{}

	virtual StringBase& GetText(StringBase& Description) const = 0;
	virtual BOOL operator > (const VisibleListItem& OtherItem) const;
};

inline BOOL VisibleListItem::operator > (const VisibleListItem& OtherItem) const
{
	String_64 ThisItemText;
	String_64 OtherItemText;

	return GetText(ThisItemText) > OtherItem.GetText(OtherItemText);
}



class VisibleListItemPtr;
/**************************************************************************************

>	class VisibleListIterator

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/10/96

	Purpose:	Returns entries in a visible list

	See Also:	VisibleList::Begin(), End()

**************************************************************************************/
class VisibleListIterator
{
public:
	VisibleListIterator& operator ++();
	VisibleListIterator& operator --();
	VisibleListItem& operator*();
	BOOL operator!=(const VisibleListIterator& Other);


	VisibleListIterator(List& Container, VisibleListItemPtr* const pPointer, 
						INT32* IndexesOfItemsToReturn = NULL);
	~VisibleListIterator();

	VisibleListIterator(const VisibleListIterator& Other);
	const VisibleListIterator& operator=(const VisibleListIterator& Other);
private:
	VisibleListItemPtr*	m_VisibleListItemPtr;
	List&				m_Container;
	INT32*				m_IndexesOfItemsToReturn;
	UINT32				m_IndexInIndex;
};

/**************************************************************************************

>	class VisibleList : public UserInterface

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/10/96

	Purpose:	Allows a user to edit a list of items

**************************************************************************************/
class VisibleList : public UserInterface, public Notifier
{
	CC_DECLARE_MEMDUMP(VisibleList);

public:
	VisibleList() : m_pUIElement(NULL)	{}
	virtual ~VisibleList();

// Overridden implementations...do nothing for now (use non-virtuals)
	virtual BOOL Display(DialogOp& Dialog);
	virtual BOOL Interact(DialogOp& Dialog);
	virtual void Hide();

	virtual BOOL Display(ListControl& Control);
	virtual BOOL Interact(ListControl& Control);

// Visible List specific
	virtual BOOL InsertEntry(VisibleListItem& EntryToInsert);
	virtual BOOL DeleteSelectedEntries();
	virtual BOOL DeleteAllEntries();

	virtual UINT32 GetNumberOfEntries() const;
	virtual UINT32 GetNumberOfSelectedEntries() const;
	virtual VisibleListItem* GetFirstSelectedEntry() const;
	virtual void RemoveSelection();

	virtual VisibleListIterator Begin();
	virtual const VisibleListIterator& End() const;
	virtual VisibleListIterator BeginOfEnd();
	
	virtual VisibleListIterator SelectionBegin();

protected:
// Implementation
	virtual VisibleListItem& GetEntryAt(UINT32 Index);
	virtual BOOL DeleteEntryAtIndex(UINT32 Index);

	List&			GetContainer();

private:
	ListControl*	m_pUIElement;
	List			m_Container;
};


/**************************************************************************************

>	class EditableText : public UserInterface

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/10/96

	Purpose:	Allows a user to edit a list of items

**************************************************************************************/
class EditableText : public UserInterface, public Notifier
{
public: // overrides of User_interface functions
	EditableText(const StringBase& TextString = NullString);

	virtual ~EditableText();
	EditableText(const EditableText& Other);
	virtual	const EditableText& operator=(const EditableText& Other);

	virtual	const EditableText& operator=(const StringBase& NewText );
	operator const StringBase&();

// Overridden implementation does nothing...slightly bodgy this
	virtual BOOL Display(DialogOp& Dialog)		{	return TRUE;	}
	virtual BOOL Interact(DialogOp& Dialog)		{	return TRUE;	}
	virtual BOOL Display(TextControl& Control);
	virtual void Hide();

private:
	// Implementation
	class Observer : public Notifiable
	{
		EditableText* m_pTheTextObject;
	public:
		Observer( EditableText* const pContainer ): m_pTheTextObject(pContainer){}
		void Notify( Notifier* const pSender );
	}
	m_Watcher;

	friend void Observer::Notify( Notifier* const pSender );

	TextControl*	m_pUIElement;
	String_256		m_String;


};



/**************************************************************************************

>	class VisibleLabel : public UserInterface, public Notifier

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/10/96

	Purpose:	Allows a user to edit a list of items

**************************************************************************************/
class VisibleLabel : public UserInterface, public Notifier
{
public: // overrides of User_interface functions
	VisibleLabel(const StringBase& TextString = NullString);

	virtual ~VisibleLabel();

	virtual	const VisibleLabel& operator=(const StringBase& NewText );
	operator const StringBase&() const;

// Overridden implementation does nothing...slightly bodgy this
	virtual BOOL Display(DialogOp& Dialog);
	virtual BOOL Interact(DialogOp& Dialog);
	virtual void Hide();

private:
	// Implementation
	class Observer : public Notifiable
	{
		VisibleLabel* m_pTheTextObject;
	public:
		Observer( VisibleLabel* const pContainer ): m_pTheTextObject(pContainer){}
		void Notify( Notifier* const pSender );
	}
	m_Watcher;

	friend void Observer::Notify( Notifier* const pSender );

	StaticTextControl*	m_pUIElement;
	String_256			m_String;
};


#endif	// INC_UIELEM
