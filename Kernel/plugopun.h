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


// OpDescriptor, Operations and Context sensitive menu for plug-ins

#ifndef INC_PLUGINUNDOOP
#define INC_PLUGINUNDOOP


class KernelBitmapRef;
class NodeBitmap;
class AttrFillGeometry;

/********************************************************************************************

>	class PlugInUndoOp : public SelOperation

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/1/97
	Purpose:	Undoable Operation so that a plug-ins can be invoked and used.  

********************************************************************************************/				

class PlugInUndoOp : public SelOperation
{
	CC_DECLARE_DYNCREATE( PlugInUndoOp );

public:

	PlugInUndoOp();

	virtual void Do(OpDescriptor*);

	static BOOL Init();
	static BOOL RegisterOpToken(TCHAR *OpToken, const String_64& NewMenuText,
								CCRuntimeClass* pClass = CC_RUNTIME_CLASS(PlugInUndoOp),
								pfnGetState gs = GetState);
	static BOOL RegisterOpToken(TCHAR *OpToken, UINT32 MenuTextID,
								CCRuntimeClass* pClass = CC_RUNTIME_CLASS(PlugInUndoOp),
								pfnGetState gs = GetState);
	static OpState GetState(String_256*, OpDescriptor*);	

public:
	// Search the selection for a bitmap
//	static BOOL FindBitmapInSelection(KernelBitmap ** ppFoundBitmap = NULL,
//									  KernelBitmapRef ** ppFoundBitmapRef = NULL,
//									  NodeBitmap ** ppFoundNode = NULL,
//									  AttrFillGeometry ** ppFoundFillAttribute = NULL);

	// Overloaded so that we can use our stored copy of the OpDescriptor to get the undo text.  
	virtual void GetOpName(String_256* OpName);

protected:
	// cannot find any stored OpDescriptor in the current operation and so
	// we must store our own 
	OpDescriptor* m_pOpDesc;
};
/********************************************************************************************

>	class ActionApplyPlugInToBitmap : public Action

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/1/97
	Purpose:	When executed, this sets up an action to redo/undo an apply a plug-in to 
				a bitmap.
	
	SeeAlso:	PlugInUndoOp

********************************************************************************************/

class CCAPI ActionApplyPlugInToBitmap : public Action
{
	CC_DECLARE_DYNCREATE( ActionApplyPlugInToBitmap )

public:
	ActionApplyPlugInToBitmap();
	~ActionApplyPlugInToBitmap();
	virtual ActionCode Execute();
	static ActionCode Init(Operation* const pOp,
							ActionList *pActionList,
							UINT32 ActionSize,
							Document *pDocument,
							KernelBitmap * pBitmap,
							KernelBitmapRef * pBitmapRef,
							NodeBitmap * pFoundNode,
							AttrFillGeometry * pFoundFillAttribute,
							Action **NewAction,
							BOOL bUpdateAspect = FALSE);

protected:

private:
	Document * m_pDocument;
	KernelBitmap * m_pBitmap;
	KernelBitmapRef * m_pBitmapRef;
	NodeBitmap * m_pFoundNode;
	AttrFillGeometry * m_pFoundFillAttribute;
	BOOL m_bUpdateAspect;
};

#endif // INC_PLUGINUNDOOP
