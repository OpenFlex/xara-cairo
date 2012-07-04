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


#include "camtypes.h"

//#include "bitmapcachekey.h" - in camtypes.h [AUTOMATICALLY REMOVED]

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBitmapCacheKey::CBitmapCacheKey()
{
	memset(&pOwner, 0, sizeof(CBitmapCacheKey)-((LPBYTE)&pOwner-(LPBYTE)this));
	pOwner = NULL;
	dPixelWidth = 0;
	nOption = 0;
}

CBitmapCacheKey::CBitmapCacheKey(LPVOID pNewOwner, double dNewPixelWidth, UINT32 nNewOption)
{
	memset(&pOwner, 0, sizeof(CBitmapCacheKey)-((LPBYTE)&pOwner-(LPBYTE)this));
	pOwner = pNewOwner;
	dPixelWidth = dNewPixelWidth;
	nOption = nNewOption;
}

// Copy constructor
// Required by CTypedPtrMap
CBitmapCacheKey::CBitmapCacheKey(const CBitmapCacheKey& key)
{
	memset(&pOwner, 0, sizeof(CBitmapCacheKey)-((LPBYTE)&pOwner-(LPBYTE)this));
	pOwner = key.pOwner;
	dPixelWidth = key.dPixelWidth;
	nOption = key.nOption;
}

CBitmapCacheKey::~CBitmapCacheKey()
{

}




/********************************************************************************************

>	CBitmapCacheKey::operator==()
	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/06/2004
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if this key is exactly the same the the specified key
	Purpose:	Test whether this object has been constructed correctly
				Required by CTypedPtrMap
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
bool CBitmapCacheKey::operator==(const CBitmapCacheKey& key) const
{
	return (pOwner == key.pOwner &&
			dPixelWidth == key.dPixelWidth &&
			nOption == key.nOption
			);
}




/********************************************************************************************

>	BOOL CBitmapCacheKey::IsValid() const
	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/06/2004
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if this key is valid
				FALSE otherwise
	Purpose:	Test whether this object has been constructed correctly
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
BOOL CBitmapCacheKey::IsValid() const
{
	return (pOwner!=NULL && dPixelWidth!=0);
}




/********************************************************************************************

>	UINT32 CBitmapCacheKey::Hash() const
	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/06/2004
	Inputs:		-
	Outputs:	-
	Returns:	UINT32 containing hashed value of all the bytes in this object
	Purpose:	Compute a Hash value to allow this object to be used as the key into
				a Hash Table
	Errors:		-
	SeeAlso:	-

********************************************************************************************/
UINT32 CBitmapCacheKey::Hash() const
{
	UINT32 nHash = 0;
	//LPBYTE pThis = (LPBYTE)this;
	LPBYTE pThis = (LPBYTE)&pOwner;
	// Can't use sizeof class because that includes alignment bytes which contain random values
	//const INT32 bytesize = sizeof(CBitmapCacheKey);
	const size_t bytesize = sizeof(CBitmapCacheKey)-((LPBYTE)&pOwner-(LPBYTE)this);

	for(unsigned i=0; i<bytesize; i++)
	{
		nHash = (nHash<<5)+nHash + *pThis++;
	}

	return nHash;
}

