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


#ifndef INC_SPEEDTST
#define	INC_SPEEDTST


#define	OPTOKEN_TIMEDRAW		_T("TimeDraw")
#define	OPTOKEN_CLEARCACHE		_T("ClearCache")
#define	OPTOKEN_THROTTLECACHE	_T("ThrottleCache")

class OpDescriptor;

/*******************************************************************************************

>	class OpTimeDraw : public Operation

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/1/94
	Purpose:	To allow easier timing of window redraws
	Notes:		In the OIL

********************************************************************************************/

class OpTimeDraw : public Operation
{
	CC_DECLARE_DYNCREATE( OpTimeDraw )

public:
	OpTimeDraw();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);
};

/*******************************************************************************************

>	class OpClearCache : public Operation

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/06/2004
	Purpose:	To allow comparitive timing of window redraws
	Notes:		In the OIL

********************************************************************************************/

class OpClearCache : public Operation
{
	CC_DECLARE_DYNCREATE( OpClearCache )

public:
	OpClearCache();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);
};

/*******************************************************************************************

>	class OpThrottleCache : public Operation

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/06/2004
	Purpose:	To allow comparitive timing of window redraws
	Notes:		In the OIL

********************************************************************************************/

class OpThrottleCache : public Operation
{
	CC_DECLARE_DYNCREATE( OpThrottleCache )

public:
	OpThrottleCache();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);
};

#endif

