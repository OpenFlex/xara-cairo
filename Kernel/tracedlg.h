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

// Trace dialog

#ifndef INC_TRACEDLG
#define INC_TRACEDLG


// Find out about the DialogOp Class
//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "doccolor.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "undoop.h"
//#include "selop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "tracectl.h"
//#include <afxtempl.h>

class KernelBitmap;
class TraceControl;
class Spread;
class DocCoord;

#define OPTOKEN_TRACEDLG _T("TraceDlg")
#define OPTOKEN_TRACEOP _T("TraceOp")

enum TraceSetting { TRACESETTING_PASSES = 0,
					TRACESETTING_REMOVENOISE,
					TRACESETTING_MINIMUMAREA,
					TRACESETTING_INITIALCOLOURTOLERANCE,
					TRACESETTING_FINALCOLOURTOLERANCE,
					TRACESETTING_ACCURACY,
					TRACESETTING_SMOOTING,

					// the end
					TRACESETTING_ILLEGAL,
					NUM_TRACESETTING=TRACESETTING_ILLEGAL};

/*********************************************************************************************
>	class TraceMessage : public Msg

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/4/95
	Purpose:	This is a foolish message to bring up a tracer dialog
	SeeAlso:	BfxDlg

*********************************************************************************************/

class TraceMsg : public Msg
{
	CC_DECLARE_DYNAMIC(TraceMsg)
public:
	KernelBitmap * pBitmap;
	TraceMsg(KernelBitmap * pTheBitmap):pBitmap(pTheBitmap) { /* empty */ };
	static void OpenOrUse(KernelBitmap * pBitmap);
};

/********************************************************************************************

>	class TraceOp : public UndoableOperation

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/02/94
	Purpose:	Handles insertion of bitmap effect nodes into the tree

********************************************************************************************/

class CCAPI TraceOp: public SelOperation
{                             
	CC_DECLARE_DYNCREATE( TraceOp )
public:
	TraceOp();								// Constructor
	static BOOL		Init();					// Register an OpDescriptor
	                                        // Read the state of an operation
	static OpState	GetState(String_256*, OpDescriptor*);		
	void DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	BOOL FindCentreInsertionPosition(Spread** Spread, DocCoord* Position);
};

class TraceOpParam: public OpParam
{
	CC_DECLARE_MEMDUMP( TraceOpParam);
public:
	TraceControl * pTraceControl;
};
     

/********************************************************************************************

>	class TraceDlg : public DialogOp

	Author:		Alex_Bligh (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/12/94
	Purpose:	Dialog for tracer

********************************************************************************************/

class TraceDlg : public DialogOp
{
	// Give my name in memory dumps
	CC_DECLARE_DYNCREATE(TraceDlg);

public:
	// Construction etc
	TraceDlg();
	~TraceDlg();
	static	BOOL Init();

	// Called when the dialog is to be displayed
	void	Do(OpDescriptor*);
	void 	DoWithParam(OpDescriptor* pOp, OpParam* pParam);
	virtual	MsgResult Message(Msg* Message);

	// Find out about the state of the dlg
	static	OpState GetState(String_256*, OpDescriptor*);
	
protected:
	BOOL RenderBitmap(ReDrawInfoType* ExtraInfo, KernelBitmap * BitmapToUse);
	BOOL FindBitmap();

	BOOL LoadSettings(INT32 * pSettings);
	BOOL SaveSettings(INT32 * pSettings);
	BOOL ReadParams();
	BOOL WriteParams();
	BOOL SetStatus(BOOL Tracing=FALSE);

	BOOL DoTrace(BOOL SingleStep);
	BOOL FixOriginalComboBox();
	BOOL ReadOriginalComboBox();
	BOOL CheckOriginalBitmap();
	BOOL DestinationChanged();
	BOOL OriginalChanged();

	BOOL SetTraceMethod(TraceMethod Method);
	TraceMethod GetTraceMethod();

	std::list< String_256 > m_p24BitCopyNames;
	void Remove24BitTempCopy(); // Remove any 24bit copies of 32bit BMPs

public:
	// Vars
	static const UINT32 IDD;
	static const CDlgMode Mode;

protected:

	KernelBitmap * pOriginal;
	KernelBitmap * pPrevOriginal;
	TraceControl * pTraceControl;

	static INT32 DefaultMode;
	static INT32 DefaultSetting[NUM_TRACEMETHOD][NUM_TRACESETTING];
	static INT32 FactorySetting[NUM_TRACEMETHOD][NUM_TRACESETTING];

};

#endif  // INC_TRACEDLG


