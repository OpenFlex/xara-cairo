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


#ifndef INC_TIMESPAN
#define INC_TIMESPAN

/********************************************************************************************

>	class TimeSpan : public CCObject

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/03/97
	Purpose:	A TimeSpan class. The class maintains a time span containing a start and
				end time. The time span is used extensively by the animation class to track
				nodes exitence.

********************************************************************************************/

typedef INT32 TimeSlice;

class TimeSpan : public CCObject
{
	CC_DECLARE_DYNAMIC(TimeSpan)

	public:
		TimeSpan();
		TimeSpan(TimeSlice lower, TimeSlice upper);
		TimeSpan(const TimeSpan& other);
		
		inline TimeSlice Lo() const;
		inline TimeSlice Hi() const;
		inline TimeSlice GetLowerBound() const;
		inline TimeSlice GetUpperBound() const;

		inline BOOL		 IsEmpty() const;
		inline double	 GetRelativeTime(TimeSlice current) const;
		inline TimeSlice GetAbsoluteTime(double current) const;

		TimeSpan Union(const TimeSpan& other) const;
		TimeSpan Intersection(const TimeSpan &other) const;
		
		BOOL SetBounds(TimeSlice lower, TimeSlice upper);
		BOOL IsSameAs(const TimeSpan& other) const;
		BOOL IsIntersectedWith(const TimeSpan& other) const;
		BOOL Contains(const TimeSpan& other) const;
		BOOL InBounds(TimeSlice current) const;
		void Inflate(TimeSlice inflate);
	
		TimeSpan  operator+(TimeSlice shift) const;
		TimeSpan  operator+(const TimeSpan& other) const;
		TimeSpan  operator-(TimeSlice shift) const;
		TimeSpan  operator-(const TimeSpan& other) const;
		TimeSpan& operator=(const TimeSpan& other);

		// don't think this really belongs here.
		// void SetCreationTimeFrame(const DocView *pView, const Document *pDoc);

	protected:
		void	 MakeInvalid();

	private:
		TimeSlice LO;
		TimeSlice HI;
};


#endif
