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
// Header file for fimagdlg.cpp
//
// 

#ifndef INC_IMAGEMAPFILTERDLG
#define INC_IMAGEMAPFILTERDLG

//#include "dialogop.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "filtimop.h"
#include "bmpprefs.h"	//For SelectionType

//This constant is the maximum pixel width and height that we allow
//A million should be enough, I think...
const INT32 PIXELWIDTH_MAX = 1000000;

/********************************************************************************************

>	class ImagemapDlg : public DialogOp

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/3/97
	Purpose:	The imagemap filter's export options dialog.

********************************************************************************************/

#define OPTOKEN_IMAGEMAPDLG _T("ImagemapDlg")

class ImagemapDlg : public DialogOp
{
	CC_DECLARE_DYNCREATE(ImagemapDlg )

	//Constructors
public:
	ImagemapDlg();

	//Initialiser
public:
	static BOOL Init();

	//Function to start the dialog
public:
	static BOOL InvokeDialog(ImagemapFilterOptions* pifoDefault, List* plstNames=NULL);


	//Message handling functions
protected:
	void OnCreate();
	void OnCommit();
	void OnAreaSelectionClicked();
	void OnAreaDrawingClicked();
	void OnWidthChanged();
	void OnHeightChanged();

	//Toolkit functions
protected:
	void SetOptions(ImagemapFilterOptions ifoSet);
	ImagemapFilterOptions GetOptions();

	void SetDPI(SelectionType stExportArea, double dDPI);
	double GetDPI(SelectionType stExportArea);

	void SetMemberVariables(ImagemapFilterOptions ifoOptions);

	//Overridden virtual functions
public:
	void DoWithParam(OpDescriptor*, OpParam* Param); 
	void Do(OpDescriptor*); 						
						  	
	static OpState GetState(String_256*, OpDescriptor*);
													
	virtual MsgResult Message(Msg* Message);		

	//Our member variables
protected:
	static ImagemapFilterOptions ms_Options;
	static List* ms_plstNames;

	double m_dWidthHeightRatio;
	static BOOL DontHandleNextMessage;

	static BOOL DialogWasCancelled;

	
	//Compulsory static member variables
public:
	static CDlgResID IDD;		
	static const CDlgMode Mode;

};

#endif
