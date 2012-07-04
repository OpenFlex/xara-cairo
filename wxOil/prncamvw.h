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


// Holds most of the OIL-y printing facilities used by ScreenCamView.

#ifndef INC_PRNCAMVW
#define INC_PRNCAMVW


/********************************************************************************************

>	class PrintMonitor : public SimpleCCObject

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	19/06/95
	Purpose:	Monitors print jobs to ensure that we don't try to start more than one
				simulataneously, and to ensure that print jobs are released when we
				suffer a serious error (CPU exception).
				Also repository for printing preferences.
	SeeAlso:	

********************************************************************************************/

class PrintMonitor : public SimpleCCObject
{
public:
	static BOOL StartPrintJob(CNativeDC *);
	static void EndPrintJob();
	static BOOL IsPrintStatusOK();
	static BOOL InitPrefs();
	static void SetPrintingActive(BOOL);
	static BOOL IsPrintingActive();
	static BOOL IsPrintingNow();
	static void WantFullRedraw(BOOL);
	static BOOL IsYieldDisabled() {return s_YieldDisabled;}

	typedef enum
	{
		MASK_SIMPLE = 0,
		MASK_MASKED,
		MASK_OPTIMAL
	} MaskType;

public:
	static BOOL PrintWithMask;
	static BOOL PrintWithDriverBands;
	static MaskType PrintMaskType;
	static BOOL FullRedrawNeeded;
	static BOOL s_YieldDisabled;

protected:
	static CNativeDC * CurrentPrintJob;
	static INT32 MySeriousErrorCount;
	static BOOL PrintingIsActive;
};


#endif  // INC_PRNCAMVW
