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


#ifndef INC_NOISE1
#define INC_NOISE1

/**************************************************************************************

>	class NoiseGen1 : public NoiseBase

	Aurthor:	Mike
	Created:	07/07/96
	Notes:		

***************************************************************************************/

class NoiseGen1 : public NoiseBase
{
	public:
		NoiseGen1();
		virtual ~NoiseGen1();

		virtual BOOL	 Initialise();
		virtual double   VNoise1D(const Vector3D &v,double s);
	//	virtual RtCoord  VNoise2D(const Vector3D &v);
		virtual Vector3D VNoise3D(const Vector3D &v);
		virtual void	 SeedTable(UINT32 seed);
	
	private:
		float*	RTable;
};


#endif
