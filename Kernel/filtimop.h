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

#ifndef INC_IMAGEMAPFILTEROPTIONS
#define INC_IMAGEMAPFILTEROPTIONS

//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "pathname.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "bmpprefs.h"
#include "flatfact.h"
				 
/**************************************************************************************

>	class ImagemapFilterOptions : public CCObject

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Purpose:	An ImagemapFilterOptions object contains all the information
				the ImagemapFilter needs to set itself up ready for export.

**************************************************************************************/
class ImagemapFilterOptions : public CCObject
{
	CC_DECLARE_DYNAMIC(ImagemapFilterOptions);

	//Constructors
public:
	ImagemapFilterOptions();
	ImagemapFilterOptions(String_256 strName,
							FlatteningFactor ffApprox=FF_CLOSELY,
							BOOL fAllRectangles=FALSE,
							SelectionType stExportArea=DRAWING,
							double dDPI=96,
							BOOL fClipboard=FALSE,
							BOOL fFile=FALSE,
							PathName pthFile=PathName(),
							BOOL fInsert=FALSE,
							CCLexFile* pfileFile=NULL,
							BOOL fReportErrors=TRUE
							);


	//Destructor, copy constructor and assignment operator
public:
	~ImagemapFilterOptions();
	ImagemapFilterOptions(const ImagemapFilterOptions& ifoCopy);
	ImagemapFilterOptions& operator=(const ImagemapFilterOptions& ifoCopy);
	

	//Access functions
public:
	String_256 GetImagemapName()
	{
		return m_strName;
	}

	FlatteningFactor GetFlatteningFactor()
	{
		return m_ffApprox;	
	}

	BOOL ExportAllRectangles()
	{
		return m_fAllRectangles;
	}

	BOOL ExportToClipboard()
	{
		return m_fClipboard;
	}

	BOOL ExportToFile()
	{
		return m_fFile;
	}


	SelectionType GetExportArea()
	{
		return m_stExportArea;
	}
	
	double GetDPI()
	{
		return m_dDPI;
	}

	PathName GetImagemapPath()
	{
		return m_pthFile;
	}

	CCLexFile* GetImagemapFile()
	{
		return m_pfileFile;
	}


	BOOL Insert()
	{
		return m_fInsert;
	}



	//Toolkit functions
public:
	static DocRect GetSizeOfExportArea(SelectionType stExportArea);
	static DocCoord GetOriginOfExportArea(SelectionType stExportArea);

	//Member variables
public:
	String_256			m_strName;			//The name of the imagemap
	FlatteningFactor	m_ffApprox;		//How much to flatten the paths
	BOOL				m_fAllRectangles;	//Whether all the clickable areas should be rectangles
	SelectionType		m_stExportArea;		//Area to export.
	double				m_dDPI;				//The DPI by which to scale the imagemap

	BOOL				m_fClipboard;		//Whether to put the imagemap on the clipboard
	BOOL				m_fFile;			//Whether to put the imagemap into a file
											//(Ignored by the ImagemapFilter, which always puts
											//imagemaps into a file)

	PathName			m_pthFile;			//The path of the file to which the imagemap
											//should be exported

	CCLexFile*			m_pfileFile;		//Pointer to the file to export into

	BOOL				m_fInsert;			//If the file specified in m_pthFile exists, 
											//whether to insert the imagemap into this file
											//or replace the entire file.
	BOOL				m_fReportErrors;	//Whether to report errors during the imagemap
											//export
											
	PathName			m_GraphicPath;		//The location of the graphic that the image map refers to
						
};



#endif	// INC_IMAGEMAPFILTER
