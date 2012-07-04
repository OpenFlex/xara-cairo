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

// Tablet.h : header file
//

// WEBSTER - markn 25/4/97
// No tablet stuff required in Webster
#ifdef WEBSTER
#define INC_TABLET
#endif // WEBSTER

#ifndef INC_TABLET
#define INC_TABLET

#include "pen.h"
#include "wintab.h"


/********************************************************************************************

>	class WinTabPressurePen : public CCPen

	Author:		Martin_Donelly (Xara Group Ltd) <camelotdev@xara.com> (& Jason)

	Created:	24/1/97

	Purpose:	Overrides the base pressure-sensitive pen class to provide support
				for WinTab pressure-sensitive tablet devices. When such a device
				is unavailable, this class returns control to the base-class to
				allow joysticks and mice to be used to simulate pens based on speed
				and/or direction of travel rather than real applied pressure.

********************************************************************************************/

class WinTabPressurePen : public CCPen
{
	CC_DECLARE_DYNAMIC(WinTabPressurePen);

public:
	WinTabPressurePen();
	~WinTabPressurePen();

protected:		// Upcalls to derived classes. If they don't handle this they should call the base class
	virtual BOOL ReadTabletPressureData(void);
	virtual void StartStroke(void);
	virtual void EndStroke(void);


protected:
	void InitPressure(void);
			// Works out how to get pressure information from the tablet, and initialises
			// scaling values, etc.


public:			// Special interfaces called by the MainFrame on WT_ messages
	void PenProximityChanged(BOOL LeavingTablet);


protected:		// Internal variables
	HCTX hTab;					// WinTab handle to the tablet

	UINT32 wActiveCsr;			// Old and current cursors
	UINT32 wOldCsr;

	BYTE wPrsBtn;				// Indicates which data channel is the pressure "button"

	UINT32 ClickThreshold;		// Pressure value at which the pen is considered to be "clicked"

	BOOL PenNotOnTablet;		// Proximity flag - TRUE when Pen is not in use
};


#endif

