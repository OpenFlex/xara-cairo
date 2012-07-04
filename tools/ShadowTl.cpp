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
#include "camtypes.h"
#include "shadowtl.h"
#include <objbase.h>
#include <initguid.h>

//#include "nodeattr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "lineattr.h"
//#include "attrmgr.h" - in camtypes.h [AUTOMATICALLY REMOVED]

// Place any IMPLEMENT type statements here
CC_IMPLEMENT_MEMDUMP(CCWobJob, CC_CLASS_MEMDUMP)

// We want better memory tracking
#define new CAM_DEBUG_NEW

/*******************************************************************************

>	class CShadowerFlat

	Author:		Harrison_Ainsworth (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/12/97
	Purpose:	COM interface for the flat shadow generation system.
				...
	See also:	ComShadowerFlat.cpp

*******************************************************************************/

interface IComShadowerFlat : public IUnknown
{
public:
	// set choices
	virtual	void __stdcall SetChoicesToDefault() = 0;

	virtual	void __stdcall SetChoices( const BOOL* MakeWallShadow, const AFloatPt01* Darkness01,
									   const APixels* Blurriness, const ACoordPixels XYPosition,
									   const ADegrees* Tilt, const AFloatPt01* YScale01 ) = 0;

	virtual	void __stdcall SetBaseline( const AFloatPt01* Baseline ) = 0;

	// get choices
	virtual	void __stdcall GetChoices( BOOL* MakeWallShadow, AFloatPt01* Darkness01, APixels* Blurriness,
									   ACoordPixels XYPosition, ADegrees* Tilt, AFloatPt01* YScale01 ) const = 0;

	virtual	void __stdcall GetBaseline( AFloatPt01* Baseline ) const = 0;

	// choices range queries
	virtual	void __stdcall GetDarknessRange( AFloatPt01& Min, AFloatPt01& Max ) const = 0;
	virtual	void __stdcall GetBlurrinessRange( APixels& Min, APixels& Max ) const = 0;
	virtual	void __stdcall GetPositionRange( ACoordPixels Min, ACoordPixels Max ) const = 0;
	virtual	void __stdcall GetProjectionRange( ADegrees& MinTilt, ADegrees& MaxTilt, AFloatPt01& MinYScale,
											   AFloatPt01& MaxYScale ) const = 0;
	// alpha channel type switches
	virtual HRESULT __stdcall SwitchToTransparencyInsteadOfAlpha( BOOL YesOrNo ) = 0;
	virtual HRESULT __stdcall SwitchToUpsideDownPixelAddressing( BOOL YesOrNo ) = 0;

	// make shadow
	virtual	HRESULT	__stdcall InverseShadowBoundCalc( ACoordPixels UnshadowedWidHei, ACoordPixels UnshadowedPos,
													  const ACoordPixels& ShadowedWidHei,
													  const AFloatPt01* Baseline ) const = 0;

	virtual	HRESULT	__stdcall CalcShadowBound( ACoordPixels ShadowWidHei, ACoordPixels ShadowPos,
											   const AAlphaChannel& TransparencyMap, const ACoordPixels& tWidHei,
											   const ACoordPixels& tPos ) const = 0;

	virtual	HRESULT	__stdcall DrawShadow( const AAlphaChannel& ShadowMapOut, const ACoordPixels& sWidHei,
										  const ACoordPixels& sPos, const AAlphaChannel& TransparencyMapIn,
										  const ACoordPixels& tWidHei, const ACoordPixels& tPos ) const = 0;
};

// globally unique IDs ////////////////////////////////////////////////////////////////////////////
const GUID CShadowerFlat::IID_IComShadowerFlat = 
					{ 0x326f6db0, 0x7b82, 0x11d1, { 0xac, 0xbf, 0x0, 0x20, 0xaf, 0xe1, 0x4b, 0x7d } };
					// {326F6DB0-7B82-11d1-ACBF-0020AFE14B7D}

const GUID CShadowerFlat::CLSID_CComShadowerFlat =
					{ 0x326f6db1, 0x7b82, 0x11d1, { 0xac, 0xbf, 0x0, 0x20, 0xaf, 0xe1, 0x4b, 0x7d } };
					// {326F6DB1-7B82-11d1-ACBF-0020AFE14B7D}

// standard object management /////////////////////////////////////////////////////////////////////
CShadowerFlat::CShadowerFlat()
{
	pShadower_m = NULL;
}

CShadowerFlat::~CShadowerFlat()
{
	if( pShadower_m )
		pShadower_m->Release();
}

CShadowerFlat::CShadowerFlat( const CShadowerFlat& Other )
{
	pShadower_m = NULL;
}

CShadowerFlat& CShadowerFlat::operator= ( const CShadowerFlat& Other )
{
   return *this;
}

HRESULT CShadowerFlat::_Init_()
{
	
	// if( pShadower_m )
	{
		// already initialised so drop out
		return S_OK;
	}
	
	HRESULT hr = ::CoCreateInstance( CLSID_CComShadowerFlat, NULL, CLSCTX_INPROC_SERVER, IID_IComShadowerFlat,
									 (void**)&pShadower_m );
	if( FAILED( hr ) )
		return hr;

	pShadower_m->SwitchToTransparencyInsteadOfAlpha( FALSE );
	pShadower_m->SwitchToUpsideDownPixelAddressing( TRUE );

	return S_OK;
}

// set choices ////////////////////////////////////////////////////////////////////////////////////
void CShadowerFlat::SetChoicesToDefault()
{
	/*
	if( pShadower_m )
		pShadower_m->SetChoicesToDefault();
		*/
}

void CShadowerFlat::SetChoices( const BOOL* MakeWallShadow, const AFloatPt01* Darkness01, const APixels* Blurriness,
                           const ACoordPixels XYPosition, const ADegrees* Tilt, const AFloatPt01* YScale01 )
{
	/*
	if( pShadower_m )
		pShadower_m->SetChoices( MakeWallShadow, Darkness01, Blurriness, XYPosition, Tilt, YScale01 );
		*/
}

void CShadowerFlat::SetBaseline( const AFloatPt01* Baseline )
{
	/*
	if( pShadower_m )
		pShadower_m->SetBaseline( Baseline );
		*/
}

// get choices ////////////////////////////////////////////////////////////////////////////////////
void CShadowerFlat::GetChoices( BOOL* MakeWallShadow, AFloatPt01* Darkness01, APixels* Blurriness,
                           ACoordPixels XYPosition, ADegrees* Tilt, AFloatPt01* YScale01 ) const
{
	/*
	if( pShadower_m )
		pShadower_m->GetChoices( MakeWallShadow, Darkness01, Blurriness, XYPosition, Tilt, YScale01 );
		*/
}

void CShadowerFlat::GetBaseline( AFloatPt01* Baseline ) const
{
	/*
	if( pShadower_m )
		pShadower_m->GetBaseline( Baseline );*/
}

// choices range queries //////////////////////////////////////////////////////////////////////////
void CShadowerFlat::GetDarknessRange( AFloatPt01& Min, AFloatPt01& Max ) const
{
	/*
	if( pShadower_m )
		pShadower_m->GetDarknessRange( Min, Max );
		*/
}

void CShadowerFlat::GetBlurrinessRange( APixels& Min, APixels& Max ) const
{
	/*
	if( pShadower_m )
		pShadower_m->GetBlurrinessRange( Min,  Max );
		*/
}

void CShadowerFlat::GetPositionRange( ACoordPixels Min, ACoordPixels Max) const
{
	/*
	if( pShadower_m )
		pShadower_m->GetPositionRange( Min, Max );
		*/
}

void CShadowerFlat::GetProjectionRange( ADegrees& MinTilt, ADegrees& MaxTilt,
                                   AFloatPt01& MinYScale, AFloatPt01& MaxYScale ) const
{
	/*
	if( pShadower_m )
		pShadower_m->GetProjectionRange( MinTilt, MaxTilt, MinYScale, MaxYScale );
		*/
}

// alpha channel type switches ////////////////////////////////////////////////////////////////////
HRESULT CShadowerFlat::SwitchToTransparencyInsteadOfAlpha( BOOL YesOrNo )
{
	/*
	if( pShadower_m )
		return pShadower_m->SwitchToTransparencyInsteadOfAlpha( YesOrNo );
	else
		return E_FAIL;
		*/

	return S_OK;
}

HRESULT CShadowerFlat::SwitchToUpsideDownPixelAddressing( BOOL YesOrNo )
{
	/*
	if( pShadower_m )
		return pShadower_m->SwitchToUpsideDownPixelAddressing( YesOrNo );
	else
		return E_FAIL;
		*/
	return S_OK;
}

// make shadow ////////////////////////////////////////////////////////////////////////////////////
HRESULT CShadowerFlat::InverseShadowBoundCalc( ACoordPixels UnshadowedWidHei, ACoordPixels UnshadowedPos,
                                          const ACoordPixels& ShadowedWidHei, const AFloatPt01* Baseline ) const
{
	/*
	if( pShadower_m )
		return pShadower_m->InverseShadowBoundCalc( UnshadowedWidHei, UnshadowedPos, ShadowedWidHei, Baseline );
	else
		return E_FAIL;
		*/

	return S_OK;
}

HRESULT CShadowerFlat::CalcShadowBound( ACoordPixels ShadowWidHei, ACoordPixels ShadowPos, const AAlphaChannel& TransparencyIn,
								   const ACoordPixels& tWidHei, const ACoordPixels& tPos ) const
{
	/*
	if( pShadower_m )
		return pShadower_m->CalcShadowBound( ShadowWidHei, ShadowPos, TransparencyIn, tWidHei, tPos );
	else
		return E_FAIL;
		*/

	return S_OK;
}

HRESULT CShadowerFlat::DrawShadow( const AAlphaChannel& ShadowOut, const ACoordPixels& sWidHei, const ACoordPixels& sPos,
							  const AAlphaChannel& TransparencyIn, const ACoordPixels& tWidHei, const ACoordPixels& tPos ) const
{
	/*
	if( pShadower_m )
		return  pShadower_m->DrawShadow( ShadowOut, sWidHei, sPos, TransparencyIn, tWidHei, tPos );
	else
		return  E_FAIL;
		*/

	return S_OK;
}
