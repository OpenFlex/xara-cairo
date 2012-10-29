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


// defines simple operation(s) to control GBrush features

#ifndef INC_GBRUSHOP
#define	INC_GBRUSHOP


/******************************************************************************************

>	class OpGBrush : public Operation

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/4/94
	Purpose:	Operation to toggle GBrush setting
	Notes:		Will be on a dialog somewhere eventually

********************************************************************************************/				

class OpGBrush : public Operation
{
	CC_DECLARE_DYNCREATE( OpGBrush )

public:
	OpGBrush();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);	
};

#define	OPTOKEN_GBRUSH	_T("GBrushToggle")

#endif
