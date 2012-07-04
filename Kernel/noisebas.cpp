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
#include "vector3d.h"
#include "noisebas.h"
#include "noise1.h"


/**************************************************************************************

BOOL NoiseMan::Construct()

***************************************************************************************/

NoiseMan::NoiseMan()
{
	pNoise=NULL;
}

NoiseMan::~NoiseMan()
{
	Destroy();
}

BOOL NoiseMan::Initialise()
{
	if (pNoise==NULL)
	{
		NoiseGen1 *pNewNoise = new NoiseGen1;
		if (pNewNoise!=NULL)
		{
			if (!pNewNoise->Initialise())
			{
				delete pNewNoise;
				return FALSE;
			}
		}
		pNoise = pNewNoise;
	}
	return TRUE;
}


void NoiseMan::Destroy()
{
	if (pNoise!=NULL)
	{
		delete pNoise;
		pNoise=NULL;
	}
}

NoiseBase* NoiseMan::NoiseGen()
{
	return pNoise;
}


/**************************************************************************************

NoiseBase::NoiseBase()

***************************************************************************************/

NoiseBase::NoiseBase()
{
}

NoiseBase::~NoiseBase()
{
}

