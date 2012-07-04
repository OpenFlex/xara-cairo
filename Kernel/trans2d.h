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

// Header for the 2D Matrix transformation class

/*
*/



#ifndef TRANS2D_INC
#define TRANS2D_INC

#include "tranform.h"
#include "matrix.h"

class DocCoord;



/********************************************************************************************

>	class Trans2DMatrix : public TransInvertable

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/02/94
	Purpose:	This transformation will perform any 2D matrix transformations such as :-
				Translate, Rotate, Scale and Shear

********************************************************************************************/

class Trans2DMatrix : public TransInvertable	  
{
CC_DECLARE_DYNAMIC(Trans2DMatrix);

public:
	// constructors
	Trans2DMatrix( );
	Trans2DMatrix( DocCoord CentreOfRot, ANGLE RotateBy );
	Trans2DMatrix( INT32 TransX, INT32 TransY );
	Trans2DMatrix( const Matrix &NewMatrix);
	Trans2DMatrix( const Trans2DMatrix&);
	void InitDecomposedTransforms();

	// construction helper functions
	void SetTransform();
	void SetTransform(DocCoord CentreOfRot, ANGLE RotateBy);
	void SetTransform(INT32 TransX, INT32 TransY);
	void SetTransform(const Matrix& NewMatrix);
	void SetTransform(const Trans2DMatrix&);

	// virtual functions
	virtual void Transform(DocCoord* Coords, INT32 NumPoints);
	virtual BOOL IsInvertable();
	virtual void Invert();
	virtual BOOL IsTranslation();

	INT32 GetWorkingQuadrant(); // MRH - 07/07/00

	Trans2DMatrix& operator*=(const Trans2DMatrix&); 
	Trans2DMatrix& operator=(const Trans2DMatrix&); 

	// Access function
	Matrix  GetMatrix()  { return  TransMatrix; }
	Matrix* GetpMatrix() { return &TransMatrix; }

	void	 EnsureDecomposedTransformsCached();
	FIXED16	 GetScale();
	FIXED16	 GetAspect();
	ANGLE    GetRotation();
	ANGLE    GetSkew();
	DocCoord GetTranslation();
	virtual	 FIXED16 GetScalar();

// Member vars
protected:
	Matrix 	TransMatrix;

	FIXED16  Scale;
	FIXED16  Aspect;
	ANGLE    Rotation;
	ANGLE    Skew;
	DocCoord Translation;
	FIXED16	 ScaleY;
};

#endif	// TRANS2D_INC
