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

      
#ifndef INC_OILRECT
#define INC_OILRECT

#include "oilcoord.h"
#include "rect.h"


class WinRect;
class WorkRect;
class DocRect;
class View;

/***********************************************************************************************

>    class CCAPI OilRect : public Rect

     Author:       Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
     Date:    	   8/8/93
     Purpose:      -
     Errors:	   -
     SeeAlso:	   OilCoord

***********************************************************************************************/

class CCAPI OilRect : public Rect
{   
public:
	OilRect();
	OilRect(OilCoord, OilCoord);
	
	WinRect  ToWin(View *pView) const;
	WorkRect ToWork(const WorkCoord& ScrollOffset) const;

	DocRect ToDoc(const Spread* pSpread, View *pView) const;
};                                            
  
#endif	// INC_OILRECT
