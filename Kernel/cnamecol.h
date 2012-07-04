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


#ifndef INC_NAMCOLREP
#define INC_NAMCOLREP

class CCObject;
class ColourFillAttribute;
class DocColour;
class TranspFillAttribute;

const INT32 MAX_TRANSP_VALUE = 255;

/********************************************************************************************

>	class CNamedColourReplacer : public CCObject

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/4/2000
	Purpose:	This is a somewhat specialised class whose purpose is to temporarily replace the
				Named colours in a ColourFillAttribute.  Its stores the colours that are replaced
				and can be called upon to put them back at a later time.
				It was designed for use with the Brush attribute, where we wish to be able to 
				replace named colours in the brush objects, and then change them back.  If you
				can think of any other uses for it then feel free.

********************************************************************************************/

class CNamedColourReplacer : public CCObject
{
	CC_DECLARE_DYNCREATE(CNamedColourReplacer)

public:
	CNamedColourReplacer();
	CNamedColourReplacer(ColourFillAttribute*, DocColour*); 
		// if you use this constructor you can skip initialisation

	~CNamedColourReplacer();

public:
	virtual BOOL Initialise(ColourFillAttribute*, DocColour*);
	
	virtual BOOL IsInitialised();

	virtual BOOL ReplaceColours(); // replaces the named colours in the attribute
	virtual BOOL RestoreColours(); // restores the replaced colours

public: // Access fns. in case you change your mind after initialisation
	ColourFillAttribute* GetColourFill();
	BOOL                 SetColourFill(ColourFillAttribute*);

	DocColour*			 GetReplacementColour();
	BOOL				 SetReplacementColour(DocColour*);

protected:  //data
	ColourFillAttribute* m_pColourFill;   
	DocColour*			 m_pReplaceColour;
	DocColour			 m_StartColour;
	DocColour			 m_EndColour1;
	DocColour			 m_EndColour2;
	DocColour			 m_EndColour3;
};

/********************************************************************************************

>	class CHSVChanger : public CNamedColourReplacer

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/4/2000
	Purpose:	Similar to its parent class but adds the following options:
				- alter HSV values in existing colours, with no replacement colour
				- replace named colours (as parent class) and make HSV changes to all
				colours whether named or not.

	Notes:      This works by taking a multiplier value and calculating a fixed value that
				will be added or subtracted from each colour value.  Values are in the range
				0 - 255, however Hue values can 'wrap - around' due to the colour wheel effect.
********************************************************************************************/

class CHSVChanger : public CNamedColourReplacer
{
	CC_DECLARE_DYNCREATE(CHSVChanger)

public:
	CHSVChanger();
	CHSVChanger(ColourFillAttribute*, DocColour*); 
		// if you use this constructor you can skip initialisation, though you will still need
		// to set the multipliers

	~CHSVChanger();

public:
	virtual BOOL ReplaceColours(); // a safe way of accessing the base class function
	virtual BOOL RestoreColours(); // restores the replaced colours
		
			BOOL ChangeHSVValues(); // does the HSV changing	
			BOOL ShouldChangeHSV();  // indicates whether or not colours need changing

			virtual BOOL IsInitialised();

public:	
	void   ChangeColour(DocColour* pCol);  // changes the values of just this colour

public: // access fns.
	double GetHueMultiplier();
	BOOL   SetHueMultiplier(double Value);

	double GetSaturationMultiplier();
	BOOL   SetSaturationMultiplier(double Value);

protected:  // helper fns.
	void	ApplyIncrements(DocColour* pCol);

protected: //data
	double m_HueMultiplier;
	double m_SaturationMultiplier;
	double m_ValueMultiplier;

	INT32   m_HueIncrement;   // these can only be set internally
	INT32   m_SatIncrement;

protected: // storing the original values, this is a bit grim but given that we sometimes 
		   // have to clip values that go over 255 we cannot rely on the mults and incrs to undo the change
	DocColour m_OrigStartCol;
	DocColour m_OrigEndCol1;
	DocColour m_OrigEndCol2;
	DocColour m_OrigEndCol3;

};

/********************************************************************************************

>	class CTransparencyReplacer : public CObject

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/6/2000
	Purpose:	Similar to CNamedColourReplacer, this class takes a transparency attribute, changes
				its values, and then changes them back.

********************************************************************************************/

class CTransparencyReplacer : public CCObject
{
	CC_DECLARE_DYNAMIC(CTransparencyReplacer)

public:
	CTransparencyReplacer();
	~CTransparencyReplacer() {};

public: // access
	BOOL SetReplacementValue(INT32 Value);
	INT32 GetReplacementValue();

	BOOL SetAdjustmentValue(double Value);
	double GetAdjustmentValue();
	BOOL SetInvertedAdjuster(double Value);
	double GetInvertedAdjuster();

	void SetTransparencyAttr(TranspFillAttribute* pAttr);
	BOOL ReplaceTransparency();
	BOOL RestoreTransparency();

	BOOL IsInitialised();
protected: // data
	UINT32 m_OriginalTransp;  // store the original value so we can replace it
	INT32 m_ReplaceTransp;   // the replacement value, can be negative, indicating do nothing

	double m_TranspAdjust;  // adjusts the final value
	double m_InvertAdjust; // we now take a second adjuster which gets inverted

	TranspFillAttribute* m_pTranspFill; // the transparency we're working on 


};


#endif
