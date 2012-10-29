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


// Support for Graphics Tablets with Pressure Sensitive Pens

// WEBSTER - markn 25/4/97
// No pen stuff required in Webster
#ifdef WEBSTER
#define	INC_PEN
#endif // WEBSTER

#ifndef INC_PEN
#define	INC_PEN


#define MAXPRESSURE 1023
#define JOYMAX 65536

typedef enum
{
	PressureMode_None,			// Pressure not being recorded (always returns max pressure)
	PressureMode_Pen,			// Pressure is recorded from a real pressure pen
	PressureMode_Speed,			// Pressure is simulated from mouse speed
	PressureMode_Direction,		// Pressure is simulated from mouse direction

	PressureMode_MaxEnum		// Placeholder so we know how many modes there are
} PressureMode;


/********************************************************************************************

>	class CCPen : public CCObject

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/5/94
	Purpose:	This provides support for Pressure Sensitive Pen devices.
 				Its job is to keep track of the current pressure of a pen.
				It will automatically mutate itself into either a Real or Pretend pen,
				depending on what is availble when it is created.
				If it is a real pen, then it gets it's pressure from mouse messages.
				If it is a pretend pen, then the pressure is adjusted using either the
				keyboard (temporarily Keypad +/-) or by using a joystick.

********************************************************************************************/

class CCPen : public CCObject
{
	CC_DECLARE_DYNAMIC(CCPen);

public:
	CCPen();				// Don't construct one. Use GetApplication()->GetPressurePen() instead.
	~CCPen();

	// Initialisation function
	static CCPen *Init();

public:		// General Info about the Pen
 	BOOL IsRealPen()		{ return PressureAvailable; }
 	BOOL IsPressureOn()		{ return DefaultPressureMode != PressureMode_None; }
 	UINT32 GetPenPressure()	{ return PenPressure; }
	UINT32 GetPressureMax()	{ return PressureMax; }


public:		// Pen control interfaces
	// Switch the pressure on or off
	void SetPressureMode(PressureMode NewMode)	{ CurrentPressureMode = DefaultPressureMode = NewMode; }
	PressureMode GetPressureMode(void)			{ return(CurrentPressureMode); }

	// Function called by CCamView, when the Joystick moves
	void SetPressureFromJoystick(WPARAM, LPARAM);


public:		// Internal calls to update the pen when mouse events occur (see scrvw.cpp)
	virtual void CheckMouseMessage(UINT32 Message, wxPoint point);
			// Check for pen information whenever we get a mouse message

	virtual void StartStroke(void);
	virtual void EndStroke(void);
			// Called by pen-using tools when they start/end a drag operation
			// This allows the pen to be disabled while not in use, and also
			// lets us detect when the user swaps between their pen and mouse


protected:	// Upcalls to derived classes. If they don't handle this they should call the base class
	virtual BOOL ReadTabletPressureData(void);


protected:
	UINT32 PenPressure;				// Last "pressure" value we read/calculated
	UINT32 PressureMax;				// The maximum pressure value

	BOOL PF_IsPressureOn;			// Are we bothering with pressure data?

	BOOL PressureAvailable;			// Is this a real or pretend pen?
	PressureMode CurrentPressureMode;	// The type of pressure recording used for this stroke

PORTNOTE("other","Removed HWND usage")
#ifndef EXCLUDE_FROM_XARALX
	HWND hMainframeWnd;				// A handle to the camelot main frame window
#endif

	wxPoint LastMousePoint;			// Last recorded mouse position when faking pressure with mouse

public:
	static PressureMode DefaultPressureMode;
									// The type of pressure recording we'll do by default
};





/********************************************************************************************

>	class OpTogglePressure : public Operation

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/6/94
	Purpose:	This class represents the TogglePressure operation.
				Creating an instance of this class and calling its "Do" function will toggle
				the state of the flag controlling whether Pressure Information is stored 
				within paths.

********************************************************************************************/

#define OPTOKEN_TOGGLEPRESSURE TEXT("TogglePressure")

class OpTogglePressure: public Operation
{
	CC_DECLARE_DYNCREATE( OpTogglePressure )
	
public:
	OpTogglePressure();											// Constructor
	~OpTogglePressure();										// Destructor

	static BOOL		Init();										// Register an OpDescriptor
	void			Do(OpDescriptor*);							// "Do" function
	static OpState	GetState(String_256*, OpDescriptor*);		// Read the state of an operation
};

#endif 	// INC_PEN
