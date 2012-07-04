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


#ifndef INC_AI_EPS_5
#define INC_AI_EPS_5

//#include "epsfiltr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "ai_eps.h"
//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "document.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "impbmp.h"

class AI5Gradient;
class AIGradientProcessor;
class AIBitmapProcessor;
class AILayerProcessor;

// All the commands used by AI EPS 5 files.
enum
{
	// Graduated fills
	EPSC_Bd = EPSC_t + 1,
	EPSC_Bm,
	EPSC_Bc,
	EPSC__Bs,
	EPSC__BS,
	EPSC__Br,
	EPSC_BD,
	EPSC_Bg,
	EPSC_Bb,
	EPSC_BB,
	EPSC_Bh,
	EPSC_HexStart,
	EPSC_HexEnd,

	// Layer stuff
	EPSC_Lb,
	EPSC_LB,
	EPSC_Ln,

	// Path tweaks
	EPSC_Ap,
	EPSC_Ar,
	EPSC_XR,

	// bitmaps
	EPSC_XI,
	EPSC_XF,
	EPSC_XG,
	EPSC_Xh,
	EPSC_XH,

	// unknown
	EPSC_XP,

	// object tags
	EPSC_XT,

	// spurious
	EPSC_Xm,

	// RGB Colours
	EPSC_Xa,
	EPSC_XA,
	EPSC_Xx,
	EPSC_XX
};

/********************************************************************************************

>	class AI5EPSFilter : public AIEPSFilter

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	A filter that imports EPS files in Adobe Illustrator 7.0 EPS format.
	SeeAlso:	EPSFilter

********************************************************************************************/

class AI5EPSFilter : public AIEPSFilter
{
	CC_DECLARE_DYNAMIC(AI5EPSFilter);
	
public:
	AI5EPSFilter();
	BOOL Init();
	TCHAR* GetEPSCommand(EPSCommand Cmd);

	// Allow a layer to be set with property flags.
	BOOL CreateLayer ( String_256	&LayerName,
					   BOOL			IsLocked,
					   BOOL			IsPrintable,
					   BOOL			IsVisible );

	// data access
	EPSStack&	GetStack()			{	return Stack;		}
	CCLexFile*	GetEPSFile()		{	return EPSFile;		}
	const TCHAR*	GetTokenBuf()	{	return TokenBuf;	}
	INT32& GetLastProgressUpdate()	{	return LastProgressUpdate;	}

protected:
	virtual BOOL PrepareToImport();
	virtual void CleanUpAfterImport(BOOL Successful);
	virtual void LookUpToken();
	virtual BOOL ProcessToken();
	INT32 EPSHeaderIsOk(ADDR pFileHeader, UINT32 HeaderSize);
	virtual BOOL ProcessFilterComment();

	void DecodeAI5GradFill(const DocCoord& StartPoint, 
						   double Angle, 
						   double Length, 
						   const String_64& FillName);
	virtual BOOL DecodeLayer ( void );
	BOOL DecodeImageOperator();
	BOOL ReadImageData( ADDR pData, INT32 nLength );
	BOOL IgnoreHexData();
	// The array of keyword names
	static CommandMap AI5Commands[];


	//	the "processors" maintain the state for the current import
	//	hypothetically it should be possible to push them on a stack
	//	but this has not been implemented
	AIGradientProcessor	*mpGradientProc;
	AIBitmapProcessor	*mpBitmapProc;
	AILayerProcessor	*mpLayerProc;

	BOOL				mbReadingGradFill;
	BOOL				mbReadingBitmap;
};

#endif
