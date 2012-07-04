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

//

#ifndef INC_SCUNITS
#define INC_SCUNITS

// Definition of the scale units class

//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]

/*********************************************************************************************

>	class Qualfier : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/05/96
	Purpose:	A ScaleUnit is defined by:
				A range for which the scaled value is between 0 & 1
				A scaler which converts any value in its range to between 0 & 1
				A qualifier which may be prefixed or suffixed onto the value
				NB: There are no base units as such.

**********************************************************************************************/ 
class Qualifier : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(Qualifier);

public:
	enum QUALIFIER_SHOWN
	{
		IS_NOTSHOWN = 0,
		IS_SHOWN = 1
	};

	enum QUALIFIER_AFFIX			// should be subclassed
	{
		SUFFIX = 0,
		PREFIX = 1,
		NONE = -1
	};

	Qualifier();
	virtual ~Qualifier() { }

	Qualifier& operator=(const Qualifier& OtherQualifier);

// Attribute access
	BOOL			SetAttributes(const String_32& NewToken, QUALIFIER_SHOWN WhetherShown);
	String_32		GetToken() const;
	BOOL			IsShown() const;

	virtual	BOOL	MakeDisplayString(const StringBase& InString, StringBase* pOutString) const = 0;

	virtual			QUALIFIER_AFFIX	GetAffix() const = 0;	// DO NOT USE

protected:
	String_32		m_Token;
	// m_Affix is the affix type of the qualifier, eg.SU_PREFIX for $10 or SU_SUFFIX for 10p
	BOOL			m_bShow;			// whether qualifier shown 

};


/*********************************************************************************************

>	class PrefixQualifier : public Qualifier

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/05/96
	Purpose:	A prefix qualifier is one of the form <QualifierToken><...>, e.g. 5.00

**********************************************************************************************/ 
class PrefixQualifier : public Qualifier
{
	CC_DECLARE_MEMDUMP(PrefixQualifier);

public:
	virtual BOOL MakeDisplayString(const StringBase& InString, StringBase* pOutString) const;

	QUALIFIER_AFFIX	GetAffix() const	{	return PREFIX;	}

};


/*********************************************************************************************

>	class SuffixQualifier : public Qualifier

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/05/96
	Purpose:	A suffix qualifier is one of the form <...><QualifierToken>, e.g. 5.00%

**********************************************************************************************/ 
class SuffixQualifier : public Qualifier
{
	CC_DECLARE_MEMDUMP(SuffixQualifier);

public:
	virtual BOOL MakeDisplayString(const StringBase& InString, StringBase* pOutString) const;

	QUALIFIER_AFFIX	GetAffix() const	{	return SUFFIX;	}

};


/*********************************************************************************************

>	class SuffixQualifier : public Qualifier

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/05/96
	Purpose:	A suffix qualifier is one of the form <...><QualifierToken>, e.g. 5.00%

**********************************************************************************************/ 
class NullQualifier : public Qualifier
{
	CC_DECLARE_MEMDUMP(NullQualifier);

public:
	virtual BOOL MakeDisplayString(const StringBase& InString, StringBase* pOutString) const;

	QUALIFIER_AFFIX	GetAffix() const	{	return NONE;	}

};


/*********************************************************************************************

>	class ScaleUnit : public ListItem

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/05/96
	Purpose:	A ScaleUnit is defined by:
				A range for which the scaled value is between 0 & 1
				A scaler which converts any value in its range to between 0 & 1
				A qualifier which may be prefixed or suffixed onto the value
				NB: There are no base units as such.

**********************************************************************************************/ 
class ScaleUnit : public ListItem
{
	CC_DECLARE_DYNAMIC(ScaleUnit)

public:
// Constructors
	ScaleUnit();
	ScaleUnit(const double dScale, const double dMin, const double dMax);
	ScaleUnit(const double dScale, const UINT32 nDPtoShow);
	ScaleUnit(const ScaleUnit& UnitToCopy);
	
	virtual ScaleUnit& operator =(const ScaleUnit& UnitToCopy);

	virtual ~ScaleUnit();

	// Two ScaleUnits are equal if they have matching qualifiers & scales(?)
	virtual BOOL operator == (const ScaleUnit& RhsUnit) const;
	virtual BOOL operator != (const ScaleUnit& RhsUnit) const;

// Attributes	

	BOOL		SetQualifier(Qualifier& NewQualifier);
	BOOL		SetQualifier(	const StringBase& QualifierParseString, 
								const Qualifier::QUALIFIER_SHOWN WhetherShown);
	const Qualifier*	GetQualifier() const;

	BOOL		SetDPtoShow(const UINT32 uNumber);
	UINT32		GetDPtoShow() const;

	BOOL		SetMin(const double dMin);
	double		GetMin() const;
	BOOL		SetMax(const double dMax);
	double		GetMax() const;

	BOOL		SetScale(const double dScale);
	double		GetScale() const;

	BOOL		SetRange(const double dMin, const double dMax);
// Operations
	BOOL 		ConvertTo0to1(double& dValue) const;
	BOOL 		ConvertFrom0to1(double& dValue) const;

	BOOL		StringFromScale(double& dNumber, StringBase* pResult, const UINT32 uSigFigs) const;
protected:

	// By dividing by m_dScale we produce a number between 0 & 1

	double			m_dScale;

	// m_pQualifier is the Qualifier used to identify unit

	Qualifier*		m_pQualifier;

	// The number of decimal places to show

	UINT32			m_nDPtoShow;

	// The range for which our unit returns 0 - 1

	double			m_dMin;
	double			m_dMax;

private:
	// Whether or not ScaleUnit created a new Qualifier
	BOOL			m_bInternalQualifier;
};





/*********************************************************************************************

>	class UnitGroup : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/05/96
	Purpose:	A UnitGroup is a set of ScaleUnits that are interconvertible
	Notes:		It is possible to violate the integrity of the UnitGroup by changing
				ScaleUnits included in the group. Kindly use the UpdateUnit method provided.

**********************************************************************************************/ 
class UnitGroup : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(UnitGroup);
public:

// Constructor & Destructor
	UnitGroup();
	UnitGroup(const UnitGroup& GroupToCopy);
	BOOL	IsValid()	{return m_bConstructedOK;}

	virtual ~UnitGroup();

	virtual UnitGroup&	operator=(const UnitGroup& GroupToCopy);

	virtual BOOL		operator==(const UnitGroup& RhsGroup) const;
	virtual BOOL		operator!=(const UnitGroup& RhsGroup) const;

// Group Member manipulation
	BOOL		AddUnit(ScaleUnit* pUnit);
	BOOL		AddUnit(ScaleUnit& NewUnit);
	ScaleUnit*	UpdateUnit(const UINT32 uIndex, ScaleUnit& NewUnit);
	BOOL		DeleteUnit(ScaleUnit& UnitToDelete);

// Operations for finding units & references given bits of info
	ScaleUnit*	FindUnitFromQualifier(const String_32& qualifier) const;
	ScaleUnit*	FindUnitFromIndex(const UINT32 uIndex) const;
	INT32			FindIndexFromUnit(const ScaleUnit& thisUnit) const;
// Attributes
	UINT32		GetUnitCount() const;
	BOOL		SetDefaultUnit(ScaleUnit* pUnit);
	ScaleUnit*	GetDefaultUnit() const;
// Conversion
	BOOL		ScaleFromString(const StringBase& string, double& dNumber) const;

protected:
	List		m_UnitList;
	List		m_UnitRefList;
	ScaleUnit*	m_pDefaultUnit;

// Overridables
	virtual void OnUnitChanged(const ScaleUnit& UpdatedUnit);
	virtual BOOL AllowDeletion(const ScaleUnit& UnitToDelete);
	virtual void OnDeleteCompletion(const ScaleUnit& DeletedUnit);

private:
	BOOL	m_bConstructedOK;
};



/*********************************************************************************************

>	class StandardUnit

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	02/05/96
	Purpose:	A class utility defining standard units for use as you please, although
				corrupting them may cause some annoyance.
	Notes:		Contains only static members.
	See Also:	class UnitGroup, class ScaleUnit

**********************************************************************************************/ 
class StandardUnit : public CC_CLASS_MEMDUMP
{
	CC_DECLARE_MEMDUMP(StandardUnit);

public:
	static BOOL Init();
	static BOOL DeInit();

	static NullQualifier TheNullQualifier;	// the Qualifier with no token
	// Declare some standard units & groups
	static ScaleUnit UnitPercent;		// 0..100
	static ScaleUnit UnitDecimalD;		// 0..255 with big D as qualifier
	static ScaleUnit UnitDecimald;		// 0..255 with little d as qualifier
	static ScaleUnit UnitDegree;		// 0..360

	static UnitGroup PercentGroup;		// UnitDecimald(D) & UnitPercent
	static UnitGroup AngleGroup;		// UnitDegree
};


//-----------------------------------------------------------------------------------------
#endif	// INC_SCUNITS

