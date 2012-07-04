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

#ifndef  Include_CShadowerFlat
#define  Include_CShadowerFlat

struct IComShadowerFlat;   // defined in the .cpp file

typedef	float			AFloatPt01;
typedef	INT32			APixels;
typedef	INT32*			ACoordPixels;    // array of 2 elements please
typedef	INT32			ADegrees;
typedef	UINT32*	AAlphaChannel;   // AlphaRGB or AlphaBGR array (alpha in the high byte)

/*******************************************************************************

>	class CShadowerFlat

	Updated by: Mark Howitt 3/8/98

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/12/97
	Purpose:	'Wrapper' for the COM interface CShadowerFlat, which is itself
	            a 'Facade' for the flat shadow generation system.
	            Simply delegates to its owned COM component.
	See also:	CShadowerFlat ( in CShadowerFlat.cpp )
	Errors:		(constructor throws if ::CoCreateInstance() fails) not currently.

	Instructions:	Construction:
						Construct, then call _init_ (if possible, rewrite this wrapper
						class, moving the _Init_() into the costructor).
					Setting/getting choices:
						Pass null pointers for the parameters you don't want to change/read.
						The baseline value means:
							position of baseline / height of image
						where:
							position of baseline  =  no. of pixels from top of image
					Switches:
						You might want to change the default init settings in _Init_(),
						The internal defaults are FALSE, FALSE - alpha channel, right way up
						(top left pixel is lowest address)
					Make shadow functions:
						Positions have their origin at the top left of the image.
						Call CalcShadowBound() to get the size and pos of the shadow,
						then allocate your shadow pixmap, then call DrawShadow() to draw the
						shadow.
						The shadow has zeros in the color channels.
					InverseShadowBoundCalc()
						Purpose:	To calculate/estimate the bound of an unshadowed pixmap,
									given the bound of a (hypothetical) shadowed pixmap,
									- the inverse of CalcShadowBound().
						Inputs:		The width, height of a hypothetical pixmap with shadow
									already applied.
						Outputs:	The width, height and position of the unshadowed pixmap,
									that would, after having it's shadow added, take up the
									above input bound.
					CalcShadowBound()
						Purpose:	Calculate the rectangular bound of the shadow that
									would be produced by DrawShadow() given a particular
									transparency/alpha map.
									Call this, use the results to allocate a shadow map,
									then call DrawShadow().
						Inputs:		A transparency/alpha map, it's width, height and position
						Outputs:	The width, height and position of the shadow
					DrawShadow()
						Purpose:	Draw the shadow cast by a particular transparency/alpha map
						Inputs:		A shadow map, it's width, height and position,
									A transparency/alpha map, it's width, height and position
						Outputs:	The shadow drawn onto the shadow map

*******************************************************************************/

class CShadowerFlat
{
public:
	// Standard object management
	CShadowerFlat();
	virtual	~CShadowerFlat();

	// (Should be in constructor)
	virtual	HRESULT _Init_();

	// Set choices
	virtual	VOID SetChoicesToDefault();
	virtual	VOID SetChoices( const BOOL* MakeWallShadow, const AFloatPt01* Darkness01,
							 const APixels* Blurriness, const ACoordPixels  XYPosition,
							 const ADegrees* Tilt, const AFloatPt01* YScale01 );

	virtual	VOID SetBaseline( const AFloatPt01* Baseline );

	// Get choices
	virtual	VOID GetChoices( BOOL* MakeWallShadow, AFloatPt01* Darkness01, APixels* Blurriness,
							 ACoordPixels  XYPosition, ADegrees* Tilt, AFloatPt01* YScale01 ) const;

	virtual	VOID GetBaseline( AFloatPt01* Baseline ) const;

	// Choices range queries
	virtual	VOID GetDarknessRange( AFloatPt01& Min, AFloatPt01& Max ) const;
	virtual	VOID GetBlurrinessRange( APixels& Min, APixels& Max ) const;
	virtual	VOID GetPositionRange( ACoordPixels Min, ACoordPixels Max ) const;

	virtual	VOID GetProjectionRange( ADegrees& MinTilt, ADegrees& MaxTilt,
									 AFloatPt01& MinYScale, AFloatPt01& MaxYScale ) const;
	// Alpha channel type switches
	virtual	HRESULT	SwitchToTransparencyInsteadOfAlpha( BOOL YesOrNo );
	virtual	HRESULT	SwitchToUpsideDownPixelAddressing( BOOL YesOrNo );

	// Make shadow
	virtual	HRESULT	InverseShadowBoundCalc( ACoordPixels UnshadowedWidHei, ACoordPixels UnshadowedPos,
											const ACoordPixels& ShadowedWidHei, const AFloatPt01* Baseline ) const;
	
	virtual	HRESULT	CalcShadowBound( ACoordPixels ShadowWidHei, ACoordPixels ShadowPos, const AAlphaChannel& TransparencyMap,
									 const ACoordPixels& tWidHei, const ACoordPixels& tPos ) const;
	
	virtual	HRESULT	DrawShadow( const AAlphaChannel& ShadowMapOut, const ACoordPixels& sWidHei,
								const ACoordPixels& sPos, const AAlphaChannel& TransparencyMapIn,
								const ACoordPixels& tWidHei, const ACoordPixels& tPos ) const;

protected:

private:
	// ptr to the actual COM component object
	IComShadowerFlat* pShadower_m;

	// COM componenent identifiers
	static const GUID IID_IComShadowerFlat;
	static const GUID CLSID_CComShadowerFlat;

	// prohibit copying
	CShadowerFlat( const CShadowerFlat& );
	CShadowerFlat& operator= ( const CShadowerFlat& );
};

/**************************************************************************************

>	class CCWobJob : public CC_CLASS_MEMDUMP

	Author:
	Created:
	Purpose:

**************************************************************************************/

class CCWobJob : public CC_CLASS_MEMDUMP
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(CCWobJob);

};

#endif	//Include_CShadowerFlat
