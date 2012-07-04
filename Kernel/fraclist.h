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


// kernel class to encompass the fractal cache

#ifndef	INC_FRACLIST
#define	INC_FRACLIST

#include "list.h"

class FillGeometryAttribute;
class Document;
class KernelBitmap;

/***********************************************************************************************

>	class CachedFractal : public ListItem

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Purpose:	A Fractal that has been cached.
	SeeAlso:	-

***********************************************************************************************/

class CachedFractal : public ListItem
{
CC_DECLARE_MEMDUMP(CachedFractal)

public:
	CachedFractal();
	~CachedFractal();

	virtual INT32 operator==(const FillGeometryAttribute& Attrib);

	void SetCachedFractal(FillGeometryAttribute*);
	FillGeometryAttribute* GetCachedFractal();

	void IncUsageCount();
	void DecUsageCount();

	INT32 GetUsageCount() { return UsageCount; }

	INT32 GetSize();

	KernelBitmap* GetBitmap();

	void MakeFakeFractal() { m_bIsFake = TRUE; }
	BOOL IsFakeFractal() { return m_bIsFake; }

protected:
	FillGeometryAttribute* Fractal;
	INT32 UsageCount;

	BOOL m_bIsFake;
};


/***********************************************************************************************

	class EnumFractalData

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Purpose:	A class to compile information about the global fractal list.
	SeeAlso:	GlobalFractalList::GetDocumentFractalData

***********************************************************************************************/

class EnumFractalData
{
	public:
		EnumFractalData() { Count=Size=0; }
	public:	
		INT32	Count;
		INT32	Size;
} ;


/***********************************************************************************************

>	class GlobalFractalList : public List

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>/Mike
	Purpose:	A list of all the Fractals available in the application
	SeeAlso:	-

***********************************************************************************************/

class GlobalFractalList : public List
{
	CC_DECLARE_MEMDUMP(GlobalFractalList)

	public:
		 GlobalFractalList();
		~GlobalFractalList();

		static BOOL Init();
		static BOOL DeInit();

	public:
		BOOL AddFractal(FillGeometryAttribute*);
		BOOL RemoveFractal(FillGeometryAttribute*);
		void GetDocumentFractalData(Document* pDoc, EnumFractalData* pData);

		CachedFractal* CheckFractalBitmap(FillGeometryAttribute*);

	private:
		INT32 GetFractalCacheCount();
		INT32 GetFractalCacheSize();
		void Destroy();
};

#endif
