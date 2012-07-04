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

      
#ifndef INC_WINRECT
#define INC_WINRECT


#include "wincoord.h"
#include "docrect.h"


class OilRect;
class View;

/***********************************************************************************************

>    class CCAPI WinRect : public CRect

     Author:       Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
     Date:    	   8/8/93
     Purpose:      A Windows rectangle.
     Errors:	   -
     SeeAlso:	   WinCoord
     			    
***********************************************************************************************/

class CCAPI WinRect : public wxRect
{   
public:
	WinRect();
	WinRect(INT32 Left, INT32 Top, INT32 Right, INT32 Bottom);

	const WinRect& operator=(const wxRect& rect)
	{
		x = rect.x;
		y = rect.y;
		width = rect.width;
		height = rect.height;
		return(*this);
	}

	// Alternate versions of these functions that deal with exclusive bottom and right
    INT32 GetRightEx()  const { return x + width; }
	INT32 GetBottomEx() const { return y + height; }
	wxPoint GetBottomRightEx() const {return wxPoint(x + width, y + height);}

    void SetRightEx(INT32 right) { width = right - x; }
    void SetBottomEx(INT32 bottom) { height = bottom - y; }
	void SetBottomRightEx(const wxPoint& pt)
	{
		width = pt.x - x;
		height = pt.y - y;
	}

	OilRect ToOil(View *pView) const;
};                                            
  

#endif	// INC_WINRECT
