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

// Tablet.cpp : implementation file
//

#include "camtypes.h"

#include "tablet.h"
#include "wintab.h"

// This must be defined before the include of pktdef.h in order to get what we want out of it
#define PACKETDATA	(PK_CURSOR | PK_BUTTONS | PK_NORMAL_PRESSURE)
#define PACKETMODE	0
#include "pktdef.h"


CC_IMPLEMENT_DYNAMIC(WinTabPressurePen, CCPen);

#define new CAM_DEBUG_NEW



//const INT32 NPACKETQSIZE = 32;


/********************************************************************************************

>	WinTabPressurePen::WinTabPressurePen()

	Author:		Martin_Donelly (Xara Group Ltd) <camelotdev@xara.com> & Jason
	Created:	24/1/97

	Purpose:	Constructor. Initialises the pen

********************************************************************************************/

WinTabPressurePen::WinTabPressurePen()
{
	// Initialise member vars to sensible defaults
	hTab			= NULL;
	wActiveCsr		= NULL;
	wOldCsr			= NULL;
	wPrsBtn			= 0;
	ClickThreshold	= 0;
	PressureMax		= MAXPRESSURE;
	PenNotOnTablet	= TRUE;

	// Read the tablet default settings as a basis for our settings
	LOGCONTEXT lcMine;		
	INT32 Result = WTInfo(WTI_DEFCONTEXT, 0, &lcMine);
	if (Result == 0)
	{
		TRACE( _T("Pressure sensitive tablet not detected\n"));
		return;
	}

	// Modify some of the flags in the block we read above
	wsprintf(lcMine.lcName, "Camelot");
	lcMine.lcOptions	|= CXO_SYSTEM;
	lcMine.lcPktData	= PACKETDATA;
	lcMine.lcPktMode	= PACKETMODE;
	lcMine.lcMoveMask	= PACKETDATA;

	hTab = WTOpen(hMainframeWnd, &lcMine, TRUE);
	if (hTab == NULL)
	{
		ERROR3("Failed to initialise pressure sensitive tablet");
		return;
	}

	PressureAvailable = TRUE;		// We initialised! Woo hoo!

	// Set the packet queue size we desire - Why? The default of 8 should be ample
/*
	Result = WTQueueSizeGet(hTab);
	TRACE( _T("Q size is %ld\n"), Result);

	INT32 QSize = NPACKETQSIZE;
	Result = 0;
	while (QSize >= 1 && Result == 0)
	{
		Result = WTQueueSizeSet(hTab, QSize);
		QSize /= 2;
	}
*/
	// And initalise the tablet ready for use
	InitPressure();
}



/********************************************************************************************

>	WinTabPressurePen::~WinTabPressurePen()

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/1/97

	Purpose:	Destructor. Deinitialises the pen

********************************************************************************************/

WinTabPressurePen::~WinTabPressurePen()
{
	// If we've got a context open, let's close it to be tidy
	if (hTab != NULL)
		WTClose(hTab);
}



/********************************************************************************************

>	virtual void WinTabPressurePen::ReadTabletPressureData(void)

	Author:		Martin_Donelly (Xara Group Ltd) <camelotdev@xara.com> & Jason
	Created:	24/1/97

	Returns:	TRUE if it read pressure successfully
				FALSE if it failed - in this case, the caller (base class) will default
				to calculating a faked pressure value from movement information. (e.g.
				if you stop getting pen pressure packets, revert to using movement
				rather than always returning zero!)

	Purpose:	Records the latest pressure info from the pressure sensitive tablet
				Does nothing if this is not a "real" pen

				Does nothing in the base class.

********************************************************************************************/

BOOL WinTabPressurePen::ReadTabletPressureData(void)
{
	// If we couldn't initialise the tablet, or the pen isn't physically present on
	// the tablet at the moment (meaning that mouse movements are being generated
	// by a mouse), then revert to using the mouse simulation modes.
	if (!PressureAvailable || PenNotOnTablet)
		return(FALSE);

	if (hTab == NULL)
	{
		ERROR3("No tablet in ReadTabletPressureData");
		return(FALSE);
	}

	// Make sure our tablet context is "on top" of all others
	WTOverlap(hTab, TRUE);

	PACKET localPacketBuf;
	INT32 nPackets = WTPacketsGet(hTab, 1, &localPacketBuf);

	// If there are no new packets, then return immediately, pretending to the base class
	// that we were happy, so that it doesn't add in mouse handling code at random while we draw!
	if (nPackets <= 0)
		return(TRUE);

	wActiveCsr = localPacketBuf.pkCursor;

	// If this cursor doesn't return pressure data we need to behave like a normal mouse...
	WTPKT pktflags = 0;
	WTInfo(WTI_CURSORS + wActiveCsr, CSR_PKTDATA, &pktflags);
	if ((pktflags & PK_NORMAL_PRESSURE) == 0)
		return FALSE;

	// Determine which cursor is active - note that a cursor in this sense is
	// an input device, such as the pen end/eraser end of the pen. I think.
	if (wActiveCsr != wOldCsr)
	{
		// re-init on cursor change.
		InitPressure();
		wOldCsr = wActiveCsr;
	}

	if (localPacketBuf.pkButtons & (1 << wPrsBtn))
	{
		// The user has pressed hard enough to pass the "click" threshold
		// so the "button" is effectively down. We subtract the click
		// threshold value from the pressure, and return that. It is automatically
		// scaled by the pen caller, using our GetPressureMax() value.
		// We must be careful not to return negative pressure, though, because
		// a second threshold is used to control "release" of the click, so
		// that the pen does not "flutter" between clicked/unclicked when it nears
		// the threshold.
		if (localPacketBuf.pkNormalPressure > ClickThreshold)
			PenPressure = localPacketBuf.pkNormalPressure - ClickThreshold;
		else
			PenPressure = 0;
	}
	else
	{
		// The user has not pressed hard enough to pass the "click" threshold
		// so the "button" is effectively up - we ignore any pressure in this case.
		PenPressure = 0;
	}

	// And flush any enqueued packets so the next one we get is vaguely related to
	// the mouse position at which it occurred.
	WTPacketsGet(hTab, 1, NULL);
	return(TRUE);
}



/********************************************************************************************

>	void WinTabPressurePen::InitPressure(void)

	Author:		Martin_Donelly (Xara Group Ltd) <camelotdev@xara.com> & Jason
	Created:	24/1/97

	Purpose:	Sets up the pen ready for reading pressure information.
				Reads back the maximum pressure value we'll be given, etc

********************************************************************************************/

void WinTabPressurePen::InitPressure(void)
{
	/* browse WinTab's many info items to discover pressure handling. */
	AXIS np;
	LOGCONTEXT lc;
	BYTE logBtns[32];
	UINT32 btnMarks[2];
	UINT32 size;

	/* discover the LOGICAL button generated by the pressure channel. */
	/* get the PHYSICAL button from the cursor category and run it */
	/* through that cursor's button map (usually the identity map). */
	wPrsBtn = (BYTE)-1;
	WTInfo(WTI_CURSORS + wActiveCsr, CSR_NPBUTTON, &wPrsBtn);
	size = WTInfo(WTI_CURSORS + wActiveCsr, CSR_BUTTONMAP, &logBtns);
	if ((UINT32)wPrsBtn < size)
		wPrsBtn = logBtns[wPrsBtn];

	/* get the current context for its device variable. */
	WTGet(hTab, &lc);

	/* get the size of the pressure axis. */
	WTInfo(WTI_DEVICES + lc.lcDevice, DVC_NPRESSURE, &np);
	UINT32 prsNoBtnOrg = (UINT32)np.axMin;
	UINT32 prsNoBtnExt = (UINT32)np.axMax - (UINT32)np.axMin;

	/* get the button marks (up & down generation thresholds) */
	/* and calculate what pressure range we get when pressure-button is down. */
	btnMarks[1] = 0; /* default if info item not present. */
	WTInfo(WTI_CURSORS + wActiveCsr, CSR_NPBTNMARKS, btnMarks);
	ClickThreshold = btnMarks[1];

	PressureMax = (UINT32)np.axMax - ClickThreshold;
}



/********************************************************************************************

>	virtual void WinTabPressurePen::StartStroke(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/1/97

	Purpose:	Informs the Pen class that you are starting a stroke (a drag
				operation for which you wish to record pressure information)

				If you do not call this method, then pressure information
				will be "faked" based on mouse speed/direction information.

				It should be called when you start your drag (on button down)

				When the stroke finishes, remember to call WinTabPressurePen::EndStroke

********************************************************************************************/

void WinTabPressurePen::StartStroke(void)
{
	// Set the base class up to generate pressure in the correct way
	// In case we fail, set pressure to maximum, so if we fall through
	// to a mouse handler, we don't get "blank" strokes
	CurrentPressureMode = DefaultPressureMode;
	PenPressure = PressureMax;

	// If we're not currently configured to use the pen pressure, then
	// we don't need to do any more - let the base class handle everything.
	if (CurrentPressureMode != PressureMode_Pen)
		return;
	
	// DY - we no longer wish to fake pressure using mouse speed, so if we're not
	// on the tablet at the start of the stroke then we're not doing it
	if (PenNotOnTablet)
		CurrentPressureMode = PressureMode_None;

	// If we failed to initialise a tablet, then revert to speed mode
	if (hTab == NULL)
	{
		CurrentPressureMode = PressureMode_Speed;
		return;
	}

	// ****!!!!TODO
	// We should really check tablet proximity here. If the pen's not
	// near the tablet, the user must be dragging with a different input
	// device. This requires that our Mainframe watches out for WT_PROXIMITY
	// messages and tells us about them.

	// OK, turn that baby on!
//	WTEnable(hTab, TRUE);

	PenPressure = 0;
}



/********************************************************************************************

>	virtual void WinTabPressurePen::EndStroke(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/1/97

	Purpose:	Informs the Pen class that you are completing a stroke (a drag
				operation for which you recorded pressure information)

				This function must be called to "cancel" out a call to StartStroke.
				It should be called in your drag completion routine, and should
				be called under all "end of drag" circumstances.

********************************************************************************************/

void WinTabPressurePen::EndStroke(void)
{
	// Stop WinTab bothering to collect packets now - we don't want em
	if (hTab != NULL)
	{
//		WTEnable(hTab, FALSE);			// Disable the pen
		WTPacketsGet(hTab, 1, NULL);	// And flush remaining packets
	}
}



/********************************************************************************************

>	void WinTabPressurePen::PenProximityChanged(BOOL LeavingTablet)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/1/97

	Inputs:		LeavingTablet - TRUE if the pen is leaving the tablet detection area
								FALSE if the pen is re-entering the tablet area

	Purpose:	Called by the CMainFrame window when it recieves a WinTab WT_PROXIMITY
				message. This indicates that the pen is moving in or out of the pen
				detection area over the tablet. We keep track of the proximity of the
				pen, so that if the user puts it down and starts drawing with their
				mouse, we realise this and revert to base-class simulated pressure.

********************************************************************************************/

void WinTabPressurePen::PenProximityChanged(BOOL LeavingTablet)
{
	PenNotOnTablet = LeavingTablet;
}

