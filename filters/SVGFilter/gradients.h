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

// gradients.h: This defines the class for handling the gradients

#ifndef GRADIENTS_H
#define GRADIENTS_H

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

// libxml2 library
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>

#ifndef LIBXML_READER_ENABLED
#error xmlreader must be enabled in libxml2!
#endif

#include "styles.h"

/***************************************************************************************************

>	struct GradientStop

	Author:		Sandro Sigala <sandro@sigala.it>
	Created:	25 July 2006
	Purpose:	Contains SVG gradients stop parameters.

***************************************************************************************************/

struct GradientStop {
	GradientStop() {
		offset = 0.0;
		stopColour = wxColour(0,0,0);
		stopOpacity = 1.0;
	}
	GradientStop(const GradientStop& copy) { *this = copy; }

	GradientStop& operator =(const GradientStop& copy) {
		offset = copy.offset;
		stopColour = copy.stopColour;
		stopOpacity = copy.stopOpacity;
		return *this;
	}

	double				offset;
	wxColour			stopColour;
	double				stopOpacity;
};

WX_DECLARE_LIST(GradientStop, GradientStopList);

/***************************************************************************************************

>	struct Gradient

	Author:		Sandro Sigala <sandro@sigala.it>
	Created:	25 July 2006
	Purpose:	Contains SVG gradients parameters.

***************************************************************************************************/

struct Gradient {
	enum Type { SolidColour, Linear, Radial };
	enum Units { UserSpaceOnUse, ObjectBoundingBox };

	Gradient() {
		type = Linear;
		units = ObjectBoundingBox;
		x1 = y1 = x2 = y2 = 0.0;
		cx = cy = r = 0.0;
		stops.DeleteContents(true);
	}
	Gradient(const Gradient& copy) { *this = copy; }
	~Gradient() {}

	Gradient& operator =(const Gradient& copy);

	Type				type;
	wxString			xmlId;
	Units				units;
	// linear gradient parameters
	double				x1, y1, x2, y2;
	// radial gradient parameters
	double				cx, cy, r;
    // common gradient parameters
	GradientStopList	stops;
	// solidColor paramenters
	wxString			solidColour;
	double				solidOpacity;
};

WX_DECLARE_STRING_HASH_MAP(Gradient*, pGradientHashTable);

#endif // !GRADIENTS_H
