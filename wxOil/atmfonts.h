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

// header file for ATM Font manager. This font manager provides access and
// control of Type1 fonts

/*
*/

#ifndef INC_ATMFONTS
#define INC_ATMFONTS

//#include "atm.h"
#include "fontbase.h"

class CharDescription;
class DocCoord;

/////////////////////////////////////////////////////////////////////////////
// Our thunk call mappings
/////////////////////////////////////////////////////////////////////////////

// DLL defined thunk calls
#define XSATM_GetUtilVersion			1
#define XSATM_ATMProperlyLoaded			2
#define XSATM_ATMGetVersion				3
#define XSATM_ATMGetOutline				4
#define XSATM_ATMForceExactWidth		5
#define XSATM_ATMBeginFontChange		6
#define XSATM_ATMEndFontChange			7
#define XSATM_ATMForceFontChange		8
#define XSATM_ATMFontStatus				9
#define XSATM_ATMAddFont				10
#define XSATM_ATMRemoveFont				11

// Minimum version of calls
#define MinVer_GetVersion				0x0100
#define MinVer_ProperlyLoaded			0x0100
#define MinVer_GetOutline				0x0100
#define MinVer_ForceExactWidth  		0x0101
#define MinVer_BeginFontChange			0x0205
#define MinVer_EndFontChange			0x0205
#define MinVer_ForceFontChange			0x0300
#define MinVer_FontStatus				0x0205
#define MinVer_AddFont					0x0205 
#define MinVer_RemoveFont				0x0205

// structures of DLL thunk calls
typedef BOOL (FAR PASCAL *LPFNMYCLOSEPATH) (LPSTR lpData);
typedef BOOL (FAR PASCAL *LPFNMYMOVETO) (LPATMFixedPoint lpFixPnt, LPSTR lpData);
typedef BOOL (FAR PASCAL *LPFNMYLINETO) (LPATMFixedPoint lpFixPnt, LPSTR lpData);
typedef BOOL (FAR PASCAL *LPFNMYCURVETO) (LPATMFixedPoint lpFixPnt0,
										  LPATMFixedPoint lpFixPnt1,
										  LPATMFixedPoint lpFixPnt2,
										  LPSTR lpData);

typedef WORD (FAR *LPFNATMPROPERLYLOADED)(void);

typedef WORD (FAR *LPFNATMGETUTILVERSION)(void);

typedef WORD (FAR *LPFNATMGETVERSION)(void);

typedef INT32  (FAR *LPFNATMGETOUTLINE)(	HDC              hDC,
					 					unsigned char    c,
							 			LPATMFixedMatrix lpMatrix,
							 			LPFNMYMOVETO     lpProcMoveTo,
							 			LPFNMYLINETO     lpProcLineTo,
							 			LPFNMYCURVETO	 lpProcCurveTo,
							 			LPFNMYCLOSEPATH	 lpProcClosePath,
							 			LPSTR            lpData);

typedef BOOL (FAR *LPFNATMFORCEEXACTWIDTH)(void);

typedef INT32 (FAR *LPFNATMFONTSTATUS)(LPSTR lpMenuName,
									WORD  style,
									LPSTR lpMetricsFile,
									LPSTR lpFontFile);

typedef INT32 (FAR *LPFNATMADDFONT)(LPSTR lpMenuName,
								 WORD  style,
								 LPSTR lpMetricsFile,
								 LPSTR lpFontFile);

typedef INT32 (FAR *LPFNATMREMOVEFONT)(LPSTR lpMenuName, WORD style);

typedef INT32 (FAR *LPFNATMBEGINFONTCHANGE)();
typedef INT32 (FAR *LPFNATMENDFONTCHANGE)();

/********************************************************************************************

>	class ATMFont : public FontBase
	   		
	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/95
	Purpose:	A class description of our ATM fonts. Mainly uses all base class functions
				at the moment, apart from the type

********************************************************************************************/

class ATMFont : public FontBase
{
	CC_DECLARE_DYNCREATE(ATMFont)

public:
	 ATMFont();
	~ATMFont();
	
	virtual FontClass GetFontClass() { return FC_ATM; };
	virtual void Dump();
};

/********************************************************************************************

>	class ATMFontMan : public CCObject
	   		
	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/9/95
	Purpose:	A static class to allow access to Type 1 fonts. There are few functions
				in this class which should be called directly. The OILFontMan provides the
				generic interface of font calls within this application.

********************************************************************************************/

class ATMFontMan : public CCObject
{
	CC_DECLARE_DYNCREATE(ATMFontMan)

	friend class OILFontMan;

// constructor
public:
	ATMFontMan();

// Function not supported by the generic OILFontMan, so you need to call them directly (yuk!)
public:
	static BOOL 	InitDLL();	// Older thunking dll 
	static BOOL 	InitLib();	// New non-thinking technology
	static void 	EnumAllFonts(OILEnumFonts* pClass);

	static INT32 	FontStatus(TCHAR *pMenuName, WORD Style, TCHAR *lpMetricsFile, TCHAR *lpFontFile);
	static INT32 	InstallFont(TCHAR *pMenuName, WORD Style, TCHAR *lpMetricsFile, TCHAR *lpFontFile);
	static INT32 	DeInstallFont(TCHAR *pMenuName, WORD Style);
	static BOOL 	ForceExactWidth();

	static OUTLINETEXTMETRIC *GetOutlineTextMetric(LOGFONT *pLogFont) { return NULL; }
// The support interface (functions OILFontMan will use)
private:
	static BOOL 	CacheNamedFont(String_64* pFontName);
	static BOOL 	CacheCompatibleFont(String_64* pFontName);
	static void 	ValidateCache();
	static void		FindClosestFont();
	static ATMFont* CreateNewFont(String_64* pFontName);
	static INT32 	GetUtilVersion() { return ATMUtilVersion; }
	static INT32 	GetVersion() { return ATMVersion; }
	static BOOL 	GetCharOutline( CharDescription& ChDesc, 
										DocCoord** ppCoords,
										PathVerb** ppVerbs,
										UINT32* pNumCoords,
										CDC* pDC);

// Utterly private - not even OILFontMan should use these!
private:
	static HINSTANCE GetATMDLL();
	static BOOL IsOkToCall();
	static BOOL CorrectVersion(INT32 version);

	// Older thunking dll
	static INT32 ThunkProperlyLoaded();
	static INT32	ThunkGetVersion();
	static INT32 ThunkGetUtilVersion();

private:
	// New non-thinking technology
	static INT32 LibProperlyLoaded();
	static INT32	LibGetVersion();
//	static INT32 LibGetUtilVersion();

	// this is NULL if the DLL isn't found on startup
	static HINSTANCE DLLHandle;

	// and here are types of ptrs to functions
	typedef WORD (FAR PASCAL * PFN_ATMProperlyLoaded)(void);
	typedef WORD (FAR PASCAL * PFN_ATMGetVersion)(void);

	typedef INT32  (FAR PASCAL * PFN_ATMGetOutline)(	HDC              hDC,
					 								unsigned char    c,
							 						LPATMFixedMatrix lpMatrix,
							 						LPFNMYMOVETO     lpProcMoveTo,
							 						LPFNMYLINETO     lpProcLineTo,
							 						LPFNMYCURVETO	 lpProcCurveTo,
							 						LPFNMYCLOSEPATH	 lpProcClosePath,
							 						LPSTR            lpData);

	typedef BOOL (FAR PASCAL * PFN_ATMForceExactWidth)(void);
	typedef WORD (FAR PASCAL * PFN_ATMBeginFontChange)(void);
	typedef WORD (FAR PASCAL * PFN_ATMEndFontChange)(void);
	typedef WORD (FAR PASCAL * PFN_ATMForceFontChange)(void);

	typedef INT32 (FAR PASCAL * PFN_ATMFontStatus)(	LPSTR lpMenuName,
													WORD  style,
													LPSTR lpMetricsFile,
													LPSTR lpFontFile);
	typedef INT32 (FAR PASCAL * PFN_ATMAddFont)(		LPSTR lpMenuName,
													WORD  style,
													LPSTR lpMetricsFile,
													LPSTR lpFontFile);
	typedef INT32 (FAR PASCAL * PFN_ATMRemoveFont)(	LPSTR lpMenuName, WORD style);


	// *******************
	// and actual pointers to functions in the DLL
	static PFN_ATMProperlyLoaded	pfnATMProperlyLoaded;
	static PFN_ATMGetVersion		pfnATMGetVersion;
	static PFN_ATMGetOutline		pfnATMGetOutline;
	static PFN_ATMForceExactWidth	pfnATMForceExactWidth;
	static PFN_ATMBeginFontChange	pfnATMBeginFontChange;
	static PFN_ATMEndFontChange		pfnATMEndFontChange;
	static PFN_ATMForceFontChange	pfnATMForceFontChange;
	static PFN_ATMFontStatus		pfnATMFontStatus;
	static PFN_ATMAddFont			pfnATMAddFont;
	static PFN_ATMRemoveFont		pfnATMRemoveFont;

	// *******************
	// Actual pointers to functions in the thunking DLL
	static LPFNATMPROPERLYLOADED	pfnXSATMProperlyLoaded;
//	static LPFNATMGETVERSION		pfnXSATMGetVersion;
	static LPFNATMGETOUTLINE		pfnXSATMGetOutline;
	static LPFNATMFORCEEXACTWIDTH	pfnXSATMForceExactWidth;
	static LPFNATMBEGINFONTCHANGE	pfnXSATMBeginFontChange;
	static LPFNATMENDFONTCHANGE		pfnXSATMEndFontChange;
//	static PFN_ATMForceFontChange	pfnXSATMForceFontChange;
	static LPFNATMFONTSTATUS		pfnXSATMFontStatus;
	static LPFNATMADDFONT			pfnXSATMAddFont;
	static LPFNATMREMOVEFONT		pfnXSATMRemoveFont;

private:
	static INT32 BeginFontChange();
	static INT32 AddFont(TCHAR *pMenuName, WORD Style, TCHAR *lpMetricsFile, TCHAR *lpFontFile);
	static INT32 RemoveFont(TCHAR *pMenuName, WORD Style);
	static INT32 EndFontChange();

private:
	static BOOL FAR PASCAL EXPORT MyClosePath(LPSTR lpData);
	static BOOL FAR PASCAL EXPORT MyMoveTo(LPATMFixedPoint lpFixPnt, LPSTR lpData);
	static BOOL FAR PASCAL EXPORT MyLineTo(LPATMFixedPoint lpFixPnt, LPSTR lpData);
	static BOOL FAR PASCAL EXPORT MyCurveTo(LPATMFixedPoint lpFixPnt1,
											LPATMFixedPoint lpFixPnt2,
											LPATMFixedPoint lpFixPnt3,
											LPSTR lpData);

// finally the class variables.
private:
	static BOOL ATMRunning;
	static INT32 ATMVersion;
	static INT32 ATMUtilVersion;

	static BOOL UseThunking;
};

// functions called as callbacks from some of the previous functions. The names break one
// of the style rules, but this is to re-enforce the fact that while these functions are
// global they should be treated as members of the ATMFontMan class.
// They can't be member functions, since they are used as callback functions.

INT32 APIENTRY	ATMFontMan_CallBackCacheNamedFont(ENUMLOGFONT FAR* lpelf,
												  NEWTEXTMETRIC FAR* lpntm,
												  INT32 FontType,
												  LPARAM lParam);
INT32 APIENTRY	ATMFontMan_CallBackValidateFont(ENUMLOGFONT FAR* lpelf,
												NEWTEXTMETRIC FAR* lpntm,
												INT32 FontType,
												LPARAM lParam);
INT32 APIENTRY	ATMFontMan_CallBackDispatchFont(ENUMLOGFONT FAR* lpelf,
												NEWTEXTMETRIC FAR* lpntm,
												INT32 FontType,
												LPARAM lParam);
INT32 APIENTRY	ATMFontMan_CallBackFindClosestFont(ENUMLOGFONT FAR* lpelf,
												   NEWTEXTMETRIC FAR* lpntm,
												   INT32 FontType,
												   LPARAM lParam);
#endif
