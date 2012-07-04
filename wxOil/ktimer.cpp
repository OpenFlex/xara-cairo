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



#include "camtypes.h"

#include "ktimer.h"

CC_IMPLEMENT_DYNAMIC(KernelTimer, CCObject);
CC_IMPLEMENT_DYNAMIC(TimerMsg, Msg);

// Note all the implementation is in the .h file, so this is really just IMPLEMENT_DYNAMIC and some
// documentation

/********************************************************************************************

>	KernelTimer::KernelTimer(CCRuntimeClass * BroadcastClass = NULL)

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	25/04/2005
	Inputs:		BroadcastClass - the class to broadcast to, or NULL for all
	Outputs:	None
	Returns:	-
	Purpose:	Constructor
	Errors:		-
	SeeAlso:	-

Use BroadcastClass to restrict the amount of broadcast traffic, e.g.
	KernelTimer MyTimer(CC_RUNTIME_CLASS(DialogOp));

********************************************************************************************/

/********************************************************************************************

>	void KernelTimer::SetBroadcastClass (CCRuntimeClass * BroadcastClass)

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	25/04/2005
	Inputs:		BroadcastClass - the class to broadcast to, or NULL for all
	Outputs:	None
	Returns:	-
	Purpose:	Change the broadcast class
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

/********************************************************************************************

>	CCRuntimeClass * KernelTimer::GetBroadcastClass () const

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	25/04/2005
	Inputs:		None
	Outputs:	None
	Returns:	The current broadcast class
	Purpose:	Return the current broadcast class
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

/********************************************************************************************

>	virtual void KernelTimer::Notify()

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	25/04/2005
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Called when a timer event occurs
	Errors:		-
	SeeAlso:	-

This function by default broadcasts a TimerMsg::Notify to all message handlers (or
to the subset set up in the constructor or KernelTimer::SetBroadcast). It can be
overridden to do something else (or something additional).

********************************************************************************************/

/********************************************************************************************

>	virtual void KernelTimer::GetInterval()

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	25/04/2005
	Inputs:		None
	Outputs:	None
	Returns:	Current interval
	Purpose:	Returns the current interval that has been set
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

/********************************************************************************************

>	BOOL KernelTimer::IsOneShost() const

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	25/04/2005
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if the timer is one shot, FALSE if the timer repeats
	Purpose:	-
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

/********************************************************************************************

>	BOOL KernelTimer::IsRunning() const

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	25/04/2005
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if the timer is running, FALSE otherwise
	Purpose:	-
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

/********************************************************************************************

>	BOOL KernelTimer::Start(INT32 milliseconds = -1, BOOL OneShot = FALSE)

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	25/04/2005
	Inputs:		milliseconds - number of ms until the next timer events (or between events)
							   or -1 to use the previous value
				OneShot - TRUE to make it a one shot rather than repeating timer
	Outputs:	None
	Returns:	TRUE if the timer was successfully started
	Purpose:	-
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

/********************************************************************************************

>	BOOL void KernelTimer::Stop()

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	25/04/2005
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if the timer was successfully stopped
	Purpose:	-
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

