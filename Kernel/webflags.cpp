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
#include "webflags.h"


DECLARE_SOURCE("$Revision: 1282 $");

CC_IMPLEMENT_DYNAMIC(WebCorrectFlags, CCObject);

/**********************************************************************************************

>	WebCorrectFlags::WebCorrectFlags(const WebCorrectFlags& wcfNew)

	Author: 	Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/9/96
	Inputs:		wcfNew
	Outputs:	None
	Returns:	None
	Purpose:	Copy Constructor for the WebCorrectFlags class
	Errors:		None

**********************************************************************************************/

WebCorrectFlags::WebCorrectFlags(const WebCorrectFlags& wcfNew)
{
	m_fBackslashes=wcfNew.m_fBackslashes;
	m_fLocalFilenames=wcfNew.m_fLocalFilenames;
	m_fNetscapeFilenames=wcfNew.m_fNetscapeFilenames;
	m_fFTP=wcfNew.m_fFTP;
	m_fHTTP=wcfNew.m_fHTTP;
	m_fMailto=wcfNew.m_fMailto;
	m_fNoSlash=wcfNew.m_fNoSlash;
	m_fNoNetLoc=wcfNew.m_fNoNetLoc;
}

/**********************************************************************************************

>	WebCorrectFlags& WebCorrectFlags::operator=(const WebCorrectFlags&)

	Author: 	Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/9/96
	Inputs:		wcfNew
	Outputs:	None
	Returns:	None
	Purpose:	Assignment operator
	Errors:		None

**********************************************************************************************/

WebCorrectFlags& WebCorrectFlags::operator=(const WebCorrectFlags& wcfNew)	
{
	m_fBackslashes=wcfNew.m_fBackslashes;
	m_fLocalFilenames=wcfNew.m_fLocalFilenames;
	m_fNetscapeFilenames=wcfNew.m_fNetscapeFilenames;
	m_fFTP=wcfNew.m_fFTP;
	m_fHTTP=wcfNew.m_fHTTP;
	m_fMailto=wcfNew.m_fMailto;
	m_fNoSlash=wcfNew.m_fNoSlash;
	m_fNoNetLoc=wcfNew.m_fNoNetLoc;

	return *this;
}

/**********************************************************************************************

>	WebCorrectFlags::~WebCorrectFlags()	

	Author: 	Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/9/96
	Inputs:		-
	Outputs:	None
	Returns:	None
	Purpose:	Destructor
	Errors:		None

**********************************************************************************************/

WebCorrectFlags::~WebCorrectFlags()	
{
	//Does nothing at the moment
}




