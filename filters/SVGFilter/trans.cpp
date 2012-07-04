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

// trans.cpp: This implements the class for handling transformations

#include "trans.h"

// define list of Transformation elements
#include <wx/listimpl.cpp>
WX_DEFINE_LIST(TransformationList);

Transformation& Transformation::operator *=(const Transformation& t)
{
	const double a11 = data[0];
	const double a12 = data[1];
	const double a13 = data[2];
	const double a21 = data[3];
	const double a22 = data[4];
	const double a23 = data[5];
	const double b11 = t.data[0];
	const double b12 = t.data[1];
	const double b13 = t.data[2];
	const double b21 = t.data[3];
	const double b22 = t.data[4];
	const double b23 = t.data[5];

#if SVGDEBUG
	svgtrace(DBGTRACE_TRANS, "original trans: ");
	DebugDumpTransformation(DBGTRACE_TRANS, *this);
	svgtrace(DBGTRACE_TRANS, "applying trans: ");
	DebugDumpTransformation(DBGTRACE_TRANS, t);
#endif

	data[0] = a11*b11 + a12*b21;
	data[1] = a11*b12 + a12*b22;
	data[2] = a11*b13 + a12*b23 + a13;
	data[3] = a21*b11 + a22*b21;
	data[4] = a21*b12 + a22*b22;
	data[5] = a21*b13 + a22*b23 + a23;

#if SVGDEBUG
	svgtrace(DBGTRACE_TRANS, "result: ");
	DebugDumpTransformation(DBGTRACE_TRANS, *this);
#endif

	return *this;
}

void Transformation::ApplyToCoordinate(double x, double y, double* pRX, double* pRY) const
{
	const double a11 = data[0];
	const double a12 = data[1];
	const double a13 = data[2];
	const double a21 = data[3];
	const double a22 = data[4];
	const double a23 = data[5];
	if (pRX) *pRX = a11*x + a12*y + a13;
	if (pRY) *pRY = a21*x + a22*y + a23;
}

void Transformation::ApplyToMeasure(double x, double* pRX) const
{
	const double a11 = data[0];
//	const double a12 = data[1];
//	const double a13 = data[2];
//	const double a21 = data[3];
//	const double a22 = data[4];
//	const double a23 = data[5];
	if (pRX) *pRX = a11*x; // + a12*y;
}

Transformation Transformation::CreateTranslate(double x, double y)
{
	Transformation trans;
	trans.data[2] = x;
	trans.data[5] = y;
	return trans;
}

Transformation Transformation::CreateScale(double x, double y)
{
	Transformation trans;
	trans.data[0] = x;
	trans.data[4] = y;
	return trans;
}

Transformation Transformation::CreateRotate(double a)
{
	Transformation trans;
	double sinA = sin(a);
	double cosA = cos(a);
	trans.data[0] = cosA;
	trans.data[1] = -sinA;
	trans.data[3] = sinA;
	trans.data[4] = cosA;
	return trans;
}

Transformation Transformation::CreateSkewX(double a)
{
	Transformation trans;
	trans.data[1] = tan(a);
	return trans;
}

Transformation Transformation::CreateSkewY(double a)
{
	Transformation trans;
	trans.data[3] = tan(a);
	return trans;
}

Transformation Transformation::CreateMatrix(double d[6])
{
	Transformation trans;
	trans.data[0] = d[0];
	trans.data[3] = d[1];
	trans.data[1] = d[2];
	trans.data[4] = d[3];
	trans.data[2] = d[4];
	trans.data[5] = d[5];
	return trans;
}

Transformation ParseTransformations(const wxString& sTrans, bool bScaleToMillipoints)
{
	wxString s = sTrans;
	Transformation trans;

	// replace commas with whitespace, if any
	s.Replace(_T(","), _T(" "));

	s = TrimWs(s);

	while (s.Length() > 0) {
		if (s.Left(10) == _T("translate(")) {
			double fX;
			double fY;

			s = s.Mid(10); // skip "translate("

			fX = TakeNumber(s);
			s = TrimWs(s);
			if (s.Left(1) == _T(")")) {
				fY = 0.0; // Y translation is implicit (equal to zero)
			} else {
				fY = TakeNumber(s);
			}
			s = s.Mid(1); // skip ")"

			if (bScaleToMillipoints) {
				fX *= 1000.0;
				fY *= 1000.0;
			}

#if SVGDEBUG
			svgtrace(DBGTRACE_TRANS, "creating translate matrix (%.4f, %.4f)\n", fX, fY);
#endif
			trans *= Transformation::CreateTranslate(fX, fY);
		} else if (s.Left(6) == _T("scale(")) {
			double fX;
			double fY;

			s = s.Mid(6); // skip "scale("

			fX = TakeNumber(s);
			s = TrimWs(s);
			if (s.Left(1) == _T(")")) {
				fY = fX; // Y scale is implicit (equal to X)
			} else {
				fY = TakeNumber(s);
			}
			s = s.Mid(1); // skip ")"
#if SVGDEBUG
			svgtrace(DBGTRACE_TRANS, "creating scale matrix (%.4f, %.4f)\n", fX, fY);
#endif
			trans *= Transformation::CreateScale(fX, fY);
		} else if (s.Left(7) == _T("rotate(")) {
			double fA;
			double fX = 0.0;
			double fY = 0.0;

			s = s.Mid(7); // skip "rotate("

			fA = deg2rad(TakeNumber(s));
			s = TrimWs(s);
			if (s.Left(1) != _T(")")) {
				// also rotation center is specified
				fX = TakeNumber(s);
				fY = TakeNumber(s);
			}
			s = s.Mid(1); // skip ")"

			if (fX != 0.0 || fY != 0.0) {
#if SVGDEBUG
				svgtrace(DBGTRACE_TRANS, "creating rotate/translate matrix %.4f (%.4f, %.4f)\n", fA, fX, fY);
#endif
				trans *= Transformation::CreateTranslate(fX, fY);
				trans *= Transformation::CreateRotate(fA);
				trans *= Transformation::CreateTranslate(-fX, -fY);
			} else {
#if SVGDEBUG
				svgtrace(DBGTRACE_TRANS, "creating rotate matrix (%.4f)\n", fA);
#endif
				trans *= Transformation::CreateRotate(fA);
			}
		} else if (s.Left(6) == _T("skewX(")) {
			double fA;

			s = s.Mid(6); // skip "skewX("

			fA = deg2rad(TakeNumber(s));
			s = TrimWs(s);
			s = s.Mid(1); // skip ")"
#if SVGDEBUG
			svgtrace(DBGTRACE_TRANS, "creating skewX matrix (%.4f)\n", fA);
#endif
			trans *= Transformation::CreateSkewX(fA);
		} else if (s.Left(6) == _T("skewY(")) {
			double fA;

			s = s.Mid(6); // skip "skewY("

			fA = deg2rad(TakeNumber(s));
			s = TrimWs(s);
			s = s.Mid(1); // skip ")"
#if SVGDEBUG
			svgtrace(DBGTRACE_TRANS, "creating skewY matrix (%.4f)\n", fA);
#endif
			trans *= Transformation::CreateSkewY(fA);
		} else if (s.Left(7) == _T("matrix(")) {
			double fX[6];

			s = s.Mid(7); // skip "matrix("

			for (int i = 0; i < 6; ++i)
				fX[i] = TakeNumber(s);
			s = TrimWs(s);
			s = s.Mid(1); // skip ")"

			if (bScaleToMillipoints) {
				fX[4] *= 1000.0;
				fX[5] *= 1000.0;
			}
#if SVGDEBUG
			svgtrace(DBGTRACE_TRANS, "creating user matrix [%.4f %.4f %.4f %.4f %.4f %.4f]\n",
					 fX[0], fX[1], fX[2], fX[3], fX[4], fX[5]);
#endif
			trans *= Transformation::CreateMatrix(fX);
		} else {
			// skip unexpected character
			s = s.Mid(1);
		}
	}

	return trans;
}

Transformation ParseTransformations(xmlNodePtr cur, const char* prop, bool bScaleToMillipoints)
{
	wxString s = GetStringProperty(cur, prop);
	Transformation trans = ParseTransformations(s, bScaleToMillipoints);
	return trans;
}

#if SVGDEBUG
void DebugDumpTransformation(int lvl, const Transformation& trans)
{
	svgtrace(lvl, "trans data[0..5] = [ ");
	for (int i = 0; i < 6; ++i)
		svgtrace(lvl, "%.4f ", trans.data[i]);
	svgtrace(lvl, "], ");
	svgtrace(lvl, "size = [%.2f %.2f]\n", trans.size.x, trans.size.y);
}
#endif
