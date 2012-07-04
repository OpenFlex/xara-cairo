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

// 


#include "camtypes.h"
//#include "list.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "tmpltarg.h"

#if defined( __WXMSW__ )
#include <comcat.h>		// should be in the slick oil registry.cpp
#endif

//#include "registry.h"
//#include "app.h" - in camtypes.h [AUTOMATICALLY REMOVED]


/********************************************************************************************

>	class WizOpProbe : public ClassCategoryProbe

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com> (from assorted dialog classes)
	Created:	09/06/97

	Purpose:	Searches through the (local) registry returning entries in the WizOp 
				category.

********************************************************************************************/
PORTNOTE("other","Removed WizOpProbe - derived from ClassCategoryProbe")
#ifndef EXCLUDE_FROM_XARALX
class WizOpProbe : public ClassCategoryProbe
{
protected:
	virtual const CATID& GetCategoryID() const	{	return s_WizOpCategoryCLSID;	}

private:
	static const CATID s_WizOpCategoryCLSID;
};
#endif


/********************************************************************************************

>	class WizOpRegistryEntry : public ClassRegistryEntry

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com> (from assorted dialog classes)
	Created:	09/06/97

	Purpose:	When the WizOpProbe returns a ClassRegistryEntry it returns one of these
				which can then be used to extract WizOp specific bits from the registry.

********************************************************************************************/
PORTNOTE("other","Removed WizOpRegistryEntry - derived from ClassRegistryEntry")
#ifndef EXCLUDE_FROM_XARALX
class WizOpRegistryEntry : public ClassRegistryEntry
{
public:
	BOOL GetInternalName(StringBase* const pValue);
	BOOL GetUserName(StringBase* const pValue);
	BOOL GetParamHint(StringBase* const pValue);

private:
//	static const String_8 s_InternalNameKey;
	static const String_16 s_UserNameKey;
	static const String_16 s_ParamHintKey;
};
#endif

// Place any IMPLEMENT type statements here
CC_IMPLEMENT_MEMDUMP(WizOp, ListItem)
CC_IMPLEMENT_MEMDUMP(WizOps, List)

PORTNOTE("other","Removed bulk of WizOp*")
#ifndef EXCLUDE_FROM_XARALX

#ifdef TEST_WIZOPS
const CATID WizOpProbe::s_WizOpCategoryCLSID = {0x40fc6ed5,0x2438,0x11cf,{0xA3,0xDB,0x08,0x00,0x36,0xF1,0x25,0x02}};
#else
// {21451410-E7E2-11d0-9AF6-0020AFE14B3D}
const CATID WizOpProbe::s_WizOpCategoryCLSID = { 0x21451410, 0xe7e2, 0x11d0, { 0x9a, 0xf6, 0x0, 0x20, 0xaf, 0xe1, 0x4b, 0x3d } };
#endif

const String_16 WizOpRegistryEntry::s_UserNameKey = TEXT("UserName");
const String_16 WizOpRegistryEntry::s_ParamHintKey = TEXT("ParamHint");
//const String_8 WizOpRegistryEntry::s_InternalNameKey = TEXT("");


// We want better memory tracking
// Declare smart memory handling in Debug builds
#define new CAM_DEBUG_NEW



// Functions follow

/********************************************************************************************

>	BOOL WizOpRegistryEntry::GetInternalName(StringBase* const pValue)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Provides a string from this registry entry for the internal name

	Returns:	TRUE if it worked, FALSE if it didn't
	Outputs:	pValue:	The string of the internal name.

********************************************************************************************/
BOOL WizOpRegistryEntry::GetInternalName(StringBase* const pValue)
{
	BOOL Ok = TRUE;

	VersionIndependentProgID VIPID(*this);
	String_128 WholeEntry;

	Ok = VIPID.GetName(&WholeEntry);

	if (Ok)
	{
		// The entry is of the form "ProgID.LongName". We want the LongName bit
		static const TCHAR ProgIDDelimiter = TEXT('.');

		INT32 StartDelimiterPosition = WholeEntry.FindNextChar(ProgIDDelimiter);

		const UINT32 LengthToCopy = WholeEntry.Length() - StartDelimiterPosition - 1;

		if (StartDelimiterPosition >= 0 && LengthToCopy > 0)
		{
			WholeEntry.Mid(pValue, StartDelimiterPosition + 1, LengthToCopy);
		}
		else
		{
			TRACE( _T("WizOpRegistryEntry::GetInternalName - no name\n"));
			Ok = FALSE;
		}
	}

	return Ok;
}


/********************************************************************************************

>	BOOL WizOpRegistryEntry::GetUserName(StringBase* const pValue)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Provides a string from this registry entry for the user name

	Returns:	TRUE if it worked, FALSE if it didn't
	Outputs:	pString:	The string of the user name.

********************************************************************************************/
BOOL WizOpRegistryEntry::GetUserName(StringBase* const pValue)
{
	return GetValue(s_UserNameKey, pValue);
}


/********************************************************************************************

>	BOOL WizOpRegistryEntry::GetParamHint(StringBase* const pValue)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Provides a string from this registry entry for the parameter hint

	Returns:	TRUE if it worked, FALSE if it didn't
	Outputs:	pString:	The string of the parameter hint

********************************************************************************************/
BOOL WizOpRegistryEntry::GetParamHint(StringBase* const pValue)
{
	return GetValue(s_ParamHintKey, pValue);
}



/*
WizOps& g_WizOps()
{
	static WizOps g_WizOps;

	return g_WizOps;
}
*/

#endif

WizOps& GetWizOps()
{
	// This static dummy object is used for returning in the ERROR2 case
	// The original used to return a ptr to a local variable, which is a tad dangerous.
	// This solution is not ideal, because there's a permanent instance of an object
	// that will probably never be used.
	static WizOps DummyOps;

	WizOps* const pWizOps = GetApplication()->GetWizOps();
	ERROR2IF(pWizOps == NULL, DummyOps, "No WizOps");

	return *pWizOps;
}




/********************************************************************************************

>	WizOps::~WizOps()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	We need an overridden destructor to delete the WizOp's we stuck on the heap.

********************************************************************************************/
WizOps::~WizOps()
{
//	TRACE( _T("Deleting those WizOps now\n"));
	DeleteAll();
}



/********************************************************************************************

>	BOOL WizOps::InitializeFromRegistry()

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Goes whizzing through the registry to find all the WizOp's in it. Then
				builds this WizOps collection using those entries.

********************************************************************************************/
BOOL WizOps::InitializeFromRegistry()
{

	PORTNOTETRACE("other"," WizOps::InitializeFromRegistry - do nothing");
#ifndef EXCLUDE_FROM_XARALX
	BOOL Ok = TRUE;
	WizOpProbe Probe;
	GetLocalRegistry()->InitializeProbe(Probe);
	
	while (!Probe.IsLast() && Ok)
	{
		WizOpRegistryEntry Entry;
		// The internal name is given by the registry entry
		Ok = Probe.GetNextEntry(&Entry);
		
		String_64 InternalName;
		if (Ok)
		{	
			Ok = Entry.GetInternalName(&InternalName);
		}

		String_64 UserName;
		if (Ok)
		{	
			Entry.GetUserName(&UserName);
			if (UserName.IsEmpty())
			{
				UserName = InternalName;
			}
		}

		String_256 ParamHint;
		if (Ok)
		{	
			Entry.GetParamHint(&ParamHint);
		}

		if (Ok)
		{	
			Ok = AddWizOp(InternalName, UserName, ParamHint);
		}
	}

	if (!Ok)
	{
		TRACE( _T("Not all WizOps were created properly\n"));
	}
#endif
	return TRUE;	// we'll pretend it worked 'cos otherwise camelot won't start
}


/********************************************************************************************

>	BOOL WizOps::AddWizOp(	const StringBase& InternalName, const StringBase& UserName,
							const StringBase& ParamHint)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Adds a WizOp with the given gubbins to this set.

	Returns:	TRUE if if worked FALSE if it didn't

********************************************************************************************/
BOOL WizOps::AddWizOp(	const StringBase& InternalName, const StringBase& UserName,
						const StringBase& ParamHint)
{
	BOOL Success = TRUE;

	WizOp* const pNewWizOp = new WizOp(InternalName, UserName, ParamHint);

	if (pNewWizOp != NULL)
	{
		AddTail(pNewWizOp);
	}
	else
	{
		Success = FALSE;
	}

	return Success;
}



/********************************************************************************************

>	WizOp* WizOps::GetFirstWizOp() const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Cheapskate duplicate code container enumeration

	Returns:	The first WizOp in the set

********************************************************************************************/
WizOp* WizOps::GetFirstWizOp() const
{
	return (WizOp*)GetHead();
}


/********************************************************************************************

>	WizOp* WizOps::GetNextWizOp(const WizOp* const pWizOp) const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Cheapskate duplicate code container enumeration

	Inputs:		pWizOp:	Don't know why it's a pointer.
	Returns:	The WizOp after the given one in the set

********************************************************************************************/
WizOp* WizOps::GetNextWizOp(const WizOp* const pWizOp) const
{
	return (WizOp*)GetNext(pWizOp);
}


/********************************************************************************************

>	WizOp* WizOps::FindWizOpFromInternalName(const StringBase& InternalName) const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Allows access to the WizOp's vital statistics

	Inputs:		InternalName :	The InternalName of the desired WizOp
	Returns:	NULL if none found
				The WizOp with the InternalName (CLSID), given in the constructor,
				InternalName.

********************************************************************************************/
WizOp* WizOps::FindWizOpFromInternalName(const StringBase& InternalName) const
{
	WizOp* pWizOp = GetFirstWizOp();

	BOOL Found = FALSE;
	while (pWizOp != NULL && !Found)
	{
		if (pWizOp->GetInternalName() == InternalName)
		{
			Found = TRUE;
		}

		if (!Found)
		{
			pWizOp = GetNextWizOp(pWizOp);
		}
	}

	return pWizOp;
}






// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
//									W  I  Z  O  P
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //






/********************************************************************************************

>	WizOp::WizOp(	const StringBase& InternalName, const StringBase& UserName, 
					const StringBase& ParamHint)

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	This constructor provides the Wizard Properties with something to talk about.

	Inputs:		InternalName :	a persistant identifier for the WizOp. The CLSID of the entry
								extracted from the registry would be good.
				UserName :		the text that will appear in the Wizard Properties dialog.
								The "UserName" subkey under the InternalName (CLSID) is good.
				ParamHint:		If the WizOp can accept a parameter this string should
								contain some text explaining what it is.

********************************************************************************************/
WizOp::WizOp(	const StringBase& InternalName, const StringBase& UserName, 
				const StringBase& ParamHint) :
	m_Name(InternalName),
	m_UserName(UserName),
	m_ParamHint(ParamHint)
{
}


/********************************************************************************************

>	const StringBase& WizOp::GetInternalName() const
>	const StringBase& WizOp::GetUserName() const
>	const StringBase& WizOp::GetParamHint() const

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/06/97
	
	Purpose:	Allows access to the WizOp's vital statistics

	Returns:	Strings of things

********************************************************************************************/
const StringBase& WizOp::GetInternalName() const
{
	return (StringBase&)m_Name;
}


const StringBase& WizOp::GetUserName() const
{
	return (StringBase&)m_UserName;
}


const StringBase& WizOp::GetParamHint() const
{
	return (StringBase&)m_ParamHint;
}
