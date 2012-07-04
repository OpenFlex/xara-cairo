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


#ifndef INC_MATRIX
#define INC_MATRIX

#include "xarlib/ccmaths.h"
#include "xarlib/coord.h"
#include "xarlib/ccobject.h"

class DocRect;
class DocCoord;

/********************************************************************************************

<	TransformType; enum

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/10/93
	Comment:	This enum is used to determine what type of matrix we have. It can be one of
				the following values :- MonoOn
				TRANS_IDENTITY		// An Identity Matrix
				TRANS_TRANSLATION	// A Translation Matrix
				TRANS_ROTATION		// A Rotation Matrix
				TRANS_SCALE			// A Scale Matrix
				TRANS_SHEAR			// A Shear Matrix
				TRANS_COMPLEX		// A Matrix that is a combination of the above
				MonoOff

********************************************************************************************/

typedef enum
{
	TRANS_IDENTITY,
	TRANS_TRANSLATION,
	TRANS_ROTATION,
	TRANS_SCALE,
	TRANS_SHEAR,
	TRANS_COMPLEX
} TransformType;


/***********************************************************************************************

>	class Matrix : public SimpleCCObject

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com> (extended by Rik)
	Created:	13/5/1993 (extended 19/10/93)
	Purpose:	Represents a mathematical transformation matrix. Transformation matrices can 
				transform the coordinate pairs of one coordinate space into another coordinate
				space.
				Matrices are used in Camelot for the rendering process in various ways. These 
				include coordinate conversion, scaling, rotation and translation. 
				
				Depending on the constructor applied it is possible to specify any of the above
				types of matrix. MonoOn
                 eg.	Matrix();              			//creates the identity matrix
                 		Matrix(ANGLE(90));              //creates a rotation matrix by 90 deg
                 		Matrix(ScaleX, ScaleY);         //creates a scaling matrix
                 		Matrix(xOffset, yOffset);       //creates a translation matrix
                MonoOff
                The Matrix also contains a couple of Public vars that may or may not be
                of any use to anyone. These are as follows :- MonoOn
                TransformType	Type;	// The type of transformation this matrix represents
                ANGLE			Angle;	// The angle of rotation for a rotation matrix
                MonoOff
	SeeAlso:	TransformType
                                    
***********************************************************************************************/

class CCAPI Matrix : public SimpleCCObject
{
friend class OSRenderRegion;
friend class XMatrix;

private:
	FIXED16 a;
	FIXED16 b;
	FIXED16 c;
	FIXED16 d;
	INT32 e;
	INT32 f;

public:
	TransformType	Type;	// The type of transform this matrix represents
	ANGLE			Angle;	// If it is a rotation, this holds the angle of rotation

public:
	// Constructors et all
	Matrix();
	Matrix(const FIXED16&, const FIXED16&);
	Matrix(const ANGLE& theta);
	Matrix(const Coord&);
	Matrix(const Coord&, const ANGLE&);
	Matrix(const INT32, const INT32);
	Matrix(const FIXED16&, const FIXED16&, const FIXED16&, const FIXED16&, const INT32, const INT32);
	Matrix(const DocRect&, const DocRect&);
	
	// Transformations using the matrix
	void transform(Coord*) const;
	void transform(Coord[], UINT32 count) const;
	void transform(Coord[], const Coord[], UINT32) const;

	void translate(const INT32 TransX, const INT32 TransY);

	BOOL TransformBounds(DocRect* pRect) const;
	BOOL Decompose(FIXED16* pScale=NULL, FIXED16* pAspect=NULL,
				   ANGLE* pRotation=NULL, ANGLE* pShear=NULL,
				   Coord* pTranslate=NULL, FIXED16* pScaleY=NULL);
	BOOL Compose(FIXED16 Scale=1.0, FIXED16 Aspect=1.0,
				 ANGLE Rotation=0, ANGLE Shear=0, Coord Translation=Coord(0,0));

	BOOL IsRotation(const double epsilon = 0.0) const;
	BOOL IsReflection(const double epsilon = 0.0) const;
	BOOL IsTranslation(const double epsilon = 0.0) const;
	BOOL IsIdentity(/*DOUBLEPARAM epsilon*/) const;

	// Matrix copy and multiplication stuff
	Matrix& operator=(const Matrix&);
	BOOL operator==(const Matrix&) const;
	friend Matrix operator*(const Matrix&, const Matrix&);
	Matrix& operator*=(const Matrix&);

	// Matrix Inversion
	Matrix Inverse() const;

	// obtain matrix compnents
	void GetComponents( FIXED16 *, INT32 * ) const;
	void GetTranslation(DocCoord&) const;
	void GetTranslation(INT32&,INT32&) const;
	void SetTranslation(const DocCoord&);
	void SetTranslation(const INT32&, const INT32&);

	// Karim 23/07/2000
	// ok, here are some factory methods so you don't have to trawl
	// through the codebase every time you want a certain type of matrix.
	static Matrix CreateTransMatrix(const Coord& dcTrans);
	static Matrix CreateScaleMatrix(const double& xScale, const double& yScale);
	static Matrix CreateScaleMatrix(const double& ScaleFactor);
	static Matrix CreateShearMatrix(const double& ShearAngle);
	static Matrix CreateRotateMatrix(const double& RotateAngle);

	// Karim 04/09/2000
	// two methods to obtain the trace and determinant of a matrix.
	double Trace() const;
	double Det() const;

	// Karim 09/2001
	// A set of matrix fns useful for geometric tweening.
	void RatioMatrix (const double ratio);
	Matrix Interpolate(const Matrix& op, const double ratio) const;
	Matrix PostRotate(DocCoord dcCentre, const ANGLE& Angle) const;

	#ifdef _DEBUG
	void Dump() const;
	#endif
};

#endif 
