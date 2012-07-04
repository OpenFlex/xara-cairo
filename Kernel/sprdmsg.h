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

// Spread message

#ifndef INC_SPRDMSG
#define INC_SPRDMSG

//#include "msg.h" - in camtypes.h [AUTOMATICALLY REMOVED]


/*********************************************************************************************
>	class SpreadMsg : public Msg

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	2/8/94
	Purpose:	This is sent when a spread event is happening that may be of interest
				to all you message handlers out there.

				At the moment, the only reason defined is the SELCHANGED reason.  This is sent
				when the selected spread has changed, either by the user selecting an object in
				a spread, or by clicking on a spread's background causing the selection to
				disappear in another spread

*********************************************************************************************/

	

class SpreadMsg : public Msg
{
	CC_DECLARE_DYNAMIC(SpreadMsg)

public:

	// Spread messages are send with these reasons
	enum SpreadReason
	{
		SELCHANGED,				// Sent when the selected spread changes
								// pOldSpread = ptr to the old selected spread
								// pNewSpread = ptr to the new selected spread
								// The new selected spread could belong to a document that
								// is different to the one belonging to the old selected spread
								// pOldSpread and/or pNewSpread can be NULL

		LAYERCHANGES,			// The layers of a spread have changed.
								// pOldSpread = pNewSpread = spread whose layers have changed

		ANIMATIONPROPERTIESCHANGED	// The animation properties of a spread have changed.
									// pOldSpread = pNewSpread = spread whose layers have changed
	};

	Spread*			pOldSpread;
	Spread*			pNewSpread;
	SpreadReason 	Reason;		// The message specifics, as enumerated above

	SpreadMsg(Spread* pThisOldSpread, Spread* pThisNewSpread, SpreadReason ThisReason)
	  : pOldSpread(pThisOldSpread), pNewSpread(pThisNewSpread), Reason(ThisReason) { /* empty */ }

	SpreadMsg(Spread* pThisSpread, SpreadReason ThisReason)
	  : pOldSpread(pThisSpread), pNewSpread(pThisSpread), Reason(ThisReason) { /* empty */ }
};


#endif

