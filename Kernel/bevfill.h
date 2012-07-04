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


#ifndef _BEVFILL_H
#define _BEVFILL_H

/******************************************************************************************

>	class CBevelFill : public SimpleCCObject

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/10/98

	Purpose:	Abstract base class for all fill types

	SeeAlso:	CBeveler

******************************************************************************************/

class CBevelFill : public CCObject
{
	CC_DECLARE_DYNAMIC(CBevelFill);


public:
	// Pos is between 0 (i.e. on the bevel path) and 1 (i.e. on the inner/outer path)
	virtual COLORREF CalcPixelValue(BYTE value, double Pos, INT32 Contrast) = 0;

	// ensures that the value is in the range 1 to 254 to make
	// sure it can be cast as a BYTE
	void EnsureValueRange(double *value);
} ;

/******************************************************************************************

>	class CBevelFillFlat : public CBevelFill

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/10/98

	Purpose:	Do a flat fill

	SeeAlso:	CBeveler

******************************************************************************************/

class CBevelFillFlat : public CBevelFill
{
	CC_DECLARE_DYNAMIC(CBevelFillFlat);


public:
	COLORREF CalcPixelValue(BYTE value, double Pos, INT32 Contrast);
} ;


/******************************************************************************************

>	class CBevelFillRound : public CBevelFill

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/10/98

	Purpose:	Do a rounded fill

	SeeAlso:	CBeveler

******************************************************************************************/

class CBevelFillRound : public CBevelFill
{
	CC_DECLARE_DYNAMIC(CBevelFillRound);

public:
	COLORREF CalcPixelValue(BYTE value, double Pos, INT32 Contrast);
} ;


/******************************************************************************************

>	class CBevelFillSquare : public CBevelFill

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/10/98

	Purpose:	Do a rounded fill

	SeeAlso:	CBeveler

******************************************************************************************/

class CBevelFillSquare : public CBevelFill
{
	CC_DECLARE_DYNAMIC(CBevelFillSquare);

public:
	COLORREF CalcPixelValue(BYTE value, double Pos, INT32 Contrast);
} ;

/******************************************************************************************

>	class CBevelFillFrame : public CBevelFill

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/10/98

	Purpose:	Do a rounded fill

	SeeAlso:	CBeveler

******************************************************************************************/

class CBevelFillFrame : public CBevelFill
{
	CC_DECLARE_DYNAMIC(CBevelFillFrame);

public:
	COLORREF CalcPixelValue(BYTE value, double Pos, INT32 Contrast);
} ;

/******************************************************************************************

>	class CBevelFillSmooth : public CBevelFill

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/10/98

	Purpose:	Do a smoothed fill

	SeeAlso:	CBeveler

******************************************************************************************/

class CBevelFillSmooth : public CBevelFill
{
	CC_DECLARE_DYNAMIC(CBevelFillSmooth);

public:
	COLORREF CalcPixelValue(BYTE value, double Pos, INT32 Contrast);
} ;

/******************************************************************************************

>	class CBevelFillPoint : public CBevelFill

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/2/99

	Purpose:	Do a pointy fill

	SeeAlso:	CBeveler

******************************************************************************************/

class CBevelFillPoint : public CBevelFill
{
	CC_DECLARE_DYNAMIC(CBevelFillPoint);

public:
	COLORREF CalcPixelValue(BYTE value, double Pos, INT32 Contrast);
} ;

/******************************************************************************************

>	class CBevelFillRuffle : public CBevelFill

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/10/98

	Purpose:	Do a ruffle fill

	SeeAlso:	CBeveler

******************************************************************************************/

class CBevelFillRuffle : public CBevelFill
{
	CC_DECLARE_DYNAMIC(CBevelFillRuffle);

public:
	COLORREF CalcPixelValue(BYTE value, double Pos, INT32 Contrast);
} ;

/******************************************************************************************

>	class CBevelFills : public SimpleCCObject

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/10/98

	Purpose:	Encapsulates all the bevel filling stuff

	SeeAlso:	CBeveler

******************************************************************************************/

class CBevelFills : public CCObject
{
	CC_DECLARE_DYNAMIC(CBevelFills);

public:
	CBevelFills();
	~CBevelFills();

	COLORREF CalcPixelValue(BYTE value, INT32 bevType, double Pos, INT32 Contrast);
private:
	CBevelFill **m_pBevFills;

	// set up the above
	BOOL SetUpFills();

	INT32 m_NumFills;
} ;





#endif
