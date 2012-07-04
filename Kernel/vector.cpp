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

// 


#include "camtypes.h"
#include "vector.h"

// Place any IMPLEMENT type statements here
//CC_IMPLEMENT_MEMDUMP(CCVector3, CC_CLASS_MEMDUMP)


// We want better memory tracking
#define new CAM_DEBUG_NEW

using namespace std;

// Functions follow

#ifdef _DEBUG
template <class T>
ostream& operator << (ostream& os, Vector3<T>& v)
{
	os << "(" << v.v0 << "," << v.v1 << "," << v.v2 << ")\n";
	return os;
}
#endif
