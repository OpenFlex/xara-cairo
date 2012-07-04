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
/***********************************************************************************************

>	class XMatrix

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/5/1993
	Purpose:	Represents a mathematical transformation matrix containing 64-bit values.
				Use instead of Matrix when larger co-ordinates are needed. Based on the
				1.11 build of matrix.h and the 1.5 build of matrix.cpp.
	Errors:		None.

***********************************************************************************************/


#ifndef INC_XMATRIX
#define INC_XMATRIX

#include "ccmaths.h"
#include "wrkcoord.h"
#include "ccobject.h"

class Matrix;

class XMatrix : public SimpleCCObject
{
friend class OSRenderRegion;

private:
	FIXED16 a;
	FIXED16 b;
	FIXED16 c;
	FIXED16 d;
	XLONG e;
	XLONG f;

public:
	XMatrix();
	XMatrix(const FIXED16&, const FIXED16&);
	XMatrix(const ANGLE& theta);
	XMatrix(const WorkCoord&);
	XMatrix(const XLONG x, const XLONG y);
	XMatrix(const INT32 x, const INT32 y);
	XMatrix(const Matrix& );
	XMatrix( const FIXED16& ca,
			 const FIXED16& cb,
			 const FIXED16& cc,
			 const FIXED16& cd,
			 const XLONG    ce,
			 const XLONG    cf
			);

	void transform(WorkCoord*);
	void transform(WorkCoord[], UINT32 count);
	void transform(WorkCoord[], const WorkCoord[], UINT32);

	XMatrix& operator=(const XMatrix&);
	friend XMatrix operator*(const XMatrix&, const XMatrix&);
	XMatrix& operator*=(const XMatrix&);


};


#endif 
