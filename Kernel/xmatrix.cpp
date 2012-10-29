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


// (this source was based on the 1.5 revision of matrix.cpp done by Mario)

// this is used to show the fact that the final parameter to XMatrixCalc is in fact modified
// by the call. It is done this way so that 32-bit implementations may replace the final
// paraemter and simply use the return result of the function.
#define	RESULT

#define	TORADIANS(x)	((x)/180.0*PI)


/********************************************************************************************

>	XMatrix::XMatrix () 

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		None
	Outputs:	None
	Returns:	None.
	Purpose:	Default initialisation - sets up the identity matrix.
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

XMatrix::XMatrix() 
{
	a = (FIXED16) 1;
	b = (FIXED16) 0;
	c = (FIXED16) 0;
    d = (FIXED16) 1;
    e = 0;
    f = 0;
}

/********************************************************************************************

>	XMatrix::XMatrix ( const Matrix& mat) 

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/6/93
	Inputs:		Matrix (32-bit flavour)
	Outputs:	None
	Returns:	None.
	Purpose:	Default initialisation - copies elements from 32- to 64-bit matrix
	Errors:		None.

********************************************************************************************/

XMatrix::XMatrix( const Matrix& mat32) 
{
	a = mat32.a;
	b = mat32.b;
	c = mat32.c;
    d = mat32.d;
    e = mat32.e;
    f = mat32.f;
}

	
/********************************************************************************************

>	XMatrix::XMatrix (const FIXED16& xScale, const FIXED16& yScale) 

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		Two fixed16s representing the x and y scale factors.
	Outputs:	None
	Returns:	None.
	Purpose:	Default initialisation - sets up the scale matrix.
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

XMatrix::XMatrix(const FIXED16& xScale, const FIXED16& yScale)  
{
	a = xScale;
	b = (FIXED16) 0;
	c = (FIXED16) 0;
    d = yScale;
    e = 0;
    f = 0;
}

/********************************************************************************************

>	XMatrix::XMatrix (const ANGLE& theta) 

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		An angle representing the degree of rotation.
	Outputs:	None
	Returns:	None.
	Purpose:	Default initialisation - sets up the rotation matrix.
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

XMatrix::XMatrix(const ANGLE& theta) 
{
#if 0
	a = b = c = d = theta;
	
	a.Cos();
	b.Sin();
	c = -(c.Sin());
	d.Cos(); 
#else
	double thetaradians = TORADIANS(theta.MakeDouble());
	FIXED16 costheta = cos(thetaradians);
	FIXED16 sintheta = sin(thetaradians);
	
	a = d = costheta;
	b = sintheta;
	c = -sintheta;
#endif
	
	e = 0;
	f = 0;
}

/********************************************************************************************

>	XMatrix::XMatrix (const WorkCoord& disp) 

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		Displacement of translation.
	Outputs:	None
	Returns:	None.
	Purpose:	Default initialisation - Sets up a translate matrix.
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

XMatrix::XMatrix(const WorkCoord& disp) 
{
	a = (FIXED16) 1;
	b = (FIXED16) 0;
	c = (FIXED16) 0;
    d = (FIXED16) 1;
    e = disp.x;
    f = disp.y;
}

/********************************************************************************************

>	XMatrix::XMatrix (const XLONG x, const XLONG y)

>	XMatrix::XMatrix (const INT32 x, const INT32 y)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		Displacement of translation.
	Outputs:	None
	Returns:	None.
	Purpose:	Default initialisation - Sets up a translate matrix.
	Errors:		None.

********************************************************************************************/

XMatrix::XMatrix(const XLONG x, const XLONG y)
{
	a = (FIXED16) 1;
	b = (FIXED16) 0;
	c = (FIXED16) 0;
    d = (FIXED16) 1;
    e = x;
    f = y;
}


XMatrix::XMatrix(const INT32 x, const INT32 y)
{
	a = (FIXED16) 1;
	b = (FIXED16) 0;
	c = (FIXED16) 0;
    d = (FIXED16) 1;
    e = x;
    f = y;
}
		
/********************************************************************************************

>	XMatrix::XMatrix (const FIXED16& ca,
					  const FIXED16& cb,
					  const FIXED16& cc,
					  const FIXED16& cd,
					  const XLONG    ce,
					  const XLONG    cf
					 ) 

	Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/7/93
	Inputs:		All six parameters which make up an Xmatrix
	Outputs:	None
	Returns:	None.
	Purpose:	Initialise a whole XMatrix.
	Errors:		None.

********************************************************************************************/

XMatrix::XMatrix( const FIXED16& ca,
				  const FIXED16& cb,
				  const FIXED16& cc,
				  const FIXED16& cd,
				  const XLONG    ce,
				  const XLONG    cf
				 ) 
{
	a = ca;
	b = cb;
	c = cc;
    d = cd;
    e = ce;
    f = cf;
}
	
/********************************************************************************************

>	void XMatrix::transform(WorkCoord pts[], UINT32 count) 

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		result - points to be translated.
				count - number of points.
	Outputs:	None
	Returns:	None.
	Purpose:	Transforms a list of points.
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

void XMatrix::transform(WorkCoord pts[], UINT32 count ) 
{                    
	UINT32 i;
	XLONG tx;		// Holds INPUT value of pts[i].x for use in second MatrixCalc
	
	for (i = 0; i < count; i++)
	{
		tx = pts[i].x;
		XMatrixCalc(a, tx, c, pts[i].y, RESULT pts[i].x);
		pts[i].x += e;
		XMatrixCalc(b, tx, d, pts[i].y, RESULT pts[i].y);
		pts[i].y += f;
	}
}

/********************************************************************************************

>	void XMatrix::transform(WorkCoord pts[], const WorkCoord input[], UINT32 count)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		input - points to be translated.
				count - number of points.
	Outputs:	result points translated.
	Returns:	None.
	Purpose:	Transforms a list of points.
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

void XMatrix::transform(WorkCoord pts[], const WorkCoord input[], UINT32 count) 
{
	UINT32 i;
	
	for (i = 0; i < count; i++)
	{
		XMatrixCalc(a, input[i].x, c, input[i].y, RESULT pts[i].x);  
		pts[i].x += e;
		XMatrixCalc(b, input[i].x, d, input[i].y, RESULT pts[i].y);
		pts[i].y += f;
	}
}

/********************************************************************************************

>	XMatrix& XMatrix::operator=(const Matrix& rhs) 

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		rhs - matrix to be assigned.
	Outputs:	None.
	Returns:	None.
	Purpose:	Matrix assignment.
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

XMatrix& XMatrix::operator=(const XMatrix& rhs) 
{
	this->a = rhs.a;
	this->b = rhs.b;
	this->c = rhs.c;
	this->d = rhs.d;
	this->e = rhs.e;
	this->f = rhs.f;
				 
	return *this;
}				 
				 
/********************************************************************************************

>	XMatrix XMatrix::operator*(const XMatrix& operand1, const XMatrix& operand2) 

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		Two matrices to be multiplied.
	Outputs:	None.
	Friend:		Matrix
	Returns:	result of multiplication.
	Purpose:	Matrix multiplication.  Cannot be used in a nested form as the result is
				contained in a static local (e.g. a = (b*c)*(d*e) will fail).
	Errors:		None.

********************************************************************************************/


XMatrix operator*(const XMatrix& op1, const XMatrix& op2) 
{
	static XMatrix result;
	
	result.a = ((op1.a * op2.a) + (op1.b * op2.c));
	result.b = ((op1.a * op2.b) + (op1.b * op2.d));
	result.c = ((op1.c * op2.a) + (op1.d * op2.c));
	result.d = ((op1.c * op2.b) + (op1.d * op2.d));

	XMatrixCalc(op2.a, op1.e, op2.c, op1.f, RESULT result.e);
	result.e += op2.e;
	XMatrixCalc(op2.b, op1.e, op2.d, op1.f, RESULT result.f);
	result.f += op2.f;
			
	return result;	
}					
					
/********************************************************************************************
					
>	XMatrix& XMatrix::operator*=(const XMatrix& op) 

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		Matrix to be multiplied.
	Outputs:	None.
	Friend:		Matrix
	Returns:	result of multiplication.
	Purpose:	Overloads the *= operator for Matrices.
	Errors:		None.

********************************************************************************************/


XMatrix& XMatrix::operator*=(const XMatrix& op) 
{
	XMatrix temp;
	
	temp.a =  ((a * op.a) + (b * op.c));
	temp.b =  ((a * op.b) + (b * op.d));
	temp.c =  ((c * op.a) + (d * op.c));
	temp.d =  ((c * op.b) + (d * op.d));
	XMatrixCalc(op.a, e, op.c, f, RESULT temp.e);
	temp.e += op.e;
	XMatrixCalc(op.b, e, op.d, f, RESULT temp.f);
	temp.f += op.f;
	
	*this = temp;
	
	return *this;
}



/********************************************************************************************

>	void XMatrix::transform(WorkCoord* pt) 

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/5/93
	Inputs:		result - points to be transformed.
	Outputs:	None
	Returns:	None.
	Purpose:	Transforms a single point.
	Errors:		None.

********************************************************************************************/

void XMatrix::transform(WorkCoord* pt) 
{                    
	XLONG tx = pt->x;		// Holds INPUT value of x for use in second MatrixCalc

	XMatrixCalc(a, tx, c, pt->y, RESULT pt->x);  
	pt->x += e;
	XMatrixCalc(b, tx, d, pt->y, RESULT pt->y);
	pt->y += f;
}
