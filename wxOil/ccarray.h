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

#ifndef INC_CCARRAY
#define INC_CCARRAY

/**************************************************************************************

>	template < class TYPE, class ARG_TYPE >
>	class CCArray : public CArray <TYPE, ARG_TYPE>

	Author:
	Created:
	Purpose:

**************************************************************************************/
template < typename TYPE, typename ARG_TYPE >
class CCArray
{
public:
	typedef std::vector< TYPE >					CArrayClass;
	typedef typename CArrayClass::iterator		iterator;

protected:
	CArrayClass			m_Array;

public:
	BOOL	SetSize( INT32 nNewSize, INT32 nGrowBy = -1 );
	BOOL	SetAtGrow(INT32 nIndex, ARG_TYPE newElement);
	size_t	Add(ARG_TYPE newElement);

	TYPE &operator[]( INT32 nIndex );
	const TYPE &operator[]( INT32 nIndex ) const;
};


template<class TYPE, class ARG_TYPE>
BOOL CCArray<TYPE, ARG_TYPE>::SetSize(INT32 nNewSize, INT32 nGrowBy)
{
//	TRY
	{
		nNewSize = ( ( nNewSize + ( nGrowBy - 1 ) ) / nGrowBy ) * nGrowBy;
		m_Array.resize( nNewSize );
	}
/*	CATCH_ALL(e)
	{
		return FALSE;
	}
	END_CATCH_ALL */

	return TRUE;
}


template<class TYPE, class ARG_TYPE>
BOOL CCArray<TYPE, ARG_TYPE>::SetAtGrow(INT32 nIndex, ARG_TYPE newElement)
{
//	TRY
	{
		m_Array.insert( m_Array.begin() + nIndex, newElement );
	}
/*	CATCH_ALL(e)
	{
		return FALSE;
	}
	END_CATCH_ALL */

	return TRUE;
}


template<class TYPE, class ARG_TYPE>
inline size_t CCArray<TYPE, ARG_TYPE>::Add(ARG_TYPE newElement)
{
	m_Array.push_back( newElement );
	return m_Array.size();
}

template<class TYPE, class ARG_TYPE>
inline TYPE &CCArray<TYPE, ARG_TYPE>::operator[]( INT32 nIndex )
{
	return *( m_Array.begin() + nIndex );
}

template<class TYPE, class ARG_TYPE>
inline const TYPE &CCArray<TYPE, ARG_TYPE>::operator[]( INT32 nIndex ) const
{
	return *( m_Array.begin() + nIndex );
}

#endif	// INC_CCARRAY
