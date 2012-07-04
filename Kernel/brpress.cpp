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


// brush pressure classes implementation

#include "camtypes.h"
#include "brpress.h"
//#include "cxfrec.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "pen.h"
#include "ndbldpth.h"

CC_IMPLEMENT_MEMDUMP(PressureItem, CCObject);

/********************************************************************************************

>	PressureItem::PressureItem(UINT32 Pressure, double Proportion, MILLIPOINT Distance)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/97
	Inputs:		Pressure - the pressure value
				Proportion - the proportional distance along the path
				Distance - the absolute distance along the path
	Purpose:	constructor with initialisation
				
	Notes:		
********************************************************************************************/

PressureItem::PressureItem(UINT32 Pressure, double Proportion, MILLIPOINT Distance)
{
	m_Pressure = Pressure;
	m_Proportion = Proportion;
	m_Distance = Distance;
}

/********************************************************************************************

>	PressureItem::PressureItem(PressureItem& Other)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/97
	Inputs:		Other
	Purpose:	copy constructor
				
	Notes:		
********************************************************************************************/

PressureItem::PressureItem(const PressureItem& Other)
{
	m_Pressure = Other.m_Pressure;
	m_Proportion = Other.m_Proportion;
	m_Distance = Other.m_Distance;
}


/********************************************************************************************

>	PressureItem::PressureItem(PressureItem& Other)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/1/97
	Inputs:		Other
	Purpose:	copy constructor
				
	Notes:		
********************************************************************************************/

PressureItem PressureItem::operator =(const PressureItem& Other)
{
	m_Pressure = Other.m_Pressure;
	m_Proportion = Other.m_Proportion;
	m_Distance = Other.m_Distance;

	return *this;
}


/********************************************************************************************

>	PressureItem::WorkOutProportion(MILLIPOINT PathLength)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99

	Inputs:		length of the path that this object is on
	Purpose:	calculates how far along the path we are and sets the member variable

********************************************************************************************/

void PressureItem::WorkOutProportion(MILLIPOINT PathLength)
{
	if (m_Distance < 0 || m_Distance > PathLength)
	{
		ERROR3("Attempting to calculate proportional distance with invalid data");
		TRACEUSER( "Diccon", _T("Invalid distance: %d, Path Length: %d\n"), m_Distance, PathLength );
		m_Proportion = 1.0;
		return;
	}
	m_Proportion = (double)((double)m_Distance / (double)PathLength);
	//if (m_Proportion < 0)
//	TRACEUSER( "Diccon", _T("Proportion: %f\n"), m_Proportion);

}

		
/********************************************************************************************


>	BOOL PressureItem::WriteNative(BaseCamelotFilter *pFilter)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99
	Inputs:		pFilter - filter to write to
	Returns:	TRUE if the Node has written out a record to the filter
	Purpose:	Writes out a record of this PressureItem to the record supplied.  Note that because
				PressureItems are generally part of a larger object they do not have their own tag etc.
				This function is merely a convenience function.

	SeeAlso:	AttrBrushType::WritePreChildrenNative; BrushAttrRecordHandler::HandleRecord

********************************************************************************************/

BOOL PressureItem::WriteNative(CXaraFileRecord* pRecord)
{
	ERROR2IF(pRecord == NULL, FALSE, "Record is NULL in PressureItem::WriteNative");
	
	BOOL ok = pRecord->WriteINT32((INT32)m_Pressure);
	if (ok) ok = pRecord->WriteDOUBLE(m_Proportion);
	if (ok) ok = pRecord->WriteINT32(m_Distance);

	return ok;
}





/********************************************************************************************

>	BrushPointInfo::BrushPointInfo()

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99

	Inputs:		-
	Purpose:	Default Constuctor for BrushPointInfo

********************************************************************************************/

BrushPointInfo::BrushPointInfo()
{
	m_Pressure = MAXPRESSURE / 2;
	m_Tangent = 0.0;
	m_Point = DocCoord(0, 0);
}


/********************************************************************************************

>	BrushPointInfo::BrushPointInfo(DocCoord Point, double Tangent, UINT32 Pressure)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99

	Inputs:		-
	Purpose:	initialising Constuctor for BrushPointInfo

********************************************************************************************/

BrushPointInfo::BrushPointInfo(DocCoord Point, double Tangent, UINT32 Pressure)
{
	m_Point = Point;
	m_Tangent = Tangent;
	m_Pressure = Pressure;
}


/********************************************************************************************

>	BrushPointInfo BrushPointInfo::operator=(BrushPointInfo &Other)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99

	Inputs:		-
	Purpose:	initialising Constuctor for BrushPointInfo

********************************************************************************************/

BrushPointInfo& BrushPointInfo::operator =(BrushPointInfo &Other)
{
	m_Point = Other.m_Point;
	m_Tangent = Other.m_Tangent;
	m_Pressure = Other.m_Pressure;

	return *(this);
}


/********************************************************************************************

>	TimeStampBrushPoint::TimeStampBrushPoint()

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99

	Inputs:		-
	Purpose:	Default Constuctor for TimeStampBrushPoint

********************************************************************************************/

TimeStampBrushPoint::TimeStampBrushPoint() : BrushPointInfo()
{
	m_Distance = -1;
	m_Proportion = -1;
}


/********************************************************************************************

>	TimeStampBrushPoint::TimeStampBrushPoint(CPathPointInfo)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99

	Inputs:		-
	Purpose:	Constuctor for TimeStampBrushPoint

********************************************************************************************/

TimeStampBrushPoint::TimeStampBrushPoint(CPathPointInfo PathInfo)
{
	m_Point = PathInfo.m_Point;
	m_Tangent = PathInfo.m_Tangent;
	m_Distance = -1;
	m_Proportion = -1;
}

/********************************************************************************************

>	TimeStampBrushPoint::TimeStampBrushPoint(CPathPointInfo)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99

	Inputs:		-
	Purpose:	Constuctor for TimeStampBrushPoint

********************************************************************************************/

TimeStampBrushPoint::TimeStampBrushPoint(CPathPointInfo PathInfo, MILLIPOINT Distance)
{
	m_Point = PathInfo.m_Point;
	m_Tangent = PathInfo.m_Tangent;
	m_Distance = Distance;
	m_Proportion = -1;
}


/********************************************************************************************

>	TimeStampBrushPoint::TimeStampBrushPoint(DocCoord Point, double Tangent, MILLIPOINT Distance)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99

	Inputs:		-
	Purpose:	Constuctor for TimeStampBrushPoint

********************************************************************************************/

TimeStampBrushPoint::TimeStampBrushPoint(DocCoord Point, double Tangent, MILLIPOINT Distance)
{
	m_Point = Point;
	m_Tangent = Tangent;
	m_Distance = Distance;
}

/********************************************************************************************

>	TimeStampBrushPoint TimeStampBrushPoint::operator=(TimeStampBrushPoint Other)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99

	Inputs:		Other - the TSBP to assign
	Purpose:	assignment operator
********************************************************************************************/

TimeStampBrushPoint TimeStampBrushPoint::operator=(TimeStampBrushPoint Other)
{
	m_Point = Other.m_Point;
	m_Tangent = Other.m_Tangent;
	m_Distance = Other.m_Distance;
	m_Proportion = Other.m_Proportion;

	return *this;
}

/********************************************************************************************

>	TimeStampBrushPoint::WorkOutProportion(MILLIPOINT PathLength)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99

	Inputs:		length of the path that this object is on
	Purpose:	calculates how far along the path we are and sets the member variable

********************************************************************************************/

void TimeStampBrushPoint::WorkOutProportion(MILLIPOINT PathLength)
{
	if (m_Distance < 0 || m_Distance > PathLength)
	{
	//	ERROR3("Attempting to calculate proportional distance with invalid data");
		TRACEUSER( "Diccon", _T("Invalid distance: %d, Path Length: %d\n"), m_Distance, PathLength );
		m_Proportion = 1.0;
		return;
	}
	m_Proportion = (double)((double)m_Distance / (double)PathLength);
	//if (m_Proportion < 0)
//	TRACEUSER( "Diccon", _T("Proportion: %f\n"), m_Proportion);

}


/********************************************************************************************

>	static INT32 TimeStampBrushPoint::ComparePointInfo(void* Point1, void* Point2)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	6/10/99
	Inputs:     Point1, Point2- the distances to be compared
	Returns:	-1, if Dist1 < Dist2
				0 , if Dist1 == Dist2
				1, if Dist1 > Dist2
	Purpose:	Compares the two points by their distances, note that they are specified as void*
				so that I can supply this fn.to qsort
	SeeAlso:	-

********************************************************************************************/

INT32 TimeStampBrushPoint::ComparePointInfo(const void* Point1, const void* Point2)
{
	TimeStampBrushPoint* pPoint1 = (TimeStampBrushPoint*)Point1;
	TimeStampBrushPoint* pPoint2 = (TimeStampBrushPoint*)Point2;
	
	if (pPoint1->m_Distance < pPoint2->m_Distance)
		return -1;
	if (pPoint1->m_Distance > pPoint2->m_Distance)
		return 1;

	return 0;
}

		
/********************************************************************************************


>	BOOL TimeStampBrushPoint::WriteNative(BaseCamelotFilter *pFilter)

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/99
	Inputs:		pFilter - filter to write to
	Returns:	TRUE if the Node has written out a record to the filter
	Purpose:	Writes out a record of this TSBP to the record supplied.  Note that because
				TSBPs are generally part of a larger object they do not have their own tag etc.
				This function is merely a convenience function.

	SeeAlso:	AttrBrushType::WritePreChildrenNative; BrushAttrRecordHandler::HandleRecord

********************************************************************************************/

BOOL TimeStampBrushPoint::WriteNative(CXaraFileRecord* pRecord)
{
	ERROR2IF(pRecord == NULL, FALSE, "Record is NULL in TimeStampBrushPoint::WriteNative");
	
	BOOL ok    = pRecord->WriteCoord(m_Point);
	TRACEUSER( "Diccon", _T("Wrote Point %d, %d\n"), m_Point.x, m_Point.y );
	if (ok) ok = pRecord->WriteDOUBLE(m_Tangent);
	if (ok) ok = pRecord->WriteDOUBLE(m_Proportion);
	if (ok) ok = pRecord->WriteINT32(m_Distance);

	return ok;
}

