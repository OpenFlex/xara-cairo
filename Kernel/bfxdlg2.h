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

// Header for bitmap effects dialog

#ifndef INC_BFXPLUGINDLG
#define INC_BFXPLUGINDLG

//#include "dialogop.h"
//#include <afxtempl.h>

class KernelBitmap;
class AccusoftBitmapEffect;
class OpDescriptor;
class BitmapInfo;
class OpParam;

/********************************************************************************************

>	class BfxPlugInDlg : public DialogTabOp

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	05/03/97
	Purpose:	Handles the dialog for bitmap effects
				From the tabbed form of the dialog in BfxPlugInDlg

********************************************************************************************/

#define OPTOKEN_BFXPLUGINDLG _T("BfxPlugInDlg")

#define OPTOKEN_BFXDLG_BRIGHTNESSCONTRAST	_T("BfxDlgBrightnessContrast")
#define OPTOKEN_BFXDLG_SPECIALEFFECTS		_T("BfxDlgSpecialEffects")
#define OPTOKEN_BFXDLG_RESIZE				_T("BfxDlgResize")
#define OPTOKEN_BFXDLG_FLIPROTATE			_T("BfxDlgFlipRotate")
#define OPTOKEN_BFXDLG_COLOURDEPTH			_T("BfxDlgColourDepth")

// main class definition
class BfxPlugInDlg : public DialogOp
{         
	CC_DECLARE_DYNCREATE( BfxPlugInDlg )  
public:

	BfxPlugInDlg(CDlgResID id = BfxPlugInDlg::IDD); 
	~BfxPlugInDlg();

	MsgResult Message( Msg* Message ); 
	 
	void Do(OpDescriptor*);		// "Do" function        
	void DoWithParam(OpDescriptor* pOp, OpParam* pParam);

	static BOOL Init();                        
	static OpState GetState(String_256*, OpDescriptor*);	

	static const CDlgMode Mode; 

	// We need to give our dialog's a unique resource ID as this is used to 
	static UINT32 IDD;

protected:
	
	INT32 Param1;
	INT32 Param2;
	INT32 Param3;
	double Matrix[9];

	// Message handlers for each page in the tabbed dialog
	void HandleFlipAndRotateMsg(DialogMsg* Msg, BOOL * pCommitValues, BOOL * pEndDialog); 
	void HandleResizeMsg(DialogMsg* Msg, BOOL * pCommitValues, BOOL * pEndDialog); 
	void HandleBrightnessAndContrastMsg(DialogMsg* Msg, BOOL * pCommitValues, BOOL * pEndDialog);
	void HandleDitherMsg(DialogMsg* Msg, BOOL * pCommitValues, BOOL * pEndDialog);
	void HandleSpecialEffectsMsg(DialogMsg* Msg, BOOL * pCommitValues, BOOL * pEndDialog);
	void HandleAlchemistMsg(DialogMsg* Msg, BOOL * pCommitValues, BOOL * pEndDialog);

	void Remove24BitTempCopy(); // Remove any 24bit copies of 32bit BMPs

	BOOL RenderBitmap(ReDrawInfoType* ExtraInfo, KernelBitmap * BitmapToUse);
	BOOL FixOriginalComboBox();
	BOOL ReadOriginalComboBox();
	BOOL SetParameters(INT32 p1=0, INT32 p2=0, INT32 p3=0)
					{ Param1=p1; Param2=p2; Param3=p3; return TRUE;};


	BOOL CheckOriginalBitmap();
	BOOL DestinationChanged();
	BOOL FindBitmap();
	BOOL OriginalChanged();
	BOOL ClearDestination(BOOL Redraw=TRUE);
	BOOL SetEffect(CCRuntimeClass * Effect);
	BOOL SetDirty(BOOL Redraw=TRUE);

	KernelBitmap * pOriginal;
	KernelBitmap * pDestination;
	KernelBitmap * pPrevOriginal;
	BitmapInfo * pOrigInfo;
	BOOL Clean;

	CList < String_256, String_256 > m_p24BitCopyNames;
	BOOL m_UseInitial;

	AccusoftBitmapEffect * pFX;

	CDlgResID OpenPage;

	static BOOL InteractiveBCC;	

	Document* m_pDocument;
	OpParam * m_pParam;
}; 
                 
// these just start up the correct dialog boxes
class BfxBrightnessContrastDlg : public BfxPlugInDlg
{
	CC_DECLARE_DYNCREATE( BfxBrightnessContrastDlg )  
public:
	BfxBrightnessContrastDlg();
};

class BfxSpecialEffectsDlg : public BfxPlugInDlg
{
	CC_DECLARE_DYNCREATE( BfxSpecialEffectsDlg )  
public:
	BfxSpecialEffectsDlg();
};

class BfxResizeDlg : public BfxPlugInDlg
{
	CC_DECLARE_DYNCREATE( BfxResizeDlg )  
public:
	BfxResizeDlg();
};

class BfxFlipAndRotateDlg : public BfxPlugInDlg
{
	CC_DECLARE_DYNCREATE( BfxFlipAndRotateDlg )  
public:
	BfxFlipAndRotateDlg();
};

class BfxColourDepthDlg : public BfxPlugInDlg
{
	CC_DECLARE_DYNCREATE( BfxColourDepthDlg )  
public:
	BfxColourDepthDlg();
};

#endif  // INC_BFXPLUGINDLG


