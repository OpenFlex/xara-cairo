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

/********************************************************************************************

>	class XLONG

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/1993
	SeeAlso:	CCMaths.h
	SeeAlso:	Xlongasm.h
	SeeAlso:	Mul64Div32
	Purpose:	
		An XLONG is a signed 64-bit value. Its purpose is to represent very large numbers.
	Errors:		None.

********************************************************************************************/

#ifndef INC_XLONG
#define INC_XLONG

class CCAPI fixed16;

#if defined(USE_NATIVE_XLONG)

#if defined(__WXMSW__)
typedef __int64			xlong;
#else
typedef INT64		xlong;
#endif

xlong &operator*=( xlong &, fixed16 );
xlong operator*( const xlong &, fixed16 );

#else

class CCAPI xlong
{
private:
	UINT32 low;
	INT32 high;
public:
	// Constructors

	inline xlong() {};				
	inline xlong(const xlong&);
	inline xlong(INT32);	
	inline xlong(INT32);	
	
	void ToString(String* out) const;

	// Friend Functions - Basic Operators 

	friend xlong CCAPI operator+ (const xlong&, const xlong&);
	friend xlong CCAPI operator+ (const xlong&, INT32); 
	friend xlong CCAPI operator+ (const xlong&, INT32); 
	
	friend xlong CCAPI operator- (const xlong&, const xlong&);
	friend xlong CCAPI operator- (const xlong&, INT32);  
	friend xlong CCAPI operator- (const xlong&, INT32);  
	friend xlong CCAPI operator- (const xlong&);
	
	friend xlong CCAPI operator* (const xlong&, const xlong&);
	friend xlong CCAPI operator* (const xlong&, INT32);  
	friend xlong CCAPI operator* (const xlong&, INT32);  
	friend xlong CCAPI operator* (const xlong&, fixed16);  
	
	friend xlong CCAPI operator/ (const xlong&, const xlong&);
	friend xlong CCAPI operator/ (const xlong&, INT32); 
	friend xlong CCAPI operator/ (const xlong&, INT32); 
	
	friend xlong CCAPI operator>> (const xlong&, UINT32);
	friend xlong CCAPI operator<< (const xlong&, UINT32);

	// Relational operators

	friend INT32 CCAPI operator== (const xlong&, const xlong&);
	friend INT32 CCAPI operator== (const xlong&, INT32);
	friend INT32 CCAPI operator== (const xlong&, INT32);

	friend INT32 CCAPI operator!= (const xlong&, const xlong&);
	friend INT32 CCAPI operator!= (const xlong&, INT32);
	friend INT32 CCAPI operator!= (const xlong&, INT32);
	
	friend INT32 CCAPI operator< (const xlong&, const xlong&);
	friend INT32 CCAPI operator< (const xlong&, INT32); 
	friend INT32 CCAPI operator< (const xlong&, INT32);
	
	friend INT32 CCAPI operator> (const xlong&, const xlong&);
	friend INT32 CCAPI operator> (const xlong&, INT32); 
	friend INT32 CCAPI operator> (const xlong&, INT32);
	
	friend INT32 CCAPI operator<= (const xlong&, const xlong&);
	friend INT32 CCAPI operator<= (const xlong&, INT32);
	friend INT32 CCAPI operator<= (const xlong&, INT32);
	
	friend INT32 CCAPI operator>= (const xlong&, const xlong&);
	friend INT32 CCAPI operator>= (const xlong&, INT32);
	friend INT32 CCAPI operator>= (const xlong&, INT32);

	// Assignment Operators
	
	xlong& CCAPI operator= (const xlong&);
	xlong& CCAPI operator= (INT32);  
	
	xlong& CCAPI operator+= (const xlong&);
	xlong& CCAPI operator+= (INT32); 
	
	xlong& CCAPI operator-= (const xlong&); 
	xlong& CCAPI operator-= (INT32);   
	
	xlong& CCAPI operator*= (const xlong&); 
	xlong& CCAPI operator*= (INT32);
	xlong& CCAPI operator*= (fixed16);
	
	xlong& CCAPI operator/= (const xlong&); 
	xlong& CCAPI operator/= (INT32 ); 
	
	xlong& CCAPI operator<<= (UINT32); 
	xlong& CCAPI operator>>= (UINT32); 

	// Increment\Decrement Operators

	xlong& CCAPI operator++ ();							// prefix
	xlong CCAPI operator++ (INT32);						// postfix   
	
	xlong& CCAPI operator-- ();							// prefix 
	xlong CCAPI operator-- (INT32);						// postfix 
	
	// Integer Conversion

	inline INT32 MakeLong () const;								
	inline INT32 MakeInt () const;
	inline double MakeDouble () const;
	fixed16 MakeFixed16 () const;
			
	operator INT32() const { return (INT32)low; }

	void GetHighLow(INT32* pdwHigh, UINT32* pdwLow) const;
	void SetHighLow(INT32 dwHigh, UINT32 dwLow);
};

// Constructors

/********************************************************************************************

>	inline XLONG::XLONG () 

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Default Constructor for the XLONG class. Its do not actually do anything!
	Errors:		None.

********************************************************************************************/

/********************************************************************************************

>	inline XLONG::XLONG (const XLONG& initValue) 

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/93
	Inputs:		XLONG initilisation value.
	Outputs:	None
	Returns:	None.
	Purpose:	Initialise an XLONG to a specific value
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

inline xlong::xlong(const xlong& initValue)
{				 
	this->low = initValue.low;
	this->high = initValue.high;
}

/********************************************************************************************
						
>	inline XLONG::XLONG (INT32 initValue) 

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/93
	Inputs:		Long initilisation value.
	Outputs:	None
	Returns:	None.
	Purpose:	Initialise an XLONG to a specific value
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

inline xlong::xlong(INT32 initValue)
{				 
	xlong temp;

	LongToXlong(initValue, temp);		// convert initValue from INT32 to xlong 

	this->low = temp.low;
	this->high = temp.high;
}

/********************************************************************************************
						
>	inline XLONG::XLONG (INT32 initValue) 

	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/93
	Inputs:		Integer initilisation value.
	Outputs:	None
	Returns:	None.
	Purpose:	Initialise an XLONG to a specific value
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

inline xlong::xlong(INT32 initValue)
{				 
	xlong 	temp;
	INT32  	initTemp = initValue;

	LongToXlong(initTemp, temp);		// convert initValue from INT32 to xlong 

	this->low = temp.low;
	this->high = temp.high;
}

/********************************************************************************************

>	inline INT32 XLONG::MakeLong () const
 	
	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/93
	SeeAlso:	XlonToLong()
	Inputs:		None.
	Outputs:	None.
	Returns:	Long value.
	Purpose:	To convert an XLONG value to a INT32. 
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/
  
inline INT32 xlong::MakeLong () const
{
	return XlongToLong( *this );
}

/********************************************************************************************

>	inline INT32 XLONG::MakeInt () const
 	
	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/93
	SeeAlso:	MakeLong
	Inputs:		None.
	Outputs:	None.
	Returns:	INT32 value.
	Purpose:	To convert an XLONG value to an integer. 
	Errors:		None.
		If XLONG is not in the integer range this will produce some unexpected 
		results.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

inline INT32 xlong::MakeInt() const
{ 
	return (INT32) this->MakeLong();	
}                              

/********************************************************************************************

>	inline double XLONG::MakeDouble () const
 	
	Author: 	Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/4/93
	SeeAlso:	XlongToDouble()
	Inputs:		None.
	Outputs:	None.
	Returns:	INT32 value.
	Purpose:	To convert an XLONG value to a double. 
	Errors:		None.

********************************************************************************************/
/*
Technical notes:

********************************************************************************************/

inline double xlong::MakeDouble() const
{
	return XlongToDouble(*this); 
}


/********************************************************************************************
>	inline void xlong::GetHighLow(INT32* pdwHigh, UINT32* pdwLow) const

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/94
	Inputs:		Pointers to a INT32 and UINT32 that will receive the high and low parts
				of the xlong.
	Outputs:	-
	Returns:	-
	Purpose:	Used when serializing XLONGs
	Errors:		-
	SeeAlso:	xlong::SetHighLow
********************************************************************************************/


inline void xlong::GetHighLow(INT32* pdwHigh, UINT32* pdwLow) const
{
	*pdwHigh = high;
	*pdwLow = low;
}



/********************************************************************************************
>	inline void xlong::SetHighLow(INT32 dwHigh, UINT32 dwLow)

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/94
	Inputs:		The high and low part of the xlong
	Outputs:	-
	Returns:	-
	Purpose:	Used when serializing XLONGs.
	Errors:		-
	SeeAlso:	xlong::GetHighLow
********************************************************************************************/

inline void xlong::SetHighLow(INT32 dwHigh, UINT32 dwLow)
{
	high = dwHigh;
	low = dwLow;
}

#endif

// prottypes for maths routines. This must be kept in snyc
// with the maths routines themselves, currently:
// xlong.cpp

// beware that although references are used to pass some parameters,
// this may not always be the case. For example, if it is more efficient then
// some versions might just pass the parameters directly

// Note that the some reference parameters get modified by these calls
// Although this is contrary to the Style Guide, this is the only way we can alter
// the calling convention without breaking existing code


// These functions are private to the xlong class - no-one else should call them
// hence the use of xlong in lower-case

extern "C"
{

// these are dyadic fns which take two input args and return a third
	void XlongAdd( const xlong& ,const xlong& , xlong& );
	void XlongSub( const xlong& ,const xlong& , xlong& );
	void XMul64(   const xlong& ,const xlong& , xlong& );
	void XDiv64(   const xlong& ,const xlong& , xlong& );
	void XlongAsl64( const xlong& input, INT32 shift, xlong& result);
	void XlongAsr64( const xlong& input, INT32 shift, xlong& result);

// these are dyadic fns who pass a reference which is modified by the calls, hence
// the use of the One postfix on the names
	void XlongAddOne( const xlong& , xlong& );
	void XlongSubOne( const xlong& , xlong& );
	void XMul64One(   const xlong& , xlong& );
	void XDiv64One(   const xlong& , xlong& );
	void XlongNegOne( xlong& );
	void XlongAsl64One( INT32 shift, xlong& result);
	void XlongAsr64One( INT32 shift, xlong& result);

// xlong conversion functions
	void LongToXlong( const INT32, xlong& );
	INT32 XlongToLong( const xlong& );
	double XlongToDouble( const xlong& );
	void DoubleToXlong( const double, xlong& );

// xlong comparison functions
	INT32 XlongCmpGT( const xlong& first, const xlong& second);
	INT32 XlongCmpGE( const xlong& first, const xlong& second);
	INT32 XlongCmpLT( const xlong& first, const xlong& second);
	INT32 XlongCmpLE( const xlong& first, const xlong& second);
	INT32 XlongCmpEQ( const xlong& first, const xlong& second);
	INT32 XlongCmpNE( const xlong& first, const xlong& second);

// xlong inc & dec functions
	void XlongIncrement( xlong& );
	void XlongDecrement( xlong& );

// utility - might be useful to others: should it be in the public block below
	void XMul32(INT32, INT32, xlong& );

// string conversions
	void XlongToAscii( const xlong&, LPSTR );
	void XlongToUnicode( const xlong&, WCHAR * );


	void XlongByFixed16One( xlong*, fixed16 );

	
};

// these functions can be called by others
// although they are prototyped using xlong, params should always be passed as XLONG
// the lower-case version is to allow this file to be included correctly by ccmath.cpp

extern "C"
{
	INT32 Mul32Div32( INT32, INT32, INT32 );
#ifndef WIN32
	xlong Mul64Div32( xlong, xlong, INT32);
#endif
	void XMatrixCalc( fixed16, const xlong&, fixed16, const xlong&, xlong& );
};

#endif
