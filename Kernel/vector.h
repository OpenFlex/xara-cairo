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

#ifndef INC_VECTOR
#define INC_VECTOR


/**************************************************************************************

>	class Vector3 : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/09/96
	Purpose:	Provides a 3D templated vector class
				Presently used as support for Path::IsIsometric()

**************************************************************************************/

template <class T>
class Vector3 : public CC_CLASS_MEMDUMP
{
	// Declare the class for memory tracking
//	CC_DECLARE_MEMDUMP(Vector3);

public:
	Vector3() {}
	Vector3(T a1, T a2, T a3) : v0(a1), v1(a2), v2(a3) {}

	T	v0;
	T	v1;
	T	v2;
#ifdef _DEBUG
//	friend ostream& operator << (ostream& os, Vector3<T>& v);
#endif
};



typedef Vector3<double> CCVector3;

#endif
