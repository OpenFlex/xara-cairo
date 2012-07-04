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


// 

#ifndef	INC_MAKEBMP
#define	INC_MAKEBMP

//#include "selop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "giffiltr.h"

#define OPTOKEN_CONVERTTOBITMAP _T("ConvertToBitmap")	

/********************************************************************************************

>	class OpConvertToBitmap: public SelOperation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/2/95
	Purpose:	Converts objects into a bitmap
	SeeAlso:	-

********************************************************************************************/

class CCAPI OpConvertToBitmap: public SelOperation
{         
	CC_DECLARE_DYNCREATE( OpConvertToBitmap );

public:
	OpConvertToBitmap();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }
};  



/********************************************************************************************

>	class MakeBitmapExportOptions : public MaskedFilterExportOptions

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/10/96
	Purpose:   	Allows "Create Bitmap Copy" to provide own defaults

********************************************************************************************/
class MakeBitmapExportOptions : public MaskedFilterExportOptions
{
CC_DECLARE_DYNCREATE(MakeBitmapExportOptions)

public:
	static BOOL Declare();

	// default constructor, fairly useful at the best of times.
	MakeBitmapExportOptions() {} // Do nothing for now

    MakeBitmapExportOptions(const FilterType FilterID, const StringBase* pFilterName);

	virtual BOOL	RetrieveDefaults();
	virtual BOOL	SetAsDefaults() const;

	// for object copying and comparing
	BitmapExportOptions *MakeCopy();
	virtual BOOL CopyFrom(BitmapExportOptions *pOther);
//	virtual BOOL Equal(BitmapExportOptions *pOther);

protected:
	// Persistant buffer
	static DPI			g_Dpi;
	static BMP_DEPTH	g_Depth;
	static DITHER		g_Dither;
	static PALETTE		g_Palette;
	static BOOL			g_TranspBkGnd;
};


/********************************************************************************************

>	class MakeBitmapFilter : public TI_GIFFilter

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/96
	Purpose:	Special filter used to convert the selection into a bitmap

********************************************************************************************/

class MakeBitmapFilter : public TI_GIFFilter
{
	CC_DECLARE_DYNAMIC(MakeBitmapFilter);
	
public:
	MakeBitmapFilter();

	// Check if this Bitmap filter can cope with saving at this Bpp/Colour depth
	virtual BOOL IsThisBppOk(UINT32 Bpp);
	virtual UINT32 GetExportMsgID();

	BOOL DoCreateBitmap(Operation *pOp, Document *pDoc, KernelBitmap** ppBitmap);
	BOOL InsertBitmapIntoDocument(UndoableOperation *pOp, KernelBitmap* KernelBmp, Document* DestDoc);

	static BOOL FindCentreInsertionPosition(Spread** Spread, DocCoord* Position);
	static BOOL Initialise();

protected:
	//
	// Export related functions
	//
	virtual BitmapExportOptions*	CreateExportOptions() const;
	virtual BOOL GetExportOptions(BitmapExportOptions* pOptions);
	virtual void CleanUpAfterExport();
	virtual BOOL WriteToFile( BOOL End );
	virtual BOOL EndWriteToFile( );

	virtual KernelBitmap* GetTheBitmap(BitmapExportOptions *pExportOptions);

	KernelBitmap* pTheBitmap;
	static FilterType s_FilterType;
};

#endif
