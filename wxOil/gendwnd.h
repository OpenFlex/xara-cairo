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



#ifndef INC_GENERICDWND
#define INC_GENERICDWND


#include "inetop.h"


///////////////////////////////////////////////////////////////////////////////
/////////////////				Generic download			///////////////////
///////////////////////////////////////////////////////////////////////////////



/****************************************************************************

>	class GenericDownloadParam : public DownloadOpParam

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/03/97
	Purpose:	File Download param, download a file in the OpMenuImport::Do().
	Purpose:	Download operation parameter structure - passes the minimum necessary information to the Op

****************************************************************************/

class GenericDownloadParam : public DownloadOpParam
{
public:

	GenericDownloadParam();
	~GenericDownloadParam();

	SelOperation* m_Op;		// operation
	Filter* m_pFilter;		//
	Document* pDoc;

};


/****************************************************************************

>	class OpGenericDownload : public DownloadOp

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/04/97
	Purpose:	File download operation. Download a file 
	SeeAlso: -

****************************************************************************/

#define OPTOKEN_OPGENERICDOWNLOAD _T("GenericDownloadOp")	// Optoken for the file download

class OpGenericDownload : public DownloadOp
{
	CC_DECLARE_DYNCREATE(OpGenericDownload)

public:
	OpGenericDownload() {};
	virtual ~OpGenericDownload() {};

	static BOOL Init();                        
	static OpState GetState(String_256*, OpDescriptor*);
	virtual BOOL OnDocChangingMsg(Document* pChangingDoc, DocChangingMsg::DocState State);

protected:
	virtual void OnDownloadSuccess();
	virtual void OnDownloadFail();
	virtual void OnDownloadAbort();
	
};


#endif
