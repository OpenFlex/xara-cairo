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

// trans.h: This defines the class for handling transformations

#ifndef TRANS_H
#define TRANS_H

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/list.h"

// XAR handling library
#include "xarlib/xarlib.h"

// for PointD
#include "utils.h"

/***************************************************************************************************

>	struct Transformation

	Author:		Sandro Sigala <sandro@sigala.it>
	Created:	20 July 2006
	Purpose:	Contains transformation matrix and applies SVG transformations to coordinates.

***************************************************************************************************/

struct Transformation {
	Transformation() {
		// default is an identity matrix
		data[0] = 1.0; // x scale
		data[1] = 0.0;
		data[2] = 0.0;
		data[3] = 0.0;
		data[4] = 1.0; // y scale
		data[5] = 0.0;
	}
	// copy constructor
	Transformation(const Transformation& copy) {
		*this = copy;
	}

	// copy operator
	Transformation& operator =(const Transformation& copy) {
		memcpy(data, copy.data, sizeof(double)*6);
		size = copy.size;
		return *this;
	}

	Transformation& operator *=(const Transformation& t);

	// is the tranformation only composed by translation and scale?
	bool IsSimpleTransformation() const {
		// check items a12 & a21
		return data[1] == 0.0 && data[3] == 0.0;
	}

	void ApplyToCoordinate(double x, double y, double* pRX, double* pRY) const;
	void ApplyToMeasure(double x, double* pX) const;
	
	static Transformation CreateTranslate(double x, double y);
	static Transformation CreateScale(double x, double y);
	static Transformation CreateRotate(double a);
	static Transformation CreateSkewX(double a);
	static Transformation CreateSkewY(double a);
	static Transformation CreateMatrix(double d[6]);

	// 3x3 matrix simplified to 6 elements vector
	// (line 3 of matrix is always [0 0 1])
	double data[6];

	// width and height of the parent object
	PointD size;
};

WX_DECLARE_LIST(Transformation, TransformationList);

Transformation ParseTransformations(const wxString& s, bool bScaleToMillipoints);
Transformation ParseTransformations(xmlNodePtr cur, const char* prop, bool bScaleToMillipoints);

#if SVGDEBUG
void DebugDumpTransformation(int lvl, const Transformation& trans);
#endif

#endif // !TRANS_H
