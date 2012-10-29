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

// CDR colour structure handling

/*
*/

#ifndef INC_CDRCOL
#define INC_CDRCOL

#include "impcol.h"
#include "cdrform.h"

#define IMPORTED_TO_DOCCOLOUR(X, Y) DocColour X((Y).Model, &((Y).Colour));

/********************************************************************************************

>	class CDRColour

	Author:		Ben_Summers (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18 03 95	
	Purpose:	Translation of colours from CDR files.	

********************************************************************************************/

class CDRColour
{
public:
	static BOOL Convert5(cdrfColour *Colour, ImportedNewColour *To); 	// Converts a version 5 colour
	static BOOL Convert4(cdrfColour *Colour, ImportedNewColour *To);	// Converts a version 4 colour
	static BOOL Convert3(cdrfColour *Colour, ImportedNewColour *To);	// Converts a version 3 colour

private:
	static BOOL MakeUKCol(ImportedNewColour *To);
};

#endif  // INC_CDRCOL
