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

/*

	lattrops.h

	Line-attribute operations.
*/

#ifndef LATTROPS_H
#define LATTROPS_H

//#include "opdesc.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "la_base.h"
//#include "selop.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#define OPTOKEN_CHANGE_LINE_JOIN	TEXT("ChangeLineJoin")
#define OPTOKEN_CHANGE_LINE_CAP		TEXT("ChangeLineCap")

#ifdef ARROWHEADS
#define OPTOKEN_CHANGE_START_ARROW_EXTENDS TEXT("ChangeStartArrowExtends")
#define OPTOKEN_CHANGE_END_ARROW_EXTENDS TEXT("ChangeEndArrowExtends")
#endif


/********************************************************************************************
>	class OpChangeLineJoinOpDesc : public OpChangeLineAttribOpDesc

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/3/95

	Purpose:	OpDescriptor to allow the user to change the join-type of all selected
				objects, or to set the AttributeManager's current join-type attribute if 
				no objects are selected.
********************************************************************************************/

class OpChangeLineJoinOpDesc : public OpChangeLineAttribOpDesc
{
public:
	// Registration.
	static BOOL Init();

	// Creation & destruction.
	OpChangeLineJoinOpDesc();   

private:
	// Implementation.
	virtual CCRuntimeClass* GetAttribRuntimeClass() const;
	virtual UINT32 ConvertAttribToStringID(NodeAttribute* pAttr) const;
	virtual UINT32 GetItemStringID(INT32 nIndex) const;
	virtual NodeAttribute* GetNewAttrib(INT32 nItemIndex) const;
};



/********************************************************************************************
>	class OpChangeLineCapOpDesc : public OpChangeLineAttribOpDesc

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/3/95

	Purpose:	OpDescriptor to allow the user to change the join-type of all selected
				objects, or to set the AttributeManager's current join-type attribute if 
				no objects are selected.
********************************************************************************************/

class OpChangeLineCapOpDesc : public OpChangeLineAttribOpDesc
{
public:
	// Registration.
	static BOOL Init();

	// Creation & destruction.
	OpChangeLineCapOpDesc();   

private:
	// Implementation.
	virtual CCRuntimeClass* GetAttribRuntimeClass() const;
	virtual UINT32 ConvertAttribToStringID(NodeAttribute* pAttr) const;
	virtual UINT32 GetItemStringID(INT32 nIndex) const;
	virtual NodeAttribute* GetNewAttrib(INT32 nItemIndex) const;
};

#ifdef ARROWHEADS

/********************************************************************************************
>	class OpChangeStartArrowExtendsDesc : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/3/95

	Purpose:	Toggles the selected arrow attributes from being tagged onto the end of
				the line to not extending the line
********************************************************************************************/

class OpChangeStartArrowExtendsDesc : public SelOperation
{
CC_DECLARE_DYNCREATE(OpChangeStartArrowExtendsDesc)
public:
	// Creation & destruction.
	OpChangeStartArrowExtendsDesc();   

	virtual void Do(OpDescriptor *pOpDesc);
	
	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

private:
};

/********************************************************************************************
>	class OpChangeEndArrowExtendsDesc : public SelOperation

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/3/95

	Purpose:	Toggles the selected arrow attributes from being tagged onto the end of
				the line to not extending the line
********************************************************************************************/

class OpChangeEndArrowExtendsDesc : public SelOperation
{
CC_DECLARE_DYNCREATE(OpChangeEndArrowExtendsDesc)
public:
	// Creation & destruction.
	OpChangeEndArrowExtendsDesc();   

	virtual void Do(OpDescriptor *pOpDesc);
	
	// These functions required for the OpDescriptor class
	static BOOL Declare();
	static OpState GetState(String_256* Description, OpDescriptor*);

private:
};

#endif

#endif	// !LATTROPS_H
