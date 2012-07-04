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


#ifndef INC_MACROS
#define INC_MACROS

#include <math.h>

#define _Long(x)  ((INT32)(x))
#define _Int(x)   ((INT32)(x))
#define _Float(x) ((FLOAT)(x))
#define _Dble(x)  ((double)(x))

double const XS_2PI			=  6.28318530717958623200;
double const XS_DEGTORAD	=  0.01745329251994329547;
double const XS_E 			=  2.71828182845904553488;
double const XS_EEXPPI 		= 23.14069263277927390732;
double const XS_GOLDEN 		=  1.61803398874989490253;
double const XS_INVPI 		=  0.31830988618379069122;
double const XS_LN10 		=  2.30258509299404590109;
double const XS_LN2			=  0.69314718055994528623;
double const XS_LOG10E		=  0.43429448190325187218;
double const XS_LOG2E		=  1.44269504088896338700;
double const XS_LOG05		= -0.693147180559945;
double const XS_PI			=  3.14159265358979323846;
double const XS_PIDIV2		=  1.57079632679489655800;
double const XS_PIDIV4		=  0.78539816339744827900;
double const XS_RADTODEG	= 57.29577951308232286465;
double const XS_SQRT2		=  1.41421356237309514547;
double const XS_SQRT2PI		=  2.50662827463100024161;
double const XS_SQRT3		=  1.73205080756887719318;
double const XS_SQRT10		=  3.16227766016837952279;
double const XS_SQRTE		=  1.64872127070012819416;
double const XS_SQRTHALF	=  0.70710678118654757274;
double const XS_SQRTLN2		=  0.83255461115769768821;
double const XS_SQRTPI		=  1.77245385090551588192;
double const XS_EPSILON		=  1.0e-10;
double const XS_GOOGOL		=  1.0e50;


//***************************************************************************************
// ONE ARGUMENT UTILITY FUNCTIONS - INT32 VERSIONS
//***************************************************************************************

inline INT32 LClamp(INT32 x, INT32 min, INT32 max)
{
	return (x < min ? min : (x > max ? max : x));
}
	
inline INT32 LAbs(INT32 x)
{
	return (x >= 0) ? x : -x;
}

inline INT32 LSign(INT32 x)
{
	return (x < 0) ? -1 : 1;
}

inline INT32 LSmooth(INT32 x)
{
	return (3 - 2 * x) * x * x;
}


//***************************************************************************************
// TWO-ARGUMENT UTILITY FUNCTIONS - INT32 VERSIONS
//***************************************************************************************

inline INT32 LMin(INT32 x, INT32 y)
{
	return (x < y) ? x : y;
}

inline INT32 LMax(INT32 x, INT32 y)
{
	return (x > y) ? x : y;
}


//***************************************************************************************
// THREE-ARGUMENT UTILITY FUNCTIONS - INT32 VERSIONS
//***************************************************************************************

inline INT32 LMin(INT32 x, INT32 y, INT32 z)
{
	return (x < y) ? LMin(x, z) : LMin(y, z);
}

inline INT32 LMax(INT32 x, INT32 y, INT32 z)
{
	return (x > y) ? LMax(x, z) : LMax(y, z);
}



//***************************************************************************************
// ONE ARGUMENT UTILITY FUNCTIONS - FLOAT VERSIONS
//***************************************************************************************

inline float FClamp(float x)
{
	return (x < 0.0f ? 0.0f : (x > 1.0f ? 1.0f : x));
}
	
inline float FAbs(float x)
{
	return (x >= 0.0f) ? x : -x;
}

inline float FFrac(float x)
{
	return (x-((INT32)(x)));
}

inline float FCeil(float x)
{
	return (x == _Int(x)) ? x : (x > 0.0f) ? _Float(_Int(x) + 1.0f) : _Float(_Int(x));
}

inline float FFloor(float x)
{
	return (x == _Int(x)) ? x : (x > 0.0f) ? _Float(_Int(x)) : _Float(_Int(x) - 1.0f);
}

inline float FRound(float x)
{
	return (x >= 0.0f) ? _Float(_Int(x + 0.5f)) : _Float(- _Int(0.5f - x));
}

inline float FSign(float x)
{
	return (x < 0.0f) ? -1.0f : 1.0f;
}

inline float FSmooth(float x)
{
	return (3.0f - 2.0f * x) * x * x;
}

inline float FTrunc(float x)
{
	return _Float(_Int(x));
}


//***************************************************************************************
// TWO-ARGUMENT UTILITY FUNCTIONS - FLOAT VERSIONS
//***************************************************************************************

inline float FMin(float x, float y)
{
	return (x < y) ? x : y;
}

inline float FMax(float x, float y)
{
	return (x > y) ? x : y;
}


//***************************************************************************************
// THREE-ARGUMENT UTILITY FUNCTIONS - FLOAT VERSIONS
//***************************************************************************************

inline float FMax(float x, float y, float z)
{
	return (x > y) ? FMax(x, z) : FMax(y, z);
}

inline float FMin(float x, float y, float z)
{
	return (x < y) ? FMin(x, z) : FMin(y, z);
}








//***************************************************************************************
// ONE ARGUMENT UTILITY FUNCTIONS - DOUBLE VERSIONS
//***************************************************************************************

inline double DAbs(double f)
{
	return (f >= 0) ? f : -f;
}

inline double DFrac(double f)
{
	return (f-_Long(f));
}

inline double DCeil(double f)
{
	return (f == _Int(f)) ? f : (f > 0) ? _Dble(_Int(f) + 1) : _Dble(_Int(f));
}

inline double DCube(double f)
{
	return f * f * f;
}

inline double DDegrees(double f)
{
	return f * XS_RADTODEG;
}

inline double DFloor(double f)
{
	return (f == _Int(f)) ? f : (f > 0) ? _Dble(_Int(f)) : _Dble(_Int(f)-1);
}

inline double DInv(double f)
{
	return 1.0 / f;
}

inline BOOL DIsZero(double f)
{
	return ((f<=0.0) ? (f >= -XS_EPSILON) : (f <= XS_EPSILON));
}

inline double DRadians(double f)
{
	return f * XS_DEGTORAD;
}

inline double DRound(double f)
{
	return (f >= 0) ? _Dble(_Int(f + 0.5)) : _Dble(- _Int(0.5 - f));
}

inline double DSign(double f)
{
	return (f < 0) ? -1.0 : 1.0;
}

inline double DSmooth(double f)
{
	return (3.0 - 2.0 * f) * f * f;
}

inline double DTrunc(double f)
{
	return _Dble(_Int(f));
}

inline double DZSign(double f)
{
	return (f > 0) ? 1.0 : (f < 0) ? -1.0 : 0.0;
}

inline double DCubeRoot(double x)
{
	return (x>0.0) ? pow(x, 1.0/3.0) : (x<0.0) ? -pow(-x, 1.0/3.0) : 0.0;
}



//***************************************************************************************
// TWO-ARGUMENT UTILITY FUNCTIONS - DOUBLE VERSIONS
//***************************************************************************************

inline BOOL DFuzEQ(double f, double g)
{
	return (f <= g) ? (f >= g - XS_EPSILON) : (f <= g + XS_EPSILON);
}

inline BOOL DFuzGEQ(double f, double g)
{
	return (f >= g - XS_EPSILON);
}

inline BOOL DFuzLEQ(double f, double g)
{
	return (f <= g + XS_EPSILON);
}

inline double DMax(double f, double g)
{
	return (f > g) ? f : g;
}

inline double DMin(double f, double g)
{
	return (f < g) ? f : g;
}

inline void DSwap(double& f, double& g)
{
	double gmTmp = f; f = g; g = gmTmp;
}

inline void DSwap(INT32& i, INT32& j)
{
	INT32 gmTmp = i; i = j; j = gmTmp;
}

inline void DSort(double& lo, double& hi)
{
	if (lo>hi) DSwap(lo,hi);
}

inline double DStep(double a, double f)
{
	return _Dble(f>=a);
}

inline double DFuzStep(double a, double f, double fzz)
{
	return _Dble(f>=(a+fzz));
}

inline double DGamma(double gamma, double f)
{
	return (gamma==0.0) ? XS_GOOGOL : pow(f, 1/gamma);
}

inline double DBias(double bias, double f)
{
	return pow(f,log(bias)/log(0.5));
}

inline double DGain(double gain, double f)
{
	return (f<0.5) ? (DBias(1.0-gain,2.0*f)/2.0) : (1-DBias(1.0-gain, 2.0-2.0*f)/2.0);
}

inline double DExculsiveOr(double a, double b)
{
	return (a + b - a * b);
}

inline double DIntersection(double a, double b)
{
	return (a * b);
}

inline double DDifference(double a, double b)
{
	return (a - a * b);
}

inline double DRepeat(double u, double freq)
{
	// return distance into tile
	return DFrac(u*freq);
}

inline double DTile(double u, double freq)
{
	// return the tile number
	return _Long(u*freq);
}



//***************************************************************************************
// MULTI-ARGUMENT UTILITY FUNCTIONS	- DOUBLE VERSIONS
//***************************************************************************************

inline double DClamp(const double x, const double a, const double b)
{
	return (x < a ? a : (x > b ? b : x));
}

inline double DLerp(double f, double l, double h)
{
	return l + ((h - l) * f );
}

inline double DNorm(double f, double a, double b)
{
	return (f-a)/(b-a);
}

inline double DMax(double f, double g, double h)
{
	return (f > g) ? DMax(f, h) : DMax(g, h);
}

inline double DMin(double f, double g, double h)
{
	return (f < g) ? DMin(f, h) : DMin(g, h);
}

inline double DSlide(double f, double l, double h)
{
	return (f < 0) ? l : (f > 1) ? h : DLerp(DSmooth(f), l, h);
}

inline double DSmoothStep(double a, double b, double f)
{
	return (f < a) ? 0.0 : (f > b) ? 1.0 : DSmooth(DNorm(f,a,b));
}

inline double DBoxStep(double a, double b, double x)
{
	return (DClamp((x-a)/(b-a),0,1));
}

inline double DPulse(double a, double b, double x)
{
	return (DStep(a,x) - DStep(b,x));
}

inline double DFuzPulse(double a, double b, double x, double fzz)
{
	return (DFuzStep(a,x,-fzz) - DFuzStep(b,x,+fzz));
}

inline double DRange(double t,
					   double min, double max, 
					   double lo, double mid, double hi)
{
	return (t<min) ? lo : ((t>max) ? hi : mid);
}


#endif
