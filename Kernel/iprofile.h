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





#ifndef  Include_IProfile
#define  Include_IProfile




typedef  double  AFp;












///-------------------------------------------------------------------------------------------------
///
///	class IProfile
///
///	Author:     Harrison Ainsworth
///	Date:		05/99
///	Purpose:	Interface / abstract class representing a functional mapping from
///				one real-valued variable to another real-valued variable.
///					MapZeroToOne() takes a zero-to-one value and maps it to another
///				zero-to-one value.
///					SetIntervals() sets intervals (or bounds) for the other mapping
///				functions. Domain is the input interval, Range is the output 
///				interval. The two param overload is a shorthand for passing the
///				same interval for domain and range.
///					MapInterval() maps values in the intervals set by calling 
///				SetIntervals().
///					MapInterval( Table ) fills in a table with mapped values in 
///				the range interval.
///	Invariants:	None - it's abstract, sir.
///
///-------------------------------------------------------------------------------------------------

class IProfile
{

public: ///-----------------------------------------------------------------------------------------

	/// standard object services -------------------------------

	//					IProfile ();					/// protected

						virtual ~IProfile ();
	//					IProfile ( const IProfile& );	/// protected
	//		IProfile&	operator= ( const IProfile& );	/// protected

	/// --------------------------------------------------------



	/// map zero-one interval
	virtual	AFp			MapZeroToOne ( AFp ZeroToOne )										const	=0;

	/// map general intervals
	virtual	void		SetIntervals ( AFp Low,   AFp High )											=0;
	virtual	void		SetIntervals ( AFp DomainLow,  AFp DomainHigh,  AFp RangeLow,  AFp RangeHigh )	=0;

	virtual	AFp			MapInterval ( AFp )													const	=0;
	virtual	void		MapInterval ( AFp TableOutput[],  INT32 length )						const	=0;

	/// compare
	virtual	bool		operator== ( const IProfile& )										const;


protected: ///--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--

	/// standard object services -------------------------------

						IProfile ();

	//					~IProfile ();
						IProfile ( const IProfile& );
			IProfile&	operator= ( const IProfile& );

	/// --------------------------------------------------------


private: ///////////////////////////////////////////////////////////////////////////////////////////

};












/// INLINES ///




/// standard object services ///////////////////////////////////////////////////////////////////////

inline
IProfile::IProfile ()
{
}




inline
IProfile::~IProfile ()
{
}




inline
IProfile::IProfile ( const IProfile& Other )
{
}




inline
IProfile&  IProfile::operator= ( const IProfile& Other )
{

	return  *this;

}


inline
bool  IProfile::operator== ( const IProfile& Other ) const
{
	return true;
}







#endif//Include_IProfile
