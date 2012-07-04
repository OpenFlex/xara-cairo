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

#ifndef INC_STACK_TEMPLATE
#define INC_STACK_TEMPLATE

// We want better memory tracking.
// Removed from this file because "new" isn't used in this class definition, and it messes up the
// CC_IMPLEMENT_DYNCREATE and CC_IMPLEMENT_DYNAMIC macros for other classes which include
// this header (NB now included in grndrgn.h so affects many classes!!)
#define new CAM_DEBUG_NEW

#include "genlist.h"

/**************************************************************************************

>	template <class Object>
>	class StackT

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com> (from STL)
	Created:	20/12/96
	Purpose:	Generic StackT

**************************************************************************************/
template <class Object>
class StackT
{
//	friend BOOL operator==(const StackT<Object>& x, const StackT<Object>& y);
//	friend BOOL operator<(const StackT<Object>& x, const StackT<Object>& y);

public:
	typedef typename ListT<Object>::ValueType		ValueType;
	typedef typename ListT<Object>::SizeType		SizeType;

protected:
	ListT<Object> m_Container;

public:
	BOOL		Empty() const		{ return m_Container.Empty(); }
	SizeType	Size() const		{ return m_Container.Size(); }

	ValueType&			Top()		{ return m_Container.Back(); }
	const ValueType&	Top() const	{ return m_Container.Back(); }
	
	ValueType&			Bottom()		{ return m_Container.Front(); }
	const ValueType&	Bottom() const	{ return m_Container.Front(); }
	
	BOOL Push(const ValueType& x)	{ return m_Container.PushBack(x); }
	void Pop()						{ m_Container.PopBack();	}

	ListT<Object>*			GetListT()			{ return &m_Container; }
	const ListT<Object>*	GetListT() const	{ return &m_Container; }
};

template <class Object>
BOOL operator==(const StackT<Object>& x, const StackT<Object>& y) {
	return x.c == y.c;
}

template <class Object>
BOOL operator<(const StackT<Object>& x, const StackT<Object>& y) {
	return x.c < y.c;
}


#endif	// INC_STACK_TEMPLATE


