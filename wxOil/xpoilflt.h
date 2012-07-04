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


// The module that controls the OIL side of plugin import/export filters.

#ifndef INC_XPOILFLT
#define INC_XPOILFLT

//#include "oilfltrs.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "xpfcaps.h"
#include "xmlutils.h"
#include "camprocess.h"

class PluginNativeFilter;

class PluginFilterProcess : public CamProcess
{
public:
	PluginFilterProcess(PluginNativeFilter* pFilter, CCLexFile* pInFile = NULL, CCLexFile* pOutFile = NULL);
	virtual ~PluginFilterProcess();

	// These are called to handle the various streams
	virtual void ProcessStdErr();

	BOOL ReportError();
	void ReportWarning();

protected:
	PluginNativeFilter* m_pFilter;
	wxArrayString m_Errors;
	wxArrayString m_Warnings;
};


/********************************************************************************************

>	class PluginOILFilter : public OILFilter

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/01/05
	Purpose:	This class is used to encapsulate the platform specific features of a filter.
				Every Filter object has a pointer to an OILFilter object.  For example, 
				under Windows, it holds the file extensions that this file understands.
	SeeAlso:	Filter

********************************************************************************************/

class PluginOILFilter : public OILFilter
{
	CC_DECLARE_MEMDUMP(PluginOILFilter);

public:
	PluginOILFilter(Filter *pFilter);

	// This function initialises the filter setting up the import and export flags, 
	// the filter name and file extension
	// The parameter will almost certainly need to change when OILFilter::CreatePluginFilters 
	// is implemented properly by scanning the installed filters
	BOOL Init( xmlNode* pFilterNode );

	BOOL IsImport() { return(m_bImport); }
	BOOL IsExport() { return(m_bExport); }

	// The import and export functions
	// The mechanism may need to be modified to efficiently launch processes and 
	// attach CCLexFile derived classes.
	// Currently GetExportFile is called first so it will only really support 
	// outputting the Xar data to a temporary location so that it can be sent to the 
	// filter's stdin when DoExport is called.
	// GetCapabilities doesn't really need the pFile parameter so it could be called 
	// before GetExportFile.
	// At the moment, the easiest thing to do would probably be to load and save the 
	// Xar data from temporary files and simply redirect stdin and stdout when running 
	// the filter
	// I expect this will involve far less work than trying to attach a CCFile to a 
	// external process though to handle the progress indication correctly, stderr will 
	// need to be attached to in such a way that the loop that waits for the process to 
	// exit can read the progress values from stderr and update the XaraLX progress system
	BOOL GetExportFile(PathName* pPath, CCLexFile** ppNewFile);
	BOOL GetCapabilities(CCLexFile* pFile, PathName* pPath, CapabilityTree* pCapTree);
	BOOL DoExport(CCLexFile* pXarFile, PathName* pPath);
	INT32 HowCompatible(PathName& FileName);
	BOOL GetImportFile(CCLexFile* pFile, CCLexFile** ppNewFile);

	void Cleanup();

protected:
//	This function is called from GetCapabilities to parse the XML
	BOOL BuildCapabilityTree(wxString strXML, CapabilityTree* pCapTree);

	// The functions from here down to CreateColourNode are all concerned with the
	// parsing of the XML and the creation of the CapabilityTree
	BOOL ReadOptions(xmlNodePtr pNode, CapabilityTree* pCapTree);
	BOOL ReadRasterise(xmlNodePtr pNode, CapabilityTree* pCapTree);
	BOOL ReadSpread(xmlNodePtr pNode, CapabilityTree* pCapTree);
	BOOL ReadObjects(xmlNodePtr pNode, CapabilityTree* pCapTree);
	BOOL ReadAttributes(xmlNodePtr pNode, CapabilityTree* pCapTree);
	BOOL ReadColour(xmlNodePtr pNode, CapabilityTree* pCapTree);

	BOOL GetConvertAsType(xmlNodePtr pNode, XPFConvertType* pValue);
	BOOL GetXPFBOOL(xmlNodePtr pNode, LPTSTR pAttrName, XPFBOOL* pbValue);
	BOOL GetXPFProp(xmlNodePtr pNode, LPTSTR pAttrName, PropMapEntry aMap[], XPFProp* pValue);
	XPFCapability* CreateObjectNode(xmlNodePtr pNode);
	XPFCapability* CreateAttributeNode(xmlNodePtr pNode);
	XPFCapability* CreateColourNode(xmlNodePtr pNode);

protected:
	BOOL m_bImport;
	BOOL m_bExport;

	wxString m_InternalName;	// Internal name for filter (used to build path for XML config)
	wxString m_PrepareExport;	// Command for PrepareExport
	wxString m_DoExport;		// Command for DoExport
	wxString m_CanImport;		// Command for CanImport
	wxString m_DoImport;		// Command for DoImport

	wxFileName m_XMLFile;		// Full path to filter XML config file for the current user
	PathName m_TempXarFile;		// Full path to temporary Xar file
};


class AutoCleanOILFilter
{
public:
	AutoCleanOILFilter(PluginOILFilter* pOILFilter) : m_pOILFilter(pOILFilter) {}
	~AutoCleanOILFilter()
	{
		if (m_pOILFilter)
			m_pOILFilter->Cleanup();
	}

protected:
	PluginOILFilter* m_pOILFilter;
};


class PathNameListItem : public ListItem
{
public:
	CC_DECLARE_DYNAMIC( PathNameListItem )
	PathNameListItem(const PathName& Path)
	{
		m_Path = Path;
	}
	
	PathName m_Path;
};


#endif // INC_XPOILFLT
