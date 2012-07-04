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





#ifndef  Include_CProfileBiasGain
#define  Include_CProfileBiasGain




#include "iprofile.h"












///-------------------------------------------------------------------------------------------------
///
///	class CProfileBiasGain
///
///	Author:     Harrison Ainsworth
///	Date:		05/99
///	Purpose:	Implementation of the IProfile interface as Perlin Bias and Gain: Bias resembling a 
///				gamma function, Gain resembling a sigma function, each being positive or negative. 
///				Together they provide a variety of simple and useful shapes.
///				references:
///				 Hypertexture - Perlin, Hoffert - Siggraph conference proceedings 1989
///				 Fast Alternatives to Perlin's Bias and Gain Functions - Schlick - Graphics Gems IV (AP 94)
///	Implemen-	There are two sub-interfaces: construction/setting and IProfile/mapping:
///	tation:			'Setting' comprises the standard object services, and the choice of the Bias and 
///				Gain parameters.
///					'Mapping' comprises the methods set out in IProfile: for using the object to map 
///				values.
///	Invariants:	0 < Bias_m < 1,                     0 < Gain_m < 1                     (0,1)
///				-1 <= BiasMinus1ToPlus1_m <= +1,    -1 <= GainMinus1ToPlus1_m <= +1    [-1,+1]
///				DomainLength_m != 0,  RangeLength_m != 0
///
///-------------------------------------------------------------------------------------------------

class CProfileBiasGain  :  public IProfile
{

public: ///-----------------------------------------------------------------------------------------

	/// standard object services -------------------------------

								CProfileBiasGain ();
								CProfileBiasGain ( AFp BiasMinus1ToPlus1,  AFp GainMinus1ToPlus1 );

								~CProfileBiasGain ();
								CProfileBiasGain ( const CProfileBiasGain& );
			CProfileBiasGain&	operator= ( const CProfileBiasGain& );

	/// --------------------------------------------------------



	/// set/get mapping
	///		Each parameter must be in the interval -1 to +1  [-1,+1]
	///		Bias:  -1 'thickest',  0 'flat',  +1 'thinnest'
	///		Gain:  -1 'sharpest',  0 'flat',  +1 'softest'
	virtual	void		SetBiasGain ( AFp BiasMinus1ToPlus1,  AFp GainMinus1ToPlus1 );
	virtual	void		SetBias ( AFp BiasMinus1ToPlus1 );
	virtual	void		SetGain ( AFp GainMinus1ToPlus1 );

	virtual	AFp			GetBias ()															const;
	virtual	AFp			GetGain ()															const;


	/// IProfile -----------------------------------------------
	/// map zero-one interval
	virtual	AFp			MapZeroToOne ( AFp ZeroToOne )										const;

	/// map general intervals
	virtual	void		SetIntervals ( AFp Low,  AFp High );
	virtual	void		SetIntervals ( AFp DomainLow,  AFp DomainHigh,  AFp RangeLow,  AFp RangeHigh );

	virtual	AFp			MapInterval ( AFp )													const;
	virtual	void		MapInterval ( AFp Table[],  INT32 length )							const;

	/// compare
	virtual	bool		operator== ( const CProfileBiasGain& )								const;

	void SetGeneratesInfiniteUndo (BOOL newVal) { generatesInfiniteUndo = newVal; }
	BOOL GetGeneratesInfiniteUndo () const { return (generatesInfiniteUndo); }

	void SetIsAFeatherProfile (BOOL newVal) { isAFeatherProfile = newVal; }
	BOOL GetIsAFeatherProfile () { return (isAFeatherProfile); }


protected: ///--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--

	/// conversion between intervals
	static	AFp			ConvertIntervalMinus1Plus1ToZeroOne ( AFp );
	        AFp			ScaleDomainToZeroOne ( AFp )										const;
	        AFp			ScaleZeroOneToRange  ( AFp )										const;

	/// the actual function-shape procedural definitions
	static	AFp			BiasGain ( AFp BiasAmount,  AFp GainAmount,  AFp Input );
	inline static	AFp			Bias ( AFp BiasAmount,  AFp Input );
	inline static	AFp			Gain ( AFp GainAmount,  AFp Input );	


private: ///////////////////////////////////////////////////////////////////////////////////////////

	/// functions ----------------------------------------------
	/// construction assistance
			void		SetDefaultIntervals ();


	/// members ------------------------------------------------
	/// parameters of the mapping
			AFp			BiasMinus1ToPlus1_m;
			AFp			GainMinus1ToPlus1_m;
			AFp			Bias_m;
			AFp			Gain_m;

	/// bounds of the mapping
			AFp			DomainLow_m;
			AFp			DomainLength_m;
			AFp			RangeLow_m;
			AFp			RangeLength_m;

	/// constants
	static const AFp	kSmallAmount_s;

	/// CGS:  when we compound a blend and change the the blends profile, we need to know whether the blend
	/// allows its parent compound to regenerate.  This is controlled by the following variable, which is
	/// guaranteed to be set CBiasGainGadget::Message () returns (for dropdown) and HandleInput () is called
	/// (for sliders).  This is the only sensible place to store the data - since it needs to be accessible
	/// (potentially) within all tool infobars
	
	BOOL generatesInfiniteUndo;			// DO NOT SET THIS VALUE YOURSELF !!!!

	BOOL isAFeatherProfile;				// CGS:  we need to do some special processing for profiles that are
										// used with feathering.
};








#endif//Include_CProfileBiasGain
