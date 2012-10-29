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

// Imagemap

#ifndef IMAGEMAPCLICKABLEAREA
#define IMAGEMAPCLICKABLEAREA

#include "overitem.h"
#include "flatfact.h"

class CCLexFile;
class ImagemapFilter;

/********************************************************************************************

>	class ImagemapClickableArea : public OverrideListItem

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Purpose:	This class represents a clickable area.

				It's a pure virtual class, so use one of the three
				derived classes (below) instead.

********************************************************************************************/

class ImagemapClickableArea : public OverrideListItem
{
	CC_DECLARE_DYNAMIC(ImagemapClickableArea)

	//Constructors
	ImagemapClickableArea();
	ImagemapClickableArea(TCHAR* pcURL, TCHAR* pcFrame);

	//Destructor, copy constructor and assignment operator
	~ImagemapClickableArea();
	ImagemapClickableArea(const ImagemapClickableArea& icaCopy);
	ImagemapClickableArea& operator=(const ImagemapClickableArea& icpCopy);

	//Writing out the clickable area
public:
	virtual INT32 Write(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)=0;
	
	INT32 WriteURLAndFrame(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	

	//Information functions
public:
	virtual DocRect GetBoundingRect()=0;

	BOOL IsAClickableArea()
	{
		return TRUE;
	}

	//Toolkit functions
public:
	ImagemapFilter* GetImagemapFilter();
	
	//Member variables
	TCHAR* m_pcURL;
	TCHAR* m_pcFrame;
};

/********************************************************************************************

>	class ImagemapClickableRectangle : public ImagemapClickableArea

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Purpose:	This class represents a clickable rectangle.

********************************************************************************************/

class ImagemapClickableRectangle : public ImagemapClickableArea
{
	CC_DECLARE_DYNAMIC(ImagemapClickableRectangle)

	//Constructors
public:
	ImagemapClickableRectangle();

	ImagemapClickableRectangle(DocRect rectToStore, TCHAR* pcURL=NULL, TCHAR* pcFrame=NULL);
	
	//Writing out the clickable area
public:
	INT32 Write(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	

	//Override functions
public:
	BOOL OverrideFromBelow(OverrideListItem* picaOther);

	BOOL OverrideFromAbove(OverrideListItem* picaOther)
	{
		return OverrideFromBelow(picaOther);
	}

	//Information function
public:
	DocRect GetBoundingRect()
	{
		return m_rect;
	}
	 
	//Member variable:
public:
	DocRect m_rect;

};

/********************************************************************************************

>	class ImagemapClickableCircle : public ImagemapClickableArea

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Purpose:	This class represents a clickable circle.

********************************************************************************************/

class ImagemapClickableCircle : public ImagemapClickableArea
{
	CC_DECLARE_DYNAMIC(ImagemapClickableCircle)

	//Constructors
public:
	ImagemapClickableCircle();

	ImagemapClickableCircle(Path* pthToCopy, TCHAR* pcURL=NULL, TCHAR* pcFrame=NULL);
	
	//Writing out the clickable area
public:
	INT32 Write(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	

	//Information function
public:
	DocRect GetBoundingRect();
	
	//Member variable:
public:
	DocCoord m_dcCentre;
	INT32 m_lRadius;
	
};

/********************************************************************************************

>	class ImagemapClickablePolygon : public ImagemapClickableArea

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Purpose:	This class represents a clickable n-sided polygon.

********************************************************************************************/

class ImagemapClickablePolygon : public ImagemapClickableArea
{
	CC_DECLARE_DYNAMIC(ImagemapClickablePolygon)

	//Constructors
public:
	ImagemapClickablePolygon();
	
	ImagemapClickablePolygon(Path* pthToCopy, TCHAR* pcURL=NULL, TCHAR* pcFrame=NULL);

	//Destructor, copy constructor and assignment operator
public:
	~ImagemapClickablePolygon();
	ImagemapClickablePolygon(const ImagemapClickablePolygon& icpCopy);
	ImagemapClickablePolygon& operator=(const ImagemapClickablePolygon& icpCopy);
	
	//Writing out the clickable area
public:
	INT32 Write(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	

	//Information function
public:
	DocRect GetBoundingRect()
	{
		if (m_ppth)
			return m_ppth->GetBoundingRect();
		else
			return DocRect(0,0,0,0);
	}

	//Member variable
public:
	Path* m_ppth;

};



#endif // IMAGEMAPCLICKABLEAERA

