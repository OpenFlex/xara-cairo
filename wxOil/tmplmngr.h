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


#ifndef INC_TEMPLATE_MANAGER
#define INC_TEMPLATE_MANAGER

/*********************************************************************************************

>	class CTemplateManager

	Author:		Luke_Hart (Xara Group Ltd) <lukeh@xara.com>
	Created:	17/07/2006
	Base Class:	None
	Purpose:	                
	Errors:		None.
				
*********************************************************************************************/

class CCAPI CTemplateManager
{
public:       
	CTemplateManager();
	~CTemplateManager();

	BOOL Init();

	// Public access to the user's defined template path
	static String_256& GetTemplatesPath();
	static void SetTemplatesPath(String_256& strToSet);

	bool GetTemplateMenuName( UINT32 ordNumberOfTemplate, String_256* pStrPathOfFile );
	bool GetTemplateFilename( UINT32 ordNumberOfTemplate, String_256* pStrPathOfFile );

	static PathName GetDefaultAnimationTemplate();
	static void SetDefaultAnimationTemplate( const String_256& strPath )	{ ms_strDefaultAnimationTemplate = strPath; }
	static PathName GetDefaultDrawingTemplate();
	static void SetDefaultDrawingTemplate( const String_256& strPath )		{ ms_strDefaultDrawingTemplate = strPath; }

private:
	static String_256	m_TemplatesPath;
	static String_256	m_LocalTemplatesPath;

	static String_256	ms_strDefaultAnimationTemplate;
	static String_256	ms_strDefaultDrawingTemplate;

	typedef std::map<String_256, bool> CTemplateList;
	void GetTemplateList( CTemplateList* pList, const String_256& strTemplatePath, bool fLocal );
};

#endif
													   
