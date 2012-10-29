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
#include "filtimop.h"

//#include "resimmap.h"		//For _R(IDS_IMAGEMAP_DEFAULTMAPNAME)
#include "bitfilt.h"		//For GetSizeOfDrawing

CC_IMPLEMENT_DYNAMIC(ImagemapFilterOptions, CCObject)

#define new CAM_DEBUG_NEW


/******************************************************

  Constructors

  *****************************************************/

/********************************************************************************************

>	ImagemapFilterOptions::ImagemapFilterOptions()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Purpose:	Default constructor

				Note that this default constructor is used to set up the default
				values on start up.

********************************************************************************************/
ImagemapFilterOptions::ImagemapFilterOptions()
{
	//Initialise our variables
	m_ffApprox=FF_APPROXIMATELY;
	m_fAllRectangles=FALSE;
	m_stExportArea=DRAWING;
	m_dDPI=96.0;

	m_fClipboard=FALSE;
	m_fFile=FALSE;
	m_fInsert=TRUE;
	m_pfileFile=NULL;
	m_fReportErrors=FALSE;
}

/********************************************************************************************

  ImagemapFilterOptions(String_256 strName,
							FlatteningFactor ffApprox,
							BOOL fAllRectangles,
							SelectionType stExportArea,
							double dDPI,
							BOOL fClipboard,
							BOOL fFile=FALSE,
							PathName pthFile,
							BOOL fInsert=FALSE,
							CCLexFile* pfileFile,
							BOOL fReportErrors
							);


	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Purpose:	Specific constructor

********************************************************************************************/
ImagemapFilterOptions::ImagemapFilterOptions(String_256 strName,
							FlatteningFactor ffApprox,
							BOOL fAllRectangles,
							SelectionType stExportArea,
							double dDPI,
							BOOL fClipboard,
							BOOL fFile,
							PathName pthFile,
							BOOL fInsert,
							CCLexFile* pfileFile,
							BOOL fReportErrors
							)
{
	//Initialise our variables
	m_strName=strName;
	m_ffApprox=ffApprox;
	m_fAllRectangles=fAllRectangles;
	m_stExportArea=stExportArea;
	m_dDPI=dDPI;

	m_fClipboard=fClipboard;
	m_fFile=fFile;
	m_pthFile=pthFile;
	m_fInsert=fInsert;
	m_pfileFile=pfileFile;
	m_fReportErrors=0;
	
	// init where the graphic is exported to
	// this makes a reasonable guess but should be set later
	m_GraphicPath = pthFile;
	m_GraphicPath.SetType("gif");
}

/******************************************************

  Copy constructor, destructor and assignment operator

  *****************************************************/
/********************************************************************************************

>	ImagemapFilterOptions::ImagemapFilterOptions(const ImagemapFilterOptions& waaCopy)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Inputs:		ImagemapFilterOptions object to copy
	Outputs:	-
	Returns:	*this
	Purpose:	Copy constructor
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

ImagemapFilterOptions::ImagemapFilterOptions(const ImagemapFilterOptions& ifoCopy)
{
	//Simply use the assigment operator
	*this=ifoCopy;
					   
}

/********************************************************************************************

>	ImagemapFilterOptions::~ImagemapFilterOptions()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destructor
	Errors:		-						   
	SeeAlso:	-

********************************************************************************************/

ImagemapFilterOptions::~ImagemapFilterOptions()
{
	//Does nothing
}

/********************************************************************************************

>	ImagemapFilterOptions& operator= (const ImagemapFilterOptions& ifoOther)					

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Inputs:		ifoOther	Object to copy
	Outputs:	-
	Returns:	-
	Purpose:	Assignment operator
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

ImagemapFilterOptions& ImagemapFilterOptions::operator= (const ImagemapFilterOptions& ifoOther)					
{
	
	//Simply copy the member variables across
	m_strName=ifoOther.m_strName;
	m_ffApprox=ifoOther.m_ffApprox;
	m_fAllRectangles=ifoOther.m_fAllRectangles;
	m_fClipboard=ifoOther.m_fClipboard;
	m_fFile=ifoOther.m_fFile;
	m_stExportArea=ifoOther.m_stExportArea;
	m_dDPI=ifoOther.m_dDPI;
	m_pthFile=ifoOther.m_pthFile;
	m_fInsert=ifoOther.m_fInsert;
	m_pfileFile=ifoOther.m_pfileFile;
	m_fReportErrors=ifoOther.m_fReportErrors;
	m_GraphicPath = ifoOther.m_GraphicPath;

	return *this;
}

/******************************************************

  Toolkit functions

  *****************************************************/
/********************************************************************************************

	static DocRect ImagemapFilterOptions::GetSizeOfExportArea(SelectionType stExportArea)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/4/97
	Inputs:		-
	Outputs:	-
	Returns:	The bounding rectangle of the export area
	
	Purpose:	Returns the bounding rectangle of the export area, based
				on the m_stExportArea member variable
	
				Note that this function assumes there are only two types
				of export area: the selection and the drawing.

	Errors:		-
	SeeAlso:	-

********************************************************************************************/

DocRect ImagemapFilterOptions::GetSizeOfExportArea(SelectionType stExportArea)
{	
	//This is the value we will return
	DocRect rectBounds;

	//If the area to export is the selection
	if (stExportArea==SELECTION)
	{
		//Then get the bounding rectangle of the selection
		rectBounds=GetApplication()->FindSelection()->GetBoundingRect();
	}
	else
	{
		//We assume the selection area is the drawing
		//Get the bounds of the drawing
		rectBounds=BaseBitmapFilter::GetSizeOfDrawing();
	}

	return rectBounds;
 
}

/********************************************************************************************

	DocCoord ImagemapFilterOptions::GetOriginOfExportArea(SelectionType stExportArea)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/4/97
	Inputs:		-
	Outputs:	-
	Returns:	The top left hand corner coordinate of the export area.
	
	Purpose:	Returns the top left hand corner of the export area - 
				which is the origin from which all bitmap coordinates are
				taken.
	
				Note that this function assumes there are only two types
				of export area: the selection and the drawing.

	Errors:		-
	SeeAlso:	ImagemapFilterOptions::GetSizeOfExportArea

********************************************************************************************/

DocCoord ImagemapFilterOptions::GetOriginOfExportArea(SelectionType stExportArea)
{	
	//Get the export area rectangle
	DocRect rectExport=ImagemapFilterOptions::GetSizeOfExportArea(stExportArea);

	//This is its top left hand corner
	DocCoord coordToReturn(rectExport.lo.x, rectExport.hi.y);
	
	return coordToReturn; 
}

