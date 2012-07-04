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

#ifndef _INC_WEB_PARAM_H
#define _INC_WEB_PARAM_H

#include "bmpprefs.h"

/********************************************************************************************

>	class WebPrefsDlgParam : public OpParam

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>	
	Created:	1/5/96
	Purpose:	Allows data to be passed into the export web preference dialog box and 
				then returned to the caller.
	
********************************************************************************************/

class WebPrefsDlgParam : public OpParam
{

CC_DECLARE_MEMDUMP(WebPrefsDlgParam);

public:
    // Default constructor, set up some useful defaults
	WebPrefsDlgParam();
	
// WEBSTER - markn 28/1/97
// Added access functions, and the Convert blends to outlines flag

	void SetBmpCompression(INT32 BmpComp)		{ BmpCompression = BmpComp; };		// Bitmap compression flag 
	void SetCompression(BOOL Comp)			{ Compression = Comp; };			// File compression flag 
	void SetExportPreviewBitmap(BOOL b)		{ ExportPreviewBitmap = b; };		// Export preview bitmap
	void SetConvertTextToOutlines(BOOL b)	{ ConvertTextToOutlines = b; };		// Convert text to outlines
	void SetConvertBlendsToOutlines(BOOL b) { ConvertBlendsToOutlines = b; };	// Convert blends to outlines
	void SetRemoveInvisibleLayers(BOOL b)	{ RemoveInvisibleLayers = b; };		// whether invisible layers should be removed or not
	void SetRemoveUnusedColours(BOOL b)		{ RemoveUnusedColours = b; };		// whether unused colours should be removed or not
	void SetMinimalWebFormat(BOOL b)		{ MinimalWebFormat = b; };			// whether we use our minimal web format or not
	void SetExportSel(SelectionType Type)	{ ExportSel = Type; };				// Export spread, drawing or selection 
	void SetViewportSel(SelectionType Type)	{ ViewportSel = Type; };			// Viewport as spread, drawing or selection 
	void SetHTMLToClipboard(BOOL Ok)		{ HTMLToClipboard = Ok; };			// whether an HTML tag should be exported to the clipboard
	void SetWebOk(BOOL Ok)					{ WebOk = Ok; };					// Ok or cancel selected 
	

	INT32				GetBmpCompression()				{ return BmpCompression; };				// Bitmap compression flag 
	BOOL			GetCompression()				{ return Compression; };				// File compression flag 
	BOOL			GetExportPreviewBitmap()		{ return ExportPreviewBitmap; };		// Export preview bitmap
	BOOL			GetConvertTextToOutlines()		{ return ConvertTextToOutlines; };		// Convert text to outlines
	BOOL			GetConvertBlendsToOutlines()	{ return ConvertBlendsToOutlines; };	// Convert blends to outlines
	BOOL			GetRemoveInvisibleLayers()		{ return RemoveInvisibleLayers; };		// whether invisible layers should be removed or not
	BOOL			GetRemoveUnusedColours()		{ return RemoveUnusedColours; };		// whether unused colours should be removed or not
	BOOL			GetMinimalWebFormat()			{ return MinimalWebFormat; };			// whether we use our minimal web format or not
	SelectionType	GetExportSel()					{ return ExportSel; };					// Export spread, drawing or selection 
	SelectionType	GetViewportSel()				{ return ViewportSel; };				// Viewport spread, drawing or selection 
	BOOL			GetHTMLToClipboard()			{ return HTMLToClipboard; };			// Whether an HTML tag should be exported to the clipboard
	BOOL			GetWebOk()						{ return WebOk; };						// Ok or cancel selected 
	
private:
	// Parameters that the dialog can set
	INT32 BmpCompression;				// Bitmap compression flag 
	BOOL Compression;				// File compression flag 
	BOOL ExportPreviewBitmap;		// Export preview bitmap
	BOOL ConvertTextToOutlines;		// Convert text to outlines
	BOOL ConvertBlendsToOutlines;	// Convert blends to outlines
	BOOL RemoveInvisibleLayers;		// whether invisible layers should be removed or not
	BOOL RemoveUnusedColours;		// whether unused colours should be removed or not
	BOOL MinimalWebFormat;			// whether we use our minimal web format or not
	BOOL HTMLToClipboard;			// whether we should export an HTML tag to the clipboard
	
	SelectionType ExportSel;		// Export spread, drawing or selection 
	SelectionType ViewportSel;		// Export spread, drawing or selection 

	BOOL WebOk;						// Ok or cancel selected 
};


#endif // _INC_WEB_PARAM_H
