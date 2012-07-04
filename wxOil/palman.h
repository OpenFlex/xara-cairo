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

// palman.h - a centralised screen palette manager

#ifndef INC_PALMAN
#define INC_PALMAN

//#include "doccolor.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class CDC;
class CPalette;

class PaletteManager : public CC_CLASS_MEMDUMP
{
public:
	// Realizes the GDraw palette for the given window, in either the foreground or background.
	// Returns TRUE if the palette mapping chnaged as a result.
	// Called to handle OnQueryNewPalette and PaletteChanged messages
	// (Set ForceRedraw to TRUE to redraw your window. THis should always be done for PALETTECHANGED)
//	static BOOL EnsurePalette(HWND hWnd, BOOL ForceRedraw);
	static BOOL EnsurePalette(wxWindow* CWindow, BOOL ForceRedraw);

	// Call this to select and realize the GDraw palette into your DC when you're about to render
//	static wxPalette* StartPaintPalette(wxDC* RenderDC, BOOL bForceBackground=FALSE);
	static wxPalette* StartPaintPalette(wxDC* hDC, wxPalette* pHPal=NULL, BOOL bForceBackground=FALSE);
//	static wxPalette* StartPaintPalette(wxDC* hDC, const wxPalette& HPal, BOOL bForceBackground=FALSE);

	// Call this to select and realize the previous palette back into your DC when you've finished rendering
	static wxPalette* StopPaintPalette(wxDC* RenderDC, wxPalette* OldPalette, BOOL bForceBackground=TRUE);
//GAT	static wxPalette* StopPaintPalette(wxDC* hDC, wxPalette* OldPalette, BOOL bForceBackground=TRUE);

	// Initialises the palette manager
	static BOOL Init(void);
	
	// Returns TRUE if should use MainPalette object
	static BOOL UsePalette(void)
	{
		return(sm_bUseMainPalette);
	};

	// Forces the palette manager to re-read it's palette (used on mode changes)
	static void UpdatePalette(void);
	
	// Returns a pointer to the main palette object
	static wxPalette* GetPalette(void)
	{
		return(sm_bUseMainPalette ? &sm_MainPalette : NULL);
	}

	// Locks the palette to force it to always realize in the background. Used by the splashbox
	static void LockPalette(BOOL fLocked);

	// Causes all camelot windows reliant on the 256-colour palette to redraw
	static void RedrawAllPalettedWindows(wxWindow* ParentWindow = NULL);

	// WEBSTER - markn 8/2/97
	// Func for getting the standard browser Palette
	// Webster requires that the palette does not contain any non-browser colours, so all bitmaps
	// produced (e.g. gif export, create bitmap copy, etc) will look correct in a browser
	static void MakePaletteBrowserCompatible(LPLOGPALETTE pPalette,BOOL IncludeSystemColours);

	// Puts all the browser colours into the given palette
	static void FillWithBrowserColours(LPLOGPALETTE pPalette,INT32 StartIndex);

	// Returns TRUE if the palatte contains all the 216 browser colours
	static BOOL ContainsAllBrowserColours(LPLOGPALETTE pPalette);

	// Creates a browser palette, returning a ptr to it (use CCFree() when you're done with it)
	static LPLOGPALETTE CreateBrowserPalette(BOOL AvoidSystemColours);

	// Find the nearest colour in a given palette, to the one provided (only works in RGB space)
	static void FindNearestColour(const ColourRGBT& Colour, LPLOGPALETTE pPalette, ColourRGBT* const pResult);

	// Find the nearest colour in a given palette, to the one provided
	static PALETTEENTRY FindNearestColour(const PALETTEENTRY& PalColour, LPLOGPALETTE pPalette);
	//  Same as above, except it returns an index, rather than a colour.
	static INT32 FindIndexOfNearestColour(const PALETTEENTRY& PalColour, LPLOGPALETTE pPalette);

	// Get the distance between two colours, squared
	static double		FindColourDistanceSquared(const PALETTEENTRY* pPal1,const PALETTEENTRY* pPal2);

	// Find the nearest colour in the browser palette, to the one provided (only works in RGB space)
	static void FindNearestBrowserColour(const ColourRGBT& Colour, ColourRGBT* const pResult);

	// Snaps the colours in one palette to nearest colours in the other palette
	static void SnapToPalette(LPLOGPALETTE pPalette, const LPLOGPALETTE pPaletteToSnapTo);

	// Snaps the colours in the palette to nearest colours in the browser palette
	static void SnapToBrowserPalette(LPLOGPALETTE pPalette);

	// set up a palette entry to a particular value
	static void PokePaletteEntry(LPLOGPALETTE Palette, INT32 * index,
								 BYTE red, BYTE green, BYTE blue, BYTE Flags = 0);

	// returns a 4bpp browser compatible palette or NULL
	static LPLOGPALETTE Get4bppBrowserPalette(UINT32 ReservedColours);
	
	// Finds the first unused colour in the palette, if any
	static INT32 FindFirstDontUseColourInPalette(LPLOGPALETTE pPalette);

protected:		// Internal worker functions
	static BOOL CALLBACK InvalidateChildProc(wxWindow* hWnd, LPARAM lParam);
	static BOOL IsRedrawOnPaletteChangeRequired(wxWindow* hWnd, BOOL* pNotifyFirst = NULL);

protected:
	static wxPalette sm_MainPalette;
	static BOOL sm_bUseMainPalette;

protected:
	static BOOL m_fPaletteLocked;		// Bodge to make the palette manager select the main palette
										// in the background while the splashbox is up
};

#endif
