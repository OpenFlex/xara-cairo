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

// Operation for doing an interactive scale of the selection

/*
*/


#include "camtypes.h"
#include "opscale2.h"

//#include "rik.h"
#include "selector.h"
//#include "clikdrag.h"
//#include "selstr.h"




// This is not compulsory, but you may as well put it in so that the correct version
// of your file can be registered in the .exe

// An implement to match the Declare in the .h file.
// If you have many classes, it is recommended to place them all together, here at the start of the file
//CC_IMPLEMENT_DYNCREATE(OpScale2Trans, OpScaleTrans)

// This will get Camelot to display the filename and linenumber of any memory allocations
// that are not released at program exit
#define new CAM_DEBUG_NEW








/********************************************************************************************

>	OpScale2Trans();

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/11/96
	Purpose:	default constructor

********************************************************************************************/

/*OpScale2Trans::OpScale2Trans()
	: OpScaleTrans()
{
}*/




/********************************************************************************************

>	virtual  ~OpScale2Trans();

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/11/96
	Purpose:	destructor

********************************************************************************************/

/*OpScale2Trans::~OpScale2Trans()
{
}*/




/********************************************************************************************

>	OpScale2Trans( const OpScale2Trans& );

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/11/96
	Purpose:	copy constructor

********************************************************************************************/
/*
OpScale2Trans::OpScale2Trans( const OpScale2Trans& Other )
	: OpScaleTrans( Other )
{
}
*/

/********************************************************************************************

>	OpScale2Trans&  operator=( const OpScale2Trans& );

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/11/96
	Purpose:	assignment operator:  delegates to virtual Assign()

********************************************************************************************/
/*
OpScale2Trans&  OpScale2Trans::operator=( const OpScale2Trans& Other )
{
	Assign( Other );

	return  *this;
}
*/



/********************************************************************************************

>	virtual	 OpScale2Trans*  Clone ()   const;

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/11/96
	Purpose:	clone function

********************************************************************************************/
/*
OpScale2Trans*  OpScale2Trans::Clone ()   const
{

   OpScale2Trans*  Clone  =  new OpScale2Trans( *this );

   if( !Clone )
      throw  "OpScale2Trans::Clone()\n\nCouldn't get memory for a OpScale2Trans\n";

   return  Clone;

}
*/



/********************************************************************************************

>	private: virtual void  Assign( const OpScale2Trans& );

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/11/96
	Purpose:	virtual assignment

********************************************************************************************/
/*
void  OpScale2Trans::Assign( const OpScale2Trans& Other )
{

	OpScaleTrans::operator=( Other );

}
*/



/********************************************************************************************

>	static BOOL OpScale2Trans::Declare()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/7/93
	Returns:	TRUE if all went OK, False otherwise
	Purpose:	Adds the operation to the list of all known operations

********************************************************************************************/

/*BOOL OpScale2Trans::Declare()
{
	return  RegisterOpDescriptor( 0, _R(IDS_SCALETRANS), CC_RUNTIME_CLASS(OpScale2Trans),
							      OPTOKEN_SCALE2, OpScaleTrans::GetState              );
}*/








/********************************************************************************************

>	virtual void  DoWithParam( OpDescriptor* pDescriptor,  OpParam* pOpParam )

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com> (adapted from Rik)
	Created:	6/11/97
	Inputs:		pDescriptor - The operations descriptor
				pOpParam    - The parameters for this operation
	Purpose:	override: slightly change to allow the scale factors setup and 
				operation execution to be delegated to a separate function - IterateToConvergence()
	See also:	TransOperation::DoWithParam()

********************************************************************************************/

/*void OpScale2Trans::DoWithParam( OpDescriptor*,  OpParam* pOpParam )
{

	// Get at my data
	TransformData* TransData = (TransformData*)(pOpParam->Param1);

	// copy across all the relavent bits of data for the transform
	CentreOfTrans 	= TransData->CentreOfTrans;
	LockAspect 		= TransData->LockAspect;
	LeaveCopy 		= TransData->LeaveCopy;
	ScaleLines 		= TransData->ScaleLines;
	TransFills 		= TransData->TransFills;
	TransformRange	= TransData->pRange;		// if NULL use the selection

	// It is not possible to move between spreads in an immediate operation
	CanChangeToNewSpread = FALSE;

	// Where was this operation started from, and are we interested
	SetStartBlob(TransData->StartBlob);

	// Find the Selection and fail if it is not there
	Selection = GetApplication()->FindSelection();
	if (Selection==NULL)
	{
		FailAndExecute();
		End();
		return;
	}


	/// a call to the extra bit
	IterateToConvergence( pOpParam );


	// mark the selection cache as invalid (bounding rects etc will no longer be correct)
	Selection->Update();


	// End the operation
	End();	

}*/




/********************************************************************************************

>	protected: virtual INT32 IterateToConvergence ( OpParam* pParam );

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/11/97
	Inputs:		pParam -  The parameters for this operation
	Returns:	dummy
	Purpose:	Calculate the scaling by iterative improvement
					1.	set scale & matrix, accumulate matrix
					2.	do a transform
					3.	compare resultant width with intended width
					4.  call to do the whole transform

********************************************************************************************/

/*INT32  OpScale2Trans::IterateToConvergence ( OpParam* pParam )
{

	const MILLIPOINT	IntendedWidth_k       =  ( (MILLIPOINT*)( pParam->Param2 ) )[0];
	const INT32			MaxWidthInaccuracy_k  =  (INT32)37;   // 0.05 * 1/96 inches (in millipoints) = 0.05 pixels
	const BOOL			OriginalSucceedAndDiscard_k  =  OpFlags.SucceedAndDiscard;
	const UINT32			MaxIterations_k       =  8;          // must be >= 1

	Matrix				AccumulatedScaling;      // default identity
	DocRect				BoundingRect          =  Selection->GetBoundingRect();
	INT32				WidthInaccuracy;
	Matrix				tmp;
	UINT32				i                     =  MaxIterations_k;



	/// do the iterations to calculate the whole transform

	OpFlags.SucceedAndDiscard  =  TRUE;   // suppress undo   // ???

	do
	{
		if( !InitTransformImmediate2( pParam,  BoundingRect ) )
			return  Failure( OriginalSucceedAndDiscard_k );
		BuildMatrix();

		/// check if the composition will underflow
		FIXED16   abcd[4];
		( tmp *= Transform ).GetComponents( abcd, 0 );
		if( abcd[0]  ==  0 )		break;
		else						AccumulatedScaling  =  tmp;


		if( !CompleteTransformation() )
			return  Failure( OriginalSucceedAndDiscard_k );
		Selection->Update();


		BoundingRect     =  Selection->GetBoundingRect();
		WidthInaccuracy  =  BoundingRect.Width() - IntendedWidth_k;
		if( WidthInaccuracy < 0 )   WidthInaccuracy  =  -WidthInaccuracy;
	}
	/// stop iterating when: iterated enough, width is accurate enough
	while(     ( --i )
	       &&  ( WidthInaccuracy > MaxWidthInaccuracy_k )  );



	/// now the scaling is calulated, it can be performed, almost straightforwardly
	ApplyAsSingleTransform( AccumulatedScaling,  OriginalSucceedAndDiscard_k );


	return  1;

}*/




/********************************************************************************************

  > protected: virtual INT32 OpScale2Trans::ApplyAsSingleTransform( Matrix& AccumulatedScaling,
                                                                  const BOOL OriginalSucceedAndDiscard_k )

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/11/97
	Inputs:		AccumulatedScaling           - the whole transform
				OriginalSucceedAndDiscard_k  - original undo flag
	Returns:	dummy
	Purpose:	1.	undo all iterated transforms, undo off
				2.	do the accumulated transform, undo set to original state
	SeeAlso:	OpScaleTrans::IterateToConvergence()

********************************************************************************************/

/*INT32 OpScale2Trans::ApplyAsSingleTransform( Matrix& AccumulatedScaling,  const BOOL OriginalSucceedAndDiscard_k )
{

	/// undo all the iterations

	Transform  =  AccumulatedScaling.Inverse();		// set  TransScaleFactor = YScaleFactor  ???

	if( !CompleteTransformation() )
		return  Failure( OriginalSucceedAndDiscard_k );

	Selection->Update();
	


	/// do the overall, correct scaling

	OpFlags.SucceedAndDiscard  =  OriginalSucceedAndDiscard_k;   // reset undo on/off choice
	Transform  =  AccumulatedScaling;				// set  TransScaleFactor = YScaleFactor  ???

	if( !CompleteTransformation() )
		return  Failure( OriginalSucceedAndDiscard_k );

	Selection->Update();



	return  1;

}*/




/********************************************************************************************

  >	protected: OpScale2Trans::Failure ( const BOOL OriginalSucceedAndDiscard_k );

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/11/97
	Inputs:		original undo flag
	Returns:	dummy
	Purpose:	acts like a 'catch' block:  general fail recovery

********************************************************************************************/

/*INT32	 OpScale2Trans::Failure ( const BOOL OriginalSucceedAndDiscard_k )
{

	OpFlags.SucceedAndDiscard  =  OriginalSucceedAndDiscard_k;   // reset undo on/off choice
	FailAndExecute();

	return  0;

}*/


			
			
/********************************************************************************************

  >	protected: virtual BOOL OpScale2Trans::InitTransformImmediate2( OpParam* pParam,  const DocRect& BoundingRect )

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/11/97
	Inputs:		pParam       -  The parameters for this operation
				BoundingRect -  (of the selection)
	Returns:	TRUE - all ok,  FALSE - fixed pt over/underflow
	Purpose:	override: calculate scale factors from the relative	change in size
	SeeAlso:	OpScaleTrans::InitTransformImmediate()

********************************************************************************************/

/*BOOL OpScale2Trans::InitTransformImmediate2( OpParam* pParam,  const DocRect& BoundingRect )
{
	/// Retrieve parameters
	MILLIPOINT*	pParams   =  (MILLIPOINT*)( pParam->Param2 );
	MILLIPOINT	Width     =  pParams[0];
	MILLIPOINT	Height    =  pParams[1];


	/// Calculate relative change in size
	double		fpXscale  =  (double)Width  / BoundingRect.Width();
	double		fpYscale  =  (double)Height / BoundingRect.Height();


	/// Check if the scale will under- or over-flow the fixed-point numbers used in the
	/// transform system.
	if( pSelTool->BeyondFixedRange(fpXscale) || pSelTool->BeyondFixedRange(fpYscale) )
	{
		TRACEUSER( "Harrison", _T("Under/overflow in OpScale2Trans::InitTransformImmediate\n"));
		//pInfoBarOp->ReportEditError(_R(IDS_SEL_ERROR_TOO_SMALL_OR_LARGE));
		ToolInformError(TOOLID_SELECTOR, _R(IDS_SEL_ERROR_TOO_SMALL_OR_LARGE));
		return  FALSE;
	}


	FIXED16 fxParams[2];
	fxParams[0]  =  fpXscale;
	fxParams[1]  =  fpYscale;

	OpScaleTrans::InitTransformImmediate( &OpParam((INT32)pParam->Param1, (INT32)fxParams) );


	return  TRUE;
}*/



