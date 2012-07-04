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


#ifndef INC_CAMPLATFORM
#define	INC_CAMPLATFORM


/*******************************************************************************************

>	class CamPlatformDependent : public wxPlatformDependent

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	7/05/2006
	Purpose:	A derived clas for implementing wx-platform depedent Oil activity
	Notes:		In the OIL
	See Also:	

********************************************************************************************/

class CamPlatformDependent : public wxPlatformDependent
{
protected:
	virtual void Initialise();

public:
	virtual void InitWindow(wxWindow * pwxWindow);

DECLARE_DYNAMIC_CLASS(wxPlatformDependent);

};

#endif

