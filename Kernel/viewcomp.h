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
// Header for the view document component classes

#ifndef INC_VIEWCOMP
#define INC_VIEWCOMP


class BaseCamelotFilter;
class Quality;

/********************************************************************************************

>	class ViewComponentClass : public DocComponentClass

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/96
	Purpose:	Provide a class that will add view components to new documents.
	SeeAlso:	DocComponentClass

********************************************************************************************/

class ViewComponentClass : public DocComponentClass
{
	CC_DECLARE_DYNAMIC(ViewComponentClass)

public:
	static BOOL Init();

	BOOL AddComponent(BaseDocument *);
};

/********************************************************************************************

>	class ViewComponent : public DocComponent

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/7/96
	Purpose:	Provide a component that handles the saving of view information
				to the v2 file format
	SeeAlso:	DocComponent

********************************************************************************************/

class ViewComponent : public DocComponent
{
	CC_DECLARE_DYNAMIC(ViewComponent)

public:
	ViewComponent();
	~ViewComponent();

	// These are the Camelot Version 2 Web and Native file related functions
	virtual BOOL StartImport(BaseCamelotFilter* pFilter);
	virtual BOOL EndImport(BaseCamelotFilter* pFilter, BOOL Success);
	virtual BOOL StartExport(BaseCamelotFilter* pFilter);
	virtual BOOL EndExport(BaseCamelotFilter* pFilter, BOOL Success);

	// Helper functions for general use
	static BOOL ExportViewPortRecord(BaseCamelotFilter* pFilter);

	BOOL ImportViewDefinition(BaseCamelotFilter* pFilter);

private:
	BOOL StartWebExport(BaseCamelotFilter* pFilter);
	BOOL StartNativeExport(BaseCamelotFilter* pFilter);
	BOOL EndWebExport(BaseCamelotFilter* pFilter);
	BOOL EndNativeExport(BaseCamelotFilter* pFilter);

	// Called by the view port & doc view record writing functions
	// A View quality record should always precede these view records
	static BOOL ExportViewQualityRecord(BaseCamelotFilter* pFilter,Quality* pQuality);

	BOOL ExportAllViews(BaseCamelotFilter* pFilter);
	BOOL ExportViewDefinition(BaseCamelotFilter* pFilter, DocView * pView);
};


#endif // INC_VIEWCOMP
