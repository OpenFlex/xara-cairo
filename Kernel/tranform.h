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

// The Transformation Base Classes

/*
*/


#ifndef TRANFORM_INC
#define TRANFORM_INC

#include "ccobject.h"


class DocCoord;

/********************************************************************************************

>	class TransformBase : public CCObject

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/02/94
	Purpose:	The Transformation Base Class. This is an abstract class - you can only create
				instances of its derived classes. The Transformation classes are used to
				give a transparent interface to arbitary transformations on objects. Nodes
				do not need to be aware of what type of transformation is being applied or
				how is should be undone.
				This class contains two virtual function :-
				MonoOn virtual void Transform(DocCoord* Coords, INT32 NumCoords) MonoOff
				MonoOn virtual BOOL IsInvertable() MonoOff
				It also contains the following public member vars
				MonoOn BOOL TransLines;		// TRUE if Line Widths are to be transformed MonoOff
				MonoOn BOOL TransFills;		// TRUE if Fills are to be transformed MonoOff
	SeeAlso:	TransInvertable; TransNonInvertable

********************************************************************************************/

class TransformBase : public CCObject
{
CC_DECLARE_DYNAMIC(TransformBase);

public:
	TransformBase()
	{
		TransFills					= TRUE;
		TransLines					= TRUE;
		bSolidDrag					= FALSE;
		bTransformYourChildren		= TRUE;
		bHaveTransformedChildren	= TRUE;
		bHaveTransformedCached		= TRUE;
		bHaveTransformedAllChildren	= FALSE;
		bHaveTransformedAllCached	= FALSE;
	};
	virtual void Transform( DocCoord* Coords, INT32 NumCoords) = 0;
	virtual BOOL IsInvertable() = 0;
	virtual BOOL IsTranslation() {return FALSE;}

	// Other functions
	virtual FIXED16 GetScalar();

// vars
public:
	BOOL TransFills : 1;					// Should the Fills be transformed
	BOOL TransLines : 1;					// Should the line widths be transformed
	BOOL bSolidDrag : 1;					// Should the object update itself fully so it can be rendered?

	BOOL bTransformYourChildren : 1;		// Should the object transform all its children (it might not need to if it can transform its cached data)
	BOOL bHaveTransformedChildren : 1;		// Feedback from Node: Node is fully transformed, including all children
	BOOL bHaveTransformedCached : 1;		// Feedback from Node: Node has transformed its cached data

	BOOL bHaveTransformedAllChildren : 1;	// Feedback from Iterator: All iterated nodes returned bHaveTransformedChildren;
	BOOL bHaveTransformedAllCached : 1;		// Feedback from Iterator: All iterated nodes returned bHaveTransformedCached;
};




/********************************************************************************************

>	class TransInvertable : public TransformBase

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/02/94
	Purpose:	One of the transformation base classes. All Transformations derived from this
				class can be inverted directly. ie Transforms that make use of a matrix can
				be inverted by inverting the matrix.
				This class adds the following virtual functions :-
				MonoOn virtual void Invert() MonoOff
	SeeAlso:	Trans2DMatrix

********************************************************************************************/

class TransInvertable : public TransformBase
{
CC_DECLARE_DYNAMIC(TransInvertable);

public:
	TransInvertable(){};
	virtual BOOL IsInvertable() { return TRUE; }
	virtual void Invert() = 0;
};




/********************************************************************************************

>	class TransNonInvertable : public TransformBase

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/02/94
	Purpose:	One of the Transformation base classes. All the transformations derived from
				this class can not be inverted. Transforms of this kind are considered to be
				one way mappings from the original coords. There is no way of getting the
				original coords back after they have been transformed by a class derived from
				this one. Examples include the Envelope transformation

********************************************************************************************/

class TransNonInvertable : public TransformBase
{
CC_DECLARE_DYNAMIC(TransNonInvertable);

public:
	TransNonInvertable(){};
	virtual BOOL IsInvertable() { return FALSE; }
};



#endif	// TRANFORM_INC


