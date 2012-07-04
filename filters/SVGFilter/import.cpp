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

// import.cpp: This implements the SVG --> XAR backend

#include "svgfilter.h"
#include "svgimporter.h"
#include "utils.h"
#include "version.h"

// Check for XML document correctness
bool DoCanImportInternal(const wxString& sFileName)
{
	bool IsCompatible = true;
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(sFileName.mb_str(wxConvUTF8));
	if (doc == NULL) {
		ReportError(_T("Failed to open input file"));
		IsCompatible = false;
		goto finish;
	}

	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		ReportError(_T("The document is empty"));
		xmlFreeDoc(doc);
		IsCompatible = false;
		goto finish;
	}
	if (!IsEntityName(cur, "svg")) {
		ReportError(_T("document root is not <svg>"));
		xmlFreeDoc(doc);
		IsCompatible = false;
		goto finish;
	}

	// All seem correct, so dispose document
	xmlFreeDoc(doc);

finish:
	wxPrintf(_T("%d\n"), IsCompatible ? 10 : 0);

	return IsCompatible;
}

// Import the XML document
bool DoImportInternal(CXarExport* pExporter, const wxString& sFileName)
{
	SVGImporter importer(pExporter, sFileName);

	if (!importer.Open())
		return false;
	if (!importer.ParseAndOutput())
		return false;

	return true;
}
