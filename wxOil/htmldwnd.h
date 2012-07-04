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



#ifndef INC_HTMLDWND
#define INC_HTMLDWND


#include "inetop.h"


///////////////////////////////////////////////////////////////////////////////
/////////////////				BMP download			///////////////////////
///////////////////////////////////////////////////////////////////////////////



/****************************************************************************

>	class BitmapDownloadParam : public DownloadOpParam

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/03/97
	Purpsoe:	File Download param, download a bitmap file.
	Purpose:	Download operation parameter structure - passes the minimum necessary information to the Op

****************************************************************************/

class BitmapDownloadParam : public DownloadOpParam
{

public:

	BitmapDownloadParam ();
	~BitmapDownloadParam ();

	//PathName m_Path;			// temporary path
	INT32 m_TagId;				// Id of tag associated with the bitmap
	SelOperation *m_Op;		// Undoable operation
	String_256 m_FileName;		// original filename
	Document *m_DestDoc;		// destination document
	INT32 m_FileNum;			// curent file
	INT32 m_FileNumber;			// number of files
	DocCoord m_PosTranslate;	// coordinates of the bitmap in the document
	BOOL m_IsCenter;			// do we have to center it ?

};


/****************************************************************************

>	class OpBitmapDownload : public DownloadOp

	Author:		Olivier_Gascoin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/04/97
	Purpose:	File download operation. Download a bitmap file 
	SeeAlso: -

****************************************************************************/

#define OPTOKEN_OPBITMAPDOWNLOAD _T("BitmapDownloadOp")	// Optoken for the bitmap file download

class OpBitmapDownload : public DownloadOp
{
	CC_DECLARE_DYNCREATE(OpBitmapDownload )

public:
	OpBitmapDownload () {};
	~OpBitmapDownload () {};

	static BOOL Init();                        
	static OpState GetState(String_256*, OpDescriptor*);

protected:
	virtual BOOL OnDocChangingMsg(Document* pChangingDoc, DocChangingMsg::DocState State);

	virtual void OnDownloadSuccess();
	virtual void OnDownloadFail();

	
};


#endif

