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


// CC super version of the MFC CDC class

/*
*/

#include "camtypes.h"
#include "ccdc.h"
//#include "gdimagic.h"
//#include "tim.h"
#include "camelot.h"


// How many individual regions should allow before we stick them all together
// It is set to be 10 rectangles by default.
#define MAX_REGIONS (sizeof(RGNDATAHEADER) + (40 * sizeof(RECT)))



/********************************************************************************************

>	class CCDC : public CDC

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/11/93
	Purpose:	A layer above the MFC CDC class which contains additional information,
				including a type word (see RenderType) and rectangle list information. Note 
				that is is derived from an MFC class, not CCObject so take care with 'new's
				and ISRUNTIME checks.
	SeeAlso:	CDC;CCPaintDC

********************************************************************************************/



// so we can runtime-check it

CC_IMPLEMENT_DYNAMIC( CCDC, ListItem )
CC_IMPLEMENT_DYNAMIC( CCPaintDC, CCDC )
CC_IMPLEMENT_DYNAMIC( CCClientDC, CCDC )
CC_IMPLEMENT_DYNAMIC( CCDummyDC, CCDC )

List CCDC::s_DCList;


/*********************************************************************************************

>	CCDC::CCDC(RenderType rType)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/10/93
	Inputs:		The type of CCDC that is required.
	Outputs:	None
	Returns:	None
	Purpose:	Constructor for CCDC. Stores type and zeros rectangle list.
	Errors:		-
	Scope:	    Public
	SeeAlso:	RenderType

*********************************************************************************************/ 

CCDC::CCDC( RenderType rType )
{
	lpRgnData = NULL;
	Type = rType;
	m_pDC = NULL;
	m_bDeleteDC = TRUE;
}

/*********************************************************************************************

>	CCDC::CCDC(CDC *cdc, RenderType rType)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/10/93
	Inputs:		An exisiting CDC and the type of CCDC that is required.
	Outputs:	None
	Returns:	None
	Purpose:	Constructor for CCDC to base it on an existing CDC. The CDC on which this
				is based MUST stay in existance while this CCDC is in existence as it
				'borrows' the members from the doner CDC.
	Errors:		-
	Scope:	    Public

*********************************************************************************************/ 

CCDC::CCDC( CNativeDC *pDC, RenderType rType )
{
	lpRgnData = NULL;
	Type = rType;
	m_pDC=NULL;
	m_bDeleteDC = FALSE;
	SetDC(pDC, FALSE); // previously m_pDC = pDC;
}

/*********************************************************************************************

>	CCDC::~CCDC()

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/10/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Destructor for CCDC.
	Errors:		-
	Scope:	    Public

*********************************************************************************************/ 

CCDC::~CCDC()
{
	SetDC(NULL);
	CCFree(lpRgnData);
	lpRgnData = NULL;

	// Karim 06/06/2000 - NULLify our handles.
//	m_hDC = NULL;
//	m_hAttribDC = NULL;
}

/*********************************************************************************************

>	static CCDC *CCDC::ConvertFromNativeDC( CNativeDC* pDC )

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/93
	Inputs:		Pointer to a CDC.
	Outputs:	None
	Returns:	A pointer to a CCDC, or NULL if it cannot be safely cast.
	Purpose:	See if a CDC* is really a CCDC* which we can get useful extra information
				from.
	Errors:		-
	Scope:	    Public

*********************************************************************************************/ 

CCDC *CCDC::ConvertFromNativeDC( CNativeDC* pDC )
{
	if (!pDC)
		return NULL;

	// Scan the DCList to find the item
	CCDC * pItem = (CCDC*)s_DCList.GetHead();
	while (pItem)
	{
		if (pItem->GetDC() == pDC)
			return pItem;

		pItem = (CCDC*)s_DCList.GetNext(pItem);
	}

	return NULL;
}

/*********************************************************************************************

>	static UINT32 CCDC::GetRectangleList( CDC*, wxRect **lpRect )

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/10/93
	Inputs:		None
	Outputs:	lpRect will point to a rectangle list. XRECT is a 32-bit rectangle, defined
				in gdimagic.h
	Returns:	Number of rectangles in list, or 0 for don't know.
	Purpose:	The whole point of CCDCs over normal CDCs is to get additional information.
				This call allows access to the clipping rectangle list. A zero return is not
				an error, it just means that the rectangle list is not known.
	Errors:		-
	Scope:	    Public

*********************************************************************************************/ 

UINT32 CCDC::GetRectangleList( wxDC* pCDC, wxRect **lpRect)
{
	const CCDC *pCCDC = ConvertFromNativeDC(pCDC);

	if (pCCDC == NULL)
		return 0;										// if not a CCDC

#ifndef EXCLUDE_FROM_XARALX
	// Multi-region draw hints are only supported on MSW
#if defined( __WXMSW__ )
	if (pCCDC->lpRgnData && (pCCDC->lpRgnData->rdh.iType == RDH_RECTANGLES) )
	{
		*lpRect = (wxRect *)( &pCCDC->lpRgnData->Buffer );	// the address of the rectangle list
		return (UINT32)(pCCDC->lpRgnData->rdh.nCount);
	}
#endif
#endif
	return 0;
}

/*********************************************************************************************

>	static RenderType CCDC::GetType( CDC* pCDC, BOOL bCalculate)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/10/93
	Inputs:		Pointer to a wxDC, bCalculate makes it return a valid type for wxDCs by
				asking GDI what the pCDC really points to. If bCalculate is FALSE and pCDC
				cannot be safely cast to a CCDC, returns RENDERTYPE_NONE as we cannot tell.
	Outputs:	None
	Returns:	The type of the CCDC
	Purpose:	Get an indication of the type of the render destination.
	Errors:		-
	Scope:	    Public
	SeeAlso:	RenderType

*********************************************************************************************/ 

RenderType CCDC::GetType( CNativeDC* pDC, BOOL bCalculate)
{
	const CCDC *pCCDC = ConvertFromNativeDC( pDC );

	if (pCCDC == NULL)
	{
		PORTNOTETRACE("other","CCDC::GetType - can't calculate device type yet");
#ifndef EXCLUDE_FROM_XARALX
		if (bCalculate)
		{
			// work out the type from the HDC if he can. We don't use the MFC fn as
			// it gets the type from the attrib, not the actual HDC, though this screws
			// up with Print Preview
			switch ( ::GetDeviceCaps( pDC->m_hDC, TECHNOLOGY ) )
			{
				case DT_RASDISPLAY:
					return RENDERTYPE_SCREEN;

				case DT_PLOTTER:
				case DT_RASPRINTER:
					// Need to detect if this is a PostScript printer - this requires
					// different code on different OSs.
					// (This code taken from MSDN - PSS ID Number: Q124135)
					WORD wEscape;					

					if (IsWin32NT() || IsWin32c())
					{
						wEscape = POSTSCRIPT_PASSTHROUGH; // Fails with Win16 driver
						if (pDC->Escape(QUERYESCSUPPORT, sizeof(WORD), (LPCSTR) &wEscape, NULL) > 0)
						{
							// Found a PS printer
							return RENDERTYPE_PRINTER_PS;
						}
					}
					else if (IsWin32s())
					{
						// use printer escape to determine printer type.
						wEscape = GETTECHNOLOGY;
						if (pDC->Escape(QUERYESCSUPPORT, sizeof(WORD), (LPCSTR) &wEscape, NULL) > 0)
						{
							// Supports Escapes - get the technology info.
							char Technology[256];
							pDC->Escape(GETTECHNOLOGY, 0, NULL, 255, Technology);

							// Does the technology description start with "postscript"?
							if (_tcsncicmp(Technology, "postscript", 10) == 0)
							{
								// Ok - does it support passthrough?
								wEscape = PASSTHROUGH;
								if (pDC->Escape(QUERYESCSUPPORT, sizeof(WORD), 
												 (LPCSTR) &wEscape, NULL) > 0)
								{
									// Found a PS printer
									return RENDERTYPE_PRINTER_PS;
								}
							}

							// GETTECHNOLOGY might not work on some printer drivers, so
							// try another escape - EPSPRINTING - should only work on PS!
							wEscape = EPSPRINTING;
							if (pDC->Escape(QUERYESCSUPPORT, sizeof(WORD), (LPCSTR) &wEscape, NULL) > 0)
							{
								// Supports EPS printing - must be PostScript.
								return RENDERTYPE_PRINTER_PS;
							}
						}
					}

					// If we've got here its a normal (non-PS) printer.
					return RENDERTYPE_PRINTER;

				case DT_METAFILE:
					return RENDERTYPE_METAFILE16;				// 32-bit metafiles return their
																// context device, which we
																// cannot create anyway as yet
			}
		}
#endif

		return RENDERTYPE_NONE;
	}

	// its an actual CCDC so its type is well-known
	return pCCDC->Type;
}

/*********************************************************************************************

>	static BOOL CCDC::IsPaperWanted( RenderType )

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/10/93
	Inputs:		Type of rendering device
	Outputs:	None
	Returns:	TRUE if the device wants paper rendered (pages, backgrounds etc), FALSE
				if it does not.
	Purpose:	Used by the document renderer to decide whether paper-like things should be
				drawn.
	Errors:		-
	Scope:	    Public

*********************************************************************************************/ 

BOOL CCDC::IsPaperWanted( RenderType rType )
{
	switch (rType)
	{
		case RENDERTYPE_SCREEN:
		case RENDERTYPE_SCREENXOR:
			return TRUE;

		case RENDERTYPE_PRINTER:
			return FALSE;

		case RENDERTYPE_MONOBITMAP:
			return FALSE;
		
		case RENDERTYPE_HITDETECT:
			return FALSE;
		
		case RENDERTYPE_COLOURBITMAP:
			return TRUE;

		case RENDERTYPE_METAFILE16:
		case RENDERTYPE_METAFILE32:
			return FALSE;

		default:
			TRACE( _T("Bad rendertype %d in IsPaperWanted\n"), rType );
			return TRUE;
	}
}


BOOL CCDC::CleanUpDCs(void)
{
	// Delete all the entries in the list (the item destructors will delete the DCs)
	s_DCList.DeleteAll();

	return(TRUE);
}


void CCDC::SetDC (CNativeDC * dc, BOOL bDeleteDC /*= TRUE*/)
{
	if (m_pDC == dc)
		return;

	if (m_pDC)
	{
		if (m_bDeleteDC)
			delete (m_pDC);
		// take us off the list
		s_DCList.RemoveItem(this);
	}
	m_pDC = dc;
	if (m_pDC)
	{
		m_bDeleteDC = bDeleteDC;
		// put us on the list
		s_DCList.AddTail(this);
	}
}

/********************************************************************************************

>	class CCPaintDC : public CCDC

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/11/93
	Purpose:	Similar to a CPaintDC but also gives us the functionality of a CCDC. In
				particular we can get at the clipping rectangle list.
	SeeAlso:	CCDC;CPaintDC

********************************************************************************************/


/*********************************************************************************************

>	CCPaintDC::CCPaintDC(CWnd* pWnd)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/10/93
	Inputs:		Pointer to owner window.
	Outputs:	None
	Returns:	None
	Purpose:	Constructor for CCPaintDC which gets the update rectangle list before doing
				a BeginPaint.
	Errors:		-
	Scope:	    Public
	SeeAlso:	CCDC;RenderType

*********************************************************************************************/ 

CCPaintDC::CCPaintDC(wxWindow *pWnd) : CCDC(RENDERTYPE_SCREEN), m_DC(pWnd)
{
	// Register this DC with the DC type system and set that it is temporary
	CCDC::SetDC(&m_DC, FALSE);

#ifndef EXCLUDE_FROM_XARALX
	// Loose the old region data
	CCFree( lpRgnData );
	lpRgnData = NULL;

	// Setup the DC
//	m_pDc		= this;
	m_clipping	= true;

#if defined(__WXMSW__)
	// before the BeginPaint we must extract
	// the update region. This is so we can more efficiently paint the window, especially after
	// diagonal scrolls.
	HRGN				hRgn = CreateRectRgn(0,0,0,0);
	if( hRgn )
	{
		INT32 result = ::GetUpdateRgn( HWND(pWnd->GetHandle()), hRgn, FALSE );
		if (result==COMPLEXREGION)
		{
			// How many regions are there in there
			DWORD res = GetRegionData( hRgn, 0, NULL );

			// If there are some and there are less than our limit then get the info about them
			if ((res!=0) && (res<MAX_REGIONS))
			{
				// alloc space to put the region data in
				lpRgnData = (LPRGNDATA)CCMalloc( res );
				if (lpRgnData)
				{
					// alloced buffer - use it
					lpRgnData->rdh.dwSize = sizeof(RGNDATAHEADER);
					DWORD newres = GetRegionData( hRgn, res, lpRgnData );

					// Note GetRegionData is documented wrongly - when it works it returns the size, not 1
					if (newres!=res)
					{
						// error occurred somehow so tidy up heap
						CCFree( lpRgnData );
						lpRgnData = NULL;

						if (newres!=0)
							TRACE( _T("GetRegionData changed from %lu to %lu\n"), res, newres);
					}
				}
			}
		}
		DeleteObject( hRgn );
	}
#endif
#endif
}


/*********************************************************************************************

>	CCPaintDC::~CCPaintDC()

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/10/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Destructor for CCPaintDC which does an EndPaint.
	Errors:		-
	Scope:	    Public

*********************************************************************************************/ 

CCPaintDC::~CCPaintDC()
{
}

/*********************************************************************************************

>	CCClientDC::CCClientDC(CWnd* pWnd)

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/10/93
	Inputs:		Pointer to owner window.
	Outputs:	None
	Returns:	None
	Purpose:	Constructor for CCClientDC which gets the update rectangle list before doing
				a BeginPaint.
	Errors:		-
	Scope:	    Public
	SeeAlso:	CCDC;RenderType

*********************************************************************************************/ 

CCClientDC::CCClientDC(wxWindow *pWnd) : CCDC(RENDERTYPE_SCREEN), m_DC(pWnd)
{
	// Register this DC with the DC type system and set that it is temporary
	CCDC::SetDC(&m_DC, FALSE);
}


/*********************************************************************************************

>	CCClientDC::~CCClientDC()

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/10/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Destructor for CCClientDC which does an EndPaint.
	Errors:		-
	Scope:	    Public

*********************************************************************************************/ 

CCClientDC::~CCClientDC()
{
}
