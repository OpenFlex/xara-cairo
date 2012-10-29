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


// Headers for the brush message and message handler classes

#ifndef BRUSHMSG
#define BRUSHMSG

#include "brshcomp.h"

/********************************************************************************************

>	class BrushMsg: public Msg

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/3/94
	Purpose:	A message broadcast by a brush when it becomes selected as the default brush 
	SeeAlso:	-

********************************************************************************************/

class BrushMsg: public Msg
{
	CC_DECLARE_DYNAMIC(BrushMsg); 

public:	
	BrushMsg() {m_BrushSelected = BrushHandle_NoBrush;}
	BrushMsg(BrushHandle Handle) {m_BrushSelected = Handle;}

	BrushHandle m_BrushSelected;

};

/********************************************************************************************

>	class ScreenChangeMsg: public Msg

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/3/94
	Purpose:	A message to be broadcast whenever what is on the screen changes.  This can be
				a dialog closing, or scrollbar moving or object being moved.  It is vital to 
				the brush that it be informed whenever something like this happens
	SeeAlso:	Currently the only place this message is received is in the freehand info bar

********************************************************************************************/

class ScreenChangeMsg: public Msg
{
	CC_DECLARE_DYNAMIC(ScreenChangeMsg); 

public:	
	ScreenChangeMsg() {m_bClear = FALSE;}
	ScreenChangeMsg(BOOL Clear) {m_bClear = Clear;}
	BOOL m_bClear; 
};


/********************************************************************************************

>	class BrushDefMsg: public Msg

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/3/94
	Purpose:	A message broadcast when a brush definition is edited.  This enables things
				that represent the brush definition (such as the combo in the freeinfobar) to 
				update themselves
	SeeAlso:	-

********************************************************************************************/

class BrushDefMsg: public Msg
{
	CC_DECLARE_DYNAMIC(BrushDefMsg); 

public:	
	BrushDefMsg() {m_BrushEdited = BrushHandle_NoBrush;}
	BrushDefMsg(BrushHandle Handle) {m_BrushEdited = Handle;}

	BrushHandle m_BrushEdited;

};


/********************************************************************************************

>	class NewBrushMsg: public Msg

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/3/94
	Purpose:	A message broadcast when a new brush is created from the Brush edit dialog. It
				should be picked up by the Freehand infobar and used to update its brush list.
	SeeAlso:	-

********************************************************************************************/

class NewBrushMsg : public Msg
{
	CC_DECLARE_DYNAMIC(NewBrushMsg);

public:
	NewBrushMsg() {}

};

/********************************************************************************************

>	class StrokeMsg: public Msg

	Author:		Diccon_Yamanaka (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/3/94
	Purpose:	A message broadcast by a Stroke when it becomes selected as the default Stroke 
	SeeAlso:	-

********************************************************************************************/

class StrokeMsg: public Msg
{
	CC_DECLARE_DYNAMIC(StrokeMsg); 

public:	
	StrokeMsg() {}

};
#endif
