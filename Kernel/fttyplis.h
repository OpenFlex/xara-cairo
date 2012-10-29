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


// This class has been implemented completely inline for speed reasons
// It is called from every WriteXXXX function in the CXaraFileRecord class...

#ifndef INC_FTTYPLIS
#define INC_FTTYPLIS


typedef enum
{
	FTT_BYTE = 1,
	FTT_UINT32,			// 2
	FTT_INT32,			// 3
	FTT_UINT16,			// 4
	FTT_INT16,			// 5
	FTT_FLOAT,			// 6
	FTT_DOUBLE,			// 7
	FTT_BINHEX,			// 8
	FTT_WCHAR,			// 9
	FTT_ASCII,			// A
	FTT_UNICODE,		// B
	FTT_COORD,			// C
	FTT_INTCOORD,		// D
	FTT_REFERENCE,		// E
	FTT_MAXTYPE			// F
} FTType;

// Now a couple of macros to make life easier in the write functions

#define ENTERWRITEFUNCTION(type)							\
	BOOL bFTTLUnlock = FALSE;								\
	if (m_pTypeList)										\
		bFTTLUnlock = m_pTypeList->AddToListAndLock(type);

#define LEAVEWRITEFUNCTION		\
	if (bFTTLUnlock)			\
		m_pTypeList->Unlock();

#define STORELENGTH(len)				\
	((bFTTLUnlock) ? (m_pTypeList->StoreLength(len)) : (ok))

/********************************************************************************************

>	class FTTypeList : public CCObject

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/07/97
	Purpose:	Object used by CXaraFileRecord for recording type information while writing

********************************************************************************************/

class FTTypeList : public CCObject
{
	// Give my name in memory dumps
	// The matching implement macro is in cxfrec.cpp
	CC_DECLARE_DYNAMIC(FTTypeList);

public:
	FTTypeList()
	{
		m_pArray = NULL;
		m_Used = 0;
		m_bLock = FALSE;
		m_Length = 0;
	};

	virtual ~FTTypeList()
	{
		if (m_pArray)
			CCFree(m_pArray);
	};

	DWORD GetCount(void) { return(m_Used); };

	BOOL StoreLength(DWORD len)
	{
		// Ensure 4 bytes of space (chances are this is the last thing to be written)
		if (!Enlarge(4))
			return(FALSE);

		DWORD* pLen = (DWORD*)(m_pArray + m_Used);
		*pLen = len;
		m_Used += 4;
		return(TRUE);
	};
	
	BOOL AddToListAndLock(FTType Type)
	{
		if (m_bLock)
			return(FALSE);

		// Add the type to the list

		if (m_Used == m_Length)
		{
			if (!Enlarge())
				return(FALSE);
		}

		// This must exist now
		m_pArray[m_Used] = Type;
		m_Used++;

		m_bLock = TRUE;
		return(TRUE);
	};

	void Unlock(void) { m_bLock = FALSE; };

	BYTE* GetBuffer(void) { return(m_pArray); };

protected:
	// Ensures at least Size entries available
	// FALSE if failed
	BOOL Enlarge(DWORD Size = 16)
	{
		if ((m_pArray == NULL) ||
			((m_Length - m_Used) < Size))
		{
			DWORD NewLength = m_Length + Size;
			BYTE* pNew = (BYTE*)CCRealloc(m_pArray, NewLength);

			if (pNew == NULL)
				return(FALSE);

			m_pArray = pNew;
			m_Length = NewLength;
		}
		return(TRUE);
	};

protected:
	DWORD m_Length;
	DWORD m_Used;
	BOOL m_bLock;
	BYTE* m_pArray;
};

#endif	// INC_FTTYPLIS
