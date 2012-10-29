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


#ifndef INC_BMPEXPDOC
#define INC_BMPEXPDOC



class KernelBitmap;
class NodeBitmap;


/********************************************************************************************
 >	class BitmapExportDocument : public Document

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
 	Purpose:	A special document used for exporting single bitmaps
 				It contains a single layer with a single NodeBitmap object
 	SeeAlso:	Document
 *********************************************************************************************/

class BitmapExportDocument : public Document
{
public:		// Construction/initialisation

	BitmapExportDocument(BOOL fHide = TRUE);
	BOOL Init(KernelBitmap* pBitmap, const DocRect& RectToExport);

	BOOL SetBitmap(KernelBitmap* pBitmap);

protected:

	BOOL InitFailed(void);

	NodeBitmap* pBitmapNode;
	DocRect ExportRect;

	CC_DECLARE_DYNAMIC(BitmapExportDocument);
};

#endif
