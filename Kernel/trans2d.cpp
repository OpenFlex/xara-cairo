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


// 2D Matrix transformation classes

#include "camtypes.h"

CC_IMPLEMENT_DYNAMIC(Trans2DMatrix, TransInvertable)

// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW



/********************************************************************************************
>	void Trans2DMatrix::InitDecomposedTransforms()

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/6//95
	Purpose:	ensure all member vars are init'ed
********************************************************************************************/

void Trans2DMatrix::InitDecomposedTransforms()
{
	Scale       = 0;	// 0 indicates cached values invalid
	Aspect      = 1;
	Rotation    = 0;
	Skew        = 0;
	Translation = DocCoord(0,0);
}
	

/********************************************************************************************
>	Trans2DMatrix::Trans2DMatrix( )

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/2/95
	Purpose:	Builds a 2D Tranform object of the identiry matrix (ie it has no effect)
********************************************************************************************/

Trans2DMatrix::Trans2DMatrix( )
{
	SetTransform();
}

void Trans2DMatrix::SetTransform()
{
	// Build the translation matrix
	TransMatrix = Matrix();

	// Set the flags
	TransLines = FALSE;
	TransFills = TRUE;
	InitDecomposedTransforms();
}
	

/********************************************************************************************

>	Trans2DMatrix::Trans2DMatrix( DocCoord CentreOfRot, ANGLE RotateBy )

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/3/94
	Inputs:		CentreOfRot - The centre of rotation
				RotateBy - The angle of the rotation that this transform object will perform
	Purpose:	Creates a 2D Matrix transform object that will perform a rotation about the
				given point by the given number of degrees.

********************************************************************************************/

Trans2DMatrix::Trans2DMatrix(DocCoord CentreOfRot, ANGLE RotateBy)
{
	SetTransform(CentreOfRot,RotateBy);
}

void Trans2DMatrix::SetTransform(DocCoord CentreOfRot, ANGLE RotateBy)
{
	// Build the matricies we need
	Matrix RotateIt(RotateBy);
	Matrix TransFromOrigin( CentreOfRot.x, CentreOfRot.y );
	
	// need to translate the centre of rotation to the origin
	TransMatrix = Matrix( -CentreOfRot.x, -CentreOfRot.y );

	// rotate about the origin
	TransMatrix *= RotateIt;

	// translate back to the centre of rotation
	TransMatrix *= TransFromOrigin;

	// Set the flags
	TransLines = FALSE;
	TransFills = TRUE;
	InitDecomposedTransforms();
}

/********************************************************************************************

>	Trans2DMatrix::Trans2DMatrix( INT32 TransX, INT32 TransY)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/3/94
	Inputs:		TransX - The X translation
				TransY - The Y translation
	Purpose:	Builds a 2D Tranform object that will perform a translation by an offset
				Transx, TransY.

********************************************************************************************/

Trans2DMatrix::Trans2DMatrix(INT32 TransX, INT32 TransY)
{
	SetTransform(TransX,TransY);
}

void Trans2DMatrix::SetTransform(INT32 TransX, INT32 TransY)
{
	// Build the translation matrix
	TransMatrix = Matrix(TransX, TransY);

	// Set the flags
	TransLines = FALSE;
	TransFills = TRUE;
	InitDecomposedTransforms();
}



/********************************************************************************************

>	Trans2DMatrix::Trans2DMatrix( Matrix& NewMatrix )

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/02/94
	Inputs:		NewMatrix - The transformation matrix that you wish to apply
	Purpose:	constructor

********************************************************************************************/

Trans2DMatrix::Trans2DMatrix( const Matrix &NewMatrix )
{
	SetTransform(NewMatrix);
}

void Trans2DMatrix::SetTransform(const Matrix& NewMatrix)
{
	// Take a copy of the matrix
	TransMatrix = NewMatrix;

	// Set the flags
	TransLines = FALSE;
	TransFills = TRUE;
	InitDecomposedTransforms();
}



/********************************************************************************************

>	Trans2DMatrix::Trans2DMatrix(const Trans2DMatrix& Other)

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/9/94
	Inputs:		Other - The other trans2dmatrix to copy
	Purpose:	Copy constructor

********************************************************************************************/

Trans2DMatrix::Trans2DMatrix(const Trans2DMatrix& Other)
{
	SetTransform(Other);
}

void Trans2DMatrix::SetTransform(const Trans2DMatrix& Other)
{
	// Copy all the elements from the other trans2dmatrix to this new one.
	TransMatrix = Other.TransMatrix;
	TransLines = Other.TransLines;
	TransFills = Other.TransFills;
	InitDecomposedTransforms();
}

/********************************************************************************************

>	void Trans2DMatrix::Transform( DocCoord* Coords, INT32 NumCoords )

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/02/94
	Inputs:		Coords - Pointer to an array of coodinates to transform
				NumCoords - the number of coodinates in the array
	Outputs:	Coords - The coordinates in the array will have been transformed
	Purpose:	Transform the coordinates in the array using the matrix in the transform
				object

********************************************************************************************/

void Trans2DMatrix::Transform( DocCoord* Coords, INT32 NumCoords )
{
	// Get the matrix to transform all the coords passed in
	TransMatrix.transform( (Coord*)Coords, NumCoords );
	InitDecomposedTransforms();
}


/********************************************************************************************

>	void Trans2DMatrix::Invert()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/02/94
	Purpose:	Inverts the transformation matrix held by this transform object. future calls
				to the transform() member function will cause it to transform coordinates
				back to their original positions. ie, call Transform(), call Invert() and 
				call Transform() again should give you the same set of coords as you started
				with

********************************************************************************************/
void Trans2DMatrix::Invert()
{
	// Invert the transformation matrix
	TransMatrix = TransMatrix.Inverse();

	InitDecomposedTransforms();
}


/********************************************************************************************
>	BOOL Trans2DMatrix::IsTranslation()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/12/2004
	Purpose:	Determine whether the transformation is a simple translation
********************************************************************************************/

BOOL Trans2DMatrix::IsTranslation()
{
	return TransMatrix.IsTranslation();
}


/********************************************************************************************

>	INT32 GetWorkingQuadrant()

	Author:		Mark_Howitt (Xara Group Ltd) <camelotdev@xara.com>
	Created:	07/07/00
	Purpose:	To find out which quadrant the current matrix is working in.
				OR To help find out if the matrix is flipping an object and in which way.
				
				1	|	2
				---------
				4	|	3

				Quadrant 1:		A > 0 && D > 0
				Quadrant 2:		A < 0 && D > 0
				Quadrant 4:		A > 0 && D < 0
				Quadrant 3:		A < 0 && D < 0

				The return value is the quadrant in which the matrix is working in.

********************************************************************************************/
INT32 Trans2DMatrix::GetWorkingQuadrant()
{
	FIXED16 ZERO = 0;
	FIXED16 ABCD[4];
	INT32 XY[2];

	TransMatrix.GetComponents(&ABCD[0],&XY[0]);

	if(ABCD[3] >= ZERO)
	{
		// either 1 or 2
		if(ABCD[0] >= ZERO)
			return 1;
		else
			return 2;
	}
	else
	{
		// either 3 or 4
		if(ABCD[0] >= ZERO)
			return 4;
		else
			return 3;
	}
	
	return 1;
}

/********************************************************************************************
					
>   Trans2DMatrix& Trans2DMatrix::operator*=(const Trans2DMatrix& op) 

	Author:     Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:    07/11/94
	Inputs:     Trans2DMatrix to be multiplied
	Outputs:    None.
	Returns:    result of multiplication.
	Purpose:    Overloads the *= operator for Trans2DMatrix.
	Errors:     None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/


Trans2DMatrix& Trans2DMatrix::operator*=(const Trans2DMatrix& op)
{
	TransMatrix*=op.TransMatrix; 
	InitDecomposedTransforms();
	return *this; 
} 



/********************************************************************************************
					
>   Trans2DMatrix& Trans2DMatrix::operator=(const Trans2DMatrix& rhs) 

	Author:     Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:    2/1/95
	Inputs:     Trans2DMatrix to be copied into this object
	Outputs:    None.
	Returns:    result of assignment
	Purpose:    Overloads the = operator for Trans2DMatrix
	Errors:     None.

********************************************************************************************/

Trans2DMatrix& Trans2DMatrix::operator=(const Trans2DMatrix& rhs)
{
	TransMatrix = rhs.TransMatrix; 

	//Graham 12/8/96: Added these because, well, you need them
	//Fixes bug 4938
	TransLines = rhs.TransLines;
	TransFills = rhs.TransFills;

	InitDecomposedTransforms();
	return *this; 
} 


/********************************************************************************************
>	void Trans2DMatrix::EnsureDecomposedTransformsCached()

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/6/95
	Purpose:	ensures the decomposed transforms are cached
********************************************************************************************/

void Trans2DMatrix::EnsureDecomposedTransformsCached()
{
	if (Scale==0)
	{
		GetpMatrix()->Decompose(&Scale, &Aspect, &Rotation, &Skew, &Translation, &ScaleY);
		Rotation = (Rotation*180)/PI;	
		Skew     = (Skew    *180)/PI;	// convert to degrees!?
	}
}


/********************************************************************************************
>	FIXED16 Trans2DMatrix::GetScale()

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/6/95
	Purpose:	get the transform's scale component
********************************************************************************************/

FIXED16 Trans2DMatrix::GetScale()
{
	EnsureDecomposedTransformsCached();
	return Scale;
}


/********************************************************************************************
>	FIXED16 Trans2DMatrix::GetAspect()

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/6/95
	Purpose:	get the transform's Aspect component
********************************************************************************************/

FIXED16 Trans2DMatrix::GetAspect()
{
	EnsureDecomposedTransformsCached();
	return Aspect;
}


/********************************************************************************************
>	ANGLE Trans2DMatrix::GetRotation()

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/6/95
	Purpose:	get the transform's Rotation component
********************************************************************************************/

ANGLE Trans2DMatrix::GetRotation()
{
	EnsureDecomposedTransformsCached();
	return Rotation;
}


/********************************************************************************************
>	ANGLE Trans2DMatrix::GetSkew()

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/6/95
	Purpose:	get the transform's Skew component
********************************************************************************************/

ANGLE Trans2DMatrix::GetSkew()
{
	EnsureDecomposedTransformsCached();
	return Skew;
}


/********************************************************************************************
>	DocCoord Trans2DMatrix::GetTranslation()

	Author:		Ed_Cornes (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/6/95
	Purpose:	get the transform's Translation component
********************************************************************************************/

DocCoord Trans2DMatrix::GetTranslation()
{
	EnsureDecomposedTransformsCached();
	return Translation;
}



/********************************************************************************************
>	FIXED16 Trans2DMatrix::GetScalar()

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/6/95
	Purpose:	get the transform's directionless scale component
				(used for scaling line widths, bevel widths, brush widths, etc.)
				For compatibility reasons this is defined to be the Y scale factor of the
				matrix!
********************************************************************************************/

FIXED16 Trans2DMatrix::GetScalar()
{
	EnsureDecomposedTransformsCached();
	return ScaleY;
}


/********************************************************************************************
>	virtual BOOL Trans2DMatrix::IsInvertable()

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/1/96
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if this transform can be inverted; FALSE if not.
	Purpose:	To see if this transform is really invertable
	SeeAlso:	TransformBase::IsInvertable
********************************************************************************************/
BOOL Trans2DMatrix::IsInvertable()
{
	if (TransMatrix.Type == TRANS_IDENTITY)
		return TRUE;
	
	// The inverse has failed if we get an identity matrix
	Matrix Inversed = TransMatrix.Inverse();

	return (Inversed.Type != TRANS_IDENTITY);
}
