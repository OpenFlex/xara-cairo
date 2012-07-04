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


class StringBase;

/*
 */ 

/*********************************************************************************************

>	class FIXED16

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/1993
	SeeAlso:	CCMaths.h
	SeeAlso:	Fixedasm.h
	SeeAlso:	Div32By32
	SeeAlso:	Keyword FIXED16
	Purpose:	
		An FIXED16 is a signed 32-bit value with a binary point between bits 15 and 16. 
		Its purpose is to represent 32-bit floating point numbers.
		FIXED16 is a fixed point number contained within a 32-bit longword.
		The high 16-bit half contains the integer part, the low half the fractional. (Intel
		implementations store this as the low half first in memory). The integer half ranges
		from -32768 to 32767, the fractional part from 0 to 65535/65536ths (1/65536th=
		0.000015259, 65535/65536=0.999984741). For efficiency all primitives are written
		in assembly-language, though most are used transparently by operator overloading.
		No-one should include fixed16.h directly - always use ccmath.h. You should also
		never use the lower-case type 'fixed16' - always used 'FIXED16'.    
    Errors:		None.
 	
********************************************************************************************/

#ifndef INC_FIXED16
#define INC_FIXED16

// One as a fixed16 as a longword, and 0.5 as...
const INT32 FIXED16_ONE = 0x10000L;
const INT32 FIXED16_HALF= 0x08000L;

#if !defined(USE_NATIVE_XLONG)
class CCAPI xlong;
#endif

class CCAPI String;

class CCAPI fixed16
{
public:
	INT32 all;



public:

	#define	F16SHIFT 16									// marks binary point position

	// this converts a short into a fixed16 longword by casting to an INT32 then shifting it
	#define	SHORT_FIXED(x)	( ((INT32)(x)) << F16SHIFT )

	inline fixed16() {};				
	inline fixed16(const fixed16&);
	inline fixed16(INT32);
	inline fixed16(short);
	inline fixed16(double);

	fixed16& Sin();
	fixed16& Cos();

	inline fixed16 trunc() const;
	inline fixed16 round() const;
	inline fixed16 abs() const;
	inline fixed16 sgn() const;
    
    void ToString(StringBase* out) const;

	// Friend Functions

	inline friend fixed16 Div32By32(const INT32 a, const INT32 b);
	inline friend fixed16 CCAPI operator+ (const fixed16&, const fixed16&);
	inline friend fixed16 CCAPI operator- (const fixed16&, const fixed16&);
	inline friend fixed16 CCAPI operator- (const fixed16&);
	inline friend fixed16 CCAPI operator* (const fixed16&, const fixed16&);
	inline friend fixed16 CCAPI operator/ (const fixed16&, const fixed16&);
	inline friend fixed16 CCAPI operator>> (const fixed16&, UINT32);
	inline friend fixed16 CCAPI operator<< (const fixed16&, UINT32);

	// Relational Operators
    
    inline friend INT32 CCAPI operator== (const fixed16&, const fixed16&);
    inline friend INT32 CCAPI operator== (const fixed16&, const short);
    inline friend INT32 CCAPI operator!= (const fixed16&, const fixed16&);
    inline friend INT32 CCAPI operator!= (const fixed16&, const short);
    inline friend INT32 CCAPI operator> (const fixed16&, const fixed16&);
    inline friend INT32 CCAPI operator> (const fixed16&, const short);
    inline friend INT32 CCAPI operator< (const fixed16&, const fixed16&);
    inline friend INT32 CCAPI operator< (const fixed16&, const short);
    inline friend INT32 CCAPI operator>= (const fixed16&, const fixed16&);
    inline friend INT32 CCAPI operator>= (const fixed16&, const short);
    inline friend INT32 CCAPI operator<= (const fixed16&, const fixed16&);
    inline friend INT32 CCAPI operator<= (const fixed16&, const short);
    
	// Assignment Operators

	inline fixed16& operator= (const fixed16&);
	inline fixed16& operator= (const INT32);
	inline fixed16& operator= (const short);
	inline fixed16& operator= (const double);
	inline fixed16& operator+= (const fixed16&);
	inline fixed16& operator+= (const short);
	inline fixed16& operator-= (const fixed16&); 
	inline fixed16& operator-= (const short);
	inline fixed16& operator*= (const fixed16&); 
	inline fixed16& operator*= (const short);
	inline fixed16& operator/= (const fixed16&);
	inline fixed16& operator/= (const short); 
	inline fixed16& operator<<= (const UINT32); 
	inline fixed16& operator>>= (const UINT32); 

	// Increment\Decrement Operators

	inline fixed16& operator++ ();							// prefix
	inline fixed16 operator++ (INT32);						// postfix 
	inline fixed16& operator-- ();							// prefix 
	inline fixed16 operator-- (INT32);						// postfix 

	// Conversion functions

	inline INT32 	 MakeInt() const;
	inline short MakeShort() const;
	inline double MakeDouble() const;
	inline INT32  MakeLong() const;
	inline xlong MakeXlong() const;

	inline static fixed16 FromRawLong(INT32 d);
	inline static fixed16 FromShifted16(INT32 d);
	inline INT32 GetRawLong() const;
	inline INT32 GetShifted16() const;
};


// this is a temporary kludge for the 32-bit MS compiler
#define	F16ASSIGN( it )		it
#define	F16ASSIGNTHIS		*this

#include "fixed.h"

/********************************************************************************************

Note that all the comment blocks live in the cpp files so they get compiled in with the help
compiler

********************************************************************************************/

#define FIXED16_DBL(d) fixed16::FromRawLong((INT32)((d)*65536))

inline fixed16::fixed16(const fixed16& initValue) 
{
	all = initValue.all;
}

inline fixed16::fixed16(INT32 initValue) 
{
	all = SHORT_FIXED( initValue );
}

inline fixed16::fixed16(short initValue) 
{
	all = SHORT_FIXED( initValue );
}

inline fixed16::fixed16(double initValue) 
{
	*this = DoubleToFixed16(initValue);
}

inline fixed16 fixed16::FromRawLong(INT32 d)
{
	fixed16 temp;
	temp.all = d;
	return temp;
}

inline fixed16 fixed16::FromShifted16(INT32 d)
{
	fixed16 temp;
	temp.all = d;
	return temp;
}

inline INT32 fixed16::MakeInt() const
{
	return (INT32) (all >> F16SHIFT);
}

inline short fixed16::MakeShort() const
{
	return (short) (all >> F16SHIFT);
}

inline INT32 fixed16::MakeLong() const
{
	return all >> F16SHIFT;
}

inline xlong fixed16::MakeXlong() const
{
    return xlong( (short) (all >> F16SHIFT) );
}


inline fixed16& fixed16::operator= (const fixed16& operand)
{ 
	this->all = operand.all;
	
	return *this; 
}

inline double fixed16::MakeDouble() const
{
	return Fixed16ToDouble(*this);
}

inline fixed16& fixed16::operator= (const short operand)
{ 
	this->all = SHORT_FIXED( operand );
	return *this;
}

inline INT32 fixed16::GetRawLong() const
{
	return this->all;
}

inline INT32 fixed16::GetShifted16() const
{
	return this->all;
}

inline fixed16 fixed16::trunc() const
{
	return FromRawLong( all & 0xFFFF0000L );
}
	
inline fixed16 fixed16::round() const
{
	return FromRawLong( ( all + FIXED16_HALF ) & 0xFFFF0000L );
}
	
inline fixed16 fixed16::abs() const
{
	return FromRawLong( all<0 ? -all : all );
}
	
inline fixed16 fixed16::sgn() const
{
	return FromRawLong( all<0 ? -FIXED16_ONE : FIXED16_ONE );
}
	
inline fixed16 operator+ (const fixed16& operand1, const fixed16& operand2)
{
	fixed16 result;
	result.all = operand1.all + operand2.all;
	return result;
}

inline fixed16 operator- (const fixed16& operand1, const fixed16& operand2)
{
	fixed16 result;
	result.all = operand1.all - operand2.all;
	return result;
}

inline fixed16 operator- (const fixed16& operand)
{
	fixed16 temp;
	temp.all = -operand.all;
	return temp;
}

inline fixed16 operator* (const fixed16& operand1, const fixed16& operand2)
{
	fixed16 result;
	F16ASSIGN(result) = Fixed16Mul( operand1, operand2 );
	return result;
}

inline fixed16 operator/ (const fixed16& operand1, const fixed16& operand2)
{
	fixed16 result;
	F16ASSIGN(result) = Fixed16Div( operand1, operand2 );
	return result;
}

inline fixed16 operator>> (const fixed16& operand1, UINT32 operand2)
{
	fixed16 result;
	result.all = operand1.all >> operand2;
	return result;
}

inline fixed16 operator<< (const fixed16& operand1, UINT32 operand2)
{
	fixed16 result;
	
	result.all = operand1.all << operand2;
	
	return result;
}

inline INT32 operator== (const fixed16& operand1, const fixed16& operand2) 
{
	return operand1.all == operand2.all;
}

inline INT32 operator== (const fixed16& operand1, const short operand2) 
{
	return operand1.all == SHORT_FIXED( operand2 );
}

inline INT32 operator!= (const fixed16& operand1, const fixed16& operand2) 
{
	return operand1.all != operand2.all;
}

inline INT32 operator!= (const fixed16& operand1, const short operand2) 
{
	return operand1.all != SHORT_FIXED( operand2 );
}

inline INT32 operator> (const fixed16& operand1, const fixed16& operand2) 
{
	return operand1.all > operand2.all;
}

inline INT32 operator> (const fixed16& operand1, const short operand2) 
{
	return operand1.all > SHORT_FIXED(operand2);
}

inline INT32 operator< (const fixed16& operand1, const fixed16& operand2) 
{
	return operand1.all < operand2.all;
}

inline INT32 operator< (const fixed16& operand1, const short operand2) 
{
	return operand1.all < SHORT_FIXED( operand2 );
}

inline INT32 operator>= (const fixed16& operand1, const fixed16& operand2) 
{
	return operand1.all >= operand2.all;
}

inline INT32 operator>= (const fixed16& operand1, const short operand2) 
{
	return operand1.all >= SHORT_FIXED( operand2 );
}

inline INT32 operator<= (const fixed16& operand1, const fixed16& operand2) 
{
	return operand1.all <= operand2.all;
}

inline INT32 operator<= (const fixed16& operand1, const short operand2) 
{
	return operand1.all <= SHORT_FIXED( operand2 );
}

inline fixed16& fixed16::operator= (const INT32 operand)
{
	this->all = SHORT_FIXED( operand );
	return *this;
}

inline fixed16& fixed16::operator= (const double operand)
{ 
	F16ASSIGNTHIS = DoubleToFixed16(operand);
	return *this;
}

inline fixed16& fixed16::operator+= (const fixed16& operand)
{ 
	this->all += operand.all;
	return *this;
}

inline fixed16& fixed16::operator+= (const short operand)
{ 
	this->all += SHORT_FIXED( operand );
	return *this;
}

inline fixed16& fixed16::operator-= (const fixed16& operand)
{
	this->all -= operand.all;
	return *this;
}

inline fixed16& fixed16::operator-= (const short operand)
{
	this->all -= SHORT_FIXED( operand );
	return *this;
}

inline fixed16& fixed16::operator*= (const fixed16& operand)
{
	F16ASSIGNTHIS = Fixed16Mul(*this, operand);
	
	return *this;
}

inline fixed16& fixed16::operator*= (const short operand)
{                                  
	fixed16 temp;
	
	temp.all = SHORT_FIXED( operand );
	
	F16ASSIGNTHIS = Fixed16Mul(*this, temp);
	
	return *this;
}

inline fixed16& fixed16::operator/= (const fixed16& operand)
{
	F16ASSIGNTHIS = Fixed16Div(*this, operand);
	
	return *this;
}

inline fixed16& fixed16::operator/= (const short operand)
{
	fixed16 temp;
	
	temp.all = SHORT_FIXED( operand );
	
	F16ASSIGNTHIS = Fixed16Div(*this, temp);
	
	return *this;
}

inline fixed16& fixed16::operator<<= (const UINT32 operand)
{
	this->all <<= operand;
	return *this;
}
  
inline fixed16& fixed16::operator>>= (const UINT32 operand)
{
	this->all >>= operand;
	return *this;
} 

inline fixed16& fixed16::operator++ ()							// prefix
{
	this->all += FIXED16_ONE;
	return *this;
}

inline fixed16 fixed16::operator++ (INT32 dummy)   				// postfix 
{                
	fixed16 result = *this;
	
	this->all += FIXED16_ONE;
	
	return result;
}

inline fixed16& fixed16::operator-- ()							// prefix 
{
	this->all -= FIXED16_ONE;
	return *this;
}

inline fixed16 fixed16::operator-- (INT32 dummy)				// postfix 
{
	fixed16 result = *this;
	
	this->all -= FIXED16_ONE;
	
	return result;
}
	
#endif
