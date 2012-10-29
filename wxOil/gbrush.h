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


// class to use GDraw to obtain GDI brush patterns

#ifndef INC_GBRUSH
#define	INC_GBRUSH


class DocColour;
class ColourContext;

/********************************************************************************************

>	class GBrush : public ListItem

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/4/94
	Purpose:	A GBrush is a way of getting to Gavin-created brushes, when available.
				It can supply GDI with better dithered brushes than it does normally.
				Before use, you should call Init which tells you whether a GBrush is
				available. If it is not, no further use can be made of it. If it is,
				call Start on it (cv StartRender). It can then be used, until such time
				as End is called on it. An in-line member function called Available can be
				used to determine its functionality at any time. There can only be one active
				GBrush in use at a time.

********************************************************************************************/

class GBrush : public ListItem
{
CC_DECLARE_MEMDUMP(GBrush);
public:
	GBrush();
	~GBrush();
	BOOL Init( wxDC* Ref );
	void Start();
	void Stop();
	BOOL Available() { return Valid; }
	void GetLogBrush( ColourContext *, DocColour &, wxBrush* );
	void GetLogBrush( const COLORREF rgb, wxBrush* pBrush );

	static BOOL InitGBrush(BOOL);
	static void DeinitGBrush(void);
	static void NewBrushState();

	void SetSolidColours(BOOL UseSolid);
		// Enables/disables solid colour override (to remove dithering)

	static void ResetOnFatalError() {if (Current) Current->Stop();}

private:
	inline void GetLogBrushInternal( const COLORREF rgb, wxBrush* pBrush );

	BOOL Valid;											// TRUE if bitmap set up
	BOOL CanUse;										// TRUE if will work

	wxDC* ReferenceDC;									// reference device (for palette)

	RGBQUAD RGBList[256];								// contains system palette (256 cols)

	static List BrushList;								// list of all active brushes
	static GBrush *Current;								// active brush

	BOOL UseSolidColours;								// TRUE = solid, FALSE = dithered colours
};

/********************************************************************************************

>	BOOL GBrush::Available()

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/4/94
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if can use it, FALSE if cannot.
	Purpose:	Determine whether this GBrush works or not. An in-line function.
	Errors:		-

********************************************************************************************/


#endif
