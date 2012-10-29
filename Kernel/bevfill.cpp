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
#include "bevfill.h"

CC_IMPLEMENT_DYNAMIC(CBevelFills, CCObject)
CC_IMPLEMENT_DYNAMIC(CBevelFill, CCObject)
CC_IMPLEMENT_DYNAMIC(CBevelFillFlat, CBevelFill)
CC_IMPLEMENT_DYNAMIC(CBevelFillRound, CBevelFill)
CC_IMPLEMENT_DYNAMIC(CBevelFillSquare, CBevelFill)
CC_IMPLEMENT_DYNAMIC(CBevelFillFrame, CBevelFill)
CC_IMPLEMENT_DYNAMIC(CBevelFillSmooth, CBevelFill)
CC_IMPLEMENT_DYNAMIC(CBevelFillRuffle, CBevelFill)
CC_IMPLEMENT_DYNAMIC(CBevelFillPoint, CBevelFill)

#define new CAM_DEBUG_NEW

// the value to set to be transparent in some fills
const double SplitValue = 213;

void CBevelFill::EnsureValueRange(double *value)
{
	if (*value > 254)
	{
		*value = 254;
	}
	else if (*value < 1)
	{
		*value = 1;
	}
}

/////////////////////////////////////////////////////////
// the CBevFills class

CBevelFills::CBevelFills()
{
	SetUpFills();
}

CBevelFills::~CBevelFills()
{
	for (INT32 i = 0 ; i < m_NumFills; i++)
	{
		TRACE( _T("deleting bevel fill %d\n"), i);
		delete m_pBevFills[i];
	}

	delete m_pBevFills;
	m_pBevFills = NULL;
}

/********************************************************************************************

>	BOOL CBevelFills::SetUpFills()

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/10/98
	Purpose:	Set up the bevel filling array
	Inputs:		
	Returns:	TRUE for success
	SeeAlso:	-

********************************************************************************************/

BOOL CBevelFills::SetUpFills()
{
	// set up the list first
	m_NumFills = 7;

	m_pBevFills = new CBevelFill *[m_NumFills];
	m_pBevFills[0] = new CBevelFillFlat;

	m_pBevFills[1] = new CBevelFillRound;

	m_pBevFills[2] = new CBevelFillSquare;

	m_pBevFills[3] = new CBevelFillFrame;

	m_pBevFills[4] = new CBevelFillSmooth;

	m_pBevFills[5] = new CBevelFillPoint;

	m_pBevFills[6] = new CBevelFillRuffle;

  	return TRUE;
}

COLORREF CBevelFills::CalcPixelValue(BYTE value, INT32 bevType, double Pos, INT32 Contrast)
{
	if (Pos < 0.00)
	{
		Pos = 0.00;
	}

	if (Pos >= 1.00)
	{
		Pos = 1.00;
	}

	if (bevType < 0 || bevType >= m_NumFills)
	{
		return m_pBevFills[0]->CalcPixelValue(value, Pos, Contrast);
	}
	
	return m_pBevFills[bevType]->CalcPixelValue(value, Pos, Contrast);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// all the fill class definitions

/********************************************************************************************

>	COLORREF CBevelFlatFill::CalcPixelValue(BYTE value, double Pos, INT32 Contrast);

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/11/98
	Purpose:	Do a flat fill
	Inputs:		
	Returns:	TRUE for success
	SeeAlso:	-

********************************************************************************************/

COLORREF CBevelFillFlat::CalcPixelValue(BYTE value, double Pos, INT32 Contrast)
{
	double RValue = value;
	double GValue = value;
	double BValue = value;
	double AValue = value;

	if (AValue < SplitValue)
	{
		AValue *= 255.0 / SplitValue;
	}
	else 
	{
		AValue = 255.0 - AValue;
		AValue *= 255.0 / (255.0 - SplitValue);

		AValue = 1.0 - (AValue / 255.0);
		AValue *= AValue;
		AValue = (1.0 - AValue) * 255.0;
	}
	
	AValue *= 200.0 / 255.0;

	RValue += 0.5;
	GValue += 0.5;
	BValue += 0.5;

	EnsureValueRange(&AValue);
	
	BYTE RByte = (BYTE)RValue;
	BYTE GByte = (BYTE)GValue;
	BYTE BByte = (BYTE)BValue;
	BYTE AByte = (BYTE)AValue;

	return RByte | (GByte << 8) | (BByte << 16) | (AByte << 24);
}

/********************************************************************************************

>	COLORREF CBevelFillRound::CalcPixelValue(BYTE value, double Pos, INT32 Contrast);

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/11/98
	Purpose:	Do a flat fill
	Inputs:		
	Returns:	TRUE for success
	SeeAlso:	-

********************************************************************************************/

COLORREF CBevelFillRound::CalcPixelValue(BYTE value, double Pos, INT32 Contrast)
{
	double RValue = value;
	double GValue = value;
	double BValue = value;
	double AValue = value;

	double Gradient = 0;


	if (Pos <= 0.5)
	{
		Pos = Pos / 0.5;

		Gradient = 128 - RValue;
		RValue = RValue + (Gradient * Pos);
	}	
	else
	{
		Pos = 1.0 - Pos;
		RValue = 255.0 - RValue;
		
		Pos = Pos / 0.5;

		Gradient = 128 - RValue;
		RValue = RValue + (Gradient * Pos);
	}		

	BYTE RByte = (BYTE)RValue;
	BYTE GByte = (BYTE)RValue;
	BYTE BByte = (BYTE)RValue;
	BYTE AByte = (BYTE)AValue;

	return RByte | (GByte << 8) | (BByte << 16) | (AByte << 24);
}
	
/********************************************************************************************

>	COLORREF CBevelFillSqaure::CalcPixelValue(BYTE value, double Pos, INT32 Contrast);

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/11/98
	Purpose:	Do a flat fill
	Inputs:		
	Returns:	TRUE for success
	SeeAlso:	-

********************************************************************************************/

COLORREF CBevelFillSquare::CalcPixelValue(BYTE value, double Pos, INT32 Contrast)
{
double RValue = value;
	double GValue = value;
	double BValue = value;
	double AValue = value;

	double Gradient = 0;


	if (Pos <= 0.3)
	{
		// do nothing
	}
	else if (Pos >= 0.7)
	{
		RValue = 255.0 - RValue;
	}
	else
	{
		RValue = 128.0;
	}		

	BYTE RByte = (BYTE)RValue;
	BYTE GByte = (BYTE)RValue;
	BYTE BByte = (BYTE)RValue;
	BYTE AByte = (BYTE)AValue;

	return RByte | (GByte << 8) | (BByte << 16) | (AByte << 24);
}
	
/********************************************************************************************

>	COLORREF CBevelFillFrame::CalcPixelValue(BYTE value, double Pos, INT32 Contrast);

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/11/98
	Purpose:	Do a Mesa fill
	Inputs:		
	Returns:	TRUE for success
	SeeAlso:	-

********************************************************************************************/

COLORREF CBevelFillFrame::CalcPixelValue(BYTE value, double Pos, INT32 Contrast)
{
	Pos = 1.0 - Pos;
	
	double RValue = value;
	double GValue = value;
	double BValue = value;
	double AValue = value;

	double kValue = value;

	// deal with the outside inwards
	if (value <= 128)
	{
		kValue = 128.0 - kValue;
		kValue *= (1.0 - Pos);
		kValue = 128.0 - kValue;
	}
	else
	{
		kValue -= 127.0;
		kValue *= (1.0 - Pos);
		kValue += 127.0;
	}

	RValue = kValue;
	GValue = kValue;
	BValue = kValue;
	AValue = kValue;
	
	BYTE RByte = (BYTE)RValue;
	BYTE GByte = (BYTE)GValue;
	BYTE BByte = (BYTE)BValue;
	BYTE AByte = (BYTE)AValue;

	return RByte | (GByte << 8) | (BByte << 16) | (AByte << 24);
}

/********************************************************************************************

>	COLORREF CBevelFillSmooth::CalcPixelValue(BYTE value, double Pos, INT32 Contrast);

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/11/98
	Purpose:	Do a flat fill
	Inputs:		
	Returns:	TRUE for success
	SeeAlso:	-

********************************************************************************************/

COLORREF CBevelFillSmooth::CalcPixelValue(BYTE value, double Pos, INT32 Contrast)
{
	double RValue = value;
	double GValue = value;
	double BValue = value;
	double AValue = value;

	double kValue = value;

	// deal with the outside inwards
	if (value <= 128)
	{
		kValue = 128.0 - kValue;
		kValue *= (1.0 - Pos);
		kValue = 128.0 - kValue;
	}
	else
	{
		kValue -= 127.0;
		kValue *= (1.0 - Pos);
		kValue += 127.0;
	}

	RValue = kValue;
	GValue = kValue;
	BValue = kValue;
	AValue = kValue;
	
	BYTE RByte = (BYTE)RValue;
	BYTE GByte = (BYTE)GValue;
	BYTE BByte = (BYTE)BValue;
	BYTE AByte = (BYTE)AValue;

	return RByte | (GByte << 8) | (BByte << 16) | (AByte << 24);
}

/********************************************************************************************

>	COLORREF CBevelFillPoint::CalcPixelValue(BYTE value, double Pos, INT32 Contrast);

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/11/98
	Purpose:	Do a flat fill
	Inputs:		
	Returns:	TRUE for success
	SeeAlso:	-

********************************************************************************************/

COLORREF CBevelFillPoint::CalcPixelValue(BYTE value, double Pos, INT32 Contrast)
{
	double RValue = value;
	double GValue = value;
	double BValue = value;
	double AValue = value;

	double kValue = value;

	if (Pos < 0.5)
	{
		// do nothing
	}
	else
	{
		kValue = 255.0 - kValue;
	}
	
	RValue = kValue;
	GValue = kValue;
	BValue = kValue;
	AValue = kValue;

	BYTE RByte = (BYTE)RValue;
	BYTE GByte = (BYTE)GValue;
	BYTE BByte = (BYTE)BValue;
	BYTE AByte = (BYTE)AValue;

	return RByte | (GByte << 8) | (BByte << 16) | (AByte << 24);
}

/********************************************************************************************

>	COLORREF CBevelFillRuffle::CalcPixelValue(BYTE value, double Pos, INT32 Contrast);

	Author:		David_McClarnon (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/11/98
	Purpose:	Do a ruffled fill
				This is the same as 3 rounded fills
	Inputs:		
	Returns:	TRUE for success
	SeeAlso:	-

********************************************************************************************/

COLORREF CBevelFillRuffle::CalcPixelValue(BYTE value, double Pos, INT32 Contrast)
{
	// change the position
	if (Pos >= 0 && Pos < 0.3)
	{
		Pos = Pos * (1.0/0.3);
	}
	else if (Pos >= 0.3 && Pos < 0.6)
	{
		Pos = (Pos - 0.3) * (1.0 / 0.3);
	}
	else 
	{
		Pos = (Pos - 0.6) * (1.0 / 0.4);
	}
	
	double RValue = value;
	double GValue = value;
	double BValue = value;
	double AValue = value;

	double kValue = value;

	if (Pos < 0.5)
	{
		// do nothing
	}
	else
	{
		kValue = 255.0 - kValue;
	}
	
	RValue = kValue;
	GValue = kValue;
	BValue = kValue;
	AValue = kValue;

	BYTE RByte = (BYTE)RValue;
	BYTE GByte = (BYTE)GValue;
	BYTE BByte = (BYTE)BValue;
	BYTE AByte = (BYTE)AValue;

	return RByte | (GByte << 8) | (BByte << 16) | (AByte << 24);
}
