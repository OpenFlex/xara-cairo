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


/////////////////////////////////////////////////////////////////////////////////////////////
//
//							Static table of GLA derived classes
//
/////////////////////////////////////////////////////////////////////////////////////////////


#ifndef GLA_TABLE 
#define GLA_TABLE
// GLA runtime class predeclarations
#include "fthrattr.h"

const INT32 NumGLAs = 1;
const CCRuntimeClass* GeometryLinkedAttributeClasses[] = { 
							CC_RUNTIME_CLASS(AttrFeather)
							// Add new GLA runtime classes here
							// Remember to increment NumGLAs above
							};

#endif // GLA_TABLE
