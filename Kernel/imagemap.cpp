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

// Imagemap class

#include "camtypes.h"
#include "imagemap.h"

#include "clicarea.h"	//For ImagemapClickableArea and derived classes
#include "filtimop.h"	//For ImagemapFilterOptions::GetOriginOfExportArea
//#include "paths.h"		//For Path::Scale - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "doccoord.h"	//For DocCoord::Scale - in camtypes.h [AUTOMATICALLY REMOVED]

CC_IMPLEMENT_DYNAMIC(Imagemap, List)

/*************************************************

  Constructors

  ***********************************************/

/********************************************************************************************

>	Imagemap::Imagemap() : List()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Purpose:	Default constructor
	
********************************************************************************************/

Imagemap::Imagemap() : OverrideList()
{
	//Does nothing
}

/*************************************************

  Destructor

  ***********************************************/

  /********************************************************************************************

>	Imagemap::~Imagemap()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Purpose:	Destructor
	
********************************************************************************************/

Imagemap::~Imagemap()
{
	//Delete all our list items
	DeleteAll();
}

/*************************************************

  Adding to the imagemap

  ***********************************************/

  /********************************************************************************************

  >	Imagemap::AddRectangle(DocRect rectToAdd, TCHAR* pcURL=NULL, TCHAR* pcFrame=NULL);


	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Inputs:		rectToAdd	The rectangle to add to the imagemap
	Purpose:	Adds a rectangular clickable region to the imagemap
	
********************************************************************************************/

void Imagemap::AddRectangle(DocRect rectToAdd, TCHAR* pcURL, TCHAR* pcFrame)
{
	//Create a new ImagemapClickableRectangle with the rectangle we've been given
	ImagemapClickableRectangle* pRectangle=new ImagemapClickableRectangle(rectToAdd, pcURL, pcFrame);

	//And add it to the imagemap
	//Note that we add it to the head of the list. That's because, in imagemaps,
	//the first clickable area found in the file is the one nearest the front.
	AddHead(pRectangle);
}

/********************************************************************************************

  >	Imagemap::AddCircle(Path* pthToAdd, TCHAR* pcURL=NULL, TCHAR* pcFrame=NULL);


	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Inputs:		pthToAdd	The circular path to add to the imagemap
	Purpose:	Adds a circular clickable region to the imagemap
	
********************************************************************************************/

void Imagemap::AddCircle(Path* pthToAdd, TCHAR* pcURL, TCHAR* pcFrame)
{
	//Create a new ImagemapClickableCircle with our scaled path
	ImagemapClickableCircle* pCircle=new ImagemapClickableCircle(pthToAdd, pcURL, pcFrame);

	//And add it to the imagemap
	//Note that we add it to the head of the list. That's because, in imagemaps,
	//the first clickable area found in the file is the one nearest the front.
	AddHead(pCircle);
}

/********************************************************************************************

  >	Imagemap::AddPolygon(Path* pthToAdd, TCHAR* pcURL=NULL, TCHAR* pcFrame=NULL);


	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/97
	Inputs:		pthToAdd	The path to add to the imagemap
				
	Purpose:	Adds a straight-sided polygon to the imagemap
	
********************************************************************************************/

void Imagemap::AddPolygon(Path* pthToAdd, TCHAR* pcURL, TCHAR* pcFrame)
{
	//Create a new ImagemapClickableCircle with the path we've been given
	ImagemapClickablePolygon* pPolygon=new ImagemapClickablePolygon(pthToAdd, pcURL, pcFrame);
		
	//And add it to the imagemap
	//Note that we add it to the head of the list. That's because, in imagemaps,
	//the first clickable area found in the file is the one nearest the front.
	AddHead(pPolygon);
}

/*************************************************

  Writing out the imagemap

  ***********************************************/


/********************************************************************************************

 >	INT32 Imagemap::WriteHelper(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)
										   
	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/4/97
	Inputs:		pfileToWrite - The file to write to
				pcBuffer	 - Pointer to a text buffer to write to

				Either of the above may be NULL.

  Returns:		The number of TCHARs written.

  Purpose:		Writes out the imagemap.

				This function simply iterates through the list and calls on
				the members to write themselves out.
	
SeeAlso:		ImagemapRenderRegion::Write()
	
********************************************************************************************/

INT32 Imagemap::Write(CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Set up a variable to remember how many bytes we have written
	INT32 lBytesWritten=0;
	
	//Now, get the first clickable area in the imagemap
	ImagemapClickableArea* pAreaToWrite=(ImagemapClickableArea*) GetHead();

	//And while we're still looking at a valid clickable area
	while (pAreaToWrite!=NULL)
	{
		//Tell that area to write itself out to the imagemap.
		//This function will return the number of TCHARs it writes
		lBytesWritten+=pAreaToWrite->Write(pfileToWrite, pcBuffer);

		//And move on to the next clickable area
		pAreaToWrite=(ImagemapClickableArea*) GetNext(pAreaToWrite);
	}

	//And return the number of TCHARs we have written
	return lBytesWritten;
	
}



