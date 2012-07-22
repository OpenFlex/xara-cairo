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

#include "camelot.h"
#include "sgliboil.h"	// AppendSlashIfNotPresent
#include "fileutil.h"

#include "tmplmngr.h"

DECLARE_SOURCE("$Revision: 1437 $");

/********************************************************************************************

	Preference:		Path
	Section:		Templates
	Range:			0 .. 256 characters
	Purpose:		The path to load the templates from and save the templates to.
					Defaults to blank which means alongside	the exe.
	SeeAlso:		CCamDoc::LoadDefaultDocument; OpMenuSave::Do;

********************************************************************************************/

String_256 CTemplateManager::m_TemplatesPath = TEXT("");
String_256 CTemplateManager::m_LocalTemplatesPath = TEXT("");

/********************************************************************************************

	Preference:		DefaultAnimationTemplate
	Section:		Templates
	Range:			String
	Purpose:		The path to the default animation template. By default, this
					is the EXE path with "\templates\animation.xar" added to the end
	SeeAlso:		-

********************************************************************************************/

String_256 CTemplateManager::ms_strDefaultAnimationTemplate = _T("");

/********************************************************************************************

	Preference:		DefaultDrawingTemplate
	Section:		Templates
	Range:			String
	Purpose:		The path to the default drawing template. By default, this
					is the EXE path with "\templates\drawing.xar" added to the end
	SeeAlso:		-

********************************************************************************************/

String_256 CTemplateManager::ms_strDefaultDrawingTemplate = _T("");


/***********************************************************************************************

> 	CTemplateManager::CTemplateManager()

    Author: 	Luke_Hart (Xara Group Ltd) <lukeh@xara.com>
    Created:	17/07/2006
	
	Inputs:		-
    Outputs:    -
    Returns:   	-
                 
    Purpose:    Initialise the manager.
               
	Errors:		None.
                   			                                     
***********************************************************************************************/

CTemplateManager::CTemplateManager()
{
}

/***********************************************************************************************

> 	CTemplateManager::~CTemplateManager()

    Author: 	Luke_Hart (Xara Group Ltd) <lukeh@xara.com>
    Created:	17/07/2006
	
	Inputs:		- 
    Outputs:    -
    Returns:   	-
                 
    Purpose:    Destroys the manager.
               
	Errors:		None.
                   			                                     
***********************************************************************************************/

CTemplateManager::~CTemplateManager()
{
}


/***********************************************************************************************

> 	BOOL CTemplateManager::Init()

    Author: 	Luke_Hart (Xara Group Ltd) <lukeh@xara.com>
    Created:	17/07/2006
	
	Inputs:		-
    Outputs:    -
    Returns:   	TRUE if the object initialised ok.
                 
    Purpose:    Initialise the manger

	Errors:		None.
                   			                                     
***********************************************************************************************/

BOOL CTemplateManager::Init()
{
	//Graham 20/10/97
	if (Camelot.DeclareSection( _T("NewTemplates"), 10))
	{
		Camelot.DeclarePref( _T("NewTemplates"), _T("DefaultAnimationFile"), &ms_strDefaultAnimationTemplate);
		Camelot.DeclarePref( _T("NewTemplates"), _T("DefaultDrawingFile"), &ms_strDefaultDrawingTemplate);
	}

	if (ms_strDefaultAnimationTemplate==String_256(_T("")))
	{
		String_256 strNameOfAnimationTemplate( _R(IDS_NEWTEMPLATES_DEFAULTANIMATIONFILE) );
		String_256 strPathOfTemplate( GetTemplatesPath() );
		strPathOfTemplate += strNameOfAnimationTemplate;

		ms_strDefaultAnimationTemplate=strPathOfTemplate;

		TRACEUSER( "jlh92", _T("DefAnimTempl = %s\n"), PCTSTR(ms_strDefaultAnimationTemplate) );
	}

	if( ms_strDefaultDrawingTemplate == String_256( _T("") ) || 
		0 == camStrcmp( ms_strDefaultDrawingTemplate, _T("default.xar") ) )
	{
		ms_strDefaultDrawingTemplate=String_256(_R(IDS_DEFAULTDOCNAME));

PORTNOTETRACE("other","CTemplateManager::Init - remove code to setup paths");
#if !defined(EXCLUDE_FROM_XARALX)
		//Then assume it's the exe path with \templates\drawing.xar on the end
		TCHAR Pathname[MAX_PATH];

		if(GetModuleFileName(NULL, Pathname, MAX_PATH) == 0) //Should be in the winoil really
			return FALSE;

		// Put the path name into a string
		String_256 strPathOfExe(Pathname);
		PathName pathPathOfExe(strPathOfExe);

		strPathOfExe = pathPathOfExe.GetLocation(TRUE);

		//And add "templates\" to the end
		String_256 strTemplatesDirectory(_R(IDS_NEWTEMPLATES_RELATIVEPATH));
		String_256 strNameOfDrawingTemplate(_R(IDS_DEFAULTDOCNAME));

		String_256 strPathOfTemplate=strPathOfExe;
		strPathOfTemplate+=strTemplatesDirectory;
		strPathOfTemplate+=strNameOfDrawingTemplate;

		ms_strDefaultDrawingTemplate=strPathOfTemplate;
#endif
	}

	// As the preference system is up, declare our preference to it
	// This is the pathname that the templates should be loaded from and saved to
	// If blank, the default, then it should use the exe path
	GetApplication()->DeclareSection(TEXT("Templates"), 2);
	GetApplication()->DeclarePref(TEXT("Templates"), TEXT("Path"), &m_TemplatesPath);
	GetApplication()->DeclarePref(TEXT("Templates"), TEXT("LocalPath"), &m_LocalTemplatesPath);
	
	//Graham 21/10/97: If it is blank, then we should use the
	//exe path with "\templates\" on the end
	if( m_TemplatesPath.IsEmpty() || !SGLibOil::DirExists( m_TemplatesPath ) )
	{
		// Put the path name into a string
		m_TemplatesPath = CCamApp::GetResourceDirectory();

		//And add "templates\" to the end
		String_256 strRelativePath(_R(IDS_NEWTEMPLATES_RELATIVEPATH));

		m_TemplatesPath+=strRelativePath;

#if defined(_DEBUG)
		if( !SGLibOil::DirExists( m_TemplatesPath ) )
			m_TemplatesPath = _T("/usr/share/xara/Templates/");
#endif
	}

	if( m_LocalTemplatesPath.IsEmpty() || !SGLibOil::DirExists( m_LocalTemplatesPath ) )
	{
		wxString		strHome( ::wxGetHomeDir() );
		m_LocalTemplatesPath = (PCTSTR)strHome;
		m_LocalTemplatesPath += _T("/.xara/templates/");
	}

	TRACEUSER( "jlh92", _T("Using %s as template store\n"), PCTSTR(m_TemplatesPath) );
	return TRUE;
}


/***********************************************************************************************

>	String_256& CTemplateManager::GetTemplatesPath()

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	03/03/97
	Inputs:		-
	Outputs:	-
	Returns:	The specfied templates path in a string
	Purpose:	To find out the user's preference for a path to the template file.
	SeeAlso:	CCamDoc::LoadDefaultDocument; OpMenuSave::Do;

***********************************************************************************************/

String_256& CTemplateManager::GetTemplatesPath()
{
	// Add a trailing slash if it hasn't got one
	SGLibOil::AppendSlashIfNotPresent(&m_LocalTemplatesPath);

	return m_LocalTemplatesPath;
}

/***********************************************************************************************

>	void CTemplateManager::SetTemplatesPath(String_256& strToSet)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/20/97
	Inputs:		strToSet - the new value
	Returns:	-
	Purpose:	To set the default templates path
	SeeAlso:	-

***********************************************************************************************/

void CTemplateManager::SetTemplatesPath(String_256& strToSet)
{
	m_LocalTemplatesPath = strToSet;

	// Add a trailing slash if it hasn't got one
	SGLibOil::AppendSlashIfNotPresent(&m_LocalTemplatesPath);
}

/********************************************************************************************

>   PathName CTemplateManager::GetDefaultAnimationTemplate()

	Author:         Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:        23/10/97
	Inputs:         -
	Outputs:        -
	Returns:        The path of the default animation template
	Purpose:        As above
	Errors:         -
	SeeAlso:        -

********************************************************************************************/

PathName CTemplateManager::GetDefaultAnimationTemplate()
{
	PathName pathToReturn=ms_strDefaultAnimationTemplate;

	return pathToReturn;
}

/********************************************************************************************

>   PathName CTemplateManager::GetDefaultDrawingTemplate()

	Author:         Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:        23/10/97
	Inputs:         -
	Outputs:        -
	Returns:        The path of the default drawing template
	Purpose:        As above
	Errors:         -
	SeeAlso:        -

********************************************************************************************/

PathName CTemplateManager::GetDefaultDrawingTemplate()
{
	PathName pathToReturn=ms_strDefaultDrawingTemplate;

	return pathToReturn;
}


/********************************************************************************************

>   PathName CTemplateManager::GetTemplateList( CTemplateList* pList, const String_256& strTemplatePath, bool fLocal )

	Author:         Luke_Hart (Xara Group Ltd) <lukehart@xara.com>
	Created:        18/07/2006
	Inputs:         const String_256& strTemplatePath	Path to directory to scan
					bool fLocal							Value local flag to stroe in list 
	Outputs:        CTemplateList* pList				The returned list
	Returns:        Nothing
	Purpose:        INTERNAL - Fill the list of templates with all templates in specified directory,
					marking each with specified user local flag
	Errors:         -
	SeeAlso:        -

********************************************************************************************/

void CTemplateManager::GetTemplateList( CTemplateList* pList, const String_256& strTemplatePath, bool fLocal )
{
	// Don't bother with any of this is directory is invalid
	if( !wxDir::Exists( (PCTSTR)strTemplatePath ) )
		return;

	//Now search that path for templates
	//Start by setting the leaf name to *.xar
	String_256			strSearchFilename( _R(IDS_NEWTEMPLATES_DEFAULTTEMPLATEEXTENSION) );

	// Get the default entry names
	String_256			strPathOfDrawingTemplate   = CTemplateManager::GetDefaultDrawingTemplate().GetPath(FALSE);
	strPathOfDrawingTemplate.SwapChar( _T('_'), _T(' ') );
	String_256			strPathOfAnimationTemplate = CTemplateManager::GetDefaultAnimationTemplate().GetPath(FALSE);
	strPathOfAnimationTemplate.SwapChar( _T('_'), _T(' ') );
	String_256			strPathOfFile;

	TRACEUSER( "jlh92", _T("DefPath = %s, %s\n"), PCTSTR(strPathOfDrawingTemplate),
		PCTSTR(strPathOfAnimationTemplate) );

	// Build system template path
	PathName			pathTemplates( strTemplatePath );
	pathTemplates.SetFileNameAndType( strSearchFilename );
	PathName			pathOfFile( pathTemplates );
	String_256			strTemplates = pathTemplates.GetPath( FALSE );

	//And search the path for xar files that are
	//NOT the default animation or drawing templates
	String_256			strNameOfFile;
	if( FileUtil::StartFindingFiles( &strTemplates ) )
	{
		while( FileUtil::FindNextFile( &strNameOfFile ) )
		{
			pathOfFile.SetFileNameAndType( strNameOfFile );
			strPathOfFile = pathOfFile.GetFileName(TRUE);

			if( 0 != strPathOfFile.CompareTo( strPathOfDrawingTemplate, FALSE ) &&
				0 != strPathOfFile.CompareTo( strPathOfAnimationTemplate, FALSE ) )
			{
				(*pList)[strPathOfFile] = fLocal;
				TRACEUSER( "jlh92", _T("Curr = %s\n"), PCTSTR(strPathOfFile) );
			}
		}
		FileUtil::StopFindingFiles();
	}

	// Don't allow any errors set while searching to propagate outside this scope
	Error::ClearError();
}


/********************************************************************************************

>   PathName CTemplateManager::GetTemplateMenuName( UINT32 ordNumberOfTemplate, String_256* pStrNameOfFile )

	Author:         Luke_Hart (Xara Group Ltd) <lukehart@xara.com>
	Created:        18/07/2006
	Inputs:         UINT32 ordNumberOfTemplate		Ordinal of template to query
	Outputs:        String_256* pStrNameOfFile		Name that is returned
	Returns:        True on success, else false if template with ordinal doesn't exist
	Purpose:        Return the name to use in the New menu in pStrNameOfFile for the template
					with ordinal ordNumberOfTemplate.
	Errors:         -
	SeeAlso:        -

********************************************************************************************/

bool CTemplateManager::GetTemplateMenuName( UINT32 ordNumberOfTemplate, String_256* pStrNameOfFile )
{
	// Fill the list with all templates (user local, begin second will over-write system ones)
	CTemplateList		setSortFilename;
	GetTemplateList( &setSortFilename, m_TemplatesPath, false );
	GetTemplateList( &setSortFilename, m_LocalTemplatesPath, true );

	// If the template with ordinal doesn't exist, fail
	if( ordNumberOfTemplate > UINT32(setSortFilename.size()) )
		return false;

	// Get enbry for template
	CTemplateList::iterator iter = setSortFilename.begin();
	for( UINT32 i = 1; i < ordNumberOfTemplate; ++i, ++iter )
	{ /*Do nothing!*/ }

	*pStrNameOfFile = iter->first;
	TRACEUSER( "jlh92", _T("Final(%d) = %s\n"), ordNumberOfTemplate, PCTSTR(*pStrNameOfFile) );

	return true;
}


/********************************************************************************************

>   PathName CTemplateManager::GetTemplateFilename( UINT32 ordNumberOfTemplate, String_256* pStrNameOfFile )

	Author:         Luke_Hart (Xara Group Ltd) <lukehart@xara.com>
	Created:        18/07/2006
	Inputs:         UINT32 ordNumberOfTemplate		Ordinal of template to query
	Outputs:        String_256* pStrNameOfFile		Path that is returned
	Returns:        True on success, else false if template with ordinal doesn't exist
	Purpose:        Return the path to template with ordinal ordNumberOfTemplate in pStrNameOfFile.
	Errors:         -
	SeeAlso:        -

********************************************************************************************/

bool CTemplateManager::GetTemplateFilename( UINT32 ordNumberOfTemplate, String_256* pStrNameOfFile )
{
	// Fill the list with all templates (user local, begin second will over-write system ones)
	CTemplateList		setSortFilename;
	GetTemplateList( &setSortFilename, m_TemplatesPath, false );
	GetTemplateList( &setSortFilename, m_LocalTemplatesPath, true );

	// If the template with ordinal doesn't exist, fail
	if( ordNumberOfTemplate > UINT32(setSortFilename.size()) )
		return false;

	// Get enbry for template
	CTemplateList::iterator iter = setSortFilename.begin();
	for( UINT32 i = 1; i < ordNumberOfTemplate; ++i, ++iter )
	{ /*Do nothing!*/ }

	// Pre-pend the path to the template
	PathName			pathTemplates = iter->second ? m_LocalTemplatesPath : m_TemplatesPath;
	pathTemplates.SetFileNameAndType( iter->first );

	*pStrNameOfFile = pathTemplates.GetPath();
	TRACEUSER( "jlh92", _T("Final(%d) = %s\n"), ordNumberOfTemplate, PCTSTR(*pStrNameOfFile) );

	return true;
}
