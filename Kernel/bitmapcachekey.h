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


#if !defined(AFX_BITMAPCACHEKEY_H__FEB76A5F_93CC_4875_B3EF_B7394B123ACD__INCLUDED_)
#define AFX_BITMAPCACHEKEY_H__FEB76A5F_93CC_4875_B3EF_B7394B123ACD__INCLUDED_

class CBitmapCacheKey  
{
	friend class CBitmapCache;

public:
	CBitmapCacheKey();
	CBitmapCacheKey(LPVOID pNewOwner, double dNewPixelWidth, UINT32 nNewOption = 0);
	CBitmapCacheKey(const CBitmapCacheKey& key);
	virtual ~CBitmapCacheKey();

// Methods
public:
	BOOL IsValid() const;
	UINT32 Hash() const;
	void SetOwner(LPVOID pNewOwner) {pOwner = pNewOwner;}
	double GetPixelWidth() const {return dPixelWidth;}

// Operators
	bool operator==(const CBitmapCacheKey& key) const;

private:
	LPVOID		pOwner;				// Pointer to owner object
	double		dPixelWidth;		// Resolution owner is looking for
	UINT32		nOption;			// Option owner is looking for (can store/retrieve several bitmaps at same resolution with different "options")

};

#endif // !defined(AFX_BITMAPCACHEKEY_H__FEB76A5F_93CC_4875_B3EF_B7394B123ACD__INCLUDED_)
