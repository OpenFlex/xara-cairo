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

// Header file and class definition of the interactive Scale operation

#ifndef INC_OPSCALE2
#define INC_OPSCALE2


#include "opscale.h"

//#define OPTOKEN_SCALE2 "Scale2"








/********************************************************************************************

>	class OpScale2Trans  : public OpScaleTrans

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/11/97
	Purpose:	Alternative interactive and immediate scale operation, an implementation to
				to overcome innacurate (horizontal, line-scaled) scaling
	See also:	OpScaleTrans

********************************************************************************************/

/*
class OpScale2Trans  : public OpScaleTrans
{
	// Give my name in memory dumps
	CC_DECLARE_DYNCREATE(OpScale2Trans);

public: //----------------------------------------------------------------------

/// standard object management -----------------------------

							OpScale2Trans();
	virtual					~OpScale2Trans();
	//						OpScale2Trans( const OpScale2Trans& );
	//		OpScale2Trans&	operator=    ( const OpScale2Trans& );

/// --------------------------------------------------------



/// These functions required for the OpDescriptor class

	static	BOOL	Declare();

/// override

	virtual void	DoWithParam( OpDescriptor*,  OpParam* );

/// clone

   //virtual	OpScale2Trans*	Clone ()									const;


protected: //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--

/// 

	virtual	BOOL	InitTransformImmediate2 ( OpParam*,  const DocRect& );

/// inherit

	//virtual	void	InitTransformImmediate ( OpParam* );
	//virtual	void	InitTransformOnDrag(DocCoord, ClickModifiers);
	//virtual	void	UpdateTransformOnDrag(DocCoord, Spread*, ClickModifiers&);
	//virtual	void	BuildMatrix();
	//virtual	void	ConstrainDrag(DocCoord*);
	//virtual	void	UpdateTransformBoundingData();

	//virtual	void	SetStartBlob(INT32 ThisStartBlob) { StartBlob = ThisStartBlob; }


/// virtual assignment

	//virtual	void	Assign( const OpScale2Trans& );
	
///

	virtual	INT32		IterateToConvergence ( OpParam* );
	virtual INT32		ApplyAsSingleTransform ( Matrix& AccumulatedScaling,
                                             const BOOL OriginalSucceedAndDiscard_k );
			INT32		Failure ( const BOOL OriginalSucceedAndDiscard_k );


private: ///////////////////////////////////////////////////////////////////////

};
*/




#endif  // INC_OPSCALE2

