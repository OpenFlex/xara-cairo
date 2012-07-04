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

#ifndef _INC_AI_LAYER_H
#define _INC_AI_LAYER_H

// Forward definitions.
class AI5EPSFilter;
class String256;

/********************************************************************************************

>	class AILayerProcessor : public CCObject  

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	14/4/00
	Purpose:	Helps with the import of an Adobe Illustrator layer. These are defined by a
				pair of instructions:

				<Flags>			Lb
				(Layer Name)	Ln

				The layer body is terminated by the LB tag.

********************************************************************************************/

class AILayerProcessor : public CCObject
{
	CC_DECLARE_DYNAMIC ( AILayerProcessor )

public:
	AILayerProcessor  ( void );					// Constructor.
	~AILayerProcessor ( void );					// Destructor.

	// Functions for decoding EPS operations.
	BOOL DecodeAI5Lb( AI5EPSFilter	&Filter );	// Decode the Lb operator.
	BOOL DecodeAI8Lb( AI5EPSFilter	&Filter );	// Decode the Lb operator.
	BOOL DecodeLB	( AI5EPSFilter	&Filter );	// Decode the LB operator.
	BOOL DecodeLn	( AI5EPSFilter	&Filter );	// Decode the Ln operator.

private:
	String_256	mLayerName;						// The name of the layer.
	BOOL		mIsLocked;						// Is the layer locked?
	BOOL		mIsPrintable;					// Is the layer printable?
	BOOL		mIsVisible;						// Is the layer visible?
};

#endif // _INC_AI_LAYER_H
