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

#ifndef INC_BFXDLG
#define INC_BFXDLG

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "undoop.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#define OPTOKEN_BFXOP _T("BfxOp")

class KernelBitmap;
class AccusoftBitmapEffect;
class OpDescriptor;
class BitmapInfo;
class Spread;
class DocCoord;


/*********************************************************************************************
>	class BfxMessage : public Msg

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/4/95
	Purpose:	This is a foolish message to bring up a bitmap effects dialog
	SeeAlso:	BfxDlg

*********************************************************************************************/

class BfxMsg : public Msg
{
	CC_DECLARE_DYNAMIC(BfxMsg)
public:
	KernelBitmap * pBitmap;
	BfxMsg(KernelBitmap * pTheBitmap):pBitmap(pTheBitmap) { /* empty */ };
	static void OpenOrUse(KernelBitmap * pBitmap);
};


/********************************************************************************************

>	class BfxDlg : public UndoableOperation

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/02/94
	Purpose:	Handles insertion of bitmap effect nodes into the tree

********************************************************************************************/

class CCAPI BfxOp: public UndoableOperation
{                             
	CC_DECLARE_DYNCREATE( BfxOp )
public:
	BfxOp();								// Constructor
	static BOOL		Init();					// Register an OpDescriptor
	                                        // Read the state of an operation
	static OpState	GetState(String_256*, OpDescriptor*);		
	void	DoWithParam(OpDescriptor* pOp, OpParam* pParam);	     
protected:
	BOOL FindCentreInsertionPosition(Spread** Spread, DocCoord* Position);
};

class BfxOpParam: public OpParam
{
	CC_DECLARE_MEMDUMP( BfxOpParam);
public:
	KernelBitmap * * ppBitmap;
};
     

/********************************************************************************************

>	class BfxDlg : public DialogTabOp

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/02/94
	Purpose:	Handles the dialog for bitmap effects

********************************************************************************************/

#define OPTOKEN_BFXDLG _T("BfxDlg")    
   
class BfxDlg: public DialogTabOp
{         
	CC_DECLARE_DYNCREATE( BfxDlg )  
public:

	BfxDlg(); 
	~BfxDlg();

	MsgResult Message( Msg* Message ); 
	 
	void Do(OpDescriptor*);		// "Do" function        
	void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	static BOOL Init();                        
	static OpState GetState(String_256*, OpDescriptor*);	
	virtual BOOL RegisterYourPagesInOrderPlease(); 
	static const CDlgMode Mode; 

	// We need to give our Tab dialog's a unique resource ID as this is used to 
	static const UINT32 IDD;

	private:
	
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

	AccusoftBitmapEffect * pFX;

	CDlgResID OpenPage;

	static BOOL InteractiveBCC;	
}; 
                   

#endif  // INC_BFXDLG


