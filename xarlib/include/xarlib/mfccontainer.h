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


// Classes which emulate MFC containers using STL

#ifndef INC_MFC_CONTAINER
#define INC_MFC_CONTAINER

template< class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, typename BaseClass = std::map<KEY, VALUE> >
class CMap
{
protected:
	BaseClass			m_TheMap;

public:
	typedef typename BaseClass::iterator		iterator;
	typedef typename BaseClass::const_iterator	const_iterator;

	CMap()
	{
	}

	CMap( INT32 )
	{
	}

// Attributes
	// number of elements
	PINT32 GetCount() const	{ return m_TheMap.size(); }
	PINT32 GetSize() const		{ return m_TheMap.size(); }
	BOOL IsEmpty() const		{ return m_TheMap.empty(); }

// Lookup
	BOOL Lookup( ARG_KEY key, VALUE& rValue ) const
	{
		const_iterator	iter = m_TheMap.find( key );
		if( m_TheMap.end() == iter )
			return FALSE;

		rValue = iter->second;
		return TRUE;
	}

// Operations
	// Lookup and add if not there
	VALUE &operator[]( ARG_KEY key )
	{
		return m_TheMap[key];
	}

	// add a new (key, value) pair
	void SetAt(ARG_KEY key, ARG_VALUE newValue)
	{
		m_TheMap[key] = newValue;
	}

	// removing existing (key, ?) pair
	BOOL RemoveKey( ARG_KEY key )
	{
		
		const_iterator	iter = m_TheMap.find( key );
		if( m_TheMap.end() == iter )
			return FALSE;
		m_TheMap.erase( key );
		return TRUE;
	}
	void RemoveAll()
	{
		m_TheMap.clear();
	}

	// iterating all (key, value) pairs
	const_iterator GetStartPosition() const
	{
		return m_TheMap.begin();
	}

	void GetNextAssoc( const_iterator &rNextPosition, KEY &rKey, VALUE &rValue ) const
	{
		if( m_TheMap.end() == rNextPosition || NULL == rNextPosition )
		{
			rNextPosition = NULL;
			return;
		}

		rKey	= rNextPosition->first;
		rValue	= rNextPosition->second;
		++rNextPosition;
	}
};

#endif//INC_MFC_CONTAINER
