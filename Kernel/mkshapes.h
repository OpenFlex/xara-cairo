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
 * */
   
#ifndef INC_MKSHAPES
#define INC_MKSHAPES 

//#include "selop.h"         - in camtypes.h [AUTOMATICALLY REMOVED]
#include <list>

#define OPTOKEN_MAKE_SHAPES _T("ConvertToShapes")
#define OPTOKEN_MAKE_NODES_SHAPES	_T("MakeNodesShapes")
   
/********************************************************************************************

>	class OpMakeShapes : public SelOperation

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/7/93
	Purpose:	This class represents the MakeShapes operation.

********************************************************************************************/

class CCAPI OpMakeShapes: public SelOperation
{         

	CC_DECLARE_DYNCREATE( OpMakeShapes )    

public:
	OpMakeShapes();								
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
	void			Do(OpDescriptor*);	

};  
 


/********************************************************************************************

>	void OpMakeNodesShapes::DoWithParam(OpDescriptor* pOp, OpParam* pParam)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/11/1999
	Purpose:	This undoable operation converts a given list of nodes to editable shapes
				(paths), each new node retaining the selection status of the original.

				**TODO**
				NOTE	that currently this Op does *NOT* call AllowOp(), which I believe
						is VERY naughty. This probably needs changing...

	See also:	OpParamMakeNodesShapes.

********************************************************************************************/
class CCAPI OpMakeNodesShapes : public UndoableOperation
{
	CC_DECLARE_DYNCREATE(OpMakeNodesShapes);

public:
	virtual void DoWithParam(OpDescriptor*, OpParam* pParam);
	static BOOL Init();
};



/********************************************************************************************

>	void OpMakeNodesShapes::DoWithParam(OpDescriptor* pOp, OpParam* pParam)

	Author:		Karim_MacDonald (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/11/1999
	Inputs:		std::list<Node*>* plpNodes		a list of pointers to Nodes, which
												OpMakeNodesShapes should convert into paths.
	Purpose:	OpParam structure required to use the OpMakeNodesShapes undoable operation.
	See also:	OpMakeNodesShapes

********************************************************************************************/
class OpParamMakeNodesShapes : public OpParam
{
public:
	OpParamMakeNodesShapes()
	{
		ERROR2RAW("OpParamMakeNodesShapes default constructor should not be called!");
	}

	OpParamMakeNodesShapes(std::list<Node*>* plpNodes)
	{
		m_plpNodes = plpNodes;
	}

	std::list<Node*>* m_plpNodes;		// a pointer to a list of pointers to Nodes
										// which OpMakeNodesShapes will make into shapes.
};



#endif	// INC_MKSHAPES
