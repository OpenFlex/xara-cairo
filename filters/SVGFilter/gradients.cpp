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

// gradients.cpp: This implements the class for handling the gradients

#include "gradients.h"
#include "utils.h"

// define list of GradientStop elements
#include <wx/listimpl.cpp>
WX_DEFINE_LIST(GradientStopList);

Gradient& Gradient::operator =(const Gradient& copy)
{
	type = copy.type;
	xmlId = copy.xmlId;
	units = copy.units;

	x1 = copy.x1;
	y1 = copy.y1;
	x2 = copy.x2;
	y2 = copy.y2;
	cx = copy.cx;
	cy = copy.cy;
	r  = copy.r;

	stops.Clear();
	// copy all the stops
    for (GradientStopList::Node* node = copy.stops.GetFirst(); node != NULL; node = node->GetNext()) {
        GradientStop* current = node->GetData();
		GradientStop* copy = new GradientStop(*current);
		stops.Append(copy);
	}

	solidColour = copy.solidColour;
	solidOpacity = copy.solidOpacity;

	return *this;
}
