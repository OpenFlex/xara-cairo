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


#if !defined(AFX_AI_GRAD_H__CFD00AD1_0547_11D4_836F_006008484641__INCLUDED_)
#define AFX_AI_GRAD_H__CFD00AD1_0547_11D4_836F_006008484641__INCLUDED_

class AI5EPSFilter;
class ColourRamp;


/********************************************************************************************

>	class AIHighlight

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/03/00
	Purpose:	Helps with the import of Adobe Illustrator 8.0 files.
				Holds the definition of a highlight to be used in subsequent fills.
				(not interpreted at present)

********************************************************************************************/
class AIHighlight
{
public:
	AIHighlight( const INT32 nAngle, const double& dLength, const DocCoord& hilight ) :
		mnAngle(nAngle), mdLength(dLength), mHilight(hilight)
	{}

	INT32		mnAngle;
	double		mdLength;
	DocCoord	mHilight;
};


/********************************************************************************************

>	class AI5Gradient : public ListItem

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/08/94
	Purpose:	Used to hold the definition of an Illustrator 5 gradient fill, while we
				are importing an AI5 file.
	SeeAlso:	AI5EPSFilter

********************************************************************************************/

class AI5Gradient : public ListItem
{
public:
	String_64 		Name;
	BOOL			IsRadial;
	DocColour		StartColour;
	DocColour		EndColour;
	ColourRamp*		mpCurrentRamp;
	AIHighlight*	mpHighlight;
	INT32			midPoint;

public:
	AI5Gradient();
	virtual ~AI5Gradient();
};


/********************************************************************************************

>	class AIGradientProcessor  

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/03/00
	Purpose:	Helps with the import of Adobe Illustrator 8.0 files.
				(at the time of writing only the version 7.0 documentation was available
				so some omissions are inevitable).
				It creates a list gradient fills and allows the filter to extract them.

********************************************************************************************/
class AIGradientProcessor  
{
public:
	AIGradientProcessor();
	virtual ~AIGradientProcessor();

	BOOL BeginGradient();
	BOOL DecodeBd( AI5EPSFilter& filter );
	BOOL DecodeBS( AI5EPSFilter& filter );
	BOOL DecodeBh( AI5EPSFilter& filter );
	BOOL EndGradient( AI5EPSFilter& filter );

	AI5Gradient* FindGradient( const StringBase& name );
private:

	BOOL Approx (const double & d1, const double & d2);

	// The list of imported grad fills
	List			mGradFills;

	// Used to indicsate if we found any gradient fills too complex to handle properly.
	BOOL			mbGradFillTooComplex;

	// The grad fill we are currently reading in (if any)
	AI5Gradient*	mpCurrentFill;

	// (ChrisG 3/4/2001) The midpoint for the fill (used to set the bias). Since Xara X
	//	profiling is for the entire fill, not individual points, this will; just be the
	//	first valid value read in.
	INT32			mMidPoint;
	INT32			mLastRampPoint;
};

#endif // !defined(AFX_AI_GRAD_H__CFD00AD1_0547_11D4_836F_006008484641__INCLUDED_)
