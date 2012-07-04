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

// svgimporter.h: This defines the XAR generator

#ifndef XARGENERATOR_H
#define XARGENERATOR_H

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/hashmap.h"

// XAR handling library
#include "xarlib/xarlib.h"

// for Style, StyleList and ColourRefHashTable
#include "styles.h"
// for GradientStop, Gradient, pGradientHashTable
#include "gradients.h"
// for Transformation
#include "trans.h"
// for SimpleVector
#include "utils.h"

// used for storing paths data (coordinate and verb)
struct PathData {
	PathData() : m_verb(0x00) {}
	PathData(BYTE verb, const PointD& coord) : m_verb(verb), m_coord(coord) {}
	BYTE m_verb;
	PointD m_coord;
};
typedef SimpleVector<PathData> PathDataVector;
typedef SimpleVector<PointD> PointDVector;

/***************************************************************************************************

>	class XARGenerator

	Author:		Sandro Sigala <sandro@sigala.it>
	Created:	28 July 2006
	Purpose:    Produces XAR documents.

***************************************************************************************************/

class XARGenerator {
public:
	XARGenerator(CXarExport* pExporter) { m_pExporter = pExporter; }
	~XARGenerator() {}

	void SetDocumentSize(const DocCoord& size) { m_docSize = size; }

	bool OutputHeader();
	bool OutputFooter();
	bool OutputPathEntity(const Style& style, const Transformation& trans, PathDataVector& pathVector);
	bool OutputRectEntity(const Style& style, const Transformation& trans, const RectD& r, double fRoundAxis);
	bool OutputEllipseEntity(const Style& style, const Transformation& trans, const RectD& r);
	bool OutputLineEntity(const Style& style, const Transformation& trans, const PointD& p1, const PointD& p2);
	bool OutputPolylineEntity(const Style& style, const Transformation& trans, const PointDVector& coordVector);
	bool OutputPolygonEntity(const Style& style, const Transformation& trans, const PointDVector& coordVector);
	bool EnterGroup();
	bool LeaveGroup();
	bool OutputOpacity(double fOpacity);

private:
	RectD GetMaximumBoundings(const PathDataVector& coordVector);
	RectD GetMaximumBoundings(const PointDVector& coordVector);
    void DetermineLinearGradientPoints(const Gradient* pGradient, const Transformation& trans,
							           const RectD& boundings, DocCoord& p1, DocCoord& p2);
    void DetermineRadialGradientPoints(const Gradient* pGradient, const Transformation& trans,
							           const RectD& boundings, DocCoord& pC, DocCoord& pMaj, DocCoord& pMin);

	bool OutputUprightRect(const RectD& r, double fRoundAxis);
	bool OutputComplexRect(const RectD& r, double fRoundAxis);
	bool OutputUprightEllipse(const RectD& r);
	bool OutputComplexEllipse(const RectD& r);
	bool OutputFillLinearGradient(const Style& style, const Transformation& trans, const RectD& boundings);
	bool OutputFillRadialGradient(const Style& style, const Transformation& trans, const RectD& boundings);
	bool OutputStyles(const Style& style, const Transformation& trans, const RectD& boundings, UINT32 witch);

	INT32 DefineColour(const wxColour& col);

	CXarExport*			m_pExporter;
	DocCoord			m_docSize;
	ColourRefHashTable  m_colourRef;
};

#endif // !XARGENERATOR_H
