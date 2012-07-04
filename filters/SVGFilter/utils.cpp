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

// utils.cpp: This implements various common utility functions

#include "utils.h"
#include "styles.h"

// trim whitespace from string
wxString TrimWs(const wxString& s)
{
	wxString ret = s;
	return ret.Trim(true).Trim(false);
}

// take (and remove) the first number from the string and return it
// XXX should be more clever parsing floating point numbers
// (e.g. bogus 1.2e2.1e3 is currently accepted)
double TakeNumber(wxString& data)
{
	wxString s;
	data = TrimWs(data);
	if (data.IsEmpty())
		return 0.0; // some error
	if (IsNumberChar(data[0])) {
		s += data[0];
		data = data.Mid(1);
		while (data.Length() > 0 && IsNumberDigit(data[0])) {
			s += data[0];
			if (data[0] == 'e' || data[0] == 'E') {
				data = data.Mid(1);
				if (data.Length() < 1)
					break;
				if (data[0] == '+' || data[0] == '-') {
					s += data[0];
					data = data.Mid(1);
				}
			} else {
				data = data.Mid(1);
			}
		}
	}
	double f;
	s.ToDouble(&f);
	return f;
}

void AddProperty(xmlNodePtr cur, const wxString& sName, const wxString& sValue)
{
	xmlSetProp(cur, (const xmlChar *)(const char *)sName.mb_str(wxConvUTF8),
			   (const xmlChar *)(const char *)sValue.mb_str(wxConvUTF8));
}

// take the property named "name"
wxString GetStringProperty(xmlNodePtr cur, const char *name, const wxString& def)
{
	wxString s = def;
	xmlChar *value = xmlGetProp(cur, (const xmlChar *)name);
	if (value != NULL) {
		s = wxString::FromAscii((const char *)value);
		xmlFree(value);
	}
	return s;
}

// take the property named "name" and convert to double
double GetDoubleProperty(xmlNodePtr cur, const char *name, double def)
{
	double x = def;
	xmlChar *value = xmlGetProp(cur, (const xmlChar *)name);
	if (value != NULL) {
		x = atof((const char *)value);
		xmlFree(value);
	}
	return x;
}

// take the property named "name" and convert to double and clamp to range [0,1]
double GetClampedDoubleProperty(xmlNodePtr cur, const char *name, double def)
{
	double x = def;
	xmlChar *value = xmlGetProp(cur, (const xmlChar *)name);
	if (value != NULL) {
		wxString s = wxString::FromAscii((const char *)value);
		xmlFree(value);

		s = TrimWs(s);
		if (s.Right(1) == _T("%")) {
			// strip "%"
			s = s.RemoveLast(1).Trim();
			s.ToDouble(&x);
			x *= 0.01;
		} else {
			s.ToDouble(&x);
		}
		if (x < 0.0)
			x = 0.0;
		else if (x > 1.0)
			x = 1.0;
	}
	return x;
}

// take the property named "name" and convert to a colour
wxColour GetColourProperty(xmlNodePtr cur, const char *name, wxColour def)
{
	wxColour col = def;
	xmlChar *value = xmlGetProp(cur, (const xmlChar *)name);
	if (value != NULL) {
		wxString s = wxString::FromAscii((const char *)value);
		col = Style::ParseColour(s);
		xmlFree(value);
	}
	return col;
}

// is the measure relative?
bool IsRelativeMeasure(const wxString& measure)
{
	wxString s = measure;
	// remove whitespace and convert to lowercase
	s = TrimWs(s).MakeLower();
	return (s.IsNumber() || s.Right(1) == _T("%"));
}

// is the string an absolute measure?
bool IsAbsoluteMeasure(const wxString& measure)
{
	wxString s = measure;
	// remove whitespace and convert to lowercase and take last 2 chars
	s = TrimWs(s).MakeLower().Right(2);
	return (s == _T("cm") || s == _T("mm") || s == _T("in") || s == _T("pc") || s == _T("px"));
}

// convert measure to millipoints
double AbsoluteMeasureToMillipoints(const wxString& measure)
{
	wxString s = measure;
	// remove whitespace and convert to lowercase
	s = TrimWs(s).MakeLower();

	double f;
	if (s.Right(2) == _T("cm")) {
		s = s.RemoveLast(2).Trim();
		s.ToDouble(&f);
		f = CM2PT(f)/0.8*1000.0; // Convert to millipoints
	} else if (s.Right(2) == _T("mm")) {
		s = s.RemoveLast(2).Trim();
		s.ToDouble(&f);
		f = MM2PT(f)/0.8*1000.0; // Convert to millipoints
	} else if (s.Right(2) == _T("in")) {
		s = s.RemoveLast(2).Trim();
		s.ToDouble(&f);
		f = IN2PT(f)/0.8*1000.0; // Convert to millipoints
	} else if (s.Right(2) == _T("pc")) {
		s = s.RemoveLast(2).Trim();
		s.ToDouble(&f);
		f = PC2PT(f)/0.8*1000.0; // Convert to millipoints
	} else if (s.Right(2) == _T("px")) {
		s = s.RemoveLast(2).Trim();
		s.ToDouble(&f);
		f = PX2PT(f)/0.8*1000.0; // Convert to millipoints
	} else { // anything else
		if (s.Right(2) == _T("pt"))
			s = s.RemoveLast(2).Trim();
		s.ToDouble(&f);
		f *= 1000.0;
	}

	return f;
}

#if SVGDEBUG
extern long iDebugTraceLevel; // from svgfilter.cpp

void svgtrace(int lvl, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	if (lvl & iDebugTraceLevel)
		vfprintf(stderr, fmt, ap);
	va_end(ap);
}
#endif
