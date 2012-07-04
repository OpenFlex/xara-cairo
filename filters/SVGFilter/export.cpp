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

// export.cpp: This implements the XAR --> SVG backend

#include "svgfilter.h"
#include "version.h"

// Should we output verbose SVG?
static bool s_bVerboseSVG = false;
// The specification version of the SVG output
enum SVGVersion { SVGVersion_11, SVGVersion_12 };
static SVGVersion s_SVGVersion = SVGVersion_11;

// Here we keep data during XAR record parsing
class ExportData
{
public:
	wxTextOutputStream *pOutText;
};

bool DoPrepareExportInternal(const wxString& sFileName, const wxString& sXMLFileName)
{
	// nothing to do here
	return true;
}

// Cycle thru each XAR record
BOOL HandleRecord(void* pMagic, CXaraFileRecord* pRecord)
{
	ExportData* pData = (ExportData*)pMagic;
	wxTextOutputStream& OutText = *pData->pOutText;

	// Get the Tag of the record
	UINT32 Tag = pRecord->GetTag();

	OutText << _T("<!-- entity tag=\"") << Tag << _T("\" -->\n");
	// XXX just to see if it works, of course units are wrong
	switch (Tag) {
		case TAG_RECTANGLE_SIMPLE:
		{
			DocCoord Centre;
			INT32 MajorAxis;
			INT32 MinorAxis;
			pRecord->ReadCoord(&Centre);
			pRecord->ReadINT32(&MajorAxis);
			pRecord->ReadINT32(&MinorAxis);
			OutText << wxString::Format(_T("<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" />\n"),
										Centre.x, Centre.y, MajorAxis, MinorAxis);
		}
	}

	return true;
}

// read the settings from the xml capatibility file (<Private/> section)
static bool ParseXmlCapatibilityFile(const wxString& sXMLFileName)
{
    xmlTextReaderPtr reader;
    int ret;

    reader = xmlReaderForFile(sXMLFileName.mb_str(wxConvUTF8), NULL, 0);
    if (reader != NULL) {
		ret = xmlTextReaderRead(reader);
		while (ret == 1) {
			const xmlChar *name;

			// get the entity name
			name = xmlTextReaderConstName(reader);

			if (!xmlStrcmp(name, (const xmlChar *)"Private")) {
				const xmlChar *attribute;

				// get the value of "version" attribute
				attribute = xmlTextReaderGetAttribute(reader, (const xmlChar *)"version");
				if (attribute != NULL) {
					if (!xmlStrcmp(attribute, (const xmlChar *)"1.2"))
						s_SVGVersion = SVGVersion_12;
				}

				// get the value of "verbose" attribute
				attribute = xmlTextReaderGetAttribute(reader, (const xmlChar *)"verbose");
				if (attribute != NULL) {
					if (!xmlStrcmp(attribute, (const xmlChar *)"1"))
						s_bVerboseSVG = true;
				}

				break;	// stop parsing
			}
			// get next item
			ret = xmlTextReaderRead(reader);
		}

		// dispose xmlReader
		xmlFreeTextReader(reader);
    } else {
		ReportError(_T("Unable to open xml capatibility file"));
		return false;
    }

	return true;
}

bool DoExportInternal(CXarImport* pImporter, const wxString& sFileName, const wxString& sXMLFileName, bool bCompress)
{
	if (!ParseXmlCapatibilityFile(sXMLFileName))
		return false;

	// Open the output file for writing
	wxFileOutputStream OutFile(sFileName);
	if (!OutFile.Ok())
	{
		ReportError(_T("Failed to open output file."));
		// Set an appropriate error here
		return false;
	}

	wxOutputStream *pOutStream;
	// Make pOutStream point to the file stream or add another
	// compressed stream filter layer on top of it,
	// depending on the bCompress flag.
	if (bCompress) {
		pOutStream = new wxZlibOutputStream(OutFile, wxZ_BEST_COMPRESSION, wxZLIB_GZIP);
		// we will delete pOutStream later
	} else {
		pOutStream = &OutFile;
	}

	// Open text stream
	wxTextOutputStream OutText(*pOutStream);

	ExportData MyData;
	MyData.pOutText = &OutText;

	// Set up our record handler function
	if (!pImporter->SetHandler(&MyData, ::HandleRecord))
	{
		ReportError(_("SetHandler failed"));
		// Set an appropriate error here
		return false;
	}

	// Output standard XML header
	OutText << _T("<?xml version=\"1.0\" standalone=\"no\"?>\n");

	// DTD is specified only for version 1.1
	if (s_SVGVersion == SVGVersion_11)
		OutText	<< _T("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n")
				<< _T("\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");

//<svg width="10cm" height="5cm" viewBox="0 0 1000 500"
//     xmlns="http://www.w3.org/2000/svg" version="1.1">

	OutText << _T("<svg xmlns=\"http://www.w3.org/2000/svg\"");
	// output version attribute
	if (s_SVGVersion == SVGVersion_11)
		OutText << _T(" version=\"1.1\"");
	else // s_SVGVersion == SVGVersion_12
		OutText << _T(" version=\"1.2\"");
	OutText << _T(">\n");

	wxDateTime date = wxDateTime::Now();
	OutText << _T("<!-- Generator: Xara Xtreme 2.0, SVG Export Plug-In Version: ") << VERSION_TSTRING << _T(" -->\n")
			<< _T("<!-- Generated ") << date.FormatISODate() << _T(" ") << date.FormatISOTime() << _T(" -->\n")
			<< _T("<!-- not very useful exporter for now... -->\n");
	if (s_bVerboseSVG)
		OutText << _T("<!-- verbose mode enabled -->\n");

	// And do the import (cycles with HandleRecord() function)
	if (!pImporter->DoImport())
	{
		ReportError(_T("Failed to parse Xar data."));
		// Set an appropriate error here
		return false;
	}

	OutText << _T("</svg>\n");

	// Delete the compress stream if compression is enabled
	if (bCompress)
	{
		delete pOutStream;
	}

	return true;
}
