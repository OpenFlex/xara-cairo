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


#ifndef INC_ANIMPARAMS
#define INC_ANIMPARAMS

#include "ops.h"
#include "paldefs.h"

/*******************************************************************************************************

  class FramePropertiesParam : publc OpParam

  Author:	Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
  Created:	30/04/97
  Purpose:	Allows the transfer of data from our Frame Gallery to our current layer object.
				
********************************************************************************************************/

class FramePropertiesParam: public OpParam
{

//	CC_DECLARE_DYNAMIC(FramePropertiesParam)

public:
	FramePropertiesParam();

	String_256& GetFrameName()								{ return m_FrameName;	};
	void		SetFrameName(const String_256& Name)		{ m_FrameName = Name;	};
	UINT32		GetAnimDelay () const						{ return m_FrameDelay;	};
	void		SetAnimDelay(const UINT32& Delay)			{ m_FrameDelay = Delay; };
	BOOL		GetOverlay()								{ return m_Overlay;		};
	void		SetOverlay (const BOOL& Val)				{ m_Overlay = Val;		};
	BOOL		GetSolid()									{ return m_Solid;		};
	void		SetSolid (const BOOL& Val)					{ m_Solid = Val;		};

protected:
	String_256 m_FrameName;				// Name of the selected bitmap.
	UINT32	   m_FrameDelay;			// Delay between frames for Animations.
	BOOL m_Overlay;						// Set if the previous layer is said to overlay the
										//	previous one rathar than  obscure it.
	BOOL m_Solid;						// A solid frame/layer is like a background layer in
										// that it forms the background for frames above it.
};


/*******************************************************************************************************

  class AnimPropertiesParam : publc OpParam

  Author:	Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
  Created:	30/04/97
  Purpose:	Allows the transfer of data from our Frame Gallery to a current spread object.
				
********************************************************************************************************/
class AnimPropertiesParam: public OpParam
{
	CC_DECLARE_DYNAMIC(AnimPropertiesParam)

public:
	AnimPropertiesParam();

	DWORD			GetAnimLoop()const							{ return m_Animloop;			};
	void			SetAnimLoop(const DWORD& Loop)				{ m_Animloop = Loop;			};
	DWORD			GetGlobalAnimDelay() const					{ return m_GlobalAnimDelay;		};
	void			SetGlobalanimDelay(const DWORD& Delay)		{ m_GlobalAnimDelay = Delay;	};
	DITHER			GetDither()const							{ return m_Dither;				};
	void			SetDither(const DITHER& dither)				{ m_Dither = dither;			};
	WEB_PALETTE		GetPalette() const							{ return m_Palette;				};
	void			SetPalette(const WEB_PALETTE& Palette)		{ m_Palette = Palette;			};
	DWORD			GetNumColsInPalette() const					{ return m_NumColsInPalette;	};
	void			SetNumColsInPalette(const DWORD& num)		{ m_NumColsInPalette = num;		};
	PALETTE_COLOURS	GetPaletteCols() const						{ return m_PaletteColours;		};
	void			SetPaletteCols(const PALETTE_COLOURS& Pal)	{ m_PaletteColours = Pal;		};
	BOOL 			GetUseSystemCols() const					{ return m_UseSystemColours;	};
	void			SetUseSystemCols(const BOOL &Val)			{ m_UseSystemColours = Val;		};
	BOOL 			GetIsBackGroundTransp() const				{ return m_BackGroundIsTransp;	};
	void			SetIsBackGroundTransp(const BOOL &Val)		{ m_BackGroundIsTransp = Val;	};

	AnimPropertiesParam& operator=(const AnimPropertiesParam& obj);

protected:

	DWORD			m_Animloop;	
	DWORD		 	m_GlobalAnimDelay; 		
	DITHER			m_Dither;				// Dither type
	WEB_PALETTE		m_Palette;				// Global\Local
	PALETTE_COLOURS m_PaletteColours;		// Browser\Optimised
	DWORD			m_NumColsInPalette;
	BOOL			m_UseSystemColours;
	BOOL			m_BackGroundIsTransp;

public:
	// Stores and gives access to the bounding rectangle of the export
	// If this changes then we will need to regenerate all frames
	void			SetBoundingRect(const DocRect& BoundingRect)	{ m_BoundingRect = BoundingRect; };
	DocRect			GetBoundingRect() const							{ return m_BoundingRect;		};
	
	// Stores and gives access to the capture quality of the export
	// If this changes then we will need to regenerate all frames
	void			SetAnimationQuality(const Quality& NewQuality)	{ m_Quality = NewQuality; };
	Quality			GetAnimationQuality() const						{ return m_Quality;		};

protected:
	DocRect			m_BoundingRect;
	Quality			m_Quality;
};

#endif	// INC_ANIMPARAMS

