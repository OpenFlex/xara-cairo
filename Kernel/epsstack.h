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


#ifndef INC_EPSSTACK_H
#define INC_EPSSTACK_H

#include "fixst256.h"
#include "list.h"
#include "doccoord.h"
#include "doccolor.h"

class StringBase;

// Special class for floating point values held as fixed point (would be a typedef except
// we then can't overload INT32s and FIXEDPOINTs).
class FIXEDPOINT
{
public:
	INT32 Long;
	void FromAscii(const TCHAR *FltPtString);
	operator INT32() const { return (INT32) Long; }
	FIXEDPOINT& operator= (INT32 Val) { this->Long = Val; return *this; }
};

// The scaling factor used to store fixed point values on the EPSStack.
const INT32 FixedPointScale = 1000;

// EPSType enumerated type - all the kinds of objects that can be pushed onto the stack
typedef enum
{
	EPSTYPE_EMPTY,
	EPSTYPE_NONE,
	EPSTYPE_INT32,
	EPSTYPE_FIXEDPOINT,
	EPSTYPE_DOUBLE,
	EPSTYPE_STRING,
	EPSTYPE_NAME,
	EPSTYPE_COMMAND
} EPSType;

typedef enum
{
	TINT_NONE,
	TINT_ILLUSTRATOR,
	TINT_COREL
} TintType;

// Forward reference for the EPSStack class
class EPSStackItem;
class EPSFilter;

typedef UINT32 EPSCommand;

/********************************************************************************************

>	class EPSStack : public List

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Purpose:	Provides a heterogeneous stack for use when reading PostScript (EPS) files.
				Graeme (30/5/00) - I've replaced the array implementation that Tim originally
				used with a linked list. The array was originally there as a performance
				tweak, but increased CPU power has made this a less perceiveable gain. By
				using a linked list, I've made the implementation a little more error
				tolerant, which means that files containing stranglely placed bitmaps are
				now loaded.
	SeeAlso:	EPSInputFilter; EPSStackItem

********************************************************************************************/

class EPSStack : public List
{
	CC_DECLARE_MEMDUMP(EPSStack)
	
public:
	EPSStack();
	~EPSStack();
	
	BOOL Push(const INT32);
	BOOL Push(const FIXEDPOINT);
	BOOL Push(const double);
	BOOL Push(const TCHAR*, BOOL IsName = FALSE);
	BOOL Push(const EPSCommand Cmd);
	
	BOOL Pop(INT32 *);
	BOOL Pop(UINT32 *);
	BOOL Pop(FIXEDPOINT *);
	BOOL Pop(double *);
	BOOL Pop(TCHAR*);
	BOOL Pop(StringBase*);

	BOOL PopCmd(EPSCommand*);
	BOOL PopCoord(INT32*);
	BOOL PopCoordPair(DocCoord*);
	BOOL PopColour(PColourCMYK *, 
				   TintType Tint = TINT_NONE, 
				   FIXEDPOINT *TintVal = NULL,
				   String_64 *pName = NULL);
		// (ChrisG 12/12/00) - Added for EPS support of RGB colours
	BOOL PopColourRGB (INT32 * red, INT32 * green, INT32 * blue,
					   TintType Tint = TINT_NONE, 
					   FIXEDPOINT *TintVal = NULL,
					   String_64 *pName = NULL);
	BOOL PopGrayScale(PColourCMYK *);

	BOOL Pop(Matrix *, BOOL);

	BOOL PopArray(INT32*, INT32*);
	
	BOOL Discard(UINT32 NumToDiscard = 1, BOOL EvenCommands = FALSE);
	BOOL DiscardArray();

	void SetCoordScaleFactor(INT32 NewScaleFactor);
	void SetCoordOrigin(DocCoord NewOrigin);
	void TranslateCoordOrigin(MILLIPOINT dx, MILLIPOINT dy);

	void SetXformMatrix(Matrix&);
	void SetNoXformMatrix();
	
	EPSType GetType();
	EPSCommand ReadCmd();
	
	void Dump(EPSFilter *);

	BOOL IsEmpty();
	
private:
	// Member variables.
	INT32 ScaleFactor;
	DocCoord Origin;

	Matrix XformMatrix;
	BOOL UseXformMatrix;
};

#endif

