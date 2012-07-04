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


#ifndef INC_ALIGNDLG
#define INC_ALIGNDLG

#include "rnddlgs.h" 
#include "transop.h" 

#define OPTOKEN_ALIGNDLG _T("ArrangeAlignment")    
#define OPTOKEN_OPALIGN  _T("OpAlign")    

// enumeration of all possible alignments on each axis
enum AlignType
{
	AlignNone		=0,
	AlignLow		=1,		// ie left or bottom
	AlignCentre		=2,
	AlignHigh		=3,		// ie right or top
	DistributeLow	=4,		// ie left or bottom
	DistributeCentre=5,
	DistributeHigh	=6,		// ie right or top
	DistributeEqui	=7
};	

// enumeration of possible target areas
enum TargetType
{
	ToSelection=0,
	ToPage     =1,
	ToSpread   =2
};	

// struct for passing params to OpAlign::DoWithParam()
struct AlignParam
{
	AlignType  h;
	AlignType  v;
	TargetType target;
};

// struct to cache x or y info about object to be affected 
struct ObjInfo
{
	INT32 i;		// cross-ref to pre-sorted state
	INT32 lo;	// left(bottom) coord of object
	INT32 hi;	// right(top)   coord of object
};

// struct to hold 1 dimensional data (1D equivelent of Rect!)
struct LineData
{
	INT32 lo;	// start position of line (x or y)
	INT32 hi;	// end   position of line (x or y)
};

// number of rects in diagram on dialog
const INT32 DiagRects=4;

/****************************************************************************
>	class ArrangeAlignment: public DialogOp

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/09/94
	Purpose:	Align object dialog
****************************************************************************/

class ArrangeAlignment: public DialogOp
{         
	CC_DECLARE_DYNCREATE( ArrangeAlignment )  
public:
	ArrangeAlignment();	
	void				Do(OpDescriptor*);	     
	static  BOOL		Init();                        
	static  OpState		GetState(String_256*, OpDescriptor*);	
 	static  void 		CalcDiagramRectsOneAxis(
 							LineData x[8][DiagRects],
 							const INT32 width[DiagRects],
 							const INT32 order[DiagRects],
 							const INT32 gap[DiagRects-1],
 							const INT32 DiagWidth
 						);
	virtual	MsgResult	Message(Msg* Message);

	// positions of 4 diagram rectangles in all 8 alignments (x and y independent)
	static LineData DiagRectX[8][DiagRects];
	static LineData DiagRectY[8][DiagRects];

	static const	UINT32 IDD;     
	static const	CDlgMode Mode;

private:
	void	  UpdateState();
	void	  DialogOKed();
	void      RedrawDiagram(ReDrawInfoType* ExtraInfo);
	void      DiagramClicked(ReDrawInfoType* ExtraInfo);
	void	  BuildIDSDropList(const CGadgetID DropListID, const INT32* IDSList, INT32 Default);
	void	  SetRadioGroup( const CGadgetID* IDCList, const CGadgetID IDC);
	CGadgetID ReadRadioGroup(const CGadgetID* IDCList, const CGadgetID IDCDefault=NULL);

	static AlignParam Align;
}; 

/****************************************************************************
>	class OpAlign: public SelOperation

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/09/94
	Purpose:	Undo-able Op to Align objects
****************************************************************************/

class OpAlign: public TransOperation
{         
	CC_DECLARE_DYNCREATE(OpAlign)

public:
	OpAlign();	
	void	DoWithParam(OpDescriptor* pOp, OpParam* pAlignParam);	     
	static	BOOL Init();                        
	static	OpState GetState(String_256*, OpDescriptor*);

private:
	void AlignOneAxis(AlignType Align, INT32 NumObjs, XLONG SumObjWidths,
							   INT32 SelRectLow, INT32 SelRectHigh, ObjInfo* x, INT32* dx);
}; 

#endif
