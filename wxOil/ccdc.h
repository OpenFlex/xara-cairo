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


// CC version of a wxDC

#ifndef INC_CCDC
#define	INC_CCDC



class CCDC : public ListItem
{
	CC_DECLARE_DYNAMIC( CCDC )

public:
	CCDC( RenderType = RENDERTYPE_NONE);
	CCDC( CNativeDC*, RenderType = RENDERTYPE_NONE );
	~CCDC();

protected:
	RenderType Type;				// type of device being rendered to
	LPRGNDATA lpRgnData;			// NULL if none
	CNativeDC * m_pDC;
	BOOL m_bDeleteDC;

public:
	CNativeDC* GetDC() const { return(m_pDC); }
	operator CNativeDC & () { return (*m_pDC); }
	void SetDC (CNativeDC * dc, BOOL bDeleteDC = TRUE);
	RenderType GetRenderType() const { return Type; }

	virtual BOOL IsPrinting() const { return (Type == RENDERTYPE_PRINTER) || (Type == RENDERTYPE_PRINTER_PS); }

	static UINT32 GetRectangleList(wxDC*, wxRect**);
	static RenderType GetType(CNativeDC*, BOOL);
	static BOOL IsPaperWanted(RenderType);
	static BOOL CleanUpDCs(void);
	static CCDC *ConvertFromNativeDC( CNativeDC* pDC );



protected:
	static List s_DCList;
};

class CCPaintDC : public CCDC
{
	CC_DECLARE_DYNAMIC( CCPaintDC )
public:
	CCPaintDC( wxWindow * );
	~CCPaintDC();

private:
	wxPaintDC m_DC;
};

class CCClientDC : public CCDC
{
	CC_DECLARE_DYNAMIC( CCClientDC )
public:
	CCClientDC( wxWindow * );
	~CCClientDC();

private:
	wxClientDC m_DC;
};

class CCDummyDC : public CCDC
{
	CC_DECLARE_DYNAMIC( CCDummyDC )
public:
	CCDummyDC(RenderType r = RENDERTYPE_NONE) : CCDC(r) { SetDC(&m_DC, FALSE); }
	CCDummyDC(CNativeDC * pNativeDC, RenderType r = RENDERTYPE_NONE) : CCDC(pNativeDC, r) { }
	~CCDummyDC() { }

private:
	wxMemoryDC m_DC;
};


#endif
