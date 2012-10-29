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


// operation(s) to test Camelot speed

/*
*/

#include "camtypes.h"
//#include "camconfig.h"
#include "speedtst.h"

//#include "andy.h"
//#include "will.h"
//#include "richard2.h"
//#include "phil.h"
//#include "resource.h"
#include "camprofile.h"

/*
#include <time.h>
#include "mainfrm.h"

#include "xadraw.h"
#include "zoomops.h"
#include "wrkrect.h"
*/

CC_IMPLEMENT_DYNCREATE(OpTimeDraw, Operation)
CC_IMPLEMENT_DYNCREATE(OpClearCache, Operation)
CC_IMPLEMENT_DYNCREATE(OpThrottleCache, Operation)

#define new CAM_DEBUG_NEW


// This global var is incremented every time the speed test op is executed.
// It was put in so I could test the speed increase of the path point caching inside 
// the NodeBlendPath object. When SpeedTest_Count was even I checked the cache, 
// when odd I ignored it
// I've left it in as I'm sure others will find it useful
// Markn - 14-5-99

//INT32 SpeedTest_Count = 0;

/********************************************************************************************

>	BOOL OpTimeDraw::Init()

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/1/94
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if worked, FALSE if failed (out of memory)
	Purpose:	Declares op descriptors for time testing
	Errors:		Returns FALSE on failure.
	Scope:		Static

********************************************************************************************/


BOOL OpTimeDraw::Init()
{
	BOOL bOK = TRUE;
	if (bOK) bOK = RegisterOpDescriptor(
										0,
										_R(IDS_TIMEDRAW),
										CC_RUNTIME_CLASS(OpTimeDraw),
										OPTOKEN_TIMEDRAW,
										GetState,
										_R(IDS_TIMEDRAW),
										_R(IDBBL_TIMEDRAW)
									  );

	if (bOK) bOK = RegisterOpDescriptor(
										0,
										_R(IDS_CLEARCACHE),
										CC_RUNTIME_CLASS(OpClearCache),
										OPTOKEN_CLEARCACHE,
										GetState,
										_R(IDS_CLEARCACHE),
										_R(IDBBL_CLEARCACHE)
									  );

	if (bOK) bOK = RegisterOpDescriptor(
										0,
										_R(IDS_THROTTLECACHE),
										CC_RUNTIME_CLASS(OpThrottleCache),
										OPTOKEN_THROTTLECACHE,
										GetState,
										_R(IDS_THROTTLECACHE),
										_R(IDBBL_THROTTLECACHE)
									  );

	return bOK;
}

/********************************************************************************************

>	void OpTimeDraw::Do(OpDescriptor*)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/1/94
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Forces a redraw of the current document and displays the time taken to do
	Errors:		None

********************************************************************************************/

#ifdef CONFIG_DEBUG_XADRAW
INT32 _cdecl XaTimingSortFunc(const void *arg1, const void *arg2)
{
	DWORD *p1 = (DWORD*)arg1;
	DWORD *p2 = (DWORD*)arg2;
	if (g_XaTimes[*p2].QuadPart - g_XaTimes[*p1].QuadPart)
		return((INT32)(g_XaTimes[*p2].QuadPart - g_XaTimes[*p1].QuadPart));
	else
		return((INT32)g_XaCalls[*p2] - (INT32)g_XaCalls[*p1]);
}
#endif

void OpTimeDraw::Do(OpDescriptor*)
{
//	SpeedTest_Count++;

	DocView *pDocView = DocView::GetSelected();
	if (pDocView == NULL)
		return;

	wxYield(); // let through some wxPaint events

	CamProfiler Profiler;
	// clock() measures system time so excludes (e.g.) X-Windows blit time
	// so this is rather a peculiar test
	clock_t Timer = clock();											// start clock

	pDocView->ForceRedraw();											// posts the paint message

	wxWindow* pWnd = DocView::GetCurrentRenderWindow();
	if (pWnd)
		pWnd->Update();											// do the paint

	// now we wait until all rendering has finished
	while ( Camelot.ServiceRendering() )
	{
	}

	Timer = clock() - Timer;											// stop clock

	double Results[CAMPROFILE_NONE];
	double total = Profiler.Read(Results);

	// as this is for our use only, it is permitted to hard-code English strings

	// this lovely line translates the clock_t value into a useful value without using
	// floats
	String_256 Buf; // "Redraw took %d.%03d secs"

	Buf.MakeMsg(_R(IDS_SPEEDTST_REDRAW_TOOK), (INT32)(Timer / CLOCKS_PER_SEC),
								(INT32)((Timer % CLOCKS_PER_SEC) * 1000 / CLOCKS_PER_SEC) );
#if 1

	// All this because MakeMsg doesn't do floating point
#define PFORM(x) ((INT32)((x<0)?ceil(x):floor(x))) , ((INT32)(floor(0.5+( ( (x<0)?(ceil(x)-x):(x - floor(x)) ) * 1000 ))))

	double error=Results[CAMPROFILE_OTHER ]+
				 Results[CAMPROFILE_GDRAW ]+
				 Results[CAMPROFILE_SHADOW]+
				 Results[CAMPROFILE_BEVEL ]+
				 Results[CAMPROFILE_BLIT  ]-total;

	String_256 Buf2;
	
	Buf2.MakeMsg(_R(IDS_SPEEDTST_REDRAW_TOOK2), _T("TOTAL"), PFORM(total));
	Buf += _T(", ");
	Buf += Buf2;
	Buf2.MakeMsg(_R(IDS_SPEEDTST_REDRAW_TOOK2), _T("GDRAW"), PFORM(Results[CAMPROFILE_GDRAW]));
	Buf += _T(", ");
	Buf += Buf2;
	Buf2.MakeMsg(_R(IDS_SPEEDTST_REDRAW_TOOK2), _T("SHADOW"), PFORM(Results[CAMPROFILE_SHADOW]));
	Buf += _T(", ");
	Buf += Buf2;
	Buf2.MakeMsg(_R(IDS_SPEEDTST_REDRAW_TOOK2), _T("BEVEL"), PFORM(Results[CAMPROFILE_BEVEL]));
	Buf += _T(", ");
	Buf += Buf2;
	Buf2.MakeMsg(_R(IDS_SPEEDTST_REDRAW_TOOK2), _T("BLIT"), PFORM(Results[CAMPROFILE_BLIT]));
	Buf += _T(", ");
	Buf += Buf2;
	Buf2.MakeMsg(_R(IDS_SPEEDTST_REDRAW_TOOK2), _T("OTHER"), PFORM(Results[CAMPROFILE_OTHER]));
	Buf += _T(", ");
	Buf += Buf2;
	
	// Only report error if it is significant. With current code, it shouldn't actually exist at all bar
	// floating point to INT32 rounding error.
	if (fabs(error) > 0.5/1000.0)
	{
		Buf2.MakeMsg(_R(IDS_SPEEDTST_REDRAW_TOOK2), _T("ERROR"), PFORM(error));
		Buf += _T(", ");
		Buf += Buf2;
	}

#endif
	Convert::ReplaceDecimalPoint(&Buf);									// Just to keep Neville happy... :-


	// URGH! This should use the proper Camelot dialog box system but we don't have it available right now
	::wxMessageBox( (TCHAR *)Buf );

	End();																// cleanup memory	
}
/********************************************************************************************

>	OpTimeDraw::OpTimeDraw()

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/1/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	Constructor for OpTimeDraw operation. It is not undoable.
	Errors:		None

********************************************************************************************/

OpTimeDraw::OpTimeDraw()
{
}


/********************************************************************************************

>	OpState OpTimeDraw::GetState(String_256*, OpDescriptor*)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/1/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	This item is always available, so long as a document is visible.
	Errors:		None

********************************************************************************************/

OpState OpTimeDraw::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;

	return OpSt;
}

/********************************************************************************************

>	void OpClearCache::Do(OpDescriptor*)

	Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/06/2004
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Toggles bitmap cache enabled pref also Clears the bitmap cache for performance testing
	Errors:		None

********************************************************************************************/

void OpClearCache::Do(OpDescriptor*)
{
	if (NodeRenderableBounded::bEnableCacheing)
	{
		InformWarning(_R(IDS_WARN_DISABLECACHEING), _R(IDS_OK));
	}

	NodeRenderableBounded::bEnableCacheing = ! NodeRenderableBounded::bEnableCacheing;

	CBitmapCache* pBitmapCache = Camelot.GetBitmapCache();
	if (pBitmapCache)
	{
		pBitmapCache->DeInitialise();
	}

	End();																// cleanup memory	
}

/********************************************************************************************

>	OpClearCache::OpClearCache()

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/1/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	Constructor for OpTimeDraw operation. It is not undoable.
	Errors:		None

********************************************************************************************/

OpClearCache::OpClearCache()
{
}


/********************************************************************************************

>	OpState OpClearCache::GetState(String_256*, OpDescriptor*)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/1/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	This item is always available, so long as a document is visible.
	Errors:		None

********************************************************************************************/

OpState OpClearCache::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;

	OpSt.Ticked = NodeRenderableBounded::bEnableCacheing;

	return OpSt;
}




/********************************************************************************************

>	void OpThrottleCache::Do(OpDescriptor*)

	Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/06/2004
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Toggles bitmap cache enabled pref also Clears the bitmap cache for performance testing
	Errors:		None

********************************************************************************************/

void OpThrottleCache::Do(OpDescriptor*)
{
	if (NodeRenderableBounded::bThrottleCacheing)
	{
		InformWarning(_R(IDS_WARN_DISABLE_THROTTLING), _R(IDS_OK));
	}
	else
	{
		InformWarning(_R(IDS_WARN_ENABLE_THROTTLING), _R(IDS_OK));
	}

	NodeRenderableBounded::bThrottleCacheing = ! NodeRenderableBounded::bThrottleCacheing;

	End();																// cleanup memory	
}

/********************************************************************************************

>	OpThrottleCache::OpThrottleCache()

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/1/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	Constructor for OpTimeDraw operation. It is not undoable.
	Errors:		None

********************************************************************************************/

OpThrottleCache::OpThrottleCache()
{
}


/********************************************************************************************

>	OpState OpThrottleCache::GetState(String_256*, OpDescriptor*)

	Author: 	Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/1/94
	Inputs:
	Outputs:
	Returns:
	Purpose:	This item is always available, so long as a document is visible.
	Errors:		None

********************************************************************************************/

OpState OpThrottleCache::GetState(String_256*, OpDescriptor*)
{
	OpState OpSt;

	OpSt.Ticked = NodeRenderableBounded::bThrottleCacheing;

	return OpSt;
}




