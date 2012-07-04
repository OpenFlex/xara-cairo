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
#include "macros.h"
#include "vector3d.h"


void Vector3D::FaceForward(const Vector3D& q)
{
	if (Dot(q)<0.0) return;
	x = -x;
	y = -y;
	z = -z;
}


double Vector3D::Normalise()
{
	double l,m;
	l = sqrt(x*x + y*y + z*z);
	if (l!=0) 
  	{	
  		m=1.0/l;
		x*=m; 
		y*=m; 
		z*=m;
  	}
	else
	{	
		x=1.0;
		y=0;
		z=0;
	};

	return l;
}

Vector3D Vector3D::NormaliseI()
{
	double l,m;
	l = sqrt(x*x + y*y + z*z);
	if (l!=0) 
  	{	
  		m=1.0/l;
		x*=m; 
		y*=m; 
		z*=m;
  	}
	else
	{	
		x=0;
		y=0;
		z=0;
	};

	return *this;
}

Vector3D Vector3D::Half(const Vector3D& p,const Vector3D& q)
{ 
	return ((p+q).NormaliseI());
}


Vector3D Vector3D::Cross(const Vector3D& q) const
{ 
   Vector3D r;
   r.x = y*q.z - z*q.y;
   r.y = z*q.x - x*q.z;
   r.z = x*q.y - y*q.x;
   return r;
}


Vector3D Vector3D::TorusUV(double srad, double trad, double u, double v)
{
	Vector3D p;
	double theta,phi;

	theta = XS_2PI*u;
	  phi = XS_2PI*v;

	p.x = srad + trad*cos(theta);
	p.y =		 trad*sin(theta);

	p.z = p.x*sin(phi);
	p.x = p.x*cos(phi);

	// translate into the positive octant
	p.x += srad+trad;
	p.y += trad;
	p.z += srad+trad;

	return p;
}
