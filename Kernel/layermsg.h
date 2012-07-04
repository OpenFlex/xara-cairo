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

// Layer message

#ifndef INC_LAYERMSG
#define INC_LAYERMSG

//#include "msg.h" - in camtypes.h [AUTOMATICALLY REMOVED]


/*********************************************************************************************
>	class LayerMsg : public Msg

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/10/95
	Purpose:	Messages detailing specific changes to layers

*********************************************************************************************/
	

class LayerMsg : public Msg
{
	CC_DECLARE_DYNAMIC(LayerMsg)

public:

	// Layer messages are send with these reasons
	enum LayerReason
	{
		LAYER_VISIBILITY_CHANGED,//new (sjk) inform anyone who is interested that someone
								// has changed what layers are visible.
								// pNewLayer == pOldLayer == layer of interest
		ACTIVE_LAYER_CHANGED,	// The active layer has changed.
								// pOldLayer = ptr to the old active layer (can be NULL)
								// pNewLayer = ptr to new active layer (should never be NULL)

		GUIDELINES_CHANGED,		// The guidelines in a layer have changed in some way
								// E.g. guideline has been moved/created/deleted etc
								// pNewLayer == pOldLayer == layer of interest
		UPDATE_ACTIVE_LAYER,	// The active layer has been changed outside the gallery.
								// This tells the gallery to update its idea of what is selected. 
								// pNewLayer = ptr to new active layer (should never be NULL)
		REDRAW_LAYER			// The layer has been changed outside the gallery.
								// This tells the gallery to redraw the item on display.
								// At present, used in debug versions to show edited layers.
								// pNewLayer = ptr to new active layer (should never be NULL)
	};

	Layer*			pOldLayer;
	Layer*			pNewLayer;
	LayerReason 	Reason;		// The message specifics, as enumerated above

	LayerMsg(Layer* pThisOldLayer, Layer* pThisNewLayer, LayerReason ThisReason)
	  : pOldLayer(pThisOldLayer), pNewLayer(pThisNewLayer), Reason(ThisReason) { /* empty */ }

	LayerMsg(Layer* pThisLayer, LayerReason ThisReason)
	  : pOldLayer(pThisLayer), pNewLayer(pThisLayer), Reason(ThisReason) { /* empty */ }
};


#endif // INC_LAYERMSG
