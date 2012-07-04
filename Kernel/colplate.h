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

// colplate.h - Definitions for colour separations in ColourContexts


#ifndef INC_COLPLATE
#define INC_COLPLATE

//#include "doccolor.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "listitem.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class IndexedColour;


typedef enum
{
	COLOURPLATE_NONE,			// No colour plate (normal rendering operation)

	COLOURPLATE_COMPOSITE,		// Composite print-preview (colour matching)

	COLOURPLATE_CYAN,			// Process colour separation plates
	COLOURPLATE_MAGENTA,
	COLOURPLATE_YELLOW,
	COLOURPLATE_KEY,

	COLOURPLATE_SPOT			// Spot colour separation plate
} ColourPlateType;



/********************************************************************************************

>	typedef enum ScreenType

	Author:		Mike_Kenny (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/6/95
	Purpose:	enumeration of the screen types we support inside a plate

********************************************************************************************/

typedef enum ScreenType
{
	SCRTYPE_NONE,
	SCRTYPE_SPOT1,
	SCRTYPE_SPOT2,
	SCRTYPE_TRIPLESPOT1,
	SCRTYPE_TRIPLESPOT2,
	SCRTYPE_ELLIPTICAL,
	SCRTYPE_LINE,
	SCRTYPE_CROSSHATCH,
	SCRTYPE_MEZZOTINT,
	SCRTYPE_SQUARE,
	SCRTYPE_DITHER
};


/********************************************************************************************
 
>	class ColourPlate : public ListItem

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Date:		20/12/95

	Purpose:	The ColourPlate class is used as a descriptor defining how a colour context
				should separate/filter a colour as it is converted.

				The ColourPlate indicates what type of separation plate is required, e.g
				none, cyan, or spot. In the case of a spot plate, the ColourPlate also
				retains a pointer to the spot colour for which a plate is required.

				A flag is available, Negate, which controls if a normal or "photographic
				negative" plate is required.

	Notes:		You can't change a colour plate "on the fly", as you must attach a new 
				one to a colour context in order to make caching of colours work
				correctly. Thus, to change the plate, you must build a new one.

	SeeAlso:	ColourContext::SetColourPlate

 ********************************************************************************************/

class ColourPlate : public ListItem
{
	CC_DECLARE_DYNCREATE(ColourPlate);

public:		// Construction/destruction
	ColourPlate();
	virtual ~ColourPlate();

	ColourPlate(ColourPlateType TheType, BOOL MonochromePlate = FALSE, BOOL NegatePlate = FALSE);
	ColourPlate(IndexedColour *SpotColour, BOOL MonochromePlate = FALSE, BOOL NegatePlate = FALSE);

	ColourPlate(const ColourPlate &Other);
	ColourPlate &operator=(const ColourPlate &Other);


public:		// Special user-interface functions
	void GetDescription(StringBase *Description);
			// Gets a description of this colour plate (e.g. "Cyan", "Gold (Spot)")

	void GetDisplayColour(DocColour *Colour);
			// Gets a display colour to be used when showing a colour patch display
			// for this plate.


public:		// Retrieving current settings
	BOOL IsDisabled(void)				{ return(Disabled); };
			// Returns TRUE if this plate is temporarily disabled

	ColourPlateType GetType(void)		{ return(Type); };
			// Gets the colour plate type that this object represents

	IndexedColour  *GetSpotColour(void)		// Gets the spot colour (if any) which this spot plate contains
	{
		return(Spot.FindParentIndexedColour()); 
	};
	
	BOOL IsMonochrome(void)				{ return(Monochrome); };
			// Returns TRUE if this plate should contain only monochromatic values
	
	BOOL IsNegative(void) 				{ return(Negate); };
			// Returns TRUE if this plate is a photographic negative

	double GetScreenAngle(void)			{ return(ScreenAngle); };
			// Returns the screen angle (0..360 degrees)

	double GetScreenFrequency(void)		{ return(ScreenFrequency); };
			// Returns the screen frequency

	ScreenType GetScreenFunction(void)	{ return(ScreenFunction); };
			// Returns the screen function
	
	BOOL ActiveScreening(void)			{ return(ActiveScreens); };
			// Returns TRUE if this plate uses screening

	BOOL Overprints(void)				{ return(Overprint); };
			// Returns TRUE if graphics (non-text) objects should overprint


public:		// Changing current settings - use as infrequently as possible
	void SetDisabled(BOOL IsDisabled = TRUE);
			// Disables/enables the output of this plate. This has 2 uses:
			// 1. Stops the plate being printed by the main print loop
			// 2. If the plate is rendered, can be used as a temporary flag to stop
			//    colour separation and correction during output.

	void SetPlateInfo(ColourContext *Parent, ColourPlateType TheType,
						BOOL MonochromePlate = FALSE, BOOL NegatePlate = FALSE);

	void SetPlateInfo(ColourContext *Parent, IndexedColour *SpotColour,
						BOOL MonochromePlate = FALSE, BOOL NegatePlate = FALSE);

	void SetType(ColourContext *Parent, ColourPlateType TheType, IndexedColour *SpotColour = NULL);
			// Set this plate to be of a particular type

	void SetScreenInfo(double Angle, double Frequency);
			// Sets screen angle/frequency for this plate
	
	void SetScreenFunction(ScreenType func);
			// Sets screen type for this plate

	void SetActiveScreening(BOOL On = TRUE);
			// Turns on screen usage for this plate

	void SetOverprint(BOOL On = TRUE);
			// Enable/Disable overprint for this plate

	void SetMonochrome(ColourContext *Parent, BOOL On = TRUE);
			// Force all output to be monochrome (print) or plate-coloured (preview)

	void SetNegative(ColourContext *Parent, BOOL On = TRUE);
			// Force all output to be photographically negated (or normal)

	void ResetScreenToDefaults(INT32 DeviceDPI = 1200, INT32 DefaultFrequency = 60);
			// Makes this colour plate reset to recommended screen angle settings for
			// the current printer resolution (dpi) and screen frequency (lpi)


protected:	// Internal helper functions
	void InitObject(ColourPlateType NewType);
			// Sets a new Type for this plate, and initisalises all other member variables
			// to sensible default values for the given plate type.


protected:	// Internal data
	BOOL Disabled;					// TRUE if this ColourPlate is disabled (used to temporarily turn
									// off colour separation for specific colours like UI/EOR DocColours)

	ColourPlateType Type;			// The type of separation/plate desired


	DocColour Spot;					// References the spot colour (spot plates only)

	double ScreenAngle;				// The screen angle for this plate
	double ScreenFrequency;			// The screen frequency for this plate

	BOOL Overprint;					// TRUE if this plate should overprint, FALSE if it should knock-out
	BOOL Monochrome;				// TRUE if the plate should contain only monochromatic shades
									// (if FALSE, e.g. a Cyan separation will be shades of Cyan)
	BOOL Negate;					// TRUE if the plate should be a negative image
	BOOL ActiveScreens;				// TRUE if the screening is active

	ScreenType	ScreenFunction;		// The screen function to use (Spot1/Spot2 etc)
};

#endif			// INC_COLPLATE


