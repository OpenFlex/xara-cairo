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


#ifndef INC_COLOURMAT
#define	INC_COLOURMAT

class ColourMatrix;


class ColourVector : public SimpleCCObject
{
public:
	double elements[5];

	enum ColourVectorElement
	{
		Red		= 0,
		Green 	= 1,
		Blue 	= 2,
		Alpha	= 3,
		Spare	= 4
	};

	ColourVector(double r=0.0, double g=0.0, double b=0.0, double a=1.0, double s=1.0)
	{	
		elements[Red]=r;
		elements[Green]=g;
		elements[Blue]=b;
		elements[Alpha]=a;
		elements[Spare]=s;
	}

	void SetRGBA(UINT32 r, UINT32 g, UINT32 b, UINT32 a=255)
	{
		elements[Red]   = ((double)r)/255.0;
		elements[Green] = ((double)g)/255.0;
		elements[Blue]  = ((double)b)/255.0;
		elements[Alpha] = ((double)a)/255.0;
	}

	static UINT32 Get(double v)
	{
		if (v<0) return 0;
		UINT32 x = (UINT32)(v*255.0+0.5);
		return (x>255)?255:x;
	}

	UINT32 GetR() {return Get(elements[Red]);}
	UINT32 GetG() {return Get(elements[Green]);}
	UINT32 GetB() {return Get(elements[Blue]);}
	UINT32 GetA (){return Get(elements[Alpha]);}

	ColourVector Apply(ColourMatrix &cm);

	ColourVector ComposeOnTop(ColourVector &v)
	{
		// Check if either is transparent
		if (elements[Alpha]==0.0) return v;
		if (v.elements[Alpha]==0.0) return *this;

		// Generate the new alpha value
		double newalpha = v.elements[Alpha] + elements[Alpha] - v.elements[Alpha]*elements[Alpha];
		if (newalpha == 0.0) return ColourVector(elements[Red], elements[Green], elements[Blue], 0.0);

		/* Here's how this works:
			on a normal composition, of (x1,a1), x= x0 * (1-a1) + x1 * a1
			So where (x2,a2) are imposed on top, x = ( x1 * a1 + x0 * (1-a1) ) * (1-a2) + x2 * a2;
			Which can be rewritten as
				x = x0 ( 1- (a1+a2-a1a2) ) + ( a1+a2-a1a2 )/(a1+a2-a1a2)*((1-a2)(x1a1)+x2a2)
			Substituting A = (a1+a2-a2a2), X=((1-a2)(x1a1)+x2a2)/A we get
				x = x0 (1-A) + X A
			Which is the formula for transparency with alpha A, colour X
		*/

		return ColourVector(
				((1-v.elements[Alpha])*(elements[Alpha]*elements[Red]  ) + (v.elements[Red]   * v.elements[Alpha])) / newalpha,
				((1-v.elements[Alpha])*(elements[Alpha]*elements[Green]) + (v.elements[Green] * v.elements[Alpha])) / newalpha,
				((1-v.elements[Alpha])*(elements[Alpha]*elements[Blue] ) + (v.elements[Blue]  * v.elements[Alpha])) / newalpha,
				newalpha);
	}
};

class ColourMatrix : public SimpleCCObject
{
public:
	typedef struct {double el[5*5];} elements_t;

	elements_t elements;

	ColourMatrix()
	{
		INT32 i,j;
		for (i = 0; i<5; i++) for (j=0 ; j<5; j++) elements.el[i+j*5]=(i==j)?1.0:0.0;
	}

	static ColourMatrix Boost(double d=1.2);
	static ColourMatrix Whiten();
	static ColourMatrix Grey();
};



#endif

