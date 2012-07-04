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

#include "camplatform.h"

IMPLEMENT_DYNAMIC_CLASS(CamPlatformDependent, wxPlatformDependent);

/********************************************************************************************

>	void CamPlatformDependent::Initialise()


	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	07/06/2005
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if succeeded, FALSE if fails
	Purpose:	Initialize platform dependent stuff
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void CamPlatformDependent::Initialise()
{
#if defined( __WXGTK__ )
	ParseGtkRcString("\n"
                     "       style \"gtk-scale-blip-style\"\n"
                     "       {\n"
                     "               GtkScale::slider-length=13\n"
                     "       }\n"
                     "\n"
                     "       widget_class \"*.GtkHScale\" style \"gtk-scale-blip-style\"\n"
                     "       widget_class \"*.GtkVScale\" style \"gtk-scale-blip-style\"\n"
                     "\n");
#endif
}

/********************************************************************************************

>	void CamPlatformDependent::InitWindow(wxWindow * pwxWindow)


	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	07/06/2005
	Inputs:		None
	Outputs:	None
	Returns:	TRUE if succeeded, FALSE if fails
	Purpose:	Set up a wxWindow
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

void CamPlatformDependent::InitWindow(wxWindow * pwxWindow)
{
#if defined( __WXGTK__ )
	// Set the GTK Widget name to the object name
	const TCHAR * ObjectName = CamResource::GetObjectNameFail(pwxWindow->GetId());
	if (ObjectName)
	{
		wxString WindowIDName(ObjectName);
		SetGtkWidgetName(pwxWindow, (char *)(const char *)(WindowIDName.mb_str(wxConvUTF8)));
	}
#endif
}
