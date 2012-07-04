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



#include "camtypes.h"
//#include "fixed.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "xlong.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ccmaths.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "fixed16.h" - in camtypes.h [AUTOMATICALLY REMOVED]

DECLARE_SOURCE("$Revision: 1282 $");


/********************************************************************************************

>	XLONG Mul(const INT32 operand1, const INT32 operand2) 

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/93
	Inputs:		Two INT32 values
	SeeAlso:	Xlongasm.h
	Outputs:	None
	Returns:	A reference to an xlong with result of multiplication.
	Purpose:	Multiplication of two 32-bit signed numbers (xlongs). 
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

XLONG Mul(const INT32 operand1, const INT32 operand2)
{
	XLONG result;

	XMul32(operand1, operand2, result);

	return result;
}

/********************************************************************************************

>	XLONG Asl (const INT32, UINT32)

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/5/93
	Inputs:		INT32 - value to be shifted
				UINT32 - shift count
	Outputs:	None
	Returns:	XLONG - shifted number. 
	Purpose:	Performs arithmetic shift left. 
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

	Using the ASL provided with xlong for now.

********************************************************************************************/

XLONG Asl (const INT32 value, UINT32 shift)
{   
	XLONG result;
	
	result = MakeXLong(value);
	
	return 	(result << shift);

}

/********************************************************************************************

>	XLONG Asr (const INT32, UINT32)

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/5/93
	Inputs:		INT32 - value to be shifted
				UINT32 - shift count
	Outputs:	None
	Returns:	XLONG - shifted number. 
	Purpose:	Performs arithmetic shift right. 
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

	Using the ASR provided with xlong for now.

********************************************************************************************/

XLONG Asr (const INT32 value, UINT32 shift)
{   
	return ( XLONG(value) >> shift);
}

/********************************************************************************************

>	INT32 MulDiv32By32(const INT32 operand1, const INT32 operand2, const INT32 operand3) 

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/5/93
	SeeAlso:	Xlongasm.h
	Inputs:		operand1 - multiplicand 1
				operand2 - multiplicand 2
				operand3 - divisor
	Outputs:	None
	Returns:	INT32 -  result of multiply-divide. 
	Purpose:	Multiplies two 32-bit values and divides the result by another 32-bit value. 
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

INT32 MulDiv32By32(const INT32 operand1, const INT32 operand2, const INT32 operand3)  
{
	return Mul32Div32( operand1, operand2, operand3 );
}

/**********************************************************************************************

>	XLONG MakeXLong (const INT32 operand)
 	
	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/5/93
	SeeAlso:	Xlongasm.h
	Inputs:		Long value to be converted.
	Outputs:	None.
	Returns:	an xlong value.
	Purpose:	To convert an INT32 value to an xlong. 
	Errors:		None.

**********************************************************************************************/
/*
Technical notes:

**********************************************************************************************/
  								
XLONG MakeXLong (const INT32 operand)
{
	return XLONG(operand);
}

/**********************************************************************************************

>	XLONG MakeXLong (const double operand)
 	
	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/5/93
	SeeAlso:	Xlongasm.h
	Inputs:		double value to be converted.
	Outputs:	None.
	Returns:	an xlong value.
	Purpose:	To convert a double value to an xlong. 
	Errors:		None.

**********************************************************************************************/
/*
Technical notes:

**********************************************************************************************/
  								
XLONG MakeXLong(const double operand)
{
	xlong result;

	DoubleToXlong(operand, result);

	return result;
}
/********************************************************************************************

>	FIXED16 Div32By32( INT32 arg1, INT32 arg2 )

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/5/93
	Inputs:		two signed 32-bit numbers
	Outputs:	None
	Returns:	FIXED16 result of arg1/arg2
	Scope:		Private to the CCMATHS library.
	Purpose:	Obtain a fixed-point representation of the ratio between two signed
			numbers.
	Errors:		None. Div0 and overflow will create a div0 exception.
	See Also:	InternalDiv32by32

This fn is inline.

********************************************************************************************/

/********************************************************

< Maths Types
< Maths Conversion Table
< Conversion

comment:
\pard\plain
\trowd \trgaph108\trleft-108 
\cellx1593\cellx3294\cellx4995\cellx6696\cellx8397\cellx10098\pard\plain 
\qc \intbl \fs20\lang2057 {\b From}{\b  }{\b \\}{\b  }{\b To}{\b \cell }{\b INT32}{\b \cell }
{\b INT32}{\b \cell }{\b XLONG}{\b \cell }{\b FIXED16}{\b \cell }{\b double}{\b \cell }\row 
\qc\intbl {\b INT32}{\b \cell }-\cell auto
\cell constructor
\par operator=\cell constructor
\par operator=\cell auto\cell \pard \intbl \row \pard \qc\intbl {\b INT32}{\b \cell }
built-in cast\cell -\cell MakeXlong()
\par constructor
\par operator=
\par cast operator\cell operator=
\par constructor\cell auto\cell \pard \intbl \row \pard \qc\intbl {\b XLONG}{\b \cell }
MakeInt()\cell MakeLong()\cell -\cell MakeFixed16()\cell MakeDouble()\cell \pard 
\intbl \row \pard \qc\intbl {\b FIXED16}{\b \cell }MakeInt()\cell MakeLong()\cell 
MakeXlong()\cell -\cell MakeDouble()\cell \row \qc\intbl {\b double}
{\b \cell }explicit cast\cell explicit cast\cell MakeXlong()\cell operator=
\par constructor\cell -\cell \pard \intbl \row \pard 

******************************************************************/
