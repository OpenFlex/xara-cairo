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

/*
	
*/

#ifndef INC__CAMSTRING
#define INC__CAMSTRING

// The base class variable-length Strings.
#include "basestr.h"

// Various sizes of fixed-length Strings, created by "template".
#include "fixstr8.h"
#include "fixstr16.h"
#include "fixstr32.h"
#include "fixstr64.h"
#include "fixst128.h"
#include "fixst256.h"

// The new self-sizing variable-length String
#include "varstr.h"

// If compiling under the 16-bit Microsoft compiler then use a pre-processor #define
// as typedef doesn't work properly. And also the 32-bit compiler.
#define String String_32

#endif	// INC__STRING
