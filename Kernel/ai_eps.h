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


// Declaration of Adobe Illustrator EPS filter.

#ifndef INC_AI_EPS
#define INC_AI_EPS

//#include "epsfiltr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "document.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "impbmp.h"

// All the commands used by AI EPS files.
enum
{
	// Text handling
	EPSC_z = EPSC_EOF + 1,
	EPSC_e,
	EPSC_T,
	EPSC_t
};

/********************************************************************************************

>	class AIEPSFilter : public EPSFilter

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	A filter that imports EPS files in Adobe Illustrator EPS format.
	SeeAlso:	EPSFilter

********************************************************************************************/

class AIEPSFilter : public EPSFilter
{
	CC_DECLARE_DYNAMIC(AIEPSFilter);
	
public:
	AIEPSFilter();
	virtual BOOL Init();
	BOOL PrepareToExport(CCLexFile*, Spread *pSpread);
	TCHAR *GetEPSCommand(EPSCommand Cmd);
	virtual BOOL NeedsPrintComponents ( void );

protected:
	virtual	BOOL WriteNodes ( RenderRegion*	pRegion,
							  ExportDC*		pDC,
							  BOOL			VisibleLayersOnly,
							  BOOL			CheckSelected,
							  BOOL			ShowProgress);

	virtual void LookUpToken();
	virtual BOOL ProcessToken();
	INT32 EPSHeaderIsOk(ADDR pFileHeader, UINT32 HeaderSize);
	virtual void ProcessTextMatrix(Matrix* pMatrix);

	virtual BOOL SetTextLineSpacing (INT32 Type, INT32 EMLSpace, MILLIPOINT MLSpace, double DLSpace);

	// The array of keyword names
	static CommandMap AICommands[];

	BOOL bDoClip;
};

/********************************************************************************************

>	class PhotoShopEPSFilter : public EPSFilter

	Author:		Chris_Gallimore (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/11/00
	Purpose:	A filter that imports EPS files in Adobe Photoshop EPS format.
				Well, actually it doesn't as it's just a stub to stop Photoshop
				files from being loaded in (as they stuff up).
	SeeAlso:	EPSFilter

********************************************************************************************/

class PhotoShopEPSFilter : public EPSFilter
{
	CC_DECLARE_DYNAMIC(PhotoShopEPSFilter);
	
public:
	PhotoShopEPSFilter();

	virtual BOOL Init();
	virtual BOOL PrepareToImport();

protected:

	virtual void CleanUpAfterImport(BOOL Successful);
	virtual INT32 EPSHeaderIsOk(ADDR pFileHeader, UINT32 HeaderSize);
};

#endif  // INC_AI_EPS
