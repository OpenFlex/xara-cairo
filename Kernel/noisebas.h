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


#ifndef INC_NOISEBASE
#define INC_NOISEBASE

#define NOISE1D(v,s) NoiseGen()->VNoise1D(v,s)
#define NOISE2D(v) NoiseGen()->VNoise2D(v)
#define NOISE3D(v) NoiseGen()->VNoise3D(v)
#define SEEDTABLE(v) NoiseGen()->SeedTable(v)

#include "vector3d.h"

/**************************************************************************************

>	class NoiseBase

	Aurthor:	Mike
	Created:	07/07/96
	Notes:		The base class noise function generator. There are several derived
				classes from this which generate different forms of noise. Each of
				these classes 

***************************************************************************************/

class NoiseBase
{
	friend class NoiseMan;

	public:
		NoiseBase();
		virtual ~NoiseBase();

	// you should write your own versions of these noise functions
	// in your derived noise class.
		
		virtual BOOL	 Initialise()=0;
		virtual double   VNoise1D(const Vector3D &v, double s)=0;
	//	virtual POINT    VNoise2D(const Vector3D &v)=0;
		virtual Vector3D VNoise3D(const Vector3D &v)=0;
		virtual void	 SeedTable(UINT32 seed)=0;

	// the following function make full use of the above
	// noise generators, however the derived creates its noise.
};


/**************************************************************************************

>	class NoiseMan

	Aurthor:	Mike
	Created:	07/07/96
	Notes:		The class which builds a version of noisebase.

***************************************************************************************/

class NoiseMan
{
	public:
		 NoiseMan();
		~NoiseMan();

		BOOL Initialise();
		void Destroy();

		NoiseBase* NoiseGen();

	private:
		NoiseBase* pNoise;
};


#endif
