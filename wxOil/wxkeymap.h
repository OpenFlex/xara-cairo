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

#ifndef WXOIL_WXKEYMAP
#define WXOIL_WXKEYMAP

#include <map>
#include "fixstr32.h"

/********************************************************************************************

	class: wxKeyMap
	Author: Jason_Williams (Xara Group Ltd) <camelotdev@xara.com> M'Sadoques
	Created: 28/05/2007
	Purpose: Maps the string representation of a wx key (i.e. "WXK_F1"), into it's enum value.

********************************************************************************************/
class wxKeyMap
{
	static std::map<String_32, UINT32> keymap;
	static void GenerateMap();
	public:
		static UINT32 GetKeyVal(String_32);
};

#endif
