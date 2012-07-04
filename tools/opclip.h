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
// Declaration of ClipView operations.
//

#ifndef INC_OPCLIP
#define INC_OPCLIP

#define OPTOKEN_APPLY_CLIPVIEW _T("ApplyClipView")
#define OPTOKEN_REMOVE_CLIPVIEW _T("RemoveClipView")

//#include "selop.h"

/********************************************************************************************

>	class OpApplyClipView : public SelOperation

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Purpose:	Operation to apply ClipView to the selection.
	See also:	

********************************************************************************************/
class OpApplyClipView : public SelOperation
{
// Give my name out in memory dumps.
CC_DECLARE_DYNCREATE(OpApplyClipView);

/////////////////////////////////////////////////////////////////////////////////////////////
//
//	Member functions.
//

public:
	// constructor, destructor & initialisation.
	OpApplyClipView();
	~OpApplyClipView();
	static BOOL Init();

	// query the op for information about itself.
	static OpState GetState(String_256* pstrDescription, OpDescriptor* pOpDesc);
	virtual void GetOpName(String_256* pstrOpName);

	// the Op's Do() function.
	virtual void Do(OpDescriptor* pOpDesc);

	// whether or not the Op may change the bounds of some nodes.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }



/////////////////////////////////////////////////////////////////////////////////////////////
//
//	Member variables.
//

};



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------



/********************************************************************************************

>	class OpRemoveClipView : public SelOperation

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01 February 2000
	Purpose:	Operation to take apart the selected ClipView object.

	NOTE:		Should this Op be able to operate on multiple clipview structures?

	See also:	

********************************************************************************************/
class OpRemoveClipView : public SelOperation
{
// Give my name out in memory dumps.
CC_DECLARE_DYNCREATE(OpRemoveClipView);

/////////////////////////////////////////////////////////////////////////////////////////////
//
//	Member functions.
//

public:
	// constructor, destructor & initialisation.
	OpRemoveClipView();
	~OpRemoveClipView();
	static BOOL Init();

	// query the op for information about itself.
	static OpState GetState(String_256* pstrDescription, OpDescriptor* pOpDesc);
	virtual void GetOpName(String_256* pstrOpName);

	// the Op's Do() function.
	virtual void Do(OpDescriptor* pOpDesc);

	// whether or not the Op may change the bounds of some nodes.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }



/////////////////////////////////////////////////////////////////////////////////////////////
//
//	Member variables.
//

};



#endif	// INC_OPCLIP
