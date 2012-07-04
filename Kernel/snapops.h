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

// Ops that are associated with snapping

#ifndef INC_SNAPOPS
#define INC_SNAPOPS

//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#define	OPTOKEN_SHOWGRID		_T("ShowGrid")
#define	OPTOKEN_SNAPTOGRID		_T("SnapToGrid")

// WEBSTER - markn 15/1/97
// Removed some op that no longer used in Webster
#ifndef WEBSTER
#define	OPTOKEN_SHOWGUIDES		_T("ShowGuides")
#define	OPTOKEN_SNAPTOOBJECTS	_T("SnapToObjects")
#define	OPTOKEN_SNAPTOGUIDES	_T("SnapToGuides")
#endif

class OpDescriptor;

/*******************************************************************************************

>	class OpShowGrid : public Operation

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/2/94
	Purpose:	Allows the user to toggle the visible state of all grids.
	Notes:		-

********************************************************************************************/

class OpShowGrid : public Operation
{
	CC_DECLARE_DYNCREATE( OpShowGrid )

public:
	OpShowGrid();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);
};


/*******************************************************************************************

>	class OpSnapToGrid : public Operation

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	11/2/94
	Purpose:	Allows the user to toggle snap-to-grid on and off.
	Notes:		-

********************************************************************************************/

class OpSnapToGrid : public Operation
{
	CC_DECLARE_DYNCREATE( OpSnapToGrid )

public:
	OpSnapToGrid();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);
};

// WEBSTER - markn 15/1/97
// Removed some op that no longer used in Webster
#ifndef WEBSTER

/*******************************************************************************************

>	class OpSnapToObjects : public Operation

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/9/94
	Purpose:	Allows the user to toggle snap-to-objects on and off.
	Notes:		-

********************************************************************************************/

class OpSnapToObjects : public Operation
{
	CC_DECLARE_DYNCREATE( OpSnapToObjects )

public:
	OpSnapToObjects();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);
};

/*******************************************************************************************

>	class OpSnapToGuides : public Operation

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/9/95
	Purpose:	Allows the user to toggle snap-to-guides on and off.
	Notes:		-

********************************************************************************************/

class OpSnapToGuides : public Operation
{
	CC_DECLARE_DYNCREATE( OpSnapToGuides )

public:
	OpSnapToGuides();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);
};

/*******************************************************************************************

>	class OpShowGuides : public Operation

	Author:		Mark_Neves (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/9/95
	Purpose:	Allows the user to toggle the visible state of all guides.
	Notes:		-

********************************************************************************************/

class OpShowGuides : public Operation
{
	CC_DECLARE_DYNCREATE( OpShowGuides )

public:
	OpShowGuides();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);
};

#endif  // WEBSTER
#endif  // INC_SNAPOPS
