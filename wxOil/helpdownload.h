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



#ifndef INC_HELPDOWNLOAD
#define INC_HELPDOWNLOAD


#include "inetop.h"


///////////////////////////////////////////////////////////////////////////////
/////////////////		Help and Support files download		///////////////////
///////////////////////////////////////////////////////////////////////////////



/****************************************************************************

>	class HelpDownloadParam : public DownloadOpParam

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/04/2004
	Purpose:	File Download param, download a file in the OpMenuImport::Do().
	Purpose:	Download operation parameter structure - passes the minimum necessary information to the Op

****************************************************************************/

class HelpDownloadParam : public DownloadOpParam
{
public:

	HelpDownloadParam();
	~HelpDownloadParam();

	PathName m_pathDestination;
	String_16 m_strResourceType;
	COleDateTime m_date;
	IXMLDOMDocumentPtr m_pIndexDoc;
	IXMLDOMNodePtr m_pOptionNode;
};


/****************************************************************************

>	class HelpDownloadOp : public DownloadOp

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/04/2004
	Purpose:	File download operation. Download a file 
	SeeAlso: -

****************************************************************************/

#define OPTOKEN_HELPDOWNLOADOP _T("HelpDownloadOp")	// Optoken for the file download
#define OPTOKEN_HELPDOWNLOADDLG _T("HelpDownloadDlg")

class HelpDownloadOp : public DownloadOp
{
	CC_DECLARE_DYNCREATE(HelpDownloadOp)

public:
	static BOOL CheckForNewFiles(BOOL bForeground);

public:
	HelpDownloadOp() {};
	virtual ~HelpDownloadOp() {};

	static BOOL		Init();                        
	static OpState	GetState(String_256*, OpDescriptor*);
//	void			Do(OpDescriptor* od);
	virtual BOOL	OnDocChangingMsg(Document* pChangingDoc, DocChangingMsg::DocState State);
	static void		DeferFileCopy(const String_256& pTempFile, const String_256& pDestFile);
	static void		DoDeferredFileCopy();

protected:
	virtual void OnDownloadSuccess();
	virtual void OnDownloadFail();
	virtual void OnDownloadAbort();

protected:
	static CString GetSupportFilepath(const CString& strLeafName = _T(""), const CString& strSupportFolder = _T("HelpAndSupport\\"));
	static CString GetIndexFileForLocale(const CString& strLocale);
	static CString GetFileForLocale(const CString& strLocale, const CString& strFile);
	static CString GetFullResourcePath(const CString& strResourceType,
									   const CString& strFilename,
									   const CString& strLocale = _T(""));
	static BOOL MatchFileAttributes(const CString& strFilePath, const COleDateTime& datetime, UINT32 size);
	static BOOL CheckIndexFile();
	static BOOL FileOnCD(IXMLDOMDocumentPtr pDoc,
							  const CString& strName,
							  const COleDateTime& datetime,
							  UINT32 size,
							  const CString& strLocale,
							  const CString& strType);
	static BOOL LegalFileType(const CString& strFilename);
	static BOOL LegalPathname(const CString& strPathname);
	static BOOL HasBeenDownloaded(IXMLDOMNodePtr pNode);

	static BOOL ProcessDownloadIndex(IXMLDOMDocumentPtr pDoc, BOOL bSilent = FALSE, BOOL* pbDidSomething = NULL);
	static BOOL EnoughDiskSpace(const CString& strPath, const UINT32 sizeRequired);
	static IXMLDOMNodePtr FindFirstOption(IXMLDOMDocumentPtr pDoc,
										   CString* pstrResourceType,
										   CString* pstrLocale);

// Properties
public:
	static String_256 IndexBaseURL;
	static String_256 DeferredCopySrc;
	static String_256 DeferredCopyDest;
	static BOOL HighBandwidth;
	static String_32 IndexLeafName;
	static INT32 CurrentIndexRelease;
	
};


class HelpDownloadDlg : public Operation
{
	CC_DECLARE_DYNCREATE(HelpDownloadDlg)

public:
	HelpDownloadDlg() {};
	virtual ~HelpDownloadDlg() {};

	static BOOL		Init();                        
	static OpState	GetState(String_256*, OpDescriptor*);
	void			Do(OpDescriptor* od);
};


#endif // INC_HELPDOWNLOAD
