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

// svgimporter.h: This defines the SVG --> XAR parser and producer

#ifndef SVGIMPORTER_H
#define SVGIMPORTER_H

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

// libxml2 library
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>

#ifndef LIBXML_READER_ENABLED
#error xmlreader must be enabled in libxml2!
#endif

#include <stdarg.h>

// for Style, StyleList and ColourRefHashTable
#include "styles.h"
// for GradientStop, Gradient, pGradientHashTable
#include "gradients.h"
// for Transformation and TransformationList
#include "trans.h"
// for XARGenerator
#include "xargenerator.h"
	 
/***************************************************************************************************

>	class SVGImporter

	Author:		Sandro Sigala <sandro@sigala.it>
	Created:	1 July 2006
	Purpose:    Handles all the parsing of SVG documents and conversion to XAR documents.

***************************************************************************************************/

class SVGImporter {
public:
	SVGImporter(CXarExport* pExporter, const wxString& sFileName);
	~SVGImporter();

	bool Open();
	bool ParseAndOutput();

private:
	// SVG/XML entities parsers ----------------------------------------------

	bool ParseRootTree();

    bool ParseGradientStopsEntity(xmlNodePtr cur, Gradient* pGradient);
	bool ParseLinearGradientEntity(xmlNodePtr cur);
	bool ParseRadialGradientEntity(xmlNodePtr cur);
	bool ParseDefsEntity(xmlNodePtr cur);
	bool ParsePathData(const wxString& data, PathDataVector& pathVector);
	bool ParsePathEntity(xmlNodePtr cur);
	bool ParseRectEntity(xmlNodePtr cur);
	bool ParseEllipseEntity(xmlNodePtr cur, bool bIsCircle);
	bool ParseLineEntity(xmlNodePtr cur);
	bool ParsePolylineData(const wxString& data, PointDVector& coordVector);
	bool ParsePolylineEntity(xmlNodePtr cur);
	bool ParsePolygonEntity(xmlNodePtr cur);
	bool ParseGroupEntity(xmlNodePtr cur);
	bool ParseEntitiesTree(xmlNodePtr cur);

	// transformations -------------------------------------------------------
	
	void PushTransformations();
	void PopTransformations();
	Transformation GetCurrentTransformation() const;
	Transformation& GetCurrentTransformation();

	double MeasureToMillipoints(const Transformation& trans, const wxString& sMeasure) const;
	PointD GetTransformedCoordinate(const Transformation& trans,
									const wxString& sX, const wxString& sY) const;
	PointD GetTransformedCoordinate(xmlNodePtr cur, const Transformation& trans,
									const char* pX, const char* pY) const;
	RectD GetTransformedRectangle(const Transformation& trans,
								  const wxString& sX, const wxString& sY,
								  const wxString& sWidth, const wxString sHeight) const;
	RectD GetTransformedRectangle(xmlNodePtr cur, const Transformation& trans,
								  const char* pX, const char* pY,
								  const char* pW, const char* pH) const;
	RectD GetTransformedCircle(const Transformation& trans,
							   const wxString& sX, const wxString& sY, const wxString& sR) const;
	RectD GetTransformedCircle(xmlNodePtr cur, const Transformation& trans,
							   const char* pX, const char* pY, const char* pR) const;
	RectD GetTransformedEllipse(const Transformation& trans,
								const wxString& sX, const wxString& sY,
								const wxString& sRX, const wxString& sRY) const;
	RectD GetTransformedEllipse(xmlNodePtr cur, const Transformation& trans,
								const char* pX, const char* pY,
								const char* pRX, const char* pRY) const;
	double GetTransformedMeasure(const Transformation& trans, const wxString& sMeasure) const;
	double GetTransformedMeasure(xmlNodePtr cur, const Transformation& trans, const char* pM) const;

	// styles ----------------------------------------------------------------

	void PushStyles();
	void PopStyles();
	Style GetCurrentStyle() const;
	Style& GetCurrentStyle();
	Style ParseStyle(xmlNodePtr cur, const Transformation& trans, bool bIsObject) const;
	Style ParseGradientStyle(xmlNodePtr cur) const;
    void ImportFillStyleFromDefs(Style& style, const wxString& sXmlId) const;
    void ImportStrokeStyleFromDefs(Style& style, const wxString& sXmlId) const;
	Gradient* FindGradientInDefs(const wxString& sXmlId) const;

	XARGenerator*		m_pGenerator;
	wxString			m_sFileName;
	xmlDocPtr			m_doc;
	xmlNodePtr			m_root;
	DocCoord			m_docSize;
	TransformationList	m_trans;
	StyleList			m_styles;
	pGradientHashTable	m_gradients;
};

#endif // !SVGIMPORTER_H
