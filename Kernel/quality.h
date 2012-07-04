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


#ifndef INC_QUALITY
#define	INC_QUALITY

/********************************************************************************************

>	class Quality

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/94
	Purpose:	Encapsulates the 'quality' of rendering, which in ArtWorks-speak was the
				WYSIWYG value. It is really a numeric value, but this fact should be hidden from
				everyone who should ask specific things of it, not use its value.

********************************************************************************************/

class Quality
{

#define	QUALITY_GUIDELAYER	(-1)
#define	QUALITY_MAX			110

#ifdef RALPH
#define	QUALITY_DEFAULT		QUALITY_MAX
#else
// Normal, default Camelot quality
#define	QUALITY_DEFAULT		100
#endif

	// these are the only people allowed to get to the real numeric value
	friend class OpQuality;
//	friend class QualityAttribute;
//	friend class AttrQuality;
	friend class QualitySliderDescriptor;

public:
	enum QualityEnums
	{
		QualityGuideLayer = QUALITY_GUIDELAYER,
		QualityMax=QUALITY_MAX,
		QualityDefault=QUALITY_DEFAULT
	};

	Quality(QualityEnums quality=QualityDefault) { QualityValue=quality; }
	~Quality()	{ }

	Quality& operator = (const Quality& Other)							// so they can be assigned
	{
		QualityValue = Other.QualityValue;
		return *this;
	}

	INT32 operator==(const Quality& Other)
	{
		return QualityValue == Other.QualityValue;
	}

	INT32 operator!=(const Quality& Other)
	{
		return QualityValue != Other.QualityValue;
	}

	// each 'quality' attribute has an enum determining how it is rendered
	enum Line
	{
		NoLine,
		BlackLine,
		ThinLine,
		FullLine
	};

	enum Fill
	{
		NoFill,
		Bitmaps,
		Solid,
		Graduated
	};

	enum Blend
	{
		NoBlend,
		StartAndEnd,
		FullBlend
	};

	enum Antialias
	{
		NoAntialias,
		FullAntialias
	};

	enum Transparency
	{
		NoTransparency,
		FullTransparency
	};

	Line			GetLineQuality() const;
	Fill			GetFillQuality() const;
	Blend			GetBlendQuality() const;
	Antialias		GetAntialiasQuality() const;
	Transparency	GetTransparencyQuality() const;

	void SetDefault();

	// These should not generally be used by people, except in very special situations
	BOOL SetQuality(INT32);
	INT32 GetQuality() const;

private:

	INT32 QualityValue;

public:
	// The default quality level to give to new views.
	static Quality DefaultQuality;
};

/********************************************************************************************

>	Quality::Quality()

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Constructor for Quality class. Puts the default value in. Inline fn.
	Errors:		-

********************************************************************************************/

/********************************************************************************************

>	Quality::~Quality()

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/4/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Destructor for Quality class. Does nothing. Inline.
	Errors:		-

********************************************************************************************/

#endif
