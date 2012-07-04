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

#ifndef INC_XMLUTILS
#define INC_XMLUTILS

#include <libxml/xpathInternals.h>

class CXMLUtils : public CCObject
{
public:
	CXMLUtils() {;}
	virtual ~CXMLUtils() {;}

	static BOOL			Initialise();
	static BOOL			DeInitialise();

	// All unicode data is stored as UTF-8 in libxml2 and xmlChar* is a pointer to a UTF-8 byte stream
	// Remember that unicode data is stored as UTF-16 in XAR files, as UTF-16 in memory on Windows builds
	// but as UTF-4/UTF-32 in memory on Linuxbuilds. So we need conversion functions!
	static wxString 	ConvertToWXString(const xmlChar*);
	static void			ConvertToXMLString(wxString str, xmlChar** pxmlstr);


#if _DEBUG
	static void Test();
	static INT32 example4(const char *filename, const xmlChar * xpathExpr, const xmlChar * value);
	static void update_xpath_nodes(xmlNodeSetPtr nodes, const xmlChar * value);
#endif


/*	static IXMLDOMDocument2Ptr NewDocument();
	static IXMLDOMDocument2Ptr NewDocument(IXMLDOMDocument2Ptr pCopySourceDoc);

	static PrepareDocument(IXMLDOMNodePtr pNode);
	static PrepareDocument(IXMLDOMDocument2Ptr pDoc2);
	static AddEncodingInstruction(IXMLDOMDocument2Ptr pDoc2,
									const CString& strVersion,
									const CString& strEncoding);

	static IXMLDOMElementPtr AppendElement(IXMLDOMElementPtr pContext, const CString& elname, const CString* value = NULL);
	static IXMLDOMElementPtr AppendElement(IXMLDOMElementPtr pContext, const CString& elname, const INT32 lValue);
	static IXMLDOMElementPtr AppendElement(IXMLDOMElementPtr pContext, const CString& elname, const BOOL bValue);

	static BOOL		ReplaceElement(IXMLDOMElementPtr pElement, const CString& strElPath, const CString& strText, const BOOL bIgnoreBlank = FALSE);
	static BOOL		ReplaceElement(IXMLDOMElementPtr pElement, const CString& strElPath, const INT32 lValue);
	static BOOL		ReplaceElement(IXMLDOMElementPtr pElement, const CString& strElPath, const BOOL bValue);

	static CString	GetNodeString(IXMLDOMNodePtr pNode, const CString& strNodePath, const CString& strDefault = _T(""));
	static INT32		GetNodeLong(IXMLDOMNodePtr pNode, const CString& strNodePath, const INT32 lDefault = 0);
	static BOOL		GetNodeBOOL(IXMLDOMNodePtr pNode, const CString& strNodePath, const BOOL bDefault = FALSE);

	static CString	GetAttributeString(IXMLDOMElementPtr pNode, const CString& strAttrName, const CString& strDefault = _T(""));
	static INT32		GetAttributeLong(IXMLDOMElementPtr pNode, const CString& strAttrName, const INT32 lDefault = 0);
	static BOOL		GetAttributeBOOL(IXMLDOMElementPtr pNode, const CString& strAttrName, const BOOL bDefault = FALSE);

	static BOOL		SetAttribute(IXMLDOMNodePtr pNode, const CString& strName, const CString& strValue);
	static BOOL		SetAttribute(IXMLDOMNodePtr pNode, const CString& strName, const INT32 lValue);
	static BOOL		SetAttribute(IXMLDOMNodePtr pNode, const CString& strName, const BOOL bValue);

	static CString	GetNodeName(IXMLDOMNodePtr pNode);
*/
};

#endif // INC_XMLUTILS

