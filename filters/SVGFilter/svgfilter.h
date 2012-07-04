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

// svgfilter.h: This defines the XAR <--> SVG command line interface

#ifndef SVGFILTER_H
#define SVGFILTER_H

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

// additional wxWidgets classes
#include "wx/cmdline.h"
#include "wx/wfstream.h"
#include "wx/txtstrm.h"
#include "wx/zstream.h"
#include "wx/datetime.h"
#include "wx/tokenzr.h"

// XAR handling library
#include "xarlib/xarlib.h"
#include "xarlib/docrect.h"
#include "xarlib/paths.h"

// libxml2 library
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>

#ifndef LIBXML_READER_ENABLED
#error xmlreader must be enabled in libxml2!
#endif

// forward declarations
void ReportError(const wxChar* pStr);
void ReportWarning(const wxChar* pStr);

// import
bool DoCanImportInternal(const wxString& sFileName);
bool DoImportInternal(CXarExport* pExporter, const wxString& sFileName);

// export
bool DoPrepareExportInternal(const wxString& sFileName, const wxString& sXMLFileName);
bool DoExportInternal(const wxString& sFileName, const wxString& sXMLFileName);
bool DoExportInternal(CXarImport* pImporter, const wxString& sFileName, const wxString& sXMLFileName, bool bCompress);

#endif // !SVGFILTER_H
