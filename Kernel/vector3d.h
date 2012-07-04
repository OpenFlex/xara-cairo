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


#ifndef INC_VEC3D
#define INC_VEC3D

#include <math.h>

/********************************************************************************************

>	class Vector3D 

	Author: 	Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/08/94
	Purpose:	Define all 3 vector operations we need.

********************************************************************************************/

class Vector3D 
{
	public:
		Vector3D()			{ x=y=z=0; }
		Vector3D(double p)	{ x=y=z=p; }
		Vector3D(double px, double py, double pz) { x=px; y=py; z=pz; }
		Vector3D(const Vector3D& v) { x=v.x; y=v.y; z=v.z; }

		inline Vector3D operator+(const Vector3D& V) const { return Vector3D(x+V.x, y+V.y, z+V.z); }
		inline Vector3D operator-(const Vector3D& V) const { return Vector3D(x-V.x, y-V.y, z-V.z); }
		inline Vector3D operator*(const Vector3D& V) const { return Vector3D(x*V.x, y*V.y, z*V.z); }
		inline Vector3D operator/(const Vector3D& V) const { return Vector3D(x/V.x, y/V.y, z/V.z); }
	
		inline Vector3D operator+(const double& V) const { return Vector3D(x+V, y+V, z+V); }
		inline Vector3D operator-(const double& V) const { return Vector3D(x-V, y-V, z-V); }
		inline Vector3D operator*(const double& V) const { return Vector3D(x*V, y*V, z*V); }
		inline Vector3D operator/(const double& V) const { return Vector3D(x/V, y/V, z/V); }

		inline Vector3D operator+() const { return Vector3D(+x, +y, +z); }
		inline Vector3D operator-() const { return Vector3D(-x, -y, -z); }

		inline BOOL operator==(const Vector3D& V) { return x==V.x && y==V.y && z==V.z; }
		inline BOOL	operator!=(const Vector3D& V) { return x!=V.x || y!=V.y || z!=V.z; }
		
		inline Vector3D& operator+=(const Vector3D& V);
		inline Vector3D& operator-=(const Vector3D& V);
		inline Vector3D& operator*=(const Vector3D& V);

		inline double xcomp() const { return x; }
		inline double ycomp() const { return y; }
		inline double zcomp() const { return z; }

		inline double Length()						const { return ( sqrt(x*x + y*y + z*z) ); }
		inline double SumSquares()					const { return ( x*x + y*y + z*z ); }
		inline double Dot(const Vector3D& p)		const { return ( x*p.x + y*p.y + z*p.z ); }
		inline double SumMult(const Vector3D& p)	const { return ( x*p.x + y*p.y + z*p.z); }
		inline double SqrDist(const Vector3D& p)	const { return (p.x-x)*(p.x-x) + (p.y-y)*(p.y-y) + (p.z-z)*(p.z-z); }
		inline double DistanceTo(const Vector3D& p) const { return sqrt(SqrDist(p)); }

		inline Vector3D Mix(const Vector3D &mix, double t) const;

		void		FaceForward(const Vector3D& p);
		double		Normalise();
		Vector3D	NormaliseI();
		Vector3D	Cross(const Vector3D& q) const;

		//Vector3D	TransformP(const Matrix3D& mat) const;
		//Vector3D	TransformN(const Matrix3D& mat) const;
		//Vector3D	TransformD(const Matrix3D& mat) const;

		static Vector3D Half(const Vector3D&, const Vector3D&);
		static Vector3D TorusUV(double srad, double trad, double u, double v);

	public:
		double x; 
		double y; 
		double z; 
};




/********************************************************************************************

********************************************************************************************/

inline Vector3D& Vector3D::operator+=(const Vector3D& p)
{
	x += p.x;
	y += p.y;
	z += p.z;
	return *this;
}

inline Vector3D& Vector3D::operator-=(const Vector3D& p)
{
	x -= p.x;
	y -= p.y;
	z -= p.z;
	return *this;
}

inline Vector3D& Vector3D::operator*=(const Vector3D& p)
{
	x *= p.x;
	y *= p.y;
	z *= p.z;
	return *this;
}

inline Vector3D Vector3D::Mix(const Vector3D &mix, double t) const
{
	Vector3D v;
	v.x = (1.0-t)*x + t*mix.x;
	v.y = (1.0-t)*y + t*mix.y;
	v.z = (1.0-t)*z + t*mix.z;
	return v;
}

#endif
