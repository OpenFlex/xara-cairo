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

*/

#include "camtypes.h"
#include "lattrops.h"
#include "lineattr.h"
#include "attrappl.h"
//#include "resource.h"
//#include "barsdlgs.h"
//#include "mario.h"
//#include "simon.h"
//#include "justin.h"

#ifdef ARROWHEADS
CC_IMPLEMENT_DYNCREATE(OpChangeStartArrowExtendsDesc, SelOperation)
CC_IMPLEMENT_DYNCREATE(OpChangeEndArrowExtendsDesc, SelOperation)
#endif

#define new CAM_DEBUG_NEW


/********************************************************************************************
>	static BOOL OpChangeLineJoinOpDesc::Init()

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/4/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Registers the OpChangeLineJoinOpDesc operation descriptor.
	Errors:		-
	SeeAlso:	LineSGallery::Init
********************************************************************************************/

BOOL OpChangeLineJoinOpDesc::Init()
{
	return (new OpChangeLineJoinOpDesc) != NULL;
}
    


/********************************************************************************************
>	OpChangeLineJoinOpDesc::OpChangeLineJoinOpDesc()
	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/3/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Simply calls the OpChangeLineAttribOpDesc base class constructor, passing
				appropriate arguments.
	Errors:		-
	SeeAlso:	UndoableOpDescriptor::UndoableOpDescriptor
********************************************************************************************/

OpChangeLineJoinOpDesc::OpChangeLineJoinOpDesc()
  :	OpChangeLineAttribOpDesc(_R(IDS_CHANGE_LINE_JOIN),
  							 OPTOKEN_CHANGE_LINE_JOIN,
  							 _R(IDBBL_CHANGE_LINE_JOIN),
  							 _R(IDLB_JOINTYPE_LIST_BOX))
{
	// Empty.
}



/********************************************************************************************
>	virtual CCRuntimeClass* OpChangeLineJoinOpDesc::GetAttribRuntimeClass() const

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/4/95
	Inputs:		-
	Outputs:	-
	Returns:	The run-time class of the AttrJoinType line attribute.
	Purpose:	
	Errors:		-
	SeeAlso:	-
********************************************************************************************/

CCRuntimeClass* OpChangeLineJoinOpDesc::GetAttribRuntimeClass() const
{
	return CC_RUNTIME_CLASS(AttrJoinType);
}



/********************************************************************************************
>	virtual UINT32 OpChangeLineJoinOpDesc::ConvertAttribToStringID(NodeAttribute* pAttr) const

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/4/95
	Inputs:		pAttr		the attribute to "convert"
	Outputs:	-
	Returns:	A string ID describing the given attribute.
	Purpose:	Called by the OpChangeLineAttribOpDesc base class when it wants to get
				a string describing the given attribute.
	Errors:		-
	SeeAlso:	-
********************************************************************************************/

UINT32 OpChangeLineJoinOpDesc::ConvertAttribToStringID(NodeAttribute* pAttr) const
{
	UINT32 nTxtID;
	switch (((AttrJoinType*) pAttr)->Value.JoinType)
	{
	case MitreJoin:
		nTxtID = _R(IDS_JOINTYPE_MITRE);
		break;

	case RoundJoin:
		nTxtID = _R(IDS_JOINTYPE_ROUND);
		break;

	case BevelledJoin:
		nTxtID = _R(IDS_JOINTYPE_BEVEL);
		break;

	default:
		nTxtID = 0;
		break;
	}
	
	return nTxtID;
}



/********************************************************************************************
>	virtual UINT32 OpChangeLineJoinOpDesc::GetItemStringID(INT32 nItemIndex) const

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/4/95
	Inputs:		A combo-box position index (ie. 0, 1, 2, 3, ...)
	Outputs:	-
	Returns:	The string ID of the item in the combo at the given position, or 0 if there
				isn't one.
	Purpose:	Called by the OpChangeLineAttribOpDesc base class when it wants the string
				to insert at the given position in the combo.
	Errors:		-
	SeeAlso:	-
********************************************************************************************/

UINT32 OpChangeLineJoinOpDesc::GetItemStringID(INT32 nItemIndex) const
{
	static UINT32 nStringID[] =
	{
		_R(IDS_JOINTYPE_MITRE),
		_R(IDS_JOINTYPE_ROUND),
		_R(IDS_JOINTYPE_BEVEL),
		0
	};

	return nStringID[nItemIndex];
}



/********************************************************************************************
>	virtual NodeAttribute* OpChangeLineJoinOpDesc::GetNewAttrib(INT32 nItemIndex) const

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/4/95
	Inputs:		nItemIndex		the index position within the combo the user has selected
	Outputs:	-
	Returns:	A pointer to an attribute corresponding to the given index position.
	Purpose:	Called by the OpChangeLineAttribOpDesc base class when it wants to create
				an attribute.
	Errors:		-
	SeeAlso:	-
********************************************************************************************/

NodeAttribute* OpChangeLineJoinOpDesc::GetNewAttrib(INT32 nItemIndex) const
{
	AttrJoinType* pAttr = new AttrJoinType;
	if (pAttr != NULL) pAttr->Value.JoinType = (JointType) nItemIndex;
	return pAttr;
}



/********************************************************************************************
>	static BOOL OpChangeLineCapOpDesc::Init()

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/4/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Registers the OpChangeLineCapOpDesc operation descriptor.
	Errors:		-
	SeeAlso:	LineSGallery::Init
********************************************************************************************/

BOOL OpChangeLineCapOpDesc::Init()
{
	return (new OpChangeLineCapOpDesc) != NULL;
}
    


/********************************************************************************************
>	OpChangeLineCapOpDesc::OpChangeLineCapOpDesc()
	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/3/95
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Simply calls the OpChangeLineAttribOpDesc base class constructor, passing
				appropriate arguments.
	Errors:		-
	SeeAlso:	UndoableOpDescriptor::UndoableOpDescriptor
********************************************************************************************/

OpChangeLineCapOpDesc::OpChangeLineCapOpDesc()
  :	OpChangeLineAttribOpDesc(_R(IDS_CHANGE_LINE_CAP),
  							 OPTOKEN_CHANGE_LINE_CAP,
  							 _R(IDBBL_CHANGE_LINE_CAP),
  							 _R(IDLB_LINECAP_LIST_BOX))
{
	// Empty.
}



/********************************************************************************************
>	virtual CCRuntimeClass* OpChangeLineCapOpDesc::GetAttribRuntimeClass() const

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/4/95
	Inputs:		-
	Outputs:	-
	Returns:	The run-time class of the AttrJoinType line attribute.
	Purpose:	
	Errors:		-
	SeeAlso:	-
********************************************************************************************/

CCRuntimeClass* OpChangeLineCapOpDesc::GetAttribRuntimeClass() const
{
	return CC_RUNTIME_CLASS(AttrStartCap);
}



/********************************************************************************************
>	virtual UINT32 OpChangeLineCapOpDesc::ConvertAttribToStringID(NodeAttribute* pAttr) const

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/4/95
	Inputs:		pAttr		the attribute to "convert"
	Outputs:	-
	Returns:	A string ID describing the given attribute.
	Purpose:	Called by the OpChangeLineAttribOpDesc base class when it wants to get
				a string describing the given attribute.
	Errors:		-
	SeeAlso:	-
********************************************************************************************/

UINT32 OpChangeLineCapOpDesc::ConvertAttribToStringID(NodeAttribute* pAttr) const
{
	UINT32 nTxtID;
	switch (((AttrStartCap*) pAttr)->Value.StartCap)
	{
	case LineCapButt:
		nTxtID = _R(IDS_CAPTYPE_BUTT);
		break;

	case LineCapRound:
		nTxtID = _R(IDS_CAPTYPE_ROUND);
		break;

	case LineCapSquare:
		nTxtID = _R(IDS_CAPTYPE_SQUARE);
		break;

	default:
		nTxtID = 0;
		break;
	}
	
	return nTxtID;
}



/********************************************************************************************
>	virtual UINT32 OpChangeLineCapOpDesc::GetItemStringID(INT32 nItemIndex) const

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/4/95
	Inputs:		A combo-box position index (ie. 0, 1, 2, 3, ...)
	Outputs:	-
	Returns:	The string ID of the item in the combo at the given position, or 0 if there
				isn't one.
	Purpose:	Called by the OpChangeLineAttribOpDesc base class when it wants the string
				to insert at the given position in the combo.
	Errors:		-
	SeeAlso:	-
********************************************************************************************/

UINT32 OpChangeLineCapOpDesc::GetItemStringID(INT32 nItemIndex) const
{
	static UINT32 nStringID[] =
	{
		_R(IDS_CAPTYPE_BUTT),
		_R(IDS_CAPTYPE_ROUND),
		_R(IDS_CAPTYPE_SQUARE),
		0
	};

	return nStringID[nItemIndex];
}



/********************************************************************************************
>	virtual NodeAttribute* OpChangeLineCapOpDesc::GetNewAttrib(INT32 nItemIndex) const

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/4/95
	Inputs:		nItemIndex		the index position within the combo the user has selected
	Outputs:	-
	Returns:	A pointer to an attribute corresponding to the given index position.
	Purpose:	Called by the OpChangeLineAttribOpDesc base class when it wants to create
				an attribute.
	Errors:		-
	SeeAlso:	-
********************************************************************************************/

NodeAttribute* OpChangeLineCapOpDesc::GetNewAttrib(INT32 nItemIndex) const
{
	AttrStartCap* pAttr = new AttrStartCap;
	if (pAttr != NULL) pAttr->Value.StartCap = (LineCapType) nItemIndex;
	return pAttr;
}

#ifdef ARROWHEADS
/********************************************************************************************
>	OpChangeStartArrowExtendsDesc::OpChangeStartArrowExtendsDesc()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com> & Olivier
	Created:	21/11/96
	Purpose:	Constructor.
********************************************************************************************/
OpChangeStartArrowExtendsDesc::OpChangeStartArrowExtendsDesc()
{
	//TRACEUSER( "MarkH", _T("Just Made a OpChangeStartArrowExtendsDesc Class!\n"));
}



/********************************************************************************************
>	virtual void OpChangeArrowStartExtendsDesc::Do(OpDescriptor *pOpDesc)

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com> & Olivier
	Created:	21/11/96
	Inputs:		pOpDesc - OpDescriptor - unused
	Outputs:	-
	Returns:	-
	Purpose:	The do function.  Inverts the arrow behaviour
********************************************************************************************/
void OpChangeStartArrowExtendsDesc::Do(OpDescriptor *pOpDesc)
{
	TRACEUSER( "DavidM", _T("OpChangeStartArrowExtendsDesc::Do !\n"));

	// ok, start the sel op
	// get the current selection
	SelRange* pSel = GetApplication()->FindSelection();

	// DoStartSelOp(TRUE);

	NodeListItem* pNodeListItem = NULL;

	// make a node list
	List * pSelList = NULL;

	pSelList = pSel->MakeListOfNodes(FALSE);

	Node * pNode = NULL;

	pNodeListItem = (NodeListItem *)pSelList->GetHead();

	AttrStartArrow * pNewAttrStartArrow = NULL;
	AttrStartArrow * pAttrStartArrow = NULL;
	
	AttrEndArrow * pNewAttrEndArrow = NULL;
	AttrEndArrow * pAttrEndArrow = NULL;
	NodeRenderableBounded * pParent = NULL;

	NodeHidden * pHidden = NULL;

	// run the the list finding arrow attributes, and invert them
	while (pNodeListItem)
	{
		pNode = pNodeListItem->pNode;

		if (pNode)
		{
			if (pNode->IsKindOf(CC_RUNTIME_CLASS(NodeRenderableInk)))
			{
				// make a copy of the node, and pass this to the attribute manager !
				pAttrStartArrow = (AttrStartArrow *)pNode->FindFirstChild(CC_RUNTIME_CLASS(AttrStartArrow));

				if (pAttrStartArrow)
				{
					// make a copy of the attribute & invert its direction flag
					pNewAttrStartArrow = (AttrStartArrow *)pAttrStartArrow->SimpleCopy();
					
					if (pNewAttrStartArrow)
					{
						if (pAttrStartArrow->Value.StartArrow.m_bExtendPath)
						{
							pNewAttrStartArrow->Value.StartArrow.m_bExtendPath = FALSE;
						}
						else
						{
							pNewAttrStartArrow->Value.StartArrow.m_bExtendPath = TRUE;
						}
						
						AttributeManager::ApplyAttribToNode(
							(NodeRenderableInk *)(pNode), pNewAttrStartArrow);
						
					}
				}
			}
		}

		pNodeListItem = (NodeListItem *)pSelList->GetNext(pNodeListItem);
	}

	// end the selection operation

	// delete the sel list
	delete pSelList;

	// End();
}

/********************************************************************************************

>	BOOL OpChangeStartArrowExtendsDesc::Declare()

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/2/99
	Returns:	TRUE if all went OK, False otherwise
	Purpose:	Adds the operation to the list of all known operations

********************************************************************************************/
BOOL OpChangeStartArrowExtendsDesc::Declare()
{
	return (RegisterOpDescriptor(
								0, 
								_R(IDS_CHANGE_START_ARROW_EXTENDS),
								CC_RUNTIME_CLASS(OpChangeStartArrowExtendsDesc), 
								OPTOKEN_CHANGE_START_ARROW_EXTENDS,
								OpChangeStartArrowExtendsDesc::GetState));

}

/********************************************************************************************

>	OpState OpChangeStartArrowExtendsDesc::GetState(String_256* Description, OpDescriptor*)

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/2/00
	Outputs:	-
	Returns:	Ungreyed, Unticked
	Purpose:	Find out the state of the new regular shape at the specific time

********************************************************************************************/
OpState OpChangeStartArrowExtendsDesc::GetState(String_256* Description, OpDescriptor*)
{
	OpState Blobby;
	
	return Blobby;
}

/********************************************************************************************
>	OpChangeEndArrowExtendsDesc::OpChangeEndArrowExtendsDesc()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com> & Olivier
	Created:	21/11/96
	Purpose:	Constructor.
********************************************************************************************/
OpChangeEndArrowExtendsDesc::OpChangeEndArrowExtendsDesc()
{
	//TRACEUSER( "MarkH", _T("Just Made a OpChangeEndArrowExtendsDesc Class!\n"));
}



/********************************************************************************************
>	virtual void OpChangeArrowStartExtendsDesc::Do(OpDescriptor *pOpDesc)

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com> & Olivier
	Created:	21/11/96
	Inputs:		pOpDesc - OpDescriptor - unused
	Outputs:	-
	Returns:	-
	Purpose:	The do function.  Inverts the arrow behaviour
********************************************************************************************/
void OpChangeEndArrowExtendsDesc::Do(OpDescriptor *pOpDesc)
{
	TRACEUSER( "DavidM", _T("OpChangeEndArrowExtendsDesc::Do !\n"));

	// ok, start the sel op
	// get the current selection
	SelRange* pSel = GetApplication()->FindSelection();

	// DoStartSelOp(TRUE);

	NodeListItem* pNodeListItem = NULL;

	// make a node list
	List * pSelList = NULL;

	pSelList = pSel->MakeListOfNodes(FALSE);

	Node * pNode = NULL;

	pNodeListItem = (NodeListItem *)pSelList->GetHead();

	AttrStartArrow * pNewAttrStartArrow = NULL;
	AttrStartArrow * pAttrStartArrow = NULL;
	
	AttrEndArrow * pNewAttrEndArrow = NULL;
	AttrEndArrow * pAttrEndArrow = NULL;
	NodeRenderableBounded * pParent = NULL;

	NodeHidden * pHidden = NULL;

	// run the the list finding arrow attributes, and invert them
	while (pNodeListItem)
	{
		pNode = pNodeListItem->pNode;

		if (pNode)
		{
			if (pNode->IsKindOf(CC_RUNTIME_CLASS(NodeRenderableInk)))
			{
				pAttrEndArrow = (AttrEndArrow *)pNode->FindFirstChild(CC_RUNTIME_CLASS(AttrEndArrow));
				
				if (pAttrEndArrow)
				{
					pNewAttrEndArrow = (AttrEndArrow *)pAttrEndArrow->SimpleCopy();
					
					if (pNewAttrEndArrow)
					{
						if (pAttrEndArrow->Value.EndArrow.m_bExtendPath)
						{
							pNewAttrEndArrow->Value.EndArrow.m_bExtendPath = FALSE;
						}
						else
						{
							pNewAttrEndArrow->Value.EndArrow.m_bExtendPath = TRUE;
						}
						
						AttributeManager::ApplyAttribToNode(
							(NodeRenderableInk *)(pNode), pNewAttrEndArrow);
						
					}
					
				}

			}
		}

		pNodeListItem = (NodeListItem *)pSelList->GetNext(pNodeListItem);
	}

	// end the selection operation

	// delete the sel list
	delete pSelList;

	// End();
}

/********************************************************************************************

>	BOOL OpChangeEndArrowExtendsDesc::Declare()

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/2/99
	Returns:	TRUE if all went OK, False otherwise
	Purpose:	Adds the operation to the list of all known operations

********************************************************************************************/
BOOL OpChangeEndArrowExtendsDesc::Declare()
{
	return (RegisterOpDescriptor(
								0, 
								_R(IDS_CHANGE_END_ARROW_EXTENDS),
								CC_RUNTIME_CLASS(OpChangeEndArrowExtendsDesc), 
								OPTOKEN_CHANGE_END_ARROW_EXTENDS,
								OpChangeEndArrowExtendsDesc::GetState));

}

/********************************************************************************************

>	OpState OpChangeEndArrowExtendsDesc::GetState(String_256* Description, OpDescriptor*)

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/2/00
	Outputs:	-
	Returns:	Ungreyed, Unticked
	Purpose:	Find out the state of the new regular shape at the specific time

********************************************************************************************/
OpState OpChangeEndArrowExtendsDesc::GetState(String_256* Description, OpDescriptor*)
{
	OpState Blobby;
	
	return Blobby;
}

#endif

