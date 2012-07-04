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


#ifndef INC_BFXPLUGINITEM
#define INC_BFXPLUGINITEM

#include "plugin.h"
#include "bfxmngr.h"
//#include "bfxrc.h"

class Progress;
class Document;
class OpDescriptor;

/**************************************************************************************

>	class BfxPlugIn : public PlugInItem

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/3/97
	Purpose:	Provides storage for details on a BFX plug-in. 

**************************************************************************************/

class BfxPlugIn : public PlugInItem
{
	// Declare the class for memory tracking
	CC_DECLARE_DYNAMIC(BfxPlugIn);

public:
	// Construction and destruction
	BfxPlugIn();
	~BfxPlugIn();

	// return a string describing a unique identifier for the plug-ins this handler is interested in
	virtual String_32 GetUniqueID() const; 
	// return a unique type for this kind of plug-in
	virtual TypeOfPlugIn GetTypeOfPlugIn() const;

	// Special BFX get dialog id function
	// Baseclass version is pure vitual to force defined classes to use it
	//virtual UINT32 GetDialogID()					= 0;
	virtual OpDescriptor * GetOpDescriptor()	= 0;

protected:

public:
	// Operations available
	// Find out about a plug-in
//	virtual BOOL About();

	// Applying the plug-in to a bitmap
	virtual BOOL Apply(KernelBitmap *pInputBitmap, Document* pDocument,
					   KernelBitmap **ppOutputBitmap = NULL);
//	virtual BOOL ApplyLastFilter(KernelBitmap *pInputBitmap, Document* pDocument,
//								 KernelBitmap **ppOutputBitmap = NULL);

	// Checking if a bitmap's colour depth is suitable
	virtual BOOL IsBitmapModeOk(INT32 ColourDepth, BOOL GreyScale);

protected:
	// Useful helper functions

	// If ApplyLast is True		- To call it to do its work on a bitmap
	// or if ApplyLast is True	- To call it to repeat its work on a bitmap
	virtual BOOL ApplyBitmapEffect(KernelBitmap *pInputBitmap, Document* pDocument, KernelBitmap **ppOutputBitmap = NULL);
//	virtual BOOL Apply(WinBitmap *pInputDIB, WinBitmap * pOutputDIB);
	//virtual BOOL ApplyPlugIn(BOOL ApplyLastFilter);
};

/**************************************************************************************

>	class BfxBrightnessContrast : public BfxPlugIn

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/3/97
	Purpose:	Provides storage for details on a BfxBrightnessContrast plug-in. 

**************************************************************************************/

class BfxBrightnessContrast : public BfxPlugIn
{
	// Declare the class for memory tracking
	CC_DECLARE_DYNAMIC(BfxBrightnessContrast);

public:
	// Construction and destruction
	BfxBrightnessContrast();

//	virtual UINT32 GetDialogID() { return _R(IDD_BFXPLUGINDLG_PG3); }
	virtual OpDescriptor * GetOpDescriptor();
};

/**************************************************************************************

>	class BfxSpecialEffects : public BfxPlugIn

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/3/97
	Purpose:	Provides storage for details on a BfxSpecialEffects plug-in. 

**************************************************************************************/

class BfxSpecialEffects : public BfxPlugIn
{
	// Declare the class for memory tracking
	CC_DECLARE_DYNAMIC(BfxSpecialEffects);

public:
	// Construction and destruction
	BfxSpecialEffects();

//	virtual UINT32 GetDialogID() { return _R(IDD_BFXPLUGINDLG_PG5); }
	virtual OpDescriptor * GetOpDescriptor();
};

/**************************************************************************************

>	class BfxResize : public BfxPlugIn

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/3/97
	Purpose:	Provides storage for details on a BfxResize plug-in. 

**************************************************************************************/

class BfxResize : public BfxPlugIn
{
	// Declare the class for memory tracking
	CC_DECLARE_DYNAMIC(BfxResize);

public:
	// Construction and destruction
	BfxResize();

//	virtual UINT32 GetDialogID() { return _R(IDD_BFXPLUGINDLG_PG3); }
	virtual OpDescriptor * GetOpDescriptor();
};

/**************************************************************************************

>	class BfxFlipAndRotate : public BfxPlugIn

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/3/97
	Purpose:	Provides storage for details on a BfxFlipAndRotate plug-in. 

**************************************************************************************/

class BfxFlipAndRotate : public BfxPlugIn
{
	// Declare the class for memory tracking
	CC_DECLARE_DYNAMIC(BfxFlipAndRotate);

public:
	// Construction and destruction
	BfxFlipAndRotate();

//	virtual UINT32 GetDialogID() { return _R(IDD_BFXPLUGINDLG_PG3); }
	virtual OpDescriptor * GetOpDescriptor();
};

/**************************************************************************************

>	class BfxColourDepth : public BfxPlugIn

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/3/97
	Purpose:	Provides storage for details on a BfxColourDepth plug-in. 

**************************************************************************************/

class BfxColourDepth : public BfxPlugIn
{
	// Declare the class for memory tracking
	CC_DECLARE_DYNAMIC(BfxColourDepth);

public:
	// Construction and destruction
	BfxColourDepth();

//	virtual UINT32 GetDialogID() { return _R(IDD_BFXPLUGINDLG_PG3); }
	virtual OpDescriptor * GetOpDescriptor();
};


#endif // INC_BFXPLUGINITEM
